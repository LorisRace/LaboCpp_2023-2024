#include "ImageNG.h"
#include "MyQT.h"
#include <iostream>

ImageNG :: ImageNG() : Image()
{
    setBackground(0);
}

ImageNG ::ImageNG (int Id, const char *Nom): Image(Id, Nom)
{
    
    setBackground(0);

}

ImageNG ::ImageNG (int Id, const char *Nom,const Dimension& d) : Image(Id, Nom, d)
{
  
    setBackground(0);
}

ImageNG ::ImageNG (const char* fichier)
{
  nom = NULL;
  setNom(fichier);
  setId(0);
  MyQT::ImportFromFile(*this, fichier);
}

ImageNG ::ImageNG (const ImageNG &image) : Image(image)
{
  
    setDimension (image.getDimension());

    for(int i = 0; i< dimension.getLargeur(); i++)
  {
    for (int j = 0; j< dimension.getHauteur(); j++)
      matrice[i][j]= image.matrice[i][j];
  }


}

ImageNG :: ~ImageNG()
{
  
}

void ImageNG ::Affiche() const
{
  cout << "id : " <<id<< endl;
    cout << "nom : "<<nom<< endl;
    dimension.Affiche();
}

void ImageNG::exportToFile(const char* fichier,const char* format)
{
  MyQT::ExportToFile (*this, fichier, format);
}


void ImageNG::Dessine() const
{

  MyQT::ViewImage(*this);

}

void ImageNG :: importFromFile(const char* fichier)
{
  MyQT::ImportFromFile(*this, fichier);
}

int ImageNG :: getPixel(int x, int y) const
{
  int Largeur = dimension.getLargeur();
  int Hauteur = dimension.getHauteur();


  
  if((x < 0 || x >= Largeur) && (y < 0 || y >= Hauteur))
  {
    throw XYException ("\nDimension invalide", x, y);
    return 0;
  }

  if(x < 0 || x >= Largeur)
  {
    throw XYException ("\nPixel de largeur invalide", x);
    return 0;
  } 

  if(y < 0 || y >= Hauteur)
  {
    throw XYException ("\nPixel de hauteur invalide", y);
    return 0;
  }

  return matrice[x][y];
}

void ImageNG :: setPixel(int x, int y, int val)
{
  if((x < 0 || x >= L_MAX) && (y < 0 || y >= H_MAX))
  {
    throw XYException ("\nDimension invalide", x, y);
    
  }

  if(x < 0 || x >= L_MAX)
  {
    throw XYException ("\nPixel de largeur invalide", x);
    
  } 

  if(y < 0 || y >= H_MAX)
  {
    throw XYException ("\nPixel de hauteur invalide", y);
    
  } 

  matrice[x][y] = val;
} 


void ImageNG :: setBackground(int val)
{
    if(val < 0 || val > 255)
    {
      cout << "aaaa" << endl;
      throw RGBException ("\nNiveau gris invalide", val);
    }
  
  for (int i = 0; i < L_MAX; i++)
  {
    for(int j = 0; j < H_MAX; j++)
    {
      matrice[i][j] = val;
    }
  }  

}

int ImageNG :: getLuminance()const
{
  int Somme = 0;
  for(int i = 0; i<dimension.getLargeur(); i++)
  {
    for(int j = 0; j<dimension.getHauteur(); j++)
      Somme = Somme +matrice[i][j];
  }

  return Somme = Somme / (dimension.getLargeur() * dimension.getHauteur());
}

int ImageNG :: getMinimum()const
{
  int Min = 255;
  for(int i = 0; i<dimension.getLargeur(); i++)
  {
    for(int j = 0; j<dimension.getHauteur(); j++)
    {
      if (Min>matrice[i][j])
        Min = matrice[i][j];
    }

  }
  return Min;
 
} 

int ImageNG :: getMaximum()const
{
  int Max = 0;
  for(int i = 0; i<dimension.getLargeur(); i++)
  {
    for(int j = 0; j<dimension.getHauteur(); j++)
    {
      if(Max<matrice[i][j])
        Max = matrice[i][j];
    }
  }
  
  return Max;
}

float ImageNG :: getContraste()const
{
    return (float)(getMaximum() - getMinimum()) / (float)(getMaximum() + getMinimum());
}

ImageNG& ImageNG:: operator= (const ImageNG &image)
{
  setNom(image.nom);
  setId(image.id);
  dimension.setLargeur(image.dimension.getLargeur());
  dimension.setHauteur(image.dimension.getHauteur());

  for (int i = 0; i < dimension.getLargeur(); i++)
  {
    for (int j = 0; j < dimension.getHauteur(); j++)
      matrice[i][j] = image.matrice[i][j];
  }

  return *this;
}

std::ostream& operator<< (std::ostream &out,const ImageNG &image)
{

  out <<"Nom : " << image.getNom() << std :: endl;
  out <<"ID : " << image.getId() << std :: endl;
  out <<"Largeur : " <<image.dimension.getLargeur() << std :: endl;
  out <<"Hauteur : " <<image.dimension.getHauteur() << std :: endl;
  return out;
}

ImageNG ImageNG :: operator+(int Nombre_Entier)
{
  ImageNG Somme(*this);

  for(int i = 0; i < Somme.dimension.getLargeur(); i++)
  {
    for(int j = 0; j < Somme.dimension.getHauteur(); j++)
    {
      Somme.matrice[i][j] = Somme.matrice[i][j] + Nombre_Entier;

      if (Somme.matrice[i][j] > 255)
        Somme.matrice[i][j] = 255;

      if (Somme.matrice[i][j] < 0)
        Somme.matrice[i][j] = 0;
    }
  }

  return Somme;
}

