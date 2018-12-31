/******************************************************************************
                           Catalogue  -
                        -------------------
    debut                :  Decembre 2018
    copyright            :  (C) 2018 par K. BOUZID et PY GENEST
    e-mail               :  kenza.bouzid@insa-lyon.fr
                            pierre-yves.genest@insa-lyon.fr
******************************************************************************/
//--------- Interface de la classe <Catalogue> (fichier Catalogue.h) ----------
#if ! defined ( Catalogue_H )
#define Catalogue_H

////////////////////////////////////////////////////////// Interfaces utilisees
#include <string>
#include <vector>

#include "TabTrajet.h"
#include "TrajetCompose.h"

using namespace std;
//------------------------------------------------------------------ Constantes
//----------------------------------------------------------------------- Types
// Enumeration pour les options de lecture de la methode LectureTrajet
typedef enum {  ACCEPTEE,	// Creation de trajet dans tous les cas
		REFUSEE,	// Pas de creation de trajet
		TRAJET_SIMPLE,	// Creation d'un trajet s'il est simple
		TRAJET_COMPOSE,	// Creation de trajet s'il est compose
		VILLE_DEPART,	// Creation de trajet si la ville de depart
				//	correspond
		VILLE_ARRIVEE,	// Creation de trajet si la ville d'arrivee 
				//	correspond
		VILLES		// Creation de trajet si la ville de depart et
				//	d'arrivee correspondent
	} OptionLecture;


//-----------------------------------------------------------------------------
// Rôle de la classe <Catalogue>
//Implemente le catalogue de trajets : mon mode d'affichage - les méthodes d'Ajout
// - la  Recherche de trajets ainsi que l'interface utilisateur
//-----------------------------------------------------------------------------
class Catalogue
{

//////////////////////////////////////////////////////////////////////// PUBLIC
public :
    //--------------------------------------------------- Methodes publiques --
    void AjoutSimple(void);
    // Mode d'emploi : Ajoute un trajet simple au catalogue à partir des infos
    //                 saisies par l'utilisateur dans le flux de sortie cin
    //                 avec vérificatin  des contraintes d'Ajout (doublons)


    void AjoutCompose(void);
    // Mode d'emploi : Ajoute un trajet simple au catalogue à partir des infos
    //                 saisies par l'utilisateur dans le flux de sortie cin
    // Contrat : l'utilisateur saisit les villes composant le trajet, vérification
    //           de la validité du trajet à la saisie


    void Rechercher(void);
    // Mode d'emploi : Recherche un trajet dans le catalogue à partir d'une ville
    //                 de départ et ville d'arrivé saisies par l'utilisateur,
    //                 utilisation du polymorphisme


    void RechercheAvancee(void);


    void RechercheEnProfondeur(char* Recherche, TrajetCompose* branche,
        TabTrajet* res);


    void MenuTrajet(void);
    // Mode d'emploi : implémente l'interface d'Ajout des trajets
    //


    void MenuCatalogue(void);
    // Mode d'emploi : implémente l'interface principale du catalogue
    
    
    void Ecriture(string nomFichier);
    // Mode d'emploi : 
    //


    void LectureTrajets();
    // Mode d'emploi :
    //	Implemente l'interface de lecture de trajets a partir d'un fichier.
    //	L'utilisateur devra choisir le fichier ainsi que les criteres de
    //		selections des trajets.
    // Contrat :
    //	Aucun contrat.


    //----------------------------------------------- Surcharge d'operateurs --
    //------------------------------------------ Constructeurs - Destructeur --
    Catalogue (void);
    // Mode d'emploi : constructeur vide
    //


    virtual ~Catalogue ( );
    // Mode d'emploi : destructeur vide- rien est alloué dynamiquement
    //


///////////////////////////////////////////////////////////////////////// PRIVE
protected :
    //--------------------------------------------------- Methodes protegees --
    //----------- Methodes de chargement des trajets par criteres
    void recupereTrajets ( ifstream & fichier, unsigned int nbTrajets );
    // Mode d'emploi :
    //	Recupere tous les trajets (simple et composes) stockes dans le fichier
    //	fichier : le fichier qui contient les trajets a recuperer
    //	nbTrajets : le nombre de trajets a recuperer
    // Contrat :
    //	Le fichier doit etre du bon format.
    //	nbTrajets doit etre dans les bornes des trajets que l'on peut recuperer
    //		dans le fichier.
    
    
    void recupereTrajetsType ( ifstream & fichier, unsigned int nbTrajets );
    // Mode d'emploi :
    //	Recupere tous les trajets du type (simple ou composes) specifie
    //		par l'utilisateur
    //	fichier : le fichier qui contient les trajets a recuperer
    //	nbTrajets : le nombre de trajets a recuperer
    // Contrat :
    //	Le fichier doit etre du bon format.
    //	nbTrajets doit etre dans les bornes des trajets que l'on peut recuperer
    //		dans le fichier.


