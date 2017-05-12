cmake_minimum_required(VERSION 3.1)

include(${FALCON_ENGINE_ROOT_DIR}/cmake/Compiler.cmake)
include(${FALCON_ENGINE_ROOT_DIR}/cmake/Dependency.cmake)
include(${FALCON_ENGINE_ROOT_DIR}/cmake/Platform.cmake)
include(${FALCON_ENGINE_ROOT_DIR}/cmake/Target.cmake)

include_directories(${FALCON_ENGINE_INCLUDE_DIR})
link_directories(${FALCON_ENGINE_LIBRARY_DIR} ${FALCON_ENGINE_ARCHIVE_OUTPUT_DIR})

file(GLOB FALCON_ENGINE_CONTENT_SOURCE_FILES *.cpp)

add_library(FalconEngine.Content           # Name
    ${FALCON_ENGINE_LIBRARY_TYPE}          # Type
    ${FALCON_ENGINE_LIBRARY_TYPE} 	       # Type
    ${FALCON_ENGINE_CONTENT_SOURCE_FILES}) # Source

target_link_libraries(FalconEngine.Content FalconEngine.Graphics)

fe_set_target_folder(FalconEngine.Content "FalconEngine Library Targets")
fe_set_target_output(FalconEngine.Content)

add_executable(FalconEngine.Content.Pipeline
    Pipeline/PipelineMain.cpp)

set(FALCON_ENGINE_CONTENT_PIPELINE_EXTRA_LIBRARY_FILES
    ${ASSIMP_LIBRARY_FILE})

target_link_libraries(FalconEngine.Content.Pipeline ${FALCON_ENGINE_CONTENT_PIPELINE_EXTRA_LIBRARY_FILES}
    FalconEngine.Core
    FalconEngine.Content
    FalconEngine.Graphics
    FalconEngine.Math)

fe_set_target_folder(FalconEngine.Content.Pipeline "FalconEngine Executable Targets")
fe_set_target_output(FalconEngine.Content.Pipeline)
