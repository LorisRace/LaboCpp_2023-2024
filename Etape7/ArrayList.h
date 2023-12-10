#include <stdlib.h>
#include <iostream>
#include <set>
#include <cstring>
using namespace std;

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

template<class T> struct Cellule
{
	T valeur;
	Cellule<T> *Suivant;
}


template<class T> class Liste
{

private:
	Cellule<T> *PTete;


public:
	Liste();
	Liste(const Liste &liste);
	~Liste();
	bool estVide()const;
	int getNombreElements()const;
	void Affiche()const;
	void AjouteElement(const T &valeur);
	T &getElement(int Ind);
	T SupprimeElement(int Ind);
	Liste &operator=(const Liste &liste);
};

#endif
