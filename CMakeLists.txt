cmake_minimum_required (VERSION 3.10)

project ("my_terraria")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

message("Source Dir: ${CMAKE_CURRENT_SOURCE_DIR}")
message("Binary Dir: ${CMAKE_CURRENT_BINARY_DIR}")

# Define paths to dependencies
set(GLEW_ROOT ${CMAKE_SOURCE_DIR}/dependencies/glew)
set(GLFW_ROOT ${CMAKE_SOURCE_DIR}/dependencies/glfw)
set(STB_IMAGE_ROOT ${CMAKE_SOURCE_DIR}/dependencies/stb_image)
set(GLM_ROOT ${CMAKE_SOURCE_DIR}/dependencies/glm)
set(ENET_ROOT ${CMAKE_SOURCE_DIR}/dependencies/enet-1.3.17)

# Add an executable target
add_executable(my_terraria "src/main.cpp")  # Make sure this file exists!

# Properly add include directories
target_include_directories(my_terraria PRIVATE
    ${GLEW_ROOT}/include
    ${GLFW_ROOT}/include
    ${ENET_ROOT}/include
    ${STB_IMAGE_ROOT}
    ${GLM_ROOT}
)

# Define GLEW_STATIC for static linking
target_compile_definitions(my_terraria PRIVATE GLEW_STATIC)

# Link libraries
target_link_libraries(my_terraria PRIVATE 
    ${GLEW_ROOT}/lib/glew32s.lib
    ${GLFW_ROOT}/lib/glfw3.lib
    opengl32
)
