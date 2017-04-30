cmake_minimum_required(VERSION 3.0)

set(FALCON_ENGINE_UTILITY_INITIALIZED TRUE)

function(assert_defined VARIABLE_NAME)
    if (NOT DEFINED ${VARIABLE_NAME})
        message(FATAL_ERROR "${VARIABLE_NAME} variable is not defined.")
    endif()
endfunction()

function(assert VARIABLE_NAME)
    if (NOT ${VARIABLE_NAME})
        message(FATAL_ERROR "${VARIABLE_NAME} variable is not true.")
    endif()
endfunction()



