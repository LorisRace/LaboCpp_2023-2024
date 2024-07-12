#include <iostream>
using namespace std;
#include <unistd.h>
#include <QApplication>

#include "PhotoShop.h"
#include "ImageNG.h"
#include "ImageB.h"
#include "ImageRGB.h"
#include "Traitements.h"

int main(int argc,char* argv[])
{
  // Initialisation de QT
  QApplication app(argc,argv);
  close(2);

  // Creation du Garage
  // implicite !!! (variable statique)

  // Ajout d'images
  cout << endl << "//***** Ajout d'images à la biblothèque ******************************" << endl;
  cout << "Ajout image NG \"../images/joconde.bmp\"..." << endl;
  Photoshop::getInstance().AjouteImage(new ImageNG("../images/joconde.bmp"));

  cout << "Ajout image NG \"../images/lena.bmp\"..." << endl;
  ImageNG *p = new ImageNG();
  p->importFromFile("../images/lena.bmp");
  p->setNom("lena");
  Photoshop::getInstance().AjouteImage(p);

  cout << "Ajout image B lena seuillée à 128..." << endl;
  Photoshop::getInstance().AjouteImage(new ImageB(Traitement::Seuillage(*p,128)));

  cout << "Ajout image NG dessin à moi..." << endl;
  p = new ImageNG();
  p->setNom("monDessin");
  p->setDimension(Dimension(400,200));
  p->setBackground(100);
  for(int i=0 ; i<200 ; i++)
    p->setPixel(i,i,250);
  Photoshop::getInstance().AjouteImage(p);

  cout << "Ajout image RGB \"../images/mandrill.bmp\"..." << endl;
  Photoshop::getInstance().AjouteImage(new ImageRGB("../images/mandrill.bmp"));

  cout << endl << "//***** Images de la biblothèque *************************************" << endl;
  Photoshop::getInstance().AfficheImages();
  Photoshop::getInstance().DessineImages();

  cout << endl << "//***** Ajout de 2 images par copie **********************************" << endl;
  cout << "Copie image id=3..." << endl;
  Image* pImage = Photoshop::getInstance().getImageParId(3);
  ImageB *pB = (ImageB*)pImage;                 // downcasting dangereux !!!
  Photoshop::getInstance().AjouteImage(new ImageB(*pB));
  cout << "Copie image indice=1..." << endl;
  pImage = Photoshop::getInstance().getImageParIndice(1);
  ImageNG *pNG = (ImageNG*)pImage;              // downcasting dangereux !!!
  Photoshop::getInstance().AjouteImage(new ImageNG(*pNG));

  cout << endl << "//***** Images de la biblothèque *************************************" << endl;
  Photoshop::getInstance().AfficheImages();

  cout << endl << "//***** Apres suppression par indice (1) *****************************" << endl;
  Photoshop::getInstance().SupprimeImageParIndice(1);
  Photoshop::getInstance().AfficheImages();

  cout << endl << "//***** Apres suppression par id (4) *********************************" << endl;
  Photoshop::getInstance().SupprimeImageParId(4);
  Photoshop::getInstance().AfficheImages();  
  
  return 0;
}

