#include "console_mouse.h"

void renderButton(Button button) {

    int textLength = strlen(button.text);
    int mid = (button.width - textLength) / 2 + 1;

    for (int i = 0; i < button.height * button.width; i++) {
        int row = i / button.width;
        int col = i % button.width;

        printf("\x1b[%d;%dH", button.y + row + 1, button.x + col + 1);
        printf(button.color);

        if(row == button.height/2 && col == mid ) {
            printf("%s", button.text);
            i+=textLength-2;
        } else {
            printf(" ");
        }
        
    }
    printf("\x1b[0m");
}

void enableAnsiEscapeCodes() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}

int hasButtonClicked(Button button, MOUSE_EVENT_RECORD mouseEvent) {
    if(mouseEvent.dwEventFlags == 0) {
        if(mouseEvent.dwMousePosition.X >= button.x && mouseEvent.dwMousePosition.X <= button.x+button.width-1 &&
            mouseEvent.dwMousePosition.Y >= button.y && mouseEvent.dwMousePosition.Y <= button.y+button.height-1 ) 
            return 1;
    }
    return 0;
}

void clearScreenTotally() {
    
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

void handleEvent(Button *buttons[], int length) {
    for (int i = 0; i < length; i++) {
        buttons[i]->onClick();
    }
}