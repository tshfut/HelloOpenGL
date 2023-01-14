//
// Created by TSHFUT on 2023-01-14.
//


#include <ShaderHelper.h>
#include <Application.h>

class HelloShaderHelper: public Application {
public:
    ShaderHelper shader;
    GLuint VAO;
    GLuint VBO;
public:
    void InitAppInfo() override {
        appInfo.title = "HelloShaderHelper";
        appInfo.windowWidth = 800;
        appInfo.windowHeight = 600;
        appInfo.majorVersion = 4;
        appInfo.minorVersion = 3;
    }

    void Startup() override {
        shader = ShaderHelper("..\\source\\ShaderClass\\VertexShader.glsl",
                              "..\\source\\ShaderClass\\FragmentShader.glsl");
        float vertices[] = {
                // positions                       // colors
                0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
                -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
                0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top
        };
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }

    void Render(double currentTime) override {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // render the triangle
        shader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    void Shutdown() override {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }

};

DECLARE_MAIN(HelloShaderHelper)