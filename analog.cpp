#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

#include "LectureLog.h"


using namespace std;



void ErreurFichier(ifstream& fic,const string format,char* nameFile )
{


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

bool Ouverture(ifstream& fic,const string format,char* nameFile )
{
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




int main(int argc, char** argv)
{

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

	lect.Lecture(fluxLog,activeGraphe,activeExtension,horaire,fluxDot);
	//la commande est valide

}




	return 0;
}
