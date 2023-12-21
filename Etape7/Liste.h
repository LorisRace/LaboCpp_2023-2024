#ifndef ARRAYLIST_H
#define ARRAYLIST_H


#include <stdlib.h>
#include <iostream>
#include <set>
#include <cstring>
using namespace std;



template<class T> struct Cellule
{
	T valeur;
	Cellule<T> *Suivant = nullptr;
};


template<class T> class ArrayList
{

private:
	Cellule<T> *PTete = nullptr;


public:
	ArrayList();
	ArrayList(const ArrayList &ArrayList);
	~ArrayList();
	bool estVide()const;
	int getNombreElements()const;
	void Affiche()const;
	void AjouteElement(const T &valeur);
	T &getElement(int Ind)const;
	T SupprimeElement(int Ind);
	ArrayList &operator=(const ArrayList &ArrayList);
};

#endif
