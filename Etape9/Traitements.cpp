#include <iostream>
#include <climits>
#include <cmath>
#include <string>
#include <vector>
#include "Traitements.h"
#include "ArrayList.h"
#include "Exception.h"
#include "ExceptionRGB.h"

ImageB Traitement :: Seuillage(const ImageNG &imageIn, int Taille)
{
    if (Taille < 0 || Taille > 700)
        throw RGBException("\nSeuillage invalide", Taille);

    else
    {
        string AncienNom = string(imageIn.getNom());
        string NouveauNom = AncienNom + "-Seuillage : " + to_string(Taille);

		ImageB imageOut(imageIn.getId(), NouveauNom.c_str(), imageIn.getDimension());

        int Largeur = imageIn.getDimension().getLargeur();
        int Hauteur = imageIn.getDimension().getHauteur();

        for (int i = 0; i < Largeur; i++)
        {
            for (int j = 0; j < Hauteur; j++)
            {
                imageOut.setPixel(i, j, imageIn.getPixel(i, j) > Taille);
            }
        }
        return imageOut;
    }
}

ImageNG Traitement::Moyenneur(const ImageNG &imageIn, int Taille)
{
    if (Taille <= 0)
    {
        throw Exception("\nDepuis quand a-t-on des tailles négatives ?\n");
    }

    if (Taille % 2 == 0)
    {
        throw Exception("\nOn n'aime pas les pairs ici\n");
    }

    string AncienNom = string(imageIn.getNom());
    string NouveauNom = AncienNom + "-Moyenne : " + to_string(Taille);

    int Largeur = imageIn.getDimension().getLargeur();
    int Hauteur = imageIn.getDimension().getHauteur();

    ImageNG imageOut(imageIn.getId(), NouveauNom.c_str(), imageIn.getDimension());

    for (int i = 0; i < Largeur; ++i)
    {
        for (int j = 0; j < Hauteur; ++j)
        {
            int Somme = 0;
            int Compter = 0;
            int offset = Taille / 2;

            for (int x = -offset; x <= offset; x++)
            {
                for (int y = -offset; y <= offset; y++)
                {
                    int NouveauX = i + x;
                    int NouveauY = j + y;

                    if (NouveauX >= 0 && NouveauX < Largeur && NouveauY >= 0 && NouveauY < Hauteur)
                    {
                        Somme = imageIn.getPixel(NouveauX, NouveauY);
                        Compter++;
                    }
                }
            }

            
            
            int Moyenne = Somme / Compter;
            imageOut.setPixel(i, j, Moyenne);
            
        }
    }

    return imageOut;
}

ImageNG Traitement::Median(const ImageNG &imageIn, int Taille)
{
    if (Taille <= 0)
    {
        throw Exception("\nDepuis quand a-t-on des tailles négatives ?\n");
    }

    if (Taille % 2 == 0)
    {
        throw Exception("\nOn n'aime pas les pairs ici\n");
    }

    string AncienNom = string(imageIn.getNom());
    string NouveauNom = AncienNom + "-Median : " + to_string(Taille);

    int Largeur = imageIn.getDimension().getLargeur();
    int Hauteur = imageIn.getDimension().getHauteur();

    ImageNG imageOut(imageIn.getId(), NouveauNom.c_str(), imageIn.getDimension());

    int offset = Taille / 2;
    for (int i = 0; i < Largeur; i++)
    {
        for (int j = 0; j < Hauteur; j++)
        {
            ArrayList<int> pixels;
            for (int k = -offset; k <= offset; k++)
            {
                for (int l = -offset; l <= offset; l++)
                {
                    int NouveauX = i + k;
                    int NouveauY = j + l;

                    if (NouveauX >= 0 && NouveauX < Largeur && NouveauY >= 0 && NouveauY < Hauteur)
                    {
                        pixels.AjouteElement(imageIn.getPixel(NouveauX, NouveauY)) ;
                    }
                }
            }

            int median;
        
            median = pixels.getElement(pixels.getNombreElements() / 2);
            
            imageOut.setPixel(i, j, median);
        }
    }

    return imageOut;
}


