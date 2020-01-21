//---------- Réalisation de la classe <GestionMenu> (fichier GestionMenu.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstring>
#include <fstream>
//------------------------------------------------------ Include personnel
#include "GestionMenu.h"
//#include "Page.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void GestionMenu:: Permissions(char* nameFile,const string format)
{
    bool ecriture;
    //besoin des ecritures juste pour le fichier .dot
    if(format==".log")
    {
        ecriture=false;
    }
    else
    {
        ecriture=true;
    }


    int testLecture=access(nameFile,R_OK);
    //test si le fichier existe

    if(testLecture!=0)
    {
        //le fichier existe ce qui implique que l'erreur est due aux droits d'acces
        cerr<<"vous n'avez pas les droits en lecture sur "<<nameFile<<" (ou bien sur un répertoire le contenant)"<<endl;
    }

    if(ecriture==true)

    {
        if(access(nameFile,W_OK)!=0 )
        {   //verification des droits en ecriture sur le fichier .dot
            cerr<<"vous n'avez pas les droits en écriture sur "<<nameFile<<" (ou bien sur un répertoire le contenant)"<<endl;
        }
    }


}

void  GestionMenu ::ErreurFichier(const string format,char* nameFile )
{
    string argString(nameFile);
    //verification du format
    if(argString.find(format,0)==string::npos)
    {
        cerr<<"Vous n'avez pas spécifié un fichier au format "<<format<<endl;
    }
    else
    {
        if(access(nameFile,F_OK)==0)
        {   //le fichier existe : probleme de permission
            Permissions(nameFile,format);
        }

        else
        {
            cerr<<"Fichier "<<argString<<" introuvable "<<endl;
        }
    }
}


bool GestionMenu::Ouverture(fstream*& fic,const string format,char* nameFile )
{
    string argString(nameFile);
    (*fic).open(nameFile,ios::trunc|ios::out);
    //ouverture fichier dot
    if(*fic)
    {
        cout<<"Ouverture avec succès du fichier "<<argString<<endl;
        return true;
    }
    else
    {
        if(format==".dot")
        {
            if(argString.find(format,0)==string::npos)
            {
                cerr<<"Vous n'avez pas spécifié un fichier au format "<<format<<endl;
                return false;
            }
            else
            {

                if(access(nameFile,F_OK)==0)
                {
                    Permissions(nameFile,format);
                    return false;
                }

                else
                {   //le fichier dot specifié n'existe pas : on le crée
                    cout<<"Création du nouveau fichier "<<argString<<endl;
                    ofstream f;
                    f.open(nameFile);
                    f.close();
                    (*fic).close();
                    (*fic).open(nameFile);
                    return true;
                }
            }
        }

        else
        {
            ErreurFichier(format,nameFile);
            return false;
        }
    }
}

void GestionMenu::LectureCommande(int argc, char** argv )
{

    string arg;
    string nameDot;
    bool activeGraphe=false;
    bool activeExtension=false;
    bool activeHeure=false;
    int horaire = -1;
    ifstream fluxLog;
    fstream* fluxDot=new fstream;
    bool erreurMenu=false;

    if(argc<=7)
    {
        for(int i=1;i<argc-1 && erreurMenu==false;i++){
            arg=argv[i];
            if(arg=="-g")
            {
              //option creation graphe
                if(i>=argc-2 || activeGraphe==true)
                {
                    //gestion des éventuelles erreurs
                    erreurMenu=true;
                    if(i>=argc-2)
                    {
                        cerr<<" Avec ces options vous devez spécifier un fichier Dot et un fichier Log. Référrez vous au manuel utilisateur "<<endl;
                    }
                    else
                    {
                        cerr<<" Erreur de syntaxe. Option double. Référrez vous au manuel utilisateur "<<endl;
                    }
                }
                else
                {
                    //on essaie d'ouvrir/creer le fichier dot
                    nameDot=argv[++i];
                    activeGraphe=Ouverture(fluxDot,formatDot,argv[i]);
                    erreurMenu= !activeGraphe;
                }
            }
            else if(arg=="-t")
            {
                //option selection horaire
                if(i>=argc-2 ||activeHeure==true)
                {
                    //gestion des éventuelles erreurs
                    erreurMenu=true;
                    if(i>=argc-2)
                    {
                        cerr<<" Avec ces options vous devez spécifier une horaire et un fichier Log. Référrez vous au manuel utilisateur "<<endl;

                    }
                    else
                    {
                        cerr<<" Erreur de syntaxe.Option double. Référrez vous au manuel utilisateur "<<endl;
                    }
                }
                else
                {
                  //lecture Heure
                    arg=argv[++i];
                    horaire=stoi(arg,0,10);
                    if(horaire<0 || horaire>24)
                    {
                        erreurMenu=true;
                        cerr<<" Horaire indiquée non valide. L'horaire doit appartenir à l'intervalle [0-24]"<<endl;
                    }
                    activeHeure=true;
                }
            }
            else
            {
                if(arg!="-e" || (arg=="-e" &&activeExtension==true))
                {
                    erreurMenu=true;

                    //gestion des éventuelles erreurs

                    if(arg!="-e")
                    {
                        cerr<<" Erreur de syntaxe.Option inconnue. Référrez vous au manuel utilisateur "<<endl;
                    }

                    else
                    {
                        cerr<<" Erreur de syntaxe.Option double. Référrez vous au manuel utilisateur "<<endl;
                    }
                }

                else
                {
                    //option -e activée
                    activeExtension=true;
                }
            }
        }

        if(erreurMenu==false)
        {
          //pas d'erreur sur la saisie de la commande

            if(argc-1>0)
            {
                fluxLog.open(argv[argc-1]);
            }
            else
            {   //pas de log en parametre
                erreurMenu=true;
                cerr<<" Aucun fichier Log passé en paramètre. Référrez vous au manuel utilisateur "<<endl;
            }

            if(fluxLog && argc-1>0 )
            {
                string nameFile=argv[argc-1];

                //verification du format
                if(nameFile.find(formatLog,0)==string::npos)
                {
                    cerr<<"Vous n'avez pas spécifié un fichier au format .log"<<endl;
                }

                else
                {
                  cout<<"Ouverture avec succès du fichier "<<nameFile<<endl;

                }
            }

            else
            {
                if(argc-1>0)
                {
                    ErreurFichier(formatLog,argv[argc-1]);
                    erreurMenu=true;
                }
            }
        }
    }
    else
    {
        cerr<<"Erreur de syntaxe. Référrez vous au manuel utilisateur "<<endl;
        erreurMenu=true;
    }

    if(!erreurMenu)
    {   //traitement correspondant aux options
        LectureLog lect;
        lect.Lecture(fluxLog, activeExtension, horaire);
        lect.Top10(10);
        if(activeGraphe==true)
        {
            lect.creationGraphe(*fluxDot, nameDot);
        }
    }

    delete fluxDot;
}

//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Construiocteurs - destructeur

GestionMenu::GestionMenu()
{
#ifdef MAP
    cout << "Appel au constructeur de <GestionMenu>" << endl;
#endif




} //----- Fin de GestionMenu


GestionMenu::~GestionMenu ()
{
#ifdef MAP
    cout << "Appel au destructeur de <GestionMenu>" << endl;
#endif

} //----- Fin de ~GestionMenu


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
