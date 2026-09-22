#include "header.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

#define BUF_SIZE 8192

static const command_t commands[] = {
    {"whereami", whereami, "Show the current directory // Одоо ажиллаж буй Directory."},
    {"whoami",   whoami,   "Show the current Windows user. // Одоо хэрэглэж буй хэрэглэгч"},
    {"echo",     echo,     "Print text. // Текст хэвлэх"},
    {"help",     help,     "Show command help. // Коммандын тайлбар"},
    {"help-error", help_error, "Explain an error code. // Алдааны кодны тайлбар харах."},
    {"cd",       cd,       "Change the current directory. // directory солих"},
    {"list",     list,     "List files and folders. // Одоо ашиглаж буй directory дахь файл болон фолдеруудыг харуулна."},
    {"ls",       ls,       "Alias for list. // list товчлосон."},
    {"create",   create,   "Create a new empty .txt file. // Өргөтгөл өгөөгүй бол .txt file үүсгэнэ."},
    {"crt",      crt,      "Alias for create. // Create товчлосон."},
    {"rename",   rename,   "Rename a file or folder: old|new. // old|new хэлбэрээр бичнэ. Файл/фолдер нэр солих."},
    {"rnm",      rnm,      "Alias for rename. // Rename товчлосон."},
    {"del",      del,      "Delete a file. // файл устгана."},
    {"rem",      rem,      "Alias for del. // файл устгана."},
    {"deldir",   deldir,   "Delete an empty directory. // Хоосон directory устгана."},
    {"rmdir",    rmdir,    "Alias for deldir. // deldir товчлосон."},
    {"move",     move,     "Move source|destination without overwriting. // Move source|destination гэж бичнэ. Файл зөөнө."},
    {"mv",       mv,       "Alias for move. // move товчлосон."},
    {"open",     open,     "Read a text file into the output buffer. // text хэлбэрээр нээнэ."},
    {"op",       op,       "Alias for open. // open товчлосон."},
    {"open2",    open2,    "Open a file in a CLI editor. // CLI editor ашиглаж text нээнэ."},
    {"op2",      op2,      "Alias for open2. // open2 товчлосон."},
    {"write",    write,    "Write text into a file line-by-line, no editor needed. Type ':wq' to save. // Мөр мөрөөр текст бичээд ':wq' гэж бичээд хадгална."},
    {NULL, NULL, NULL}
};

static void trim_newline(char *s) {
    size_t len = strlen(s);
    while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r')) {
        s[--len] = '\0';
    }
}

int main(void) {
    char line[BUF_SIZE];
    char buf[BUF_SIZE];

    SetConsoleOutputCP(CP_UTF8);

    printf("Mini CLI - type 'exit' to quit\n");

    while (1) {
        printf("> ");
        fflush(stdout);

        if (fgets(line, sizeof(line), stdin) == NULL) {
            break;
        }
        trim_newline(line);

        if (line[0] == '\0') {
            continue;
        }

        if (strcmp(line, "exit") == 0 || strcmp(line, "quit") == 0) {
            break;
        }

        char *cmd_name = line;
        while (isspace((unsigned char)*cmd_name)) cmd_name++;
        if (*cmd_name == '\0') {
            continue;
        }

        char *arg = cmd_name;
        while (*arg != '\0' && !isspace((unsigned char)*arg)) arg++;
        if (*arg != '\0') {
            *arg++ = '\0';
            while (isspace((unsigned char)*arg)) arg++;
        }

        command_fn fn = NULL;
        for (size_t i = 0; commands[i].name != NULL; i++) {
            if (strcmp(cmd_name, commands[i].name) == 0) {
                fn = commands[i].fn;
                break;
            }
        }

        if (fn == NULL) {
            printf("Error 026: Unknown command '%s'. Use help to see commands.\n", cmd_name);
            continue;
        }

        if (strlen(arg) >= sizeof(buf)) {
            printf("Error 027: Command argument is too long.\n");
            continue;
        }
        snprintf(buf, sizeof(buf), "%s", arg);

        char *result = fn(buf, sizeof(buf));
        if (result == NULL) {
            printf("Command failed.\n");
        } else if (result[0] != '\0') {
            printf("%s\n", result);
        }
    }

    return 0;
}