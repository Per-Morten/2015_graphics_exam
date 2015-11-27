#pragma once
#include <string>
#include <unordered_map>

#include <gl\glew.h>
#include <gl\glu.h>
#include <glm\glm.hpp>
#include "GSL\gsl.h"
#include <SDL.h>
#include <SDL_opengl.h>

#include "Camera.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Texture.h"

class Renderer
{
public:
    enum class FacingDirection
    {
        FRONT,
        BACK,
    };

    static constexpr auto groundTexture = "Ground";
    static constexpr auto skyboxDayTexture = "SkyBoxDay";
    static constexpr auto skyboxNightTexture = "SkyBoxNight";
    static constexpr auto cubeMesh = "Cube";
    static constexpr auto regularShader = "DirectionalFullTexture";
    static constexpr auto skyboxShader = "SkyBox";

    Renderer(GLint width, GLint height, Camera& _camera) noexcept;
    ~Renderer() noexcept;

    void clear() noexcept;
    void render(const std::string& shaderName,
                const std::string& meshName,
                const std::string& textureName,
                const glm::mat4& modelMatrix,
                const glm::vec4& color,
                GLuint textureIndex,
                FacingDirection facing = FacingDirection::BACK) noexcept;
    void present() noexcept;

    void handleInput() noexcept;

    bool initialize() noexcept;
    bool windowIsOpen() const noexcept;

    void advanceLight(float deltaTime) noexcept;
    void regressLight(float deltaTime) noexcept;

    void increaseWorldScale() noexcept;
    void decreaseWorldScale() noexcept;
    void resetWorldScale() noexcept;

    void keepWindowOpen(bool isOpen) noexcept;



    const std::string windowName{ "Graphics Exam 2015 - Per-Morten Straume" };
    const GLint width{};
    const GLint height{};
private:
    // Rendering Functions
    // object related
    void setColorUniform(const std::string& shaderName, bool newShader, const glm::vec4& color) noexcept;
    void setModelMatrixUniform(const std::string& shaderName, bool newShader, const glm::mat4& modelMatrix) noexcept;
    void setTextureOffsetUniform(const std::string& shaderName, bool newShader, GLuint textureIndex, GLuint numberOfRows) noexcept;
    void setNormalMatrixUniform(const std::string& shaderName, bool newShader, const glm::mat4& modelMatrix) noexcept;
    void setNumberOfRows(const std::string& shaderName, bool newShader, GLuint numberOfRows) noexcept;

    // Static for each total draw round
    void setViewMatrixUniform(const std::string& shaderName, bool newShader) noexcept;
    void setProjectionMatrixUniform(const std::string& shaderName, bool newShader) noexcept;
    void setAmbientFactorUniform(const std::string& shaderName, bool newShader) noexcept;
    void setLightDirectionUniform(const std::string& shaderName, bool newShader) noexcept;
    void setWorldScaleUniform(const std::string& shaderName, bool newShader) noexcept;

    // initializing Functions
    bool initializeSDL() noexcept;
    bool createWindow() noexcept;
    bool createContext() noexcept;
    bool initializeGlew() noexcept;
    bool setVsyncOn() noexcept;
    void initializeOpenGL() noexcept;
    void initializeVariables() noexcept;


    Camera& _camera;
    gsl::owner<SDL_Window*> _window{};
    gsl::owner<SDL_GLContext> _context{};
    float _ambientFactor{ 0.1f };
    // length*cos(angle) = xDirection,
    // length*sin(angle) = yDirection,
    glm::vec3 _lightDirection{ -1.8792f, 0.684, -0.2 };

    glm::mat4 _worldScale{ 1.0f, 0.0f, 0.0f, 0.0f,
                           0.0f, 1.0f, 0.0f, 0.0f,
                           0.0f, 0.0f, 1.0f, 0.0f,
                           0.0f, 0.0f, 0.0f, 1.0f };
    glm::mat4 _projectionMatrix{};
    std::unordered_map<std::string, gsl::owner<ShaderProgram*>> _shaderPrograms{};
    std::unordered_map<std::string, gsl::owner<Mesh*>> _meshes{};
    std::unordered_map<std::string, gsl::owner<Texture*>> _textures{};

    bool _windowIsOpen{};
};

