#ifndef TERMINAL_H
#define TERMINAL_H


void terminal_init();
void terminal_clear();
void terminal_printheader(const char *s);
void terminal_printstr(const char *s);
void terminal_printfile(const char *filename);


#endif /* TERMINAL_H */
