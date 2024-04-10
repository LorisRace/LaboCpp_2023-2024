#include <stdlib.h>
#include <iostream>
#include <set>
#include <cstring>
#include "ArrayList.h"
using namespace std;

#ifndef ITERATEUR_H
#define ITERATEUR_H

template<class T> class ArrayList;

template<class T> class Iterateur
{
private:
	Cellule<T> *Courant = nullptr;
	const ArrayList<T> &liste;

public:
	Iterateur(const ArrayList<T> &liste);
	~Iterateur();
	void Reset();
	bool end()const;
	bool operator++(int);
	bool operator++();
	operator T()const;
	T &operator&()const;
};

#endif