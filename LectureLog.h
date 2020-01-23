/*************************************************************************
                           LectureLog  -  description
                             -------------------
    début                : novembre 2019
    copyright            : (C) 2019 par Yann Dupont et Thomas MIGNOT
*************************************************************************/

//---------- Interface de la classe <LectureLog> (fichier LectureLog.h) ----------------
#if ! defined ( LectureLog_H )
#define LectureLog_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <map>

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <LectureLog>
//classe permettant de lire le fichier log passé en paramètre et de faire des statistiques en rapport
//------------------------------------------------------------------------
using namespace std;

typedef struct Page
{
  string url;
  string nbClics;
  unordered_map<int,int>dicoTransition;//clef : indice page départ | valeur: nb hits avec l'instance page qui le contient

  Page ( string adresse="",int nombreClics=0)
  {
    url=adresse;
    nbClics=nombreClics;
  }

}
Page;


class LectureLog
{
//----------------------------------------------------------------- PUBLIC

public:

//----------------------------------------------------- Méthodes publiques


  string getNextWord(const string& line, const int& curSpace, int& nextSpace);
  //Mode d'emploi:renvoie un string correspondant au mot d'après

  bool checkExtension(string url);
  //Mode d'emploi : renvoie un booleen qui verifie si l'extension correspond à un filtre passé avec l'option -e

  void  Lecture(ifstream& fluxLog, bool activeExtension, int horaire);
  //Mode d'emploi : permet de lire le fichier .log et de le stocker dans les structures de données pour faire des stats

  unordered_map <int,int> ConstructionMapTemp();
  //Mode d'emploi : construit un dictionnaire temporaire permettant ensuite de construire l'ABR pour faire le top10

  void creationGraphe(fstream& fluxDot, string nameFile);
  //Mode d'emploi: permet de recopier le code correspondant au graphe sur le flux voulu

  string creationGrapheString();
  //Mode d'emploi: renvoie un string contenant tout le code orrespondant au graphe
  
  void  Top10(int nbTop=10);
  //Mode d'emploi: écrit sur la sortie standard le classement des nbTop pages les plus consultées

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

  LectureLog ();
  // Mode d'emploi : construit un objet de type LectureLog
  //

  virtual ~LectureLog ();
  // Mode d'emploi : Détruit un objet de type LectureLog
  //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
  unordered_map <string,int> dicoURL;//clef : URL | valeur: indice Page

  unordered_map <int,Page> dicoPages;//clef : indice Page | valeur : Page

};

//-------------------------------- Autres définitions dépendantes de <LectureLog>

#endif // LectureLog_H
