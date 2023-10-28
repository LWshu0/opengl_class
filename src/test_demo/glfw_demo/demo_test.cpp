/*
    使用自定义的着色器类
    显示一个渐变的三角形
*/

#include "glad/glad.h"
#include "glfw3.h"

#include <iostream>
#include <cmath>

#include "Shader.h"

float vertices[] = {
    // 位置                 
    -0.3f,  0.5f,   0.0f,   // 左上
    0.3f,   0.5f,   0.0f,   // 右上
    -0.5f,  0.0f,   0.0f,   // 左中
    0.5f,   0.0f,   0.0f,   // 右中
    -0.3f,  -0.5f,  0.0f,   // 左下
    0.3f,   -0.5f,  0.0f,   // 右下
};

unsigned int index[] = {
    0,1,3,
    0,2,4,
    3,4,5,
    0,3,4
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    // 初始化
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // 定义一个窗口
    GLFWwindow* window = glfwCreateWindow(800, 600, "21307124", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    // 定义 顶点缓冲对象
    // unsigned int VBO;
    // glGenBuffers(1, &VBO);
    // unsigned int EBO;
    // glGenBuffers(1, &EBO);

    // // 定义 顶点数组对象
    // unsigned int VAO;
    // glGenVertexArrays(1, &VAO);

    // glBindVertexArray(VAO);

    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

    // /*
    //     自定义着色器
    //     判断是否成功创建 编译
    // */
    // Shader my_shader("Shaders/shader_test.vs", "Shaders/Shader.fs");

    // /*
    //     说明顶点属性的形式
    //     存储在 VAO 中
    //     VAO 存放 顶点顶点属性配置 和 对应的VBO
    // */
    // // 定义 解析顶点属性方式
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);

    // // 解绑 VBO VAO
    // // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // // glBindVertexArray(0);

    // // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //图元绘制设置为线框模式
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //图元绘制设置为默认(填充)模式

    while(!glfwWindowShouldClose(window))
    {
        // 输入 处理函数
        processInput(window);
        //渲染指令

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // 设置屏幕颜色
        glClear(GL_COLOR_BUFFER_BIT); //清除屏幕

        // //设置着色器程序
        // my_shader.use();
        // // 绑定 VAO
        // glBindVertexArray(VAO);
        // glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, (void*)0);

        // glDrawArrays(GL_TRIANGLES, 0, 3); // 绘制三角形

        // 检查并调用事件 交换缓冲
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    // glDeleteVertexArrays(1, &VAO);
    // glDeleteBuffers(1, &VBO);
    // my_shader.deleteShader();

    glfwTerminate();
    return 0;
}