cmake_minimum_required(VERSION 3.0)

include(${FALCON_ENGINE_ROOT_DIR}/cmake/Compiler.cmake)
include(${FALCON_ENGINE_ROOT_DIR}/cmake/Platform.cmake)
include(${FALCON_ENGINE_ROOT_DIR}/cmake/Target.cmake)

include_directories(${FALCON_ENGINE_INCLUDE_DIR})
link_directories(${FALCON_ENGINE_LIBRARY_DIR})

file(GLOB_RECURSE FALCON_ENGINE_HEADER_FILES *.h)
add_library(FalconEngine.Include STATIC ${FALCON_ENGINE_HEADER_FILES})
fe_set_target_folder(FalconEngine.Include "FalconEngine Library Targets")
fe_set_target_language(FalconEngine.Include CXX)

file(GLOB_RECURSE FALCON_ENGINE_CONTENT_HEADER_FILES Content/*.h)
add_library(FalconEngine.Content.Include STATIC ${FALCON_ENGINE_CONTENT_HEADER_FILES})
fe_set_target_folder(FalconEngine.Content.Include "FalconEngine Library Targets")
fe_set_target_language(FalconEngine.Content.Include CXX)

file(GLOB_RECURSE FALCON_ENGINE_CONTEXT_HEADER_FILES Context/*.h)
add_library(FalconEngine.Context.Include STATIC ${FALCON_ENGINE_CONTEXT_HEADER_FILES})
fe_set_target_folder(FalconEngine.Context.Include "FalconEngine Library Targets")
fe_set_target_language(FalconEngine.Context.Include CXX)

file(GLOB_RECURSE FALCON_ENGINE_CORE_HEADER_FILES Core/*.h)
add_library(FalconEngine.Core.Include STATIC ${FALCON_ENGINE_CORE_HEADER_FILES})
fe_set_target_folder(FalconEngine.Core.Include "FalconEngine Library Targets")
fe_set_target_language(FalconEngine.Core.Include CXX)

file(GLOB_RECURSE FALCON_ENGINE_GRAPHICS_HEADER_FILES Graphics/*.h)
add_library(FalconEngine.Graphics.Include STATIC ${FALCON_ENGINE_GRAPHICS_HEADER_FILES})
fe_set_target_folder(FalconEngine.Graphics.Include "FalconEngine Library Targets")
fe_set_target_language(FalconEngine.Graphics.Include CXX)

file(GLOB_RECURSE FALCON_ENGINE_INPUT_HEADER_FILES Input/*.h)
add_library(FalconEngine.Input.Include STATIC ${FALCON_ENGINE_INPUT_HEADER_FILES})
fe_set_target_folder(FalconEngine.Input.Include "FalconEngine Library Targets")
fe_set_target_language(FalconEngine.Input.Include CXX)

file(GLOB_RECURSE FALCON_ENGINE_MATH_HEADER_FILES Math/*.h)
add_library(FalconEngine.Math.Include STATIC ${FALCON_ENGINE_MATH_HEADER_FILES})
fe_set_target_folder(FalconEngine.Math.Include "FalconEngine Library Targets")
fe_set_target_language(FalconEngine.Math.Include CXX)
