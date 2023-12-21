#include<iostream>
#include"Iterateur.h"

template<class T>
Iterateur<T> :: Iterateur(const ArrayList<T> &ArrayList) : ArrayList(ArrayList)
{
	Courant = arrayList.PTete;
}

template<class T>
Iterateur<T> :: ~Iterateur()
{

}

template<class T>
void Iterateur<T> :: reset()
{
	Courant = arrayList.PTete;
}

template<class T>
bool Iterateur<T> :: end()const
{
	if (Courant == nullptr)
	{
		return Courant;
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
}

template<class T>
T &Iterateur<T> :: operator&()const
{
	if (Courant != nullptr)
	{
		return Courant->valeur;
	}

	else
	{
		cout << "Iterateur en fin de liste" << endl;
	}
}