#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

//#include "unistd.h"


#include "LectureLog.h"
#include "GestionMenu.h"

using namespace std;



int main(int argc, char** argv)
{

	GestionMenu app;
	app.LectureCommande(argc,argv);

	return 0;
}
