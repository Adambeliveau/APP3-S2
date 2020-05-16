/*
*   La classe MonInterface teste l'interface usager VisiTest (librairie).
*   
*   $Author: bruc2001 $
*   $Date: 2018-02-13 08:54:36 -0500 (mar., 13 févr. 2018) $
*   $Revision: 108 $
*   $Id: MonInterface.h 108 2018-02-13 13:54:36Z bruc2001 $
*
*   Copyright 2016 Département de génie électrique et génie informatique
*                  Université de Sherbrooke  
*/
#ifndef MONINTERFACE_H
#define MONINTERFACE_H

#include "VisiTest.h"
#include"CommunicationFPGA.h"
#include"vecteur.h"


class MonInterface : public VisiTest
{
public:
	MonInterface(const char *theName);
	void sauvegarder(char *nomFichier); 
public slots:
	virtual	void testSuivant();
	void demarrer();
	void arreter();
	void vider();
	void modeFile();
	void modePile();

	void premier();
	void dernier();
	void precedent();
	void suivant();

	void ajouter(DonneesTest val);

	friend ostream& operator<<(ostream& os, DonneesTest&const donnAffiche);
	
	


	
	
private:
	DonneesTest donnee;
	Vecteur<DonneesTest> myvecteur;
	bool isStarted;
	bool isFile;
	bool isPile;
	CommunicationFPGA comm;
	int nb_test;
	int test_courant;
	
};

#endif // MONINTERFACE_H