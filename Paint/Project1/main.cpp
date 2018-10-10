#include<stdlib.h>
#include"conio2.h"
#include<stdio.h>

#define przesuniecieY 2
#define przesuniecieX 36
#define SZEROKOSC 50
#define WYSOKOSC 20
char nazwa[255];
int x_szer;
int y_wys;
int obraz[WYSOKOSC][SZEROKOSC] = {0};
FILE *plik;
bool rysuj_ciagle=false;

struct Punkt {
	int pol_x;
	int pol_y;
}poczatek, koniec;

void rysowanie() {
	gotoxy(1, 24);
	cputs(" TRYB RYSOWANIA: ");
	if (rysuj_ciagle == true) {
		rysuj_ciagle = false;	
			cputs("Kursor");		
	}
	else {
		rysuj_ciagle = true;
		cputs("Rysuje");
	}	
}
void menu() {
	textcolor(15);
	textbackground(0);
	gotoxy(15, 1);
	cputs("MENU");
	gotoxy(1, 2);
	cputs("---------------------------------");
	gotoxy(1, 3);
	cputs(" Strzalki -> poruszanie");
	gotoxy(1, 4);
	cputs(" Esc -> wyjscie z aplikacji");
	gotoxy(1, 5);
	cputs("---------------------------------");
	gotoxy(1, 6);
	cputs(" Klawisze 1-0 i q-r");
	gotoxy(1, 7);
	cputs(" Przelaczaja kolory");
	gotoxy(1, 8);
	cputs("---------------------------------");
	gotoxy(1, 9);
	cputs(" n -> otwiera nowy plik");
	gotoxy(1, 10);
	cputs(" o -> otwiera wpisany plik");
	gotoxy(1, 11);
	cputs(" i -> otwiera domyslny obrazek");
	gotoxy(1, 12);
	cputs(" s -> zapisuje plik");
	gotoxy(1, 13);
	cputs("---------------------------------");
	gotoxy(1, 14);
	cputs(" l -> rysuje linie");
	gotoxy(1, 15);
	cputs(" z -> przelacza tryb rysowania");
	gotoxy(1, 16);
	cputs(" f -> wypelnia");
	gotoxy(1, 17);
	cputs("---------------------------------");


	gotoxy(1, 25);
	textcolor(15);
	cputs(" Nazwa pliku: ");
	cputs(nazwa);
}
void ramka(){
	textcolor(15);
	textbackground(0);
	gotoxy(przesuniecieX, przesuniecieY);
	cputs("*");
	gotoxy(x_szer+przesuniecieX, przesuniecieY);
	cputs("*");
	gotoxy(przesuniecieX, przesuniecieY+y_wys);
	cputs("*");
	gotoxy(x_szer+przesuniecieX, przesuniecieY+y_wys);
	cputs("*");
}
void dodaj_znak(int x,int y, int attr, int back, bool rysuj_ciagle) {
	
	obraz[y-1][x-1] = attr;
	gotoxy(x+przesuniecieX, y+przesuniecieY);
	if (rysuj_ciagle) {
		textcolor(attr);
		textbackground(back);
		putch('#');
	}
	
}
void zapisz_do_pliku() {
	textcolor(15);
	textbackground(0);
	
	plik = fopen(nazwa, "w");

	char tab_naglx[32];
	itoa(x_szer, tab_naglx, 10);
	fputs(tab_naglx, plik);
	fputs(" ", plik);
	fputs("x", plik);
	fputs(" ", plik);
	char tab_nagly[32];
	itoa(y_wys, tab_nagly, 10);
	fputs(tab_nagly, plik);
	fputs("\n", plik);

	int n = 0;
	int m = 0;
	while (n < y_wys) {	
		for (int m = 0; m < x_szer; m++) {
			char tab[10];
			itoa(obraz[n][m], tab, 10);
			fputs(tab, plik);
			fputc(' ', plik);				
		}
		fputs("\n", plik);
		n++;
	}
	fclose(plik);	
}
void wpisanie_nazwy() {
	char litera;
	int l = 0;
	textcolor(15);
	textbackground(0);
	gotoxy(1, 30);
	cputs("Wpisz nazwe pliku: ");
	litera = 0;
	while ((litera != '\r') && (l < 255))
	{
		litera = getch();
		nazwa[l] = litera;
		putchar(litera);
		l++;

	}
	nazwa[l - 1] = '\0';
}
void wpisanie_wymiaru() {
	
	int n = 0;
	int i = 0;


	textcolor(15);
	gotoxy(1, 31);
	cputs("Wpisz wymiary obrazka, ktory chcesz utworzyc:");
	gotoxy(1, 32);

	char yc = NULL;
	char xc = NULL;


	int j = 0;
	char tab2[3] = { '\r','\r','\r' };
	while (xc != '\r') {
		xc = getch();
		tab2[j] = xc;
		j++;
		putchar(xc);
	}
	x_szer = atoi(tab2);
	gotoxy(5, 32);
	cputs("x");
	gotoxy(9, 32);
	j = 0;
	char tab1[3] = { '\r','\r','\r' };
	while (yc != '\r') {
		yc = getch();
		tab1[j] = yc;
		j++;
		putchar(yc);
	}
	y_wys = atoi(tab1);
	j = 0;

	char tab_naglx[32];
	itoa(x_szer, tab_naglx, 10);
	fputs(tab_naglx, plik);
	fputs(" ", plik);
	fputs("x", plik);
	fputs(" ", plik);
	char tab_nagly[32];
	itoa(y_wys, tab_nagly, 10);
	fputs(tab_nagly, plik);
	fputs("\n", plik);

	while (n < y_wys) {
		for (int m = 0; m < x_szer; m++) {
			fputc('0', plik);
			obraz[n][m] = i;
		}
		fputs("\n", plik);
		n++;
	}
}


