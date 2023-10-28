# 为所有的库链接 glad
link_libraries(glad stb_image)

link_libraries(shader icamera)

link_libraries(Vertex_Manager Cube)

if(GLFW_LIB_ENABLE)
    link_libraries(glfw3 camera_glfw)

    # 以下添加可执行文件

    add_executable(demo1 glfw_demo/demo1.cpp)

    add_executable(demo2 glfw_demo/demo2.cpp)

    add_executable(demo_test glfw_demo/demo_test.cpp)

    add_executable(demo3 glfw_demo/demo3.cpp)

    add_executable(demo4 glfw_demo/demo4.cpp)

    add_executable(demo5 glfw_demo/demo5.cpp)

    add_executable(demo6 glfw_demo/demo6.cpp)

    add_executable(demo7 glfw_demo/demo7.cpp)
    
    add_executable(x glfw_demo/x.cpp)

else()
    link_libraries(mingw32 SDL2main SDL2 camera_sdl World Character)

    add_executable(sdl_opengl sdl_demo/sdl_opengl.cpp)
    add_executable(demo8 sdl_demo/demo8.cpp)
    add_executable(demo9 sdl_demo/demo9.cpp)
    link_libraries(model)
    add_executable(demo10 sdl_demo/demo10.cpp)
    add_executable(world sdl_demo/world.cpp)
endif()