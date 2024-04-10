#include "PhotoShop.h"
#include "Iterateur.h"
#include <iostream>


int Photoshop :: NumCourant = 1;
Image *Photoshop::Operande1 = nullptr;
Image *Photoshop::Operande2 = nullptr;
Image *Photoshop::Resultat = nullptr;
Photoshop Photoshop :: Instance;

Photoshop :: Photoshop()
{

}

Photoshop :: ~Photoshop()
{
	Reset();
}

void Photoshop :: Reset()
{
	while(!images.estVide())
	{
		delete images.getElement(0);

		images.SupprimeElement(0);

	}

	NumCourant = 1;
}

void Photoshop :: AjouteImage(Image *PointeurImage)
{
	PointeurImage->setId(NumCourant);

	NumCourant += 1;

	images.AjouteElement(PointeurImage);
}

void Photoshop :: AfficheImages()const
{
	Iterateur<Image *> iterateur(images);
	for(iterateur.Reset(); !iterateur.end(); iterateur++)
	{
		(*iterateur).Affiche();
	}
}

void Photoshop :: DessineImages()const
{
	Iterateur<Image *> iterateur(images);
	for(iterateur.Reset(); !iterateur.end(); iterateur++)
	{
		(*iterateur).Dessine();
	}
}

Image *Photoshop :: getImageParIndice(int Indice)
{
	int Nombre = images.getNombreElements();

	if (Indice >= Nombre)
	{
		return nullptr;
	}

	else
	{
		return images.getElement(Indice);
	}
	
}

Image *Photoshop :: getImageParId(int Id)
{
	Iterateur<Image *> iterateur(images);
	for(iterateur.Reset(); !iterateur.end(); iterateur++)
	{
		if((*iterateur).getId() == Id)
		{
			return iterateur;
		}
	}

	return nullptr;
}

void Photoshop :: SupprimeImageParIndice(int Indice)
{
	images.SupprimeElement(Indice);
}

void Photoshop :: SupprimeImageParId(int Id)
{
	int Index = 0;
	Iterateur<Image *> iterateur(images);

	for(iterateur.Reset(); !iterateur.end(); iterateur++)
	{
		if((*iterateur).getId() == Id)
		{
			delete images.getElement(Index);
			images.SupprimeElement(Index);

		}
		Index++;
	}
}

Photoshop &Photoshop :: getInstance()
{
	return Instance;
}

