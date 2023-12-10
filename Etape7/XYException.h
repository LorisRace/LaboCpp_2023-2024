#include <stdlib.h>
#include <iostream>
#include <set>
#include <cstring>
#include <stdexcept>
#include "Exception.h"
using namespace std;
using std :: string;


#ifndef XYEXCEPTION_H
#define XYEXCEPTION_H

class XYException : public Exception
{

private:
	char ErreurValeur;

	int x, y;

public:
	XYException();
	XYException(const string& message, const char ErreurValeur, const int x, const int y);
	XYException(const string& message, const char ErreurValeur, const int valeur);
	XYException(const string& message, const char ErreurValeur);
	XYException(const XYException &xyexception);
	~XYException();
	void setErreurValeur(const char ErreurValeur);
	char getErreurValeur()const;
	void setX(const int x);
	int getX()const;
	void setY(const int y);
	int getY()const;
	void Affiche()const;




};

#endif