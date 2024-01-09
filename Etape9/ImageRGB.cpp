#include "ImageRGB.h"
#include "MyQT.h"
#include <iostream>
using namespace std;

ImageRGB :: ImageRGB(): Image()
{
	for(int i = 0; i< dimension.getLargeur(); i++)
		for(int j = 0; j < dimension.getHauteur(); j++)
			matrice[i][j];
}

ImageRGB :: ImageRGB(int Id, const char *nom): Image(Id, nom)
{
	for(int i = 0; i< dimension.getLargeur(); i++)
		for(int j = 0; j < dimension.getHauteur(); j++)
			matrice[i][j];
}

ImageRGB :: ImageRGB (const ImageRGB &imagergb): Image(imagergb)
{
	setDimension(imagergb.getDimension());

	for(int i = 0; i< dimension.getLargeur(); i++)
		for(int j = 0; j < dimension.getHauteur(); j++)
			matrice[i][j] = imagergb.matrice[i][j];
}

ImageRGB :: ImageRGB (int Id, const char *Nom, const Dimension &d) : Image(Id, Nom, d)
{
	for(int i = 0; i< dimension.getLargeur(); i++)
		for(int j = 0; j < dimension.getHauteur(); j++)
			matrice[i][j];
}

ImageRGB :: ImageRGB (const char *fichier)
{
	nom = NULL;
	setNom(fichier);
	setId(0);
	MyQT::ImportFromFile(*this, fichier);
}

ImageRGB :: ~ImageRGB()
{

}

void ImageRGB :: Affiche()const
{
	cout << "id : " <<id<< endl;
    cout << "nom : "<<nom<< endl;
    dimension.Affiche();
}

void ImageRGB :: Dessine()const
{
	MyQT::ViewImage(*this);
}

void ImageRGB :: setBackground(const Couleur &valeur)
{
	for(int i = 0; i < L_MAX; i++)
		for(int j = 0; j < H_MAX; j++)
			matrice[i][j] = valeur;
}

void ImageRGB :: setPixel(int x, int y, const Couleur &valeur)
{
	if((x < 0 || x >= 255) && (y < 0 || y >= 255))
  {
    throw RGBException();
  }

  if(x < 0 || x >= 255)
  {
    throw RGBException();
    
  } 

  if(y < 0 || y >= 255)
  {
    throw RGBException();
    
  }

	matrice[x][y] = valeur;
}

Couleur ImageRGB :: getPixel(int x, int y)const
{
	int Largeur = dimension.getLargeur();
	int Hauteur = dimension.getHauteur();

	if ((x < 0 || x >= Largeur) && (y < 0 || y >= Hauteur))
	{
		throw RGBException();
	}
		

	if (x < 0 || x >= Largeur)
	{
		throw RGBException();
	}
		

	if (y < 0 || y >= Hauteur)
	{
		throw RGBException();
		
	}

	return matrice[x][y];
}

ImageRGB &ImageRGB :: operator =(const ImageRGB &imagergb)
{
	setNom(imagergb.nom);
	setId(imagergb.id);
	dimension.setLargeur(imagergb.getDimension().getLargeur());
	dimension.setHauteur(imagergb.getDimension().getHauteur());

	for(int i = 0; i < dimension.getLargeur(); i++)
		for(int j = 0; j < dimension.getHauteur(); j++)
			matrice[i][j] = imagergb.matrice[i][j];

	return *this;
}

ostream &operator <<(std :: ostream &out, const ImageRGB &imagergb)
{
  out <<"Nom : " << imagergb.getNom() << std :: endl;
  out <<"ID : " << imagergb.getId() << std :: endl;
  out <<"Largeur : " <<imagergb.dimension.getLargeur() << std :: endl;
  out <<"Hauteur : " <<imagergb.dimension.getHauteur() << std :: endl;
  return out;
}

void ImageRGB :: exportToFile(const char *fichier, const char *format)
{
	MyQT::ExportToFile (*this, fichier, format);
}

void ImageRGB :: importFromFile(const char *fichier)
{
	MyQT::ImportFromFile(*this, fichier);
}

void ImageRGB :: Save(ofstream &fichier)const
{
	Image::Save(fichier);

  int LLargeur = dimension.getLargeur();
  int HHauteur = dimension.getHauteur();

  for(int i = 0; i < LLargeur; i++)
  {
  	for(int j = 0; j < HHauteur; j++)
  	{
  		matrice[i][j].Save(fichier);
  	}
  }
}

void ImageRGB :: Load(ifstream &fichier)
{
	Image::Load(fichier);

	Dimension dimension;

	dimension.Load(fichier);

	setDimension(dimension);

	int LLargeur = dimension.getLargeur();
  int HHauteur = dimension.getHauteur();

  Couleur couleur;

  for(int i = 0; i < LLargeur; i++)
  {
  	for(int j = 0; j < HHauteur; j++)
  	{
  		couleur.Load(fichier);

  		setPixel(i, j, couleur);
  	}
  }
}
