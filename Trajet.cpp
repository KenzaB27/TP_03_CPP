/*************************************************************************
                           Trajet  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Trajet> (fichier Trajet.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <cstring>
using namespace std;
//------------------------------------------------------ Include personnel
#include "Trajet.h"
#include <cstring>
//------------------------------------------------------------------ CONSTANTES


//////////////////////////////////////////////////////////////////////// PUBLIC
//------------------------------------------------------- Methodes publiques --
void Trajet::Affichage(const char * c ) const
{
	cout << c << "De " << GetVilleDepart() << " a " << GetVilleArrive() << " ";
} //----- Fin de Affichage


bool Trajet::VerifVilleDepart(char *villeDepart)
{
	return strcmp(GetVilleDepart() , villeDepart); 
}//----- Fin de VerifVilleDepart


bool Trajet:: VerifVilleArrive(char *villeArrive)
{
	return strcmp(GetVilleArrive(), villeArrive);
}//----- Fin de VerifVilleArrive


//--------------------------------------------------- Surcharge d'operateurs --
//---------------------------------------------- Constructeurs - Destructeur --
Trajet::~Trajet()
{
#ifdef MAP
	cout << "Appel au destructeur de <Trajet>" << endl;
#endif
} //----- Fin de ~Trajet


///////////////////////////////////////////////////////////////////////// PRIVE
//------------------------------------------------------- Methodes protegees --
Trajet::Trajet()
{
#ifdef MAP
	cout << "Appel au constructeur de <Trajet>" << endl;
#endif
} //----- Fin de Trajet
