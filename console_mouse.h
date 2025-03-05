#ifndef CONSOLE_MOUSE_H
#define CONSOLE_MOUSE_H

#include <windows.h>
#include <stdio.h>

/**
 * Estrutura que representa um botão na interface do console.
 * 
 * @param x Posição X do botão.
 * @param y Posição Y do botão.
 * @param width Largura do botão.
 * @param height Altura do botão.
 * @param text Texto exibido no botão.
 * @param onClick Ponteiro da função a ser chamada quando o botão é clicado.
 * @param color Caractere ANSI de escape definido por "\x1b[{Foreground color};{Background color};"
 * 
 * ```plaintext
 * |------------------------------------------------------------|
 * | Color      | Foreground Color      | Background Color      |
 * |------------|-----------------------|-----------------------|
 * | Black      | 30                    | 40                    |
 * | Red        | 31                    | 41                    |
 * | Green      | 32                    | 42                    |
 * | Yellow     | 33                    | 43                    |
 * | Blue       | 34                    | 44                    |
 * | Magenta    | 35                    | 45                    |
 * | Cyan       | 36                    | 46                    |
 * | White      | 37                    | 47                    |
 * | Default    | 39                    | 49                    |
 * |------------------------------------------------------------|
 * ```
 */
typedef struct Button Button;

struct Button {
    int x, y, width, height;
    char text[50];
    char color[16];
    void (*onClcik)(Button *);
};

void enableAnsiEscapeCodes();
void renderButton(Button button);
/**
 * Returna 1 para verdadeiro e zero para falso.
 */
int hasButtonClicked(Button button, MOUSE_EVENT_RECORD mouseEvent);

/**
 * Limpa a tela totalmente.
 * Diferente de um clear comum, esse clear posiciona o cursor na posição 0, 0 (Topo definitivo da tela) e sobrescreve cada caractere para um espaço em branco.
 */
void clearScreenTotally();

void handleButtonClickEvent(Button *buttons[], int lenght, MOUSE_EVENT_RECORD mouseEvent);

#endif