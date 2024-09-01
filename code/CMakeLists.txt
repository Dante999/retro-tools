project(retro-os C)

add_executable(${PROJECT_NAME} 
    main.c
    terminal.c
    util_strings.c
    cmd_show.c
    cmd_files.c
    cmd_help.c
)
