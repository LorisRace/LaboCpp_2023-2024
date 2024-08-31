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

int Photoshop :: ImportationImage(string Fichier)
{
	int i;
	ifstream Fichiers(Fichier, ios::in);
	string Ligne;

	for(i = 0; getline(Fichiers, Ligne); i++)
	{
		std::istringstream iStringStream(Ligne);

		string CategorieImage;
		string CheminImage;
		string NomImage;

		getline(iStringStream, CategorieImage, ';');
		getline(iStringStream, CheminImage, ';');
		getline(iStringStream, NomImage, ';');

		if(CategorieImage == "NG")
		{
			ImageNG *imageng = new ImageNG;
			imageng->importFromFile(CheminImage.c_str());
			imageng->setNom(NomImage.c_str());
			AjouteImage(imageng);
		}

		else if(CategorieImage == "RGB")
		{
			ImageRGB *imagergb = new ImageRGB;
			imagergb->importFromFile(CheminImage.c_str());
			imagergb->setNom(NomImage.c_str());
			AjouteImage(imagergb);
		}
	}

	Fichiers.close();

	return i;
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

void Photoshop :: Sauvegarder()
{
	ofstream FichierSauvegarde("SAVE.dat", ios::out | ios::binary);

	FichierSauvegarde.write((char*)&NumCourant, sizeof(int));

	ImageB::couleurTrue.Save(FichierSauvegarde);
	ImageB::couleurFalse.Save(FichierSauvegarde);

	int NombreImages = images.getNombreElements();
	FichierSauvegarde.write((char*)&NombreImages, sizeof(int));

	for(int i = 0; i < NombreImages; i++)
	{
		Image *image = getImageParIndice(i);

		if(dynamic_cast<ImageNG*>(image) != nullptr)
		{
			string NG = "NG";
			FichierSauvegarde.write((char*)&NG, sizeof(string));
			ImageNG *imageNG = dynamic_cast<ImageNG*>(image);
			imageNG->Save(FichierSauvegarde);
		}

		else if(dynamic_cast<ImageRGB*>(image) != nullptr)
		{
			string RGB = "RGB";
			FichierSauvegarde.write((char*)&RGB, sizeof(string));
			ImageRGB *imageRGB = dynamic_cast<ImageRGB*>(image);
			imageRGB->Save(FichierSauvegarde);
		}

		if(dynamic_cast<ImageB*>(image) != nullptr)
		{
			string B = "B";
			FichierSauvegarde.write((char*)&B, sizeof(string));
			ImageB *imageB = dynamic_cast<ImageB*>(image);
			imageB->Save(FichierSauvegarde);
		}
	}

	FichierSauvegarde.close();

}

void Photoshop :: Charger()
{
	ifstream FichierSauvegarde("SAVE.dat", ios::in | ios::binary);

	FichierSauvegarde.read((char*)&NumCourant, sizeof(int));

	ImageB::couleurTrue.Load(FichierSauvegarde);
	ImageB::couleurFalse.Load(FichierSauvegarde);

	int NombreImages;
	//FichierSauvegarde.read((char*)&NombreImages, sizeof(int));

	for(int i = 0; i != NombreImages; i++)
	{
		string CategorieImage;

		FichierSauvegarde.read((char*)&CategorieImage, sizeof(string));

		if(CategorieImage == "NG")
		{
			ImageNG *imageNG = new ImageNG;
			imageNG->Load(FichierSauvegarde);
			AjouteImage(imageNG);
		}

		else if(CategorieImage == "RGB")
		{
			ImageRGB *imageRGB = new ImageRGB;
			imageRGB->Load(FichierSauvegarde);
			AjouteImage(imageRGB);
		}

		else if(CategorieImage == "B")
		{
			ImageB *imageB = new ImageB;
			imageB->Load(FichierSauvegarde);
			AjouteImage(imageB);
		}
	}


	FichierSauvegarde.close();
}

