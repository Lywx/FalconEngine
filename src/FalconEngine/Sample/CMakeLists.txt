set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${FALCON_ENGINE_ARCHIVE_OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${FALCON_ENGINE_LIBRARY_OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${FALCON_ENGINE_RUNTIME_OUTPUT_DIR})

function(add_sample sampleProject sampleDir)
    file(GLOB FALCON_ENGINE_SAMPLE_FILES ${sampleDir}/*.h ${sampleDir}/*.cpp)

    include_directories(${FALCON_ENGINE_INCLUDE_DIR})

    link_directories(${FALCON_ENGINE_LIBRARY_DIR} ${FALCON_ENGINE_RUNTIME_OUTPUT_DIR})

    add_executable(${sampleProject} ${FALCON_ENGINE_SAMPLE_FILES})

    if (FALCON_ENGINE_PLATFORM_GLFW)
        if (WIN32)
            set(FALCON_ENGINE_SAMPLE_EXTRA_LIBRARY_FILES
                assimp-vc140-mt.lib # Assimp
                glew32sd.lib        # Glew
                glfw3.lib           # GLFW
                opengl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib
                )
        elseif (UNIX)
            set(FALCON_ENGINE_SAMPLE_EXTRA_LIBRARY_FILES
                libassimp.a # Assimp
                libGLEW.a   # Glew
                libglfw3.a  # GLFW
                )
        endif()

    elseif(PLATFORM_QT)
        if (WIN32)
            # TODO(Wuxiang):
            message(WARNING "Windows Qt dependency not configured properly.")
        elseif (UNIX)
            set(FALCON_ENGINE_SAMPLE_EXTRA_LIBRARY_FILES
                # Assimp
                libassimp.a)
        endif()
    endif()

    target_link_libraries(${sampleProject}
        FalconEngine.Content.lib
        FalconEngine.Context.lib
        FalconEngine.Core.lib
        FalconEngine.Graphics.lib
        FalconEngine.Input.lib
        FalconEngine.Math.lib
        ${FALCON_ENGINE_SAMPLE_EXTRA_LIBRARY_FILES}
        )

    if (WIN32)
        set_target_properties(${sampleProject} PROPERTIES SUFFIX ".exe")

        set_target_properties(${sampleProject} PROPERTIES COMPILE_FLAGS "/MTd /ZI")
        set_target_properties(${sampleProject} PROPERTIES LINK_FLAGS "/IMPLIB:")
        #set_target_properties(${sampleProject} PROPERTIES LINK_FLAGS "/INCREMENTAL /IMPLIB:")
        set_target_properties(${sampleProject} PROPERTIES FOLDER "FalconEngine Sample Targets")
    else()
    endif()

endfunction()

add_sample("FalconEngine.Sample.Viewer" "Viewer")
