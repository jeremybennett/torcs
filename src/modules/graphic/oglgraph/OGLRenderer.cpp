/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "OGLRenderer.h"
#include "Texture.h"

#include <tgfclient.h>
#include <track.h>
#include <car.h>
#include <raceman.h>

#include <cmath>
#include <cstring>
#include <cstdio>
#include <string>

// Global shader pointers referenced by PostProcess.cpp
Shader* g_postShader  = nullptr;
Shader* g_bloomShader = nullptr;

// ---- Construction / Destruction ----

OGLRenderer::OGLRenderer()
    : m_particles(nullptr), m_skidMarks(nullptr),
      m_trackModel(nullptr), m_track(nullptr),
      m_hudVAO(0), m_hudVBO(0)
{
    m_lightDir[0]    = 0.5f;  m_lightDir[1]    = 0.5f;  m_lightDir[2]    = 1.0f;
    m_lightColor[0]  = 0.9f;  m_lightColor[1]  = 0.9f;  m_lightColor[2]  = 0.9f;
    m_ambientColor[0]= 0.3f;  m_ambientColor[1]= 0.3f;  m_ambientColor[2]= 0.3f;
    m_winX = m_winY = 0;
    m_winW = 800; m_winH = 600;
}

OGLRenderer::~OGLRenderer() {
    shutdownCars();
    shutdownTrack();
    delete m_particles;  m_particles = nullptr;
    delete m_skidMarks;  m_skidMarks = nullptr;
    TextureManager::instance().unloadAll();
    if (m_hudVAO) { glDeleteVertexArrays(1, &m_hudVAO); m_hudVAO = 0; }
    if (m_hudVBO) { glDeleteBuffers(1, &m_hudVBO); m_hudVBO = 0; }
}

// ---- Shader helpers ----

std::string OGLRenderer::getShaderPath(const std::string& name) {
    std::string dir = std::string(GetDataDir()) + "modules/graphic/oglgraph/shaders/";
    return dir + name;
}

bool OGLRenderer::loadShaders(const std::string& shaderDir) {
    bool ok = true;

    if (!m_geomShader.load(shaderDir + "geometry.vert", shaderDir + "geometry.frag")) {
        GfOut("OGLRenderer: WARNING - geometry shader failed to load\n");
        ok = false;
    }
    if (!m_shadowShader.load(shaderDir + "shadow.vert", shaderDir + "shadow.frag")) {
        GfOut("OGLRenderer: WARNING - shadow shader failed to load\n");
    }
    if (!m_postShader.load(shaderDir + "postprocess.vert", shaderDir + "postprocess.frag")) {
        GfOut("OGLRenderer: WARNING - postprocess shader failed to load\n");
    }
    if (!m_bloomShader.load(shaderDir + "postprocess.vert", shaderDir + "bloom.frag")) {
        GfOut("OGLRenderer: WARNING - bloom shader failed to load\n");
    }
    if (!m_particleShader.load(shaderDir + "particle.vert", shaderDir + "particle.frag")) {
        GfOut("OGLRenderer: WARNING - particle shader failed to load\n");
    }
    if (!m_skidShader.load(shaderDir + "skidmark.vert", shaderDir + "skidmark.frag")) {
        GfOut("OGLRenderer: WARNING - skidmark shader failed to load\n");
    }
    if (!m_hudShader.load(shaderDir + "hud.vert", shaderDir + "hud.frag")) {
        GfOut("OGLRenderer: WARNING - HUD shader failed to load\n");
    }

    // Publish shaders for PostProcess
    g_postShader  = &m_postShader;
    g_bloomShader = &m_bloomShader;

    return ok;
}

// ---- Initialisation ----

bool OGLRenderer::init(int x, int y, int width, int height) {
    m_winX = x; m_winY = y; m_winW = width; m_winH = height;

    loadShaders(getShaderPath(""));

    if (!m_shadowMap.init(2048)) {
        GfOut("OGLRenderer: WARNING - shadow map init failed\n");
    }

    if (!m_postProcess.init(width, height)) {
        GfOut("OGLRenderer: WARNING - post-process init failed\n");
    }

    m_particles = new ParticleSystem(5000);
    m_skidMarks = new SkidMarkSystem(100, 300);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    initHUDQuad();
    return true;
}

