cmake_minimum_required(VERSION 3.16)
project(scratch)

cmake_policy(SET CMP0048 NEW)
cmake_policy(SET CMP0115 NEW)
cmake_policy(SET CMP0135 NEW)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall")

set(scratch_NAME Scratch)
set(scratch_VERSION_MAJOR 0)
set(scratch_VERSION_MINOR 1)

set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR})
set(scratch_DIR ${CMAKE_INSTALL_PREFIX})
set(scratch_DATADIR ${CMAKE_INSTALL_PREFIX}/share)

set(INCLUDES "${PROJECT_SOURCE_DIR}" "${PROJECT_SOURCE_DIR}/include")

find_package(SDL2 REQUIRED)
find_package(SDL2_gfx REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

set(INCLUDES ${INCLUDES} "${SDL2_INCLUDE_DIRS}" "${SDL2_TTF_INCLUDE_DIRS}")

if(FETCH_OBELIXLIBS)
    include(FetchContent)
    FetchContent_Declare(
            obelixlibs
            GIT_REPOSITORY git@github.com:JanDeVisser/obelixlibs.git
            GIT_TAG main
    )
    FetchContent_MakeAvailable(obelixlibs)
else()
    set(INCLUDES ${INCLUDES} ${PROJECT_SOURCE_DIR}/obelixlibs)
    add_subdirectory(${PROJECT_SOURCE_DIR}/obelixlibs)
endif()

include_directories(
        "${INCLUDES}"
        "${SDL2_INCLUDE_DIRS}"
        "${SDL2_TTF_INCLUDE_DIRS}"
)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(
        Widget
        SHARED
        Widget/Command.cpp
        Widget/Alert.cpp
        Widget/App.cpp
        Widget/Frame.cpp
        Widget/Geometry.h
        Widget/Key.cpp
        Widget/Layout.cpp
        Widget/ModalWidget.cpp
        Widget/SDLContext.cpp
        Widget/Text.cpp
        Widget/Widget.cpp
        Widget/WindowedWidget.cpp
        Widget/WidgetContainer.cpp
)

target_link_libraries(
        Widget
        oblcore
        SDL2::Main
        SDL2::GFX
        SDL2::Image
        SDL2::TTF
)

add_library(
        LSP
        SHARED
        LSP/JSON.cpp
        LSP/LSP.cpp
        LSP/Message.cpp
)

target_link_libraries(
        LSP
        oblcore
        obllexer
)

add_library(
        Scribble
        SHARED
        Scribble/Interp/CommandAdapter.cpp
        Scribble/Interp/ExpressionResult.cpp
        Scribble/Interp/Function.cpp
        Scribble/Interp/Interpreter.cpp
        Scribble/Interp/Value.cpp
        Scribble/Parser.cpp
        Scribble/Processor.cpp
        Scribble/Scribble.cpp
        Scribble/Syntax/ControlFlow.cpp
        Scribble/Syntax/Expression.cpp
        Scribble/Syntax/Function.cpp
        Scribble/Syntax/Literal.cpp
        Scribble/Syntax/Statement.cpp
        Scribble/Syntax/Syntax.cpp
        Scribble/Syntax/Variable.cpp
)

target_link_libraries(
        Scribble
        oblcore
        obllexer
)

add_library(
        Scratch
        App/ArgumentHandler.cpp
        App/Buffer.cpp
        App/CommandHandler.cpp
#        App/Console.cpp
        App/DefaultArgumentHandler.cpp
        App/Document.cpp
        App/EditAction.cpp
        App/Editor.cpp
        App/EditorState.cpp
        App/Gutter.cpp
        App/Palette.h
        App/Scratch.cpp
        App/StatusBar.cpp
#        Parser/CPlusPlus.cpp
#        Parser/PlainText.cpp
#        Parser/ScratchParser.cpp
#        Parser/Scribble.cpp
        Mode/Mode.cpp Mode/Mode.h Mode/PlainText.cpp Mode/PlainText.h Mode/CPlusPlus.cpp Mode/CPlusPlus.h)

add_executable(
        scratch
        App/main.cpp
)

target_link_libraries(
        scratch
        Scratch
        Scribble
        Widget
        oblcore
        obllexer
)

target_compile_features(scratch PUBLIC cxx_std_20)

enable_testing()
include(GoogleTest)

add_executable(
        ScribbleTest
        Test/ScribbleTest.cpp
)

target_link_libraries(
        ScribbleTest
        Scratch
        Scribble
        Widget
        gtest_main
)

add_test(NAME ScribbleTest COMMAND ScribbleTest)
gtest_discover_tests(ScribbleTest)

add_executable(
        LSPTest
        Test/JSONTest.cpp
        Test/LSPTest.cpp
)

target_link_libraries(
        LSPTest
        LSP
        gtest_main
)

add_test(NAME LSPTest COMMAND LSPTest)
gtest_discover_tests(LSPTest)

install(TARGETS scratch # ScribbleTest
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
)
