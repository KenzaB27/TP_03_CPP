/******************************************************************************
  Catalogue  -
  -------------------
debut                : 	Decembre 2018
copyright            : 	(C) 2018 par K. BOUZID et PY GENEST
e-mail               : 	kenza.bouzid@insa-lyon.fr
pierre-yves.genest@insa-lyon.fr
 ******************************************************************************/
//--------- Réalisation de la classe <Catalogue> (fichier Catalogue.cpp) ------

////////////////////////////////////////////////////////////////////// INCLUDES
//--------------------------------------------------------- Includes systeme --
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
//------------------------------------------------------ Includes personnels --
#include "Catalogue.h"
#include "TabTrajet.h"
#include "Trajet.h"
#include "TrajetSimple.h"
#include "TrajetCompose.h"
//------------------------------------------------------------------ CONSTANTES
const unsigned int TAILLE_CHAR = 100;

//-------- initialisation des variables de classe

//////////////////////////////////////////////////////////////////////// PUBLIC
//------------------------------------------------------- Methodes publiques --
void Catalogue::RechercheEnProfondeur(char* Recherche, TrajetCompose* branche,
		TabTrajet* res)
{
	//Recherches des trajets non etudiés, pas dans le TC de la branche
	//	d'avant donc
	for(int i = 0; i < liste.GetNbTrajets(); i++)
	{
		bool used = false;
		for(int j = 0; j < branche->GetTab()->GetNbTrajets(); j++)
		{
			char * desBranche = branche->GetTab()->GetTabTrajet()[j]->toString();
			char * desCurr = liste.GetTabTrajet()[i]->toString();

			if(strcmp(desCurr, desBranche) == 0)
			{
				used = true;
				delete [] desBranche;
				delete [] desCurr;
				break;
			}
			delete [] desBranche;
			delete [] desCurr;
		}
		//On ne selectionne que les trajets restants et valides
		if(!used &&
				(strcmp(liste.GetTabTrajet()[i]->GetVilleDepart(), branche->GetVilleArrive()) == 0))
		{
			TabTrajet * temp_S = new TabTrajet();
			for(int k = 0; k < branche->GetTab()->GetNbTrajets(); k++)
			{
				temp_S->AjouterTrajet(branche->GetTab()->GetTabTrajet()[k]);
			}
			temp_S->AjouterTrajet(liste.GetTabTrajet()[i]);
			TrajetCompose* temp = new TrajetCompose(temp_S); //Creer une nouvelle branche a partir de l'ancienne
			res->AjouterTrajet(temp);


#ifdef MAP
			cout << "analyse POUSSEE trajet suivant:" << endl;
			liste.GetTabTrajet()[i]->Affichage();
			cout << endl;
			cout << "Construction branche :" << endl;
			temp->Affichage();
#endif


			if(strcmp(liste.GetTabTrajet()[i]->GetVilleArrive(), Recherche) == 0)
			{
				cout << "- Trajet :" << endl;
				temp->Affichage();
			}
			else{
				RechercheEnProfondeur(Recherche, temp, res);
				//On recommence le processus sur les trajets restants
			}
		}
	}
}


void Catalogue::RechercheAvancee()
{
	char depart [ TAILLE_CHAR ];
	char arrivee [ TAILLE_CHAR ];

	cout << "Bonjour, quelle est votre destination de depart ? " << endl;
	saisirTexte( depart, TAILLE_CHAR );
	cout << "Et votre ville d'arrivee" << endl;
	saisirTexte ( arrivee, TAILLE_CHAR );

	cout << "\n" << "\n" << "Resultats de la requete : " << endl;

	TabTrajet* resultats = new TabTrajet(); //On stocke toutes les branches parcourues

	for(int i = 0; i < liste.GetNbTrajets(); i++)
	{
		if(strcmp(liste.GetTabTrajet()[i]->GetVilleDepart(), depart) == 0)
			// On ne choisit que les trajets compatibles
		{

			TabTrajet *tabT (new TabTrajet());
			tabT->AjouterTrajet(liste.GetTabTrajet()[i]);

			//Creation de la 1ere branche
			TrajetCompose* temp = new TrajetCompose(tabT);
			resultats->AjouterTrajet(temp);

			if(strcmp(liste.GetTabTrajet()[i]->GetVilleArrive(), arrivee) == 0)
				//Si le trajet correspond on l'affiche
			{
				cout << "- Trajet :" << endl;
				liste.GetTabTrajet()[i]->Affichage("");
			}
			else{
				//Recursivité de la rechercche
				RechercheEnProfondeur(arrivee, temp, resultats);
			}
		}
	}
}


