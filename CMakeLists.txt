cmake_minimum_required(VERSION 3.19)
project(point_vortex)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH $ENV{QT6_DIR})

function(loadQt6DllsIntoTarget target)
    if (WIN32)
        set(DEBUG_SUFFIX)
        if (MSVC)
            if (CMAKE_BUILD_TYPE MATCHES "Debug")
                set(DEBUG_SUFFIX "d")
            endif ()
        endif ()
        set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
            if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
                set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
            endif ()
        endif ()
        if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
            add_custom_command(TARGET ${target} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E make_directory
                    "$<TARGET_FILE_DIR:${target}>/plugins/platforms/")
            add_custom_command(TARGET ${target} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                    "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                    "$<TARGET_FILE_DIR:${target}>/plugins/platforms/")
        endif ()
        foreach (QT_LIB ${REQUIRED_LIBS})
            add_custom_command(TARGET ${target} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                    "${QT_INSTALL_PATH}/bin/Qt${QT_VERSION}${QT_LIB}${DEBUG_SUFFIX}.dll"
                    "$<TARGET_FILE_DIR:${target}>")
        endforeach (QT_LIB)
    endif ()
endfunction()

# -------------------------------------------------- Setting up QT
set(QT_VERSION 6)
set(REQUIRED_LIBS Core Gui Widgets OpenGL)
set(REQUIRED_LIBS_QUALIFIED Qt6::Core Qt6::Gui Qt6::Widgets Qt6::OpenGL)

file(GLOB_RECURSE HEADERS "${PROJECT_SOURCE_DIR}/include/*.h")
file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")
# Exclude main.cpp from sources
list(REMOVE_ITEM SOURCES "${PROJECT_SOURCE_DIR}/src/main.cpp")

file(GLOB_RECURSE TEST_SOURCES "${PROJECT_SOURCE_DIR}/tests/*.cpp")

include_directories(${CMAKE_SOURCE_DIR}/include)
add_executable(${PROJECT_NAME} ${SOURCES} "${PROJECT_SOURCE_DIR}/src/main.cpp" ${HEADERS})

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()

find_package(OpenGL REQUIRED)
if (NOT WIN32) # TODO: change to if linux
    find_package(GLUT REQUIRED)
endif ()

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
loadQt6DllsIntoTarget(${PROJECT_NAME})

# -------------------------------------------------- Google test
if (ENABLE_GOOGLE_TEST)
    include(FetchContent)
    FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    # TODO: add SOURCES to compile
    add_executable(${PROJECT_NAME}_test ${TEST_SOURCES} ${HEADERS} ${SOURCES})
    target_link_libraries(
            ${PROJECT_NAME}_test
            gtest_main
    )
    target_link_libraries(${PROJECT_NAME}_test ${REQUIRED_LIBS_QUALIFIED})

    loadQt6DllsIntoTarget(${PROJECT_NAME}_test)

    include(GoogleTest)
    gtest_discover_tests(${PROJECT_NAME}_test)
endif ()

# -------------------------------------------------- Compiling GLSL shaders
if (${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL "AMD64")
    find_program(GLSL_VALIDATOR NAMES glslangValidator PATH "$ENV{VULKAN_SDK}/Bin")
else ()
    find_program(GLSL_VALIDATOR NAMES glslangValidator PATH "$ENV{VULKAN_SDK}/Bin32")
endif ()

file(GLOB_RECURSE GLSL_SOURCE_FILES
        "shaders/*.frag"
        "shaders/*.vert"
        )

foreach (GLSL ${GLSL_SOURCE_FILES})
    get_filename_component(FILE_NAME ${GLSL} NAME)
    set(SPIRV "${PROJECT_BINARY_DIR}/shaders/${FILE_NAME}.spv")
    add_custom_command(
            OUTPUT ${SPIRV}
            COMMAND ${CMAKE_COMMAND} -E make_directory "${PROJECT_BINARY_DIR}/shaders/"
            COMMAND ${GLSL_VALIDATOR} -V ${GLSL} -o ${SPIRV}
            DEPENDS ${GLSL})
    list(APPEND SPIRV_BINARY_FILES ${SPIRV})
endforeach (GLSL)

add_custom_target(
        glsl_shaders
        DEPENDS ${SPIRV_BINARY_FILES}
)

add_dependencies(${PROJECT_NAME} glsl_shaders)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders/"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_BINARY_DIR}/shaders"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders"
        )
