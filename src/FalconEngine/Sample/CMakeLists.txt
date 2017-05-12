cmake_minimum_required(VERSION 3.1)

# TODO(Wuxiang)
include(${FALCON_ENGINE_ROOT_DIR}/cmake/Compiler.cmake)
include(${FALCON_ENGINE_ROOT_DIR}/cmake/Dependency.cmake)
include(${FALCON_ENGINE_ROOT_DIR}/cmake/Platform.cmake)
include(${FALCON_ENGINE_ROOT_DIR}/cmake/Target.cmake)

function(add_sample SAMPLE_PROJECT_NAME SAMPLE_PROJECT_DIR)

    include_directories(${FALCON_ENGINE_INCLUDE_DIR})
    link_directories(
        ${FALCON_ENGINE_LIBRARY_DIR} 
        ${FALCON_ENGINE_ARCHIVE_OUTPUT_DIR})

    file(GLOB_RECURSE SAMPLE_PROJECT_FILES ${SAMPLE_PROJECT_DIR}/*.h ${SAMPLE_PROJECT_DIR}/*.cpp)

    add_executable(${SAMPLE_PROJECT_NAME} ${SAMPLE_PROJECT_FILES})

    set(SAMPLE_EXTRA_LIBRARY_FILES ${ASSIMP_LIBRARY_FILE})

    if (FALCON_ENGINE_PLATFORM_GLFW)
        set(SAMPLE_EXTRA_LIBRARY_FILES ${SAMPLE_EXTRA_LIBRARY_FILES}
            ${GL_LIBRARY_FILE}
            ${GLEW_LIBRARY_FILE}
            ${GLFW_LIBRARY_FILE})

        if (FALCON_ENGINE_PLATFORM_WINDOWS)
            set(SAMPLE_EXTRA_LIBRARY_FILES ${SAMPLE_EXTRA_LIBRARY_FILES} 
                kernel32 user32 gdi32 winspool shell32 ole32 oleaut32 uuid comdlg32 advapi32)
        elseif (FALCON_ENGINE_PLATFORM_LINUX)
            set(SAMPLE_EXTRA_LIBRARY_FILES ${SAMPLE_EXTRA_LIBRARY_FILES} 
                dl X11)
        endif()
    elseif(PLATFORM_QT)
        # TODO(Wuxiang):
        message(WARNING "Windows Qt dependency not configured properly.")
    endif()

    target_link_libraries(${SAMPLE_PROJECT_NAME} ${SAMPLE_EXTRA_LIBRARY_FILES}
        FalconEngine.Content
        FalconEngine.Context
        FalconEngine.Core
        FalconEngine.Graphics
        FalconEngine.Input
        FalconEngine.Math)

    fe_set_target_folder(${SAMPLE_PROJECT_NAME} "FalconEngine Sample Targets")
    fe_set_target_output(${SAMPLE_PROJECT_NAME})

endfunction()

add_sample("FalconEngine.Sample.Viewer" "Viewer")
