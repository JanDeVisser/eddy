add_library(
        Lexer
        STATIC
        BasicParser.cpp
        CustomScanner.cpp
        IdentifierScanner.cpp
        KeywordScanner.cpp
        Lexer.cpp
        NumberScanner.cpp
        QStringScanner.cpp
        Token.cpp
        Tokenizer.cpp
        WhitespaceScanner.cpp
        CommentScanner.cpp
        PlainTextParser.cpp)

target_link_libraries(
        Lexer
        Core
)

install(TARGETS Lexer
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib)

add_subdirectory(test)
