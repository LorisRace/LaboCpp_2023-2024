#include <stdlib.h>
#include <iostream>
#include <set>
#include <cstring>
#include <fstream>
#include "ArrayList.h"
#include "Image.h"

using namespace std;

#ifndef PHOTOSHOP_H
#define PHOTOSHOP_H

class Photoshop
{
private:
	ArrayList<Image*>images;
	static int NumCourant;
	static Photoshop Instance;

	Photoshop();
	Photoshop(const Photoshop &photoshop);
	Photoshop &operator=(const Photoshop &photoshop);


public:
	~Photoshop();

	void Reset();
	void AjouteImage(Image *PointeurImage);
	void AfficheImages()const;
	void DessineImages()const;

	Image *getImageParIndice(int Indice);
	Image *getImageParId(int Id);

	void SupprimeImageParIndice(int Indice);
	void SupprimeImageParId(int Id);

	static Photoshop& getInstance();

	static Image *Operande1;
	static Image *Operande2;
	static Image *Resultat;


};


#endif