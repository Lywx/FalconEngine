file(GLOB FALCON_ENGINE_HEADER_FILES *.h)

include_directories(${FALCON_ENGINE_INCLUDE_DIR})
link_directories(${FALCON_ENGINE_LIBRARY_DIR})

add_library(FalconEngine.Include STATIC ${FALCON_ENGINE_HEADER_FILES})
set_target_properties(FalconEngine.Include PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(FalconEngine.Include PROPERTIES FOLDER "FalconEngine Targets")

file(GLOB FALCON_ENGINE_CONTENT_HEADER_FILES
    Content/*.h 
    Content/*.inl)
add_library(FalconEngine.Content.Include STATIC ${FALCON_ENGINE_CONTENT_HEADER_FILES})
set_target_properties(FalconEngine.Content.Include PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(FalconEngine.Content.Include PROPERTIES FOLDER "FalconEngine Targets")

file(GLOB FALCON_ENGINE_CORE_HEADER_FILES
    Core/*.h 
    Core/*.inl
    Core/Objects/*.h 
    Core/Objects/*.inl)
add_library(FalconEngine.Core.Include STATIC ${FALCON_ENGINE_CORE_HEADER_FILES})
set_target_properties(FalconEngine.Core.Include PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(FalconEngine.Core.Include PROPERTIES FOLDER "FalconEngine Targets")

file(GLOB FALCON_ENGINE_GRAPHICS_HEADER_FILES
    Graphics/*.h 
    Graphics/*.inl
    Graphics/Controllers/*.h 
    Graphics/Controllers/*.inl 
    Graphics/GlobalEffects/*.h
    Graphics/GlobalEffects/*.inl
    Graphics/LocalEffects/*.h
    Graphics/LocalEffects/*.inl
    Graphics/Renderers/*.h
    Graphics/Renderers/*.inl
    Graphics/Renderers/OpenGL/*.h
    Graphics/Renderers/OpenGL/*.inl
    Graphics/Resources/*.h 
    Graphics/Resources/*.inl 
    Graphics/Scenes/*.h 
    Graphics/Scenes/*.inl 
    Graphics/Shaders/*.h 
    Graphics/Shaders/*.inl
    Graphics/States/*.h
    Graphics/States/*.inl)
add_library(FalconEngine.Graphics.Include STATIC ${FALCON_ENGINE_GRAPHICS_HEADER_FILES})
set_target_properties(FalconEngine.Graphics.Include PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(FalconEngine.Graphics.Include PROPERTIES FOLDER "FalconEngine Targets")

file(GLOB FALCON_ENGINE_GEOMETRY_HEADER_FILES
    Geometry/*.h 
    Geometry/*.inl)
add_library(FalconEngine.Geometry.Include STATIC ${FALCON_ENGINE_GEOMETRY_HEADER_FILES})
set_target_properties(FalconEngine.Geometry.Include PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(FalconEngine.Geometry.Include PROPERTIES FOLDER "FalconEngine Targets")

file(GLOB FALCON_ENGINE_INPUT_HEADER_FILES
    Input/*.h
    Input/*.inl)
add_library(FalconEngine.Input.Include STATIC ${FALCON_ENGINE_INPUT_HEADER_FILES})
set_target_properties(FalconEngine.Input.Include PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(FalconEngine.Input.Include PROPERTIES FOLDER "FalconEngine Targets")
 
file(GLOB FALCON_ENGINE_MATH_HEADER_FILES
    Math/*.h
    Math/*.inl)
add_library(FalconEngine.Math.Include STATIC ${FALCON_ENGINE_MATH_HEADER_FILES})
set_target_properties(FalconEngine.Math.Include PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(FalconEngine.Math.Include PROPERTIES FOLDER "FalconEngine Targets")