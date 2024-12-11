
#ifndef ENGINE_EDITVIEW_H
#define ENGINE_EDITVIEW_H


#include "framebuffer.h"

class EditView {
public:
    EditView(int width, int height);
    ~EditView();

    void Render();
    void Resize(int width, int height);
private:
    Framebuffer* framebuffer;
    int width, height;
};


#endif //ENGINE_EDITVIEW_H