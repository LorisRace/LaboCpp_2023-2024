#include "mainwindowphotoshop.h"
#include "ui_mainwindowphotoshop.h"

#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <QScreen>
#include <QRect>
#include <QPixmap>
#include <QColorDialog>


#include "ImageNG.h"
#include "ImageRGB.h"
#include "ImageB.h"
#include "PhotoShop.h"
#include "Iterateur.h"
#include "Traitements.h"
#include "XYException.h"


MainWindowPhotoShop::MainWindowPhotoShop(QWidget *parent) : QMainWindow(parent),ui(new Ui::MainWindowPhotoShop)
{
    ui->setupUi(this);
    setTitre("Mini-PhotoShop  en C++");

    // Centrage de la fenetre
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->availableGeometry();
    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;
    move(x, y);
    setFixedSize(1021,845);

    // Configuration de la table des images
    ui->tableWidgetImages->setColumnCount(4);
    ui->tableWidgetImages->setRowCount(0);
    QStringList labelsTableOptions;
    labelsTableOptions << "Id" << "Type" << "Dimension" << "Nom";
    ui->tableWidgetImages->setHorizontalHeaderLabels(labelsTableOptions);
    ui->tableWidgetImages->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidgetImages->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetImages->horizontalHeader()->setVisible(true);
    ui->tableWidgetImages->horizontalHeader()->setDefaultSectionSize(100);
    ui->tableWidgetImages->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetImages->verticalHeader()->setVisible(false);
    ui->tableWidgetImages->horizontalHeader()->setStyleSheet("background-color: lightyellow");

    // Intialisation des scrollArea
    
    setImageNG("selection");
    setImageNG("operande1");
    setImageNG("operande2");
    setImageNG("resultat");
    

    // ComboBox des traitements disponibles
    ajouteTraitementDisponible("Eclaircir (+ val)");
    ajouteTraitementDisponible("Eclaircir (++)");
    ajouteTraitementDisponible("Assombrir (- val)");
    ajouteTraitementDisponible("Assombrir (--)");
    ajouteTraitementDisponible("Différence");
    ajouteTraitementDisponible("Comparaison (==)");
    ajouteTraitementDisponible("Comparaison (<)");
    ajouteTraitementDisponible("Comparaison (>)");
    ajouteTraitementDisponible("Seuillage");
    ajouteTraitementDisponible("Filtre moyenneur");
    ajouteTraitementDisponible("Filtre médian");
    ajouteTraitementDisponible("Erosion");
    ajouteTraitementDisponible("Dilatation");
    ajouteTraitementDisponible("Négatif");

    // Etape 14 (TO DO)
    // Restauration bibliothèque via fichier de sauvegarde
    ifstream FichierSauvegarde ("SAVE.dat", std::ios::in | std::ios::binary);

    if(FichierSauvegarde)
    {
        Photoshop::getInstance().Charger();
        videTableImages();

        int i;

        for(i = 0; Photoshop::getInstance().getImageParIndice(i) != nullptr; i++)
        {
            Image *image = Photoshop::getInstance().getImageParIndice(i);

            int Id = image->getId();
            string NomImage = image->getNom();
            Dimension dimensions = image->getDimension();
            string ValeursDimension = to_string(dimensions.getLargeur()) + "X" + to_string(dimensions.getHauteur());


            string CategorieImage;
            if(dynamic_cast<ImageNG*>(image) != nullptr)
            {
                CategorieImage = "NG";
            }

            else if(dynamic_cast<ImageRGB*>(image) != nullptr)
            {
                CategorieImage = "RGB";
            }

            else if(dynamic_cast<ImageB*>(image) != nullptr)
            {
                CategorieImage = "B";
            }

            ajouteTupleTableImages(Id, CategorieImage, ValeursDimension, NomImage);
        }
    }


    // TESTS DEMOS A SUPPRIMER
    /*ajouteTupleTableImages(3,"NG","256x256","lena.bmp");
    setResultatBoolean(1);*/
}

