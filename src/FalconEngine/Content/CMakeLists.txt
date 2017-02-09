set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${FALCON_ENGINE_ARCHIVE_OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${FALCON_ENGINE_LIBRARY_OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${FALCON_ENGINE_RUNTIME_OUTPUT_DIR})

file(GLOB FALCON_ENGINE_CONTENT_SOURCE_FILES *.cpp)

include_directories(${FALCON_ENGINE_INCLUDE_DIR})
link_directories(${FALCON_ENGINE_LIBRARY_DIR})

# Content
add_library(FalconEngine.Content STATIC
    ${FALCON_ENGINE_CONTENT_SOURCE_FILES})

target_link_libraries(FalconEngine.Content 
    FalconEngine.Core.lib
    FalconEngine.Graphics.lib)

set_target_properties(FalconEngine.Content PROPERTIES COMPILE_FLAGS "/MTd")
set_target_properties(FalconEngine.Content PROPERTIES SUFFIX ".lib")
set_target_properties(FalconEngine.Content PROPERTIES FOLDER "FalconEngine Library Targets")

link_directories(
    ${FALCON_ENGINE_LIBRARY_DIR}
    ${FALCON_ENGINE_RUNTIME_OUTPUT_DIR})

# Content Pipeline
add_executable(FalconEngine.Content.Pipeline AssetBuilder.cpp)

if (WIN32)
set(FALCON_ENGINE_CONTENT_PIPELINE_EXTRA_BINRARY_FILES assimp-vc140-mt.lib)
else()
message(WARNING "Dependency not available in linux.")
endif()

target_link_libraries(FalconEngine.Content.Pipeline 
    FalconEngine.Core.lib
    FalconEngine.Content.lib
    FalconEngine.Graphics.lib
    ${FALCON_ENGINE_CONTENT_PIPELINE_EXTRA_BINRARY_FILES}
    )

set_target_properties(FalconEngine.Content.Pipeline PROPERTIES COMPILE_FLAGS "/MTd /Gm-")

# Prevent strangely setting the import library: https://msdn.microsoft.com/en-us/library/67wc07b9.aspx
set_target_properties(FalconEngine.Content.Pipeline PROPERTIES LINK_FLAGS "/INCREMENTAL:NO /IMPLIB:")
set_target_properties(FalconEngine.Content.Pipeline PROPERTIES SUFFIX ".exe")
set_target_properties(FalconEngine.Content.Pipeline PROPERTIES FOLDER "FalconEngine Executable Targets")