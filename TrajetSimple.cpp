#define _CRT_SECURE_NO_WARNINGS
/*************************************************************************
                           TrajetSimple  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <TrajetSimple> (fichier TrajetSimple.cpp)

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <cstring>
using namespace std;
//------------------------------------------------------ Include personnel
#include "TrajetSimple.h"

//----------------------------------------------------- Méthodes publiques

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
  strcat(description, villeDepart);
  strcat(description, villeArrive);
  strcat(description, moyenTransport);

  return description;
}//-- Fin toString


//-------------------------------------------- Constructeurs - destructeur

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
