//===========================================================
// File: ShaderProgram.cpp	
// StudentName: Per-Morten Straume                          
//                                                          
// Exam 2015: IMT-2531 Graphics Programming Exam.                                
//===========================================================
#include "ShaderProgram.h"
#include "shader.hpp"

const ShaderProgram::UniformName ShaderProgram::color{"VertexColor"};
const ShaderProgram::UniformName ShaderProgram::viewMatrix{ "ViewMatrix" };
const ShaderProgram::UniformName ShaderProgram::modelMatrix{ "ModelMatrix" };
const ShaderProgram::UniformName ShaderProgram::normalMatrix{ "NormalMatrix" };
const ShaderProgram::UniformName ShaderProgram::ambientFactor{ "AmbientFactor" };
const ShaderProgram::UniformName ShaderProgram::lightDirection{ "LightDirection_worldspace" };
const ShaderProgram::UniformName ShaderProgram::textureOffset{ "TextureOffset" };
const ShaderProgram::UniformName ShaderProgram::worldScale{ "WorldScale" };
const ShaderProgram::UniformName ShaderProgram::projectionMatrix{ "ProjectionMatrix" };
const ShaderProgram::UniformName ShaderProgram::numberOfRows{ "NumberOfRows" };

ShaderProgram::ShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) noexcept
    : _programHandle(LoadShaders(vertexShaderPath.c_str(), fragmentShaderPath.c_str()))
{
    _uniformAddresses[color] = glGetUniformLocation(_programHandle, color.c_str());
    _uniformAddresses[viewMatrix] = glGetUniformLocation(_programHandle, viewMatrix.c_str());
    _uniformAddresses[modelMatrix] = glGetUniformLocation(_programHandle, modelMatrix.c_str());
    _uniformAddresses[normalMatrix] = glGetUniformLocation(_programHandle, normalMatrix.c_str());
    _uniformAddresses[ambientFactor] = glGetUniformLocation(_programHandle, ambientFactor.c_str());
    _uniformAddresses[lightDirection] = glGetUniformLocation(_programHandle, lightDirection.c_str());
    _uniformAddresses[textureOffset] = glGetUniformLocation(_programHandle, textureOffset.c_str());
    _uniformAddresses[worldScale] = glGetUniformLocation(_programHandle, worldScale.c_str());
    _uniformAddresses[projectionMatrix] = glGetUniformLocation(_programHandle, projectionMatrix.c_str());
    _uniformAddresses[numberOfRows] = glGetUniformLocation(_programHandle, numberOfRows.c_str());
}

ShaderProgram::~ShaderProgram() noexcept
{
    glDeleteProgram(_programHandle);
}

void ShaderProgram::bind() noexcept
{
    glUseProgram(_programHandle);
}

ShaderProgram::UniformAddress 
ShaderProgram::getUniformAddress(const UniformName& uniformName) noexcept
{
    return _uniformAddresses.at(uniformName);
}

