file(GLOB FALCON_ENGINE_HEADER_FILES *.h)

include_directories(${FALCON_ENGINE_INCLUDE_DIR})
link_directories(${FALCON_ENGINE_LIBRARY_DIR})

add_library(FalconEngine.Include STATIC ${FALCON_ENGINE_HEADER_FILES})
set_target_properties(FalconEngine.Include PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(FalconEngine.Include PROPERTIES FOLDER "FalconEngine Library Targets")

file(GLOB_RECURSE FALCON_ENGINE_CONTENT_HEADER_FILES Content/*.h)
add_library(FalconEngine.Content.Include STATIC ${FALCON_ENGINE_CONTENT_HEADER_FILES})
set_target_properties(FalconEngine.Content.Include PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(FalconEngine.Content.Include PROPERTIES FOLDER "FalconEngine Library Targets")

file(GLOB_RECURSE FALCON_ENGINE_CONTEXT_HEADER_FILES Context/*.h)
add_library(FalconEngine.Context.Include STATIC ${FALCON_ENGINE_CONTEXT_HEADER_FILES})
set_target_properties(FalconEngine.Context.Include PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(FalconEngine.Context.Include PROPERTIES FOLDER "FalconEngine Library Targets")

file(GLOB_RECURSE FALCON_ENGINE_CORE_HEADER_FILES Core/*.h)
add_library(FalconEngine.Core.Include STATIC ${FALCON_ENGINE_CORE_HEADER_FILES})
set_target_properties(FalconEngine.Core.Include PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(FalconEngine.Core.Include PROPERTIES FOLDER "FalconEngine Library Targets")

file(GLOB_RECURSE FALCON_ENGINE_GRAPHICS_HEADER_FILES Graphics/*.h)
add_library(FalconEngine.Graphics.Include STATIC ${FALCON_ENGINE_GRAPHICS_HEADER_FILES})
set_target_properties(FalconEngine.Graphics.Include PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(FalconEngine.Graphics.Include PROPERTIES FOLDER "FalconEngine Library Targets")

file(GLOB_RECURSE FALCON_ENGINE_INPUT_HEADER_FILES Input/*.h)
add_library(FalconEngine.Input.Include STATIC ${FALCON_ENGINE_INPUT_HEADER_FILES})
set_target_properties(FalconEngine.Input.Include PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(FalconEngine.Input.Include PROPERTIES FOLDER "FalconEngine Library Targets")
 
file(GLOB_RECURSE FALCON_ENGINE_MATH_HEADER_FILES Math/*.h)
add_library(FalconEngine.Math.Include STATIC ${FALCON_ENGINE_MATH_HEADER_FILES})
set_target_properties(FalconEngine.Math.Include PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(FalconEngine.Math.Include PROPERTIES FOLDER "FalconEngine Library Targets")
