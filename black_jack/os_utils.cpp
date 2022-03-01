// os_utils.cpp
// This file contains the implementation for OS specific functions

# include <iostream>
# include "os_utils.h"

// Windows systems
# ifdef _WIN32
# include <Windows.h>

namespace os_utils {
    void clrscr() {
        HANDLE                     hStdOut;
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        DWORD                      count;
        DWORD                      cellCount;
        COORD                      homeCoords = { 0, 0 };

        hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hStdOut == INVALID_HANDLE_VALUE) return;

        /* Get the number of cells in the current buffer */
        if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
        cellCount = csbi.dwSize.X * csbi.dwSize.Y;

        /* Fill the entire buffer with spaces */
        if (!FillConsoleOutputCharacter(
            hStdOut,
            (TCHAR)' ',
            cellCount,
            homeCoords,
            &count
        )) return;

        /* Fill the entire buffer with the current colors and attributes */
        if (!FillConsoleOutputAttribute(
            hStdOut,
            csbi.wAttributes,
            cellCount,
            homeCoords,
            &count
        )) return;

        /* Move the cursor home */
        SetConsoleCursorPosition(hStdOut, homeCoords);
    }
}

# endif

// Unix systems
# ifdef __unix__

# include <unistd.h>
# include <term.h>

namespace os_utils {
    void clrscr() {
        if (!cur_term) {
            int result;
            setupterm(NULL, STDOUT_FILENO, &result);
            if (result <= 0) return;
        }

        putp(tigetstr("clear"));
    }
}

# endif