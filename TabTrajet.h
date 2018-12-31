/******************************************************************************
                           TabTrajet  -
                             -------------------
    debut                :  Decembre 2018
    copyright            :  (C) 2018 par K. BOUZID et PY GENEST
    e-mail               :  kenza.bouzid@insa-lyon.fr
              pierre-yves.genest@insa-lyon.fr
******************************************************************************/
//--------- Interface de la classe <TabTrajet> (fichier TabTrajet.h) ----------
#if ! defined ( TabTrajet_H )
#define TabTrajet_H

////////////////////////////////////////////////////////// Interfaces utilisees
#include "Trajet.h"
//------------------------------------------------------------------ Constantes
//----------------------------------------------------------------------- Types


//-----------------------------------------------------------------------------
// Rôle de la classe <TabTrajet>
//  Implémente un tableau dynamique de pointeur de trajet pour en stocker une liste
//  ordonnée par ordre d'ajout.
//-----------------------------------------------------------------------------
class TabTrajet
{

//////////////////////////////////////////////////////////////////////// PUBLIC
public :
  //--------------------------------------------------- Methodes publiques --
  Trajet** GetTabTrajet(void) const;
  // Mode d'emploi : Renvoie le tableau de pointeur de trajets contenus dans TabTrajet
  //


  int GetNbTrajets(void) const;
  // Mode d'emploi : Renvoie le nombre de trajets pointés par la TabTrajet
  //


  void Affichage(void) const;
  // Mode d'emploi : Parcours le tableau de pointeur de trajet et appelle
  //                 leur méthode affichage


  void AjouterTrajet(Trajet *t);
  // Mode d'emploi : Ajoute *t au tableau de pointeur de trajets


  bool ExisteDeja ( const Trajet * t ) const;
  // Mode d'emploi:
  //	Verifie si le trajet en parametre est deja present dans le TabTrajet
  //	t : le trajet a comparer.
  //	retour : true si il existe deja un trajet identique
  //		false sinon.
  // Contrat:
  //	Aucun.


  //----------------------------------------------- Surcharge d'operateurs --
  //------------------------------------------ Constructeurs - Destructeur --
  TabTrajet (void);
  // Mode d'emploi : Création d'une TabTrajet.
  //


  virtual ~TabTrajet ( );
  // Mode d'emploi : Libéraation mémoire de la TabTrajet et de ses attributs
  //


///////////////////////////////////////////////////////////////////////// PRIVE
protected :
  //--------------------------------------------------- Methodes protegees --
  //--------------------------------------------------- Attributs proteges --
  Trajet** trajet ;  //Liste de trajets
  int nbTrajets;    //Nombre de trajets dans le catalogue
  int nbAllocated; //Espace alloué


};

#endif // TabTrajet_H
