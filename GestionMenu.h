/*************************************************************************
                           GestionMenu  -  description
                             -------------------
    début                : novembre 2019
    copyright            : (C) 2019 par Yann Dupont et Thomas MIGNOT
*************************************************************************/

//---------- Interface de la classe <GestionMenu> (fichier GestionMenu.h) ----------------
#if ! defined ( GestionMenu_H )
#define GestionMenu_H

//--------------------------------------------------- Interfaces utilisées
#include <fstream>
#include <string>
#include <unordered_map>

//#include "Page.h"
#include "unistd.h"
#include "LectureLog.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <GestionMenu>
//classe permettant de lire le fichier log passé en paramètre
//------------------------------------------------------------------------
using namespace std;



class GestionMenu
{
//----------------------------------------------------------------- PUBLIC

public:

//----------------------------------------------------- Méthodes publiques
  void Permissions(char* nameFile,const string format);
  void ErreurFichier(const string format,char* nameFile );
  bool Ouverture(fstream*& fic,const string format,char* nameFile );
  void LectureCommande(int argc, char** argv );

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

    GestionMenu ();
    // Mode d'emploi :
    //

    virtual ~GestionMenu ( );
    // Mode d'emploi :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés




};

//-------------------------------- Autres définitions dépendantes de <GestionMenu>

#endif // GestionMenu_H
