//---------- Réalisation de la classe <Requete> (fichier Requete.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
//#include <cstring>

//------------------------------------------------------ Include personnel
#include "Requete.h"
//#include "Page.h"


//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques







//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur

Requete::Requete(string adrIP,string dateH, string action,int codeRetour,long quantite,string userLogName,string authentificatedUser)
{
  #ifdef MAP
    cout << "Appel au constructeur de <Requete>" << endl;
  #endif

 	dateHeure=dateH;
	this->userLogName=userLogName;
	this->authentificatedUser=authentificatedUser;
	this->action=action;
	this->codeRetour=codeRetour;
	this->quantite=quantite;


} //----- Fin de Requete


Requete::~Requete ()
{
#ifdef MAP
    cout << "Appel au destructeur de <Requete>" << endl;
#endif

} //----- Fin de ~Requete


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
