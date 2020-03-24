#ifndef _TEMPS_H
#define _TEMPS_H

#include<iostream>
#include<time.h>
#include<string>

using namespace std;

// ce fichier permet d'accèder au temps courant et permet donc lors de la création d'une tâche de mettre la date de création automatiquement

string get_time() {
    time_t now = time(0);
    struct tm tstruct;
    char  buf[80];
    tstruct = *localtime(&now);
    
    strftime(buf, sizeof(buf), "%d/%m/%Y", &tstruct);

    return buf;
}

#endif