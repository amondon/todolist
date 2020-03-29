#ifndef _SAVE_H
#define _SAVE_H

#include<iostream>
#include<fstream>
#include<string>
#include<vector>

#include "task.h"

using namespace std;



vector<Task*> get_data(string adress){ // lecture d'un fichier de sauvegarde en un tableau qui sera lu par l'editeur

    vector<Task*> vect;

    ifstream data{adress};
    
    string ligne;
    
    int flag=1;
      
    getline(data,ligne);

    while(flag){
        string des{};
        int ID;
        int a_st;
        int ID_st;
        int avan;
        string name;
        string status;
        string prio;
        string dc;
        string df;
        string com;

        getline(data,ligne);
        name=name+ligne;
        
            
        getline(data,ligne);
        des=des+ligne;
        getline(data,ligne);
        while(ligne!=""){
            des=des+"\n"+ligne;
            getline(data,ligne);
            
            }
        getline(data,ligne);
        ID=stoi(ligne);

        getline(data,ligne);
        a_st=stoi(ligne);

        getline(data,ligne);
        ID_st=stoi(ligne);


        getline(data,ligne);
        avan=stoi(ligne);

        getline(data,ligne);
        status=status+ligne;

        getline(data,ligne);
        prio+=ligne;
        getline(data,ligne);
        dc+=ligne;
        getline(data,ligne);
        df+=ligne;

        getline(data,ligne);
        com+=ligne;

        getline(data,ligne);
        while(ligne!=""){
            com+="\n -";
            com+=ligne;
            getline(data,ligne);
            }


        /*cout<<endl<<endl;
        cout<<"Nom : "<<name<<endl;
        cout<<"Description : "<<des<<endl;
        cout<<"Identifiant : "<<ID<<endl;
        cout<<"Avancement : "<<avan<<endl;
        cout<<"Statut : "<<status<<endl;
        cout<<"Priorité : "<<prio<<endl;
        cout<<"Date de création : "<<dc<<endl;
        cout<<"Date de fin : "<<df<<endl;
        cout<<"Commentaires : "<<com<<endl<<endl<<endl;*/

        // forme constructor Task(string n,string datec ,string datef,int s =0,string d="",string p="normale",ID=0)
        
        Task* t = new Task {name,dc,df,a_st,ID_st,avan,des,prio,ID};
          
        t->commentaire(com);
        
        vect.push_back(t);
        

                
        getline(data,ligne);
        if(ligne=="&"){
            flag=0;
        }
        
    }
    data.close();

    
    return vect;
 
    
}

void save_data( vector<Task*> vect, string adress){ // fait le processus inverse, à partir d'une liste de taches sauvegarde dans un fichier texte
    ofstream data{adress};
    int n= vect.size();
    
    for(int i=0;i<n;i++){
        data<<"\n";
        data<<vect[i]->save();
        data<<"\n";
    }

    data<<"&";

    data.close();


}

#endif