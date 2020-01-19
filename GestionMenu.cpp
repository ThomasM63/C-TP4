//---------- Réalisation de la classe <GestionMenu> (fichier GestionMenu.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
//------------------------------------------------------ Include personnel
#include "GestionMenu.h"
//#include "Page.h"


//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void GestionMenu:: Permissions(char* nameFile,const string format)
{

	bool ecriture;
	if(format==".log")
	{
		ecriture=false;
	}

	else
	{
		ecriture=true;
	}

	int testLecture=access(nameFile,R_OK);

	if(testLecture!=0)
	{
		cerr<<"vous n'avez pas les droits en lecture sur "<<nameFile<<" (ou bien sur un répertoire le contenant )"<<endl;

	}


	if(ecriture==true)
	{
		if(access(nameFile,W_OK)!=0 )
		{
			cerr<<"vous n'avez pas les droits en écriture sur "<<nameFile<<" (ou bien sur un répertoire le contenant )"<<endl;
		}
	}


}

void  GestionMenu ::ErreurFichier(const string format,char* nameFile )
{

	string argString(nameFile);

	if(argString.find(format,0)==string::npos)
	{
		cerr<<"Vous n'avez pas spécifié un fichier au format "<<format<<endl;

	}
	else
	{

		if(access(nameFile,F_OK)==0)
		{

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
	(*fic).open(nameFile,ios::in|ios::out);
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
				{
					cout<<"Creation du nouveau fichier "<<argString<<endl;
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


	const string formatLog=".log";
	const string formatDot=".dot";

	bool activeGraphe=false;
	bool activeExtension=false;
	bool activeHeure=false;
	int horaire;

	ifstream fluxLog;
	//ofstream fluxDot;

	fstream* fluxDot=new fstream;
	//*fluxDot=fluxDotOut;

	bool erreurMenu=false;

	if(argc<=7)
	{


	for(int i=1;i<argc-1 && erreurMenu==false;i++){

		arg=argv[i];

		if(arg=="-g")
		{
			if(i>=argc-2 || activeGraphe==true)
			{
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
				nameDot=argv[++i];
				activeGraphe=Ouverture(fluxDot,formatDot,argv[i]);

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
					cerr<<" Avec ces options vous devez spécifier une horaire et un fichier Log. Référrez vous au manuel utilisateur "<<endl;

				}
				else
				{
					cerr<<" Erreur de syntaxe.Option double. Référrez vous au manuel utilisateur "<<endl;

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

				if(arg!="-e")

				{
					cerr<<" Erreur de syntaxe.Option inconnue. Référrez vous au manuel utilisateur "<<endl;

				}

				else
				{
					cerr<<" Erreur de syntaxe.Option double. Référrez vous au manuel utilisateur "<<endl;


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
			cerr<<" Aucun fichier Log passé en paramètre. Référrez vous au manuel utilisateur "<<endl;

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

{
	LectureLog lect;

	//lect.Lecture(fluxLog,activeGraphe,activeExtension,horaire,fluxDot);
	lect.Top10();

	if(activeGraphe==true)
	{
		lect.creationGraphe(*fluxDot,nameDot);


	}
	//la commande est valide

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
