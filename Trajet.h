/*************************************************************************
                           Trajet  -  description
                             -------------------
    début                : 23/11/18
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Trajet> (fichier Trajet.h) ----------------
#if ! defined ( Trajet_H )
#define Trajet_H

//------------------------------------------------------------------------
// Rôle de la classe <Trajet>
// Implémente un trajet entre uneVilleDepart et uneVilleArrive
//
//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <cstring>
//------------------------------------------------------------------------


class Trajet
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    virtual void Affichage ( const char * c = "") const = 0;
    // Mode d'emploi : char* c permet d'afficher un texte avec l'affichage
    //
    // Contrat :
    // il s'agit d'un méthode virtuelle pure (=0) on définit ainsi une classe abstraite
	  // son constructeur est déclaré en protected pour bien eviter la création d'instances
	  // de trajet ce qui n'a aucun sens

    virtual char * GetVilleDepart (void) const = 0;
    // Mode d'emploi : Renvoi la ville de départ
    //
    // Contrat : Aucun
    //

    virtual char * GetVilleArrive(void) const = 0;
    // Mode d'emploi : Renvoi la ville d'arrivee
    //
    // Contrat : Aucun
    //

    virtual char* GetMoyenTransport(void) const = 0 ;
    // Mode d'emploi : retourne le moyen de transport employé
    //
    // Contrat : Aucun
    //

    virtual char * toString(void) = 0;
    // Mode d'emploi : Renvoi une description textuelle sorte d'ID du trajet
    //
    // Contrat : Aucun
    //
    
    virtual string DescriptionTrajet(void)=0 ; 
    // Mode d'emploi : 
    //
    // Contrat : Aucun
    //

    bool VerifVilleDepart(char * villeDepart); 
    // Mode d'emploi : 
    //
    // Contrat : Aucun
    //

    virtual string DescriptionTrajet(void)=0 ; 
    // Mode d'emploi : 
    //
    // Contrat : Aucun
    //


    bool VerifVilleDepart(char * villeDepart); 
    // Mode d'emploi : 
    //
    // Contrat : Aucun
    //


    bool VerifVilleArrive(char * villeArrive); 
    // Mode d'emploi : 
    //
    // Contrat : Aucun
    //


	//virtual bool Lecture ( );


    //----------------------------------------------- Surcharge d'operateurs --
    //------------------------------------------ Constructeurs - Destructeur --
    virtual ~Trajet ( );
    // Mode d'emploi : libère toutes les allocations dynamiques effectuées
    //
    // Contrat : Aucun
    //

//-------------------------------------------- Constructeurs - destructeur

    virtual ~Trajet ( );
    // Mode d'emploi : libère toutes les allocations dynamiques effectuées
    //
    // Contrat : Aucun
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
	Trajet();
	// Mode d'emploi :
	//
	// Contrat : constructeur protégé - interdicteion de création d'instance
  //           car classe abstraite
  //
//----------------------------------------------------- Attributs protégés
};

//-------------------------------- Autres définitions dépendantes de <Trajet>

#endif // Trajet_H
