#include <stdlib.h>
#include <iostream>
#include <set>
#include <cstring>
#include <fstream>
#include "Dimension.h"
#include "Image.h"
#include "ExceptionRGB.h"
#include "XYException.h"
using namespace std;

#ifndef IMAGENG_H
#define IMAGENG_H

class MyQT;

class ImageNG : public Image
{
  public:
    static const int L_MAX = 700;
    static const int H_MAX = 700;

  private:
    int matrice[L_MAX][H_MAX];
    int compImage(const ImageNG &image);

  public:
    ImageNG();
    int getPixel(int x, int y)const;
    int getLuminance()const;
    int getMinimum()const;
    int getMaximum()const;
    float getContraste()const;
    void setPixel (int x, int y, int val);
    void setBackground(int val);
    ~ImageNG();
    
    ImageNG (int Id, const char *Nom);
    ImageNG (const ImageNG &image);
    ImageNG (int Id, const char *Nom,const Dimension& d);
    ImageNG (const char *fichier);
    void Affiche() const;
    void Dessine()const;
    void exportToFile(const char* fichier,const char* format);

    void importFromFile(const char* fichier);
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

    void Save(ofstream &fichier)const;
    void Load(ifstream &fichier);


 
};
#endif