void Catalogue::AjoutSimple(void)
{
	char depart [TAILLE_CHAR];
	char arrivee [TAILLE_CHAR];
	char mt [TAILLE_CHAR];

	cout << "Quel est le depart du trajet" << endl;
	saisirTexte(depart, TAILLE_CHAR);
	cout << "Quelle est l'arrivee du trajet" << endl;
	saisirTexte(arrivee, TAILLE_CHAR);
	cout << "Quel est le moyen de transport employe ?" << endl;
	saisirTexte(mt, TAILLE_CHAR);

	TrajetSimple* t (new TrajetSimple(depart, arrivee, mt));


	if( ! liste.ExisteDeja ( t ) )
	{
		liste.AjouterTrajet(t);
		cout << "\n" << "Trajet Ajoute !" << endl;
	}
	else
	{
		cout << endl << "Trajet existant" << endl << endl;
		delete t;
	}

} //----- Fin de AjoutSimple


void Catalogue::AjoutCompose(void)
{
	int nbVilles = 0;
	cout << "Combien d'etapes comporte votre trajet " <<
		"(nombre de villes total)" << endl;

	while ( nbVilles <= 2 )
	{
		while( ! ( cin >> nbVilles) )
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Veuillez rentrer un nombre !" << endl;
		}
		cin.ignore();	//Probleme du \n avec cin >>

		if ( nbVilles <= 2 )
		{
			cout << "Erreur : Le nombre d'etapes minimum est 3 !"
				<< endl;
		}
	}

	char** tabVille (new char *[nbVilles]);
	char** tabMT (new char *[nbVilles]);
	TabTrajet *tabTS (new TabTrajet());
	for (int i = 0; i < nbVilles; i++)
	{
		cout << "Rentrer la " << (i+1) <<
			( ( i + 1 > 1 ) ? "eme" : "ere" )
			<< " ville : " << endl;
		tabVille[i] = new char[20];
		saisirTexte( tabVille[i], 20 );

		if(i != nbVilles - 1) tabMT[i]=new char[20];
		//On a moins de moyens de transport que de villes
		if (i != 0)
		{
			cout << "Quel est le moyen de transport entre " << tabVille[i - 1]
				<< " et " << tabVille[i] << " ?" << endl;
			saisirTexte( tabMT[i-1], 20 );
			//Le moyen de transport est stocke e l'adresse de la ville d'arrivee,
			// aucun moyen de transport en 0

			Trajet* t = new TrajetSimple(tabVille[i - 1], tabVille[i], tabMT[i-1]);
			tabTS->AjouterTrajet(t);
		}
	}

	TrajetCompose* tc(new TrajetCompose(tabTS));

	if( ! liste.ExisteDeja ( tc ) )
	{
		liste.AjouterTrajet(tc);
		cout << "\n" << "Trajet ajoute !" << endl;
	}
	else{
		cout << "\n" << "Trajet existant" << "\n" << endl;
		delete tc;
	}

	freeTab ( tabMT , nbVilles - 1 );
	freeTab ( tabVille , nbVilles ) ;
} //----- Fin de AjoutCompose


void Catalogue::Rechercher(void)
{
	char depart [TAILLE_CHAR];
	char arrivee[TAILLE_CHAR];
	int count = 0 ;
	cout << "Bonjour, quelle est votre destination de depart ? " << endl;
	saisirTexte( depart, TAILLE_CHAR );

	cout << "Et votre ville d'arrivee" << endl;
	saisirTexte( arrivee, TAILLE_CHAR );

	cout << "\n" << "\n" << "Resultats de la requete : " << endl;

	for (int i=0; i<liste.GetNbTrajets(); i++)
	{
		if (!strcmp(liste.GetTabTrajet()[i]->GetVilleDepart(), depart) &&
				!strcmp(liste.GetTabTrajet()[i]->GetVilleArrive(), arrivee))
		{
			cout << "Trajet : ", liste.GetTabTrajet()[i]->Affichage();
			count++;
		}
	}
	if ( count ==0)
	{
		cout << "Désolé, ce trajet n'est pas disponible!" << endl ;
	}

} //----- Fin de Rechercher


void Catalogue::MenuTrajet(void)
{
	int choix2 = 0;
	do
	{
		cout << "Quel est le type de trajet ?" << endl;
		cout << "1. Simple" << endl;
		cout << "2. Compose" << endl;
		cout << "3. Retour au Catalogue" << endl;

		while( !( cin >> choix2 ))
		{
			cin.clear();
			cin.ignore(1000,'\n');
			cout << "Veuillez saisir un chiffre !" << endl;
		}
		cin.ignore();

		switch (choix2)
		{
			case 1:
				cout << "Ajout d'un trajet simple" << endl;
				AjoutSimple();
				if (!presentTS)
				{
					presentTS=true ;
				}
				break;
			case 2:
				cout << "Ajout d'un trajet compose" << endl;
				AjoutCompose();
				if (!presentTC)
				{
					presentTC=true ;
				}
				break;
			case 3:
				break;
			default:
				cout << "Choix invalide. Attendu : 1-2-3" << endl;
				break;
		}
	} while (choix2 != 3);

} //----- Fin de MenuTrajet


