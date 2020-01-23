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
#include <iostream>
#include <fstream>

#include "unistd.h"
#include "LectureLog.h"

//------------------------------------------------------------- Constantes
const string formatLog=".log";
const string formatDot=".dot";

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <GestionMenu>
//classe permettant de gérer toutes les saisies de la commande d'éxécution (erreurs saisies, gérer les options etc..)
//------------------------------------------------------------------------
using namespace std;

class GestionMenu
{
//----------------------------------------------------------------- PUBLIC

public:

//----------------------------------------------------- Méthodes publiques
  void Permissions(char* nameFile,const string format);
  //Mode d'emploi: vérifie les permissions sur le fichier passé en paramètre
  void ErreurFichier(const string format,char* nameFile );
  //Mode d'emploi: identifie le type d'erreur lors de l'ouverture du fichier passé en paramètre
  bool Ouverture(fstream*& fic,const string format,char* nameFile );
  // Mode d'emploi: Essai d'ouvrir le fichier passé en paramètre : renvoie faux si problème
  void LectureCommande(int argc, char** argv );
  //Mode d'emploi : gère la saisie de la commande à partir des arguments du main

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

  GestionMenu ();
    // Mode d'emploi :construit un objet de type GestionMenu
    //

  virtual ~GestionMenu ( );
    // Mode d'emploi : détruit un objet de type GestionMenu
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés




};

//-------------------------------- Autres définitions dépendantes de <GestionMenu>

#endif // GestionMenu_H
