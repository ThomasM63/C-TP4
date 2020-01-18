#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include "LectureLog.h"
using namespace std;

int main(int argc, char** argv)
{
    LectureLog ll;// = LectureLog();
    ll.LectureCommande(argc, argv);
    return 0;
}