void Catalogue::MenuCatalogue(void)
{
	int choix1 = 0;
	do
	{

		cout << endl << endl << "------Bienvenue sur FlexiTrip------"
			<< endl << endl;
		cout << "         Catalogue         " << endl;
		cout << "1. Ajouter un trajet" << endl;
		cout << "2. Afficher le catalogue de trajets proposes" << endl;
		cout << "3. Rechercher un parcours" << endl;
		cout << "4. Rechercher un parcours - Recherche avancee" << endl;
		cout << "5. Sauvegarder le catalogue dans un fichier" << endl;
		cout << "6. Recuperer des trajets a partir d'un fichier"
			<< endl;
		cout << "7. Quitter" << endl;

		while( !( cin >> choix1 ) )
		{
			cin.clear();
			cin.ignore(1000,'\n');
			cout << "Veuillez saisir un chiffre" << endl;
		}
		cin.ignore();

		switch (choix1)
		{
			case 1:
				cout << "*Ajout d'un trajet*" << endl;
				MenuTrajet();
				break;
			case 2:
				cout << "*------Catalogue-------*" << endl;
				liste.Affichage();
				break;
			case 3:
				cout << "*Recherche...*" << endl;
				Rechercher();
				break;
			case 4:
				cout << "4. Rechercher un parcours -"
					<< " Recherche avancee" << endl;
				RechercheAvancee();
				break;
			case 5:
				// Ecriture des trajets dans le fichier
				cout << endl << "Sauvegarde des trajets dans un fichier " << endl << endl;
				EcritureTrajets();
				break;
			case 6:
				// Lecture des trajets a partir d'un fichier
				cout << endl << "Lecture de trajets a partir"
					<< " d'un fichier" << endl << endl;
				LectureTrajets();
				break;
			case 7:
				break;
			default:
				cout << "Choix invalide. Attendu : 1-7" << endl;
				break;
		}

	} while (choix1 != 7);
}//----- Fin de mainCatalogue


void Catalogue::LectureTrajets()
{
	//--- Choix du fichier
	cout << "Chemin vers le fichier qui contient les trajets :" << endl;

	string source;
	getline(cin, source);	//getline pour les noms de fichier avec espaces
	supprimerEspaceFin (source);

	ifstream fichier;
	fichier.open(source, ios_base::in);

	//--- Verification de l'accessibilite du fichier
	if( !fichier )
	{
		cerr << "Le fichier n'est pas accessible !" << endl;
		fichier.close();
		return;
	}

	//--- Recuperation de l'entete
	string infos;
	getline(fichier, infos);

	vector < string > dec = Catalogue::decouperChaine ( infos );

	if ( dec.size() != 3 )
		//Format non respecte de l'entete
	{
		cout << "Le format du fichier n'est pas bon ou "
			<< "le fichier est vide" << endl;
		fichier.close();
		return;
	}
	int nbTrajets = stoi ( dec[0] );
	bool existeTS = stoi ( dec[1] );
	bool existeTC = stoi ( dec[2] );

	//Liste vide
	if( nbTrajets <= 0 )
	{
		cout << "Pas de trajets sauvegardes dans ce fichier !" << endl;
		fichier.close();
		return;
	}

	optionUtilisateur ("de chargement", existeTS , existeTC) ;

	bool choixJuste = false;
	int choix;
	while ( !choixJuste )
	{
		while ( !( cin >> choix ))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Veuillez rentrer un chiffre !" << endl;
		}

		switch( choix )
		{
			case 1:
				recupereTrajets ( fichier, nbTrajets );
				choixJuste = true;
				break;
			case 2:
				if( existeTC && existeTS )
				{
					recupereTrajetsType ( fichier,
						nbTrajets );
					choixJuste = true;
				}
				else
				{
					cout << "Choix invalide !" << endl;
				}
				break;
			case 3:
				recupereTrajetsVille ( fichier, nbTrajets );
				choixJuste = true;
				break;
			case 4:
				recupereTrajetsIntervalle ( fichier, nbTrajets );
				choixJuste = true;
				break;
			default:
				cout << "Choix invalide !" << endl;
				break;
		}
	}

	fichier.close();
}//----- Fin de LectureTrajets

