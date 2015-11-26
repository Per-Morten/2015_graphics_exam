#pragma once
#include <string>

#include <GL\glew.h>

class Texture
{
public:
    using TextureHandle = GLuint;

    Texture() = delete;
    Texture(const std::string& fileName, GLuint numberOfRows = 4) noexcept;
    ~Texture() noexcept;

    void bind() noexcept;
    GLuint getNumberOfRows() noexcept;
private:
    TextureHandle _textureHandle{};
    GLuint _numberOfRows{};

};