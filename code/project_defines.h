#ifndef PROJECT_DEFINES_H
#define PROJECT_DEFINES_H

#ifndef ARRAY_SIZE
#	define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))
#endif

#define DEFAULT_CONFIG_FILE "resources/retro-os.conf"
#define FILES_SUBDIR        "files"

#define CFG_TERMINAL_CHAR_PRINT_DELAY_MSEC "terminal_character_print_delay_msec"
#define CFG_TERMINAL_FONT                  "terminal_font"
#define CFG_TERMINAL_FONT_SIZE             "terminal_font_size"

#endif /* PROJECT_DEFINES_H */