void Catalogue::EcritureTrajets()
{
	// --- Vérifier si le catalogue est vide

	if ( liste.GetNbTrajets () == 0 )
	{
		cout <<"Le catalogue est vide, la sauvegarde est impossible!" << endl;
		return;
	}

	// --- Affichage des métadonnées afin de guider le choix de l'utilisateur
	cout << endl;
	cout << "Le catalogue courant contient " << liste.GetNbTrajets ();
	cout << " trajet" ;
  (liste.GetNbTrajets ()>1) ?	cout << "s." << endl : cout << "." << endl;
	cout << "Celui-ci contient " ;
	if (presentTC!=presentTS)
	{
		cout << "que " ;
	}
	if (presentTC)
	{
		 cout << "des trajets composés" ;
	}
	if (presentTC && presentTS )
	{
		cout << " et " ;
	}
	(presentTS)? cout << "des trajets simples." << endl : cout << "." << endl;


	//--- Choix du fichier
	cout << endl ;
	cout << "Veuillez saisir le chemin vers le fichier dans lequel vous "
			 << "souhaitez sauvegarder le catalogue courant :" << endl;

	string source;
	getline(cin, source);	//getline pour les noms de fichier avec espaces
  supprimerEspaceFin(source);

	ofstream fichier;
	fichier.open(source, ios::out | ios::trunc);
	//ouverture en écriture avec effacement du fichier ouvert

	//--- Verification de l'accessibilite du fichier
	if( !fichier )
	{
		cerr << "Le fichier n'est pas accessible !" << endl;
		fichier.close();
		return;
	}

	optionUtilisateur ("de sauvegarde", presentTS , presentTC);
	bool choixJuste = false;
	int choix;
	while ( !choixJuste )
	{
		while ( !( cin >> choix ))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Veuillez rentrer un chiffre !" << endl;
		}

		switch( choix )
		{
			case 1:
				sauvegardeTrajets (fichier);
				choixJuste = true;
				break;
			case 2:
				if( presentTC && presentTS )
				{
					sauvegardeTrajetsType (fichier);
					choixJuste = true;
				}
				else
				{
					cout << "Choix invalide !" << endl;
				}
				break;
			case 3:
				sauvegardeTrajetsVille (fichier);
				choixJuste = true;
				break;
			case 4:
				sauvegardeTrajetsIntervalle (fichier);
				choixJuste = true;
				break;
			default:
				cout << "Choix invalide !" << endl;
				break;
		}
	}

	fichier.close();
}//----- Fin de EcritureTrajets


//--------------------------------------------------- Surcharge d'operateurs --
//---------------------------------------------- Constructeurs - Destructeur --
Catalogue::Catalogue (void) : liste() , presentTS (false) , presentTC(false)
{
#ifdef MAP
	cout << "Appel au constructeur de <Catalogue>" << endl;
#endif
} //----- Fin de Catalogue


Catalogue::~Catalogue ()
{
#ifdef MAP
	cout << "Appel au destructeur de <Catalogue>" << endl;
#endif

} //----- Fin de ~Catalogue


///////////////////////////////////////////////////////////////////////// PRIVE
//------------------------------------------------------- Methodes protegees --

// -------- Méthodes de lecture ---------
void Catalogue::recupereTrajets ( ifstream & fichier, unsigned int nbTrajets )
{
	cout << endl;
	cout << "Recuperation de tous les trajets :" << endl;

	// On parcourt tous les trajets et on les ajoute si possible
	for ( unsigned int i = 0; i < nbTrajets && fichier.good() ; i++ )
	{
		Trajet * t = lectureTrajet ( fichier, ACCEPTEE );

		if ( t != nullptr && ! liste.ExisteDeja ( t ) )
		{
			liste.AjouterTrajet ( t );
			cout << "Ajout de : ";
			t->Affichage();
		}
		else
		{
			if( t != nullptr )
			{
				delete t;
			}
		}
	}
}//--- Fin de recupereTrajets


void Catalogue::recupereTrajetsType ( ifstream & fichier,
	unsigned int nbTrajets )
{
	OptionLecEcr option = optionType ("Recuperation" ) ;
	// On lit les trajets et on recupere ceux qui marchent
	//	(simple ou compose)
	for ( unsigned int i = 0; i < nbTrajets && fichier.good() ; i++ )
	{
		Trajet * t = lectureTrajet ( fichier, option );

		if ( t != nullptr && ! liste.ExisteDeja ( t ) )
		{
			liste.AjouterTrajet ( t );
			cout << "Ajout de : ";
			t->Affichage();
		}
		else
		{
			if( t != nullptr )
			{
				delete t;
			}
		}
	}

}//--- Fin de recupereTrajetsType


