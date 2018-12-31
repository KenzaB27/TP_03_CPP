/******************************************************************************
                           TabTrajet  -
                             -------------------
    debut                :  Decembre 2018
    copyright            :  (C) 2018 par K. BOUZID et PY GENEST
    e-mail               :  kenza.bouzid@insa-lyon.fr
              pierre-yves.genest@insa-lyon.fr
******************************************************************************/
//--------- Réalisation de la classe <TabTrajet> (fichier TabTrajet.cpp) ------

////////////////////////////////////////////////////////////////////// INCLUDES
//--------------------------------------------------------- Includes systeme --
#include <iostream>
#include <cstring>

using namespace std;

//------------------------------------------------------ Includes personnels --
#include "TabTrajet.h"
//------------------------------------------------------------------ CONSTANTES
const unsigned int TAILLE = 20;

//////////////////////////////////////////////////////////////////////// PUBLIC
//------------------------------------------------------- Methodes publiques --
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


bool TabTrajet::ExisteDeja ( const Trajet * t ) const
{
	char * t_S = t->toString();
	cout << " t : \"" << t_S << "\"" << endl; 

	for(int j = 0; j < nbTrajets; j++)
	{
		char * l_S = trajet[j]->toString();
		cout << " \"" << l_S << "\"" << endl;

		if(strcmp(t_S, l_S) == 0)
		{
			delete [] t_S;
			delete [] l_S;
			return true;
		}
		delete [] l_S;
	}
	
	delete [] t_S;
	return false;
} //--- Fin de ExisteDeja


//--------------------------------------------------- Surcharge d'operateurs --
//---------------------------------------------- Constructeurs - Destructeur --
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


///////////////////////////////////////////////////////////////////////// PRIVE
//------------------------------------------------------- Methodes protegees --
