#include "ImageNG.h"
#include "MyQT.h"

ImageNG :: ImageNG()
{
	  nom = NULL;
    setNom ("Default");
    setId (1);
    setBackground(0);
}

ImageNG ::ImageNG (int Id, const char *Nom)
{
    nom = NULL;
    setNom (Nom);
    setId (Id);
}

ImageNG ::ImageNG (int Id, const char *Nom,const Dimension& d)
{
    nom = NULL;
    setNom (Nom);
    setId (Id);
    setDimension(d);
    setBackground(0);
}

ImageNG ::ImageNG (ImageNG &Image)
{
  nom = NULL;
    setId (Image.getId());
    setNom (Image.getNom());
    setDimension (Image.getDimension());

    for(int i = 0; i< dimension.getLargeur(); i++)
  {
    for (int j = 0; j< dimension.getHauteur(); j++)
      matrice[i][j]= Image.matrice[i][j];
  }


}

ImageNG :: ~ImageNG()
{
  
  if(nom)
        delete nom;
}

int ImageNG :: getId() const
{
	return id;
}

void ImageNG :: setId (int val)
{

	if (val >= 0)
      
        id = val;
      
	
}

const char * ImageNG :: getNom() const
{
  return nom;
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


Dimension ImageNG::getDimension() const
{
  return dimension;
}

void ImageNG::setDimension(const Dimension& d)
{
  dimension.setLargeur(d.getLargeur());

  dimension.setHauteur(d.getHauteur());
    
}

int ImageNG :: getPixel(int x, int y) const
{
  return matrice[x][y];
}

void ImageNG :: setPixel(int x, int y, int val)
{
   if(x < 0)
    exit(0);

  if(y < 0)
    exit(0);

  if (val < 0)
    exit(0);

  matrice[x][y] = val;
} 


void ImageNG :: setBackground(int val)
{
  if (val < 0)
    return;

  for(int i = 0; i< L_MAX; i++)
  {
    for (int j = 0; j< H_MAX; j++)
      matrice[i][j]= val;
  }
}

void ImageNG ::Affiche() const
{
	  cout << "id : " <<id<< endl;
    cout << "nom : "<<nom<< endl;
    dimension.Affiche();

}


void ImageNG :: importFromFile(const char* fichier)
{
  MyQT::ImportFromFile(*this, fichier);
}

void ImageNG :: exportToFile(const char* fichier,const char* format)
{
  MyQT::ExportToFile (*this, fichier, format);
}


void ImageNG :: Dessine() const
{

  MyQT::ViewImage(*this);

}