void Catalogue::recupereTrajetsVille ( ifstream & fichier,
	unsigned int nbTrajets )
{
	OptionLecEcr option =	optionVille ("Recuperation");

	// Villes de depart et d'arrivee
	char villeDepart [ TAILLE_CHAR ];
	villeDepart[0] = '\0';
	char villeArrivee[ TAILLE_CHAR ];
	villeArrivee[0] = '\0';

	if ( option == VILLE_DEPART || option == VILLES )
	{
		cout << "Ville de depart :" << endl;
		saisirTexte( villeDepart, TAILLE_CHAR );
	}

	if ( option == VILLE_ARRIVEE || option == VILLES )
	{
		cout << "Ville d'arrivee :" << endl;
		saisirTexte( villeArrivee, TAILLE_CHAR );
	}

	// On parcourt tous les trajets et on gardent ceux qui sont bons
	for ( unsigned int i = 0; i < nbTrajets && fichier.good(); i++ )
	{
		Trajet * t = lectureTrajet ( fichier, option, villeDepart,
			villeArrivee );

		if ( t != nullptr && ! liste.ExisteDeja ( t ) )
		{
			liste.AjouterTrajet ( t );
			cout << "Ajout de : ";
			t->Affichage();
		}
		else
		{
			if( t != nullptr )
			{
				delete t;
			}
		}
	}
}//--- Fin de recupereTrajetsVille


void Catalogue::recupereTrajetsIntervalle ( ifstream & fichier,
	unsigned int nbTrajets )
{
	unsigned int borneBasse = 0;
	unsigned int borneHaute = 0;
	optionIntervalle ( "Recuperation", borneBasse, borneHaute , nbTrajets);
	// On parcourt tous les trajets
	for ( unsigned int i = 1; i <= borneHaute && fichier.good(); i++ )
		//Les bornes de i sont decalees : le premier trajet doit avoir
		//	un indice de 1
	{
		if ( i >= borneBasse )
			// Dans les bornes : on sauvegarde
		{
			Trajet * t = lectureTrajet ( fichier, ACCEPTEE );

			if ( t != nullptr && ! liste.ExisteDeja ( t ) )
			{
				liste.AjouterTrajet ( t );
				cout << "Ajout de : ";
				t->Affichage();
			}
			else
			{
				if( t != nullptr )
				{
					delete t;
				}
			}
		}
		else	//Sinon on ignore
		{
			lectureTrajet ( fichier, REFUSEE );
		}
	}
}//--- Fin de recupereTrajetsIntervalle


Trajet * Catalogue::lectureTrajet ( ifstream & fichier,
	OptionLecEcr optionLecture, string villeDepart, string villeArrivee )
{
	// Dans tous les cas, on lit le trajet
	string chaineTrajet = "";
	getline(fichier, chaineTrajet);
	vector <string> params = decouperChaine ( chaineTrajet );

	if( ! fichier.good() || params.size() != 4 )	// Erreur de lecture
	{
		cerr << "Erreur de lecture du trajet !" << endl;
		return nullptr;
	}

	bool estCompose = params[ 0 ].compare ( "C" ) == 0;

	supprimerEspaceFin (villeDepart);
  supprimerEspaceFin (villeArrivee);

	// Comparaison des villes sans soucis de la casse des lettres
	char * vDepUpper = TrajetSimple::toUpper ( villeDepart.c_str() );
	char * paramsVDepUpper = TrajetSimple::toUpper ( params[1].c_str() );
	char * vArrUpper = TrajetSimple::toUpper ( villeArrivee.c_str() );
	char * paramsVArrUpper = TrajetSimple::toUpper ( params[2].c_str() );

	bool bonneVilleDepart = strcmp ( vDepUpper, paramsVDepUpper ) == 0;
	bool bonneVilleArrivee = strcmp ( vArrUpper, paramsVArrUpper ) == 0;

	delete[] vDepUpper;
	delete[] vArrUpper;
	delete[] paramsVDepUpper;
	delete[] paramsVArrUpper;

	// Gestion des differents cas
	if( estCompose )
	{
		int nbTrajets = stoi ( params [ 3 ] );

		if (	optionLecture == ACCEPTEE		||
			optionLecture == TRAJET_COMPOSE		||
			( optionLecture == VILLE_DEPART
				&& bonneVilleDepart )		||
			( optionLecture == VILLE_ARRIVEE
				&& bonneVilleArrivee )		||
			( optionLecture == VILLES
				&& bonneVilleDepart
				&& bonneVilleArrivee )
		   )	// Critere verifie = creation d'objet
		{
			TabTrajet * tab = new TabTrajet();

			for ( int i = 0; i < nbTrajets; i++)
			{

				Trajet *t = lectureTrajet ( fichier,
						ACCEPTEE );
				// On suppose que le trajet compose est
				//	correct (les villes de depart
				//	et d'arrivee correspondent bien
				//	entre chaque trajet)
				tab->AjouterTrajet ( t );
			}
			if ( !presentTC)
			{
				presentTC = true ;
			}
			return new TrajetCompose ( tab );
		}
		else	// Sinon on lit les trajets sans creer d'objet
		{
			for ( int i = 0; i < nbTrajets; i++)
			{
				lectureTrajet ( fichier,
					REFUSEE );
			}
			return nullptr;
		}
	}
	else
	{
		if (    optionLecture == ACCEPTEE		||
			optionLecture == TRAJET_SIMPLE		||
			( optionLecture == VILLE_DEPART
				&& bonneVilleDepart )		||
			( optionLecture == VILLE_ARRIVEE
				&& bonneVilleArrivee )		||
			( optionLecture == VILLES
				&& bonneVilleDepart
				&& bonneVilleArrivee )
		   )	// Critere verifie = creation d'objet
		{
			if ( !presentTS)
			{
				presentTS = true ;
			}
			return new TrajetSimple ( params[1].c_str(),
				params[2].c_str(), params[3].c_str());

		}
		else	// On ne cree pas d'objet
		{
			return nullptr;
		}

	}
}//--- Fin de lectureTrajet

