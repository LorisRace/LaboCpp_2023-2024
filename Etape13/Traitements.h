#include <stdlib.h>
#include <iostream>
#include <set>
#include <cstring>
#include <fstream>
#include "ImageNG.h"
#include "ImageB.h"
using namespace std;

#ifndef TRAITEMENT_H
#define TRAITEMENT_H

class Traitement
{
public:
	static ImageB Seuillage(const ImageNG &imageIn, int Taille);
	static ImageNG Moyenneur(const ImageNG &imageIn, int Taille);
	static ImageNG Median(const ImageNG &imageIn, int Taille);
	static ImageNG Erosion(const ImageNG &imageIn, int Taille);
	static ImageNG Dilatation(const ImageNG &imageIn, int Taille);
	static ImageNG Negatif(const ImageNG &imageIn);
};

#endif