int UtworzNowyPlik() {

	
		wpisanie_nazwy();

		int t[WYSOKOSC][SZEROKOSC];

		plik = fopen(nazwa, "w+t");
		int rozmiar = sizeof(t) / sizeof(int); 
		wpisanie_wymiaru();
		clrscr();
		menu();
		ramka();
		fclose(plik);   
		
		return 0;
}

void linia(int attr, int back)
{
	textbackground(back);
	textcolor(attr);
    int x = poczatek.pol_x;
	int y = poczatek.pol_y;

	// zmienne pomocnicze
	int d, dx, dy, ai, bi, xi, yi;
	// ustalenie kierunku rysowania
	if (poczatek.pol_x < koniec.pol_x)
	{
		xi = 1;
		dx = koniec.pol_x - poczatek.pol_x;
	}
	else
	{
		xi = -1;
		dx = poczatek.pol_x - koniec.pol_y;
	}
	// ustalenie kierunku rysowania
	if (poczatek.pol_y < koniec.pol_y)
	{
		yi = 1;
		dy = koniec.pol_y - poczatek.pol_y;
	}
	else
	{
		yi = -1;
		dy = poczatek.pol_y - koniec.pol_y;
	}
	gotoxy(x+przesuniecieX, y+przesuniecieY);
	putch('*');
	// oœ wiod¹ca OX
	obraz[x-1][y-1] = attr;
	if (dx > dy)
	{
		ai = (dy - dx) * 2;
		bi = dy * 2;
		d = bi - dx;
		// pêtla po kolejnych x
		while (x != koniec.pol_x)
		{
			// test wspó³czynnika
			if (d >= 0)
			{
				x += xi;
				y += yi;
				d += ai;
			}
			else
			{
				d += bi;
				x += xi;
			}
			gotoxy(x+przesuniecieX, y+przesuniecieY);
			putch('*');
			obraz[x-1][y-1] = attr;
		}
	}
	// oœ wiod¹ca OY
	else
	{
		ai = (dx - dy) * 2;
		bi = dx * 2;
		d = bi - dy;
		// pêtla po kolejnych y
		while (y != koniec.pol_y)
		{
			// test wspó³czynnika
			if (d >= 0)
			{
				x += xi;
				y += yi;
				d += ai;
			}
			else
			{
				d += bi;
				y += yi;
			}
			gotoxy(x+przesuniecieX, y+przesuniecieY);
			putch('*');
			obraz[x-1][y-1] = attr;
		}
	}
	getch();
}
void WczytajTenPlik() {
	FILE *przykladowy;
	przykladowy = fopen("przyklad.txt", "r");

	for (int i = 0; i<WYSOKOSC; i++) {
		for (int j = 0; j < SZEROKOSC; j++) {
			obraz[i][j] = 0;
		}
	}
	clrscr();

	menu();
	char x[20] = {};
	int szerokosc;
	int wysokosc;
	fscanf(plik, "%d", &szerokosc);
	fscanf(plik, "%s", x);
	fscanf(plik, "%d", &wysokosc);
	x_szer = szerokosc;
	y_wys = wysokosc;


	for (int i = 0; i < wysokosc; i++) {
		for (int j = 0; j < szerokosc; j++) {
			fscanf(przykladowy, "%d", &obraz[i][j]);
			gotoxy(j + przesuniecieX + 1, i + przesuniecieY + 1);
			textcolor(obraz[i][j]);
			textbackground(obraz[i][j]);
			putch('#');
		}
	}   ramka();
	fclose(przykladowy);

}

