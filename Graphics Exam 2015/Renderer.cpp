//===========================================================
// File: Renderer.cpp	
// StudentName: Per-Morten Straume                          
//                                                          
// Exam 2015: IMT-2531 Graphics Programming Exam.                                
//===========================================================
#include "Renderer.h"

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <tuple>

#include "Consts.h"

namespace
{
    namespace Local
    {
        // Stolen from the graphicsProgramming labs
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
    , _projectionMatrix(glm::perspective(fieldOfView,
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
                      GLuint textureIndex,
                      Renderer::FacingDirection facing) noexcept
{
    if (_shaderPrograms[shaderName] != nullptr)
    {
        static std::string lastShader;
        bool newShader = false;
        bool newTexture = false;
        if (lastShader != shaderName)
        {
            newShader = true;
            _shaderPrograms[shaderName]->bind();
            lastShader = shaderName;
        }

        static GLuint numberOfRows;
        static std::string lastTexture;
        if (lastTexture != textureName)
        {
            numberOfRows = _textures[textureName]->getNumberOfRows();
            _textures[textureName]->bind();
            lastTexture = textureName;

            newTexture = true;
        }


        static FacingDirection prevFacingDirection = FacingDirection::BACK;
        // Feels very like a hack!
        if (prevFacingDirection != facing)
        {
            if (facing == FacingDirection::FRONT)
            {
                glCullFace(GL_FRONT);
            }
            if (facing == FacingDirection::BACK)
            {
                glCullFace(GL_BACK);
            }
            prevFacingDirection = facing;
        }



        // Object related Uniforms
        setColorUniform(shaderName, newShader, color);
        setModelMatrixUniform(shaderName, newShader, modelMatrix);
        setNormalMatrixUniform(shaderName, newShader, modelMatrix);
        setTextureOffsetUniform(shaderName, newShader, newTexture, textureIndex, numberOfRows);
        setNumberOfRows(shaderName, newShader, newTexture, numberOfRows);

        // Total Drawing loop Uniforms
        setViewMatrixUniform(shaderName, newShader);
        setProjectionMatrixUniform(shaderName, newShader);
        setAmbientFactorUniform(shaderName, newShader);
        setLightDirectionUniform(shaderName, newShader);
        setWorldScaleUniform(shaderName, newShader);

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
    _sunAngle += deltaTime * lightRotationSpeed;
    _lightDirection = glm::vec3(cos(degToRad(_sunAngle)), sin(degToRad(_sunAngle)), 0.0);
    if (_sunAngle > 180.0f)
    {
        _sunAngle = 0.0f;
    }
}

void Renderer::regressLight(float deltaTime) noexcept
{
    _sunAngle -= deltaTime * lightRotationSpeed;
    _lightDirection = glm::vec3(cos(degToRad(_sunAngle)), sin(degToRad(_sunAngle)), 0.0);
    if (_sunAngle < 0.0f)
    {
        _sunAngle = 180.0f;
    }
}

void Renderer::increaseWorldScale() noexcept
{
    _worldScale[1][1] *= worldUpScaleRate;
}

void Renderer::decreaseWorldScale() noexcept
{
    _worldScale[1][1] *= worldDownScaleRate;
}

void Renderer::resetWorldScale() noexcept
{
    _worldScale[1][1] = 1.0f;
}

void Renderer::toggleWarpMode() noexcept
{
    _warpMode = !_warpMode;
    if (_warpMode)
    {
        _projectionMatrix = glm::perspective(warpFov,
                                             static_cast<float>(width) / static_cast<float>(height),
                                             _camera.minViewDistance, _camera.maxViewDistance);
    }
    else
    {
        _projectionMatrix = glm::perspective(fieldOfView,
                                             static_cast<float>(width) / static_cast<float>(height),
                                             _camera.minViewDistance, _camera.maxViewDistance);
    }
}

void Renderer::keepWindowOpen(bool isOpen) noexcept
{
    _windowIsOpen = isOpen;
}

bool Renderer::isDayTime() const noexcept
{
    return _sunAngle > lowerNightAngle && _sunAngle < upperNightAngle;
}

// Private functions
// Rendering functions
// Object related
void Renderer::setColorUniform(const std::string& shaderName, bool newShader, const glm::vec4& color) noexcept
{
    static ShaderProgram::UniformAddress colorId;
    static glm::vec4 prevColor;
    if (newShader)
    {
        colorId = _shaderPrograms[shaderName]->getUniformAddress(ShaderProgram::color);
        prevColor = color;
        glUniform4f(colorId, color.r, color.g, color.b, color.a);
        return;
    }
    if (color != prevColor)
    {
        prevColor = color;
        glUniform4f(colorId, color.r, color.g, color.b, color.a);
        return;
    }
}

void Renderer::setModelMatrixUniform(const std::string& shaderName, bool newShader, const glm::mat4& modelMatrix) noexcept
{
    static ShaderProgram::UniformAddress modelMatrixId;
    static glm::mat4 prevModelMatrix;
    if (newShader)
    {
        modelMatrixId = _shaderPrograms[shaderName]->getUniformAddress(ShaderProgram::modelMatrix);
        prevModelMatrix = modelMatrix;
        glUniformMatrix4fv(modelMatrixId, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        return;
    }
    if (modelMatrix != prevModelMatrix)
    {
        prevModelMatrix = modelMatrix;
        glUniformMatrix4fv(modelMatrixId, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        return;
    }
}

void Renderer::setTextureOffsetUniform(const std::string& shaderName, bool newShader, bool newTexture, GLuint textureIndex, GLuint numberOfRows) noexcept
{
    static ShaderProgram::UniformAddress textureOffsetId;
    static GLuint prevTextureIndex;
    if (newShader || newTexture)
    {
        textureOffsetId = _shaderPrograms[shaderName]->getUniformAddress(ShaderProgram::textureOffset);
        prevTextureIndex = textureIndex;
        float column = static_cast<float>(textureIndex % numberOfRows);
        float row = static_cast<float>(textureIndex / numberOfRows);
        glm::vec2 offset = { column / numberOfRows, row / numberOfRows };

        glUniform2f(textureOffsetId, offset.x, offset.y);
        return;
    }
    if (textureIndex != prevTextureIndex)
    {
        prevTextureIndex = textureIndex;
        float column = static_cast<float>(textureIndex % numberOfRows);
        float row = static_cast<float>(textureIndex / numberOfRows);
        glm::vec2 offset = { column / numberOfRows, row / numberOfRows };

        glUniform2f(textureOffsetId, offset.x, offset.y);
        return;
    }
}

void Renderer::setNormalMatrixUniform(const std::string& shaderName, bool newShader, const glm::mat4& modelMatrix) noexcept
{
    static ShaderProgram::UniformAddress normalMatrixId;
    static glm::mat4 prevModelMatrix;
    if (newShader)
    {
        normalMatrixId = _shaderPrograms[shaderName]->getUniformAddress(ShaderProgram::normalMatrix);
        prevModelMatrix = modelMatrix;
        glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(_camera.getViewMatrix() * modelMatrix)));
        glUniformMatrix3fv(normalMatrixId, 1, GL_FALSE, glm::value_ptr(normalMatrix));
        return;
    }
    if (modelMatrix != prevModelMatrix)
    {
        prevModelMatrix = modelMatrix;
        glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(_camera.getViewMatrix() * modelMatrix)));
        glUniformMatrix3fv(normalMatrixId, 1, GL_FALSE, glm::value_ptr(normalMatrix));
        return;
    }
}

void Renderer::setNumberOfRows(const std::string& shaderName, bool newShader, bool newTexture, GLuint numberOfRows) noexcept
{
    static ShaderProgram::UniformAddress numberOfRowsId;
    static GLuint prevNumberOfRows;
    if (newShader || newTexture)
    {
        numberOfRowsId = _shaderPrograms[shaderName]->getUniformAddress(ShaderProgram::numberOfRows);
        prevNumberOfRows = numberOfRows;
        glUniform1ui(numberOfRowsId, numberOfRows);
        return;
    }
    if (numberOfRows != prevNumberOfRows)
    {
        prevNumberOfRows = numberOfRows;
        glUniform1ui(numberOfRowsId, numberOfRows);
        return;
    }
}

// Static for each total draw round
void Renderer::setViewMatrixUniform(const std::string& shaderName, bool newShader) noexcept
{

    static ShaderProgram::UniformAddress viewMatrixId;
    static glm::mat4 prevViewMatrix;
    const glm::mat4& viewMatrix = _camera.getViewMatrix();
    if (newShader)
    {
        viewMatrixId = _shaderPrograms[shaderName]->getUniformAddress(ShaderProgram::viewMatrix);
        prevViewMatrix = viewMatrix;
        glUniformMatrix4fv(viewMatrixId, 1, GL_FALSE, glm::value_ptr(viewMatrix));
        return;
    }
    if (viewMatrix != prevViewMatrix)
    {
        prevViewMatrix = viewMatrix;
        glUniformMatrix4fv(viewMatrixId, 1, GL_FALSE, glm::value_ptr(viewMatrix));
        return;
    }
}

void Renderer::setProjectionMatrixUniform(const std::string& shaderName, bool newShader) noexcept
{
    static ShaderProgram::UniformAddress projectionMatrixId;
    static glm::mat4 prevProjectionMatrix;
    if (newShader)
    {
        projectionMatrixId = _shaderPrograms[shaderName]->getUniformAddress(ShaderProgram::projectionMatrix);
        prevProjectionMatrix = _projectionMatrix;
        glUniformMatrix4fv(projectionMatrixId, 1, GL_FALSE, glm::value_ptr(_projectionMatrix));
        return;
    }
    if (_projectionMatrix != prevProjectionMatrix)
    {

        prevProjectionMatrix = _projectionMatrix;
        glUniformMatrix4fv(projectionMatrixId, 1, GL_FALSE, glm::value_ptr(_projectionMatrix));
        return;
    }
}

void Renderer::setAmbientFactorUniform(const std::string & shaderName, bool newShader) noexcept
{
    static ShaderProgram::UniformAddress ambientFactorId;
    static float prevAmbientFactor;
    if (newShader)
    {
        ambientFactorId = _shaderPrograms[shaderName]->getUniformAddress(ShaderProgram::ambientFactor);
        prevAmbientFactor = _ambientFactor;
        glUniform1f(ambientFactorId, _ambientFactor);
        return;
    }
    if (_ambientFactor != prevAmbientFactor)
    {

        prevAmbientFactor = _ambientFactor;
        glUniform1f(ambientFactorId, _ambientFactor);
        return;
    }
}

void Renderer::setLightDirectionUniform(const std::string & shaderName, bool newShader) noexcept
{
    static ShaderProgram::UniformAddress lightDirectionId;
    static glm::vec3 prevLightDirection;
    if (newShader)
    {
        lightDirectionId = _shaderPrograms[shaderName]->getUniformAddress(ShaderProgram::lightDirection);
        prevLightDirection = _lightDirection;
        glUniform3f(lightDirectionId, _lightDirection.x, _lightDirection.y, _lightDirection.z);
        return;
    }
    if (_lightDirection != prevLightDirection)
    {
        prevLightDirection = _lightDirection;
        glUniform3f(lightDirectionId, _lightDirection.x, _lightDirection.y, _lightDirection.z);
        return;
    }
}

void Renderer::setWorldScaleUniform(const std::string& shaderName, bool newShader) noexcept
{
    static ShaderProgram::UniformAddress worldScaleId;
    static glm::mat4 prevWorldScale;
    if (newShader)
    {
        worldScaleId = _shaderPrograms[shaderName]->getUniformAddress(ShaderProgram::worldScale);
        prevWorldScale = _worldScale;
        glUniformMatrix4fv(worldScaleId, 1, GL_FALSE, glm::value_ptr(_worldScale));
        return;
    }
    if (_worldScale != prevWorldScale)
    {
        prevWorldScale = _worldScale;
        glUniformMatrix4fv(worldScaleId, 1, GL_FALSE, glm::value_ptr(_worldScale));
        return;
    }
}


// Initializing Functions
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
    _window = SDL_CreateWindow(windowName,
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

    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void Renderer::initializeVariables() noexcept
{
    std::string regular = "Resources/Shaders/directionalFullTexturev3Indexed";
    std::string skybox = "Resources/Shaders/NonScaling";
    std::string nonScalingWLightsShader = "Resources/Shaders/NonScalingWLight";
    _shaderPrograms[regularShader] = new ShaderProgram(regular + ".vert", regular + ".frag");
    _shaderPrograms[nonScalingShader] = new ShaderProgram(skybox + ".vert", skybox + ".frag");
    _shaderPrograms[nonScalingWLight] = new ShaderProgram(nonScalingWLightsShader + ".vert", nonScalingWLightsShader + ".frag");


    auto meshData = Local::createCube();

    constexpr std::size_t positions = 0;
    constexpr std::size_t normals = 1;
    constexpr std::size_t textureCoordinates = 2;
    constexpr std::size_t ibo = 3;
    _meshes[cubeMesh] = new Mesh(std::get<positions>(meshData),
                                 std::get<normals>(meshData),
                                 std::get<textureCoordinates>(meshData),
                                 std::get<ibo>(meshData));

    _textures[groundTexture] = new Texture("Resources/Textures/texture.png", Consts::NUMBEROFROWSINATLAS);
    _textures[skyboxNightTexture] = new Texture("Resources/Textures/Night.jpg", 1);
    _textures[skyboxDayTexture] = new Texture("Resources/Textures/Sky.jpg", 1);
}

