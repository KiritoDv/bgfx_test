#include <iostream>
#include "core/core.h"

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

using namespace std;

struct PosColorVertex {
    float mx;
    float my;
    float mz;

    uint32_t mabgr;

    static void init() {
        ms_layout
            .begin()
            .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
            .add(bgfx::Attrib::Color0,   4, bgfx::AttribType::Uint8, true)
            .end();
    };

    static bgfx::VertexLayout ms_layout;
};

int main() {
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
    };

    auto update = []() {
    };

    Core::init(&init, update);
}
