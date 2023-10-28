#include "glad.h"
#include "SDL.h"
#include "stb_image.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include "Shader.h"
#include "Camera_SDL.h"

#include "Cube.h"

#include <iostream>
#include <cmath>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间

Camera_SDL camera;

void CreatTexture() {
    // 载入图像
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("img/container.jpg", &width, &height, &nrChannels, 0);
    if (data == NULL) {
        std::cout << "fail to load image" << std::endl;
    }
    // 创建纹理
    unsigned int texture;
    glGenTextures(1, &texture);
    // 激活纹理单元
    glActiveTexture(GL_TEXTURE0);
    // 绑定纹理
    glBindTexture(GL_TEXTURE_2D, texture);
    // 根据图像数据生成纹理
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    // 生成多级渐远纹理
    glGenerateMipmap(GL_TEXTURE_2D);
    // 生成纹理后释放图片数据
    stbi_image_free(data);

    data = stbi_load("img/awesomeface.png", &width, &height, &nrChannels, 0);
    if (data == NULL) {
        std::cout << "fail to load image" << std::endl;
    }
    // 创建纹理
    unsigned int texture2;
    glGenTextures(1, &texture2);
    // 激活纹理单元
    glActiveTexture(GL_TEXTURE1);
    // 绑定纹理
    glBindTexture(GL_TEXTURE_2D, texture2);
    // 根据图像数据生成纹理
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    // 生成多级渐远纹理
    glGenerateMipmap(GL_TEXTURE_2D);
    // 生成纹理后释放图片数据
    stbi_image_free(data);
}

int main(int argc, char* args[]) {
    //启动SDL
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        return 1;
    }
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    // SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    // SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    // SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    // SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    //设置窗口
    SDL_Window* win = SDL_CreateWindow("hello",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WIN_WIDTH, WIN_HEIGHT,
        SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN);

    if (win == NULL) {
        std::cout << "Failed to create SDL2 window" << std::endl;
        SDL_Quit();
        return 2;
    }

    //SDL_SetWindowGrab(win, SDL_TRUE);
    SDL_SetRelativeMouseMode(SDL_TRUE);
    
    SDL_GLContext gl_context = SDL_GL_CreateContext(win);
    // SDL_GL_MakeCurrent(win, gl_context);
    // SDL_GL_SetSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);

    Cube cube(36, 6, "Object/light_cube.v");
    unsigned int temp[2] = { 3,3 };
    // 物体
    cube.CreateCube(2, temp, false);
    // 光源
    cube.CreateCube(1, temp, false);

    /*
        自定义着色器
        判断是否成功创建 编译
    */
    Shader object_shader("Shaders/object_shader.vs", "Shaders/object_shader.fs");
    Shader light_shader("Shaders/light_shader.vs", "Shaders/light_shader.fs");

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //图元绘制设置为线框模式
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //图元绘制设置为默认(填充)模式

    // 开启Z缓冲
    glEnable(GL_DEPTH_TEST);

    // 变换矩阵
    glm::mat4 projection(1.0f);
    glm::mat4 view(1.0f);
    glm::mat4 model(1.0f);
    // 旋转矩阵
    glm::mat4 rotate_mat(1.0f);

    model = glm::translate(model, glm::vec3(0.0f, -0.7f, -1.0f));

    glm::vec3 lightpos = glm::vec3(1.0f, 1.5f, -1.5f);
    glm::mat4 light(1.0f);
    light = glm::translate(light, lightpos);
    light = glm::scale(light, glm::vec3(0.2f));
    
    SDL_Event event;
    bool quit_flag = false;
    while (!quit_flag) {

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit_flag = true;
            camera.ProcessEvent(event);
        }
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // 设置屏幕颜色
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 清除屏幕

        view = camera.GetViewMatrix();
        projection = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 100.0f);
        rotate_mat = glm::rotate(model, (float)(SDL_GetTicks()), glm::vec3(1.0f, 0.3f, 0.5f));

        // 绘制物体
        object_shader.use();
        // 设置采样器 为其赋值着色器位置
        // object_shader.setInt("Texture0", 0);
        // object_shader.setInt("Texture1", 1);
        object_shader.setMat4("view", view);
        object_shader.setMat4("projection", projection);
        object_shader.setMat4("model", model);
        object_shader.setVec3("lightPos", lightpos);
        object_shader.setVec3("viewPos", camera.Position);
        object_shader.setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
        object_shader.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        cube.DrawCube(0);

        // 绘制光源
        light_shader.use();

        light_shader.setMat4("view", view);
        light_shader.setMat4("projection", projection);
        light_shader.setMat4("model", light);

        cube.DrawCube(1);

        SDL_GL_SwapWindow(win);
        camera.FlushFrameTime();
    }

    object_shader.deleteShader();
    light_shader.deleteShader();

    SDL_DestroyWindow(win);
    //退出SDL 
    SDL_Quit();

    return 0;
}