void OGLRenderer::initHUDQuad() {
    // Simple unit quad for HUD elements
    float verts[] = {
        0.0f, 0.0f,  0.0f, 0.0f,
        1.0f, 0.0f,  1.0f, 0.0f,
        1.0f, 1.0f,  1.0f, 1.0f,
        0.0f, 0.0f,  0.0f, 0.0f,
        1.0f, 1.0f,  1.0f, 1.0f,
        0.0f, 1.0f,  0.0f, 1.0f
    };
    glGenVertexArrays(1, &m_hudVAO);
    glGenBuffers(1, &m_hudVBO);
    glBindVertexArray(m_hudVAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_hudVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)(2*sizeof(float)));
    glBindVertexArray(0);
}

bool OGLRenderer::initTrack(tTrack* track) {
    m_track = track;

    void* trackHandle = GfParmReadFile(track->filename, GFPARM_RMODE_STD | GFPARM_RMODE_CREAT);
    if (!trackHandle) {
        GfOut("OGLRenderer::initTrack: could not read track file '%s'\n", track->filename);
        return false;
    }

    const char* acFile = GfParmGetStr(trackHandle, TRK_SECT_GRAPH, TRK_ATT_3DDESC, "");

    // Extract directory from track filename
    char trackDir[1024];
    strncpy(trackDir, track->filename, sizeof(trackDir)-1);
    trackDir[sizeof(trackDir)-1] = '\0';
    char* lastSlash = strrchr(trackDir, '/');
    if (lastSlash) *(lastSlash+1) = '\0';
    else trackDir[0] = '\0';

    // Load lighting parameters
    m_lightDir[0] = GfParmGetNum(trackHandle, TRK_SECT_GRAPH, TRK_ATT_LIPOS_X, NULL, 0.5f);
    m_lightDir[1] = GfParmGetNum(trackHandle, TRK_SECT_GRAPH, TRK_ATT_LIPOS_Y, NULL, 0.5f);
    m_lightDir[2] = GfParmGetNum(trackHandle, TRK_SECT_GRAPH, TRK_ATT_LIPOS_Z, NULL, 1.0f);
    float llen = sqrtf(m_lightDir[0]*m_lightDir[0]+m_lightDir[1]*m_lightDir[1]+m_lightDir[2]*m_lightDir[2]);
    if (llen > 1e-6f) { m_lightDir[0]/=llen; m_lightDir[1]/=llen; m_lightDir[2]/=llen; }

    m_ambientColor[0] = GfParmGetNum(trackHandle, TRK_SECT_GRAPH, TRK_ATT_AMBIENT_R, NULL, 0.3f);
    m_ambientColor[1] = GfParmGetNum(trackHandle, TRK_SECT_GRAPH, TRK_ATT_AMBIENT_G, NULL, 0.3f);
    m_ambientColor[2] = GfParmGetNum(trackHandle, TRK_SECT_GRAPH, TRK_ATT_AMBIENT_B, NULL, 0.3f);
    m_lightColor[0]   = GfParmGetNum(trackHandle, TRK_SECT_GRAPH, TRK_ATT_DIFFUSE_R, NULL, 0.9f);
    m_lightColor[1]   = GfParmGetNum(trackHandle, TRK_SECT_GRAPH, TRK_ATT_DIFFUSE_G, NULL, 0.9f);
    m_lightColor[2]   = GfParmGetNum(trackHandle, TRK_SECT_GRAPH, TRK_ATT_DIFFUSE_B, NULL, 0.9f);

    if (acFile && strlen(acFile) > 0) {
        char acPath[1024];
        snprintf(acPath, sizeof(acPath), "%s%s", trackDir, acFile);
        m_trackTexPath = trackDir;
        m_trackModel   = AC3DLoader::load(acPath, trackDir);
        if (!m_trackModel)
            GfOut("OGLRenderer::initTrack: WARNING - could not load track model '%s'\n", acPath);
    }

    GfParmReleaseHandle(trackHandle);
    return true;
}

