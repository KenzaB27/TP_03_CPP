/******************************************************************************
                           TrajetCompose  -
                             -------------------
    debut                :  Decembre 2018
    copyright            :  (C) 2018 par K. BOUZID et PY GENEST
    e-mail               :  kenza.bouzid@insa-lyon.fr
                            pierre-yves.genest@insa-lyon.fr
******************************************************************************/
//----- Interface de la classe <TrajetCompose> (fichier TrajetCompose.h) ------
#if ! defined ( TrajetCompose_H )
#define TrajetCompose_H

////////////////////////////////////////////////////////// Interfaces utilisees
#include <string>
//------------------------------------------------------------------ Constantes
#include "Trajet.h"
#include "TabTrajet.h"
//----------------------------------------------------------------------- Types


//-----------------------------------------------------------------------------
// Rôle de la classe <TrajetCompose>
// Implémente un trajet compose de n trajets (éventuellement simple ou composé)
// reliant une ville de départ et une ville d'arrivé.
//-----------------------------------------------------------------------------
class TrajetCompose : public Trajet
{

//////////////////////////////////////////////////////////////////////// PUBLIC
public :
    //--------------------------------------------------- Methodes publiques --
    void Affichage (const char* c = "") const;
    // Mode d'emploi : Affiche les caractéristiques du trajet avec la 
    //  possibilité d'ajouter des specifications grace au char * c
    // Contrat : Redéfinition de la méthode virtuelle pure de la classe mère
    //  Trajet


    char * toString(void);
    // Mode d'emploi : Renvoi une description textuelle sorte d'ID du trajet
    //
    // Contrat : Aucun
    //


    TabTrajet* GetTab(void);
    // Mode d'emploi : Renvoie la TabTrajet de trajets constituant le trajet
    //  composé
    //
    // Contrat : Aucun
    //


    char * GetVilleArrive(void) const ;
    // Mode d'emploi : Renvoi la ville d'arrivee
    //
    // Contrat : Aucun
    //


    char * GetVilleDepart (void) const ;
    // Mode d'emploi : Renvoi la ville de départ
    //
    // Contrat : Aucun
    //


    char* GetMoyenTransport(void) const ;
    // Mode d'emploi : retourne le moyen de transport employé
    //
    // Contrat : Aucun
    //


    string DescriptionTrajet(void); 
    // Mode d'emploi :
    //
    // Contrat : Aucun
    //


    //----------------------------------------------- Surcharge d'operateurs --
    //------------------------------------------ Constructeurs - Destructeur --
    TrajetCompose (TabTrajet *s);
    // Mode d'emploi : définition des attributs des instances de trajet composé
    //                 à partir des paramètres formels du constructeur
    // Contrat : Aucun
    //


    virtual ~TrajetCompose ( );
    // Mode d'emploi : libère les allocations dynamiques réalisées
    //
    // Contrat : Aucun
    //


///////////////////////////////////////////////////////////////////////// PRIVE
protected :
    //--------------------------------------------------- Methodes protegees --
    //--------------------------------------------------- Attributs proteges --
    TabTrajet * tabTC;
    // Les trajets du trajet compose


};

//--------------------------- Autres définitions dépendantes de <TrajetCompose>

#endif // TrajetCompose_H
