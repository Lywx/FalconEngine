cmake_minimum_required(VERSION 3.8)
cmake_policy(SET CMP0054 NEW)

# NOTE(Wuxiang): Include guard.
if (FALCON_ENGINE_UTILITY_INITIALIZED)
    return()
endif()

set(FALCON_ENGINE_UTILITY_INITIALIZED TRUE)

function(fe_assert_defined VARIABLE_NAME)
    if (NOT DEFINED ${VARIABLE_NAME})
        message(FATAL_ERROR "${VARIABLE_NAME} variable is not defined.")
    endif()
endfunction()

function(fe_assert VARIABLE_NAME)
    if (NOT ${VARIABLE_NAME})
        message(FATAL_ERROR "${VARIABLE_NAME} variable is not true.")
    endif()
endfunction()

function(fe_set_target_output TARGET_NAME)

    fe_assert_defined(FALCON_ENGINE_OUTPUT_SUFFIX)
    fe_assert_defined(FALCON_ENGINE_ARCHIVE_OUTPUT_DIR)
    fe_assert_defined(FALCON_ENGINE_LIBRARY_OUTPUT_DIR)
    fe_assert_defined(FALCON_ENGINE_RUNTIME_OUTPUT_DIR)

    set_target_properties(${TARGET_NAME} PROPERTIES
        PROJECT_LABEL                           ${TARGET_NAME}

        ARCHIVE_OUTPUT_DIRECTORY                ${FALCON_ENGINE_ARCHIVE_OUTPUT_DIR}
        ARCHIVE_OUTPUT_DIRECTORY_DEBUG          ${FALCON_ENGINE_ARCHIVE_OUTPUT_DIR}/Debug
        ARCHIVE_OUTPUT_DIRECTORY_RELEASE        ${FALCON_ENGINE_ARCHIVE_OUTPUT_DIR}/Release
        ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO ${FALCON_ENGINE_ARCHIVE_OUTPUT_DIR}/Release
        ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL     ${FALCON_ENGINE_ARCHIVE_OUTPUT_DIR}/Release

        LIBRARY_OUTPUT_DIRECTORY                ${FALCON_ENGINE_LIBRARY_OUTPUT_DIR}
        LIBRARY_OUTPUT_DIRECTORY_DEBUG          ${FALCON_ENGINE_LIBRARY_OUTPUT_DIR}/Debug
        LIBRARY_OUTPUT_DIRECTORY_RELEASE        ${FALCON_ENGINE_LIBRARY_OUTPUT_DIR}/Release
        LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO ${FALCON_ENGINE_LIBRARY_OUTPUT_DIR}/Release
        LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL     ${FALCON_ENGINE_LIBRARY_OUTPUT_DIR}/Release

        RUNTIME_OUTPUT_DIRECTORY                ${FALCON_ENGINE_RUNTIME_OUTPUT_DIR}
        RUNTIME_OUTPUT_DIRECTORY_DEBUG          ${FALCON_ENGINE_RUNTIME_OUTPUT_DIR}/Debug
        RUNTIME_OUTPUT_DIRECTORY_RELEASE        ${FALCON_ENGINE_RUNTIME_OUTPUT_DIR}/Release
        RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${FALCON_ENGINE_RUNTIME_OUTPUT_DIR}/Release
        RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL     ${FALCON_ENGINE_RUNTIME_OUTPUT_DIR}/Release

        DEBUG_POSTFIX                           "-d"
        RELEASE_POSTFIX                         ""
        
        OUTPUT_NAME                             "${TARGET_NAME}${FALCON_ENGINE_OUTPUT_SUFFIX}"
    )

    set_target_properties(${TARGET_NAME} PROPERTIES 
        VS_DEBUGGER_WORKING_DIRECTORY "${FALCON_ENGINE_RUNTIME_OUTPUT_DIR}/Debug")

endfunction()

function(fe_set_target_folder TARGET_NAME FOLDER_NAME)
    set_target_properties(${TARGET_NAME} PROPERTIES
        FOLDER "${FOLDER_NAME}")
endfunction()

function(fe_set_target_language TARGET_NAME LANGUAGE_NAME)
    set_target_properties(${TARGET_NAME} PROPERTIES
        LINKER_LANGUAGE ${LANGUAGE_NAME})
endfunction()

