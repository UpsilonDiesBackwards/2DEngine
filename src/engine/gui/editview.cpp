
#include "engine/gui/editview.h"
#include "glad/glad.h"
#include "imgui.h"

EditView::EditView(int width, int height) : width(width), height(height) { framebuffer = new Framebuffer(width, height); }

EditView::~EditView() { delete framebuffer; }

void EditView::Render() {
    framebuffer->Bind();

    float aRatio = static_cast<float>(width) / static_cast<float>(height);

    glViewport(0, 0, width, height);
    glClearColor(0.18f, 0.21f, 0.23f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render Space


    framebuffer->Unbind();

    ImVec2 winSize = ImGui::GetContentRegionAvail();
    float wRatio = winSize.x / winSize.y;

    if (winSize.x != width || winSize.y != height) {
        width = static_cast<int>(winSize.x);
        height = static_cast<int>(winSize.y);
        Resize(width, height);
    }

    // Retain Aspect Ratio
    if (wRatio > aRatio) {
        width = static_cast<int>(winSize.y * aRatio);
        height = static_cast<int>(winSize.y);
    } else {
        width = static_cast<int>(winSize.x);
        height = static_cast<int>(winSize.x / aRatio);
    }

    ImGui::Image(framebuffer->GetTexture(), ImVec2(winSize.x, winSize.y), ImVec2(0, 1), ImVec2(1, 0));
}

void EditView::Resize(int width, int height) {
    this->width = width;
    this->height = height;

    framebuffer->Resize(width, height);
}
