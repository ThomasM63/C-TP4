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
#include <fstream>
#include <string>
#include <unordered_map>

//#include "Page.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <LectureLog>
//classe permettant de lire le fichier log passé en paramètre
//------------------------------------------------------------------------
using namespace std;


typedef struct Page
{



    string url;
    string nbClics;
    unordered_map<int,int>dicoTransition;

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
    bool checkExtension(string url);
    void  Lecture(ifstream& fluxLog, bool activeExtension, int horaire);
    void creationGraphe(fstream& fluxDot, string nameFile);
    void  Top10();



//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

    LectureLog ( );
    // Mode d'emploi :
    //

    virtual ~LectureLog ( );
    // Mode d'emploi :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    unordered_map <string,int> dicoURL;

    unordered_map <int,Page> dicoPages;




};

//-------------------------------- Autres définitions dépendantes de <LectureLog>

#endif // LectureLog_H
