#include <stdlib.h>
#include <iostream>
#include <string>
#include "Exception.h"
using namespace std;


#ifndef XYEXCEPTION_H
#define XYEXCEPTION_H

class XYException : public Exception
{

private:
	char ErreurValeur;

	int x, y;

public:
	XYException();
	XYException(const string& message, const char e, const int x, const int y);
	XYException(const string& message, const char e, const int valeur);
	XYException(const string& message, const char e);
	XYException(const XYException &xyexception);
	~XYException();
	void setErreurValeur(const char e);
	char getErreurValeur()const;
	void setX(const int x);
	int getX()const;
	void setY(const int y);
	int getY()const;
	void Affiche()const;




};

#endif