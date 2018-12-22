/******************************************************************************
                           TrajetCompose  -
                             -------------------
    debut                : 	Decembre 2018
    copyright            : 	(C) 2018 par K. BOUZID et PY GENEST
    e-mail               : 	kenza.bouzid@insa-lyon.fr
							pierre-yves.genest@insa-lyon.fr
******************************************************************************/
//-------- Réalisation de la classe <TrajetCompose> (fichier TrajetCompose.cpp)

////////////////////////////////////////////////////////////////////// INCLUDES
//--------------------------------------------------------- Includes systeme --
#include <iostream>
#include <cstring>
using namespace std;
//------------------------------------------------------ Includes personnels --
#include "TrajetCompose.h"
//------------------------------------------------------------------ CONSTANTES


//////////////////////////////////////////////////////////////////////// PUBLIC
//------------------------------------------------------- Methodes publiques --
void TrajetCompose::Affichage (const char* c) const
{
	Trajet::Affichage("TC : ");
	cout << "Le trajet est compose de " << tabTC->GetNbTrajets()
			 << " trajets : " << endl;
	for (int i = 0; i < tabTC->GetNbTrajets(); i++)
	{
		tabTC->GetTabTrajet()[i]->Affichage(c);
	}
	cout << "\n";
} //----- Fin de Affichage


char * TrajetCompose::toString(void)
{
	char * description = new char[1000];
	description[0]='\0';
	for(int i=0; i<tabTC->GetNbTrajets(); i++)
	{
		char * t_S =tabTC->GetTabTrajet()[i]->toString();
		strcat(description, t_S);
		delete [] t_S;
	}
	return description;
}//-- Fin toString


char* TrajetCompose::GetVilleDepart(void) const
{
  return tabTC->GetTabTrajet()[0]->GetVilleDepart();
} //----- Fin de GetVilleDepart


char* TrajetCompose::GetVilleArrive(void) const
{
  return tabTC->GetTabTrajet()[tabTC->GetNbTrajets()-1]->GetVilleArrive();
} //----- Fin de GetVilleDepart


char* TrajetCompose::GetMoyenTransport(void) const
{
	char * moyenTransport = new char [20] ;
	strcpy(moyenTransport,"MT");
	return moyenTransport;
} //----- Fin de GetMoyenTrasport


TabTrajet* TrajetCompose::GetTab(void)
{
	return tabTC;
}//-- Fin GetTab


string TrajetCompose::DescriptionTrajet(void)
{
	string descrption = "TC_"+villeDepart +"_"+villeArrive+tabTC->GetNbTrajets()+"\n";
	for(int i=0; i<tabTC->GetNbTrajets(); i++)
	{
		description+=(tabTC->GetTabTrajet()[i]->DescriptionTrajet() +"\n");
	}
	return description; 
}


//--------------------------------------------------- Surcharge d'operateurs --
//---------------------------------------------- Constructeurs - Destructeur --
TrajetCompose::TrajetCompose (TabTrajet *tab) : tabTC (tab)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <TrajetCompose>" << endl;
#endif
} //----- Fin de TrajetCompose


TrajetCompose::~TrajetCompose ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <TrajetCompose>" << endl;
#endif
	delete tabTC;
} //----- Fin de ~TrajetCompose


///////////////////////////////////////////////////////////////////////// PRIVE
//------------------------------------------------------- Methodes protegees --