function(fe_add_export_definition TARGET_NAME)
    fe_assert_defined(FALCON_ENGINE_BUILD_DYNAMIC)
    if(FALCON_ENGINE_BUILD_DYNAMIC)
        set_target_properties(${TARGET_NAME} PROPERTIES 
            COMPILE_DEFINITIONS FALCON_ENGINE_SYMBOL_EXPORT)
    else()
        set_target_properties(${TARGET_NAME} PROPERTIES 
            COMPILE_DEFINITIONS FALCON_ENGINE_BUILD_STATIC)
    endif()
endfunction()

function(fe_add_import_definition TARGET_NAME)
    fe_assert_defined(FALCON_ENGINE_BUILD_DYNAMIC)
    if(FALCON_ENGINE_BUILD_DYNAMIC)
        set_target_properties(${TARGET_NAME} PROPERTIES 
            COMPILE_DEFINITIONS FALCON_ENGINE_SYMBOL_IMPORT)
    else()
        set_target_properties(${TARGET_NAME} PROPERTIES 
            COMPILE_DEFINITIONS FALCON_ENGINE_BUILD_STATIC)
    endif()
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

function(fe_add_external_object TARGET_NAME
                                SOURCE_FILES
                                SOURCE_EXTENSION
                                SOURCE_ROOT_DIR
                                OBJECT_FILES      # Output
                                OBJECT_EXTENSION
                                OBJECT_ROOT_DIR
                                OBJECT_HIERARCHY
                                COMPILER_EXE
                                COMPILER_ARGS)

    fe_assert(TARGET_NAME)

    fe_assert(SOURCE_FILES)
    fe_assert(SOURCE_EXTENSION)
    fe_assert(SOURCE_ROOT_DIR)

    fe_assert_defined(OBJECT_FILES)

    # Clean output variable
    set(${OBJECT_FILES} "" PARENT_SCOPE)
    set(OBJECT_FILES_LOCAL "")

    fe_assert(OBJECT_EXTENSION)
    fe_assert(OBJECT_ROOT_DIR)
    fe_assert_defined(OBJECT_HIERARCHY)

    fe_assert(COMPILER_EXE)
    fe_assert(COMPILER_ARGS)

    foreach(SOURCE_FILE ${SOURCE_FILES})

        #
        # Produce output object file path and object target name.
        #

        # Replace extension to get object file path.
        string(REPLACE
            "${SOURCE_EXTENSION}" # Match
            "${OBJECT_EXTENSION}" # Replace
            OBJECT_FILE           # Output
            "${SOURCE_FILE}"      # Input
        )

        get_filename_component(
            OBJECT_TARGET
            "${OBJECT_FILE}" NAME)

        if(${OBJECT_HIERARCHY})

            # Replace source directory path to with object directory to get object file path.
            string(REPLACE
                "${SOURCE_ROOT_DIR}" # Match
                "${OBJECT_ROOT_DIR}" # Replace
                OBJECT_FILE          # Output
                "${OBJECT_FILE}")    # Input
        else()

            # Replace source directory path to with object directory to get object file path.
            get_filename_component(
                OBJECT_FILE
                "${OBJECT_FILE}" NAME)

            string(CONCAT OBJECT_FILE
                "${OBJECT_ROOT_DIR}"
                "${OBJECT_FILE}")
        endif()

        # Get object output directory.
        if(${OBJECT_HIERARCHY})
            get_filename_component(OBJECT_DIR
                ${OBJECT_FILE} DIRECTORY)

            # Create folder hierarchy.
            execute_process(
                COMMAND mkdir ${OBJECT_DIR} --parents)
        else()
            execute_process(
                COMMAND mkdir ${OBJECT_ROOT_DIR} --parents)
        endif()

        # Add object to link target list.
        if(NOT "${OBJECT_FILES_LOCAL}" STREQUAL "")
            set(OBJECT_FILES_LOCAL ${OBJECT_FILES_LOCAL} ${OBJECT_FILE})
        else()
            # Special case for first target.
            set(OBJECT_FILES_LOCAL ${OBJECT_FILE})
        endif()

        # Add custom target to the project.
        add_custom_command(
            OUTPUT            ${OBJECT_FILE}

            # Call compiler to compile.
            COMMAND           ${COMPILER_EXE} ${COMPILER_ARGS} ${SOURCE_FILE} -o=${OBJECT_FILE}
            VERBATIM)
        add_custom_target(${OBJECT_TARGET} DEPENDS ${OBJECT_FILE})
        add_dependencies(${TARGET_NAME} ${OBJECT_TARGET})
    endforeach()

    # Return computed variable.
    set(${OBJECT_FILES} ${OBJECT_FILES_LOCAL} PARENT_SCOPE)
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
                dl)
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
