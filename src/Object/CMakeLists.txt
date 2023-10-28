# 为所有的库链接 glad
link_libraries(glad)


add_library(Cube OBJECT Cube.cpp)

add_library(Vertex_Manager OBJECT Vertex_Manager.cpp)

add_library(World OBJECT World.cpp)

add_library(Character OBJECT Character.cpp)