MainWindowPhotoShop::~MainWindowPhotoShop()
{
    delete ui;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Méthodes de la fenêtre (ne pas modifier) ///////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::setTitre(string titre)
{
  this->setWindowTitle(titre.c_str());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::setNomImage(string nom)
{
  ui->lineEditNom->setText(QString::fromStdString(nom));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string MainWindowPhotoShop::getNomImage() const
{
  return ui->lineEditNom->text().toStdString();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::setParametresImageNG(int max,int min,int luminance,float contraste)
{
  if (max == -1)
  {
    ui->lineEditMax->setText("");
    ui->lineEditMin->setText("");
    ui->lineEditLuminance->setText("");
    ui->lineEditContraste->setText("");
    return;
  }
  char tmp[20];
  sprintf(tmp,"%d",max);
  ui->lineEditMax->setText(tmp);
  sprintf(tmp,"%d",min);
  ui->lineEditMin->setText(tmp);
  sprintf(tmp,"%d",luminance);
  ui->lineEditLuminance->setText(tmp);
  sprintf(tmp,"%f",contraste);
  ui->lineEditContraste->setText(tmp);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MainWindowPhotoShop::setImageNG(string destination,const ImageNG* imageng)
{
    QPixmap * pixmap = NULL;
    if (imageng != NULL)
    {
      // Creation du QPixmap
      int largeur = imageng->getDimension().getLargeur();
      int hauteur = imageng->getDimension().getHauteur();
      QImage im1(largeur,hauteur,QImage::Format_RGB32);
      for(int x=0 ; x<largeur ; x++)
        for(int y=0 ; y<hauteur ; y++)
        {
          int valeur = imageng->getPixel(x,y);
          im1.setPixel(x,y,qRgb(valeur,valeur,valeur));
        }
     pixmap = new QPixmap(QPixmap::fromImage(im1));
    }

    // Mise en place du QPixmap
    QLabel* label = new QLabel();
    label->setAlignment(Qt::AlignCenter);
    if (pixmap) label->setPixmap(*pixmap);
    else label->setText("vide");
    if (destination == "selection") ui->scrollAreaSelection->setWidget(label);
    if (destination == "operande1") ui->scrollAreaOperande1->setWidget(label);
    if (destination == "operande2") ui->scrollAreaOperande2->setWidget(label);
    if (destination == "resultat") ui->scrollAreaResultat->setWidget(label);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MainWindowPhotoShop::setImageRGB(string destination,const ImageRGB* imagergb)
{
    QPixmap * pixmap = NULL;
    if (imagergb != NULL)
    {
      // Creation du QPixmap
      int largeur = imagergb->getDimension().getLargeur();
      int hauteur = imagergb->getDimension().getHauteur();
      QImage im1(largeur,hauteur,QImage::Format_RGB32);
      for(int x=0 ; x<largeur ; x++)
        for(int y=0 ; y<hauteur ; y++)
        {
          Couleur valeur = imagergb->getPixel(x,y);
          im1.setPixel(x,y,qRgb(valeur.getRouge(),valeur.getVert(),valeur.getBleu()));
        }
     pixmap = new QPixmap(QPixmap::fromImage(im1));
    }

    // Mise en place du QPixmap
    QLabel* label = new QLabel();
    label->setAlignment(Qt::AlignCenter);
    if (pixmap) label->setPixmap(*pixmap);
    else label->setText("vide");
    if (destination == "selection") ui->scrollAreaSelection->setWidget(label);
    if (destination == "operande1") ui->scrollAreaOperande1->setWidget(label);
    if (destination == "operande2") ui->scrollAreaOperande2->setWidget(label);
    if (destination == "resultat") ui->scrollAreaResultat->setWidget(label);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MainWindowPhotoShop::setImageB(string destination,const ImageB* imageb)
{
    QPixmap * pixmap = NULL;
    if (imageb != NULL)
    {
      // Creation du QPixmap
      int largeur = imageb->getDimension().getLargeur();
      int hauteur = imageb->getDimension().getHauteur();
      QImage im1(largeur,hauteur,QImage::Format_RGB32);
      for(int x=0 ; x<largeur ; x++)
        for(int y=0 ; y<hauteur ; y++)
        {
          bool valeur = imageb->getPixel(x,y);
          if (valeur) im1.setPixel(x,y,qRgb(ImageB::couleurTrue.getRouge(),ImageB::couleurTrue.getVert(),ImageB::couleurTrue.getBleu()));
          else im1.setPixel(x,y,qRgb(ImageB::couleurFalse.getRouge(),ImageB::couleurFalse.getVert(),ImageB::couleurFalse.getBleu()));
        }
     pixmap = new QPixmap(QPixmap::fromImage(im1));
    }

    // Mise en place du QPixmap
    QLabel* label = new QLabel();
    label->setAlignment(Qt::AlignCenter);
    if (pixmap) label->setPixmap(*pixmap);
    else label->setText("vide");
    if (destination == "selection") ui->scrollAreaSelection->setWidget(label);
    if (destination == "operande1") ui->scrollAreaOperande1->setWidget(label);
    if (destination == "operande2") ui->scrollAreaOperande2->setWidget(label);
    if (destination == "resultat") ui->scrollAreaResultat->setWidget(label);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::setResultatBoolean(int val)
{
  if (val == 1) // vrai
  {
    ui->checkBoxResultat->setChecked(true);
    ui->checkBoxResultat->setText("VRAI");
    ui->checkBoxResultat->setStyleSheet("background-color: lightgreen;border: 1px solid black;");
    return;
  }
  if (val == 0) // faux
  {
    ui->checkBoxResultat->setChecked(false);
    ui->checkBoxResultat->setText("FAUX");
    ui->checkBoxResultat->setStyleSheet("background-color: red;border: 1px solid black;");
    return;
  }
  // ni vrai, ni faux
  ui->checkBoxResultat->setChecked(false);
  ui->checkBoxResultat->setText("resultat");
  ui->checkBoxResultat->setStyleSheet("background-color: lightyellow;border: 1px solid black;");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles Table des Images (ne pas modifier) ////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::ajouteTupleTableImages(int id,string type,string dimension,string nom)
{
    char Id[20];
    sprintf(Id,"%d",id);

    char Type[20];
    strcpy(Type,type.c_str());

    char Dimension[20];
    strcpy(Dimension,dimension.c_str());

    char Nom[80];
    strcpy(Nom,nom.c_str());

    // Ajout possible
    int nbLignes = ui->tableWidgetImages->rowCount();
    nbLignes++;
    ui->tableWidgetImages->setRowCount(nbLignes);
    ui->tableWidgetImages->setRowHeight(nbLignes-1,20);

    QTableWidgetItem *item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(Id);
    ui->tableWidgetImages->setItem(nbLignes-1,0,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(Type);
    ui->tableWidgetImages->setItem(nbLignes-1,1,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(Dimension);
    ui->tableWidgetImages->setItem(nbLignes-1,2,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(Nom);
    ui->tableWidgetImages->setItem(nbLignes-1,3,item);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::videTableImages()
{
    ui->tableWidgetImages->setRowCount(0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MainWindowPhotoShop::getIndiceImageSelectionnee()
{
    QModelIndexList liste = ui->tableWidgetImages->selectionModel()->selectedRows();
    if (liste.size() == 0) return -1;
    QModelIndex index = liste.at(0);
    int indice = index.row();
    return indice;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Combox des traitements disponibles (ne pas modifier) ///////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::ajouteTraitementDisponible(string operation)
{
    ui->comboBoxTraitements->addItem(operation.c_str());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::videTraitementsDisponibles()
{
    ui->comboBoxTraitements->clear();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string MainWindowPhotoShop::getTraitementSelectionne() const
{
    return ui->comboBoxTraitements->currentText().toStdString();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions permettant d'afficher des boites de dialogue (ne pas modifier) ///////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::dialogueMessage(const char* titre,const char* message)
{
   QMessageBox::information(this,titre,message);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::dialogueErreur(const char* titre,const char* message)
{
   QMessageBox::critical(this,titre,message);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string MainWindowPhotoShop::dialogueDemandeTexte(const char* titre,const char* question)
{
    QString chaine = QInputDialog::getText(this,titre,question);
    return chaine.toStdString();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MainWindowPhotoShop::dialogueDemandeInt(const char* titre,const char* question)
{
    return QInputDialog::getInt(this,titre,question);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
float MainWindowPhotoShop::dialogueDemandeFloat(const char* titre,const char* question)
{
    return QInputDialog::getDouble(this,titre,question);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string MainWindowPhotoShop::dialogueDemandeFichierOuvrir(const char* question)
{
  QString fileName = QFileDialog::getOpenFileName(this,question, "", "Tous les fichiers (*.*)");
  return fileName.toStdString();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string MainWindowPhotoShop::dialogueDemandeFichierEnregistrer(const char* question)
{
  QString fileName = QFileDialog::getSaveFileName(this,question, "", "Tous les fichiers (*.*)");
  return fileName.toStdString();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::dialogueDemandeCouleur(const char* message,int* pRouge,int* pVert,int* pBleu)
{
  QColor color = QColorDialog::getColor(Qt::red,this,message);
  *pRouge = color.red();
  *pVert = color.green();
  *pBleu = color.blue();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Clic sur la croix de la fenêtre ////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::closeEvent(QCloseEvent *event)
{
  if (event == NULL) {} // pour éviter le warning à la compilation
  // Etape 14 (TO DO)

  string SortieApplication = dialogueDemandeTexte("Sortie d'application", "Souhaitez-vous sauvergarder vos données , O-N ?");
  
  if(SortieApplication == "O")
  {
      Photoshop::getInstance().Sauvegarder();
      dialogueMessage("Données sauvegardées", "Les données ont été sauvegardées");
  }

  else if(SortieApplication == "N")
  {
      bool Resultat = deleteSaveFile();

      if(Resultat)
      {
          dialogueMessage("Données supprimées", "Les données ont été supprimées");
      }

      else
      {
          dialogueMessage("Erreur Suppression", "Il n'y avait aucune donnée à supprimer");
      }
  }

  dialogueMessage("Au revoir", "Revenez vite :)");
  QApplication::exit();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions clics sur les items de menu //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionQuitter_triggered()
{
  // Etape 14 (TO DO)

  string SortieApplication = dialogueDemandeTexte("Sortie d'application", "Souhaitez-vous sauvergarder vos données , O-N ?");
  
  if(SortieApplication == "O")
  {
      Photoshop::getInstance().Sauvegarder();
      dialogueMessage("Données sauvegardées", "Les données ont été sauvegardées");
  }

  else if(SortieApplication == "N")
  {
      bool Resultat = deleteSaveFile();

      if(Resultat)
      {
          dialogueMessage("Données supprimées", "Les données ont été supprimées");
      }

      else
      {
          dialogueMessage("Erreur Suppression", "Il n'y avait aucune donnée à supprimer");
      }
  }

  dialogueMessage("Au revoir", "Revenez vite :)");


  QApplication::exit();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionCharger_ImageNB_triggered()
{
  // Etape 11 (TO DO)

  string Fichier = dialogueDemandeFichierOuvrir("Entrez le nom du fichier à ouvrir");

  if(Fichier.empty())
  {
    dialogueMessage("Annulation", "Aucun fichier ne sera ouvert");
    return;
  }

  ImageNG *IImage = new ImageNG;
  IImage->importFromFile(Fichier.c_str());
  IImage->setNom(Fichier.c_str());
  Photoshop::getInstance().AjouteImage(IImage);
  videTableImages();


  for(int i = 0; Photoshop::getInstance().getImageParIndice(i) != nullptr; i++)
  {
    Image *SelectionImage = Photoshop::getInstance().getImageParIndice(i);
    int Id = SelectionImage->getId();
    const char * Nom = SelectionImage->getNom();
    Dimension dimension = SelectionImage->getDimension();
    string ValeursDimension = to_string(dimension.getLargeur()) + "X" + to_string(dimension.getHauteur());

    string CategorieImage;

    if(dynamic_cast<ImageB*>(SelectionImage) != nullptr)
    {
        CategorieImage = "B";
        ImageB imageb;
        setImageB("selection", dynamic_cast<ImageB*>(Photoshop::getInstance().getImageParIndice(i)));
    }

    else if(dynamic_cast<ImageRGB*>(SelectionImage) != nullptr)
    {
        CategorieImage = "RGB";
        ImageRGB imagergb;
        setImageRGB("selection", dynamic_cast<ImageRGB*>(Photoshop::getInstance().getImageParIndice(i)));
        
    }

    else if(dynamic_cast<ImageNG*>(SelectionImage) != nullptr)
    {
        CategorieImage = "NG";
        ImageNG imageng;
        setImageNG("selection", dynamic_cast<ImageNG*>(Photoshop::getInstance().getImageParIndice(i)));
        
    }

    else
    {
      dialogueErreur("Erreur", "Désolé, mais aucune catégorie d'image n'a été sélectionnée");
    }

    ajouteTupleTableImages(Id, CategorieImage, ValeursDimension, Nom);
  
  }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionCharger_ImageRGB_triggered()
{
  // Etape 11 (TO DO)

  string Fichier = dialogueDemandeFichierOuvrir("Entrez le nom du fichier à ouvrir");

  if(Fichier.empty())
  {
    dialogueMessage("Annulation", "Aucun fichier ne sera ouvert");
    return;
  }

  ImageRGB *IImage = new ImageRGB;
  IImage->importFromFile(Fichier.c_str());
  IImage->setNom(Fichier.c_str());
  Photoshop::getInstance().AjouteImage(IImage);
  videTableImages();
  
  for(int i = 0; Photoshop::getInstance().getImageParIndice(i) != nullptr; i++)
  {
    Image *SelectionImage = Photoshop::getInstance().getImageParIndice(i);
    int Id = SelectionImage->getId();
    string Nom = SelectionImage->getNom();
    Dimension dimension = SelectionImage->getDimension();
    string ValeursDimension = to_string(dimension.getLargeur()) + "X" + to_string(dimension.getHauteur());

    string CategorieImage;

    if(dynamic_cast<ImageB*>(SelectionImage) != nullptr)
    {
        CategorieImage = "B";
        ImageB imageb;
        setImageB("selection", dynamic_cast<ImageB*>(Photoshop::getInstance().getImageParIndice(i)));
    }

    else if(dynamic_cast<ImageRGB*>(SelectionImage) != nullptr)
    {
        CategorieImage = "RGB";
        ImageRGB imagergb;
        setImageRGB("selection", dynamic_cast<ImageRGB*>(Photoshop::getInstance().getImageParIndice(i)));
    }

    else if(dynamic_cast<ImageNG*>(SelectionImage) != nullptr)
    {
        CategorieImage = "NG";
        ImageNG imageng;
        setImageNG("selection", dynamic_cast<ImageNG*>(Photoshop::getInstance().getImageParIndice(i)));
    }

    else
    {
      dialogueErreur("Erreur", "Désolé, mais aucune catégorie d'image n'a été sélectionnée");
    }

    ajouteTupleTableImages(Id, CategorieImage, ValeursDimension, Nom);

  }


}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionEnregistrer_ImageNB_triggered()
{
  // Etape 11 (TO DO)

  int Indice = getIndiceImageSelectionnee();

  if(Indice < 0)
  {
    dialogueErreur("Erreur","Désolé, mais aucune image n'a été sélectionée");
    return;
  }

  Image *image = Photoshop::getInstance().getImageParIndice(Indice);

  dynamic_cast <ImageNG*> (image);

  if(image == nullptr)
  {
    dialogueErreur("Erreur","Désolé, mais l'image chargée n'est pas une ImageRGB");
    return;
  }

  string NomEnregistrement = dialogueDemandeFichierEnregistrer("Sous quel nom souhaitez-vous enregistrer le fichier (exemple : test.bmp) ? => ");

  if(NomEnregistrement.empty())
  {
    dialogueMessage("Annulation","L'image n'est pas enregistrée");
    return;
  }

  string Format = dialogueDemandeTexte("Enregistrement du format", "Format à écrire comme ceci : jpg, png, bmp");
  
  if(Format.empty())
  {
    dialogueMessage("Annulation","Le format n'a pas été sélectionné");
    return;
  }  

  image->exportToFile(NomEnregistrement.c_str(), Format.c_str());

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionEnregistrer_ImageRGB_triggered()
{
  // Etape 11 (TO DO)

  int Indice = getIndiceImageSelectionnee();

  if(Indice < 0)
  {
    dialogueErreur("Erreur","Désolé, mais aucune image n'a été sélectionée");
    return;
  }

  Image *image = Photoshop::getInstance().getImageParIndice(Indice);

  dynamic_cast <ImageRGB*> (image);

  if(image == nullptr)
  {
    dialogueErreur("Erreur","Désolé, mais l'image chargée n'est pas une ImageRGB");
    return;
  }

  string NomEnregistrement = dialogueDemandeFichierEnregistrer("Sous quel nom souhaitez-vous enregistrer le fichier ? => ");

  if(NomEnregistrement.empty())
  {
    dialogueMessage("Annulation","L'image n'est pas enregistrée");
    return;
  }

  string Format = dialogueDemandeTexte("Enregistrement du format", "Format à écrire comme ceci : jpg, png, bmp");
  
  if(Format.empty())
  {
    dialogueMessage("Annulation","Le format n'a pas été sélectionné");
    return;
  }  

  image->exportToFile(NomEnregistrement.c_str(), Format.c_str());

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionEnregistrer_ImageB_triggered()
{
  // Etape 11 (TO DO)

  int Indice = getIndiceImageSelectionnee();

  if(Indice < 0)
  {
    dialogueErreur("Erreur","Désolé, mais aucune image n'a été sélectionée");
    return;
  }

  Image *image = Photoshop::getInstance().getImageParIndice(Indice);

  dynamic_cast <ImageB*> (image);

  if(image == nullptr)
  {
    dialogueErreur("Erreur","Désolé, mais l'image chargée n'est pas une ImageRGB");
    return;
  }

  string NomEnregistrement = dialogueDemandeFichierEnregistrer("Sous quel nom souhaitez-vous enregistrer le fichier ? => ");

  if(NomEnregistrement.empty())
  {
    dialogueMessage("Annulation","L'image n'est pas enregistrée");
    return;
  }

  string Format = dialogueDemandeTexte("Enregistrement du format", "Format à écrire comme ceci : jpg, png, bmp");
  
  if(Format.empty())
  {
    dialogueMessage("Annulation","Le format n'a pas été sélectionné");
    return;
  }  

  image->exportToFile(NomEnregistrement.c_str(), Format.c_str());

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionImage_selectionn_e_triggered()
{
  // Etape 11 (TO DO)

  int Indice = getIndiceImageSelectionnee();

  if(Indice < 0)
  {
    dialogueErreur("Erreur","Désolé, mais aucune image n'a été sélectionée");
    return;
  }

  Photoshop::getInstance().SupprimeImageParIndice(Indice);
  setNomImage("Vide");
  setParametresImageNG();
  setImageNG("selection");
  videTableImages();

  for(int i = 0; Photoshop::getInstance().getImageParIndice(i) != nullptr; i++)
  {
    Image *SelectionImage = Photoshop::getInstance().getImageParIndice(i);
    int Id = SelectionImage->getId();
    string Nom = SelectionImage->getNom();
    Dimension dimension = SelectionImage->getDimension();
    string ValeursDimension = to_string(dimension.getLargeur()) + "X" + to_string(dimension.getHauteur());

    string CategorieImage;

    if(dynamic_cast<ImageB*>(SelectionImage) != nullptr)
    {
        CategorieImage = "B";
    }

    else if(dynamic_cast<ImageRGB*>(SelectionImage) != nullptr)
    {
        CategorieImage = "RGB";
    }

    else if(dynamic_cast<ImageNG*>(SelectionImage) != nullptr)
    {
        CategorieImage = "NG";
    }

    else
    {
      dialogueErreur("Erreur", "Désolé, mais aucune catégorie d'image n'a été sélectionnée");
    }

    ajouteTupleTableImages(Id, CategorieImage, ValeursDimension, Nom);

  }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionImage_par_id_triggered()
{
  // Etape 11 (TO DO)
  int Indice = dialogueDemandeInt("Appui sur le bouton repéré !!!", "Selectionnez l'identifiant de l'image à supprimer : ");

  if(Indice < 0|| Photoshop::getInstance().getImageParId(Indice) == nullptr)
  {
    dialogueErreur("Erreur","Désolé, mais l'identifant n'est relié à aucune image");
    return;
  }

  Photoshop::getInstance().SupprimeImageParIndice(Indice);
  setNomImage("Vide");
  setParametresImageNG();
  setImageNG("selection");
  videTableImages();

  for(int i = 0; Photoshop::getInstance().getImageParIndice(i) != nullptr; i++)
  {
    Image *SelectionImage = Photoshop::getInstance().getImageParId(Indice);
    int Id = SelectionImage->getId();
    string Nom = SelectionImage->getNom();
    Dimension dimension = SelectionImage->getDimension();
    string ValeursDimension = to_string(dimension.getLargeur()) + "X" + to_string(dimension.getHauteur());

    string CategorieImage;

    if(dynamic_cast<ImageB*>(SelectionImage) != nullptr)
    {
        CategorieImage = "B";
    }

    else if(dynamic_cast<ImageRGB*>(SelectionImage) != nullptr)
    {
        CategorieImage = "RGB";
    }

    else if(dynamic_cast<ImageNG*>(SelectionImage) != nullptr)
    {
        CategorieImage = "NG";
    }

    else
    {
      dialogueErreur("Erreur", "Désolé, mais aucune catégorie d'image n'a été sélectionnée");
    }

    ajouteTupleTableImages(Id, CategorieImage, ValeursDimension, Nom);

  }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionCouleur_TRUE_pour_ImageB_triggered()
{
  // Etape 12 (TO DO)
  int Bleu, Rouge, Vert;

  dialogueDemandeCouleur("TRUE cliqué.Veuillez choisir une couleur pour l'image binaire", &Rouge, &Vert, &Bleu);

  Couleur couleur(Rouge, Vert, Bleu);

  ImageB::couleurTrue = couleur;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionCouleur_FALSE_pour_imageB_triggered()
{
  // Etape 12 (TO DO)

  int Bleu, Rouge, Vert;

  dialogueDemandeCouleur("FALSE cliqué Veuillez choisir une couleur pour l'image binaire", &Rouge, &Vert, &Bleu);

  Couleur couleur(Rouge, Vert, Bleu);

  ImageB::couleurFalse = couleur;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionImporterCSV_triggered()
{
    // Etape 13 (TO DO)

    string Fichier = dialogueDemandeFichierOuvrir("Nom du fichier à ouvrir");

    if(Fichier.empty())
    {
        dialogueErreur("Erreur", "Désolé, mais le fichier choisi est vide");
        return;
    }

    int Importation = Photoshop::getInstance().ImportationImage(Fichier);
    int i;

    videTableImages();

    for(i = 0; Photoshop::getInstance().getImageParIndice(i) != nullptr; i++)
    {
        Image *image = Photoshop::getInstance().getImageParIndice(i);

        int Indice = image->getId();
        string Nom = image->getNom();
        Dimension dimension = image->getDimension();
        string Dimensions = to_string(dimension.getLargeur()) + "X" + to_string(dimension.getHauteur());

        string CategorieImage;

        if(dynamic_cast<ImageNG*>(image) != nullptr)
        {
            CategorieImage = "NG";
        }

        else if(dynamic_cast<ImageRGB*>(image) != nullptr)
        {
            CategorieImage = "RGB";
        }

        else if(dynamic_cast<ImageB*>(image) != nullptr)
        {
            CategorieImage = "B";
        }

        ajouteTupleTableImages(Indice, CategorieImage, Dimensions, Nom);
    }

    string MessageImportation = "Les " + to_string(Importation) + " images ont été importées avec succès";
    dialogueMessage("Importation d'image(s)", MessageImportation.c_str());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionReset_triggered()
{
  // Etape 14 (TO DO)

  Photoshop::getInstance().Reset();

  Couleur Blanc(255,255,255);
  Couleur Noir(0,0,0);

  ImageB::couleurTrue = Blanc;
  ImageB::couleurFalse = Noir;

  videTableImages();
  setNomImage("");
  setParametresImageNG();
  setImageNG("selection");
  setImageNG("operande1");
  setImageNG("operande2");
  setImageNG("resultat");

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions selection sur la table des images ////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_tableWidgetImages_itemSelectionChanged()
{
  // Etape 11 (TO DO)

  int Indice = getIndiceImageSelectionnee();
  if(Indice < 0)
  {
    dialogueErreur("Erreur", "L'indice entré est invalide");
    return;
  }

  else
  {
    Image *Image = Photoshop::getInstance().getImageParIndice(Indice);

    if(ImageNG *imageNG = dynamic_cast<ImageNG*>(Image))
    {
      setParametresImageNG(imageNG->getMaximum(), imageNG->getMinimum(), imageNG->getLuminance(), imageNG->getContraste());
      setImageNG("selection", imageNG);
      string Nom = Image->getNom();
      setNomImage(Nom);
    }

    else if(ImageB *imageB = dynamic_cast<ImageB*>(Image))
    {
      setParametresImageNG();
      setImageB("selection", imageB);
      string Nom = Image->getNom();
      setNomImage(Nom);
    }

    else if(ImageRGB *imageRGB = dynamic_cast<ImageRGB*>(Image))
    {
      setParametresImageNG();
      setImageRGB("selection", imageRGB);
      string Nom = Image->getNom();
      setNomImage(Nom);
    }

    else
    {
      setImageB("selection");
      setImageNG("selection");
      setImageRGB("selection");
    }
  }

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions clics sur les boutons ////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_pushButtonModifierNom_clicked()
{
  // Etape 11 (TO DO)

  int Indice = getIndiceImageSelectionnee();

  cout << "Indice sélectionné: " << Indice << endl;
  if(Indice <= 0)
  {
    dialogueErreur("Erreur", "L'indice entré est invalide");
  }
  string ModificationNom = getNomImage();

  Image *IImage = Photoshop::getInstance().getImageParIndice(Indice);
  IImage->setNom(ModificationNom.c_str());

  videTableImages();

  for(int i = 0; Photoshop::getInstance().getImageParIndice(i) != nullptr; i++)
  {
    Image *SelectionImage = Photoshop::getInstance().getImageParIndice(i);
    int Id = SelectionImage->getId();
    string Nom = SelectionImage->getNom();
    Dimension dimension = SelectionImage->getDimension();
    string ValeursDimension = to_string(dimension.getLargeur()) + "X" + to_string(dimension.getHauteur());

    string CategorieImage;

    if(dynamic_cast<ImageB*>(SelectionImage) != nullptr)
    {
        CategorieImage = "B";
    }

    else if(dynamic_cast<ImageRGB*>(SelectionImage) != nullptr)
    {
        CategorieImage = "RGB";
    }

    else if(dynamic_cast<ImageNG*>(SelectionImage) != nullptr)
    {
        CategorieImage = "NG";
    }

    else
    {
      dialogueErreur("Erreur", "Désolé, mais aucune catégorie d'image n'a été sélectionnée");
    }

    ajouteTupleTableImages(Id, CategorieImage, ValeursDimension, Nom);

  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_pushButtonOperande1_clicked()
{
    // Etape 12 (TO DO)
    int Indice = getIndiceImageSelectionnee();

    if(Indice < 0)
    {
      dialogueErreur("Erreur", "Désolé, mais aucune image n'a été sélectionée");
      return;
    }

    Photoshop::Operande1 = Photoshop::getInstance().getImageParIndice(Indice);

    if(Photoshop::Operande1 == nullptr)
    {
      dialogueErreur("Erreur", "Désolé, mais l'image n'est pas pointée");
    }

    else
    {
      if(dynamic_cast<const ImageNG*>(Photoshop::Operande1) != nullptr)
      {
        setImageNG("operande1", dynamic_cast<const ImageNG*>(Photoshop::Operande1));
      }

      else if(dynamic_cast<const ImageRGB*>(Photoshop::Operande1) != nullptr)
      {
        setImageRGB("operande1", dynamic_cast<const ImageRGB*>(Photoshop::Operande1));
      }

      else if(dynamic_cast<const ImageB*>(Photoshop::Operande1) != nullptr)
      {
        setImageB("operande1", dynamic_cast<const ImageB*>(Photoshop::Operande1));
      }
    }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_pushButtonSupprimeOperande1_clicked()
{
    // Etape 12 (TO DO)
    Photoshop::Operande1 = nullptr;

    if(dynamic_cast<const ImageNG*>(Photoshop::Operande1) == nullptr)
      {
        setImageNG("operande1");
      }

      else if(dynamic_cast<const ImageRGB*>(Photoshop::Operande1) == nullptr)
      {
        setImageRGB("operande1");
      }

      else if(dynamic_cast<const ImageB*>(Photoshop::Operande1) == nullptr)
      {
        setImageB("operande1");
      }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_pushButtonOperande2_clicked()
{
    // Etape 12 (TO DO)
    int Indice = getIndiceImageSelectionnee();

    if(Indice < 0)
    {
      dialogueErreur("Erreur", "Désolé, mais aucune image n'a été sélectionée");
      return;
    }

    Photoshop::Operande2 = Photoshop::getInstance().getImageParIndice(Indice);

    if(Photoshop::Operande2 == nullptr)
    {
      dialogueErreur("Erreur", "Désolé, mais l'image n'est pas pointée");
      return;
    }

    else
    {
      if(dynamic_cast<const ImageNG*>(Photoshop::Operande2) != nullptr)
      {
        setImageNG("operande2", dynamic_cast<const ImageNG*>(Photoshop::Operande2));
      }

      else if(dynamic_cast<const ImageRGB*>(Photoshop::Operande2) != nullptr)
      {
        setImageRGB("operande2", dynamic_cast<const ImageRGB*>(Photoshop::Operande2));
      }

      else if(dynamic_cast<const ImageB*>(Photoshop::Operande2) != nullptr)
      {
        setImageB("operande2", dynamic_cast<const ImageB*>(Photoshop::Operande2));
      }
    }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_pushButtonSupprimerOperande2_clicked()
{
    // Etape 12 (TO DO)
    Photoshop::Operande2 = nullptr;

    if(dynamic_cast<const ImageNG*>(Photoshop::Operande2) == nullptr)
      {
        setImageNG("operande2");
      }

      else if(dynamic_cast<const ImageRGB*>(Photoshop::Operande2) == nullptr)
      {
        setImageRGB("operande2");
      }

      else if(dynamic_cast<const ImageB*>(Photoshop::Operande2) == nullptr)
      {
        setImageB("operande2");
      }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_pushButtonResultat_clicked()
{
    // Etape 12 (TO DO)
    if(dynamic_cast<ImageNG *>(Photoshop::Resultat) != nullptr)
    {
      Photoshop::getInstance().AjouteImage(dynamic_cast<ImageNG *>(Photoshop::Resultat));
    }

    else if(dynamic_cast<ImageRGB *>(Photoshop::Resultat) != nullptr)
    {
      Photoshop::getInstance().AjouteImage(dynamic_cast<ImageRGB *>(Photoshop::Resultat));
    }

    else if(dynamic_cast<ImageB *>(Photoshop::Resultat) != nullptr)
    {
      Photoshop::getInstance().AjouteImage(dynamic_cast<ImageB *>(Photoshop::Resultat));
    }

    videTableImages();

    for(int i = 0; Photoshop::getInstance().getImageParIndice(i) != nullptr; i++)
    {
      Image *image = Photoshop::getInstance().getImageParIndice(i);

      int Id;
      Id = image->getId();

      string Nom;
      Nom = image->getNom();

      Dimension dimension;
      dimension = image->getDimension();

      string Dimensions;
      Dimensions = to_string(dimension.getLargeur()) + "X" + to_string(dimension.getHauteur());

      string CategorieImage;

      if(dynamic_cast<ImageNG *>(image) != nullptr)
      {
        CategorieImage = "NG";
      }

      else if(dynamic_cast<ImageRGB *>(image) != nullptr)
      {
        CategorieImage = "RGB";
      }

      else if(dynamic_cast<ImageB *>(image) != nullptr)
      {
        CategorieImage = "B";
      }

      ajouteTupleTableImages(Id, CategorieImage, Dimensions, Nom);
    }

    Photoshop::Resultat = nullptr;
    setImageNG("resultat");
    setResultatBoolean();

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_pushButtonSupprimerResultat_clicked()
{
    // Etape 12 (TO DO)
    Photoshop::Resultat = nullptr;
    delete Photoshop::Resultat;

    setImageNG("resultat");
    setResultatBoolean();

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_pushButtonTraitement_clicked()
{
    // Etape 12 (TO DO)
    string ChoixTraitement = getTraitementSelectionne();

    if(Photoshop::Operande1 == nullptr || dynamic_cast<const ImageNG*>(Photoshop::Operande1) == nullptr)
    {

        dialogueErreur("Erreur", "Soit vous n'avez pas ajouté d'image à l'opérande 1, soit l'image choisie n'est pas une ImageNG");
        return;
    }

    ImageNG *imageng = dynamic_cast<ImageNG*>(Photoshop::Operande1);

    if(ChoixTraitement == "Eclaircir (++)")
    {
        int i = 100;
        ImageNG Bis = imageng->operator++(i);
        ImageNG *imageFinal = new ImageNG(Bis);
        Photoshop::Resultat = imageFinal;
        setImageNG("resultat", dynamic_cast<ImageNG*>(Photoshop::Resultat));
        setImageNG("selection", dynamic_cast<ImageNG*>(Photoshop::Resultat));
    }

    else if(ChoixTraitement == "Eclaircir (+ val)")
    {
        int Valeur = dialogueDemandeInt("Eclaircissement de l'image", "Veuillez entrez une valeur entière pour éclaircir l'image");
        ImageNG Bis = imageng->operator+(Valeur);
        ImageNG *imageFinal = new ImageNG(Bis);
        Photoshop::Resultat = imageFinal;
        setImageNG("resultat", dynamic_cast<ImageNG*>(Photoshop::Resultat));
        setImageNG("selection", dynamic_cast<ImageNG*>(Photoshop::Resultat));
    }

    else if(ChoixTraitement == "Assombrir (--)")
    {
        int i = -10;
        ImageNG Bis = imageng->operator--(i);
        ImageNG *imageFinal = new ImageNG(Bis);
        Photoshop::Resultat = imageFinal;
        setImageNG("resultat", dynamic_cast<ImageNG*>(Photoshop::Resultat));
        setImageNG("selection", dynamic_cast<ImageNG*>(Photoshop::Resultat));
    }

    else if(ChoixTraitement == "Assombrir (- val)")
    {
        int Valeur = dialogueDemandeInt("Assombrissement de l'image", "Veuillez entrez une valeur entière pour assombrir l'image");
        ImageNG Bis = imageng->operator-(Valeur);
        ImageNG *imageFinal = new ImageNG(Bis);
        Photoshop::Resultat = imageFinal;
        setImageNG("resultat", dynamic_cast<ImageNG*>(Photoshop::Resultat));
        setImageNG("selection", dynamic_cast<ImageNG*>(Photoshop::Resultat));
    }

    else if(ChoixTraitement == "Comparaison (==)")
    {
        if(Photoshop::Operande2 == nullptr || dynamic_cast<const ImageNG*>(Photoshop::Operande2) == nullptr)
        {

            dialogueErreur("Erreur", "Soit vous n'avez pas ajouté d'image à l'opérande 2, soit l'image choisie n'est pas une ImageNG");
            return;
        }

        ImageNG *imageng2 = dynamic_cast<ImageNG*>(Photoshop::Operande2);

        bool Temporaire;

        try
        {
            Temporaire = imageng->operator==(*imageng2);
        }

        catch(XYException &exception)
        {
            dialogueErreur("Erreur", "Désolé, mais les 2 images ne sont pas de la même dimension");
            return;
        }

        setResultatBoolean(Temporaire);
    }

    else if(ChoixTraitement == "Comparaison (>)")
    {
        if(Photoshop::Operande2 == nullptr || dynamic_cast<const ImageNG*>(Photoshop::Operande2) == nullptr)
        {

            dialogueErreur("Erreur", "Soit vous n'avez pas ajouté d'image à l'opérande 2, soit l'image choisie n'est pas une ImageNG");
            return;
        }

        ImageNG *imageng2 = dynamic_cast<ImageNG*>(Photoshop::Operande2);

        bool Temporaire;

        try
        {
            Temporaire = imageng->operator>(*imageng2);
        }

        catch(XYException &exception)
        {
            dialogueErreur("Erreur", "Désolé, mais les 2 images ne sont pas de la même dimension");
            return;
        }

        setResultatBoolean(Temporaire);   
    }

    else if(ChoixTraitement == "Comparaison (<)")
    {
        if(Photoshop::Operande2 == nullptr || dynamic_cast<const ImageNG*>(Photoshop::Operande2) == nullptr)
        {

            dialogueErreur("Erreur", "Soit vous n'avez pas ajouté d'image à l'opérande 2, soit l'image choisie n'est pas une ImageNG");
            return;
        }

        ImageNG *imageng2 = dynamic_cast<ImageNG*>(Photoshop::Operande2);

        bool Temporaire;

        try
        {
            Temporaire = imageng->operator<(*imageng2);
        }

        catch(XYException &exception)
        {
            dialogueErreur("Erreur", "Désolé, mais les 2 images ne sont pas de la même dimension");
            return;
        }

        setResultatBoolean(Temporaire);
    }

    else if(ChoixTraitement == "Différence")
    {
        if(Photoshop::Operande2 == nullptr || dynamic_cast<const ImageNG*>(Photoshop::Operande2) == nullptr)
        {

            dialogueErreur("Erreur", "Soit vous n'avez pas ajouté d'image à l'opérande 2, soit l'image choisie n'est pas une ImageNG");
            return;
        }

        ImageNG *imageng2 = dynamic_cast<ImageNG*>(Photoshop::Operande2);
        ImageNG Temporaire = imageng->operator-(*imageng2);
        ImageNG *imageFinal = new ImageNG(Temporaire);

        Photoshop::Resultat = imageFinal;
        setImageNG("resultat", dynamic_cast<ImageNG*>(Photoshop::Resultat));
        setImageNG("selection", dynamic_cast<ImageNG*>(Photoshop::Resultat));
    }

    else if(ChoixTraitement == "Seuillage")
    {
        
        int Valeur = dialogueDemandeInt("Seuillage", "Veuillez entrer une valeur entière pour effectuer un seuillage");

        if(Valeur < 0 || Valeur > 255)
        {
            dialogueErreur("Erreur", "Désolé, mais la valeur du seuillage doit être comprise entre 0 et 255");
            return;
        }

        ImageB Temporaire = Traitement::Seuillage(*imageng, Valeur);
        ImageB *imageFinal = new ImageB(Temporaire);
        Photoshop::Resultat = imageFinal;

        setImageB("resultat", dynamic_cast<ImageB*>(Photoshop::Resultat));
        setImageNG("selection", dynamic_cast<ImageNG*>(Photoshop::Resultat));
    }

    else if(ChoixTraitement == "Filtre médian")
    {
        int Valeur = dialogueDemandeInt("Filtre Médian", "Veuillez entrer une valeur entière pour effectuer un filtre médian");

        if(Valeur %2 == 0|| Valeur < 3)
        {
            dialogueErreur("Erreur", "Désolé, mais la valeur du filtre médian doit être un nombre impair entier et au moins égal à 3");
            return;
        }

        ImageNG Temporaire = Traitement::Median(*imageng, Valeur);
        ImageNG *imageFinal = new ImageNG(Temporaire);
        Photoshop::Resultat = imageFinal;

        setImageNG("resultat", dynamic_cast<ImageNG*>(Photoshop::Resultat));
        setImageNG("selection", dynamic_cast<ImageNG*>(Photoshop::Resultat));
    }

    else if(ChoixTraitement == "Filtre moyenneur")
    {
        int Valeur = dialogueDemandeInt("Filtre Moyenneur", "Veuillez entrer une valeur entière pour effectuer un filtre moyenneur");

        if(Valeur %2 == 0|| Valeur < 3)
        {
            dialogueErreur("Erreur", "Désolé, mais la valeur du filtre moyenneur doit être un nombre impair entier et au moins égal à 3");
            return;
        }

        ImageNG Temporaire = Traitement::Moyenneur(*imageng, Valeur);
        ImageNG *imageFinal = new ImageNG(Temporaire);
        Photoshop::Resultat = imageFinal;

        setImageNG("resultat", dynamic_cast<ImageNG*>(Photoshop::Resultat));
        setImageNG("selection", dynamic_cast<ImageNG*>(Photoshop::Resultat));
    }

    else if(ChoixTraitement == "Erosion")
    {
        int Valeur = dialogueDemandeInt("Erosion", "Veuillez entrer une valeur entière pour effectuer une érosion");

        if(Valeur %2 == 0|| Valeur < 3)
        {
            dialogueErreur("Erreur", "Désolé, mais la valeur de l'érosion doit être un nombre impair entier et au moins égal à 3");
            return;
        }

        ImageNG Temporaire = Traitement::Erosion(*imageng, Valeur);
        ImageNG *imageFinal = new ImageNG(Temporaire);
        Photoshop::Resultat = imageFinal;  

        setImageNG("resultat", dynamic_cast<ImageNG*>(Photoshop::Resultat));
        setImageNG("selection", dynamic_cast<ImageNG*>(Photoshop::Resultat));
    }

    else if(ChoixTraitement == "Dilatation")
    {
        int Valeur = dialogueDemandeInt("Dilatation", "Veuillez entrer une valeur entière pour effectuer une dilatation");

        if(Valeur %2 == 0|| Valeur < 3)
        {
            dialogueErreur("Erreur", "Désolé, mais la valeur de la dilatation doit être un nombre impair entier et au moins égal à 3");
            return;
        }

        ImageNG Temporaire = Traitement::Dilatation(*imageng, Valeur);
        ImageNG *imageFinal = new ImageNG(Temporaire);
        Photoshop::Resultat = imageFinal;

        setImageNG("resultat", dynamic_cast<ImageNG*>(Photoshop::Resultat));
        setImageNG("selection", dynamic_cast<ImageNG*>(Photoshop::Resultat));
    }

    else if(ChoixTraitement == "Négatif")
    {
        ImageNG Temporaire = Traitement::Negatif(*imageng);
        ImageNG *imageFinal = new ImageNG(Temporaire);
        Photoshop::Resultat = imageFinal;

        setImageNG("resultat", dynamic_cast<ImageNG*>(Photoshop::Resultat));
        setImageNG("selection", dynamic_cast<ImageNG*>(Photoshop::Resultat));
    }

}

bool MainWindowPhotoShop :: deleteSaveFile()
{
    const char *FichierSauvegarde = "SAVE.dat";

    if(remove(FichierSauvegarde) == 0)
    {
        return true;
    }

    else
    {
        return false;
    }
}
