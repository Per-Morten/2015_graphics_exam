#include "Renderer.h"

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <tuple>

namespace
{
    namespace Local
    {
        decltype(auto) createCube()
        {
            using MeshInfo = std::tuple < std::vector<glm::vec3>
                , std::vector<glm::vec3>
                , std::vector<glm::vec2>
                , std::vector < GLuint >> ;

            std::vector<glm::vec3> cubePositions =
            {
                //VERTEX///////////////////////////
                //front
                glm::vec3(-5.0f, -5.0f, 5.0f),
                glm::vec3(5.0f, -5.0f, 5.0f),
                glm::vec3(5.0f, 5.0f, 5.0f),
                glm::vec3(-5.0f, 5.0f, 5.0f),

                //right
                glm::vec3(5.0f, -5.0f, 5.0f),
                glm::vec3(5.0f, -5.0f, -5.0f),
                glm::vec3(5.0f, 5.0f, -5.0f),
                glm::vec3(5.0f, 5.0f, 5.0f),

                //back
                glm::vec3(5.0f, -5.0f, -5.0f),
                glm::vec3(-5.0f, -5.0f, -5.0f),
                glm::vec3(-5.0f, 5.0f, -5.0f),
                glm::vec3(5.0f, 5.0f, -5.0f),

                //left
                glm::vec3(-5.0f, -5.0f, -5.0f),
                glm::vec3(-5.0f, -5.0f, 5.0f),
                glm::vec3(-5.0f, 5.0f, 5.0f),
                glm::vec3(-5.0f, 5.0f, -5.0f),

                //top
                glm::vec3(-5.0f, 5.0f, 5.0f),
                glm::vec3(5.0f, 5.0f, 5.0f),
                glm::vec3(5.0f, 5.0f, -5.0f),
                glm::vec3(-5.0f, 5.0f, -5.0f),

                //bottom
                glm::vec3(-5.0f, -5.0f, -5.0f),
                glm::vec3(5.0f, -5.0f, -5.0f),
                glm::vec3(5.0f, -5.0f, 5.0f),
                glm::vec3(-5.0f, -5.0f, 5.0f)
            };

            std::vector<glm::vec3> cubeNormals =
            {
                ////////////////////////////////////
                //front
                glm::vec3(0.0, 0.0, 1.0),
                glm::vec3(0.0, 0.0, 1.0),
                glm::vec3(0.0, 0.0, 1.0),
                glm::vec3(0.0, 0.0, 1.0),

                //right
                glm::vec3(1.0, 0.0, 0.0),
                glm::vec3(1.0, 0.0, 0.0),
                glm::vec3(1.0, 0.0, 0.0),
                glm::vec3(1.0, 0.0, 0.0),

                //back
                glm::vec3(0.0, 0.0, -1.0),
                glm::vec3(0.0, 0.0, -1.0),
                glm::vec3(0.0, 0.0, -1.0),
                glm::vec3(0.0, 0.0, -1.0),

                //left
                glm::vec3(-1.0, 0.0, 0.0),
                glm::vec3(-1.0, 0.0, 0.0),
                glm::vec3(-1.0, 0.0, 0.0),
                glm::vec3(-1.0, 0.0, 0.0),

                //top
                glm::vec3(0.0, 1.0, 0.0),
                glm::vec3(0.0, 1.0, 0.0),
                glm::vec3(0.0, 1.0, 0.0),
                glm::vec3(0.0, 1.0, 0.0),

                //bottom
                glm::vec3(0.0, -1.0, 0.0),
                glm::vec3(0.0, -1.0, 0.0),
                glm::vec3(0.0, -1.0, 0.0),
                glm::vec3(0.0, -1.0, 0.0)
            };

            std::vector<glm::vec2> cubeTextureCoordinates =
            {
                //front
                glm::vec2(0.0f, 0.0f),
                glm::vec2(1.0f, 0.0f),
                glm::vec2(1.0f, 1.0f),
                glm::vec2(0.0f, 1.0f),

                //right
                glm::vec2(0.0f, 0.0f),
                glm::vec2(1.0f, 0.0f),
                glm::vec2(1.0f, 1.0f),
                glm::vec2(0.0f, 1.0f),

                //back
                glm::vec2(0.0f, 0.0f),
                glm::vec2(1.0f, 0.0f),
                glm::vec2(1.0f, 1.0f),
                glm::vec2(0.0f, 1.0f),

                //left
                glm::vec2(0.0f, 0.0f),
                glm::vec2(1.0f, 0.0f),
                glm::vec2(1.0f, 1.0f),
                glm::vec2(0.0f, 1.0f),

                //top
                glm::vec2(0.0f, 0.0f),
                glm::vec2(1.0f, 0.0f),
                glm::vec2(1.0f, 1.0f),
                glm::vec2(0.0f, 1.0f),

                //bottom
                glm::vec2(0.0f, 0.0f),
                glm::vec2(1.0f, 0.0f),
                glm::vec2(1.0f, 1.0f),
                glm::vec2(0.0f, 1.0f)
            };

            std::vector<GLuint> IBO =
            {
                //front
                0,1,2, 0,2,3,

                //right
                4,5,6, 4,6,7,

                //back
                8,9,10, 8,10,11,

                //left
                12,13,14, 12,14,15,

                //top
                16,17,18, 16,18,19,

                //bottom
                20,21,22, 20,22,23
            };

            MeshInfo result = std::make_tuple(cubePositions, cubeNormals, cubeTextureCoordinates, IBO);
            return result;
        }
    }
}

