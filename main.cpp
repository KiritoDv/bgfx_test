#include <iostream>
#include <functional>
#include "core/core.h"

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <bx/math.h>
#include <audio/AudioPlayer.h>

using namespace std;

struct PosColorVertex {
    float mx;
    float my;
    float mz;

    uint32_t m_abgr;

    static void init() {
        ms_layout
            .begin()
            .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
            .add(bgfx::Attrib::Color0,   4, bgfx::AttribType::Uint8, true)
            .end();
    };

    static bgfx::VertexLayout ms_layout;
};

bgfx::VertexLayout PosColorVertex::ms_layout;

AudioPlayer a;

int main() {

    a.initDevice();

    a.preloadSound(1, R"(/home/alex/Downloads/test.wav)");

    static PosColorVertex s_cubeVertices[] = {
        { 0.5f,  0.5f,  0.0f, 0xff0000ff },
        { 0.5f,  -0.5f, 0.0f, 0xff0000ff },
        { -0.5f, -0.5f, 0.0f, 0xff00ff00 },
        { -0.5f, 0.5f,  0.0f, 0xff00ff00 },
    };

    static const uint16_t s_cubeTriList[] = {
        0, 1, 3,
        1, 2, 3
    };

    bgfx::VertexBufferHandle m_vbh;
    bgfx::IndexBufferHandle m_ibh;

    auto init = [&]() {
        PosColorVertex::init();

        m_vbh = bgfx::createVertexBuffer(
            bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices)),
            PosColorVertex::ms_layout
        );

        m_ibh = bgfx::createIndexBuffer(
            bgfx::makeRef(s_cubeTriList, sizeof(s_cubeTriList))
        );
    };

    int counter = 0;

    auto update = [&]() {

        counter++;

        const bx::Vec3 at  = { 0.0f, 0.0f,   0.0f };
        const bx::Vec3 eye = { 0.0f, 0.0f, 10.0f };

        int WIDTH = 640;
        int HEIGHT = 480;

        float view[16];
        bx::mtxLookAt(view, eye, at);

        float proj[16];
        bx::mtxProj(proj,
                    60.0f,
                    float(WIDTH)/float(HEIGHT),
                    0.1f, 100.0f,
                    bgfx::getCaps()->homogeneousDepth);

        bgfx::setViewTransform(0, view, proj);

        bgfx::setViewRect(0, 0, 0,
                          WIDTH,
                          HEIGHT);

        bgfx::touch(0);

        float mtx[16];
        bx::mtxRotateZ(mtx, counter / 3 % 360);

        mtx[12] = 0.0f;
        mtx[13] = 0.0f;
        mtx[14] = 0.0f;

        bgfx::setTransform(mtx);

        bgfx::setVertexBuffer(0, m_vbh);
        bgfx::setIndexBuffer(m_ibh);
        bgfx::setState(BGFX_STATE_DEFAULT);

    };

    Core::init(init, update);
}
