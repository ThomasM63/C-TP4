//---------- Réalisation de la classe <LectureLog> (fichier LectureLog.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
//------------------------------------------------------ Include personnel
#include "LectureLog.h"
//#include "Page.h"


//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

string LectureLog::getNextWord(const string& line, const int& curSpace, int& nextSpace)
{
  #ifdef MAP
    cout << "Appel à la méthode LectureLog::getNextWord" << endl;
  #endif

  nextSpace = line.find(' ', curSpace + 1);
  return line.substr(curSpace + 1, nextSpace - curSpace - 1);
}


 void LectureLog::Lecture(ifstream& fluxLog,bool activeGraphe=false, bool activeExtension=false,int horaire=-1,fstream* fluxDot=nullptr)
{
  #ifdef MAP
    cout << "Appel à la méthode LectureLog::LectureFichier" << endl;
  #endif

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
  string line, urlDepart, urlArrivee, mot;

  while(getline(fluxLog, line))
  {
    int curSpace = -1, nextSpace;
    for (int i = 0; i < 7; ++i)
    {
        mot = getNextWord(line, curSpace, nextSpace);
        curSpace = nextSpace;
    }
    urlDepart = getNextWord(line, curSpace, nextSpace);
    curSpace = nextSpace;
    for (int i = 0; i < 3; ++i)
    {
      mot = getNextWord(line, curSpace, nextSpace);
      curSpace = nextSpace;
    }
    urlArrivee = getNextWord(line, curSpace, nextSpace);
    urlArrivee = urlArrivee.substr(1, urlArrivee.size()-3);
    urlArrivee = urlArrivee.substr(31, urlArrivee.size()-31); // temp, adresse locale
    curSpace = nextSpace;

        //cout << urlDepart << " -> " << urlArrivee << endl;

    if(dicoURL.find(urlDepart) == dicoURL.end())
    {
      unsigned int indice = dicoURL.size();
      dicoURL.insert({urlDepart, indice});
      dicoPages.insert({indice, Page(urlDepart)});
    }

    if(dicoURL.find(urlArrivee) == dicoURL.end())
    {
            //cout << "insertion nouvelle page arrivee" << endl;
      unsigned int indice = dicoURL.size();
      dicoURL.insert({urlArrivee, indice});
      dicoPages.insert({indice, Page(urlArrivee)});
    }

    unsigned int indiceDepart = dicoURL[urlDepart];
    unsigned int indiceArrivee = dicoURL[urlArrivee];
    Page * pageArrivee = &dicoPages[indiceArrivee];

    int count = pageArrivee->dicoTransition.count(indiceDepart);
    if(count == 0) // la transition n'existait pas encore
    {
      pageArrivee->dicoTransition.insert({indiceDepart, 1}); // transition effectuee 1 fois
    } else
    {
      ++pageArrivee->dicoTransition[indiceDepart];
    }
  }

  cerr << endl;
  for(auto it1 = dicoPages.begin(); it1 != dicoPages.end(); ++it1)
  {
    cerr << "Page n." << (*it1).first << " : " << (*it1).second.url << endl;
    cerr << "   transitions :" << endl;
    for(auto it2 = (*it1).second.dicoTransition.begin(); it2 != (*it1).second.dicoTransition.end(); ++it2)
    {
      cerr << "   Depuis la page n." << (*it2).first << " : " << (*it2).second << " clics" << endl;
    }
      cerr << endl;
  }

  fluxLog.close();

}


void LectureLog::creationGraphe(fstream& fluxDot, string nameFile)
{

  /*

  TEST pour création de graphe avec valeurs arbitraires

  Page p1("https:Google.fr",1);

  Page p2("https:Youtube.fr",3);

  Page p3("https:Yahoo.fr",5);


  p1.dicoTransition[3]=6;
  p2.dicoTransition[5]=2;
  p3.dicoTransition[5]=0;

  dicoPages[0]=p1;
  dicoPages[1]=p2;
  dicoPages[2]=p3;

  */

  streambuf* oldCoutBuffer = cout.rdbuf(fluxDot.rdbuf());//redirection de la sortie sur le flux en parametre

  int indiceC;
  string URL;

  string resultat="";
  string noeuds;
  string liens;
  int indiceDebut;
  int nbClics;

  for(auto page : dicoPages)
  {

    indiceC=page.first;

    //URL=page.second.getURL();

    noeuds="node"+to_string(indiceC)+" [label=\""+page.second.url+"\"];\n";
    resultat.insert(0,noeuds);

    for(auto trans: page.second.dicoTransition)
    {
      indiceDebut=trans.first;
      nbClics=trans.second;
      //cout<<"node"<<indiceDebut<<"->"<<" node"<<indiceC<<" [label="<<nbClics<<"];"<<endl;
      liens="node"+to_string(indiceDebut)+"->"+" node"+to_string(indiceC)+" [label=\""+to_string(nbClics)+"\"];\n";
      resultat.append(liens);

    }

  }

  resultat.append("}");
  resultat.insert(0,"digraph {\n");

  cout<<resultat;

  cout.rdbuf(oldCoutBuffer);//redirection sur la sortie standard

  cout<<"Dot-file "<<nameFile<<" généré";

  fluxDot.close();

}



//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur

LectureLog::LectureLog()
{
  #ifdef MAP
    cout << "Appel au constructeur de <LectureLog>" << endl;
  #endif

//  dicoURL=new unordered_map<string, int>;

//  dicoPages=new unordered_map<int,Page>;


} //----- Fin de LectureLog


LectureLog::~LectureLog ()
{
#ifdef MAP
    cout << "Appel au destructeur de <LectureLog>" << endl;
#endif

} //----- Fin de ~LectureLog


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
