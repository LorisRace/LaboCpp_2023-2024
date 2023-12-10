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
  
  if(nom)
        delete nom;
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

  for (int i = 0; i < Largeur; i++)
  {
    if(x < 0 || x > Largeur)
    {
      throw XYException ("\nLargeur invalide", x);
      return x;
    }

    for(int j = 0; j < Hauteur; j++)
    {
      if(y < 0 || y > Hauteur)
      {
        throw XYException ("\nHauteur invalide", y);
        return y;
      }

      if (matrice[x][y] < 0 || (matrice[x][y] > L_MAX && matrice[x][y] > H_MAX))
      {
          throw XYException ("\nMatrice invalide", matrice[x][y]);
          //return matrice[x][y];
      }
    }
  }  

  return matrice[x][y];
}

void ImageNG :: setPixel(int x, int y, int val)
{
  for (int i = 0; i < L_MAX; i++)
  {
    if(val < 0 || val > L_MAX)
    {
      throw XYException ("\nLargeur invalide", val);
      return;
    }

    for(int j = 0; j < H_MAX; j++)
    {
      if(val < 0 || val > H_MAX)
      {
        throw XYException ("\nHauteur invalide", val);
        return;
      }

      if (val < 0 || (val > L_MAX && val > H_MAX))
      {
          throw XYException ("\nMatrice invalide", val);
          return;
      }
    }
  } 

  matrice[x][y] = val;
} 


void ImageNG :: setBackground(int val)
{
  
  for (int i = 0; i < L_MAX; i++)
  {
    if(val < 0 || val > L_MAX)
    {
      throw XYException ("\nLargeur invalide", val);
      return;
    }

    for(int j = 0; j < H_MAX; j++)
    {
      if(val < 0 || val > H_MAX)
      {
        throw XYException ("\nHauteur invalide", val);
        return;
      }

      if (val < 0 || (val > L_MAX && val > H_MAX))
      {
          throw XYException ("\nMatrice invalide", val);
          return;
      }

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
        Difference.matrice[i][j] = 255;

      if (Difference.matrice[i][j] < 0)
        Difference.matrice[i][j] = 0;

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
  if(dimension != image.dimension)
    //throw XYException("\nDimension n'est pas égale à sa copie", dimension);
    return false;

  for (int i = 0; i < dimension.getLargeur(); i++)
    for (int j = 0; j < dimension.getHauteur(); j++)
      if (matrice[i][j] != image.matrice[i][j])
        throw XYException("\nMatrice 1 n'est pas égale à Matrice 2", matrice[i][j]);
        return false;

  return true;
}

bool ImageNG :: operator<(const ImageNG &image)
{
  int SommeThis = 0;
  int SommeCopie = 0;

  for (int i = 0; i < dimension.getLargeur(); i++)
    for (int j = 0; j < dimension.getHauteur(); j++)
    {
      SommeThis = SommeThis + matrice[i][j];

      SommeCopie = SommeCopie + image.matrice[i][j];
    }

    if(SommeThis > SommeCopie)
    {
      throw XYException ("\nLa somme est plus grande que sa copie", SommeThis);
    }

    return SommeThis < SommeCopie;
}

bool ImageNG :: operator>(const ImageNG &image)
{
  int SommeThis = 0;
  int SommeCopie = 0;

  for (int i = 0; i < dimension.getLargeur(); i++)
    for (int j = 0; j < dimension.getHauteur(); j++)
    {
      SommeThis = SommeThis + matrice[i][j];

      SommeCopie = SommeCopie + image.matrice[i][j];
    }

    if(SommeThis < SommeCopie)
    {
      throw XYException ("\nLa somme est plus petite que sa copie", SommeThis);
    }

    return SommeThis > SommeCopie;
}
