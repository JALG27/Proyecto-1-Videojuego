#include <stdio.h>    //libreria que contiene las definiciones de las macros, las constantes, las declaraciones de funciones de la biblioteca estándar
#include <windows.h>  //permite ingresar al teclado las funciones en general de movimiento
#include <conio.h>  //libreria que sirve para darle movimiento a un punto a traves de la consola
#include <stdlib.h> //libreria que sirve para darle color a la consola
#include <list>  //libreria que sirve para declarar funciones y generar punto de origen de un caracter
using namespace std; //darle validacion a las funciones de std

#define ARRIBA 72  //Permite el ingreso del teclado para poder mover un punto
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80

void gotoxy(int x, int y) {           //la funcion de retorno con gotoxy permite permite mover el punto en la ventana segun las coordenadas x e y
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;

    SetConsoleCursorPosition(hCon, dwPos);
}

void OcultarCursor(){             //la funcion de retorno de Ocultar cursor se realiza para ocultar el cursor al momento de compilar el programa
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cco;
    cco.dwSize = 2;
    cco.bVisible = FALSE;

    SetConsoleCursorInfo(hCon,&cco);

}

 void pintar_limites(){     // la funcion de retorno de pintar limites se utiliza para poder pintar los bordes con un for declarando la funcion int con la altura y anchura del borde y el icono 177 con los iconos ascii
	for(int i = 2 ; i<78 ; i++){
		gotoxy(i,3); printf("%c",177);
		gotoxy(i,33);printf("%c",177);
	}
	
	for(int i = 4 ; i<33 ; i++){
		gotoxy(2,i); printf("%c",177);
		gotoxy(77,i); printf("%c",177);
}

gotoxy(2,3); printf("%c",177); //esquinas del marco
gotoxy(2,33);printf("%c",177);
gotoxy(77,3);printf("%c",177);
gotoxy(77,33);printf("%c",177);
}

class NAVE{       //en la clase nave se declaran las variables de coordenadas, corazones y vidas
    int x,y;
    int corazones;
    int vidas;
    public:    //se hace llamado a las funciones
        NAVE(int _x, int _y, int _corazones, int _vidas): x(_x),y(_y),corazones(_corazones),vidas(_vidas){}
        int X() { return x;	}
        int Y() { return y;	}
        int VID() { return vidas; }
        void COR() { corazones--; }
        void pintar();
        void borrar();
        void mover();
        void pintar_corazones();
        void explosion();

};

void NAVE::pintar(){   //diseño de la nave con codigos ascii
    gotoxy(x,y);  printf("  %c",30);
    gotoxy(x,y+1);printf(" %c%c%c",193,219,193);
    gotoxy(x,y+2);printf("%c%c %c%c",174,254,254,175);
}

void NAVE::borrar(){  //espacio que se genera para el diseño de la nave
    gotoxy(x,y); printf("     ");
    gotoxy(x,y+1); printf("     ");
    gotoxy(x,y+2); printf("     ");

}

void NAVE::mover(){    //se usa la funcion khbit para declarar variable de tipo char y getch para poder obtener acceso al teclado a traves de los siguientes numeros
        if(kbhit()){
            char tecla = getch();
            borrar();
            if(tecla == IZQUIERDA) x--;
            if(tecla == DERECHA) x++;
            if(tecla == ARRIBA) y--;
            if(tecla == ABAJO) y++;
            if(tecla == 'e')corazones--;
            pintar();
            pintar_corazones();

        }
}

void NAVE::pintar_corazones(){   // se busca generar las palabras de vida y salud cuando se compila el programa por medio de gotoxy y un for
	gotoxy(50,2); printf("Vidas %d",vidas);
	gotoxy(64,2); printf("Salud");
	gotoxy(70,2); printf("      ");
	for (int i =0 ; i< corazones; i++){
		gotoxy(70+i,2); printf("%c",3);
	}
}

