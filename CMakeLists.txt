cmake_minimum_required(VERSION 3.1)

# Set up deployment configuration
option(FALCON_ENGINE_BUILD_DYNAMIC "Build dynamic library" ON)
option(FALCON_ENGINE_WINDOW_QT "Using Qt window system" OFF)
option(FALCON_ENGINE_WINDOW_GLFW "Using GLFW window system" ON)

# Set up solution root
set(FALCON_ENGINE_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "Falcon Engine root path.")

# Set up include
include(${FALCON_ENGINE_ROOT_DIR}/cmake/Compiler.cmake)
include(${FALCON_ENGINE_ROOT_DIR}/cmake/Dependency.cmake)
include(${FALCON_ENGINE_ROOT_DIR}/cmake/Platform.cmake)
include(${FALCON_ENGINE_ROOT_DIR}/cmake/Target.cmake)

# Set up IDE solution
project(FalconEngine CXX)

# Set up IDE project folder
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake Targets")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# 
# Set up Falcon Engine library targets
#

include_directories(${FALCON_ENGINE_INCLUDE_DIR})
link_directories(${FALCON_ENGINE_LIBRARY_DIR} ${FALCON_ENGINE_ARCHIVE_OUTPUT_DIR})

file(GLOB_RECURSE FALCON_ENGINE_CONTENT_SOURCE_FILES src/FalconEngine/Content/*.cpp)
file(GLOB_RECURSE FALCON_ENGINE_CONTENT_PIPELINE_SOURCE_FILES src/FalconEngine/Content/Pipeline/*.cpp)

# Remove pipeline source from content source.
if (NOT "${FALCON_ENGINE_CONTENT_PIPELINE_SOURCE_FILES}" STREQUAL "")
    list(REMOVE_ITEM FALCON_ENGINE_CONTENT_SOURCE_FILES ${FALCON_ENGINE_CONTENT_PIPELINE_SOURCE_FILES})
endif()

file(GLOB_RECURSE FALCON_ENGINE_CONTENT_HEADER_FILES include/FalconEngine/Content/*.h)
file(GLOB_RECURSE FALCON_ENGINE_CONTEXT_SOURCE_FILES src/FalconEngine/Context/*.cpp)
file(GLOB_RECURSE FALCON_ENGINE_CONTEXT_HEADER_FILES include/FalconEngine/Context/*.h)
file(GLOB_RECURSE FALCON_ENGINE_CORE_SOURCE_FILES src/FalconEngine/Core/*.cpp)
file(GLOB_RECURSE FALCON_ENGINE_CORE_HEADER_FILES include/FalconEngine/Core/*.h)
file(GLOB_RECURSE FALCON_ENGINE_GRAPHICS_SHADER_FILES src/FalconEngine/Graphics/*.glsl)
file(GLOB_RECURSE FALCON_ENGINE_GRAPHICS_SOURCE_FILES src/FalconEngine/Graphics/*.cpp)
file(GLOB_RECURSE FALCON_ENGINE_GRAPHICS_HEADER_FILES include/FalconEngine/Graphics/*.h)
file(GLOB_RECURSE FALCON_ENGINE_INPUT_SOURCE_FILES src/FalconEngine/Input/*.cpp)
file(GLOB_RECURSE FALCON_ENGINE_INPUT_HEADER_FILES include/FalconEngine/Input/*.h)
file(GLOB_RECURSE FALCON_ENGINE_MATH_SOURCE_FILES src/FalconEngine/Math/*.cpp)
file(GLOB_RECURSE FALCON_ENGINE_MATH_HEADER_FILES include/FalconEngine/Math/*.h)

add_library(FalconEngine                   # Name
    ${FALCON_ENGINE_LIBRARY_TYPE}          # Type
    ${FALCON_ENGINE_LIBRARY_TYPE}          # Type
    ${FALCON_ENGINE_CONTENT_HEADER_FILES}  # Source 
    ${FALCON_ENGINE_CONTENT_SOURCE_FILES}
    ${FALCON_ENGINE_CONTEXT_HEADER_FILES}
    ${FALCON_ENGINE_CONTEXT_SOURCE_FILES}
    ${FALCON_ENGINE_CORE_HEADER_FILES}
    ${FALCON_ENGINE_CORE_SOURCE_FILES}
    ${FALCON_ENGINE_GRAPHICS_HEADER_FILES}
    ${FALCON_ENGINE_GRAPHICS_SHADER_FILES}
    ${FALCON_ENGINE_GRAPHICS_SOURCE_FILES}
    ${FALCON_ENGINE_INPUT_HEADER_FILES}
    ${FALCON_ENGINE_INPUT_SOURCE_FILES}
    ${FALCON_ENGINE_MATH_HEADER_FILES}
    ${FALCON_ENGINE_MATH_SOURCE_FILES})

set(FALCON_ENGINE_EXTRA_LIBRARY_FILES
    ${ASSIMP_LIBRARY_FILE}
    ${GL_LIBRARY_FILE}
    ${GLEW_LIBRARY_FILE}
    ${GLFW_LIBRARY_FILE})

if(FALCON_ENGINE_PLATFORM_WINDOWS)
elseif(FALCON_ENGINE_PLATFORM_LINUX)
    set(FALCON_ENGINE_EXTRA_LIBRARY_FILES ${FALCON_ENGINE_EXTRA_LIBRARY_FILES}
        ${BOOST_LIBRARY_FILE} dl Xcursor Xinerama Xrandr Xxf86vm X11)
endif()

target_link_libraries(FalconEngine ${FALCON_ENGINE_EXTRA_LIBRARY_FILES})

fe_add_export_definition(FalconEngine)

fe_add_source_group("Shader Files" ${CMAKE_CURRENT_SOURCE_DIR}/src/FalconEngine "${FALCON_ENGINE_GRAPHICS_SHADER_FILES}")

fe_add_source_group("Source Files" ${CMAKE_CURRENT_SOURCE_DIR}/src/FalconEngine "${FALCON_ENGINE_CONTENT_SOURCE_FILES}")
fe_add_source_group("Source Files" ${CMAKE_CURRENT_SOURCE_DIR}/src/FalconEngine "${FALCON_ENGINE_CONTEXT_SOURCE_FILES}")
fe_add_source_group("Source Files" ${CMAKE_CURRENT_SOURCE_DIR}/src/FalconEngine "${FALCON_ENGINE_CORE_SOURCE_FILES}")
fe_add_source_group("Source Files" ${CMAKE_CURRENT_SOURCE_DIR}/src/FalconEngine "${FALCON_ENGINE_GRAPHICS_SOURCE_FILES}")
fe_add_source_group("Source Files" ${CMAKE_CURRENT_SOURCE_DIR}/src/FalconEngine "${FALCON_ENGINE_INPUT_SOURCE_FILES}")
fe_add_source_group("Source Files" ${CMAKE_CURRENT_SOURCE_DIR}/src/FalconEngine "${FALCON_ENGINE_MATH_SOURCE_FILES}")

fe_add_source_group("Header Files" ${CMAKE_CURRENT_SOURCE_DIR}/include/FalconEngine "${FALCON_ENGINE_CONTENT_HEADER_FILES}")
fe_add_source_group("Header Files" ${CMAKE_CURRENT_SOURCE_DIR}/include/FalconEngine "${FALCON_ENGINE_CONTEXT_HEADER_FILES}")
fe_add_source_group("Header Files" ${CMAKE_CURRENT_SOURCE_DIR}/include/FalconEngine "${FALCON_ENGINE_CORE_HEADER_FILES}")
fe_add_source_group("Header Files" ${CMAKE_CURRENT_SOURCE_DIR}/include/FalconEngine "${FALCON_ENGINE_GRAPHICS_HEADER_FILES}")
fe_add_source_group("Header Files" ${CMAKE_CURRENT_SOURCE_DIR}/include/FalconEngine "${FALCON_ENGINE_INPUT_HEADER_FILES}")
fe_add_source_group("Header Files" ${CMAKE_CURRENT_SOURCE_DIR}/include/FalconEngine "${FALCON_ENGINE_MATH_HEADER_FILES}")

fe_set_target_folder(FalconEngine "Falcon Engine Library Targets")
fe_set_target_output(FalconEngine)

# Update output shader folders
fe_assert_defined(FALCON_ENGINE_RUNTIME_OUTPUT_DIR)

file(REMOVE_RECURSE "${FALCON_ENGINE_RUNTIME_OUTPUT_DIR}/Debug/Content/Shader")
file(REMOVE_RECURSE "${FALCON_ENGINE_RUNTIME_OUTPUT_DIR}/Release/Content/Shader")
file(COPY ${FALCON_ENGINE_GRAPHICS_SHADER_FILES} DESTINATION "${FALCON_ENGINE_RUNTIME_OUTPUT_DIR}/Debug/Content/Shader")
file(COPY ${FALCON_ENGINE_GRAPHICS_SHADER_FILES} DESTINATION "${FALCON_ENGINE_RUNTIME_OUTPUT_DIR}/Release/Content/Shader")

#
# Set up Falcon Engine tool targets
#

if (NOT "${FALCON_ENGINE_CONTENT_PIPELINE_SOURCE_FILES}" STREQUAL "")
    add_executable(FalconEngine.Pipeline
        ${FALCON_ENGINE_CONTENT_PIPELINE_SOURCE_FILES})

    target_link_libraries(FalconEngine.Pipeline
        FalconEngine)

    fe_set_target_folder(FalconEngine.Pipeline "Falcon Engine Tool Targets")
    fe_set_target_output(FalconEngine.Pipeline)
endif()

#
# Set up Falcon Engine sample targets
#

fe_add_sample("FalconEngine.Sample.FPS" "src/FalconEngine/Sample/FPS")
fe_add_sample("FalconEngine.Sample.TPS" "src/FalconEngine/Sample/TPS")

