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
#include "Page.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <LectureLog>
//classe permettant de lire le fichier log passé en paramètre
//------------------------------------------------------------------------
using namespace std;
class LectureLog
{
//----------------------------------------------------------------- PUBLIC

public:

//----------------------------------------------------- Méthodes publiques

    void ErreurFichier(ifstream& fic,const string format,char* nameFile );

    bool Ouverture(ifstream& fic,const string format,char* nameFile );

    string getNextWord(const string& line, const int& curSpace, int& nextSpace);

    int LectureFichier(ifstream& fluxLog, bool activeGraphe, bool activeExtension, int horaire, ifstream * fluxDot);

    int LectureCommande(int argc, char** argv);

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

    LectureLog();
    // Mode d'emploi :
    //

    virtual ~LectureLog();
    // Mode d'emploi :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    unordered_map<string, unsigned int> dicoURL;
    unordered_map<unsigned int, string> dicoIndices;
    unordered_map<unsigned int, Page> dicoPages;

};

//-------------------------------- Autres définitions dépendantes de <LectureLog>

#endif // LectureLog_H
