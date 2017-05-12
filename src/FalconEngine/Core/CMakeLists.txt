cmake_minimum_required(VERSION 3.1)

include(${FALCON_ENGINE_ROOT_DIR}/cmake/Compiler.cmake)
include(${FALCON_ENGINE_ROOT_DIR}/cmake/Platform.cmake)
include(${FALCON_ENGINE_ROOT_DIR}/cmake/Target.cmake)

include_directories(${FALCON_ENGINE_INCLUDE_DIR})
link_directories(${FALCON_ENGINE_LIBRARY_DIR})

file(GLOB_RECURSE FALCON_ENGINE_CORE_SOURCE_FILES *.cpp)

add_library(
    FalconEngine.Core                   # Name
    ${FALCON_ENGINE_LIBRARY_TYPE} 	    # Type
    ${FALCON_ENGINE_CORE_SOURCE_FILES}) # Source

fe_add_export_definition(Core)
fe_set_target_folder(FalconEngine.Core "FalconEngine Library Targets")
fe_set_target_output(FalconEngine.Core)
