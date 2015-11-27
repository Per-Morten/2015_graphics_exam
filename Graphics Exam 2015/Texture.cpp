//===========================================================
// File: Texture.cpp	
// StudentName: Per-Morten Straume                          
//                                                          
// Exam 2015: IMT-2531 Graphics Programming Exam.                                
//===========================================================
#include "Texture.h"

#include "stb_image.h"

Texture::Texture(const std::string& fileName, GLuint numberOfRows) noexcept
    : _numberOfRows(numberOfRows)
{
    int width = 0;
    int height = 0;
    int numComponents = 0;

    unsigned char* imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);

    if (imageData == nullptr)
    {
        printf("Texture loading failed for texture: %s\n", fileName.c_str());
    }

    glGenTextures(1, &_textureHandle);
    glBindTexture(GL_TEXTURE_2D, _textureHandle);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    
    stbi_image_free(imageData);

}

Texture::~Texture() noexcept
{
    //glDeleteTextures(1, &_textureHandle);
}

void Texture::bind() noexcept
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _textureHandle);
}

GLuint Texture::getNumberOfRows() noexcept
{
    return _numberOfRows;
}
