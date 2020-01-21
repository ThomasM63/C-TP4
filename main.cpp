#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

#include "GestionMenu.h"

using namespace std;

int main(int argc, char** argv)
{
	GestionMenu app;
	app.LectureCommande(argc,argv);

	return 0;
}
