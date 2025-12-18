#include <ncurses.h>
#include <unistd.h>  // Para usleep()


int main(){
    int ch;
    int max_y, max_x;
   
    int gameover = false;
    initscr(); // Inicia la terminal en modo curses
    cbreak(); //cada carácter se lee inmediatamente (menos el ctrl+ c)
    noecho(); // No me muestra por pantalla lo que pulso
    keypad(stdscr,true); //Activa las flechas y las teclas f1,f2...etc
    nodelay(stdscr,true); //Para que el juego no se detenga esperando a que pulse una tecla. (Si no pulso nada getch devuelve ERR)
    getmaxyx(stdscr, max_y, max_x);//Obtiene el alto y ancho de la pantalla


    //#######Juego########
    int pos_y = max_y/2;
    int pos_x = max_x/2;
    
    int dir_x =1;
    int dir_y =0;

    mvprintw(pos_y,pos_x,"*");
    refresh();

    while(!gameover){
        ch = getch();
        //MOVER A LA SERPIENTE
        switch(ch){
            case KEY_UP:
            dir_y = -1;
            dir_x = 0;
            break;

            case KEY_DOWN:
            dir_y = 1;
            dir_x = 0;
            break;

            case KEY_RIGHT:
            dir_x = 1;
            dir_y = 0;
            break;

            case KEY_LEFT:
            dir_x = -1;
            dir_y = 0;
            break;

        }

        pos_x += dir_x * 2; // Multiplico por 2 porque el tamaño de la pantalla no es cuadrado. Movimiento horizontal debe ser igual de rapido que el vertical
        pos_y += dir_y;
        
        mvprintw(pos_y,pos_x,"*");
        refresh();
        clear();
        usleep(200000); //Se detiene 0,2 segundos
    }
    endwin();
}