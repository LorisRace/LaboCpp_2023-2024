#include "Image.h"
#include "MyQT.h"


Image :: Image()
{
	nom = NULL;
  setNom ("Default");
  setId (1);
}

Image ::Image (int Id, const char *Nom) 
{
    //nom = NULL;
    setNom (Nom);
    setId (Id);
}

Image ::Image (int Id, const char *Nom, const Dimension& d) 
{
    //nom = NULL;
    setNom (Nom);
    setId (Id);
    setDimension(d);
}

Image ::Image (const Image &image)
{
  	//nom = NULL;
    setId (image.getId());
    setNom (image.getNom());
    setDimension(image.getDimension());
}



Image::~Image()
{ 
	if(nom)
        delete nom;
}

int Image :: getId() const
{
	return id;
}

void Image :: setId (int val)
{

	if (val >= 0)
      
        id = val;  
	
}

const char * Image :: getNom() const
{
  return nom;
}

void Image :: setNom (const char *n)
{

	if (nom)
        delete nom;
      nom = new char [strlen(n)+1];
      if (strlen(n)== 0)
      {
        return;
      }

      strcpy (nom, n);

}


Dimension Image::getDimension() const
{
  return dimension;
}

void Image::setDimension(const Dimension& d)
{
  dimension.setLargeur(d.getLargeur());

  dimension.setHauteur(d.getHauteur());
    
}

void Image :: Save(ofstream &fichier)const
{
  int Id = getId();
  const char *Nom = getNom();
  int Taille = strlen(Nom);
  Dimension dimension = getDimension();

  fichier.write((char *)&Id, sizeof(int));
  fichier.write((char *)&Taille, sizeof(int));
  fichier.write((char *)Nom, Taille *sizeof(char));
  dimension.Save(fichier);
}

void Image :: Load(ifstream &fichier)
{
  int Id;
  int Taille;

  fichier.read((char *)&Id, sizeof(int));
  fichier.read((char *)&Taille, sizeof(int));

  char *Nom = new char[Taille + 1];

  fichier.read(Nom, Taille *sizeof(char));

  Nom[Taille] = '\0';

  setNom(Nom);

  delete[] Nom;
}

