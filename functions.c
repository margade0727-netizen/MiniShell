#include "header.h"

typedef struct {
    int code;
    const char *message;
} error_entry;

static const error_entry error_table[] = {
    {1, "Current working directory could not be read. // Одоогийн directory уншигдахгүй байна."},
    {2, "A required command argument is missing or invalid. // Комманд ажиллахад шаардлагатай argument алга эсвэл алдаатай."},
    {3, "Windows user name could not be read. // Windows хэрэглэгчийн нэр уншигдсангүй."},
    {4, "Directory change failed. // Directory солигдсонгүй."},
    {5, "List search path is too long. // List хайлтын зам хэтэрхий урт байна. "},
    {6, "The requested file or directory already exists. // Ийм нэртэй file юм уу directory байна."},
    {7, "The file could not be created. // Файл үүсгэж чадсангүй."},
    {8, "Rename arguments are invalid. // Argument асуудалтай байна."},
    {9, "Rename failed. // Нэр солигдсонгүй"},
    {10, "not allowed for this delete command. // устдаггүй ээ..."},
    {11, "File deletion failed. // устдаггүй ээ."},
    {12, "The directory is not empty. // Directory хоосон биш байна."},
    {13, "Access was denied. // Зөвшөөрөл байхгүй."},
    {14, "The requested path does not exist. // Ийм path байдаггүй ээ xD."},
    {15, "Directory deletion failed. // Directory устаагүй."},
    {16, "Move syntax must be source|destination. // source|destination хэлбэртэйгээр бичээд үзээрэй."},
    {17, "Move source was not found. // source нь байдаггүй ээ."},
    {18, "Move destination already exists. // Ийм destination аль хэдийн байна."},
    {19, "The file is in use by another process. // Энэ файлыг өөр процесс хэрэглэж байна."},
    {20, "Move failed. // Зөөгдсөнгүй ээ."},
    {21, "The path is too long. // Пүү ийм урт path бас байдаг аа!!! Арай богино path ашиглаад үзээрэй."},
    {22, "The path refers to a directory, not a file. // Энэ чинь файл биш directory байна шдэ!!!"},
    {23, "The file could not be opened. // Файл нээгддэггүй ээ!"},
    {24, "The file could not be read. // Файл уншигддаггүй ээ"},
    {25, "File output was truncated because it exceeds the shell buffer. // Файл чинь хэтэрхий урт байсан болохоор таслаад орууллаа шүү!!!"},
    {26, "The command is not recognized. // Ийм команд байхгүй!"},
    {27, "The command argument is too long. // Хэтэрхий урт argument авчихжээ... Богино болгоод туршаад үздээ."},
    {28, "No supported CLI editor was found. // Тохирох  CLI editor алгоо."},
    {29, "The editor command line is toooooooooooo long. // Editor-н коммандын мөр арай л дэндүү урт байнаа"},
    {30, "The editor could not be started. // Editor ажилдаггүй ээ..."},
    {31, "IDK"}
};

static const char *error_message(int code) {
    for (size_t i = 0; i < sizeof(error_table) / sizeof(error_table[0]); ++i) {
        if (error_table[i].code == code) return error_table[i].message;
    }
    return "Unknown MiniShell error.";
}

static void print_error(int code) {
    printf("Error %03d: %s\n", code, error_message(code));
}

char *whereami(char *buf, size_t bufsize){ //whereami
    if (_getcwd(buf, bufsize) == NULL) { //_getcwd == get Current Working Directory
        print_error(1);
        return NULL;
    }
    return buf;
}

