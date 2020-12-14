#ifndef CUSTOM_IO_MODULE_H
#define CUSTOM_IO_MODULE_H

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_INPUT_BUFFER_LENGTH 2048

#define PROMPT_NOTIFIER ">"
#define INFO_NOTIFIER "->"
#define ERROR_NOTIFIER "-> ERR:"

#define INPUT_STREAM stdin
#define OUTPUT_STREAM stdout
#define ERROR_STREAM stdout

int fgetsln(char *string, size_t size, FILE *stream);
char *prompt(const char *promptString);
void printErr(const char *errorString);
void clearScreen();
void toLowerString(char *str);

#define pause() system("PAUSE")

#endif