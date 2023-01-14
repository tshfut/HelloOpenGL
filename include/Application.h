#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
// GLEW  
#define GLEW_STATIC

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct APPINFO {
public:
    std::string title = "Default";
    int windowWidth = 800;
    int windowHeight = 600;
    int majorVersion = 4;
    int minorVersion = 3;
    int samples = 0;
};

class Application {
private:
    std::string winName;
    int winWidth;
    int winHeight;
public:
    APPINFO appInfo;

public:
    Application() {
        appInfo.title = "Hello OpenGL";
        appInfo.windowWidth = 800;
        appInfo.windowHeight = 600;
        appInfo.majorVersion = 4;
        appInfo.minorVersion = 3;
    }

    Application(std::string name, int width, int height)
            : winName(name), winWidth(width), winHeight(height) {}

    virtual ~Application() {}

    virtual void Run() {
        bool running = true;
        if (!glfwInit()) {
            std::cout << "Failed to initialize GLFW" << std::endl;
            return;
        }

        InitAppInfo();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, appInfo.majorVersion);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, appInfo.minorVersion);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWwindow *window = glfwCreateWindow(
                appInfo.windowWidth, appInfo.windowHeight,
                appInfo.title.c_str(), nullptr, nullptr);
        if (window == nullptr) {
            std::cout << "Failed to create GLFW window." << std::endl;
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(window);
        glfwSetKeyCallback(window, OnKey);
        glfwSetWindowSizeCallback(window, OnResize);
        glfwSetMouseButtonCallback(window, OnMouseButton);
        glfwSetCursorPosCallback(window, OnMouseMove);
        glfwSetScrollCallback(window, OnMouseWheel);
        //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return;
        }

        // OpenGL begin ====================================
        Startup();
        do {
            Render(glfwGetTime());

            glfwSwapBuffers(window);
            glfwPollEvents();

            running &= (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE);
            running &= (glfwWindowShouldClose(window) != GL_TRUE);
        } while (running);
        Shutdown();
        // OpenGL end  ====================================

        // Terminate GLFW, clearing any resources allocated by GLFW.
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    virtual void InitAppInfo() = 0;
    virtual void Startup() = 0;
    virtual void Render(double currentTime) = 0;
    virtual void Shutdown() = 0;

    static void OnKey(GLFWwindow *window, int key, int scancode, int action, int mods) {}
    static void OnMouseButton(GLFWwindow *window, int button, int action, int mods) {}
    static void OnMouseMove(GLFWwindow *window, double x, double y) {}
    static void OnMouseWheel(GLFWwindow *window, double xoffset, double yoffset) {}
    static void OnResize(GLFWwindow *window, int w, int h) {
        glViewport(0, 0, w, h);
    }
};

#define DECLARE_MAIN(A)                         \
int main(int argc, const char** argv) {         \
    A* app = new A;                             \
    app->Run();                                 \
    delete app;                                 \
    return 0;                                   \
}                                               \

#endif // !APPLICATION_H