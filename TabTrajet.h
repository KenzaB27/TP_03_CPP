/*************************************************************************
                           TabTrajet  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <TabTrajet> (fichier TabTrajet.h) ----------
#if ! defined ( TabTrajet_H )
#define TabTrajet_H

//--------------------------------------------------- Interfaces utilisées
#include "Trajet.h"
#include <cstring>

//------------------------------------------------------------------------
// Rôle de la classe <TabTrajet>
//  Implémente un tableau dynamique de pointeur de trajet pour en stocker une liste
//  ordonnée par ordre d'ajout.
//------------------------------------------------------------------------

class TabTrajet
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

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
    //
//-------------------------------------------- Constructeurs - destructeur
    TabTrajet (void);
    // Mode d'emploi : Création d'une TabTrajet.
    //

    virtual ~TabTrajet ( );
    // Mode d'emploi : Libéraation mémoire de la TabTrajet et de ses attributs
    //

//------------------------------------------------------------------ PROTEGE

protected:
//----------------------------------------------------- Attributs protégés
  Trajet** trajet ;  //Liste de trajets
  int nbTrajets;    //Nombre de trajets dans le catalogue
  int nbAllocated; //Espace alloué
};

#endif // TabTrajet_H