// --------------Fin des méthodes de lecture ------------

// ------- Méthodes de sauvegarde ---------
void Catalogue::sauvegardeTrajets ( ofstream & fichier)
{
	cout << "Sauvegarde de tous les trajets :" << endl;
	fichier << liste.GetNbTrajets() << "_" << presentTS << "_" << presentTC << "\n";
	// On parcourt tous les trajets et on ajoute leur descrpition dans le fichier
	for ( unsigned int i = 0; i < (unsigned int)liste.GetNbTrajets()
	&& fichier.good(); i++ )
	{
		if (ecritureTrajet (liste.GetTabTrajet()[i]->DescriptionTrajet (),
		 								 		SAUVEGARDE_COMPLETE))
	 {
		 fichier << liste.GetTabTrajet()[i]->DescriptionTrajet();
	 }
	}
}//--- Fin de sauvegardeTrajets


void Catalogue::sauvegardeTrajetsType ( ofstream & fichier)
{
	OptionLecEcr option = optionType ("Sauvegarde") ;
	unsigned int compteur = 0 ; // compteur des trajets réellement sauvegardés
	string description= "" ;
	// On parcourt tous les trajets et on ajoute la descrpition dans le fichier
	// de ceux qui correspondent aux critères
	for ( unsigned int i = 0; i <(unsigned int) liste.GetNbTrajets()
	 && fichier.good() ; i++ )
	{
		if (ecritureTrajet (liste.GetTabTrajet()[i]->DescriptionTrajet (),
		 								 option))
		{
			compteur ++ ;
			description += liste.GetTabTrajet()[i]->DescriptionTrajet () ;
		}
	}
	if (!compteur)
	{
		cout << "Aucun trajet du catalogue ne correspond a vos criteres !" << endl ;
		return ;
	}
	bool existeTS = (option == TRAJET_SIMPLE )? 1 : 0  ;
	bool existeTC = (option == TRAJET_COMPOSE )? 1 : 0  ;
	fichier << compteur << "_" << existeTS << "_" << existeTC << endl ;
	fichier << description ;
}//--- Fin de sauvegardeTrajetsType


void Catalogue::sauvegardeTrajetsVille ( ofstream & fichier )
{
	OptionLecEcr option =	optionVille ( "Sauvegarde");

	// Villes de depart et d'arrivee
	char villeDepart [ TAILLE_CHAR ];
	villeDepart[0] = '\0';
	char villeArrivee[ TAILLE_CHAR ];
	villeArrivee[0] = '\0';

	if ( option == VILLE_DEPART || option == VILLES )
	{
		cout << "Ville de depart :" << endl;
		saisirTexte( villeDepart, TAILLE_CHAR );
	}

	if ( option == VILLE_ARRIVEE || option == VILLES )
	{
		cout << "Ville d'arrivee :" << endl;
		saisirTexte( villeArrivee, TAILLE_CHAR );
	}

	ecritureTrajetOption (fichier , option, villeDepart, villeArrivee,
  	0 , 0 ,(unsigned int)liste.GetNbTrajets());

}//--- Fin de sauvegardeTrajetsVille


void Catalogue::sauvegardeTrajetsIntervalle ( ofstream & fichier)
{
	unsigned int borneBasse = 0;
	unsigned int borneHaute = 0;
	optionIntervalle ( "Sauvegarde" , borneBasse , borneHaute ,
	(unsigned int)liste.GetNbTrajets());
	ecritureTrajetOption (fichier , SAUVEGARDE_COMPLETE , "", "" , 1 ,
	  borneBasse, borneHaute );

}//--- Fin de recupereTrajetsIntervalle


