# 关于本项目的一些使用方法

## 构建

在vscode中打开project文件夹, 打开一个终端, cd到build文件夹, `./make_build.bat`运行批处理文件, 如果没有错误将会输出一系列可执行文件在run/bin目录下.

进入run/bin即可运行对应的可执行文件

关于调式, 使用vscode的拓展CMakeTool工具, 具体方法: [调试教程](https://www.bilibili.com/video/BV1o34y1675i/)

关于CMake, [视频教程](https://www.bilibili.com/video/BV1nU4y1B7mJ/)

## project/CMakeList.txt

>这是控制本项目的最重要的CMakLists.txt

### 编译器

```
# 指定编译器
set (CMAKE_C_COMPILER "D:/mingw64/bin/gcc.exe")
set (CMAKE_CXX_COMPILER "D:/mingw64/bin/g++.exe")
```
需要确定到编译器可执行文件的绝对路径

### 项目路径

```
# 定义路径
set(PROJECT_DIR E:/computer_graphics/project)
set(INCLUDE_DIR ${PROJECT_DIR}/include)
set(RUN_DIR ${PROJECT_DIR}/run)
```

`PROJECT_DIR`是本项目的绝对路径, 在所有子目录下的CMakeLists.txt都使用这个变量定义的路径来寻找头文件, 库文件等

### 头文件

```
# 指明所有头文件路径
include_directories(${INCLUDE_DIR}
                    ${INCLUDE_DIR}/glad
                    ${INCLUDE_DIR}/GLFW
                    ${INCLUDE_DIR}/KHR
                    ${INCLUDE_DIR}/Shader
                    ${INCLUDE_DIR}/STB_IMAGE
                    ${INCLUDE_DIR}/glm
                    ${INCLUDE_DIR}/Camera)
```

本项目的头文件都放在`/include`目录下, 这个路径存放在变量`INCLUDE_DIR`中, 后续如果需要新建文件夹添加头文件, 把路径添加在这后面

## src/CMakeLists.txt

```
link_libraries(glfw3)

# 生成 glad 库, 这是后续可执行文件的依赖
add_library(glad STATIC glad.c)

add_library(stb_image STATIC stb_image.cpp)
```

这三行是编译OpenGL教程中提到的库

```
add_subdirectory(Shader)

add_subdirectory(Camera)

add_subdirectory(test_demo)
```

这三行将进入对应的文件夹下构建其中的CMakeLists.txt

## Camera/Shader

这是教程中提到的类, 有源码, 应该不需要太大的变动, 其中的CMakeLists.txt是为了生成对应的静态库文件

## test_demo

```
add_executable(demo1 demo1.cpp)
add_executable(可执行文件名称 源文件)
```

这一个命令是生成可执行文件(.exe)

```
link_libraries(glad)
```
这个命令是链接库文件, 此命令后的所有使用`add_executable`添加的可执行文件都将链接这个库. 因为所有的源文件都需要`glad`这个库, 所以在所有`add_executable`之前声明.

## 更多文件

如果要添加更多文件, 需要简单的CMakeLists.txt使用. 真正用到的命令其实就只有几个:
```
//链接库文件
link_libraries

//生成可执行文件
add_executable

//生成库文件
add_library

//进入子目录
add_subdirectory

//设置变量
set

```