#include "ExceptionRGB.h"
#include <iostream>

RGBException :: RGBException() : Exception()
{
	setMessage("Exception de type RGB");
}

RGBException :: RGBException(const string& message, int valeur) : Exception(message)
{
	setMessage(message);
}

RGBException :: RGBException(const RGBException &rgbexception) : Exception(rgbexception)
{

}

RGBException :: ~RGBException()
{

}

void RGBException :: setValeur(int valeur)
{
	if (valeur < 0 || valeur > 255)
		valeur = valeur;

}

int RGBException :: getValeur()const
{
	return ErreurValeur;
}

void RGBException :: Affiche()const
{
	cout << "\nException RGB de type : " << MessageErreur << endl;
}