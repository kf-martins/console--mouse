#include <stdio.h>
#include <windows.h>
#include "console_mouse.h"

// Função para esconder o cursor
void hideCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    // Obtém informações sobre o cursor atual
    GetConsoleCursorInfo(hConsole, &cursorInfo);

    // Define a visibilidade como 0 (invisível)
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}
// Função para mostrar o cursor
void showCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    // Obtém informações sobre o cursor atual
    GetConsoleCursorInfo(hConsole, &cursorInfo);

    // Define a visibilidade como 1 (visível)
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void onButtonClick(Button *button) {    
    printf("\x1b[0;0H");
    printf("\x1b[32mBotão \"%s\" clicado!\x1b[0m\n", button->text);
}

int main() {
    hideCursor();
    enableAnsiEscapeCodes();

    SetConsoleOutputCP(CP_UTF8);

    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD inputRecord;
    DWORD eventsRead;

    Button button1 = {2, 2, 7, 3, "BOTÃO", "\x1b[30;42m", onButtonClick};
    Button button2 = {2, 6, 16, 3, "APERTE", "\x1b[30;42m", onButtonClick};
    Button button3 = {2, 10, 17, 3, "APERTE", "\x1b[30;42m", onButtonClick};
    Button button4 = {2, 14, 17, 3, "APERTE", "\x1b[30;42m", onButtonClick};

    Button *buttons[] = {&button1, &button2, &button3, &button4};
    
    clearScreenTotally();
    while (1) {
        hideCursor();
        ReadConsoleInput(hInput, &inputRecord, 1, &eventsRead);
        
        renderButton(button1);
        renderButton(button2);
        renderButton(button3);
        renderButton(button4);

        if (inputRecord.EventType == MOUSE_EVENT) {
            MOUSE_EVENT_RECORD mouseEvent = inputRecord.Event.MouseEvent;

            printf("\x1B[1;90H\x1B[2K X: %d, Y: %d\n", mouseEvent.dwMousePosition.X, mouseEvent.dwMousePosition.Y);

            handleEvent(buttons, 4);

            // if (hasButtonClicked(button1, mouseEvent)) {
            //     // printf("\x1B[6;1H\x1b[2K");
            //     button1.onClick(button1);
            // } else {
            //     printf("\x1B[6;1H\x1b[2K");
            // }
        }

        if (inputRecord.EventType == KEY_EVENT && inputRecord.Event.KeyEvent.bKeyDown && inputRecord.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE) {
            break;
        }
    }

    showCursor();
    return 0;
}
