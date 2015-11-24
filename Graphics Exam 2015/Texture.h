#pragma once
#include <string>

#include <GL\glew.h>

class Texture
{
public:
    using TextureHandle = GLuint;

    Texture() = delete;
    Texture(const std::string& fileName) noexcept;
    ~Texture() noexcept;

    void bind() noexcept;

private:
    TextureHandle _textureHandle{};
};