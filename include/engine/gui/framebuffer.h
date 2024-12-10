
#ifndef ENGINE_FRAMEBUFFER_H
#define ENGINE_FRAMEBUFFER_H


class Framebuffer {
public:
    Framebuffer(int width, int height);
    ~Framebuffer();

    void Bind();
    void Unbind();
    void Resize(int width, int height);
    unsigned int GetTexture() const;

private:
    unsigned int fbo;
    unsigned int texture;
    unsigned int rbo;

    int width;
    int height;

    void InitializeFramebuffer();
};


#endif //ENGINE_FRAMEBUFFER_H
