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

  public:
    ImageNG();
    int getId() const;
    const char *getNom() const;
    Dimension getDimension() const;
    int getPixel(int x, int y)const;
    void setId (int val);
    void setNom (const char *n);
    void setDimension(const Dimension& d);
    void setPixel (int x, int y, int val);
    void setBackground(int val);
    ~ImageNG();
    void Affiche() const;
    void Dessine()const;
    ImageNG (int Id, const char *Nom);
    ImageNG (ImageNG &Image);
    ImageNG (int Id, const char *Nom,const Dimension& d);
    void importFromFile(const char* fichier);
   void exportToFile(const char* fichier,const char* format);
 
};

#endif