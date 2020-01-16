//---------- Réalisation de la classe <Page> (fichier Page.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>


//------------------------------------------------------ Include personnel
#include "Page.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques


//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur

Page::Page(int nombreClics=0)
{
  #ifdef MAP
      cout << "Appel au constructeur de <Page>" << endl;
  #endif

  nbClics=nombreClics;

} //----- Fin de Page


Page::~Page ()
{
#ifdef MAP
    cout << "Appel au destructeur de <Page>" << endl;
#endif

} //----- Fin de ~Page


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
