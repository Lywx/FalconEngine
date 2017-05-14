cmake_minimum_required(VERSION 3.0)
cmake_policy(SET CMP0054 NEW)

# NOTE(Wuxiang): Include guard.
if (FALCON_ENGINE_TARGET_INITIALIZED)
    return()
endif()

set(FALCON_ENGINE_TARGET_INITIALIZED TRUE)

# Set up solution dependency
set(FALCON_ENGINE_INCLUDE_DIR ${FALCON_ENGINE_ROOT_DIR}/include)
set(FALCON_ENGINE_LIBRARY_DIR ${FALCON_ENGINE_ROOT_DIR}/lib)

# Set up solution output
set(FALCON_ENGINE_ARCHIVE_OUTPUT_DIR ${FALCON_ENGINE_ROOT_DIR}/bin)
set(FALCON_ENGINE_LIBRARY_OUTPUT_DIR ${FALCON_ENGINE_ROOT_DIR}/bin)
set(FALCON_ENGINE_RUNTIME_OUTPUT_DIR ${FALCON_ENGINE_ROOT_DIR}/bin)

# Set up library type
assert_defined(FALCON_ENGINE_BUILD_DYNAMIC)
if(FALCON_ENGINE_BUILD_DYNAMIC)
set(FALCON_ENGINE_LIBRARY_TYPE "SHARED")
else()
set(FALCON_ENGINE_LIBRARY_TYPE "STATIC")
endif()

function(fe_set_target_output CURRENT_TARGET_NAME)

    assert_defined(FALCON_ENGINE_OUTPUT_SUFFIX)

    set_target_properties(${CURRENT_TARGET_NAME} PROPERTIES
        PROJECT_LABEL                           ${CURRENT_TARGET_NAME}

        ARCHIVE_OUTPUT_DIRECTORY 			    ${FALCON_ENGINE_ARCHIVE_OUTPUT_DIR}
        ARCHIVE_OUTPUT_DIRECTORY_DEBUG          ${FALCON_ENGINE_ARCHIVE_OUTPUT_DIR}/Debug
        ARCHIVE_OUTPUT_DIRECTORY_RELEASE        ${FALCON_ENGINE_ARCHIVE_OUTPUT_DIR}/Release
        ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO ${FALCON_ENGINE_ARCHIVE_OUTPUT_DIR}/Release
        ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL     ${FALCON_ENGINE_ARCHIVE_OUTPUT_DIR}/Release

        RUNTIME_OUTPUT_DIRECTORY 			    ${FALCON_ENGINE_RUNTIME_OUTPUT_DIR}
        RUNTIME_OUTPUT_DIRECTORY_DEBUG 			${FALCON_ENGINE_RUNTIME_OUTPUT_DIR}/Debug
        RUNTIME_OUTPUT_DIRECTORY_RELEASE        ${FALCON_ENGINE_RUNTIME_OUTPUT_DIR}/Release
        RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${FALCON_ENGINE_RUNTIME_OUTPUT_DIR}/Release
        RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL     ${FALCON_ENGINE_RUNTIME_OUTPUT_DIR}/Release

        DEBUG_POSTFIX                           "-d"
        RELEASE_POSTFIX                         ""
        
        OUTPUT_NAME                             "${CURRENT_TARGET_NAME}${FALCON_ENGINE_OUTPUT_SUFFIX}"
    )
endfunction()

function(fe_set_target_folder TARGET_NAME FOLDER_NAME)
    set_target_properties(${TARGET_NAME} PROPERTIES
        FOLDER "${FOLDER_NAME}")
endfunction()

function(fe_set_target_language TARGET_NAME LANGUAGE_NAME)
    set_target_properties(${TARGET_NAME} PROPERTIES
        LINKER_LANGUAGE ${LANGUAGE_NAME})
endfunction()

function(fe_add_source_group GROUP_NAME TARGET_DIRECTORY TARGET_FILE_LIST)
    set(SOURCE_GROUP_DELIMITER "/")
    set(PREVIOUS_FILE_DIRECTORY "")
    set(CURRENT_FILE_LIST "")

    foreach(FILE ${TARGET_FILE_LIST})
        # Get the relative path.
        file(RELATIVE_PATH CURRENT_FILE_RELATIVE_PATH "${TARGET_DIRECTORY}" ${FILE})
        # Get the top relative folder, assuming file is ordered lexicographically.
        get_filename_component(CURRENT_FILE_DIRECTORY "${CURRENT_FILE_RELATIVE_PATH}" DIRECTORY)
        # Test if hit upon a sub-folder. If so, you should push all of previous file 
        # list into the previous folder before you process new file.
        if(NOT "${CURRENT_FILE_DIRECTORY}" STREQUAL "${PREVIOUS_FILE_DIRECTORY}")
            if(CURRENT_FILE_LIST)
                source_group("${GROUP_NAME}/${PREVIOUS_FILE_DIRECTORY}" FILES ${CURRENT_FILE_LIST})
            endif()
            # Reset file list after pushing all of them into a folder
            set(CURRENT_FILE_LIST "")
        endif()
        # Add new file into the file list.
        set(CURRENT_FILE_LIST ${CURRENT_FILE_LIST} ${FILE})
        # Update file directory.
        set(PREVIOUS_FILE_DIRECTORY "${CURRENT_FILE_DIRECTORY}")
    endforeach()
    # Push the remaining files into belonging folder.
    if(CURRENT_FILE_LIST)
        source_group("${GROUP_NAME}/${PREVIOUS_FILE_DIRECTORY}" FILES ${CURRENT_FILE_LIST})
    endif()
endfunction()

function(fe_add_sample SAMPLE_PROJECT_NAME SAMPLE_PROJECT_DIR)
    include_directories(${FALCON_ENGINE_INCLUDE_DIR})
    link_directories(${FALCON_ENGINE_ARCHIVE_OUTPUT_DIR}
        ${FALCON_ENGINE_LIBRARY_DIR})

    file(GLOB_RECURSE SAMPLE_PROJECT_FILES ${SAMPLE_PROJECT_DIR}/*.h ${SAMPLE_PROJECT_DIR}/*.cpp)
    add_executable(${SAMPLE_PROJECT_NAME} ${SAMPLE_PROJECT_FILES})

    set(SAMPLE_EXTRA_LIBRARY_FILES "")
    if(FALCON_ENGINE_WINDOW_GLFW)
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
        FalconEngine)

    fe_add_import_definition(${SAMPLE_PROJECT_NAME})
    fe_set_target_folder(${SAMPLE_PROJECT_NAME} "Falcon Engine Sample Targets")
    fe_set_target_output(${SAMPLE_PROJECT_NAME})

endfunction()
