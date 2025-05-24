cmake_minimum_required(VERSION 3.10)
project("my_terraria")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Dependency paths
set(GLEW_ROOT ${CMAKE_SOURCE_DIR}/dependencies/glew)
set(GLFW_ROOT ${CMAKE_SOURCE_DIR}/dependencies/glfw)
set(STB_IMAGE_ROOT ${CMAKE_SOURCE_DIR}/dependencies/stb_image)
set(GLM_ROOT ${CMAKE_SOURCE_DIR}/dependencies/glm)
set(ENET_ROOT ${CMAKE_SOURCE_DIR}/dependencies/enet-1.3.17)
set(SFML_ROOT ${CMAKE_SOURCE_DIR}/dependencies/SFML)

add_compile_definitions(SFML_STATIC)

# Include and link directories
include_directories(
    ${GLEW_ROOT}/include
    ${GLFW_ROOT}/include
    ${STB_IMAGE_ROOT}
    ${GLM_ROOT}
    ${ENET_ROOT}/include
    ${SFML_ROOT}/include
)

link_directories(
    ${GLEW_ROOT}/lib
    ${GLFW_ROOT}/lib
    ${ENET_ROOT}/lib
    ${SFML_ROOT}/lib
)

# CLIENT
add_executable(client "src/client.cpp")
target_compile_definitions(client PRIVATE GLEW_STATIC)
target_link_libraries(client
    glew32s
    glfw3
    enet
    opengl32
    ws2_32
    winmm
    sfml-window-s-d
    sfml-system-s-d
    sfml-graphics-s-d
    freetype
    gdi32
    flac
    vorbisenc
    vorbisfile
    vorbis
    ogg
    ws2_32
)

# SERVER
add_executable(server "src/server.cpp")
target_link_libraries(server
    enet
    ws2_32
    winmm
)