char *whoami(char *buf, size_t bufsize){ //whomai
    DWORD size = (DWORD)bufsize;
    if (GetUserNameA(buf, &size) == 0) {
        print_error(3);
        return NULL;
    }
    return buf;
}
char *echo(char *buf, size_t bufsize){ //echo
    if (buf == NULL || bufsize == 0) {
        return NULL;
    }
    return buf;
}
char *help(char *buf, size_t bufsize){
    const char *text =
        "Commands: whereami, whoami, echo, cd, list (ls), create (crt), "
        "rename (rnm), del (rem), deldir (rmdir), move (mv), "
        "open (op), open2 (op2), write, help-error <code>, exit, quit\n"
        "whereami   Show the current directory // Одоо ажиллаж буй Directory.\n"
        "whoami     Show the current Windows user. // Одоо хэрэглэж буй хэрэглэгч\n"
        "echo       Print text. // Текст хэвлэх\n"
        "help       Show command help. // Коммандын тайлбар\n"
        "help-error Explain an error code. // Алдааны кодны тайлбар харах.\n"
        "cd         Change the current directory. // directory солих\n"
        "list       List files and folders. // Одоо ашиглаж буй directory дахь файл болон фолдеруудыг харуулна.\n"
        "ls         Alias for list. // list товчлосон.\n"
        "create     Create a new empty .txt file. // Өргөтгөл өгөөгүй бол .txt file үүсгэнэ.\n"
        "crt        Alias for create. // Create товчлосон.\n"
        "rename     Rename a file or folder. // Фолдер юм уу файл нэр солих.\n"
        "rnm        Alias for rename. // Rename товчлосон.\n"
        "del        Delete a file. // файл устгана.\n"
        "rem        Alias for del. // файл устгана.\n"
        "deldir     Delete an empty directory. // Хоосон directory устгана.\n"
        "rmdir      Alias for deldir. // deldir товчлосон.\n"
        "rename   Rename a file or folder: old|new. // old|new хэлбэрээр бичнэ. Файл/фолдер нэр солих.\n"
        "mv         Alias for move. // move товчлосон.\n"
        "open       Read a text file into the output buffer. // text хэлбэрээр нээнэ.\n"
        "op         Alias for open. // open товчлосон.\n"
        "open2      Open a file in a CLI editor. // CLI editor ашиглаж text нээнэ.\n"
        "op2        Alias for open2. // open2 товчлосон.\n"
        "write      Write text into an existing file line-by-line. Type ':wq' to save. // Мөр мөрөөр текст бичээд ':wq' гэж бичээд хадгална.";

    if (buf == NULL || bufsize == 0 || strlen(text) >= bufsize) {
        return NULL;
    }
    strcpy(buf, text);
    return buf;
}
char *help_error(char *buf, size_t bufsize){
    char *end;
    long code;
    if (buf == NULL || bufsize == 0 || buf[0] == '\0') {
        size_t used = 0;
        for (size_t i = 0; i < sizeof(error_table) / sizeof(error_table[0]); ++i) {
            int written = snprintf(buf + used, bufsize - used, "%03d: %s\n",
                error_table[i].code, error_table[i].message);
            if (written < 0 || (size_t)written >= bufsize - used) return NULL;
            used += (size_t)written;
        }
        return buf;
    }
    code = strtol(buf, &end, 10);
    if (*end != '\0' || code < 1 || code > 999 || error_message((int)code)[0] == 'U') {
        print_error(31);
        return NULL;
    }
    int written = snprintf(buf, bufsize, "%03ld: %s", code, error_message((int)code));
    return (written < 0 || (size_t)written >= bufsize) ? NULL : buf;
}
char *cd(char *buf, size_t bufsize){
    if (buf == NULL || bufsize == 0 || buf[0] == '\0') {
        print_error(2);
        return NULL;
    }
    if (_chdir(buf) != 0) {
        print_error(4);
        return NULL;
    }
    if (_getcwd(buf, bufsize) == NULL) {
        print_error(1);
        return NULL;
    }
    return buf;
}
#include <stdio.h>
#include <string.h>
#include <io.h>       // For _findfirst, _findnext, _findclose
#include <direct.h>   // For _getcwd

