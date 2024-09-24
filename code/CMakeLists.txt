project(retro-os C)

find_package(SDL2 REQUIRED)


add_executable(${PROJECT_NAME} 
    main.c
    logger.c
    terminal.c
    config.c
    result.c
    util_strings.c
    cmd_show.c
    cmd_files.c
    cmd_help.c
    screen.c
    screenbuffer.c
)


target_link_libraries(${PROJECT_NAME}
    PRIVATE
        SDL2
        SDL2_ttf
)
