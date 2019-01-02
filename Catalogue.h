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
// Enumeration pour les options de lecture et d'ecriture des methode
// LectureTrajet et EcritureTrajets
typedef enum {  ACCEPTEE,	// Creation de trajet dans tous les cas
		REFUSEE,	// Pas de creation de trajet
		SAUVEGARDE_COMPLETE,//Sauvegarde de tous les trajets du catalogue courant
		TRAJET_SIMPLE,	// Creation ou sauvegarde d'un trajet s'il est simple
		TRAJET_COMPOSE,	// Creation ou sauvegarde de trajet s'il est compose
		VILLE_DEPART,	// Creation ou sauvegarde de trajet si la ville de depart correspond
		VILLE_ARRIVEE,	// Creation ou sauvegarde de trajet si la ville d'arrivee correspond
		VILLES// Creation ou sauvegarde de trajet si la ville de depart et d'arrivee correspondent
	} OptionLecEcr;
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
    // Mode d'emploi : implémente l'interface principale du catalogue.


    void LectureTrajets();
    // Mode d'emploi :
    //	Implemente l'interface de lecture de trajets a partir d'un fichier.
    //	L'utilisateur devra choisir le fichier ainsi que les criteres de
    //		selections des trajets.
    // Contrat :
    //	Aucun contrat.


    void EcritureTrajets();
    // Mode d'emploi :
    //	Implemente l'interface d'écriture de trajets a partir du catalogue
    //  courant dans un fichier.
    //	L'utilisateur devra choisir le fichier de sauvegarde ainsi que les criteres
    //  d'écriture des trajets qu'ils souhaitent sauvegarder.
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
    //	nbTrajets : le nombre de trajets contenus dans le fichier
    // Contrat :
    //	Le fichier doit etre du bon format.
    //	nbTrajets doit etre dans les bornes des trajets que l'on peut recuperer
    //		dans le fichier.


    void recupereTrajetsType ( ifstream & fichier, unsigned int nbTrajets );
    // Mode d'emploi :
    //	Recupere tous les trajets du type (simple ou composes) specifie
    //		par l'utilisateur
    //	fichier : le fichier qui contient les trajets a recuperer
    //	nbTrajets : le nombre de trajets contenus dans le fichier
    // Contrat :
    //	Le fichier doit etre du bon format.
    //	nbTrajets doit etre dans les bornes des trajets que l'on peut recuperer
    //		dans le fichier.


    void recupereTrajetsVille ( ifstream & fichier, unsigned int nbTrajets );
    // Mode d'emploi :
    //	Recupere tous les trajets qui correspondent a la ville de depart/
    //		d'arrivee specifiees par l'utilisateur
    //	fichier : le fichier qui contient les trajets a recuperer
    //	nbTrajets : le nombre de trajets contenus dans le fichier
    // Contrat :
    //	Le fichier doit etre du bon format.
    //	nbTrajets doit etre dans les bornes des trajets que l'on peut recuperer
    //		dans le fichier.


    void recupereTrajetsIntervalle ( ifstream & fichier, unsigned int nbTrajets );
    // Mode d'emploi :
    //	Recupere tous les trajets dans l'intervalle specifie par l'utilisateur
    //	fichier : le fichier qui contient les trajets a recuperer
    //	nbTrajets : le nombre de trajets contenus dans le fichier
    // Contrat :
    //	Le fichier doit etre du bon format.
    //	nbTrajets doit etre dans les bornes des trajets que l'on peut recuperer
    //		dans le fichier.


    Trajet * lectureTrajet ( ifstream & fichier,
    	OptionLecEcr optionLecture, string villeDepart = "" ,
	string villeArrivee = "" );
    // Mode d'emploi :
    //	Permet de lire un trajet dans le fichier et de creer un objet associe
    //		a ce trajet suivant l'option de lecture renseignee
    //	Le trajet qui est lu est celui qui se situe a la position du curseur
    //		dans le fichier. Le trajet est lu dans tous les cas.
    //	fichier : le fichier qui contient le trajet a recuperer.
    //	OptionLecEcr : l'option de lecture sur le trajet (voir la description
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


    //----------- Methodes de sauvegarde des trajets par criteres
    void sauvegardeTrajets ( ofstream & fichier);
    // Mode d'emploi :
    //	Sauvegarde tous les trajets (simple et composes) du catalogue courant
    //	fichier : le fichier dans lequel la sauvegarde sera réalisée
    // Contrat :
    //	Le fichier doit etre vide, le cas échéant, son contenu sera écrasé
    //  pour laisser place à la nouvelle sauvegarde.


    void sauvegardeTrajetsType ( ofstream & fichier);
    // Mode d'emploi :
    //	Sauvegarde tous les trajets du type (simple ou composes) specifie
    //	par l'utilisateur
    //	fichier :  le fichier dans lequel la sauvegarde sera réalisée
    // Contrat :
    //	Le fichier doit etre vide, le cas échéant, son contenu sera écrasé
    //  pour laisser place à la nouvelle sauvegarde.


    void sauvegardeTrajetsVille ( ofstream & fichier);
    // Mode d'emploi :
    // Sauvegarde tous les trajets qui correspondent a la ville de depart/
    //		d'arrivee specifiees par l'utilisateur
    //	fichier :  le fichier dans lequel la sauvegarde sera réalisée
    // Contrat :
    //	Le fichier doit etre vide, le cas échéant, son contenu sera écrasé
    //  pour laisser place à la nouvelle sauvegarde.


    void sauvegardeTrajetsIntervalle ( ofstream & fichier);
    // Mode d'emploi :
    //	Sauvegarde tous les trajets dans l'intervalle specifie par l'utilisateur
    //	fichier :  le fichier dans lequel la sauvegarde sera réalisée
    // Contrat :
    //	Le fichier doit etre vide, le cas échéant, son contenu sera écrasé
    //  pour laisser place à la nouvelle sauvegarde.


    static bool ecritureTrajet (string description,
    	OptionLecEcr OptionEcriture, string villeDepart = "" ,
	string villeArrivee = "" );
    // Mode d'emploi :
    //	vérifie la conformité de la description passée en par avec l'option
		//  d'écriture choisie par l'utilisateur
    //	description : représente la description d'un trajet donné
    //	OptionEcriture : l'option d'écriture  dans le fichier (voir la description
    //		de l'enumeration en haut du fichier)
    //	villeDepart : specification de la ville de depart (uniquement pour
    //		VILLE_DEPART et VILLES).
    //	villeArrivee : specification de la ville d'arrivee (uniquement pour
    //		VILLE_ARRIVEE et VILLES).
    //	bool : retourne un bool qui indique la correspondance de la description aux critères
    // Contrat :
    //	Le fichier doit etre vide, le cas échéant, son contenu sera écrasé
    //  pour laisser place à la nouvelle sauvegarde.