char *list(char *buf, size_t bufsize) {
    if (buf == NULL || bufsize == 0) return NULL;

    char current_directory[MINISHELL_PATH_MAX];
    if (_getcwd(current_directory, sizeof(current_directory)) == NULL) {
        return NULL;
    }

    char pattern[MINISHELL_PATH_MAX];
    snprintf(pattern, sizeof(pattern), "%s\\*", current_directory);

    buf[0] = '\0';

    struct _finddata_t file_info;
    intptr_t handle = _findfirst(pattern, &file_info);

    if (handle == -1) {
        return buf; 
    }

    do {
        const char *name = file_info.name;

        if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0) {
            continue;
        }

        const char *kind = (file_info.attrib & _A_SUBDIR) ? "[DIR] " : "[FILE] ";

        size_t used = strlen(buf);
        if (used >= bufsize - 1) break; // Buffer full

        snprintf(buf + used, bufsize - used, "%s%s\r\n", kind, name);

    } while (_findnext(handle, &file_info) == 0);

    _findclose(handle);
    return buf;
}

char *ls(char *buf, size_t bufsize){ // ls alias
    return list(buf, bufsize);
}

char *create(char *buf, size_t bufsize){
    if (buf == NULL || bufsize == 0 || buf[0] == '\0') {
        print_error(2);
        return NULL;
    }

    size_t length = strlen(buf);
    char *filename = buf + length;
    while (filename > buf && filename[-1] != '\\' && filename[-1] != '/') {
        --filename;
    }

    if (strchr(filename, '.') == NULL) { //strchr -- string search (file name-d . oroogui buyu extension bhgu bol auto
        //-aar .txt extension avnadaah hu)
        if (length + 4 >= bufsize) {
            print_error(21);
            return NULL;
        }
        memcpy(buf + length, ".txt", 5);
    }

    if (GetFileAttributesA(buf) != INVALID_FILE_ATTRIBUTES) {
        print_error(6);
        return NULL;
    }

    FILE *file = fopen(buf, "wb");
    if (file == NULL) {
        print_error(7);
        return NULL;
    }

    fclose(file);
    return buf;
}
char *crt(char *buf, size_t bufsize){ //create alias --
    return create(buf,bufsize);
}
char *rename(char *buf, size_t bufsize){ //rename func 
    if (buf == NULL || bufsize == 0 || buf[0] == '\0') {
        print_error(8);
        return NULL;
    }

    char *sep = strchr(buf, '|');
    if (sep == NULL || sep == buf || *(sep + 1) == '\0') {
        print_error(8);
        return NULL;
    }

    *sep = '\0';
    char *old_name = buf;
    char *new_name = sep + 1;

    if (MoveFileA(old_name, new_name) == 0) {
        print_error(9);
        *sep = '|'; // buffer-aa butsaagaad niiluulne, move()-toi ijil
        return NULL;
    }

    *sep = '|';
    return buf;
}

char *rnm(char *buf, size_t bufsize){  //rename alias
    return rename(buf,bufsize);
}

char *delete(char *buf, size_t bufsize){ //delete
    if (buf == NULL || bufsize == 0 || buf[0] == '\0') {
        print_error(2);
        return NULL;
    }

    if (strstr(buf, "..") != NULL) {
        print_error(10);
        return NULL;
    }

    if (DeleteFileA(buf) == 0) {
        print_error(11);
        return NULL;
    }

    return buf;
}

char *del(char *buf, size_t bufsize){ //delete alias
    return delete(buf, bufsize);
}

char *rem(char *buf, size_t bufsize){ //delete alias
    return delete(buf, bufsize);
}

char *deletedirective(char *buf, size_t bufsize){ //delete directory / rmdir
    if (buf == NULL || bufsize == 0 || buf[0] == '\0') {
        print_error(2);
        return NULL;
    }
    if (RemoveDirectoryA(buf) == 0) {
        DWORD err = GetLastError();
        if (err == ERROR_DIR_NOT_EMPTY) print_error(12);
        else if (err == ERROR_ACCESS_DENIED) print_error(13);
        else if (err == ERROR_FILE_NOT_FOUND || err == ERROR_PATH_NOT_FOUND) print_error(14);
        else print_error(15);
        return NULL;
    }

    return buf;
}
char *deldir(char *buf, size_t bufsize){ //Deletedirective alias
    return deletedirective(buf, bufsize);
}
char *rmdir(char *buf, size_t bufsize){ //deletedirective alias
    return deletedirective(buf, bufsize);
}

