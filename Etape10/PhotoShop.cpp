#include "PhotoShop.h"
#include "Iterateur.h"
#include <iostream>


int Photoshop :: NumCourant = 1;

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
		Image *Image_A_Supprimer = images.SupprimeElement(0);

		delete Image_A_Supprimer;
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
	for(Iterateur<Image *> iterateur(images); !iterateur.end(); iterateur++)
	{
		((Image *)iterateur)->Affiche();
	}
}

void Photoshop :: DessineImages()const
{
	for(Iterateur<Image *> iterateur(images); !iterateur.end(); iterateur++)
	{
		((Image *)iterateur)->Dessine();
	}
}

Image *Photoshop :: getImageParIndice(int Indice)
{
	return images.getElement(Indice);
}

Image *Photoshop :: getImageParId(int Id)
{
	for(Iterateur<Image *> iterateur(images); !iterateur.end(); iterateur++)
	{
		if(((Image *)iterateur)->getId() == Id)
		{
			return (Image *)iterateur;
		}
	}

	return nullptr;
}

void Photoshop :: SupprimeImageParIndice(int Indice)
{
	Image *Image_A_Supprimer = images.SupprimeElement(Indice);

	delete Image_A_Supprimer;
}

void Photoshop :: SupprimeImageParId(int Id)
{
	int Index;
	Iterateur<Image *> iterateur(images);

	for(Index = 0; !iterateur.end(); iterateur++, Index++)
	{
		if(((Image *)iterateur)->getId() == Id)
		{
			Image *Image_A_Supprimer = images.SupprimeElement(Index);

			delete Image_A_Supprimer;

			return;

		}
	}
}

