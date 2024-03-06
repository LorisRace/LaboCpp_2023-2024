#include "Dimension.h"
#include "MyQT.h"
#include <iostream>

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
		setLargeur(largeur);
		setHauteur(hauteur);
	}

	Dimension :: Dimension (const Dimension &d)
	{

		setLargeur(d.getLargeur());
		setHauteur(d.getHauteur());

	}

	void Dimension :: setLargeur (int Val) 
	{
		
		if (Val <= 0)
			throw XYException("\nLargeur invalide !", Val);
			
		if(Val > 0)
			Largeur = Val;
		
	}

	int Dimension :: getLargeur()const
	{
		if(Largeur <= 0 || Largeur >= 700)
		{
			throw XYException("\nLargeur invalide !", Hauteur);
		}
		return Largeur;
	}

	void Dimension :: setHauteur (int Val) 
	{
		
		if (Val <= 0)
			throw XYException("\nLargeur invalide !", Val);
		

		if(Val > 0)
			Hauteur = Val;

		
	}

	int Dimension :: getHauteur()const
	{
		if(Hauteur <= 0 || Hauteur >= 700)
		{
			throw XYException("\nLargeur invalide !", Hauteur);
		}

		return Hauteur;
	}

	void Dimension :: Affiche () const
	{
		cout << "Largeur : " <<Largeur<<endl;
		cout << "Hauteur : " <<Hauteur<<endl;
	}

	std::ostream& operator<<(std::ostream& out,const Dimension &d)
	{

		out<< "Largeur : " << d.getLargeur() <<std :: endl;
		out<< "Hauteur : " << d.getHauteur() <<std :: endl;
		return out;
	}

	std::istream& operator>> (std::istream& in, Dimension &d)
	{
		int temporaire_A, temporaire_B;

		cout << "Largeur : ";
		fflush(stdin);
		cin >> temporaire_A;

		cout << "Hauteur : ";
		fflush(stdin);
		cin >> temporaire_B;


		if(temporaire_A < 0 || temporaire_A > 700)
		{
			throw XYException("\nLargeur invalide !", temporaire_A);
		}

		if(temporaire_B < 0 || temporaire_B > 700)
		{
			throw XYException("\nLargeur invalide !", temporaire_B);
		}

		d.setLargeur(temporaire_A);
		d.setHauteur(temporaire_B);

		return in;	
	}

	bool Dimension:: operator==(const Dimension &d)
	{
		return (getLargeur() == d.getLargeur()) && (getHauteur() == d.getHauteur());
	}

	bool Dimension:: operator!=(const Dimension &d)
	{
		return (getLargeur() != d.getLargeur()) || (getHauteur() != d.getHauteur());
	}

	void Dimension :: Save(ofstream &fichier)const
	{
		int LLargeur = getLargeur();
		int HHauteur = getHauteur();

		fichier.write((char *)&LLargeur, sizeof(int));
		fichier.write((char *)&HHauteur, sizeof(int));
	}

	void Dimension :: Load(ifstream &fichier)
	{
		int LLargeur;
		int HHauteur;

		fichier.read((char *)&LLargeur, sizeof(int));
		fichier.read((char *)&HHauteur, sizeof(int));

		setLargeur(LLargeur);
		setHauteur(HHauteur);
	}