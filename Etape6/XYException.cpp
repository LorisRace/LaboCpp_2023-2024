#include "XYException.h"
#include <iostream>

XYException :: XYException() : Exception()
{
	setMessage("\nException XY\n");
}

XYException :: XYException(const string& message, const char ErreurValeur, const int x, const int y) : Exception(message)
{
	setErreurValeur(ErreurValeur);

	setX(x);

	setY(y);
}

XYException :: XYException(const string& message, const char ErreurValeur, const int valeur) : Exception(message)
{
	setErreurValeur(ErreurValeur);

	switch(ErreurValeur)
	{
		case 'x' : 	setX(valeur);
				 	break;

		case 'y' :	setY(valeur);
					break;

		default :	cout << "\nCommande invalide..." << endl;
	}
}

XYException :: XYException(const string& message, const char ErreurValeur) : Exception(message)
{
	setErreurValeur(ErreurValeur);
}

XYException :: XYException(const XYException &xyexception) : Exception(xyexception)
{
	setErreurValeur(xyexception.getErreurValeur());

	setX(xyexception.getX());

	setY(xyexception.getY());
}

XYException :: ~XYException()
{

}

void XYException :: setErreurValeur(const char ErreurValeur)
{
	if(ErreurValeur < 0 || ErreurValeur > 700)
		this->ErreurValeur = ErreurValeur;
}

char XYException :: getErreurValeur()const
{
	return ErreurValeur;
}

void XYException:: setX(const int x)
{
	
	if(x < 0 || x > 700)
		this->x = x;

	
}

int XYException :: getX()const
{
	return x;
}

void XYException :: setY(const int y)
{
	if(y < 0 || y > 700)
		this->y = y;
}

int XYException :: getY()const
{
	return y;
}

void XYException :: Affiche()const
{
	if(ErreurValeur != 0)
	{
		cout<<"\nExeption dans la matrice"<< endl;

		if(ErreurValeur == 'x' || ErreurValeur == 'd')
		{
			cout << "\nException dans Largeur X" << endl;
			if(x != 1)
			{
				cout << "\nComposant Largeur X invalide" << endl;
			}
		}

		if(ErreurValeur == 'd')
		{
			cout << "\nException Matrice" << endl;
		}

		if(ErreurValeur == 'y' || ErreurValeur == 'd')
		{
			cout << "\nException dans Hauteur Y" << endl;
			if(y != 1)
			{
				cout << "\nComposant Hauteur Y invalide" << endl;
			}	
		}
	}
}