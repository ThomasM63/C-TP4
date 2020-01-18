/*************************************************************************
                           Requete  -  description
                             -------------------
    début                : novembre 2019
    copyright            : (C) 2019 par Yann Dupont et Thomas MIGNOT
*************************************************************************/

//---------- Interface de la classe <Requete> (fichier Requete.h) ----------------
#if ! defined ( Requete_H )
#define Requete_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Requete>
//classe permettant de lire le fichier log passé en paramètre
//------------------------------------------------------------------------
using namespace std;
class Requete
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques


//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

    Requete ( );
    // Mode d'emploi :
    //

    virtual ~Requete ( );
    // Mode d'emploi :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

};

//-------------------------------- Autres définitions dépendantes de <Requete>

#endif // Requete_H
