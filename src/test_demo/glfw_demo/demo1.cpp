/*
    使用uniform
    显示颜色随时间变化的矩形
*/

#include "glad/glad.h"
#include "glfw3.h"

#include <iostream>
#include <cmath>
// 定义三角形顶点数组
float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

// 定义一个矩形
// float vertices[] = {
//     0.5f, 0.5f, 0.0f,   // 右上角
//     0.5f, -0.5f, 0.0f,  // 右下角
//     -0.5f, -0.5f, 0.0f, // 左下角
//     -0.5f, 0.5f, 0.0f   // 左上角
// };

// 定义顶点索引
unsigned int indices[] = {
    // 注意索引从0开始! 
    // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
    // 这样可以由下标代表顶点组合成矩形

    0, 1, 3, // 第一个三角形
    1, 2, 3  // 第二个三角形
};

// 定义着色器
const char *vertexShaderSource = 
"\
#version 330 core\n\
layout (location = 0) in vec3 aPos;\n\
void main()\n\
{\n\
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n\
}\0\
";

const char *fragmentShaderSource = 
"\
#version 330 core\n\
uniform vec4 cpuColor;\n\
out vec4 FragColor;\n\
void main()\n\
{\n\
   FragColor = cpuColor;\n\
}\0\
";

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
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    // 定义 顶点数组对象
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    
    // 定义 元素缓冲对象
    unsigned int EBO;
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    /*
        自定义着色器
        判断是否成功创建 编译
    */
    int success;
    char infolog[512];

    // 定义 顶点着色器
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER); // 创建一个顶点着色器
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // 为着色器添加源码
    glCompileShader(vertexShader); // 编译顶点着色器

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infolog << std::endl;
    }
    //定义 片段着色器
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // 创建一个片段着色器
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); // 为着色器添加源码
    glCompileShader(fragmentShader); // 编译片段着色器

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentShader, 512, NULL, infolog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infolog << std::endl;
    }

    /*
        构建一个完整的着色器程序对象
        即 将顶点着色器和片段着色器链接合并到着色器程序对象中
        判断是否链接成功
    */

    // 创建一个(着色器)程序对象
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    //链接着色器
    glAttachShader(shaderProgram, vertexShader); // 附加顶点着色器
    glAttachShader(shaderProgram, fragmentShader); // 附加片段着色器
    glLinkProgram(shaderProgram); // 链接所有着色器

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infolog);
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infolog << std::endl;
    }

    // 激活程序对象
    glUseProgram(shaderProgram);

    // 链接后 定义的着色器对象将不再使用 可以删除先前定义的两个着色器对象
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    /*
        说明顶点属性的形式
        存储在 VAO 中
        VAO 存放 顶点顶点属性配置 和 对应的VBO
    */
    // 定义 解析顶点属性方式
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //图元绘制设置为线框模式
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //图元绘制设置为默认(填充)模式

    while(!glfwWindowShouldClose(window))
    {
        // 输入 处理函数
        processInput(window);
        //渲染指令

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // 设置屏幕颜色
        glClear(GL_COLOR_BUFFER_BIT); //清除屏幕

        //设置三角形颜色
        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "cpuColor");
        glUseProgram(shaderProgram);
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        // 绘制三角形
        glUseProgram(shaderProgram);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3); // 绘制三角形

        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // 绘制矩形

        glBindVertexArray(VAO);

        // 检查并调用事件 交换缓冲
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}