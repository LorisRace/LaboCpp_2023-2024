#include <stdlib.h>
#include <iostream>
#include <set>
#include <cstring>
#include <stdexcept>
#include "Exception.h"
using namespace std;
using std :: string;

#ifndef RGBEXCEPTION_H
#define RGBEXCEPTION_H

class RGBException : public Exception
{

private:
	int ErreurValeur;

public:
	RGBException();
	RGBException(const string& message, int valeur);
	RGBException(const RGBException &rgbexception);
	~RGBException();
	void setValeur(int valeur);
    int getValeur()const;
    void Affiche()const;

};


#endif