#include "ImageNG.h"


ImageNG :: ImageNG()
{
	nom = NULL;
    setNom ("Default");
    setId (1);
}

int ImageNG :: getId() const
{
	return id;
}

const char * ImageNG :: getNom() const
{
	return nom;
}

void ImageNG :: setId (int val)
{

	if (val >= 0)
      {
        id = val;
      }
	
}

void ImageNG :: setNom (const char *n)
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

ImageNG :: ~ImageNG()
{
	
	if(nom)
        delete nom;
}

void ImageNG ::Affiche()
{
	cout << "id : " <<id<< endl;
    cout << "nom : "<<nom<< endl;
}
ImageNG ::ImageNG (int Id, const char *Nom)
{
	nom = NULL;
    setNom (Nom);
    setId (Id);
}

ImageNG ::ImageNG (ImageNG &Image)
{
	nom = NULL;
    setId (Image.getId());
    setNom (Image.getNom());
}


