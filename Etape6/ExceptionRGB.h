#include <stdlib.h>
#include <iostream>
#include <string>
#include "Exception.h"
using namespace std;

#ifndef RGBEXCEPTION_H
#define RGBEXCEPTION_H

class RGBException : public Exception
{

private:
	int ErreurValeur;

public:
	RGBException();
	RGBException(string message, int valeur);
	RGBException(const RGBException &rgbexception);
	~RGBException();
	void setValeur(int valeur);
    int getValeur()const;
    void Affiche()const;

};


#endif