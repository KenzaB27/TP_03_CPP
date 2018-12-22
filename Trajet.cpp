/******************************************************************************
                           Trajet  -
                             -------------------
    debut                : 	Decembre 2018
    copyright            : 	(C) 2018 par K. BOUZID et PY GENEST
    e-mail               : 	kenza.bouzid@insa-lyon.fr
							pierre-yves.genest@insa-lyon.fr
******************************************************************************/
//--------- Réalisation de la classe <Trajet> (fichier Trajet.cpp) ------------

////////////////////////////////////////////////////////////////////// INCLUDES
//--------------------------------------------------------- Includes systeme --
#include <iostream>
#include <cstring>
using namespace std;
//------------------------------------------------------ Includes personnels --
#include "Trajet.h"
#include <cstring>
//------------------------------------------------------------------ CONSTANTES


//////////////////////////////////////////////////////////////////////// PUBLIC
//------------------------------------------------------- Methodes publiques --
void Trajet::Affichage(const char * c ) const
{
	cout << c << "De " << GetVilleDepart() << " a " << GetVilleArrive() << " ";
} //----- Fin de Affichage


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