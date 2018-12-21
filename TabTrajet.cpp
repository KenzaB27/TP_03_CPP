/*************************************************************************
                           TabTrajet  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <TabTrajet> (fichier TabTrajet.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "TabTrajet.h"

//------------------------------------------------------------- Constantes
#define TAILLE 20
//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques


Trajet** TabTrajet::GetTabTrajet(void) const
{
  return trajet;
} //-- Fin GetTabTrajet

int TabTrajet::GetNbTrajets(void) const
{
  return nbTrajets;
} //-- Fin GetNbTrajets

void TabTrajet::Affichage(void) const
{
  if (nbTrajets == 0)
  {
    cout << "Le catalogue est vide!" << endl;
  }
  for (int i = 0; i < nbTrajets; i++)
	{
		trajet[i]->Affichage();
	}
} //-- Fin Affichage

void TabTrajet::AjouterTrajet(Trajet *t)
{
//Réallocation dynamique du tableau de pointeur de trajet si il est plein
if(nbAllocated == nbTrajets)
{
  #ifdef MAP
      cout << "Reallocation de la TabTrajet" << endl;
  #endif
		Trajet ** temp;
		nbAllocated += 30;
		temp = new Trajet *[nbAllocated];

		for (int i = 0; i < nbTrajets; i++) {
			temp[i] = trajet[i];
		}

    delete[] trajet;
    trajet = temp;
	}

  nbTrajets++;
	trajet[nbTrajets - 1] = t;
} //-- Fin AjouterTrajet

//-------------------------------------------- Constructeurs - destructeur

TabTrajet::TabTrajet (void)
{
#ifdef MAP
    cout << "Appel au constructeur de <TabTrajet>" << endl;
#endif
nbTrajets =0;
nbAllocated = TAILLE ;
trajet = new Trajet*[TAILLE];
} //----- Fin de TabTrajet

TabTrajet::~TabTrajet ( )
{
#ifdef MAP
    cout << "Appel au destructeur de <TabTrajet>" << endl;
#endif

	for (int i = 0; i < nbTrajets; i++)
	{
    if(trajet[i] != nullptr)
    {
      delete trajet[i];
      trajet[i] = nullptr;
    }
	}
  if( trajet != nullptr)
  {
    delete[] trajet;
    trajet = nullptr;
  }
} //----- Fin de ~TabTrajet

//----------------------------------------------------- Méthodes protégées
