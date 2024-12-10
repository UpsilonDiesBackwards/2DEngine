
#ifndef ENGINE_GAMEVIEW_H
#define ENGINE_GAMEVIEW_H


#include "framebuffer.h"

class GameView {
public:
    GameView(int width, int height);
    ~GameView();

    void Render();
    void Resize(int width, int height);

    void ShowTriangle();
private:
    Framebuffer* framebuffer;
    int width, height;
};


#endif //ENGINE_GAMEVIEW_H