void NAVE::explosion(){  // se genera la animacion de colision de meteoritos con la nave a traves de un if y gotoxy con un sleep para establecer el tiempo en que se genera la animacion
	if(corazones == 0){
		borrar();
		gotoxy(x,y); printf("        ");
		gotoxy(x,y+1); printf("  GAME  ");
		gotoxy(x,y+2); printf("  OVER  ");
		Sleep(500);
		
		borrar();
		gotoxy(x,y); printf(" / OO /");
		gotoxy(x,y+1); printf("  FFFF  ");
		gotoxy(x,y+2); printf(" / OO /");
		Sleep(500);
		borrar();
		vidas--;
		corazones = 3;
		pintar_corazones();
		pintar();
	}
}

class NAV{ //se declara variable de tipo caracter para poder pintar y darle movimiento al programa por medio deu n if
	int x,y;
	public:
		NAV(int _x, int _y):x(_x),y(_y){}
		void pintar();
		void mover();
		void choque( NAVE &N);
		int X() { return x;}
		int Y() { return y;}
};

void NAV::pintar(){  
	gotoxy(x,y);printf("%c",219);
}

void NAV::mover(){
	gotoxy(x,y); printf(" ");
	y++;
	if(y> 32){
		x = rand()%71 + 4;
		y = 4;
	}
	pintar();
}

void NAV::choque( NAVE &N){  // se declara la funcion de choque para borrar y pintar cuando exista una colision X define al asterioide y N a la nave
	if( x >=N.X() && x <N.X()+6 && y >= N.Y() && y <= N.Y() +2)
	{
		N.COR();
		N.borrar();
		N.pintar();
		N.pintar_corazones();
		x = rand()%71 + 4;
		y = 4;
	}
}

class BALA{  //se declara el diseño y funciones de la bala 
	int x,y;
	public:
		BALA(int _x, int _y): x(_x),y(_y){}
		int X(){ return x; }
		int Y(){ return y; }
		void mover();
		bool fuera();
};

void BALA::mover(){ // se genera el movimiento y diseño de la bala
	gotoxy (x,y); printf(" ");
	y--;
	gotoxy(x,y); printf("*");
}

bool BALA::fuera(){ // una funcion de tipo bool  para poder llamar la clase nave
	if(y== 4) return true;
	return false;
}


int main() {  // se declaran las opciones parap oder utilizar la aplicacion a traves de listas y un iterador y declarar en una clase
	system("color 0A");
    OcultarCursor();
    pintar_limites();
    NAVE N(37,30,3,3);
    N.pintar();
    N.pintar_corazones();
    
    list<NAV*> A;
    list<NAV*>::iterator itA;
    for(int i=0; i<5; i++){ 
    	A.push_back(new NAV(rand()%75 + 3, rand()%5 + 4));
	}
	
	list<BALA*> B;  // se da la funcion de la bala
	list<BALA*>::iterator it;


    bool game_over = false;
    int puntos = 0;
    while(!game_over){
    	
    	gotoxy(4,2); printf("Puntos %d", puntos);
    	if(kbhit())
    	{
    		char tecla = getch();
    			if (tecla == 'z')
    			B.push_back(new BALA(N.X() +2 , N.Y() - 1));   // las funciones que permiten que la bala pueda chocar con un asteroide
		}
		
		for(it = B.begin(); it !=B.end(); it ++)
		{
			(*it)->mover();
			if((*it)->fuera()){
				gotoxy((*it)->X(), (*it)->Y()); printf(" ");
				delete(*it);
				it = B.erase(it);
			}
		}
		for(itA = A.begin(); itA != A.end(); itA++){
			(*itA)->mover();
			(*itA)->choque(N);
		}
		
		for(itA = A.begin(); itA != A.end(); itA++){
			for(it = B.begin(); it != B.end(); it++){
				if((*itA)->X() == (*it)->X() && ( (*itA)->Y() +1 == (*it)->Y() || (*itA)->Y() == (*it)->Y() ))
			{
			gotoxy((*it)->X(),(*it)->Y());printf(" ");
			delete(*it);
			it = B.erase(it);
			
			A.push_back(new NAV(rand()%74 + 3, 4));
			gotoxy((*itA)->X(),(*itA)->Y());printf(" ");
			delete(*itA);
			itA = A.erase(itA);
			
			puntos+=5;
		}
	}
}
		
		if(N.VID() == 0) game_over = true;
		N.explosion();
		N.mover();
        Sleep(50);

    }



    return 0;
}
