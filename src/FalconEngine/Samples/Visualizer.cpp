#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// GLEW
#define GLEW_BUILD
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Falcon Engine
#include <FalconEngine/Content.h>
#include <FalconEngine/Context.h>
#include <FalconEngine/Core.h>
#include <FalconEngine/Geometry.h>
#include <FalconEngine/Graphics.h>
#include <FalconEngine/Math.h>

using namespace FalconEngine;

class Visualizer : public Game
{
private:
    // Windows
    const GLuint        m_windowWidth = 1600;
    const GLuint        m_windowHeight = 1200;
    GLFWwindow         *m_window = nullptr;

    // Camera
    HandednessRight     m_handedness;
    Viewport            m_viewport;
    Camera              m_camera;
    Shader              m_shader;

    // Data
    std::wstring        m_vertexFileName;
    std::wstring        m_indexFileName;

    TriangleGeometryPtr m_geometry     = std::make_shared<TriangleGeometry>();
    TriangleMeshPtr     m_geometryMesh = std::make_shared<TriangleMesh>();

    // Scene
    NodePtr             m_scene;

public:
    Visualizer(const std::wstring vertexFileName, const std::wstring indexFileName) :
        m_viewport(Viewport(0, 0, m_windowWidth, m_windowHeight, 0.0f, 1.0f)) ,
        m_camera(Camera(m_handedness, m_viewport)) ,
        m_vertexFileName(vertexFileName) ,
        m_indexFileName(indexFileName)
    {
    }

    virtual void Initialize() override
    {
        InitGLFW();
        InitGLEW();
        InitGL();

        InitShader();
        InitModel();
        InitScene();
    }

    void InitGLFW()
    {
        glfwInit();

        // Set all the required options for GLFW
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        m_window = glfwCreateWindow(m_windowWidth, m_windowHeight, "Points", nullptr,
                                    nullptr);
        glfwMakeContextCurrent(m_window);

        // Set the required callback functions
        glfwSetKeyCallback(m_window, KeycallbackDispatch);
        glfwSetMouseButtonCallback(m_window, MouseButtonCallbackDispatch);
        glfwSetCursorPosCallback(m_window, cursor_position_callback_dispatch);
        glfwSetScrollCallback(m_window, scroll_callback_dispatch);

        glfwSetWindowUserPointer(m_window, this);
    }

    void InitGLEW() const
    {
        glewExperimental = GL_TRUE;
        glewInit();

        glViewport(0, 0, m_windowWidth, m_windowHeight);
    }

    void InitGL() const
    {
        glEnable(GL_PROGRAM_POINT_SIZE);
        glEnable(GL_POINT_SPRITE);
        glPointSize(20.0);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glClearColor(0, 0, 0, 0);
    }

    void InitShader()
    {
        m_shader = Shader(std::wstring(L"Shader\\VertexShader.glsl"),
                          std::wstring(L"Shader\\FragmentShader.glsl"));
    }

    void InitModel()
    {
        m_geometryMesh->LoadMesh({ m_vertexFileName, m_indexFileName });
        m_geometry->SetMesh(m_geometryMesh);
    }

    void InitScene()
    {
        // Initialize objects
        m_scene = std::make_shared<Node>();
        m_scene->AttachChild(m_geometry);

        // Initialize camera
        Vector3f position = Vector3f(5, 5, 5);
        Vector3f up = Vector3f::UnitZ;

        // Rotate the camera for proper orientation
        m_camera.LookAt(position, Vector3f::Zero, );
    }

    virtual void Exit() override
    {
        // Terminate GLFW, clearing any resources allocated by GLFW.
        glfwTerminate();
    }

    virtual void Render(double percent) override
    {
        // Clear the color and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_shader.UseBegin();

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        m_geometry.Render(percent);

        glfwSwapBuffers(m_window);

        m_shader.UseEnd();
    }

    virtual void Update(double elapsed) override
    {
        m_camera.Update(elapsed);

        GLint projLoc  = glGetUniformLocation(m_shader.ProgramId(), "projection");
        GLint viewLoc  = glGetUniformLocation(m_shader.ProgramId(), "view");
        GLint worldLoc = glGetUniformLocation(m_shader.ProgramId(), "world");

        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, m_camera.View().Ptr());
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, m_camera.Projection().Ptr());
        glUniformMatrix4fv(worldLoc, 1, GL_FALSE, m_geometry->WorldTransform.Matrix().Ptr());
    }

    virtual void UpdateInput() override
    {
        glfwPollEvents();
    }

    /************************************************************************/
    /* Event Handling                                                       */
    /************************************************************************/
    static void KeycallbackDispatch(GLFWwindow *window, int key, int scancode,
                                    int action, int mods)
    {
        auto instance = reinterpret_cast<Visualizer *>(glfwGetWindowUserPointer(window));
        if (instance) {
            instance->KeyCallback(window, key, scancode, action, mods);
        }
    }

    void KeyCallback(GLFWwindow *window, int key, int scancode, int action,
                     int mods)
    {
        if (action != GLFW_PRESS)
        {
            return;
        }

        switch (key)
        {
        case GLFW_KEY_ESCAPE:
            Game->Shutdown();
            break;

        case GLFW_KEY_LEFT:
            m_camera.MoveLeft(5);
            break;

        case GLFW_KEY_RIGHT:
            m_camera.MoveRight(5);
            break;

        case GLFW_KEY_UP:
            m_camera.MoveUp(5);
            break;

        case GLFW_KEY_DOWN:
            m_camera.MoveDown(5);
            break;

        //case GLFW_KEY_PAGE_UP:
        //    g_zoom -= 0.25f;
        //    if (g_zoom < 0.f)
        //    { g_zoom = 0.f; }
        //    break;

        //case GLFW_KEY_PAGE_DOWN:
        //    g_zoom += 0.25f;
        //    break;

        default:
            break;
        }
    }

    static void MouseButtonCallbackDispatch(GLFWwindow *window, int button,
                                            int action, int mods)
    {
        auto instance = reinterpret_cast<Visualizer *>(glfwGetWindowUserPointer(window));
        if (instance)
        {
            instance->MouseButtonCallback(window, button, action, mods);
        }
    }

    void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
    {
        if (button != GLFW_MOUSE_BUTTON_LEFT)
        {
            return;
        }

        //if (action == GLFW_PRESS)
        //{
        //    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        //    glfwGetCursorPos(window, &g_cursor_x, &g_cursor_y);
        //}
        //else
        //{
        //    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        //}
    }

    static void scroll_callback_dispatch(GLFWwindow *window, double x, double y)
    {
        auto instance = reinterpret_cast<Visualizer *>(glfwGetWindowUserPointer(window));
        if (instance) {
            instance->scroll_callback(window, x, y);
        }
    }

    void scroll_callback(GLFWwindow *window, double x, double y)
    {
        //g_zoom += static_cast<float>(y) / 4.f;
        //if (g_zoom < 0)
        //{
        //    g_zoom = 0;
        //}
    }

    static void cursor_position_callback_dispatch(GLFWwindow *window, double x,
            double y)
    {
        auto instance = reinterpret_cast<Visualizer *>(glfwGetWindowUserPointer(window));
        if (instance) {
            instance->cursor_position_callback(window, x, y);
        }
    }

    void cursor_position_callback(GLFWwindow *window, double x, double y)
    {
        //if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
        //{
        //    g_alpha += static_cast<GLfloat>(x - g_cursor_x) / 10.f;
        //    g_beta += static_cast<GLfloat>(y - g_cursor_y) / 10.f;

        //    g_cursor_x = x;
        //    g_cursor_y = y;
        //}
    }
};
