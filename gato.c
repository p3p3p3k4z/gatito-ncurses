#include <ncurses.h>//Recordar que ya ncurses incluye stdio
#include <string.h>

#define FILA 17
#define COL 19
#define MAX_TEXT_LENGTH 50

int dibujar_gato[FILA][COL] = {
    //0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18
    {0,0,0,1,1,0,0,0,0,0, 0, 0, 0, 0, 1, 1, 0, 0, 0}, //0
    {0,0,1,0,0,1,0,0,0,0, 0, 0, 0, 1, 0, 0, 1, 0, 0}, //1
    {0,0,1,0,0,0,1,0,0,0, 0, 0, 1, 0, 0, 0, 1, 0, 0}, //2
    {0,0,1,0,0,0,0,1,1,1, 1, 0, 0, 0, 0, 0, 1, 0, 0}, //3
    {0,0,1,0,0,0,0,0,0,0, 0, 0, 0, 0, 0, 0, 1, 0, 0}, //4
    {0,1,0,0,0,0,0,0,0,0, 0, 0, 0, 0, 0, 0, 0, 1, 0}, //5
    {0,1,0,0,0,0,5,0,0,0, 0, 0, 5, 0, 0, 0, 0, 1, 0}, //6
    {0,1,0,0,0,5,5,0,0,0, 0, 5, 5, 0, 0, 0, 0, 1, 0}, //7
    {0,1,2,2,0,0,0,0,0,0, 0, 0, 0, 0, 0, 2, 2, 1, 0}, //8
    {0,1,2,2,0,0,4,0,0,4, 0, 0, 4, 0, 0, 2, 2, 1, 0}, //9
    {0,0,1,0,0,0,4,4,4,4, 4, 4, 4, 0, 0, 0, 1, 0, 0}, //10
    {0,0,0,1,0,0,0,0,0,0, 0, 0, 0, 0, 0, 1, 0, 0, 0}, //11
    {0,0,0,0,3,3,3,3,2,2, 2, 3, 3, 3, 0, 0, 0, 0, 0}, //12
    {0,0,0,1,0,0,0,2,2,2, 2, 2, 0, 0, 1, 0, 0, 0, 0}, //13
    {0,0,1,0,0,0,0,2,2,2, 2, 2, 0, 0, 0, 1, 0, 0, 0}, //14
    {0,1,0,0,0,0,0,0,2,2, 2, 0, 0, 0, 0, 0, 1, 0, 0}, //15
    {0,1,0,0,0,0,0,0,0,0, 0, 0, 0, 0, 0, 0, 0, 1, 0}  //16
};

int main(int argc, char* argv[]) {
    char input_text[MAX_TEXT_LENGTH];
    strncpy(input_text, argc > 1 ? argv[1] : "Hello World", MAX_TEXT_LENGTH); // Obtener el texto de entrada del usuario o usar "Hello World" por defecto

    initscr(); // Iniciar modo ncurses
    cbreak(); // Desactivar buffer de línea
    noecho(); // Ocultar caracteres
    curs_set(0); // Ocultar el cursor

    // Dimensiones de la ventana
    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);

    // Centrar el dibujo
    int start_x = (max_x - COL) / 2;
    int start_y = (max_y - FILA) / 2;

    // Coordenadas para el texto ingresado por el usuario
    int text_x = (max_x - COL) / 2 + 4; 
    int text_y = (max_y - FILA) / 2 - 3;          

    // Verificar si la terminal soporta colores
    if (has_colors()) {
        start_color(); // Iniciar modo color para ncurses

        // Definir pares de colores (n_color, color, fondo)
        init_pair(1, COLOR_BLACK, COLOR_WHITE);    
        init_pair(2, COLOR_MAGENTA, COLOR_WHITE);  
        init_pair(3, COLOR_BLUE, COLOR_WHITE);    

        // Establecer fondo negro en toda la pantalla
        bkgd(' ' | COLOR_PAIR(1)); 
    }

    // Imprimir el texto ingresado por el usuario en negritas
    attron(COLOR_PAIR(1) | A_BOLD); // Activar el color y negritas para el texto
    mvprintw(text_y, text_x, "%s", input_text); // Imprimir el texto en las coordenadas ajustadas
    attroff(COLOR_PAIR(1) | A_BOLD); // Desactivar el color y negritas para el texto

    // Imprimir el gato en pantalla
    for (int i = 0; i < FILA; ++i) {
        for (int j = 0; j < COL; ++j) {
            switch (dibujar_gato[i][j]) {
                case 1:
                    attron(COLOR_PAIR(1));
                    mvprintw(start_y + i, start_x + j, "W");
                    attroff(COLOR_PAIR(1));
                    break;
                case 2:
                    attron(COLOR_PAIR(2));
                    mvprintw(start_y + i, start_x + j, "0");
                    attroff(COLOR_PAIR(2));
                    break;
                case 3:
                    attron(COLOR_PAIR(3));
                    mvprintw(start_y + i, start_x + j, "W");
                    attroff(COLOR_PAIR(3));
                    break;
                case 4:
                    attron(COLOR_PAIR(1));
                    mvprintw(start_y + i, start_x + j, "u");
                    attroff(COLOR_PAIR(1));
                    break;
                case 5:
                    attron(COLOR_PAIR(1));
                    mvprintw(start_y + i, start_x + j, "T");
                    attroff(COLOR_PAIR(1));
                    break;
                default:
                    // No hacer nada si el valor es 0
                    break;
            }
        }
    }

    refresh(); // Aplicar cambios a pantalla
    getch(); 
    endwin(); // Finalizar modo ncurses

    return 0;
}
