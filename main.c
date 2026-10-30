#include "BUF.h"  // A Rudimentary Text Editor
//#include "NDL.h"  // Description, Grammar, Macros
//#include "SIM.h" //networks simulation
//#include "CPL.h" //Compiler
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include <signal.h>



void term_write(const char *fmt, ...) {
    char buf[1024];
    va_list args;
    va_start(args, fmt);
    int len = vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);
    if (len > 0) {
        write(STDOUT_FILENO, buf, (size_t)len);
    }
}

// Helper that formats strings and writes them to standard output (file descriptor 1)
void unistd_printf(const char *fmt, ...) {
    char buffer[1024];
    va_list args;
    va_start(args, fmt);
    int len = vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);

    if (len > 0) {
        write(STDOUT_FILENO, buffer, (size_t)len);
    }
}

// Restore terminal state on exit
void cleanup(int signum) {
    (void)signum;
    // Show cursor, exit alternate screen, reset text attributes
    term_write("\033[?25h\033[?1049l\033[0m");
    _exit(0);
}

int main(void) {
    // 1. Clear terminal and move cursor to row 1, col 1
    unistd_printf("\033[2J\033[1;1H");

    // 2. Position at row 5, col 10: bold red text
    unistd_printf("\033[5;10H\033[1;31mNDL - Compiler and Simulator.\033[0m\n");

    // 3. Position at row 7, col 15: green text with dark blue background
    unistd_printf("\033[7;15H\033[32;44mNDL is a language used to describe and simulate networks\033[0m\n");

    // 4. Position at row 9, col 5: 24-bit TrueColor (RGB: 255, 165, 0 = Orange)
    unistd_printf("\033[9;5H\033[38;2;255;165;0mauthor: Luis F. Silva\033[255;255;0m\n");
            
    // 5. Position cursor further down for shell prompt readability
    unistd_printf("\033[12;1H");
    
    unistd_printf("\033[9;5H\033[44;12;10;10;10mTHIS IS A WARMING UP - THIS CODE IS GLP LICENSED\033[0m\n");


    // Register signal handlers for clean exit
    signal(SIGINT, cleanup);
    signal(SIGTERM, cleanup);

    // Enter alternate buffer, hide cursor, clear screen
    term_write("\033[?1049h\033[?25l\033[2J");

    const int width = 30;
    int pos = 1;
    int dir = 1;

    for (int frame = 0; frame < 200; ++frame) {
        // Move cursor to origin (avoids flicker vs clearing)
        term_write("\033[H");

        // Render header
        term_write("\033[1;36m=== Smooth POSIX Animation (Frame %03d) ===\033[0m\n\n", frame);

        // Draw track with a bouncing particle
        term_write("  [");
        for (int i = 1; i <= width; ++i) {
            if (i == pos) {
                term_write("\033[1;33m●\033[0m"); // Gold particle
            } else {
                term_write("\033[90m·\033[0m"); // Dim track path
            }
        }
        term_write("]\n\n");
        term_write("\033[90mPress Ctrl+C to exit.\033[0m\n");

        // Update physics
        pos += dir;
        if (pos >= width || pos <= 1) {
            dir = -dir;
        }

        // Frame delay: ~30 FPS (33ms)
        usleep(33000);
    }

    cleanup(0);

    return 0;
}
/*
Effect,ANSI Sequence,Description
CURSOR POSITION,\033[{row};{col}H,"Moves the cursor to the 1-based (row, col) coordinate"
CLEAR SCREEN,\033[2J,Clears the entire visible screen
RESET FORMAT,\033[0m,Clears all text styles and colors
BOLD / BRIGHT,\033[1m,Enables bold text
FOREGROUND COLOR,\033[38;2;{r};{g};{b}m or \033[31m,24-bit TrueColor or 4-bit standard red
BACKGROUND COLOR,\033[48;2;{r};{g};{b}m or \033[44m,24-bit TrueColor or 4-bit standard blue
*/