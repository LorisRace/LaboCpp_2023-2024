#include<iostream>
#include"ArrayList.h"

template<class T>
Liste<T> :: Liste()
{
	
}

template<class T>
Liste<T> :: Liste(const Liste &liste)
{
	Cellule<T> *Courante = liste.PTete;

	while (Courante != nullptr)
	{
		AjouteElement(Courante->valeur);
		Courante = Courante->Suivant;
	}
}

template<class T>
Liste<T> :: ~Liste()
{
	if(PTete == NULL)
	{
		return;
	}

	else
	{
		Cellule<T> *Courante = PTete;
		Cellule<T> *Suivante = nullptr;

		while (Courante != nullptr)
		{
			Suivante = Courante->Suivant;
			delete Courante;
			Courante = Suivante;
		}
	}
}

template<class T>
bool Liste<T> :: estVide()const
{
	if (PTete == nullptr)
	{
		return PTete;
	}
}

template<class T>
int Liste<T> :: getNombreElements()const
{
	int Taille = 0;

	Cellule<T> *Courante = PTete;

	while(Courante != nullptr)
	{
		Taille++;

		Courante = Courante->Suivant;
	}

	return Taille;
}

template<class T>
void Liste<T> :: Affiche()const
{
	Cellule<T> *Courante = PTete;

	while (Courante != nullptr)
	{
		cout << "Valeur : " <<Courante->valeur << endl;

		Courante = Courante->Suivant;
	}
}

template<class T>
void Liste<T> :: AjouteElement(const T &valeur)
{
	Cellule<T> *Nouvelle = new Cellule<T>;
	Nouvelle->valeur = valeur;

	if (PTete == nullptr)
	{
		PTete = Nouvelle;
	}

	else
	{
		Cellule<T> *Courante = PTete;

		while(Courante->Suivant != nullptr)
		{
			Courante = Courante->Suivant;
		}

		Courante->Suivant = Nouvelle;
	}
}

template<class T>
T &Liste<T> :: getElement(int Ind)const
{
	Cellule<T> *Courante = PTete;

	for (int i = 0; i < Ind; i++)
	{
		Courante = Courante->Suivant;
	}

	return Courante->valeur;
}

template<class T>
T Liste<T> :: SupprimeElement(int Ind)
{
	Cellule<T> *Precedente = nullptr;
	Cellule<T> *Courante = PTete;

	for (int i = 0; i < Ind; i++)
	{
		Precedente = Courante;
		Courante = Courante->Suivant;
	}

	if (Precedente == nullptr)
	{
		PTete = Courante->Suivant;
	}

	else
	{
		Precedente->Suivant = Courante->Suivant;
	}

	T valeur = Courante->valeur;
	delete Courante;
	return valeur;
}

template<class T>
Liste<T> &Liste<T> :: operator=(const Liste &liste)
{
	//~Liste();
	//Liste(liste);
	return *this;
}








