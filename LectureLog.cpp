//---------- Réalisation de la classe <LectureLog> (fichier LectureLog.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;

//------------------------------------------------------ Include personnel
#include "LectureLog.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

string LectureLog::getNextWord(const string& line, const int& curSpace, int& nextSpace)
{
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
    // variables contenant les informations de la requête en cours
    string line, urlDepart, urlArrivee, urlBase, extensionDepart, ip, ulog, aUser, date, fuseau, typeAction, protocole, status, tailleRep, idClient;
    int curSpace; // positions de caractères espace pour le découpage des lignes
    int nextSpace;
    int tailleHeure = 1; // nombre de caractères à considérer dans le string de l'heure
    if(horaire >= 10)
    {
        tailleHeure = 2;
    }
    unsigned int posQMark; // position de caractère '?' pour le nettoyage d'url
    // récupération de l'url de base
    ifstream fichierURLbase;
    fichierURLbase.open("D:\\C et C++\\C-TP4\\URL_base.txt");
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
            if(!(date.substr(date.size()-6-tailleHeure, tailleHeure) == to_string(horaire)))
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
        if(posQMark != urlArrivee.npos) // on coupe tout à partir du premier '?' trouvé
        {
            urlArrivee = urlArrivee.substr(0, posQMark);
        }
        if(activeExtension) // vérification du critère d'extension de l'option -e
        {
            if(checkExtension(urlArrivee))
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


unordered_map <int,int> LectureLog::ConstructionMapTemp()
{
  unordered_map <int,int> mapTemp;//clef : indicePage | valeur: nbHits

  //map temporelle pour stocker les hits

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
          mapTemp[indiceC]+=nbClics; //somme totale des hits de chaque page incrémentée
      }
  }

  return mapTemp;
}


void LectureLog::Top10(int nbTop)
{

  int indiceC;
  string URL;

  string resultat="";//contient tout le texte a recopier dans le fichier.dot
  string noeuds;
  string liens;
  int indiceDebut;
  int nbClics;

  for(auto page : dicoPages)
  {
      //parcours des documents
      indiceC=page.first;
      noeuds="node"+to_string(indiceC)+" [label=\""+page.second.url+"\"];\n";
      //ajout (au debut)du noeud dans resultat
      resultat.insert(0,noeuds);

      for(auto trans: page.second.dicoTransition)
      {
          //parcours des transitions avec pour page d'arrivee  la variable page
          indiceDebut=trans.first;
          nbClics=trans.second;
          liens="node"+to_string(indiceDebut)+"->"+" node"+to_string(indiceC)+" [label=\""+to_string(nbClics)+"\"];\n";
          //ajout a la fin de resultat les transitions
          resultat.append(liens);
      }
  }

  resultat.append("}");
  resultat.insert(0,"digraph {\n");

  unordered_map <int,int> mapTemp=ConstructionMapTemp();

  if(mapTemp.size()==0)
  {
      cout<<"Fichier .log vide"<<endl;
  }

  multimap<int,int> mapHits;//clé: nombre de Hits | valeur: indicePage

  for(auto el : mapTemp)
  {
      mapHits.insert({el.second,el.first});
      //construction multimap à l'aide de la map temporelle
  }

  int nbIter=0;
  multimap<int,int>::reverse_iterator rit;//parcours en sens inverse car par défaut l'ABR est trié selon valeurs croissantes
  int indicePage;
  string urlPage;
  for(rit=mapHits.rbegin();rit!=mapHits.rend() && nbIter<=nbTop-1;rit++)
  {
      nbIter++;
      indicePage=rit->second;
      urlPage=(dicoPages[indicePage]).url;
      cout<<urlPage<<" (nombre hits = "<<rit->first<<")"<<endl;
      //affichage des pages les plus visitées
  }
}

string LectureLog::creationGrapheString()
{
    int indiceC;
    string URL;

    string resultat="";//contient tout le texte a recopier dans le fichier.dot
    string noeuds;
    string liens;
    int indiceDebut;
    int nbClics;

    for(auto page : dicoPages)
    {
        //parcours des documents
        indiceC=page.first;
        noeuds="node"+to_string(indiceC)+" [label=\""+page.second.url+"\"];\n";
        //ajout (au debut)du noeud dans resultat
        resultat.insert(0,noeuds);

        for(auto trans: page.second.dicoTransition)
        {
            //parcours des transitions avec pour page d'arrivee  la variable page
            indiceDebut=trans.first;
            nbClics=trans.second;
            liens="node"+to_string(indiceDebut)+"->"+" node"+to_string(indiceC)+" [label=\""+to_string(nbClics)+"\"];\n";
            //ajout a la fin de resultat les transitions
            resultat.append(liens);
        }
    }

    resultat.append("}");
    resultat.insert(0,"digraph {\n");

    return resultat;
  }

  void LectureLog::creationGraphe(fstream& fluxDot, string nameFile)
  {

    streambuf* oldCoutBuffer = cout.rdbuf(fluxDot.rdbuf());//redirection de la sortie sur le .dot
    string resultat=creationGrapheString();

    cout<<resultat;//on recopie la chaine resultat dans le dot

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



} //----- Fin de LectureLog


LectureLog::~LectureLog ()
{
  #ifdef MAP
    cout << "Appel au destructeur de <LectureLog>" << endl;
  #endif

} //----- Fin de ~LectureLog


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