ImageNG Traitement :: Erosion(const ImageNG &imageIn, int Taille)
{
	if (Taille <= 0)
    {
        throw Exception("\nDepuis quand a-t-on des tailles négatives ?\n");
    }

    if (Taille % 2 == 0)
    {
        throw Exception("\nOn n'aime pas les pairs ici\n");
    }

    string AncienNom = string(imageIn.getNom());
    string NouveauNom = AncienNom + "-Erosion : " + to_string(Taille);

	ImageNG imageOut(imageIn.getId(), NouveauNom.c_str(), imageIn.getDimension());

    int Largeur = imageIn.getDimension().getLargeur();
    int Hauteur = imageIn.getDimension().getHauteur();

    int offset = Taille / 2;

    for (int i = 0; i < Largeur; i++)
    {
		for (int j = 0; j < Hauteur; j++)
		{
			int PlusBas = 255;
			for (int k = -offset; k <= offset; k++)
            {
				for (int l = -offset; l <= offset; l++)
                {
					int NouveauX = i + k;
                    int NouveauY = j + l;

                    if (NouveauX >= 0 && NouveauX < Largeur && NouveauY >= 0 && NouveauY < Hauteur)
                    {
                        if(PlusBas > imageIn.getPixel(NouveauX, NouveauY))
                        {
                            PlusBas = imageIn.getPixel(NouveauX, NouveauY);
                        }
                    }
                }
            }
			imageOut.setPixel(i, j, PlusBas);
		}
	}

	return imageOut;
}

ImageNG Traitement :: Dilatation(const ImageNG &imageIn, int Taille)
{
	if (Taille <= 0)
    {
        throw Exception("\nDepuis quand a-t-on des tailles négatives ?\n");
    }

    if (Taille % 2 == 0)
    {
        throw Exception("\nOn n'aime pas les pairs ici\n");
    }

    string AncienNom = string(imageIn.getNom()); 
    string NouveauNom = AncienNom + "-Dilatation : " + to_string(Taille);

	ImageNG imageOut(imageIn.getId(), NouveauNom.c_str(), imageIn.getDimension());

    int Largeur = imageIn.getDimension().getLargeur();
    int Hauteur = imageIn.getDimension().getHauteur();

    int offset = Taille / 2;

    for (int i = 0; i < Largeur; i++)
    {
		for (int j = 0; j < Hauteur; j++)
		{
			int PlusHaut = 0;
			for (int k = offset; k <= offset; k++)
            {
				for (int l = offset; l <= offset; l++)
                {
					int NouveauX = i + k;
                    int NouveauY = j + l;

                    if (NouveauX >= 0 && NouveauX < Largeur && NouveauY >= 0 && NouveauY < Hauteur)
                    {
                        if(PlusHaut < imageIn.getPixel(NouveauX, NouveauY))
                        {
                            PlusHaut = imageIn.getPixel(NouveauX, NouveauY);
                        }
                    }
                }
            }
			imageOut.setPixel(i, j, PlusHaut);
		}
	}

	return imageOut;
}

ImageNG Traitement :: Negatif(const ImageNG &imageIn)
{

   string AncienNom = string(imageIn.getNom());
    string NouveauNom = AncienNom + "-Negatif";

   ImageNG imageOut(imageIn.getId(), NouveauNom.c_str(), imageIn.getDimension());

   int Largeur = imageIn.getDimension().getLargeur();
   int Hauteur = imageIn.getDimension().getHauteur();

   for (int i = 0; i < Largeur; i++)
   {
   		for(int j = 0; j < Hauteur; j++)
   		{
   			imageOut.setPixel(i, j, 255 - imageIn.getPixel(i, j));
   		}
   }

   return imageOut;




}