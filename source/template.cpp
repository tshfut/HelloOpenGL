//
// Created by TSHFUT on 2023-01-14.
//

#include <ShaderHelper.h>
#include <Application.h>

class Hello: public Application {
public:
    ShaderHelper shader;

public:
    void InitAppInfo() override {
        appInfo.title = "Hello";
        appInfo.windowWidth = 800;
        appInfo.windowHeight = 600;
        appInfo.majorVersion = 4;
        appInfo.minorVersion = 3;
    }

    void Startup() override {
        shader = ShaderHelper("", "");

    }

    void Render(double currentTime) override {

    }

    void Shutdown() override {

    }

};

DECLARE_MAIN(Hello)