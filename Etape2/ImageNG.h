#include <stdlib.h>
#include <iostream>
#include <set>
#include <cstring>
using namespace std;

#ifndef IMAGENG_H
#define IMAGENG_H
#include "Dimension.h"

class ImageNG
{
  private:
    int id;
    char *nom;
    Dimension dimension;

  public:
    ImageNG();
    int getId() const;
    const char *getNom() const;
    Dimension getDimension() const;
    void setId (int val);
    void setNom (const char *n);
    void setDimension(const Dimension& d);
    ~ImageNG();
    void Affiche() const;
    ImageNG (int Id, const char *Nom);
    ImageNG (ImageNG &Image);
    ImageNG (int Id, const char *Nom,const Dimension& d);

};

#endif