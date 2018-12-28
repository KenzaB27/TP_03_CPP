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
#include <queue>

using namespace std;
//------------------------------------------------------ Includes personnels --
#include "Catalogue.h"
#include "TabTrajet.h"
#include "Trajet.h"
#include "TrajetSimple.h"
#include "TrajetCompose.h"
//------------------------------------------------------------------ CONSTANTES
const unsigned int TAILLE_CHAR = 100;

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

	bool used = false;
	for(int j = 0; j < liste.GetNbTrajets(); j++)
	{
		char * t_S =t->toString();
		char * l_S = liste.GetTabTrajet()[j]->toString();

		if(strcmp(t_S, l_S) == 0)
		{
			used = true;
			cout << "\n" << "Trajet existant" << "\n" << endl;
			delete [] t_S;
			delete [] l_S;
			break;
		}
		delete [] t_S;
		delete [] l_S;
	}

	if(used == false)
	{
		liste.AjouterTrajet(t);
		cout << "\n" << "Trajet Ajoute !" << endl;
	}
	else
	{
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

	bool used = false;
	for(int j = 0; j < liste.GetNbTrajets(); j++)
	{
		char * t_S =tc->toString();
		char * l_S = liste.GetTabTrajet()[j]->toString();

		if(strcmp(t_S, l_S) == 0)
		{
			used = true;
			cout << "\n" << "Trajet existant" << "\n" << endl;
			delete [] t_S;
			delete [] l_S;
			break;
		}
		delete [] t_S;
		delete [] l_S;
	}
	if(!used)
	{
		liste.AjouterTrajet(tc);
		cout << "\n" << "Trajet ajoute !" << endl;
	}
	else{
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


void Catalogue::MenuTrajet(void) {
	do
	{
		cout << "Quel est le type de trajet ?" << endl;
		cout << "1. Simple" << endl;
		cout << "2. Compose" << endl;
		cout << "3. Retour au Catalogue" << endl;

		if( !( cin >> choix2 ))
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
				break;
			case 2:
				cout << "Ajout d'un trajet compose" << endl;
				AjoutCompose();
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
	do
	{
		choix2 = 0;

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

		if( !( cin >> choix1 ) )
		{
			cin.clear();
			cin.ignore(1000,'\n');
			cout << "Veuillez saisir un chiffre !" << endl;
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
				break;
			case 6:
				// Lecture des trajets a partir d'un fichier
				cout << "Lecture de trajets a partir"
					<< " d'un fichier" << endl;
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


void Ecriture(string nomFichier , int option ){

	/* ofstream fichier(nomFichier, ios::out | (option==1)? ios::trunc : ios::app); //ouverture en écriture avec effacement du fichier ouvert
	   if (fichier)
	   {
	   for (int i =0 ; i < liste.GetNbTrajets(); i++)
	   {
	   fichier

	   }

	   }
	 */

}//----- Fin de Ecriture


void Catalogue::LectureTrajets()
{
	// NE PAS OUBLIER DE FERMER LE FICHIER !!!

	//--- Choix du fichier
	cout << "Chemin vers le fichier qui contient les trajets :" << endl;

	string source;
	getline(cin, source);	//getline pour les noms de fichier avec espaces

	ifstream fichier;
	fichier.open(source, ios_base::in);

	//--- Verification de l'accessibilite du fichier
	if( !fichier )
	{
		cout << "Le fichier n'est pas accessible !" << endl;
		fichier.close();
		return;
	}

	//--- Recuperation de l'entete
	string infos;
	getline(fichier, infos);

	queue < string > dec = Catalogue::decouperString ( infos );

	if ( dec.size() != 3 )
		//Format non respecte de l'entete
	{
		cout << "Le format du fichier n'est pas bon ou "
			<< "le fichier est vide" << endl;
		fichier.close();
		return;
	}
	int nbTrajets = stoi ( dec.front() );
	dec.pop();
	
	bool existeTS = stoi ( dec.front() );
	dec.pop();

	bool existeTC = stoi ( dec.front() );

	//Liste vide
	if( nbTrajets <= 0 )
	{
		cout << "Pas de trajets sauvegardes dans ce fichier !" << endl;
		fichier.close();
		return;
	}

	//--- Options pour l'utilisateur
	cout << "Choisissez l'option pour le chargement des trajets :" << endl;
	cout << "1. Tous les trajets" << endl;
	if( existeTC && existeTS )
	{
		cout << "2. Selon le type de trajet" << endl;
	}
	cout << "3. Selon la ville de depart/d'arrivee" << endl;
	cout << "4. Selon un intervalle de trajets" << endl;
	cout << "Votre choix :" << endl;

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


//--------------------------------------------------- Surcharge d'operateurs --
//---------------------------------------------- Constructeurs - Destructeur --
Catalogue::Catalogue (void)
{
#ifdef MAP
	cout << "Appel au constructeur de <Catalogue>" << endl;
#endif
	choix1 = 0;
	choix2 = 3;
} //----- Fin de Catalogue


Catalogue::~Catalogue ()
{
#ifdef MAP
	cout << "Appel au destructeur de <Catalogue>" << endl;
#endif

} //----- Fin de ~Catalogue


///////////////////////////////////////////////////////////////////////// PRIVE
//------------------------------------------------------- Methodes protegees --
void Catalogue::recupereTrajets ( ifstream & fichier, unsigned int nbTrajets )
{

}


void Catalogue::recupereTrajetsType ( ifstream & fichier,
	unsigned int nbTrajets )
{

}


void Catalogue::recupereTrajetsVille ( ifstream & fichier,
	unsigned int nbTrajets )
{

}


void Catalogue::recupereTrajetsIntervalle ( ifstream & fichier,
	unsigned int nbTrajets )
{

}


Trajet * Catalogue::lectureTrajet ( ifstream & fichier, TypeTrajet * type )
{
	string description;
	getline ( fichier, description );
	queue < string > decoupage = decouperString ( description );

	Trajet * trajet (nullptr) ;

	if ( decoupage.front().compare ( "S" ) == 0 )
		//Trajet Simple
	{
		decoupage.pop();
		string villeDepart, villeArrivee, moyenTransport;
		villeDepart = decoupage.front();
		decoupage.pop();

		villeArrivee = decoupage.front();
		decoupage.pop();
		
		moyenTransport = decoupage.front();

		trajet = new TrajetSimple ( villeDepart.c_str(), 
			villeArrivee.c_str(), moyenTransport.c_str() );
		*type = SIMPLE;
	}
	else
		//Trajet compose
	{
		decoupage.pop();
		decoupage.pop();
		decoupage.pop();

		//Nombre de trajets du trajet compose
		int nbTrajets = stoi ( decoupage.front() );
		
		TabTrajet * tab = new TabTrajet ();
		TypeTrajet * typeVide = new TypeTrajet;
		
		//On lit tous les trajets
		for ( int i = 0; i < nbTrajets; i++ )
		{
			tab->AjouterTrajet ( lectureTrajet ( fichier, typeVide ) );
		}
		delete typeVide;

		trajet = new TrajetCompose ( tab );
		*type = COMPOSE;
	}

	return trajet;
}


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
		cin.getline(destination, tailleMax );

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
}


queue < string > Catalogue::decouperString ( const string & lecture,
		char separateur )
{
	queue < string > decoupage;
	string::const_iterator precCopieIterateur = lecture.cbegin();

	for ( string::const_iterator i = lecture.cbegin(); i != lecture.cend(); i++)
	{
		if ( *i == separateur )
		{
			decoupage.emplace ( precCopieIterateur, i );
			precCopieIterateur = i + 1;//On saute le separateur
		}
	}

	//Pour le dernier decoupage au besoin
	if ( precCopieIterateur < lecture.cend() )
	{
		decoupage.emplace ( precCopieIterateur, lecture.cend() );	
	}

	return decoupage;	//On ne peut pas renvoyer de reference
}
