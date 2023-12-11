#include "ExceptionRGB.h"
#include <iostream>

RGBException :: RGBException() : Exception()
{
	setMessage("Exception de type RGB");
}

RGBException :: RGBException(const string& message, int valeur) : Exception(message)
{
	setMessage(message);

	setValeur(valeur);
}

RGBException :: RGBException(const RGBException &rgbexception) : Exception(rgbexception)
{
	setValeur(rgbexception.getValeur());
}

RGBException :: ~RGBException()
{

}

void RGBException :: setValeur(int valeur)
{
	if (valeur < 0 || valeur > 700)
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