#include "ImageB.h"
#include "MyQT.h"
#include <iostream>
using namespace std;

Couleur ImageB::couleurTrue = Couleur(255,255,255);
Couleur ImageB::couleurFalse = Couleur(0,0,0);


ImageB :: ImageB(): Image()
{
	for(int i = 0; i< dimension.getLargeur(); i++)
		for(int j = 0; j < dimension.getHauteur(); j++)
			matrice[i][j] = false;
	
}

ImageB :: ImageB(int Id, const char *nom): Image(Id,nom)
{
	for(int i = 0; i< dimension.getLargeur(); i++)
		for(int j = 0; j < dimension.getHauteur(); j++)
			matrice[i][j] = false;
	
}

ImageB :: ImageB (const ImageB &imageb): Image(imageb)
{
	for(int i = 0; i< dimension.getLargeur(); i++)
		for(int j = 0; j < dimension.getHauteur(); j++)
			matrice[i][j] = imageb.matrice[i][j];
}

ImageB :: ImageB (int Id, const char *Nom, const Dimension &d) : Image(Id,Nom,d)
{
	for(int i = 0; i< dimension.getLargeur(); i++)
		for(int j = 0; j < dimension.getHauteur(); j++)
			matrice[i][j] = false;
}

ImageB :: ~ImageB()
{

}

void ImageB :: Affiche()const
{
	cout << "id : " <<id<< endl;
    cout << "nom : "<<nom<< endl;
    dimension.Affiche();
}

void ImageB :: Dessine()const
{
	MyQT::ViewImage(*this);
}

void ImageB :: setBackground(bool valeur)
{
	for(int i = 0; i < L_MAX; i++)
		for(int j = 0; j < H_MAX; j++)
			matrice[i][j] = valeur;
}

void ImageB :: setPixel(int x, int y, bool valeur)
{
	if (x < 0 || x > 255)
		throw RGBException("\nPixel de couleur largeur invalide", x);
		

	if (y < 0 || y > 255)
		throw RGBException("\nPixel de couleur largeur invalide", y);
		

	matrice[x][y] = valeur;
}

bool ImageB :: getPixel(int x, int y)const
{
	int Largeur = dimension.getLargeur();
	int Hauteur = dimension.getHauteur();

	if ((x < 0 || x >= Largeur) && (y < 0 || y >= Hauteur))
	{
		throw XYException("\nDimension d'image binaire invalide", x, y);
	}
		

	if (x < 0 || x >= Largeur)
	{
		throw XYException("\nLargeur d'image binaire invalide", x);
		
	}
		

	if (y < 0 || y >= Hauteur)
	{
		throw XYException("\nLargeur d'image binaire invalide", y);
	}
		

	return matrice[x][y];
}

ImageB &ImageB :: operator =(const ImageB &imageb)
{
	setNom(imageb.nom);
	setId(imageb.id);
	dimension.setLargeur(imageb.getDimension().getLargeur());
	dimension.setHauteur(imageb.getDimension().getHauteur());

	for(int i = 0; i < dimension.getLargeur(); i++)
		for(int j = 0; j < dimension.getHauteur(); j++)
			matrice[i][j] = imageb.matrice[i][j];

	return *this;
}

ostream &operator <<(std :: ostream &out, const ImageB &imageb)
{
  out <<"Nom : " << imageb.getNom() << std :: endl;
  out <<"ID : " << imageb.getId() << std :: endl;
  out <<"Largeur : " <<imageb.dimension.getLargeur() << std :: endl;
  out <<"Hauteur : " <<imageb.dimension.getHauteur() << std :: endl;
  return out;
}

void ImageB :: exportToFile(const char *fichier, const char *format)
{
	MyQT::ExportToFile (*this, fichier, format);
}

void ImageB :: Save(ofstream &fichier)const
{
	Image::Save(fichier);

	int LLargeur = dimension.getLargeur();
	int HHauteur = dimension.getHauteur();

	bool *Vecteur = new bool[LLargeur * HHauteur];

	for(int i = 0; i < LLargeur; i++)
	{
		for(int j = 0; j < HHauteur; j++)
		{
			Vecteur[i *HHauteur + j] = getPixel(i, j);
		}
	}

	fichier.write((char *)Vecteur, LLargeur * HHauteur *sizeof(bool));
	delete[] Vecteur;
}

void ImageB :: Load(ifstream &fichier)
{
	Image::Load(fichier);

	Dimension dimension;
	dimension.Load(fichier);

	int LLargeur = dimension.getLargeur();
	int HHauteur = dimension.getHauteur();

	bool *Vecteur = new bool[LLargeur * HHauteur];
	fichier.read((char *)Vecteur, LLargeur * HHauteur *sizeof(bool));

	for(int i = 0; i < LLargeur; i++)
	{
		for(int j = 0; j < HHauteur; j++)
		{
			setPixel(i, j, Vecteur[i * HHauteur + j]);
		}
	}

	delete[] Vecteur;
}