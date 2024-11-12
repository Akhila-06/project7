#include "console.h"

#define VGA_BUFFER ((char*)0xb8000)
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define TAB_WIDTH 8

// Static variables for terminal colors
static VGA_Color terminal_font_color = GRAY;
static VGA_Color terminal_background_color = BLACK;

void clear_terminal() {
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        VGA_BUFFER[i * 2] = ' ';      
        VGA_BUFFER[i * 2 + 1] = (terminal_background_color << 4) | terminal_font_color;
    }
}

void set_terminal_font_color(VGA_Color color) {
    terminal_font_color = color;
}

void set_terminal_background_color(VGA_Color color) {
    terminal_background_color = color;
}

void print_character_with_color(char character, VGA_Color color) {
    static int cursor_position = 0;

    if (character == '\n') {
        cursor_position += VGA_WIDTH - (cursor_position % VGA_WIDTH);
    } else {
        if (cursor_position < VGA_WIDTH * VGA_HEIGHT) {
            VGA_BUFFER[cursor_position * 2] = character;
            VGA_BUFFER[cursor_position * 2 + 1] = (terminal_background_color << 4) | color;
            cursor_position++;
        }
    }

    if (cursor_position >= VGA_WIDTH * VGA_HEIGHT) {
        cursor_position = 0;
    }
}

void print_string_with_color(char* str, VGA_Color color) {
    while (*str) {
        print_character_with_color(*str++, color);
    }
}

void print_line_with_color(char* str, VGA_Color color) {
    print_string_with_color(str, color);
    print_character_with_color('\n', color);
}


void print_character(char character) {
    print_character_with_color(character, terminal_font_color);
}

void print_string(char* str) {
    print_string_with_color(str, terminal_font_color);
}

void print_line(char* str) {
    print_line_with_color(str, terminal_font_color);
   
}
