#include "Couleur.h"
#include "MyQT.h"
#include <iostream>

const Couleur Couleur::BLEU(0, 0, 255);

const Couleur Couleur::ROUGE(255, 0, 0);

const Couleur Couleur::VERT(0, 255, 0);

const Couleur Couleur::BLANC(255, 255, 255);

const Couleur Couleur::NOIR(0, 0, 0);

Couleur :: Couleur()
{
	setBleu(0);
	setRouge(0);
	setVert(0);
}

Couleur :: Couleur(int rouge, int vert, int bleu)
{
	setBleu(bleu);
	setRouge(rouge);
	setVert(vert);
}

Couleur :: Couleur(const Couleur &couleur)
{

	Bleu = couleur.Bleu;

	Rouge = couleur.Rouge;

	Vert = couleur.Vert;
}

int Couleur :: getBleu()const
{
	return Bleu;
}

void Couleur :: setBleu(int val)
{
	if (val >= 0)
		Bleu = val;

	if (val < 0 || val > 255)
		throw RGBException("\nComposante bleue invalide !", val);
}

int Couleur :: getRouge()const
{
	return Rouge;
}

void Couleur :: setRouge(int val)
{
	if (val >= 0)
		Rouge = val;

	if (val < 0 || val > 255)
		throw RGBException("\nComposante rouge invalide !", val);
}

int Couleur :: getVert()const
{
	return Vert;
}

void Couleur :: setVert(int val)
{
	if (val >= 0)
		Vert = val;

	if (val < 0 || val > 255)
		throw RGBException("\nComposante verte invalide !", val);
}

std::ostream& operator<< (std::ostream &out,const Couleur &couleur)
{
	out <<"Bleu : " << couleur.getBleu() << std :: endl;
	out <<"Rouge : " << couleur.getRouge() << std :: endl;
	out <<"Vert : " << couleur.getVert() << std :: endl;

	return out;
}


void Couleur :: Affiche()const
{
	cout <<"Bleu : " << Bleu << endl;
	cout <<"Rouge : " << Rouge << endl;
	cout <<"Vert : " << Bleu << endl;

}

void Couleur :: Save(ofstream &fichier)const
{
	int bleu = getBleu();
	int rouge = getRouge();
	int vert = getVert();

	fichier.write((char *)&bleu, sizeof(int));
	fichier.write((char *)&rouge, sizeof(int));
	fichier.write((char *)&vert, sizeof(int));
}

void Couleur :: Load(ifstream &fichier)
{
	int bleu;
	int rouge;
	int vert;

	fichier.read((char *)&bleu, sizeof(int));
	fichier.read((char *)&rouge, sizeof(int));
	fichier.read((char *)&vert, sizeof(int));

	setBleu(bleu);
	setRouge(rouge);
	setVert(vert);
}









