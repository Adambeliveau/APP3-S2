/*
*   Voir fichier d'entête pour informations.
*   
*   $Author: bruc2001 $
*   $Date: 2018-02-13 08:54:36 -0500 (mar., 13 févr. 2018) $
*   $Revision: 108 $
*   $Id: MonInterface.cpp 108 2018-02-13 13:54:36Z bruc2001 $
*
*   Copyright 2013 Département de génie électrique et génie informatique
*                  Université de Sherbrooke  
*/
#include <QStyleFactory>
#include "MonInterface.h"
#include<cmath>
#include<fstream>


enum Registre { SW = 8, BTN = 9, LD = 10, AN0 = 11, AN1 = 12, AN2 = 13, AN3 = 14 };

using namespace std;

MonInterface::MonInterface(const char * theName) : VisiTest(theName)
{
	donnee.typeTest = 0;
	donnee.registreSW = SW;
	donnee.retourSW = 0;

	donnee.registreLD = LD;
	donnee.valeurLD = 0;

	donnee.etatLD = 0;
	donnee.etatSW = 0;

	resetTest();
	resetArchive();
	comm.estOk();
	test_courant = 0;
	isFile = true;
	isStarted = false;
	nb_test = 0;
	
}

void MonInterface::sauvegarder(char * nomFichier)
{
	if (!isStarted)
	{
		message("vous devez demarrer pour sauvegarder");
	}
	else
	{
		fstream file;
		file.open(nomFichier, ios_base::out);
		
		for (int i = 0; i < nb_test; i++)
		{
			file << myvecteur[i];
		}
		
		file.close();	
		message("sauvegarde effectuee avec succes");
	}
	
	
}

void MonInterface::demarrer()
{
	
	isStarted = true;
	message("Test demarre avec succes!");
}

void MonInterface::arreter()
{
	isStarted = false;
	message("Test arrete avec succes!");
}

void MonInterface::vider()
{
	resetTest();
	resetArchive();
	myvecteur.viderVecteur();
	nb_test = 0;
	test_courant = 0;
	message("Archive et test vide avec succes!");
}

void MonInterface::modeFile()
{
	if (!isStarted)
	{
		isPile = false;
		isFile = true;
		message("Mode file active avec succes!");
	}
	else
		message("Vous ne pouvez pas changer de mode si cest demarre");
}

void MonInterface::modePile()
{
	if (!isStarted)
	{
		isPile = true;
		isFile = false;
		message("Mode pile active avec succes!");
	}
	else
		message("Vous ne pouvez pas changer de mode si cest demarre");
}

void MonInterface::premier()
{
	if (myvecteur.getSize() != 0)
	{
		setArchive(myvecteur[0]);
		setArchive(1, nb_test);
	}
		
}

void MonInterface::dernier()
{
	if (myvecteur.getSize() != 0)
	{
		setArchive(myvecteur[nb_test-1]);
		setArchive(nb_test, nb_test);
	}
}

void MonInterface::precedent()
{
	if (myvecteur.getSize() != 0)
	{
		setArchive(--myvecteur);
		setArchive(myvecteur.getindex(), nb_test);
	}
}

void MonInterface::suivant()
{
	if (myvecteur.getSize() != 0)
	{
		setArchive(++myvecteur);
		setArchive(myvecteur.getindex(), nb_test);
	}
}

void MonInterface::ajouter(DonneesTest val)
{
	if (isPile)
	{
		myvecteur.add(val);
		message("Test ajoute au debut des archives");
	}
		
	else if (isFile)
	{
		myvecteur += val;
		message("Test ajoute a la fin des archives");
	}
		
}

void MonInterface::testSuivant()
{
	test_courant++;
	if (test_courant > 3)
		test_courant = 1;
	setTest(donnee);
	if(isStarted)
		nb_test++;
	
	if (test_courant == 1)
	{
		donnee.typeTest = 1;
		comm.lireRegistre(SW, donnee.retourSW);
		donnee.valeurLD = donnee.retourSW;
		comm.ecrireRegistre(LD, donnee.valeurLD);
		donnee.etatLD = donnee.valeurLD;
		donnee.etatSW = donnee.retourSW;
		setTest(donnee);
		if (isStarted)
		{
			setArchive(0, nb_test);
			ajouter(donnee);
		}
		

	}
	if (test_courant == 2)
	{
		donnee.typeTest = 2;
		int tempdonn = donnee.retourSW;
		int res = 0;
		for (int i = 7; i >= 0; i--)
		{
			int temp = res;
			if (donnee.retourSW - pow(2,i)>= 0 ? res++ : res = res);
			if (temp != res)
				donnee.retourSW -= pow(2, i);
		}
		donnee.retourSW = tempdonn;
		if (res % 2 == 0)
		{
			
			donnee.etatLD = 255;
			donnee.valeurLD = 255;

			comm.ecrireRegistre(LD, 255);
			setTest(donnee);
			
			if (isStarted)
			{
				setArchive(0, nb_test);
				ajouter(donnee);
			}
		}
		else
		{
			donnee.etatLD = 0;
			donnee.valeurLD = 0;
			
			comm.ecrireRegistre(LD, 0);
			setTest(donnee);
			
			if (isStarted)
			{
				setArchive(0, nb_test);
				ajouter(donnee);
			}
		}
	}
	if (test_courant == 3)
	{
		donnee.typeTest = 3;
		donnee.etatLD = 0;
		int NLC = log2(donnee.retourSW + 1);
		for (int i = 0; i < NLC; i++)
		{
			donnee.etatLD += pow(2, i);
		}
		comm.ecrireRegistre(LD, donnee.etatLD);
		donnee.valeurLD = donnee.etatLD;
		
		setTest(donnee);
		if (isStarted)
		{
			setArchive(0, nb_test);
			ajouter(donnee);
		}
	}
    
}

ostream& operator<<(ostream& os,DonneesTest&const donnAffiche)
{
	
	os << endl << "Type de Test : "<< donnAffiche.typeTest << endl 
		<< "RegistreSW : " << donnAffiche.registreSW << endl 
		<< "RetourSW : " << donnAffiche.retourSW << endl 
		<< "EtatSW : " << donnAffiche.etatSW << endl
		<< "RegistreLD : " << donnAffiche.registreLD << endl 
		<< "ValeurLD : " << donnAffiche.valeurLD << endl 
		<< "EtatLD : " << donnAffiche.etatLD << endl;
	return os;
}


