/*************************************************************************
                           TrajetSimple  -  description
                             -------------------
    début                : 23/11/18
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <TrajetSimple> (fichier TrajetSimple.h) ----
#if ! defined ( TrajetSimple_H )
#define TrajetSimple_H

//--------------------------------------------------- Interfaces utilisées
#include "Trajet.h"
//------------------------------------------------------------------------
// Rôle de la classe <TrajetSimple>
// Implemente un trajet direct entre une uneVilleDepart et uneVilleArrive
// avec unMoyenTransport.
//------------------------------------------------------------------------

class TrajetSimple : public Trajet
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    void Affichage (const char* c = "" ) const;
    // Mode d'emploi : AFfiche les caractéristiques du trajet
    //                 Redéfinition de Affichage de Trajet
    //                  char* c permet d'afficher un texte avec l'affichage
    // Contrat : Affichage est purement virtuelle dans Trajet
    //           Affichage doit donc etre redéfinie ici.

    char* GetMoyenTransport(void) const ;
    // Mode d'emploi : retourne le moyen de transport employé
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

    char * toString(void);
    // Mode d'emploi : Renvoi une description textuelle sorte d'ID du trajet
    //
    // Contrat : Aucun
    //

//-------------------------------------------- Constructeurs - destructeur

    TrajetSimple ( const char*  uneVilleDepart,
                   const char*  uneVilleArrive,
                   const char* unMoyenTransport);
    // Contrat : Aucun
    //

    virtual ~TrajetSimple ();

    // Contrat : Aucun
    //

//------------------------------------------------------------------ Protégé

protected:
//---------------------------------------------------------- Methodes protegees
	static char * toUpper ( char * chaine );
	// Mode d'emploi :
	//	Permet de creer une copie de la chaine de caractere qui est en
	//		majuscule.
	//	chaine : la chaine de caractere a copier en majuscule
	//	retour : copie de la chaine en entree, en majuscule.
	//			La suppression du pointeur est a la charge du client
	// Contrat :
	//	Format chaine de caractere en entree
	 
//---------------------------------------------------------- Attributs protégés
     char* villeDepart;
     char* villeArrive;
     char* moyenTransport;
};
//---------------------------- Autres définitions dépendantes de <TrajetSimple>

#endif // TrajetSimple_H
