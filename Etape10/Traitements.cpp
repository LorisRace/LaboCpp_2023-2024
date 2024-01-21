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
        char* nouveauNom = ImageNG::concatenerNoms(imageIn.getNom(), "Seuillage", Taille);
		ImageB imageOut(imageIn.getId(), nouveauNom, imageIn.getDimension());

        int Largeur = imageIn.getDimension().getLargeur();
        int Hauteur = imageIn.getDimension().getHauteur();

        for (int i = 0; i < Largeur; i++)
        {
            for (int j = 0; j < Hauteur; j++)
            {
                imageOut.setPixel(i, j, imageIn.getPixel(i, j) < Taille);
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

    char* nouveauNom = ImageNG::concatenerNoms(imageIn.getNom(), "Moyenneur", Taille);

	ImageNG imageOut(imageIn.getId(), nouveauNom, imageIn.getDimension());

    int Largeur = imageIn.getDimension().getLargeur();
    int Hauteur = imageIn.getDimension().getHauteur();
    

    for (int i = 0; i < Largeur; i++)
    {
        for (int j = 0; j < Hauteur; j++)
        {
            
            int Somme = 0;
            int Compter = 0;

            for (int x = -Taille / 2; x <= Taille / 2; x++)
            {
                for (int y = -Taille / 2; y <= Taille / 2; y++)
                {
                    int NouveauX = i + x;
                    int NouveauY = j + y;

                    if (NouveauX >= 0 && NouveauX < Largeur && NouveauY >= 0 && NouveauY < Hauteur)
                    {
                        Somme += imageIn.getPixel(NouveauX, NouveauY);
                        Compter++;
                    }
                }
            }

            if (Compter > 0)
            {
                int Moyenne = Somme / Compter;
                imageOut.setPixel(i, j, Moyenne);
            }
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

    char* nouveauNom = ImageNG::concatenerNoms(imageIn.getNom(), "Median", Taille);

	ImageNG imageOut(imageIn.getId(), nouveauNom, imageIn.getDimension());

    int Largeur = imageIn.getDimension().getLargeur();
    int Hauteur = imageIn.getDimension().getHauteur();

    int offset = Taille / 2;
    for (int i = 0; i < Largeur; i++)
    {
        for (int j = 0; j < Hauteur; j++)
        {
            ArrayList<int> pixels;
            for (int k = std::max(0, i - offset); k <= std::min(Largeur - 1, i + offset); k++)
            {
                for (int l = std::max(0, j - offset); l <= std::min(Hauteur - 1, j + offset); l++)
                {
                    pixels.AjouteElement(imageIn.getPixel(k, l));
                }
            }

            int median;
            if (pixels.getNombreElements() % 2 == 1)
            {
                median = pixels.getElement(pixels.getNombreElements() / 2);
            }
            else
            {
                int midIdx = pixels.getNombreElements() / 2;
                median = static_cast<int>(std::round((pixels.getElement(midIdx - 1) + pixels.getElement(midIdx)) / 2.0));
            }
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

    char* nouveauNom = ImageNG::concatenerNoms(imageIn.getNom(), "Erosion", Taille);

	ImageNG imageOut(imageIn.getId(), nouveauNom, imageIn.getDimension());

    int Largeur = imageIn.getDimension().getLargeur();
    int Hauteur = imageIn.getDimension().getHauteur();

    int offset = Taille / 2;

    for (int i = 0; i < Largeur; i++)
    {
		for (int j = 0; j < Hauteur; j++)
		{
			int PlusBas = 0;
			for (int k = max(0, i - offset); k <= min(Largeur - 1, i + offset); k++)
				for (int l = max(0, j - offset); l <= min(Hauteur - 1, j + offset); l++)
					PlusBas = min(PlusBas, imageIn.getPixel(k, l));
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

    char* nouveauNom = ImageNG::concatenerNoms(imageIn.getNom(), "Dilatation", Taille);

	ImageNG imageOut(imageIn.getId(), nouveauNom, imageIn.getDimension());

    int Largeur = imageIn.getDimension().getLargeur();
    int Hauteur = imageIn.getDimension().getHauteur();

    int offset = Taille / 2;

    for (int i = 0; i < Largeur; i++)
    {
		for (int j = 0; j < Hauteur; j++)
		{
			int PlusHaut = 255;
			for (int k = max(0, i - offset); k <= min(Largeur - 1, i + offset); k++)
				for (int l = max(0, j - offset); l <= min(Hauteur - 1, j + offset); l++)
					PlusHaut = min(PlusHaut, imageIn.getPixel(k, l));
			imageOut.setPixel(i, j, PlusHaut);
		}
	}

	return imageOut;
}

ImageNG Traitement :: Negatif(const ImageNG &imageIn)
{

   char* nouveauNom = ImageNG::concatenerNoms(imageIn.getNom(), "Negatif", 255);

   ImageNG imageOut(imageIn.getId(), nouveauNom, imageIn.getDimension());

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