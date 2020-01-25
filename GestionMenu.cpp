//---------- Réalisation de la classe <GestionMenu> (fichier GestionMenu.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;

//------------------------------------------------------ Include personnel
#include "GestionMenu.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void GestionMenu::Permissions(char* nameFile, const string format)
{
    bool ecriture = true;
    if(format == ".log") // besoin des ecritures juste pour le fichier .dot
    {
        ecriture=false;
    }
    int testLecture=access(nameFile, R_OK); // test si le fichier existe

    if(testLecture!=0) // le fichier existe ce qui implique que l'erreur est due aux droits d'acces
    {
        cerr << "vous n'avez pas les droits en lecture sur " << nameFile << " (ou bien sur un répertoire le contenant)" << endl;
    }

    if(ecriture==true)
    {
        if(access(nameFile,W_OK) != 0) // verification des droits en ecriture sur le fichier .dot
        {
            cerr << "vous n'avez pas les droits en écriture sur " << nameFile << " (ou bien sur un répertoire le contenant)" << endl;
        }
    }
}

void  GestionMenu::ErreurFichier(char* nameFile, const string format)
{
    string argString(nameFile);
    if(argString.find(format,0) == string::npos) // verification du format
    {
        cerr << "Vous n'avez pas spécifié un fichier au format " << format << endl;
    }
    else
    {
        if(access(nameFile, F_OK) == 0) // le fichier existe : probleme de permission
        {
            Permissions(nameFile, format);
        }
        else
        {
            cerr << "Fichier " << argString << " introuvable " << endl;
        }
    }
}

bool GestionMenu::Ouverture(fstream*& fic, char* nameFile, const string format)
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
            ErreurFichier(nameFile, format);
            return false;
        }
    }
}

void GestionMenu::LectureCommande(int argc, char** argv )
{
    string arg; // argument courant parmi la liste des arguments
    string nameDot;
    bool activeGraphe = false;
    bool activeExtension = false;
    bool activeHeure = false;
    int horaire = -1;
    ifstream fluxLog;
    fstream * fluxDot = new fstream;
    bool erreurMenu = false;
    string messageManuel = "Référrez vous au manuel utilisateur";

    if(argc <= 7) // si il y a plus de 7 arguments, la syntaxe ne peut pas être correcte
    {
        for(int i=1; i < argc-1 && !erreurMenu; i++) // on parcoure les arguments (on ne connaît pas encore leur ordre)
        {
            arg = argv[i];
            if(arg == "-g") // traitement de l'option -g (génération de fichier .dot)
            {
                if(i >= argc-2 || activeGraphe) // il y a une erreur
                {
                    erreurMenu=true;
                    if(i >= argc-2) // si il ne reste plus assez d'arguments pour contenir deux fichiers
                    {
                        cerr << " Avec ces options vous devez spécifier un fichier Dot et un fichier Log. " << messageManuel << endl;
                    }
                    else // -g a déjà été indiqué parmi les arguments
                    {
                        cerr << " Erreur de syntaxe. Option double. " << messageManuel << endl;
                    }
                }
                else
                {
                    //on essaie d'ouvrir/creer le fichier dot
                    nameDot=argv[++i];
                    activeGraphe=Ouverture(fluxDot, argv[i], formatDot);
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
                        cerr<<" Avec ces options vous devez spécifier une horaire et un fichier Log. "<<messageManuel<<endl;

                    }
                    else
                    {
                        cerr<<" Erreur de syntaxe.Option double. "<<messageManuel<<endl;
                    }
                }
                else
                {
                  //lecture Heure
                    arg=argv[++i];
                    horaire=stoi(arg,0,10);
                    if(horaire<0 || horaire>=24)
                    {
                        erreurMenu=true;
                        cerr<<" Horaire indiquée non valide. L'horaire doit appartenir à l'intervalle [0-23]"<<endl;
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
                        cerr<<" Erreur de syntaxe.Option inconnue. "<<messageManuel<<endl;
                    }

                    else
                    {
                        cerr<<" Erreur de syntaxe.Option double. "<<messageManuel<<endl;
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
                cerr<<" Aucun fichier Log passé en paramètre. "<<messageManuel<<endl;
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
                    ErreurFichier(argv[argc-1], formatLog);
                    erreurMenu=true;
                }
            }
        }
    }
    else // trop d'arguments : la syntaxe ne peut pas être correcte
    {
        cerr<<"Erreur de syntaxe. "<<messageManuel<<endl;
        erreurMenu=true;
    }

    if(!erreurMenu)
    {   //traitement correspondant aux options
        LectureLog lect;
        lect.Lecture(fluxLog, activeExtension, horaire);//lecture fichier log
        lect.Top10();//par défaut affiche les 10 pages les plus consultées

        if(activeGraphe==true)
        {
            lect.creationGraphe(*fluxDot, nameDot);
        }
    }

    delete fluxDot;
}

//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur

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
