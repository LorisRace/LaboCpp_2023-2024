#include "Dimension.h"

	const Dimension Dimension :: VGA(640, 480);
	const Dimension Dimension :: HD (1280, 720);
	const Dimension Dimension :: FULL_HD(1920,1080);

	Dimension :: Dimension()
	{
		setLargeur(400);
		setHauteur(300);
	}

	Dimension :: Dimension(int largeur, int hauteur)
	{
		setLargeur(400);
		setHauteur(300);
	}

	Dimension :: Dimension (const Dimension &d)
	{

		setLargeur(d.getLargeur());
		setHauteur(d.getHauteur());

	}

	void Dimension :: setLargeur (int Val) 
	{
		if (Val < 0)
			exit (0);

		Largeur = Val;
	}

	int Dimension :: getLargeur()const
	{
		return Largeur;
	}

	void Dimension :: setHauteur (int Val) 
	{
		Hauteur = Val;
	}

	int Dimension :: getHauteur()const
	{
		return Hauteur;
	}

	void Dimension :: Affiche () const
	{
		cout << "Largeur : " <<Largeur<<endl;
		cout << "Hauteur : " <<Hauteur<<endl;
	}