bool OGLRenderer::initCars(tSituation* s) {
    const char* dataDir = GetDataDir();

    for (int i = 0; i < s->_ncars; i++) {
        tCarElt* car = s->cars[i];
        CarRenderData crd;
        memset(&crd, 0, sizeof(crd));
        crd.carIdx = car->index;

        // Build paths
        char path[1024];
        std::string modelBase = std::string(dataDir) + "data/cars/models/" + car->_carName + "/";

        snprintf(path, sizeof(path), "%s%s.ac", modelBase.c_str(), car->_carName);
        crd.bodyModel = AC3DLoader::load(path, modelBase);
        if (!crd.bodyModel)
            GfOut("OGLRenderer::initCars: WARNING - no body model for car '%s'\n", car->_carName);

        for (int w = 0; w < 4; w++) {
            snprintf(path, sizeof(path), "%swheel%d.ac", modelBase.c_str(), w);
            crd.wheelModels[w] = AC3DLoader::load(path, modelBase);
        }

        // Identity transforms initially
        float id[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
        memcpy(crd.bodyTransform, id, sizeof(id));
        for (int w = 0; w < 4; w++) memcpy(crd.wheelTransforms[w], id, sizeof(id));

        m_cars.push_back(crd);
    }
    return true;
}

// ---- Shutdown ----

void OGLRenderer::shutdownCars() {
    for (auto& crd : m_cars) {
        delete crd.bodyModel;
        for (int w = 0; w < 4; w++) delete crd.wheelModels[w];
    }
    m_cars.clear();
}

void OGLRenderer::shutdownTrack() {
    delete m_trackModel;
    m_trackModel = nullptr;
    m_track = nullptr;
}

// ---- Per-frame update ----

void OGLRenderer::buildTransformMatrix(float* mat16, const float pos[3], const float rotMat[3][3]) {
    mat16[0]  = rotMat[0][0]; mat16[1]  = rotMat[1][0]; mat16[2]  = rotMat[2][0]; mat16[3]  = 0.0f;
    mat16[4]  = rotMat[0][1]; mat16[5]  = rotMat[1][1]; mat16[6]  = rotMat[2][1]; mat16[7]  = 0.0f;
    mat16[8]  = rotMat[0][2]; mat16[9]  = rotMat[1][2]; mat16[10] = rotMat[2][2]; mat16[11] = 0.0f;
    mat16[12] = pos[0];       mat16[13] = pos[1];       mat16[14] = pos[2];       mat16[15] = 1.0f;
}

void OGLRenderer::updateCarsFromSituation(tSituation* s) {
    for (auto& crd : m_cars) {
        tCarElt* car = nullptr;
        for (int i = 0; i < s->_ncars; i++) {
            if (s->cars[i]->index == crd.carIdx) { car = s->cars[i]; break; }
        }
        if (!car) continue;

        float pos[3] = { (float)car->_pos_X, (float)car->_pos_Y, (float)car->_pos_Z };
        float yaw   = (float)car->_yaw;
        float pitch = (float)car->_pitch;
        float roll  = (float)car->_roll;

        // Rotation: Z-Y-X Euler (yaw=az, pitch=ay, roll=ax)
        float cy = cosf(yaw),   sy = sinf(yaw);
        float cp = cosf(pitch), sp = sinf(pitch);
        float cr = cosf(roll),  sr = sinf(roll);

        float rotMat[3][3] = {
            { cy*cp,  cy*sp*sr - sy*cr,  cy*sp*cr + sy*sr },
            { sy*cp,  sy*sp*sr + cy*cr,  sy*sp*cr - cy*sr },
            { -sp,    cp*sr,             cp*cr            }
        };
        buildTransformMatrix(crd.bodyTransform, pos, rotMat);

        // Wheel transforms: approximate from car GC + relative position
        for (int w = 0; w < 4; w++) {
            float wpos[3] = {
                pos[0] + car->priv.wheel[w].relPos.x,
                pos[1] + car->priv.wheel[w].relPos.y,
                pos[2] + car->priv.wheel[w].relPos.z
            };
            float identity[3][3] = {{1,0,0},{0,1,0},{0,0,1}};
            buildTransformMatrix(crd.wheelTransforms[w], wpos, identity);
        }
    }
}

void OGLRenderer::updateCamera(tSituation* s) {
    if (s->_ncars <= 0) return;

    // Prefer first human-driven car, fall back to first car
    tCarElt* car = s->cars[0];
    for (int i = 0; i < s->_ncars; i++) {
        if (s->cars[i]->_driverType == RM_DRV_HUMAN) { car = s->cars[i]; break; }
    }

    float cx = (float)car->_pos_X;
    float cy = (float)car->_pos_Y;
    float cz = (float)car->_pos_Z;
    float yaw = (float)car->_yaw;

    // Chase camera: 8 m behind, 3 m up
    float camX = cx - cosf(yaw) * 8.0f;
    float camY = cy - sinf(yaw) * 8.0f;
    float camZ = cz + 3.0f;

    float tgtX = cx + cosf(yaw) * 5.0f;
    float tgtY = cy + sinf(yaw) * 5.0f;
    float tgtZ = cz + 0.5f;

    m_camera.setPosition(camX, camY, camZ);
    m_camera.setTarget(tgtX, tgtY, tgtZ);
    m_camera.setUp(0.0f, 0.0f, 1.0f);
    m_camera.setPerspective(60.0f, (float)m_winW / (float)m_winH, 0.1f, 3000.0f);
}

// ---- Render passes ----

void OGLRenderer::renderShadowPass() {
    if (!m_shadowShader.id()) return;

    float sceneBounds[6] = { -500,-500,-10, 500,500,50 };
    float lightSpaceMat[16];
    m_shadowMap.getLightSpaceMatrix(m_lightDir, sceneBounds, lightSpaceMat);

    m_shadowMap.bindForWriting();
    glCullFace(GL_FRONT);

    m_shadowShader.use();
    m_shadowShader.setMat4("lightSpaceMatrix", lightSpaceMat);

    renderGeometry(true);
    renderCars(true);

    glCullFace(GL_BACK);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OGLRenderer::renderGeometry(bool shadowPass) {
    Shader& sh = shadowPass ? m_shadowShader : m_geomShader;
    if (!sh.id()) return;
    sh.use();

    float lightSpaceMat[16];
    float sceneBounds[6] = { -500,-500,-10, 500,500,50 };
    m_shadowMap.getLightSpaceMatrix(m_lightDir, sceneBounds, lightSpaceMat);

    if (!shadowPass) {
        float viewMat[16], projMat[16];
        m_camera.getViewMatrix(viewMat);
        m_camera.getProjectionMatrix(projMat);
        sh.setMat4("view", viewMat);
        sh.setMat4("projection", projMat);
        sh.setMat4("lightSpaceMatrix", lightSpaceMat);
        sh.setVec3("lightDir",     m_lightDir[0],     m_lightDir[1],     m_lightDir[2]);
        sh.setVec3("lightColor",   m_lightColor[0],   m_lightColor[1],   m_lightColor[2]);
        sh.setVec3("ambientColor", m_ambientColor[0], m_ambientColor[1], m_ambientColor[2]);
        float camPos[3]; m_camera.getPosition(camPos);
        sh.setVec3("viewPos", camPos[0], camPos[1], camPos[2]);
        m_shadowMap.bindForReading(4);
        sh.setInt("shadowMap", 4);
    }

    if (!m_trackModel) return;

    float identity[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
    sh.setMat4("model", identity);

    for (auto& mesh : m_trackModel->meshes) {
        if (!mesh || !mesh->valid()) continue;
        if (!shadowPass) {
            sh.setVec4("matAmbient",  mesh->ambient[0],  mesh->ambient[1],  mesh->ambient[2],  mesh->ambient[3]);
            sh.setVec4("matDiffuse",  mesh->diffuse[0],  mesh->diffuse[1],  mesh->diffuse[2],  mesh->diffuse[3]);
            sh.setVec4("matSpecular", mesh->specular[0], mesh->specular[1], mesh->specular[2], mesh->specular[3]);
            sh.setFloat("matShininess", mesh->shininess);

            glActiveTexture(GL_TEXTURE0);
            GLuint tex = TextureManager::instance().load(mesh->texturePath);
            glBindTexture(GL_TEXTURE_2D, tex);
            sh.setInt("texture1", 0);
        }
        mesh->draw();
    }
}

void OGLRenderer::renderCars(bool shadowPass) {
    Shader& sh = shadowPass ? m_shadowShader : m_geomShader;
    if (!sh.id()) return;
    sh.use();

    float lightSpaceMat[16];
    float sceneBounds[6] = { -500,-500,-10, 500,500,50 };
    m_shadowMap.getLightSpaceMatrix(m_lightDir, sceneBounds, lightSpaceMat);

    if (!shadowPass) {
        float viewMat[16], projMat[16];
        m_camera.getViewMatrix(viewMat);
        m_camera.getProjectionMatrix(projMat);
        sh.setMat4("view", viewMat);
        sh.setMat4("projection", projMat);
        sh.setMat4("lightSpaceMatrix", lightSpaceMat);
        sh.setVec3("lightDir",     m_lightDir[0],     m_lightDir[1],     m_lightDir[2]);
        sh.setVec3("lightColor",   m_lightColor[0],   m_lightColor[1],   m_lightColor[2]);
        sh.setVec3("ambientColor", m_ambientColor[0], m_ambientColor[1], m_ambientColor[2]);
        float camPos[3]; m_camera.getPosition(camPos);
        sh.setVec3("viewPos", camPos[0], camPos[1], camPos[2]);
        m_shadowMap.bindForReading(4);
        sh.setInt("shadowMap", 4);
    }

    for (auto& crd : m_cars) {
        // Draw body
        if (crd.bodyModel) {
            sh.setMat4("model", crd.bodyTransform);
            for (auto& mesh : crd.bodyModel->meshes) {
                if (!mesh || !mesh->valid()) continue;
                if (!shadowPass) {
                    sh.setVec4("matAmbient",  mesh->ambient[0],  mesh->ambient[1],  mesh->ambient[2],  mesh->ambient[3]);
                    sh.setVec4("matDiffuse",  mesh->diffuse[0],  mesh->diffuse[1],  mesh->diffuse[2],  mesh->diffuse[3]);
                    sh.setVec4("matSpecular", mesh->specular[0], mesh->specular[1], mesh->specular[2], mesh->specular[3]);
                    sh.setFloat("matShininess", mesh->shininess);
                    glActiveTexture(GL_TEXTURE0);
                    GLuint tex = TextureManager::instance().load(mesh->texturePath);
                    glBindTexture(GL_TEXTURE_2D, tex);
                    sh.setInt("texture1", 0);
                }
                mesh->draw();
            }
        }

        // Draw wheels
        for (int w = 0; w < 4; w++) {
            if (!crd.wheelModels[w]) continue;
            sh.setMat4("model", crd.wheelTransforms[w]);
            for (auto& mesh : crd.wheelModels[w]->meshes) {
                if (!mesh || !mesh->valid()) continue;
                if (!shadowPass) {
                    sh.setVec4("matAmbient",  mesh->ambient[0],  mesh->ambient[1],  mesh->ambient[2],  mesh->ambient[3]);
                    sh.setVec4("matDiffuse",  mesh->diffuse[0],  mesh->diffuse[1],  mesh->diffuse[2],  mesh->diffuse[3]);
                    sh.setVec4("matSpecular", mesh->specular[0], mesh->specular[1], mesh->specular[2], mesh->specular[3]);
                    sh.setFloat("matShininess", mesh->shininess);
                    glActiveTexture(GL_TEXTURE0);
                    GLuint tex = TextureManager::instance().load(mesh->texturePath);
                    glBindTexture(GL_TEXTURE_2D, tex);
                    sh.setInt("texture1", 0);
                }
                mesh->draw();
            }
        }
    }
}

void OGLRenderer::renderParticles() {
    if (!m_particles || m_particles->liveCount() <= 0) return;
    if (!m_particleShader.id()) return;

    m_particleShader.use();
    float viewMat[16], projMat[16];
    m_camera.getViewMatrix(viewMat);
    m_camera.getProjectionMatrix(projMat);
    m_particleShader.setMat4("view", viewMat);
    m_particleShader.setMat4("projection", projMat);

    float camPos[3]; m_camera.getPosition(camPos);
    m_particles->draw(viewMat, camPos);
}

void OGLRenderer::renderSkidMarks() {
    if (!m_skidShader.id()) return;

    m_skidShader.use();
    float viewMat[16], projMat[16];
    m_camera.getViewMatrix(viewMat);
    m_camera.getProjectionMatrix(projMat);
    m_skidShader.setMat4("view", viewMat);
    m_skidShader.setMat4("projection", projMat);
    m_skidShader.setFloat("alpha", 0.8f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE);
    m_skidMarks->draw();
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
}

void OGLRenderer::renderHUD(tSituation* s) {
    if (!m_hudShader.id() || !m_hudVAO) return;
    if (s->_ncars <= 0) return;

    // Orthographic projection for 2D HUD
    float w = (float)m_winW;
    float h = (float)m_winH;
    float ortho[16] = {
        2.0f/w, 0,       0, 0,
        0,      2.0f/h,  0, 0,
        0,      0,      -1, 0,
       -1,     -1,       0, 1
    };

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_hudShader.use();
    m_hudShader.setMat4("projection", ortho);

    // Speed bar background (dark grey)
    tCarElt* car = s->cars[0];
    for (int i = 0; i < s->_ncars; i++) {
        if (s->cars[i]->_driverType == RM_DRV_HUMAN) { car = s->cars[i]; break; }
    }
    float speed = sqrtf((float)(car->_speed_x * car->_speed_x + car->_speed_y * car->_speed_y));
    float speedKmh = speed * 3.6f;

    // Simple speed bar: bottom-left corner, 200px wide, 20px tall
    float barW  = 200.0f * (speedKmh / 300.0f); // scale to 300 km/h max
    if (barW > 200.0f) barW = 200.0f;

    // Draw background quad at position (10, 10), size (200, 20)
    auto drawQuad = [&](float x, float y, float qw, float qh, float r, float g, float b, float a) {
        // Update VBO with scaled position
        float verts[] = {
            x,    y,     0.0f, 0.0f,
            x+qw, y,     1.0f, 0.0f,
            x+qw, y+qh,  1.0f, 1.0f,
            x,    y,     0.0f, 0.0f,
            x+qw, y+qh,  1.0f, 1.0f,
            x,    y+qh,  0.0f, 1.0f
        };
        glBindBuffer(GL_ARRAY_BUFFER, m_hudVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verts), verts);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        m_hudShader.setVec4("color", r, g, b, a);
        glBindVertexArray(m_hudVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    };

    drawQuad(10.0f, 10.0f, 200.0f, 20.0f, 0.1f, 0.1f, 0.1f, 0.6f);
    drawQuad(10.0f, 10.0f, barW,   20.0f, 0.2f, 0.6f, 1.0f, 0.8f);

    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
}

// ---- Main refresh ----

void OGLRenderer::refresh(tSituation* s) {
    updateCamera(s);
    updateCarsFromSituation(s);

    // Shadow pass
    renderShadowPass();

    // HDR pass
    m_postProcess.bindHDRFramebuffer();
    glViewport(m_winX, m_winY, m_winW, m_winH);
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderGeometry(false);
    renderCars(false);
    renderParticles();
    renderSkidMarks();

    // Tone mapping + bloom
    glViewport(m_winX, m_winY, m_winW, m_winH);
    m_postProcess.render(1.0f);

    // 2D HUD on top of composited frame
    renderHUD(s);
}
