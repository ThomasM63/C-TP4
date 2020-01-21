//---------- Réalisation de la classe <LectureLog> (fichier LectureLog.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
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

bool LectureLog::checkExtension(string url)
{
    if (url.size() > 3)
    {
        string extensionDepart = url.substr(url.size() - 3, 3);
        if (extensionDepart == "css" || extensionDepart == ".js" || extensionDepart == "png" ||
            extensionDepart == "jpg" || extensionDepart == "gif" || extensionDepart == "bmp") {
            return true;
        }
    }
    return false;
}

void LectureLog::Lecture(ifstream& fluxLog, bool activeExtension, int horaire)
{
#ifdef MAP
    cout << "Appel à la méthode LectureLog::LectureFichier" << endl;
#endif
    // variables contenant les informations de la requête en cours
    string line, urlDepart, urlArrivee, urlBase, extensionDepart, ip, ulog, aUser, date, fuseau, typeAction, protocole, status, tailleRep, idClient;
    int curSpace; // positions de caractères espace pour le découpage des lignes
    int nextSpace;
    int posQMark; // position de caractère '?' pour le nettoyage d'url
    // récupération de l'url de base
    ifstream fichierURLbase;
    fichierURLbase.open("URL_base.txt");
    if(fichierURLbase)
    {
        getline(fichierURLbase, urlBase);
    }
    fichierURLbase.close();

    while(getline(fluxLog, line)) // pour chaque ligne du fichier log
    {
        curSpace = -1;

        ip = getNextWord(line, curSpace, nextSpace);
        curSpace = nextSpace;
        ulog = getNextWord(line, curSpace, nextSpace);
        curSpace = nextSpace;
        aUser = getNextWord(line, curSpace, nextSpace);
        curSpace = nextSpace;
        date = getNextWord(line, curSpace+1, nextSpace);
        curSpace = nextSpace;

        if(horaire != -1) // vérification du critère d'horaire de l'option -t
        {
            if(!(date.substr(date.size()-8, 2) == to_string(horaire)))
            {
                continue;
            }
        }

        fuseau = getNextWord(line, curSpace, nextSpace);
        fuseau = fuseau.substr(0, fuseau.size()-1);
        curSpace = nextSpace;
        typeAction = getNextWord(line, curSpace+1, nextSpace);
        curSpace = nextSpace;

        // récupération de l'url d'arrivée
        urlArrivee = getNextWord(line, curSpace, nextSpace);
        curSpace = nextSpace;
        posQMark = urlArrivee.find('?');
        if(posQMark != string::npos) // on coupe tout à partir du premier '?' trouvé
        {
            urlArrivee = urlArrivee.substr(0, posQMark);
        }
        if(activeExtension) // vérification du critère d'extension de l'option -e
        {
            if(checkExtension(urlDepart))
            {
                continue;
            }
        }

        protocole = getNextWord(line, curSpace, nextSpace);
        protocole = protocole.substr(0, protocole.size()-1);
        curSpace = nextSpace;
        status = getNextWord(line, curSpace, nextSpace);
        curSpace = nextSpace;
        tailleRep = getNextWord(line, curSpace, nextSpace);
        curSpace = nextSpace;

        // récupération de l'url de départ
        urlDepart = getNextWord(line, curSpace, nextSpace);
        urlDepart = urlDepart.substr(1, urlDepart.size()-2);
        if(urlDepart.size() >= urlBase.size())
        {
            if(urlDepart.substr(0, urlBase.size()) == urlBase)
            {
                urlDepart = urlDepart.substr(urlBase.size(), urlDepart.size()-urlBase.size());
            }
        }
        posQMark = urlDepart.find('?');
        if(posQMark != string::npos) // on coupe tout à partir du premier '?' trouvé
        {
            urlDepart = urlDepart.substr(0, posQMark);
        }

        idClient = line.substr(nextSpace+1, line.size()-nextSpace-2); // tout le reste de la ligne

        // création des nouvelles pages si besoin, et insertion dans les dictionnaires
        if(dicoURL.find(urlDepart) == dicoURL.end()) // url de départ
        {
            unsigned int indice = dicoURL.size();
            dicoURL.insert({urlDepart, indice});
            dicoPages.insert({indice, Page(urlDepart)});
        }
        if(dicoURL.find(urlArrivee) == dicoURL.end()) // url d'arrivée
        {
            unsigned int indice = dicoURL.size();
            dicoURL.insert({urlArrivee, indice});
            dicoPages.insert({indice, Page(urlArrivee)});
        }
        // récupération des indices de départ et d'arrivée (on n'utilise plus les url à partir d'ici)
        unsigned int indiceDepart = dicoURL[urlDepart];
        unsigned int indiceArrivee = dicoURL[urlArrivee];
        Page * pageArrivee = &dicoPages[indiceArrivee];

        // on vérifie si la transition entre la page de départ et la page d'arrivée existe déjà
        int count = pageArrivee->dicoTransition.count(indiceDepart);
        if(count == 0) // la transition n'existait pas encore
        {
            pageArrivee->dicoTransition.insert({indiceDepart, 1}); // transition effectuee 1 fois
        } else // la transition existait déjà
        {
            ++pageArrivee->dicoTransition[indiceDepart];
        }

        //cout << extensionDepart << " " << ip << " " << ulog << " " << aUser << " " << date << " " << fuseau << " " << typeAction << " " << protocole << " " << status << " " << tailleRep << " " << idClient << endl;
        // un traitement des informations de la requête peut être ajouté ici
    }

    fluxLog.close();
}


void LectureLog:: Top10()
{

    unordered_map <int,int> mapTemp;
    int indiceC;
    int nbClics;

    for(auto page : dicoPages)
    {

        indiceC=page.first;

        int count = mapTemp.count(indiceC);
        if(count == 0) // la transition n'existait pas encore
        {
            mapTemp.insert({indiceC, 0}); // transition effectuee 1 fois
        }

        for(auto trans: page.second.dicoTransition)
        {

            nbClics=trans.second;
            mapTemp[indiceC]+=nbClics;


        }

    }

    if(mapTemp.size()==0)
    {

        cout<<"Fichier .log vide"<<endl;
    }

    multimap<int,int> mapHits;

    for(auto el : mapTemp)
    {

        mapHits.insert({el.second,el.first});

    }


    int nbIter=0;
    multimap<int,int>::reverse_iterator rit;
    int indicePage;
    string urlPage;
    for(rit=mapHits.rbegin();rit!=mapHits.rend() && nbIter<=9;rit++)
    {
        nbIter++;
        //cout<<rit->first<<"|"<<rit->second<<endl;
        indicePage=rit->second;
        urlPage=(dicoPages[indicePage]).url;
        cout<<urlPage<<" (nombre hits = "<<rit->first<<")"<<endl;



    }


}


void LectureLog::creationGraphe(fstream& fluxDot, string nameFile)
{



    //TEST pour création de graphe avec valeurs arbitraires

    /*Page p1("https:Google.fr");

    Page p2("https:Youtube.fr");

    Page p3("https:Yahoo.fr");


    p1.dicoTransition[1]=6;
    p2.dicoTransition[2]=8;
    p3.dicoTransition[0]=8;

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

    cout<<"Dot-file "<<nameFile<<" généré"<<endl;

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
