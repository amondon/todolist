#ifndef _EDITOR_H
#define _EDITOR_H

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<stdexcept>

#include"task.h"
#include "save.h"
#include"temps.h"

using namespace std;




class Editor{
    //prend un fichier et lis les données pour avoir une liste de taches
    //on pourra ajouter a cette éditeur des taches, les modifier ...

    private :
    string adress {};
    vector<Task*> tab; //tableau qui pointe vers les tâches
    vector<int> IDs; //contient la liste des ID qui sont pris
    
    
    public:

    Editor(){
        menu();
    }

    Editor (string adresse):adress(adresse){  
        cout<<"Création d'une nouvelle liste de tache"<<endl;
        tab=get_data(adress);

        int n = tab.size();
        for(int i =0;i<n;i++){
            IDs.push_back(tab[i]->get_ID());
        }//construction de la liste des IDs déja existants

    }

    Editor (vector<Task*> vect):tab(vect){
        int n = tab.size();
        for(int i =0;i<n;i++){
            IDs.push_back(tab[i]->get_ID());
        }//construction de la liste des IDs déja existants
    }

    void nouveau( string adresse){
        tab=get_data(adresse);
       int n = tab.size();
        for(int i =0;i<n;i++){
            IDs.push_back(tab[i]->get_ID());
        }//construction de la liste des IDs déja existants 
    }


    void afficher(){
        int n=tab.size();

        for(int i=0;i<n;i++){
            tab[i]->afficher();
        }
    }

    void save(){
        save_data(tab,adress);
    }

    void ajout(){

        string name;
        string des;
        string dc;
        string df;
        string status;
        int avan;
        string prio;
        string com;
        int a_st;
        
        int ID=0; //On cherche un ID qui est disponible
        
        int flag=1;
        int flag2=1;
        int n=IDs.size();
        while(flag){
            int i=0;
            while(i<n){
                if (IDs[i]==ID){
                    flag2=0;}
                i++;}
            if (flag2==0){//c'est que l'ID appartient déja à la liste
                ID++;
                flag2=1;}
            else {
                flag=0; //c'est que l'ID n'est pas dans la liste, on peut donc sortir de la boucle
                }

        }//ID est maintenant trouvé

        cout<<"Nom :"<<endl;
        cin.ignore();
        getline(cin,name);

        cout<<"Description :"<<endl;
        
        getline(cin,des);

        string rprio;
        int flag3=1;
        while(flag3){ //tant qu'il n'y a pas de bonne réponse on recommence
            cout<<"Priorité :"<<endl;
            cout<<"1 - Normal"<<endl;
            cout<<"2 - Prioritaire"<<endl;
            cout<<"q - annuler"<<endl;
            
            
            
            getline(cin,rprio);
            if(rprio=="1"){
                prio="Normal";
                flag3=0;
            }
            else if (rprio=="2"){
                prio="Prioritaire";
                flag3=0;
            }
            else if (rprio=="q"){
                menu_liste();
            }

            else {
                cout<<"Erreur"<<endl;
            }

        }

        string rdf;
        int flag5=1;
        while(flag5){ //tant qu'il n'y a pas de bonne réponse on recommence
            cout<<"Date limite avant la fin de la tâche ?"<<endl;
            cout<<"(au format JJ/MM/AAAA)"<<endl;
            cout<<"q - annuler"<<endl;
            
            
            getline(cin,rdf);
            if(rdf=="q"){
                menu_liste();
            }
            
            else if (rdf[2]=='/' && rdf[5]=='/'){//la date est au bon format
                df=rdf;
                flag5=0;
            }
            
            else {
                cout<<"Erreur"<<endl;
            }
        }

        cout<<"Commentaires :";
        
        getline(cin,com);

        int flag4=1;
        string rst;
        while(flag4){ //tant qu'il n'y a pas de bonne réponse on recommence
            cout<<"Ajouter une sous-tâche ?"<<endl;
            cout<<"q - annuler"<<endl;
            cout<<"1 - Oui"<<endl;
            cout<<"2 - Non"<<endl;
            
            
            
            getline(cin,rst);
            if(rst=="1"){//on veut créer des sous-taches : il faut faire apparaitre un nouveau menu qui permet d'en créer un
                a_st=1;
                //ajout_sous_tache(); // a coder
            }
            else if (rst=="2"){
                a_st=0;
                flag4=0;
            }
            else if (rst=="q"){
                menu_liste();
            }

            else {
                cout<<"Erreur"<<endl;
            }
        }
        
        dc=get_time();
        status="ouverte";

        Task* pt = new Task{name,dc,df,a_st,des,prio,ID};
        pt->commentaire(com);
        tab.push_back(pt);
        cout<<"nouvelle tâche ajoutée à la liste"<<endl;
        menu_liste();

    }


    void menu(){
        cout<<"----------- Menu-------------"<<endl<<endl;
        cout<<"1 - Nouvelle liste de tâches"<<endl;
        cout<<"2 - Ouvrir une liste de tâches"<<endl;
        cout<<"q - Quitter"<<endl;

        string rep;
        cin>>rep;

        if (rep=="1"){
            cout<<"Nom du fichier de sauvegarde"<<endl;
            cout<<"(au format nom_de_sauvegarde.txt"<<endl;
            string adresse;
            cin>>adresse;
            adress=adresse;
            menu_liste();
        }
            
        if (rep=="2"){
            cout<<"Adresse du fichier de sauvegarde"<<endl;
            string adresse;
            cin>>adresse;
            adress=adresse;
            nouveau(adress);
            menu_liste();

            
        }
        
        if (rep=="q" or rep=="Q"){
            throw invalid_argument("fin du programme");

        }

        
    }

    void menu_liste(){
        cout<<"----------- Menu - Liste de tâches -------------"<<endl<<endl;
        cout<<"1 - ajouter tâche"<<endl;
        cout<<"2 - liste des tâches"<<endl;
        cout<<"3 - modifier"<<endl;
        cout<<"4 - Sauvegarder"<<endl;
        cout<<"Q - quitter"<<endl;

        string rep;
        cin>>rep;

        if (rep=="1"){
            ajout();
        }
        if(rep=="2"){
            afficher();
            menu_liste();
        }
        if(rep=="3"){
            modifier();
        }
        if(rep=="4"){
            save();
            menu();
        }

        if (rep=="q" or rep=="Q"){
            throw invalid_argument("fin du programme");

        }
    }
    
    void modifier(){
        cout<< "---------------Tâche à modifier--------------"<<endl;
        int n=tab.size();
        for (int i=0;i<n;i++){
            cout<<i+1<<" - "<<tab[i]->get_name()<<endl;
        }
        string res;
        getline(cin,res);
        int ntask;
        ntask=stoi(res);

        cout<<"----------------Elément à modifier ------------"<<endl;
        cout<<"1 - Nom"<<endl;
        cout<<"2 - Date de fin"<<endl;
        cout<<"3 - Priorité"<<endl;
        cout<<"4 - Description"<<endl;
        cout<<"5 - Commentaire"<<endl;
        cout<<"Q - Menu"<<endl;

        string newres;

        if (res=="1"){
            cout<<"nouveau nom"<<endl;
            getline(cin,newres);
            

        }

    }


};







#endif