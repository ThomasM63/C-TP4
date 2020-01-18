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
#include <unordered_map>
//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes
//#define MAP
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
    unsigned int nbClics;
    // indice de la page de depart, nb de clics (page d'arrivee = this)
    unordered_map<unsigned int, unsigned int> dicoTransitions;
//----------------------------------------------------- Méthodes publiques


//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

    Page(unsigned int nbClics=0);
    // Mode d'emploi :
    //

    virtual ~Page();
    // Mode d'emploi :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

};

//-------------------------------- Autres définitions dépendantes de <Page>

#endif // Page_H
