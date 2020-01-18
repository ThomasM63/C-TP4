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

void LectureLog::ErreurFichier(ifstream& fic,const string format,char* nameFile )
{
#ifdef MAP
    cout << "Appel à la méthode LectureLog::ErreurFichier" << endl;
#endif
//	string argString(argv[argc-1]);
    string argString(nameFile);

    if(argString.find(format,0)==string::npos)
    {
        cerr<<"Vous n'avez pas spécifié un fichier au format "<<format;


    }
    else
    {
        cerr<<"Fichier "<<argString<<" introuvable ";

    }



}

bool LectureLog::Ouverture(ifstream& fic,const string format,char* nameFile )
{
#ifdef MAP
    cout << "Appel à la méthode LectureLog::Ouverture" << endl;
#endif
    string argString(nameFile);
    fic.open(nameFile);
    if(fic)
    {
        cout<<"Ouverture avec succès du fichier "<<argString<<endl;
        return true;
    }
    else
    {
        ErreurFichier(fic,format,nameFile);
        return false;

    }

}

string LectureLog::getNextWord(const string& line, const int& curSpace, int& nextSpace)
{
#ifdef MAP
    cout << "Appel à la méthode LectureLog::getNextWord" << endl;
#endif
    nextSpace = line.find(' ', curSpace + 1);
    return line.substr(curSpace + 1, nextSpace - curSpace - 1);
}

int LectureLog::LectureFichier(ifstream& fluxLog, bool activeGraphe=false, bool activeExtension=false, int horaire=-1, ifstream * fluxDot=nullptr)
{
#ifdef MAP
    cout << "Appel à la méthode LectureLog::LectureFichier" << endl;
#endif
    string line, urlDepart, urlArrivee, mot;
    while(getline(fluxLog, line))
    {
        int curSpace = -1, nextSpace;
        for (int i = 0; i < 7; ++i) {
            mot = getNextWord(line, curSpace, nextSpace);
            curSpace = nextSpace;
        }
        urlDepart = getNextWord(line, curSpace, nextSpace);
        curSpace = nextSpace;
        for (int i = 0; i < 3; ++i) {
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
            //cout << "insertion nouvelle page depart" << endl;
            unsigned int indice = dicoURL.size();
            dicoURL.insert({urlDepart, indice});
            dicoIndices.insert({indice, urlDepart});
            dicoPages.insert({indice, Page()});
        }
        if(dicoURL.find(urlArrivee) == dicoURL.end())
        {
            //cout << "insertion nouvelle page arrivee" << endl;
            unsigned int indice = dicoURL.size();
            dicoURL.insert({urlArrivee, indice});
            dicoIndices.insert({indice, urlArrivee});
            dicoPages.insert({indice, Page()});
        }

        unsigned int indiceDepart = dicoURL[urlDepart];
        unsigned int indiceArrivee = dicoURL[urlArrivee];
        Page * pageArrivee = &dicoPages[indiceArrivee];

        int count = pageArrivee->dicoTransitions.count(indiceDepart);
        if(count == 0) // la transition n'existait pas encore
        {
            //cout << "insertion nouvelle transition" << endl;
            pageArrivee->dicoTransitions.insert({indiceDepart, 1}); // transition effectuee 1 fois
        } else {
            //cout << "incrementation nb clics" << endl;
            ++pageArrivee->dicoTransitions[indiceDepart];
        }
    }

    cerr << endl;
    for(auto it1 = dicoPages.begin(); it1 != dicoPages.end(); ++it1)
    {
        cerr << "Page n." << (*it1).first << " : " << dicoIndices[(*it1).first] << endl;
        cerr << "   transitions :" << endl;
        for(auto it2 = (*it1).second.dicoTransitions.begin(); it2 != (*it1).second.dicoTransitions.end(); ++it2)
        {
            cerr << "   Depuis la page n." << (*it2).first << " : " << (*it2).second << " clics" << endl;
        }
        cerr << endl;
    }

    return 0;
}

int LectureLog::LectureCommande(int argc, char **argv)
{
#ifdef MAP
    cout << "Appel à la méthode LectureLog::LectureCommande" << endl;
#endif
    string arg;
    const string formatLog=".log";
    const string formatDot=".dot";

    bool activeDefault=false;
    bool activeGraphe=false;
    bool activeExtension=false;
    bool activeHeure=false;
    int horaire;

    ifstream fluxLog;
    ifstream* fluxDot=nullptr;
    bool erreurMenu=false;

    if(argc<=7){

        for(int i=1;i<argc-1 && erreurMenu==false;i++){
            arg=argv[i];
            if(arg=="-g")
            {
                if(i>=argc-2 || activeGraphe==true)
                {
                    erreurMenu=true;
                    if(i>=argc-2)
                    {
                        cerr<<" Avec ces options vous devez spécifier un fichier Dot et un fichier Log. Référrez vous au manuel utilisateur ";
                    }
                    else
                    {
                        cerr<<" Erreur de syntaxe. Option double. Référrez vous au manuel utilisateur ";
                    }
                }
                else
                {
                    activeGraphe=Ouverture(*fluxDot,formatDot,argv[++i]);
                    erreurMenu= !activeGraphe;
                    //lire nom de fichier .dot.Possible erreur ouverture
                }
            }
            else if(arg=="-t")
            {
                if(i>=argc-2 ||activeHeure==true)
                {
                    erreurMenu=true;
                    if(i>=argc-2)
                    {
                        cerr<<" Avec ces options vous devez spécifier une horaire et un fichier Log. Référrez vous au manuel utilisateur ";
                    }
                    else
                    {
                        cerr<<" Erreur de syntaxe.Option double. Référrez vous au manuel utilisateur ";
                    }
                }
                else
                {
                    //lire heure
                    arg=argv[++i];
                    horaire=stoi(arg,0,10);
                    if(horaire<0 || horaire>24)
                    {
                        erreurMenu=true;
                        cerr<<" Horaire indiquée non valide. L'horaire doit appartenir à l'intervalle [0-24]";
                    }
                    activeHeure=true;
                }
            }
            else
            {

                if(arg!="-e" || (arg=="-e" &&activeExtension==true))
                {
                    erreurMenu=true;
                    if(arg!="-e")
                    {
                        cerr<<" Erreur de syntaxe.Option inconnue. Référrez vous au manuel utilisateur ";
                    }
                    else
                    {
                        cerr<<" Erreur de syntaxe.Option double. Référrez vous au manuel utilisateur ";
                    }
                }
                else{
                    activeExtension=true;
                }
            }
        }

        if(erreurMenu==false)
        {
            if(argc-1>0)
            {
                fluxLog.open(argv[argc-1]);
            }
            else
            {
                erreurMenu=true;
                cerr<<" Aucun fichier Log passé en paramètre. Référrez vous au manuel utilisateur ";
            }
            if(fluxLog && argc-1>0 )
            {
                string nameFile=argv[argc-1];
                cout<<"Ouverture avec succès du fichier "<<nameFile<<endl;
            }
            else
            {
                if(argc-1>0)
                {
                    ErreurFichier(fluxLog,formatLog,argv[argc-1]);
                    erreurMenu=true;
                }
            }
        }
    }
    else
    {
        cerr<<"Erreur de syntaxe. Référrez vous au manuel utilisateur ";
        erreurMenu=true;
    }

    if(!erreurMenu)
    {
        LectureLog lect;
        lect.LectureFichier(fluxLog,activeGraphe,activeExtension,horaire,fluxDot);
        //la commande est valide
    }
    return 0;
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