int Wczytaj_plik() {
	
	wpisanie_nazwy();
	plik = fopen(nazwa, "r");	
	if (plik == NULL) {
		gotoxy(1, 25);
		clrscr();
		cputs("Plik nie istnieje!");
		return -1;
	}
	    for(int i=0; i<WYSOKOSC; i++){
			for (int j = 0; j < SZEROKOSC; j++) {
				obraz[i][j] = 0;
			}}
		clrscr();

		menu();
		char x[20] = {};
		int szerokosc;
		int wysokosc;
		fscanf(plik, "%d", &szerokosc);
		fscanf(plik, "%s", x);
		fscanf(plik, "%d", &wysokosc);
		x_szer = szerokosc;
		y_wys = wysokosc;
		
	
		for (int i = 0; i < wysokosc; i++) {
			for (int j = 0; j < szerokosc; j++) {
				fscanf(plik, "%d", &obraz[i][j]);
				gotoxy(j + przesuniecieX+1, i + przesuniecieY+1);
				textcolor(obraz[i][j]);
				textbackground(obraz[i][j]);
				putch('#');
			}
		}   ramka();
			fclose(plik);
			return 0;
}


	int sprawdzczyXwtablicy(int x)
	{
		
		
		plik=fopen(nazwa, "r");
		int szerokosc;
		fscanf(plik, "%d", &szerokosc);
		if (x >= szerokosc)return 0;            
		else return 1;                             
	}                                              
	int sprawdzczyXwtablicy2(int x)
	{
		if (x <= 0)return 0;
		else return 1;
	}
	int sprawdzczyYwtablicy(int y)
	{
		
		plik = fopen(nazwa, "r");
		char x[20] = {};
		int szerokosc;
		int wysokosc;
		fscanf(plik, "%d", &szerokosc);
    	fscanf(plik, "%s", x);
		fscanf(plik, "%d", &wysokosc);
		if (y >= wysokosc)return 0;
		else return 1;
	}
	int sprawdzczyYwtablicy2(int y)
	{
		if (y <= 0)return 0;
		else return 1;
	}


int main() {
	
	int zn = 10, x = 1, y = 1, attr = 15, back = 15, zero = 0;
	bool rysuj_linie = false;
	UtworzNowyPlik();
	settitle("Laura Zuchowska 165101");
	do {
		textbackground(BLACK);
		if (zn == 'z') {
			rysowanie();
		}	
		
		dodaj_znak(x, y, attr, back, rysuj_ciagle);	
		zero = 0;
		zn = getch();
		if(zn == 0) {
			zero = 1;
			zn = getch();
			if(zn == 0x48 && sprawdzczyYwtablicy2(y-1)) y--;
			else if (zn == 0x50 && sprawdzczyYwtablicy(y + 1)) y++;
			else if(zn == 0x4b && sprawdzczyXwtablicy2(x - 1)) x--;
			else if (zn == 0x4d && sprawdzczyXwtablicy(x + 1)) x++;
			
		}
		else if (zn == '1') { attr = 1, back = 1; }
		else if (zn == '2') { attr = 2, back = 2; }
		else if (zn == '3') { attr = 3, back = 3; }
		else if (zn == '4') { attr = 4, back = 4; }
		else if (zn == '5') { attr = 5, back = 5; }
		else if (zn == '6') { attr = 6, back = 6; }
		else if (zn == '7') {attr = 7, back = 7;}
		else if (zn == '8') { attr = 8, back = 8; }
		else if (zn == '9') { attr = 9, back = 9; }
		else if (zn == '0') { attr = 10, back = 10; }
		else if (zn == 'q') { attr = 11, back = 11; }
		else if (zn == 'w') { attr = 12, back = 12; }
		else if (zn == 'e') { attr = 13, back = 13; }
		else if (zn == 'r') { attr = 14, back = 14; }
		else if (zn == 't') { attr = 15, back = 15; }
		else if (zn == 'y') { attr = 16, back = 16; }
		
		else if (zn == 'o') {
			Wczytaj_plik();
		}
		else if (zn == 'i') { WczytajTenPlik(); }
		else if (zn == 'n') {
			back = 0;  UtworzNowyPlik();
		}
		else if (zn == 's') {
			  zapisz_do_pliku();
		}
		else if (zn == 'l') {
			if (rysuj_linie == false) {
				poczatek.pol_x = x;
				poczatek.pol_y = y;
				rysuj_linie = true;
			}
			else {
				koniec.pol_x = x;
				koniec.pol_y = y;
				rysuj_linie = false;
				linia(attr, back);
			}
		}

		
		//else if (zn == 'k') funkcja na rysowanie prostokata;

		//else if (zn == 'f') funkcja na wypelnienie;

		

	} while (zn != 27);
	


	return 0;
	}