bool Catalogue::ecritureTrajet ( string description ,
	OptionLecEcr optionEcriture, string villeDepart, string villeArrivee )
{
	vector <string> params = decouperChaine (description);

	bool estCompose = params[ 0 ].compare ( "C" ) == 0;

	supprimerEspaceFin (villeDepart);
  supprimerEspaceFin (villeArrivee);
	// Comparaison des villes sans soucis de la casse des lettres
	char * vDepUpper = TrajetSimple::toUpper ( villeDepart.c_str() );
	char * paramsVDepUpper = TrajetSimple::toUpper ( params[1].c_str() );
	char * vArrUpper = TrajetSimple::toUpper ( villeArrivee.c_str() );
	char * paramsVArrUpper = TrajetSimple::toUpper ( params[2].c_str() );

	bool bonneVilleDepart = strcmp ( vDepUpper, paramsVDepUpper ) == 0;
	bool bonneVilleArrivee = strcmp ( vArrUpper, paramsVArrUpper ) == 0;

	delete[] vDepUpper;
	delete[] vArrUpper;
	delete[] paramsVDepUpper;
	delete[] paramsVArrUpper;

	// Gestion des differents cas
	if(estCompose)
	{
		if (optionEcriture == SAUVEGARDE_COMPLETE	||
				optionEcriture == TRAJET_COMPOSE	||
			 (optionEcriture == VILLE_DEPART && bonneVilleDepart ) ||
			 (optionEcriture == VILLE_ARRIVEE&& bonneVilleArrivee) ||
			 (optionEcriture == VILLES && bonneVilleDepart && bonneVilleArrivee )
		 )	// Critere verifie = ecriture dans le fichier
	 {
			return true;
	 }
	}
	else
	{
		if (optionEcriture ==  SAUVEGARDE_COMPLETE	||
				optionEcriture == TRAJET_SIMPLE	||
		 	 (optionEcriture == VILLE_DEPART && bonneVilleDepart ) ||
		   (optionEcriture == VILLE_ARRIVEE&& bonneVilleArrivee) ||
		   (optionEcriture == VILLES && bonneVilleDepart && bonneVilleArrivee )
		   )	// Critere verifie = creation d'objet
		{
			return true;
		}
	}
	return false;
}//--- Fin de ectritureTrajet


void Catalogue :: ecritureTrajetOption (ofstream & fichier , OptionLecEcr option,
	string villeDepart, string villeArrivee , unsigned int debut ,
	unsigned int  borneBasse , unsigned int  borneHaute )
{
	// variables relatifs à la composition des métadonnées
	unsigned int compteur = 0 ; // compteur des trajets réellement sauvegardés
	string description= "";
	bool existeTC = false ;
	bool existeTS = false ;

	for ( unsigned int i = debut; i < (borneHaute+debut) && fichier.good(); i++ )
		//Les bornes de i sont decalees : le premier trajet doit avoir
		//	un indice de 1
	{
		if ( i >= borneBasse )
			// Dans les bornes : on sauvegarde
		{
				if (ecritureTrajet (liste.GetTabTrajet()[i-debut]->DescriptionTrajet (),
												 option, villeDepart , villeArrivee))
				{
					// composition des métadonnées
					compteur ++ ;
					string descriptionTr = liste.GetTabTrajet()[i-debut]->DescriptionTrajet();
					vector <string> params = decouperChaine (descriptionTr);
					if ( !existeTS )
					{
						existeTS = params[ 0 ].compare ( "S" ) == 0;
					}
					if ( !existeTC )
					{
						existeTC = params[ 0 ].compare ( "C" ) == 0;
					}
					description += liste.GetTabTrajet()[i-debut]->DescriptionTrajet () ;
				}
			}
		}
			if (!compteur)
			{
				cout << "Aucun trajet du catalogue ne correspond a vos criteres !" << endl ;
				return ;
			}
			fichier << compteur << "_" << existeTS<< "_"	<<existeTC<< endl ;
			fichier << description ;

}// ------ Fin de ecritureTrajetOption

// --------------Fin des méthodes de sauvegarde ------------

//---- Méthodes interface utilisateur ------

void Catalogue::optionUtilisateur (string lecOuEcr , bool existeTS , bool existeTC)
{
	//--- Options pour l'utilisateur
	cout << "Choisissez l'option pour "<<lecOuEcr<<" des trajets :" << endl;
	cout << "1. Tous les trajets" << endl;
	if( existeTC && existeTS )
	{
		cout << "2. Selon le type de trajet" << endl;
	}
	cout << "3. Selon la ville de depart/d'arrivee" << endl;
	cout << "4. Selon un intervalle de trajets" << endl;
	cout << "Votre choix :" << endl;
}// ----- Fin de optionUtilisateur


OptionLecEcr Catalogue::optionType(string lecOuEcr )
{
	int choix=0;
	cout << endl;
	cout << lecOuEcr <<" de tous les trajets en fonction du type :"	<< endl;
	cout << "Saisissez le type de trajet" << endl;
	cout << "1. Trajets simples" << endl;
	cout << "2. Trajets composes" << endl;

	while ( ! ( cin >> choix ) || ( choix != 1 && choix != 2 ) )
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Saisissez un chiffre entre 1 et 2 !" << endl;
	}
	OptionLecEcr option = ( choix == 1 ) ? TRAJET_SIMPLE : TRAJET_COMPOSE;
	return option ;
}// ----- Fin de optionType


