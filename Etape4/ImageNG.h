#include <stdlib.h>
#include <iostream>
#include <set>
#include <cstring>
#include "Dimension.h"
using namespace std;

#ifndef IMAGENG_H
#define IMAGENG_H

class MyQT;

class ImageNG
{
  public:
    static const int L_MAX = 700;
    static const int H_MAX = 700;

  private:
    int id;
    char *nom;
    Dimension dimension;
    int matrice [L_MAX] [H_MAX];
    int compImage(const ImageNG &image);

  public:
    ImageNG();
    int getId() const;
    const char *getNom() const;
    Dimension getDimension() const;
    int getPixel(int x, int y)const;
    int getLuminance()const;
    int getMinimum()const;
    int getMaximum()const;
    float getContraste()const;
    void setId (int val);
    void setNom (const char *n);
    void setDimension(const Dimension& d);
    void setPixel (int x, int y, int val);
    void setBackground(int val);
    ~ImageNG();
    void Affiche() const;
    void Dessine()const;
    ImageNG (int Id, const char *Nom);
    ImageNG (const ImageNG &Image);
    ImageNG (int Id, const char *Nom,const Dimension& d);
    ImageNG (const char *fichier);
    void importFromFile(const char* fichier);
    void exportToFile(const char* fichier,const char* format);
    ImageNG& operator= (const ImageNG &image);
    friend std::ostream& operator<< (std::ostream &out,const ImageNG &image);
    ImageNG  operator+(int Nombre_Entier);
    friend ImageNG operator+(int Nombre_Entier, ImageNG image);
    ImageNG operator-(int Nombre_Entier);
    friend ImageNG operator-(int Val, ImageNG &image);
    friend ImageNG operator++(ImageNG image);
    ImageNG operator++(int);
    friend ImageNG operator--(ImageNG image);
    ImageNG operator--(int);
    ImageNG operator-(const ImageNG &image);
    bool operator==(const ImageNG &image);
    bool operator<(const ImageNG &image);
    bool operator>(const ImageNG &image);

 
};
#endif