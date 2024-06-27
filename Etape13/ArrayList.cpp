#include<iostream>
#include"ArrayList.h"

template<class T>
Cellule<T>* ArrayList<T>::getPTete() const 
{
    return PTete;
}

template<class T>
ArrayList<T> :: ArrayList()
{
	PTete = nullptr;
}

template<class T>
ArrayList<T> :: ArrayList(const ArrayList &liste)
{
	PTete = nullptr;

	Cellule<T> *Courante = liste.PTete;
	Cellule<T> *Precedente = nullptr;

	while (Courante != nullptr)
	{
		Cellule<T> *Nouveau = new Cellule<T>;
		Nouveau->valeur = Courante->valeur;
		Nouveau->Suivant = nullptr;

		if(PTete != nullptr)
		{
			Precedente->Suivant = Nouveau;
		}

		else
		{
			PTete = Nouveau;
		}

		Precedente = Nouveau;
		Courante = Courante->Suivant;
	}
}

template<class T>
ArrayList<T> :: ~ArrayList()
{
	if(PTete == NULL)
	{
		return;
	}

	else
	{
		Cellule<T> *Courante = PTete;
		Cellule<T> *Precedente = nullptr;

		while (Courante != nullptr)
		{
			Precedente = Courante;
			Courante = Courante->Suivant;
			delete Precedente;
		}
	}
}

template<class T>
bool ArrayList<T> :: estVide()const
{

	if (PTete != nullptr)
	{
		return false;
	}

	else
	{
		return true;
	}
}

template<class T>
int ArrayList<T> :: getNombreElements()const
{
	int Taille = 0;

	Cellule<T> *Courante = PTete;

	while(Courante != nullptr)
	{
		Courante = Courante->Suivant;
		Taille++;
	}

	return Taille;
}

template<class T>
void ArrayList<T> :: Affiche()const
{
	
	if(PTete == nullptr)
	{
		cout << "Désolé, mais la liste est vide" << endl;
		return;
	}

	else
	{
		cout << "Désolé, mais la liste est vide" << endl;
		return;
	}

	
}

template<class T>
void ArrayList<T> :: AjouteElement(const T &valeur)
{
	Cellule<T> *Nouvelle = new Cellule<T>;
	Nouvelle->valeur = valeur;
	Nouvelle->Suivant = nullptr;

	if (PTete == nullptr)
	{
		PTete = Nouvelle;
	}

	else
	{
		Cellule<T> *Courante = PTete;
		Cellule<T> *Precedente = nullptr;

		while(Courante != nullptr)
		{
			Precedente = Courante;
			Courante = Courante->Suivant;
		}

		Precedente->Suivant = Nouvelle;
	}
}

template<class T>
T &ArrayList<T> :: getElement(int Ind)const
{
	Cellule<T> *Courante = PTete;

	for (int i = 0; i < Ind; i++)
	{
		Courante = Courante->Suivant;
	}

	return Courante->valeur;
}

template<class T>
T ArrayList<T> :: SupprimeElement(int Ind)
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

	T valeurEnlevee = Courante->valeur;
	delete Courante;
	return valeurEnlevee;
}

template<class T>
ArrayList<T> &ArrayList<T> :: operator=(const ArrayList &liste)
{
	Cellule<T> *Courante = liste.PTete;
	Cellule<T> *Precedente = nullptr;

	while(Courante != nullptr)
	{
		Cellule<T> *Nouvelle = new Cellule<T>;
		Nouvelle->valeur = Courante->valeur;
		Nouvelle->Suivant = nullptr;

		if(PTete != nullptr)
		{
			Precedente->Suivant = Nouvelle;
		}

		else
		{
			PTete = Nouvelle;
		}

		Precedente = Nouvelle;
		Courante = Courante->Suivant;
	}
	return *this;
}

template class ArrayList<int>;
template class ArrayList<Couleur>;
template class ArrayList<Image *>;







