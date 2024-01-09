#include <stdlib.h>
#include <iostream>
#include <set>
#include <cstring>
#include <fstream>
#include "Dimension.h"
#include "Image.h"
#include "Couleur.h"
#include "XYException.h"
using namespace std;

#ifndef IMAGEB_H
#define IMAGEB_H

class ImageB : public Image
{

public:
	static const int L_MAX = 700;
	static const int H_MAX = 700;

	static Couleur couleurTrue;
	static Couleur couleurFalse;

private:
	bool matrice[L_MAX][H_MAX];


public:
	ImageB();
    ImageB (int Id, const char *Nom);
    ImageB (const ImageB &imageb);
    ImageB (int Id, const char *Nom,const Dimension& d);
    ~ImageB();

    void Affiche() const;
    void Dessine()const;
	void setBackground(bool valeur);
	void setPixel(int x, int y, bool valeur);
	bool getPixel(int x, int y)const;
	ImageB& operator= (const ImageB &imageb);
    friend std::ostream& operator<< (std::ostream &out,const ImageB &imageb);
	void exportToFile(const char* fichier,const char* format);

	void Save(ofstream &fichier)const;
	void Load(ifstream &fichier);

	char* concatenerNoms(const char* nom, const char* suffixe, int taille);

};

#endif


