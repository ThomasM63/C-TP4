/*************************************************************************
                           Page  -  description
                             -------------------
    début                : novembre 2019
    copyright            : (C) 2019 par Yann Dupont et Thomas MIGNOT
*************************************************************************/

//---------- Interface de la classe <Page> (fichier Page.h) ----------------
#if ! defined ( Page_H )
#define Page_H
#include <fstream>
//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Page>
//classe permettant de lire le fichier log passé en paramètre
//------------------------------------------------------------------------
using namespace std;
class Page
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques


//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

    Page (int nbClics);
    // Mode d'emploi :
    //

    virtual ~Page ( );
    // Mode d'emploi :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
  int nbClics;

};

//-------------------------------- Autres définitions dépendantes de <Page>

#endif // Page_H