OptionLecEcr Catalogue::optionVille ( string lecOuEcr)
{
	cout << endl ;
	cout << lecOuEcr << " du trajet en fonction des villes de depart"
		<< " et d'arrivee" << endl;
	cout << "Saisissez le critere sur les villes de depart et d'arrivee"
		<< endl;
	cout << "1. Ville de depart uniquement" << endl;
	cout << "2. Ville d'arrivee uniquement" << endl;
	cout << "3. Ville de depart et d'arrivee" << endl;

	// Recuperation du choix
	int choix = 0;
	while ( ! ( cin >> choix ) || choix < 1 || choix > 3 )
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Saisissez un chiffre entre 1 et 3 !" << endl;
	}
	cin.ignore();	//On elimine de '\n'

	// Parametre de lecture du trajet
	OptionLecEcr option = REFUSEE;
	switch ( choix )
	{
		case 1:
			option = VILLE_DEPART;
			break;
		case 2:
			option = VILLE_ARRIVEE;
			break;
		case 3:
			option = VILLES;
			break;
		}
	 return option ;

}// ------- Fin de optionVille


void Catalogue::optionIntervalle ( string lecOuEcr, unsigned int & borneBasse ,
	 unsigned int & borneHaute , unsigned int nbTrajets)
{
cout << lecOuEcr << " des trajets suivant un intervalle" << endl;
cout << "Saisissez des nombres entre 1 et " << nbTrajets << endl;
// Borne du bas
cout << "Borne basse :" << endl;
while ( !( cin >> borneBasse )
	|| borneBasse < 1 || borneBasse > nbTrajets )
{
	cin.clear();
	cin.ignore ( 1000, '\n' );
	cout << "Saisissez des nombres entre 1 et " << nbTrajets
		<< " !" << endl;
}

// Borne du haut
cout << "Borne haute entre " << borneBasse << " et " << nbTrajets
	<< endl;
while ( !( cin >> borneHaute )
	|| borneHaute < borneBasse || borneHaute > nbTrajets )
{
	cin.clear();
	cin.ignore ( 1000, '\n' );
	cout << "Saisissez un nombre entre " << borneBasse << " et "
		<< nbTrajets << " !" << endl;
}
cin.ignore();	// On supprime le '\n' pour les lectures suivantes

}// ----- Fin de optionIntervalle

// --------------Fin des méthodes d'inteerface utilisateur------------

// -------- Autres méthodes ----------
void Catalogue::freeTab ( char ** tab , int size )
{
	for ( int i = 0 ; i<size ; i++ )
	{
		delete[] tab[i] ;
	}
	delete [] tab ;
}//----- Fin de freeTab


void Catalogue::saisirTexte ( char * destination, unsigned int tailleMax )
{
	bool saisieJuste = false;
	char * c;
	do
	{
		cin.getline( destination, tailleMax );

		for ( c = destination; *c != '\0' && *c!='_'; c++ );

		if(*c=='\0')
		{
			saisieJuste = true;
		}
		else
		{
			cout << "Le caractere '_' est interdit !" << endl;
		}
	} while ( !saisieJuste );

}//--- Fin de saisirTexte


void Catalogue::supprimerEspaceFin (string & chaine )
{
	string::iterator end = chaine.end() ;
	end--;
	if (*end == ' ')
	{
		chaine.erase(end);
	}
}//--- Fin de supprimerEspaceFin


void Catalogue::supprimerNonImprimable ( string & chaine )
{
	for ( string::iterator i = chaine.begin(); i <= chaine.end(); ++i )
	{
		if( *i != '\0' && ( ! isprint ( *i ) || *i < 0 ) )
		// On verifie que *i n'est pas le caractere de fin de chaine
		// ( non imprimable, mais attendu )
		{
			chaine.erase ( i - chaine.begin() );
			--i;
		}
	}
}//----Fin de supprimerNonImprimable


vector < string > Catalogue::decouperChaine ( string & chaine,
		char separateur )
{
	vector < string > decoupage;
	supprimerNonImprimable ( chaine );
	supprimerEspaceFin (chaine);
	string::iterator precCopieIterateur = chaine.begin();

	for ( string::iterator i = chaine.begin(); i <= chaine.end(); ++i)
	{
		if ( *i == separateur)
		{
			decoupage.emplace_back ( precCopieIterateur, i );
			precCopieIterateur = i + 1;//On saute le separateur
		}

	}

	//Pour le dernier decoupage au besoin
	if ( precCopieIterateur < chaine.end() )
	{
		decoupage.emplace_back ( precCopieIterateur, chaine.end() );
	}

	return decoupage;	//On ne peut pas renvoyer de reference
}//---- Fin de decouperChaine

// --------------Fin des autres méthodes ------------