char *move(char *buf, size_t bufsize){ //move / rename "source|destination"
    if (buf == NULL || bufsize == 0 || buf[0] == '\0') {
        print_error(2);
        return NULL;
    }

    char *sep = strchr(buf, '|');
    //!comeback --- function maani neg *buf buyu inputtei bga bolhr source, destination geed 
    //2 input avah shaardlatai asuudal deer neg inputiin gold ni "|" avch salgaad 2 input bolgoj
    //ashiglsn!  zalhuu hurehgui bol ergej ired zzasnaa. !comeback !comeback !comeback !comeback !comeback !comeback
    if (sep == NULL || sep == buf || *(sep + 1) == '\0') {
        print_error(16);
        return NULL;
    }

    *sep = '\0';
    char *src = buf;
    char *dst = sep + 1;

    if (MoveFileExA(src, dst, MOVEFILE_COPY_ALLOWED) == 0) {
        DWORD err = GetLastError();
        if (err == ERROR_ACCESS_DENIED) print_error(13);
        else if (err == ERROR_FILE_NOT_FOUND) print_error(17);
        else if (err == ERROR_ALREADY_EXISTS) print_error(18);
        else if (err == ERROR_SHARING_VIOLATION) print_error(19);
        else print_error(20);
        *sep = '|'; //buffer aa butsaagaad niiluulne. !comeback
        return NULL;
    }

    *sep = '|'; //buffer aa butsaagaad niiluulne. !comeback
    return buf;
}
char *mv(char *buf, size_t bufsize){
    return move(buf, bufsize);
}
char *open(char *buf, size_t bufsize){ //open (readonly) 
    if (buf == NULL || bufsize == 0 || buf[0] == '\0') {
        print_error(2);
        return NULL;
    }
    char path[MAX_PATH];
    if (strnlen(buf, bufsize) >= sizeof(path)) {
        print_error(21);
        return NULL;
    }
    strcpy(path, buf);

    DWORD attrs = GetFileAttributesA(path);
    if (attrs == INVALID_FILE_ATTRIBUTES) {
        print_error(14);
        return NULL;
    }
    if (attrs & FILE_ATTRIBUTE_DIRECTORY) {
        print_error(22);
        return NULL;
    }

    FILE *fp = fopen(path, "rb");
    if (fp == NULL) {
        print_error(23);
        return NULL;
    }

    size_t read_count = fread(buf, 1, bufsize - 1, fp);

    if (ferror(fp)) {
        print_error(24);
        fclose(fp);
        return NULL;
    }

    if (!feof(fp)) { //warning but didnt fail. i cut the text lol!!!!
        print_error(25);
    }

    fclose(fp);
    buf[read_count] = '\0';
    return buf;
}
char *op(char *buf, size_t bufsize){
    return open(buf, bufsize);
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++=
//Text file edit hiihed editor heregtei tul tatah gej oroldsn. Enenii uchriig olohgui baisan
//dood taliin nemeh temdegtei mur hurtel AI dav, chadval daraa uuruu hiinee hah. !comeback 
//Zugeer sonirhood nemj uzsen bolno.

// Searches PATH for a known CLI editor, in preference order.
// Returns a static buffer with the found executable name, or NULL if none found.
static const char *find_cli_editor(void) {
    static const char *candidates[] = { "micro.exe", "nano.exe", "edit.exe", "vim.exe", NULL };
    static char found[MAX_PATH];

    for (int i = 0; candidates[i] != NULL; i++) {
        if (SearchPathA(NULL, candidates[i], NULL, MAX_PATH, found, NULL) != 0) {
            return found; // full resolved path
        }
    }
    return NULL;
}

char *open2(char *buf, size_t bufsize){ 
    if (buf == NULL || bufsize == 0 || buf[0] == '\0') {
        print_error(2);
        return NULL;
    }

    char work[1024];
    if (strnlen(buf, bufsize) >= sizeof(work)) {
        print_error(21);
        return NULL;
    }
    strcpy(work, buf);

    char *editor = NULL;
    char *path;
    char *sep = strchr(work, '|');
    if (sep != NULL) {
        *sep = '\0';
        editor = work;
        path = sep + 1;
    } else {
        path = work;
    }

    if (path[0] == '\0') {
        print_error(2);
        return NULL;
    }

    DWORD attrs = GetFileAttributesA(path);
    if (attrs == INVALID_FILE_ATTRIBUTES) {
        print_error(14);
        return NULL;
    }
    if (attrs & FILE_ATTRIBUTE_DIRECTORY) {
        print_error(22);
        return NULL;
    }

    const char *resolved_editor = NULL;
    char editor_search[MAX_PATH];

    if (editor != NULL && editor[0] != '\0') {
        
        if (SearchPathA(NULL, editor, ".exe", MAX_PATH, editor_search, NULL) != 0) {
            resolved_editor = editor_search;
        } else {
            print_error(28);
            return NULL;
        }
    } else {
        resolved_editor = find_cli_editor();
        if (resolved_editor == NULL) {
            // (install_cli_editor() != 0) {
            //    return NULL;
            //}
            resolved_editor = find_cli_editor();
            if (resolved_editor == NULL) {
                print_error(28);
                return NULL;
            }
        }
    }

    char cmdline[MAX_PATH * 2 + 8];
    int cmdline_length = snprintf(cmdline, sizeof(cmdline), "\"%s\" \"%s\"", resolved_editor, path);
    if (cmdline_length < 0 || (size_t)cmdline_length >= sizeof(cmdline)) {
        print_error(29);
        return NULL;
    }

    STARTUPINFOA si = {0};
    PROCESS_INFORMATION pi = {0};
    si.cb = sizeof(si);
    if (!CreateProcessA(NULL, cmdline, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        print_error(30);
        return NULL;
    }

    WaitForSingleObject(pi.hProcess, INFINITE); 
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return buf;
}
////Text file edit hiihed editor heregtei tul tatah gej oroldsn. Enenii uchriig olohgui baisan
//deed taliin nemeh temdegtei mur hurtel AI dav, chadval daraa uuruu hiinee hah. !comeback 
//Zugeer sonirhood nemj uzsen bolno.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++=
char *op2(char *buf, size_t bufsize){
    return open2(buf, bufsize);
}

char *write(char *buf, size_t bufsize) {
    if (buf == NULL || bufsize == 0 || buf[0] == '\0') {
        print_error(2);
        return NULL;
    }

    char path[MINISHELL_PATH_MAX];
    
    if (strchr(buf, '.') == NULL) {
        if (snprintf(path, sizeof(path), "%s.txt", buf) >= (int)sizeof(path)) {
            print_error(21);
            return NULL;
        }
    } else {
        if (snprintf(path, sizeof(path), "%s", buf) >= (int)sizeof(path)) {
            print_error(21);
            return NULL;
        }
    }

    DWORD attrs = GetFileAttributesA(path);
    if (attrs == INVALID_FILE_ATTRIBUTES) {
        print_error(14);
        return NULL;
    }
    if (attrs & FILE_ATTRIBUTE_DIRECTORY) {
        print_error(22);
        return NULL;
    }

    FILE *fp = fopen(path, "ab");
    if (fp == NULL) {
        print_error(23);
        return NULL;
    }

    printf("Writing to '%s'. Type ':wq' alone on a line to save and exit.\n", path);

    char line[1024];
    while (fgets(line, sizeof(line), stdin) != NULL) {
        size_t len = strlen(line);
        while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r')) {
            line[--len] = '\0';
        }

        if (strcmp(line, ":wq") == 0) {
            break; 
        }

        fprintf(fp, "%s\r\n", line);
    }

    fclose(fp);

    snprintf(buf, bufsize, "%s", path);
    return buf;
}