void ecritureTrajetOption (ofstream & fichier , OptionLecEcr option,
	string villeDepart, string villeArrive , unsigned int debut ,
	unsigned int  borneBasse , unsigned int  borneHaute );
	// Mode d'emploi :
	//	permet d'ecrire dans le fichier de sauvegarde la descrpition
	// des différents trajets respectant l'option d'écriture pour la sélection
	// suivant une ville de départ et ou d'arrivée ou la sélection selon un
	// intervalle
	//	fichier :  le fichier dans lequel la sauvegarde sera réalisée
	//	OptionEcriture : l'option d'écriture  dans le fichier (voir la description
	//		de l'enumeration en haut du fichier)
	//	villeDepart : specification de la ville de depart (uniquement pour
	//		VILLE_DEPART et VILLES).
	//	villeArrivee : specification de la ville d'arrivee (uniquement pour
	//		VILLE_ARRIVEE et VILLES).
	//  borneBasse : la borne inférieure de l'intervalle de sélection
	//  borneHaute : la borne supérieure de l'intervalle de sélection
	//  debut : entier non signé representant le début de boucle = 0 pour
	//  critère de villes et =1 pour critère intervalle
	// Contrat :
	//	Le fichier doit etre vide, le cas échéant, son contenu sera écrasé
	//  pour laisser place à la nouvelle sauvegarde.

	void optionUtilisateur (string lecOuEcr , bool existeTS, 	bool existeTC ) ;
	 // Mode d'emploi : implémente l'interface des options d'écriture ou de
	 // lecture offertes à lutilisateur
	 //	lecOuEcr : un string qui précise s'il s'agit d'un chargement ou
	 // d'une sauvegarde
	 // existeTS : bool qui indique la presence ou non de trajet simple dans un
	 // fichier (le cas de lecture) ou dans un catalogue(cas d'ecriture),
	 // existeTC : bool qui indique la presence ou non de trajet composé dans un
	 // fichier (cas de lecture) ou dans un catalogue (cas d'ecriture),
	 // Contrat :
	 //	Aucun contrat.


	 OptionLecEcr optionType(string lecOuEcr ) ;
	 // Mode d'emploi : implémente l'interface des options d'écriture ou de
	 // lecture offertes à lutilisateur selon le type de trajets
	 //	lecOuEcr : un string qui précise s'il s'agit d'une récupération ou
	 // d'une sauvegarde
	 // OptionLecEcr : retourne l'option d'écriture ou  de lecture choisie
	 // par l'utilisateur
	 // Contrat :
	 //	Aucun contrat.

	 OptionLecEcr optionVille ( string lecOuEcr );
		// Mode d'emploi : implémente l'interface des options d'écriture ou de
		// lecture offertes à lutilisateur selon le choix des villes
		//	lecOuEcr : un string qui précise s'il s'agit d'une récupération ou
		// d'une sauvegarde
		// OptionLecEcr : retourne l'option d'écriture ou  de lecture choisie
		// par l'utilisateur
		// Contrat :
		//	Aucun contrat.

		void optionIntervalle ( string lecOuEcr, unsigned int & borneBasse ,
			 unsigned int & borneHaute , unsigned int nbTrajets) ;
		// Mode d'emploi : implémente l'interface des options d'écriture ou de
		// lecture offertes à lutilisateur selon le choix d'intervalle de sélection
		//	lecOuEcr : un string qui précise s'il s'agit d'une récupération ou
		// d'une sauvegarde
		// borneBasse: entier non signée pour récupérer la borne inférieure de
		// l'intervalle de sélection -- passage par référence
		// borneHaute: entier non signée pour récupérer la borne supérieure de
		// l'intervalle de sélection -- passage par référence
		//  nbTrajets: entier non signé représentant le nombre de trajets dans
		// le fichier de lecture ou dans le catalogue courant selon le cas
		// d'écriture ou de lecture
		// Contrat :
		//	Aucun contrat.


    static void saisirTexte ( char * destination, unsigned int tailleMax );
    // Mode d'emploi
    //  Permet de saisir du texte a partir de l'entree standard, empeche
    //      l'utilisation des caracteres reserves a la sauvegarde (_)
    //  destination : la destination ou le texte sera stocke
    //  tailleMax : la taille maximale de l'entree
    // Contrat :
    //  Aucun contrat.

    static void supprimerEspaceFin (string & chaine ) ;
		// Mode d'emploi :
		//	Supprime l'espace en fin de chaine s'il existe
		//	chaine : la chaine de caractere qui peut contenir un espace inutile
		//  à sa fin
		// Contrat :
		//	Aucun contrat.

    static void supprimerNonImprimable ( string & chaine );
    // Mode d'emploi :
    //	Supprime tous les caracteres non imprimables de la chaine de caractere
    //		fournie en entree. La chaine en entree est modifiee !
    //	chaine : la chaine de caractere qui contient les caracteres non
    //		imprimables.
    // Contrat :
    //	Aucun contrat.


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
		// Contrat :
    //	Aucun contrat.


    //--------------------------------------------------- Attributs proteges --
    TabTrajet liste;  // Tableau des trajets du catalogue

    bool presentTS ;  // booléen pour les tests d'existence des trajets simples
    		// dans le catalogue courant
    bool presentTC ; // booléen pour les tests d'existence des trajets composés
    		// dans le catalogue courant
};

//------------------------------- Autres définitions dépendantes de <Catalogue>
#endif // Catalogue_H
