find_package(Freetype)

add_executable(
        Eddy
        MACOSX_BUNDLE
        App.cpp
        Buffer.cpp
	Colour.cpp
        BufferView.cpp
        Eddy.cpp
        Editor.cpp
        FileSelector.h
        Gutter.cpp
        Layout.cpp
	LexerMode.h
        MiniBuffer.h
        Modal.h
	Mode.cpp
        StatusBar.cpp
        Theme.cpp
        Widget.cpp
        Project.cpp
)

target_include_directories(Eddy PRIVATE ${raylib_INCLUDE_DIRS} ${FREETYPE_INCLUDE_DIRS})
target_link_libraries(
        Eddy
        PRIVATE
        LibCore
#       LSPSchema
        ${raylib_LIBRARIES}
        ${FREETYPE_LIBRARIES}
        m
)

install(TARGETS Eddy
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        BUNDLE DESTINATION bundle)
