/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#pragma once
#include "gl3.h"
#include "Shader.h"
#include "Camera.h"
#include "ShadowMap.h"
#include "PostProcess.h"
#include "Particles.h"
#include "SkidMarks.h"
#include "AC3DLoader.h"
#include <vector>
#include <string>

// Forward declarations of TORCS types to avoid plib dependency in this header
struct tTrack;
struct Situation;
typedef Situation tSituation;
struct CarElt;
typedef CarElt tCarElt;

struct CarRenderData {
    int carIdx;
    AC3DModel* bodyModel;
    AC3DModel* wheelModels[4];
    float bodyTransform[16];
    float wheelTransforms[4][16];
};

class OGLRenderer {
public:
    OGLRenderer();
    ~OGLRenderer();

    bool init(int x, int y, int width, int height);
    bool initTrack(tTrack* track);
    bool initCars(tSituation* s);
    void refresh(tSituation* s);
    void shutdownCars();
    void shutdownTrack();

private:
    // Shaders
    Shader m_geomShader;
    Shader m_shadowShader;
    Shader m_postShader;
    Shader m_bloomShader;
    Shader m_particleShader;
    Shader m_skidShader;
    Shader m_hudShader;

    // Sub-systems
    Camera        m_camera;
    ShadowMap     m_shadowMap;
    PostProcess   m_postProcess;
    ParticleSystem* m_particles;
    SkidMarkSystem* m_skidMarks;

    // Scene data
    AC3DModel*   m_trackModel;
    std::string  m_trackTexPath;
    tTrack*      m_track;

    std::vector<CarRenderData> m_cars;

    // Lighting
    float m_lightDir[3];
    float m_lightColor[3];
    float m_ambientColor[3];

    // Viewport
    int m_winX, m_winY, m_winW, m_winH;

    // HUD quad
    GLuint m_hudVAO, m_hudVBO;

    // Private methods
    bool loadShaders(const std::string& shaderDir);
    std::string getShaderPath(const std::string& name);

    void updateCamera(tSituation* s);
    void updateCarsFromSituation(tSituation* s);

    void renderShadowPass();
    void renderGeometry(bool shadowPass);
    void renderCars(bool shadowPass);
    void renderParticles();
    void renderSkidMarks();
    void renderHUD(tSituation* s);

    static void buildTransformMatrix(float* mat16, const float pos[3], const float rotMat[3][3]);
    void initHUDQuad();
};
