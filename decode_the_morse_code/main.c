#include <stdlib.h>
#include <string.h>
#include <stdio.h>

const char *const morse[55] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", ".-.-.-", "--..--", "..--..", ".----.", "-.-.--", "-..-.", "-.--.", "-.--.-", ".-...", "---...", "-.-.-.", "-...-", ".-.-.", "-....-", "..--.-", ".-..-.", "...-..-", ".--.-.", "...---..."};  
const char *const ascii[55] = {"A",  "B",    "C",    "D",   "E", "F",    "G",   "H",    "I",  "J",    "K",   "L",    "M",  "N",  "O",   "P",    "Q",    "R",   "S",   "T", "U",   "V",    "W",   "X",    "Y",    "Z",    "0",     "1",     "2",     "3",     "4",     "5",     "6",     "7",     "8",     "9",     ".",      ",",      "?",      "'",      "!",      "/",     "(",     ")",      "&",     ":",      ";",      "=",     "+",     "-",      "_",      "\"",     "$",       "@",      "SOS"};

int find_code_index(const char* code);
char *decode_morse(const char* morse_code);
void trim_and_resize(char** buffer_ptr);

int main() {
    char* morse_code = ".";
    char* decoded = decode_morse(morse_code);
    if (strcmp(decoded, "") == 0) { 
        free(decoded);
        return 0;
    }
    printf("%s\n", decoded);  // should print "E"

    free(decoded);
    return 0;
}

char *decode_morse(const char* morse_code) {
    //max code len in morse is 9 so 9 + null terminator = 10
    char code[10] = "";
  
    // estimate length of translated morse code
    size_t buffer_len = strlen(morse_code) + 1;
    char* str_buffer = malloc(buffer_len);
    if (!str_buffer) return NULL;
    str_buffer[0] = '\0';
  
    size_t code_pos = 0;
    size_t space_count = 0;
    
    for (size_t i = 0; morse_code[i] != '\0'; i++) {
        if (morse_code[i] == '.' || morse_code[i] == '-') {
            code[code_pos] = morse_code[i];
            code_pos++;
            code[code_pos] = '\0';
          
            space_count = 0;
        } else if (morse_code[i] == ' ') {
            space_count++;
          
            if (space_count == 1 && code_pos > 0) {
                int code_index = find_code_index(code);
                if (code_index == -1) {
                    free(str_buffer);
                    return NULL;
                }
                strncat(str_buffer, ascii[code_index], buffer_len - strlen(str_buffer) - 1);
                code_pos = 0;
            }
          
            if (space_count == 3) {
                strncat(str_buffer, " ", buffer_len - strlen(str_buffer) - 1);
                space_count = 0;
            }
        }
    }
  
    if (code_pos > 0) {
        int code_index = find_code_index(code);
        if (code_index == -1) {
            free(str_buffer);
            return NULL;
        }
        strncat(str_buffer, ascii[code_index], buffer_len - strlen(str_buffer) - 1);       
    }
  
    trim_and_resize(&str_buffer);
    return str_buffer;
}

void trim_and_resize(char** buffer_ptr) {
    char* str_buffer = *buffer_ptr;

    // Trim leading spaces
    char* start = str_buffer;
    while (*start == ' ') {
        start++;
    }

    // Trim trailing spaces
    char* end = start + strlen(start) - 1;
    while (end > start && *end == ' ') {
        *end = '\0';
        end--;
    }

    // Move trimmed string to start of buffer if needed
    if (start != str_buffer) {
        memmove(str_buffer, start, strlen(start) + 1);
    }

    // Resize buffer
    size_t new_len = strlen(str_buffer) + 1;
    char* resized = realloc(str_buffer, new_len);
    if (resized != NULL) {
        *buffer_ptr = resized;
    }
}

int find_code_index(const char* code) {
    for (size_t i = 0; i < 55; i++) {
        if (strcmp(code, morse[i]) == 0) {
            return i;
        }
    }
    return -1;
}