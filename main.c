#include "smartDisplay.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	OpenConsole(); //obligatoire 

	COORD coord = { 5,5 }; //les coordonnnés d'affichage (point en haut a gauche)
	afficheRectangle(coord, 10, 7, Jaune);
	
	coord.X = 20;
	smartChiffreBox(coord, 7016, Vert);
	
	int tab[10] = { 1,2,3,4,5,6,7,8,9,10 };
	coord.Y = 1;
	smartTableauInt(coord, tab, 10, BleuGris);
	
	coord.Y = 10;
	
	int **tab2D = malloc(5*sizeof(int*));
	for (size_t i = 0; i < 5; i++)
		tab2D[i] = malloc(10 * sizeof(int));
	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			tab2D[i][j] = (i+1)*(j+1)*(j+1);
		}
	}
	smart2DTableauInt(coord, tab2D, 5,10, Vert );
	
	coord.X = 1; coord.Y = 1;
	smartCadreText(coord, "char * toto", BlancBrillant,Rouge);

	_getch();		//pour faire une pause avant de quiter le programme
	CloseConsole(); //obligatoire 
	return;
}