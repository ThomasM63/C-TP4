//---------- Réalisation de la classe <LectureLog> (fichier LectureLog.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstring>
#include <fstream>
//------------------------------------------------------ Include personnel
#include "LectureLog.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques


 void LectureLog::Lecture(ifstream& fluxLog,bool activeGraphe=false, bool activeExtension=false,int horaire=-1,ifstream*  fluxDot=nullptr)
{


  string adresseIP;
  string dateHeure;
  string action;
  string URLDest;
  int coderetour;
  long quantite;
  string URLSource;
  string idClient;

  string fichierLog;
  string fichierDot;



}


//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur

LectureLog::LectureLog()
{
  #ifdef MAP
    cout << "Appel au constructeur de <LectureLog>" << endl;
  #endif



} //----- Fin de LectureLog


LectureLog::~LectureLog ()
{
#ifdef MAP
    cout << "Appel au destructeur de <LectureLog>" << endl;
#endif

} //----- Fin de ~LectureLog


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
