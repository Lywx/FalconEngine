cmake_minimum_required(VERSION 3.1)

include(${FALCON_ENGINE_ROOT_DIR}/cmake/Compiler.cmake)
include(${FALCON_ENGINE_ROOT_DIR}/cmake/Platform.cmake)
include(${FALCON_ENGINE_ROOT_DIR}/cmake/Target.cmake)

include_directories(${FALCON_ENGINE_INCLUDE_DIR})
link_directories(${FALCON_ENGINE_LIBRARY_DIR})

file(GLOB_RECURSE FALCON_ENGINE_CONTEXT_SOURCE_FILES *.cpp)

add_library(
    FalconEngine.Context                  # Name
    ${FALCON_ENGINE_LIBRARY_TYPE} 	      # Type
    ${FALCON_ENGINE_CONTEXT_SOURCE_FILES} # Source
    )

target_link_libraries(FalconEngine.Context 
    FalconEngine.Core 
    FalconEngine.Graphics
    FalconEngine.Math)

fe_add_export_definition(Context)
fe_add_import_definition("Core;Graphics;Math")
fe_set_target_folder(FalconEngine.Context "FalconEngine Library Targets")
fe_set_target_output(FalconEngine.Context)
