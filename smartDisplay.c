#include "smartDisplay.h"

/*******************************************/
/*          Hérité de consoleTool          */
/*******************************************/
int OpenConsole() {

	// Seed the random-number generator with the current time so that
	// the numbers will be different every time we run.
	srand((unsigned)time(NULL));


	// Get handles to STDIN and STDOUT. 
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	if (hStdin == INVALID_HANDLE_VALUE ||
		hStdout == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, TEXT("GetStdHandle"), TEXT("Console Error"),
			MB_OK);
		return 1;
	}
	// Save the current text colors. 

	if (!GetConsoleScreenBufferInfo(hStdout, &csbiInfo))
	{
		MessageBox(NULL, TEXT("GetConsoleScreenBufferInfo"),
			TEXT("Console Error"), MB_OK);
		return 1;
	}

	wOldColorAttrs = csbiInfo.wAttributes;
	return(0);
}

int CloseConsole() {
	// Restore the original text colors. 

	SetConsoleTextAttribute(hStdout, wOldColorAttrs);
	return(0);
}

COORD GetConsoleSize() {
	COORD Size;

	Size.X = csbiInfo.dwSize.X;
	Size.Y = csbiInfo.dwSize.Y;
	return(Size);
}

void GotoXY(unsigned short int X, unsigned short int Y) {

	COORD pos;
	pos.X = X;
	pos.Y = Y;
	SetConsoleCursorPosition(hStdout, pos);

	return;
}
int PlotChar(char SomeChar) {
	chBuffer[0] = SomeChar;
	chBuffer[1] = 0;
	cRead = 1;
	if (WriteFile(hStdout, chBuffer, cRead, &cWritten, NULL)) {
		return(0);
	}
	else {
		return(GetLastError());
	}
}

int RangedRand(int range_min, int range_max)
{
	// Generate random numbers in the half-closed interval
	// [range_min, range_max). In other words,
	// range_min <= random number < range_max

	int u = (double)rand() / (RAND_MAX + 1) * (range_max - range_min) + range_min;
	return(u);
}



/*******************************************/
/*          Nouveaux trucs crées           */
/*******************************************/

void setBackgroundColor(const unsigned short couleur)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), couleur * 16);
}

void setFontColor(const unsigned short couleur)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), couleur);
}

void setConsoleColor(const unsigned short Font, const unsigned short Background)
{
	setBackgroundColor(Background);
	setFontColor(Font);
}

int compteDigit(int nb)
{
	int nbDigit = 1;
	if (nb == 0)
		return 1;
	if (nb > 0) {
		while (nb / pow(10, nbDigit) >= 1) nbDigit++;
		return nbDigit;
	}
	else {
		while (nb / pow(10, nbDigit) <= -1) nbDigit++;
		return nbDigit + 1;
	}
}

void afficheRectangle(COORD pos, int largeur, int hauteur, int couleur)
{
	setBackgroundColor(couleur);
	//attention pour des raison d'affichage les bordures latérales seront plus large
	for (size_t i = pos.X; i < pos.X + largeur; i++)
	{
		for (size_t j = pos.Y; j < pos.Y + hauteur; j++)
		{
			if (i > pos.X + 1 && i<pos.X + largeur - 2 && j>pos.Y && j < pos.Y + hauteur - 1)
				continue;
			GotoXY(i, j);
			PlotChar(' ');
		}
	}
	setConsoleColor(Blanc, Noir);
}

void smartChiffreBox(COORD coord, int nombre, int couleur)
{
	afficheRectangle(coord, compteDigit(nombre) + 4, 3, couleur);
	GotoXY(coord.X + 2, coord.Y + 1);
	printf("%d", nombre);

}

void smartChifreSizedBox(COORD coord, int nombre, int size, int couleur)
{
	afficheRectangle(coord, size + 4, 3, couleur);
	GotoXY(coord.X + 2, coord.Y + 1);
	printf("%d", nombre);
}

void smartTableauInt(COORD coord, int * tableau, int len, int couleur)
{

	for (size_t i = 0; i < len; i++)
	{
		smartChiffreBox(coord, tableau[i], couleur);
		coord.X = coord.X + compteDigit(tableau[i]) + 4;
		GotoXY(coord.X, coord.Y + 1);
		if (i < len - 1)
			PlotChar('-');
		coord.X++;
	}

}

void smart2DTableauInt(COORD coord, int  **tableau, int len1D, int len2D, int couleur)
{
	int savedX = coord.X;
	int **tmp = tableau;
	int maxDigit = 0;
	//on calcul la taille max des chiffre
	for (size_t i = 0; i < len1D; i++) 
	{
		for (size_t j = 0; j < len2D; j++)
		{
			if (compteDigit(tmp[i][j]) >= maxDigit) maxDigit = compteDigit(tmp[i][j]);
		}
	}
	
	//on affiche
	for (size_t i = 0; i < len1D; i++)
	{
		for (size_t j = 0; j < len2D; j++)
		{
			smartChifreSizedBox(coord, tmp[i][j], maxDigit, couleur);
			if (j <= len2D - 2)	{
				GotoXY(coord.X + maxDigit + 4, coord.Y + 1);
				PlotChar('-');
			}
			if (i < len1D -1){
				GotoXY(coord.X + 2+maxDigit/2, coord.Y + 3);
				PlotChar('|');
			}
			coord.X += 5 + maxDigit;
		}
		coord.X = savedX;
		coord.Y += 4;
	}

}

void smartCadreText(COORD coord, char * text, const unsigned short font ,const unsigned short cadre )
{
	afficheRectangle(coord, strlen(text)+4, 3, cadre);
	GotoXY(coord.X + 2, coord.Y + 1);
	setFontColor(font);
	printf("%s", text);

	setConsoleColor(Blanc, Noir);
}

 























