#include<iostream>
#include"Iterateur.h"

template<class T>
Iterateur<T> :: Iterateur(const ArrayList<T> &liste) : liste(liste)
{
	Courant = liste.getPTete();
}

template<class T>
Iterateur<T> :: ~Iterateur()
{

}

template<class T>
void Iterateur<T> :: Reset()
{
	Courant = liste.getPTete();
}

template<class T>
bool Iterateur<T> :: end()const
{
	if (Courant == nullptr)
	{
		return true;
	}

	else
	{
		return false;
	}
}

template<class T>
bool Iterateur<T> :: operator++(int)
{
	return operator++();
}

template<class T>
bool Iterateur<T> :: operator++()
{
	if (Courant == nullptr)
	{
		return false;
	}

	else
	{
		Courant = Courant->Suivant;

		return true;
	}
}

template<class T>
Iterateur<T> :: operator T()const
{
	if (Courant != nullptr)
	{
		return Courant->valeur;
	}

	else
	{
		cout << "Iterateur en fin de liste" << endl;
	}

	return T();
}

template<class T>
T &Iterateur<T> :: operator&()const
{
	static T ValeurDefaut;
	
	if (Courant != nullptr)
	{
		return Courant->valeur;
	}

	else
	{
		cout << "Iterateur en fin de liste" << endl;

		
	}

	return ValeurDefaut;
}

template class Iterateur<int>;
template class Iterateur<Couleur>;
template class Iterateur<Image *>;