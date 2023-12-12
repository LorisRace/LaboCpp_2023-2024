#include "ExceptionRGB.h"

RGBException :: RGBException() : Exception()
{
	setMessage("Pixel RGB invalide");
	setValeur(0);
}

RGBException :: RGBException(string message, int valeur) : Exception(message)
{
	setValeur(valeur);
}

RGBException :: RGBException(const RGBException &rgbexception) : Exception(rgbexception)
{
	setValeur(rgbexception.getValeur());
}

RGBException :: ~RGBException()
{

}

void RGBException :: setValeur(int v)
{
		ErreurValeur = v;
}

int RGBException :: getValeur()const
{
	return ErreurValeur;
}

void RGBException :: Affiche()const
{
	cout << "\nException RGB de type : " << MessageErreur << endl;
}