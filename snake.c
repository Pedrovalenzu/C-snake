#include <ncurses.h>
#include <unistd.h>  // Para usleep()
#include <stdlib.h> 
#include <time.h>    

typedef struct { //Necesito un struct para saber la posición de cada componente de la serpiente
    int x;
    int y;
}Posicion;


int aleatorio(int min, int max){
    //Debería comprobar que no hay una cola por ahí!!
    return min + rand() % (max-min +1);
}

bool colfruta(int posy, int posx, Posicion fruta){
    return abs(fruta.x - posx) <= 1 && fruta.y == posy;
}

int main(){
    int ch;
    int max_y, max_x;

    Posicion s[50];
    Posicion fruta; 
    int longitud = 2; //Longitud actual de la serpiente

    int gameover = false;
    initscr(); // Inicia la terminal en modo curses
    cbreak(); //cada carácter se lee inmediatamente (menos el ctrl+ c)
    noecho(); // No me muestra por pantalla lo que pulso
    keypad(stdscr,true); //Activa las flechas y las teclas f1,f2...etc
    nodelay(stdscr,true); //Para que el juego no se detenga esperando a que pulse una tecla. (Si no pulso nada getch devuelve ERR)
    curs_set(0); //Para que no se vea el cursor
    getmaxyx(stdscr, max_y, max_x);//Obtiene el alto y ancho de la pantalla

    //#######Juego########
    
    int pos_y = max_y/2;
    int pos_x = max_x/2;
    s[0].x = pos_x;  s[0].y = pos_y; // Cabeza
    s[1].x = pos_x-1; s[1].y = pos_y; //Primera cola
    fruta.x = aleatorio(0,max_x-1)*2; fruta.y = aleatorio(0,max_y-1); //Obtiene la posicion de la fruta

    int dir_x =1;
    int dir_y =0;

    mvprintw(pos_y,pos_x,"*");
    mvprintw(pos_y,pos_x-1,"*");
    mvprintw(fruta.y,fruta.x,"@");
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
        int p_antx = pos_x;
        int p_anty = pos_y;
        pos_x += dir_x * 2; // Multiplico por 2 porque el tamaño de la pantalla no es cuadrado. Movimiento horizontal debe ser igual de rapido que el vertical
        pos_y += dir_y;
        mvprintw(pos_y,pos_x,"*");
        s[0].y = pos_y; s[0].x = pos_x;
        
        for(int i = 1; i<longitud; i++){
            mvprintw(p_anty,p_antx,"*");
            int auxx = p_antx; int auxy = p_anty;
            p_anty = s[i].y;
            p_antx = s[i].x;
            s[i].y= auxy; s[i].x = auxx;
            
        }
        
        //Comprueba si consigue una fruta
        if(colfruta(s[0].y,s[0].x, fruta)){
            longitud++;
            mvprintw(p_anty,p_antx,"*");
            s[longitud-1].y = p_anty;
            s[longitud-1].x = p_antx;
            
            //Debe hacer aparecer otra fruta
            fruta.x = fruta.x = aleatorio(0,max_x-1); fruta.y = aleatorio(0,max_y-1);
            

        }
        
        mvaddch(fruta.y, fruta.x, '@');
        refresh();
        clear();
        usleep(100000); //Se detiene 0,1 segundos
    }
    endwin();
}