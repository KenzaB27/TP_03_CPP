/******************************************************************************
  TrajetSimple  -
  -------------------
    debut                : 	Decembre 2018
    copyright            : 	(C) 2018 par K. BOUZID et PY GENEST
    e-mail               : 	kenza.bouzid@insa-lyon.fr
							pierre-yves.genest@insa-lyon.fr
******************************************************************************/
//---------- Réalisation de la classe <TrajetSimple> (fichier TrajetSimple.cpp)

////////////////////////////////////////////////////////////////////// INCLUDES
//--------------------------------------------------------- Includes systeme --
#include <iostream>
#include <cstring>
#include <ctype.h>

using namespace std;
//------------------------------------------------------ Includes personnels --
#include "TrajetSimple.h"
//------------------------------------------------------------------ CONSTANTES


//////////////////////////////////////////////////////////////////////// PUBLIC
//------------------------------------------------------- Methodes publiques --
void TrajetSimple::Affichage (const char* c) const
{
	   Trajet::Affichage("TS : ");
	   cout << "en "<< moyenTransport << endl;
	   cout << "\n";
} //----- Fin de Méthode


char* TrajetSimple::GetVilleDepart(void) const
{
	   return villeDepart;
} //----- Fin de GetVilleDepart


char* TrajetSimple::GetVilleArrive(void) const
{
	   return villeArrive;
} //----- Fin de GetVilleDepart


char* TrajetSimple::GetMoyenTransport(void) const
{
	   return moyenTransport;
} //----- Fin de Méthode


char * TrajetSimple::toString(void)
{
	   char * description = new char[100];
	   description[0]='\0';

	   //On passe aux majuscules pour eviter les problemes de casse
	   char * villeDepartUpper = toUpper ( villeDepart );
	   char * villeArriveUpper = toUpper ( villeArrive );
	   char * moyenTransportUpper = toUpper ( moyenTransport );

	   strcat(description, villeDepartUpper );
	   strcat(description, villeArriveUpper );
	   strcat(description, moyenTransportUpper );

	   delete[] villeDepartUpper;
	   delete[] villeArriveUpper;
	   delete[] moyenTransportUpper;

	   return description;
}//-- Fin toString


//--------------------------------------------------- Surcharge d'operateurs --
//---------------------------------------------- Constructeurs - Destructeur --
TrajetSimple::TrajetSimple ( const char* uneVilleDepart,
			 const char* uneVilleArrive,
			 const char* unMoyenTransport)
{
#ifdef MAP
	   cout << "Appel au constructeur de <TrajetSimple>" << endl;
#endif
	   //Allocation et copie des paramètres pour l'encapsulation
	   villeDepart = new char [strlen(uneVilleDepart)+1];
	   villeDepart = strcpy (villeDepart,uneVilleDepart);
	   villeArrive = new char [strlen(uneVilleArrive)+1];
	   villeArrive = strcpy (villeArrive,uneVilleArrive);
	   moyenTransport = new char [strlen(unMoyenTransport)+1];
	   moyenTransport = strcpy(moyenTransport, unMoyenTransport);
} //----- Fin de TrajetSimple


TrajetSimple::~TrajetSimple ( )
{
#ifdef MAP
	   cout << "Appel au destructeur de <TrajetSimple>" << endl;
#endif
	   if (villeDepart != nullptr)
	   {
			 delete[] villeDepart;
			 villeDepart = nullptr;
	   }
	   if (villeArrive != nullptr)
	   {
			 delete[] villeArrive;
			 villeArrive = nullptr;
	   }
	   if (moyenTransport != nullptr)
	   {
			 delete[] moyenTransport;
			 moyenTransport = nullptr;
	   }
} //----- Fin de ~TrajetSimple


///////////////////////////////////////////////////////////////////////// PRIVE
//------------------------------------------------------- Methodes protegees --
char * TrajetSimple::toUpper ( char * chaine )
{
	   unsigned int longueur = strlen ( chaine ) + 1;
	   char * chaineUpper = new char [ longueur ];

	   for ( unsigned int i = 0; i < longueur; i++ )
	   {
			 chaineUpper [ i ] = toupper ( chaine [ i ] );
	   }

	   return chaineUpper;
}//-- Fin de toUpper
