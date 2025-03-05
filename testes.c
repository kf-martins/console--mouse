#include <stdio.h>
#include <windows.h>
#include "console_mouse.h"

void clearTotally() {
    
    COORD coord = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int width = 0;
    int height = 0;
    // Obtém as informações do console
    if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        // A largura é a distância entre a posição de início e a posição final da tela
         width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        // A altura é a diferença entre a linha inferior e superior da janela
         height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++)
            printf("\x1b[%d;%dH ", i+1, j+1);
    }

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    
}


int main() {
    enableAnsiEscapeCodes();

    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;

    // Habilita a captura de eventos do mouse
    GetConsoleMode(hInput, &mode);
    SetConsoleMode(hInput, mode | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);

    INPUT_RECORD inputRecord;
    DWORD eventsRead;

    // printf("\x1b[2J");
    // clearScreen();

    while (1) {
        ReadConsoleInput(hInput, &inputRecord, 1, &eventsRead);

        if (inputRecord.EventType == MOUSE_EVENT) {
            MOUSE_EVENT_RECORD mouseEvent = inputRecord.Event.MouseEvent;

            if (mouseEvent.dwEventFlags == 0) { // 0 = botão pressionado
                printf("\x1b[0;0H\x1b[2KClique detectado em X: %d, Y: %d\n",
                       mouseEvent.dwMousePosition.X,
                       mouseEvent.dwMousePosition.Y);
            }
        }
        
        // Sai do loop se a tecla ESC for pressionada
        if (inputRecord.EventType == KEY_EVENT &&
            inputRecord.Event.KeyEvent.bKeyDown &&
            inputRecord.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE) {
            break;
        }
    }

    return 0;
}
