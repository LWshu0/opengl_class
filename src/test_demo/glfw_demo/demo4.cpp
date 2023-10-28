/*
    使用自定义的着色器类
    应用纹理
    使用uniform变换矩阵
    显示一个旋转的笑脸箱子
*/

#include "glad/glad.h"
#include "glfw3.h"

#include "stb_image.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include <iostream>
#include <cmath>


#include "Shader.h"

float vertices[] = {
//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
};

// 定义顶点索引
unsigned int indices[] = {
    // 注意索引从0开始! 
    // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
    // 这样可以由下标代表顶点组合成矩形

    0, 1, 3, // 第一个三角形
    1, 2, 3  // 第二个三角形
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
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    // 定义 顶点数组对象
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    //定义 元素缓冲对象
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
    Shader my_shader("Shaders/4shader.vs", "Shaders/3shader.fs");

    /*
        说明顶点属性的形式
        存储在 VAO 中
        VAO 存放 顶点顶点属性配置 和 对应的VBO, EBO
    */
    // 定义 解析顶点属性方式
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // 载入图像
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load("img/container.jpg", &width, &height, &nrChannels, 0);
    // 创建纹理
    unsigned int texture;
    glGenTextures(1, &texture);
    // 绑定纹理
    glBindTexture(GL_TEXTURE_2D, texture);
    // 根据图像数据生成纹理
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    // 生成多级渐远纹理
    glGenerateMipmap(GL_TEXTURE_2D);
    // 生成纹理后释放图片数据
    stbi_image_free(data);

    data = stbi_load("img/awesomeface.png", &width, &height, &nrChannels, 0);
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

    glm::mat4 trans(1.0f); // 变换矩阵

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //图元绘制设置为线框模式
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //图元绘制设置为默认(填充)模式

    while(!glfwWindowShouldClose(window))
    {
        // 输入 处理函数
        processInput(window);
        //渲染指令

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // 设置屏幕颜色
        glClear(GL_COLOR_BUFFER_BIT); //清除屏幕

        //设置着色器程序
        my_shader.use();
        // 设置采样器
        my_shader.setInt("Texture0", 0);
        my_shader.setInt("Texture1", 1);
        
        trans = glm::rotate(trans, (float)0.01, glm::vec3(0.0, 0.0, 1.0));

        glm::mat4 temp_trans(1.0f);

        // temp_trans = glm::translate(trans, glm::vec3(0.5, -0.5, 0));

        temp_trans = glm::translate(temp_trans, glm::vec3(0.5, -0.5, 0));
        temp_trans = temp_trans * trans;

        //trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

        unsigned int transformLoc = glGetUniformLocation(my_shader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(temp_trans));

        // 绑定 VAO
        glBindVertexArray(VAO);
        // 绘制矩形
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // 检查并调用事件 交换缓冲
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    my_shader.deleteShader();

    glfwTerminate();
    return 0;
}