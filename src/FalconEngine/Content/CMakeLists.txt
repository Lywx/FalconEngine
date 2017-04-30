cmake_minimum_required(VERSION 3.0)

include(${FALCON_ENGINE_ROOT_DIR}/cmake/Compiler.cmake)
include(${FALCON_ENGINE_ROOT_DIR}/cmake/Platform.cmake)
include(${FALCON_ENGINE_ROOT_DIR}/cmake/Target.cmake)

include_directories(${FALCON_ENGINE_INCLUDE_DIR})
link_directories(${FALCON_ENGINE_LIBRARY_DIR} ${FALCON_ENGINE_ARCHIVE_OUTPUT_DIR})

file(GLOB FALCON_ENGINE_CONTENT_SOURCE_FILES *.cpp)

add_library(FalconEngine.Content           # Name
    ${FALCON_ENGINE_LIBRARY_TYPE} 	       # Type
    ${FALCON_ENGINE_CONTENT_SOURCE_FILES}) # Source

target_link_libraries(FalconEngine.Content
    FalconEngine.Core
    FalconEngine.Graphics)

fe_set_target_folder(FalconEngine.Content "FalconEngine Library Targets")
fe_set_target_output(FalconEngine.Content)

add_executable(FalconEngine.Content.Pipeline
    Pipeline/PipelineMain.cpp)

# TODO(Wuxiang)
# set(FALCON_ENGINE_CONTENT_PIPELINE_EXTRA_LIBRARY_FILES
#     assimp-vc140-mt
#     glew32sd
#     glfw3
#     opengl32)

target_link_libraries(FalconEngine.Content.Pipeline
    FalconEngine.Core
    FalconEngine.Content
    FalconEngine.Graphics
    FalconEngine.Math
    ${FALCON_ENGINE_CONTENT_PIPELINE_EXTRA_LIBRARY_FILES}
)

fe_set_target_folder(FalconEngine.Content.Pipeline "FalconEngine Executable Targets")
fe_set_target_output(FalconEngine.Content.Pipeline)