    void recupereTrajetsVille ( ifstream & fichier, unsigned int nbTrajets );
    // Mode d'emploi :
    //	Recupere tous les trajets qui correspondent a la ville de depart/
    //		d'arrivee specifiees par l'utilisateur
    //	fichier : le fichier qui contient les trajets a recuperer
    //	nbTrajets : le nombre de trajets a recuperer
    // Contrat :
    //	Le fichier doit etre du bon format.
    //	nbTrajets doit etre dans les bornes des trajets que l'on peut recuperer
    //		dans le fichier.


    void recupereTrajetsIntervalle ( ifstream & fichier, unsigned int nbTrajets );
    // Mode d'emploi :
    //	Recupere tous les trajets dans l'intervalle specifie par l'utilisateur
    //	fichier : le fichier qui contient les trajets a recuperer
    //	nbTrajets : le nombre de trajets a recuperer
    // Contrat :
    //	Le fichier doit etre du bon format.
    //	nbTrajets doit etre dans les bornes des trajets que l'on peut recuperer
    //		dans le fichier.


    static Trajet * lectureTrajet ( ifstream & fichier,
    	OptionLecture optionLecture, string villeDepart = "",
	string villeArrivee = "" );
    // Mode d'emploi :
    //	Permet de lire un trajet dans le fichier et de creer un objet associe
    //		a ce trajet suivant l'option de lecture renseignee
    //	Le trajet qui est lu est celui qui se situe a la position du curseur
    //		dans le fichier. Le trajet est lu dans tous les cas.
    //	fichier : le fichier qui contient le trajet a recuperer.
    //	optionLecture : l'option de lecture sur le trajet (voir la description
    //		de l'enumeration en haut du fichier)
    //	villeDepart : specification de la ville de depart (uniquement pour
    //		VILLE_DEPART et VILLES).
    //	villeArrivee : specification de la ville d'arrivee (uniquement pour
    //		VILLE_ARRIVEE et VILLES)
    //	Trajet * : le pointeur vers le trajet cree. La destruction est a la
    //		charge du client.
    //		Si aucun trajet n'est cree (option non verifiese, on renvoie
    //			nullptr.
    // Contrat :
    //	Le format du fichier doit etre correct et contenir un trajet lisible a 
    //		la position du curseur.


    static void saisirTexte ( char * destination, unsigned int tailleMax );
    // Mode d'emploi
    //  Permet de saisir du texte a partir de l'entree standard, empeche
    //      l'utilisation des caracteres reserves a la sauvegarde (_)
    //  destination : la destination ou le texte sera stocke
    //  tailleMax : la taille maximale de l'entree
    // Contrat :
    //  Aucun contrat.


    static vector < string > decouperChaine ( string & chaine,
    	char separateur = '_' );
    // Mode d'emploi :
    //	Permet de decouper une chaine de caracteres en plusieurs morceaux, 
    //		suivant un caractere separateur.
    //	chaine : la chaine de caracteres a decouper. La chaine est modifiee
    //		pendant la methode, on supprime tous les caracteres
    //		non imprimables \n, \r ...
    //	separateur : le caractere qui separer les morceaux (il ne sera pas
    //		recopie)
    //	retour : un vecteur de string qui contient les informations decoupees.
    // Contrat :
    //	Aucun contrat.
    
    
    void freeTab(char ** tab , int size);
    // Mode d'emploi : permet de libérer les tableaux de chaines de caractères
    //		utilisée pour stocker les variables récupérées du flux cin


    //--------------------------------------------------- Attributs proteges --
    TabTrajet liste;
    // Tableau des trajets du catalogue
};

//------------------------------- Autres définitions dépendantes de <Catalogue>
#endif // Catalogue_H
