#include <stdlib.h>
#include <iostream>
#include <set>
#include <cstring>
#include "ArrayList.h"
using namespace std;

#ifndef ITERATEUR_H
#define ITERATEUR_H

template<class T> class Iterateur
{
private:
	Cellule<T> *Courant = nullptr;
	const ArrayList<T> &arrayList;

public:
	Iterateur(const ArrayList<T> &ArrayList);
	~Iterateur();
	void reset();
	bool end()const;
	bool operator++(int);
	bool operator++();
	operator T()const;
	T &operator&()const;
};

#endif