Renderer::Renderer(GLint width,
                   GLint height,
                   Camera& camera) noexcept
    : width(width)
    , height(height)
    , _camera(camera)
    , _projectionMatrix(glm::perspective(glm::pi<float>() / 3.0f,
                                         static_cast<float>(width) / static_cast<float>(height),
                                         camera.minViewDistance, camera.maxViewDistance))
{
}

Renderer::~Renderer() noexcept
{
    for (auto& shaderProgram : _shaderPrograms)
    {
        delete shaderProgram.second;
        shaderProgram.second = nullptr;
    }
    for (auto& mesh : _meshes)
    {
        delete mesh.second;
        mesh.second = nullptr;
    }
    for (auto& texture : _textures)
    {
        delete texture.second;
        texture.second = nullptr;
    }
    SDL_GL_DeleteContext(_context);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void Renderer::clear() noexcept
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::render(const std::string& shaderName,
                      const std::string& meshName,
                      const std::string& textureName,
                      const glm::mat4& modelMatrix,
                      const glm::vec4& color,
                      const glm::vec2& textureOffset) noexcept
{
    if (_shaderPrograms[shaderName] != nullptr)
    {
        static ShaderProgram::UniformAddress colorId;
        static ShaderProgram::UniformAddress viewMatrixId;
        static ShaderProgram::UniformAddress modelMatrixId;
        static ShaderProgram::UniformAddress mvpId;
        static ShaderProgram::UniformAddress normalMatrixId;
        static ShaderProgram::UniformAddress ambientFactorId;
        static ShaderProgram::UniformAddress lightDirectionId;
        static ShaderProgram::UniformAddress textureOffsetId;
        static ShaderProgram::UniformAddress worldScaleId;
        static ShaderProgram::UniformAddress projectionMatrixId;

        static std::string lastShader;

        if (lastShader != shaderName)
        {
            _shaderPrograms[shaderName]->bind();
            lastShader = shaderName;

            // Set it here, cause looking up map in debug can be slow. Especially if its done 1016 times a second :P
            colorId = _shaderPrograms[shaderName]->getUniformAddress(ShaderProgram::color);
            viewMatrixId = _shaderPrograms[shaderName]->getUniformAddress(ShaderProgram::viewMatrix);
            modelMatrixId = _shaderPrograms[shaderName]->getUniformAddress(ShaderProgram::modelMatrix);
            mvpId = _shaderPrograms[shaderName]->getUniformAddress(ShaderProgram::mvp);
            normalMatrixId = _shaderPrograms[shaderName]->getUniformAddress(ShaderProgram::normalMatrix);
            ambientFactorId = _shaderPrograms[shaderName]->getUniformAddress(ShaderProgram::ambientFactor);
            lightDirectionId = _shaderPrograms[shaderName]->getUniformAddress(ShaderProgram::lightDirection);
            textureOffsetId = _shaderPrograms[shaderName]->getUniformAddress(ShaderProgram::textureOffset);
            worldScaleId = _shaderPrograms[shaderName]->getUniformAddress(ShaderProgram::worldScale);
            projectionMatrixId = _shaderPrograms[shaderName]->getUniformAddress(ShaderProgram::projectionMatrix);
        }

        glUniform4f(colorId, color.r, color.g, color.b, color.a);

        // Calculate needed matrices

        glm::mat4 viewMatrix = _camera.getViewMatrix();
        glUniformMatrix4fv(viewMatrixId, 1, GL_FALSE, glm::value_ptr(viewMatrix));

        glUniformMatrix4fv(modelMatrixId, 1, GL_FALSE, glm::value_ptr(modelMatrix));

        glm::mat4 mvp = _projectionMatrix * viewMatrix * modelMatrix;
        glUniformMatrix4fv(mvpId, 1, GL_FALSE, glm::value_ptr(mvp));

        glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(viewMatrix * modelMatrix)));
        glUniformMatrix3fv(normalMatrixId, 1, GL_FALSE, glm::value_ptr(normalMatrix));

        // Send in ambientFactor for light
        glUniform1f(ambientFactorId, _ambientFactor);

        // Send in lightDirection
        glUniform3f(lightDirectionId, _lightDirection.x, _lightDirection.y, _lightDirection.z);

        glUniform2f(textureOffsetId, textureOffset.x, textureOffset.y);

        // Scaling
        glUniformMatrix4fv(worldScaleId, 1, GL_FALSE, glm::value_ptr(_worldScale));
        glUniformMatrix4fv(projectionMatrixId, 1, GL_FALSE, glm::value_ptr(_projectionMatrix));


        static std::string lastTexture;
        if (lastTexture != textureName)
        {
            _textures[textureName]->bind();
            lastTexture = textureName;
        }

        _meshes[meshName]->draw();
    }
    else
    {
        std::cout << shaderName << " Does not exist" << std::endl;
    }
}

