#include <stdlib.h>
#include <iostream>
#include <set>
#include <cstring>
using namespace std;

#ifndef IMAGENG_H
#define IMAGENG_H


class ImageNG
{
  private:
    int id;
    char *nom;

  public:
    ImageNG();
    int getId() const;
    const char *getNom() const;
    void setId (int val);
    void setNom (const char *n);
    ~ImageNG();
    void Affiche();
    ImageNG (int Id, const char *Nom);
    ImageNG (ImageNG &Image);

};

#endif