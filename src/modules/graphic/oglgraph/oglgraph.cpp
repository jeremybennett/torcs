/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifdef WIN32
#include <windows.h>
#endif
#include "gl3.h"
#include <tgfclient.h>
#include <graphic.h>
#include "OGLRenderer.h"

static OGLRenderer* g_renderer = nullptr;

static int grInitTrack(tTrack* track) {
    if (!g_renderer) return -1;
    return g_renderer->initTrack(track) ? 0 : -1;
}

static int grInitCars(tSituation* s) {
    if (!g_renderer) return -1;
    return g_renderer->initCars(s) ? 0 : -1;
}

static int grInitView(int x, int y, int w, int h, int /*flag*/, void* /*screen*/) {
    if (!g_renderer) g_renderer = new OGLRenderer();
    return g_renderer->init(x, y, w, h) ? 0 : -1;
}

static int grRefresh(tSituation* s) {
    if (!g_renderer) return -1;
    g_renderer->refresh(s);
    return 0;
}

static void grShutdownCars() {
    if (g_renderer) g_renderer->shutdownCars();
}

static void grShutdownTrack() {
    if (g_renderer) {
        g_renderer->shutdownTrack();
        delete g_renderer;
        g_renderer = nullptr;
    }
}

static void grMuteForMenu() { /* no-op */ }

static int graphInit(int /*idx*/, void* pt) {
    tGraphicItf* itf = (tGraphicItf*)pt;
    itf->inittrack    = grInitTrack;
    itf->initcars     = grInitCars;
    itf->initview     = grInitView;
    itf->refresh      = grRefresh;
    itf->shutdowncars  = grShutdownCars;
    itf->shutdowntrack = grShutdownTrack;
    itf->muteformenu   = grMuteForMenu;
    return 0;
}

extern "C" int oglgraph(tModInfo* modInfo) {
    modInfo->name    = strdup("oglgraph");
    modInfo->desc    = strdup("Modern OpenGL 3.3 Core Profile Renderer");
    modInfo->fctInit = graphInit;
    modInfo->gfId    = 1;
    return 0;
}