ImageNG operator+(int Nombre_Entier, ImageNG image)
{
  return image + Nombre_Entier;
}

ImageNG ImageNG :: operator-(int Nombre_Entier)
{
  ImageNG Difference(*this);

  for(int i = 0; i < Difference.dimension.getLargeur(); i++)
  {
    for(int j = 0; j < Difference.dimension.getHauteur(); j++)
    {
      Difference.matrice[i][j] = Difference.matrice[i][j] - Nombre_Entier;
      if (Difference.matrice[i][j] > 255)
      {
        throw XYException("\nDifférence invalide", matrice[i][j]);
        Difference.matrice[i][j] = 255;
      }

      if (Difference.matrice[i][j] < 0)
      {
        throw XYException("\nDifférence invalide", matrice[i][j]);
        Difference.matrice[i][j] = 0;
      }

    }
  }

  return Difference;
}

ImageNG operator-(int Nombre_Entier, ImageNG image)
{

  return image - Nombre_Entier;
}

ImageNG operator++(ImageNG image)
{
  return image++;
}

ImageNG ImageNG :: operator++(int)
{
  ImageNG temp(*this);

  temp.dimension.setLargeur(temp.dimension.getLargeur());
  temp.dimension.setHauteur(temp.dimension.getHauteur());

  for (int i = 0; i < temp.dimension.getLargeur(); i++)
  {
    for (int j = 0; j < temp.dimension.getHauteur(); j++)
    {
      temp.matrice[i][j]++;

      if(temp.matrice[i][j] > 255)
        temp.matrice[i][j] = 255;

      if(temp.matrice[i][j] < 0)
        temp.matrice[i][j] = 0;


    }
  }

  return temp;

}

ImageNG operator--(ImageNG image)
{
  return image--;
}

ImageNG ImageNG :: operator--(int)
{
  ImageNG temp(*this);

  temp.dimension.setLargeur(temp.dimension.getLargeur());
  temp.dimension.setHauteur(temp.dimension.getHauteur());

  for (int i = 0; i < temp.dimension.getLargeur(); i++)
  {
    for (int j = 0; j < temp.dimension.getHauteur(); j++)
    {
      temp.matrice[i][j]--;


    }
  }

  return temp;
}

ImageNG ImageNG:: operator-(const ImageNG &image)
{
  ImageNG Resultat(*this);

  for(int i = 0; i < dimension.getLargeur(); i++)
    for(int j = 0; j < dimension.getHauteur(); j++)
      Resultat.matrice[i][j] = Resultat.matrice[i][j] - image.matrice[i][j];


  return Resultat;
}

bool ImageNG :: operator==(const ImageNG &image)
{
  if(dimension != image.getDimension())
    {
      throw XYException ("\nDimension 1 pas égale à Dimension 2", 'd');
    }

  for (int i = 0; i < dimension.getLargeur(); i++)
    for (int j = 0; j < dimension.getHauteur(); j++)
      if (matrice[i][j] != image.matrice[i][j])
      {
        return false;
      } 

  return true;
}

bool ImageNG :: operator<(const ImageNG &image)
{
  if(dimension != image.getDimension())
  {
    throw XYException ("Image de dimension differente",'d');
  }

  for (int i = 0; i < dimension.getLargeur(); i++)
    for (int j = 0; j < dimension.getHauteur(); j++)
    {
      if (matrice[i][j] >= image.matrice[i][j]) 
      {
        return false;
      }
    }

  return true;
}

bool ImageNG :: operator>(const ImageNG &image)
{
  if (dimension != image.getDimension())
  {
    throw XYException ("Image de dimension differente",'d');
  }

  for (int i = 0; i < dimension.getLargeur(); i++)
    for (int j = 0; j < dimension.getHauteur(); j++)
    {
      if (matrice[i][j] <= image.matrice[i][j])
      { 
        return false;
      }
    }

  return true;
}


void ImageNG :: Save(ofstream &fichier)const
{
  Image::Save(fichier);

  int LLargeur = dimension.getLargeur();
  int HHauteur = dimension.getHauteur();

  char *Vecteur = new char[LLargeur * HHauteur];

  for(int i = 0; i < LLargeur; i++)
  {
    for(int j = 0; j < HHauteur; j++)
    {
      Vecteur[i *HHauteur + j] = getPixel(i, j);
    }
  }

  fichier.write((char *)Vecteur, LLargeur * HHauteur *sizeof(char));
  delete[] Vecteur;
}

void ImageNG :: Load(ifstream &fichier)
{
  Image::Load(fichier);

  Dimension dimension;
  dimension.Load(fichier);

  int LLargeur = dimension.getLargeur();
  int HHauteur = dimension.getHauteur();

  char *Vecteur = new char[LLargeur * HHauteur];
  fichier.read((char *)Vecteur, LLargeur * HHauteur *sizeof(char));

  for(int i = 0; i < LLargeur; i++)
  {
    for(int j = 0; j < HHauteur; j++)
    {
      setPixel(i, j, Vecteur[i * HHauteur + j]);
    }
  }

  delete[] Vecteur;
}


char *ImageNG :: concatenerNoms(const char* nom, const char* suffixe, int taille)
{
    int tailleNouveauNom = strlen(nom) + strlen(suffixe) + 10;
    char* nouveauNom = new char[tailleNouveauNom];

    strcpy(nouveauNom, nom);

    strcat(nouveauNom, suffixe);
    sprintf(nouveauNom + strlen(nouveauNom), "%d", taille);

    return nouveauNom;
}