#pragma once

#include <windows.h> 
#include <time.h>
#include <math.h>
#include <stdio.h>

//console tool 
HANDLE hStdout, hStdin;
CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
WORD wOldColorAttrs;
CHAR chBuffer[256];
DWORD cRead, cWritten, fdwMode, fdwOldMode;

int OpenConsole();
int CloseConsole();
COORD GetConsoleSize();
void GotoXY(unsigned short int X, unsigned short int Y);
int PlotChar(char SomeChar);

int RangedRand(int range_min, int range_max);

//mes nouvelles fonctions

enum color{
	Noir,
	Bleu,
	Vert,
	BleuGris,
	Rouge,
	Violet,
	Jaune,
	Blanc,
	Gris,
	BleuClair,
	VertClair,
	Cyan,
	RougeClair,
	VioletClair,
	JauneClair,
	BlancBrillant,
};

void setBackgroundColor(const unsigned short couleur);

void setFontColor(const unsigned short couleur);

void setConsoleColor(const unsigned short Font, const unsigned short Background);

int compteDigit(int);

void afficheRectangle(COORD, int largeur, int hauteur, int couleur); //le rectange fera de base 5 de large et 3 de haut

void smartChiffreBox(COORD coord, int nombre, int couleur);

void smartChifreSizedBox(COORD coord, int nombre, int size, int couleur);

void smartTableauInt(COORD coord, int *tableau, int lenght, int couleur);

void smart2DTableauInt(COORD coord, int **tableau, int len1D, int len2D, int couleur);

void smartCadreText(COORD coord, char *text, const unsigned short font, const unsigned short cadre);

