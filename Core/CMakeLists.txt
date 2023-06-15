add_library(
        Core
        STATIC
        Checked.h
        Error.cpp
        FileBuffer.cpp
        Format.h
        Logging.cpp
        Process.cpp
        Resolve.cpp
        ScopeGuard.h
        StringBuffer.cpp
        StringUtil.cpp
)

target_link_libraries(
        Core
        dl
)

install(TARGETS Core
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib)

add_subdirectory(test)