void Renderer::present() noexcept
{
    SDL_GL_SwapWindow(_window);
}

void Renderer::handleInput() noexcept
{

}

bool Renderer::initialize() noexcept
{
    if (!initializeSDL())
    {
        return false;
    }
    if (!createWindow())
    {
        return false;
    }
    if (!createContext())
    {
        return false;
    }
    if (!initializeGlew())
    {
        return false;
    }
    initializeOpenGL();
    initializeVariables();
    return true;
}


bool Renderer::windowIsOpen() const noexcept
{
    return _windowIsOpen;
}

void Renderer::advanceLight(float deltaTime) noexcept
{
    _lightDirection.x += deltaTime;
}

void Renderer::regressLight(float deltaTime) noexcept
{
    _lightDirection.x -= deltaTime;
}

void Renderer::increaseWorldScale() noexcept
{
    _worldScale[1][1] *= 1.1f;
}

void Renderer::decreaseWorldScale() noexcept
{
    _worldScale[1][1] *= 0.9f;
}

void Renderer::resetWorldScale() noexcept
{
    _worldScale[1][1] = 1.0f;
}

void Renderer::keepWindowOpen(bool isOpen) noexcept
{
    _windowIsOpen = isOpen;
}

// Private functions
bool Renderer::initializeSDL() noexcept
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

bool Renderer::createWindow() noexcept
{
    _window = SDL_CreateWindow(windowName.c_str(),
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               width,
                               height,
                               SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if (_window == nullptr)
    {
        printf("Could not create window, Error: %s\n", SDL_GetError());
        return false;
    }
    _windowIsOpen = true;
    return true;
}

bool Renderer::createContext() noexcept
{
    _context = SDL_GL_CreateContext(_window);
    if (_context == nullptr)
    {
        printf("Could not create context, Error: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

bool Renderer::initializeGlew() noexcept
{
    glewExperimental = GL_TRUE;
    auto glewError = glewInit();
    if (glewError != GLEW_OK)
    {
        printf("Could not initialize GLEW, Error: %s\n", glewGetErrorString(glewError));
        return false;
    }
    return true;
}

bool Renderer::setVsyncOn() noexcept
{
    if (SDL_GL_SetSwapInterval(1) < 0)
    {
        printf("Could not set VSync, Error: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

void Renderer::initializeOpenGL() noexcept
{

    glClearColor(0.25f, 0.25f, 0.25f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void Renderer::initializeVariables() noexcept
{
    std::string shaderName = "Resources/Shaders/directionalFullTextureV3WScale";
    _shaderPrograms["DirectionalFullTexture"] = new ShaderProgram(shaderName + ".vert", shaderName + ".frag");

    auto meshData = Local::createCube();
    _meshes["Cube"] = new Mesh(std::get<0>(meshData),
                               std::get<1>(meshData),
                               std::get<2>(meshData),
                               std::get<3>(meshData));

    _textures["Bricks"] = new Texture("Resources/Textures/texture.png");
}
