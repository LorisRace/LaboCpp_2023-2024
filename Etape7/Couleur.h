#include <stdlib.h>
#include <iostream>
#include <set>
#include <cstring>
#include "ImageNG.h"
#include "Image.h"
#include "ExceptionRGB.h"
using namespace std;

#ifndef COULEUR_H
#define COULEUR_H

class Couleur 
{
	public:
		static const Couleur BLEU;
		static const Couleur ROUGE;
		static const Couleur VERT;
		static const Couleur NOIR;
		static const Couleur BLANC;

	private:
		int Bleu;
		int Rouge;
		int Vert;
		

	public:
		Couleur();
		Couleur(int bleu, int rouge, int vert);
		Couleur(const Couleur &couleur);
		int getBleu() const;
		void setBleu(int val);
		int getRouge() const;
		void setRouge(int val);
		int getVert() const;
		void setVert(int val);
		friend std::ostream& operator<< (std::ostream &out,const Couleur &couleur);
		void Affiche()const;

};
#endif