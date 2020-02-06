#ifndef _TASK_H

#define _TASK_H 

#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

class Task{
    private :
        string name {};
        string des;
        int ID{};
        string dc {};
        string df {};
        string status{};
        int avan {};
        string prio{};
        string com{};
        //vector<Task*> st {nullptr}; //tableau qui contient une liste de pointeurs qui chacun pointe vers une tâche qui est une sous-tâche
        //int sth{};//on est a quelle sous tache dans le tableau (pour pouvoir en ajouter une)
        int a_st{};//permet de savoir si notre tache est une sous-tache ou une tache primaire 0=tache, 1=sous-tache
        //int ID_st; //permet de savoir une tache est sous-tâche de quelle tâche
    public :

    Task(){}
    Task(string n,string datec ,string datef,int s =0,string d="",string p="normale",int i=0):name(n),des(d),prio(p),a_st(s),ID(i){
        
        //on vérifie que les dates soient au bon format

        //a modifier pour prendre automatiquement la date au moment de la création
        if (datec[2]=='/' and datec[5]=='/'){
            dc=datec;
            }
        else { 
            cout<<"date de création au mauvais format"<<endl;}

        if (datef[2]=='/' and datef[5]=='/'){
            df=datef;
            }
        else { 
            cout<<"date de fin de tâche au mauvais format"<<endl;}
        
        status="ouverte";
        avan=0;
        
        
        //sth=0;

        cout<<"nouvelle tache ajoutée"<<endl;}

    Task(const Task& t){
        name=t.name;
        ID=t.ID;
        dc=t.dc;
        df=t.df;
        status=t.status;
        avan=t.avan;
        prio=t.prio;
        com=t.com;
        a_st=t.a_st;

    }

    void afficher(){
        cout<<endl<<endl;
        cout<<"affichage :"<<endl;
        cout<<"Nom : "<<name<<endl;
        cout<<"Description : "<<des<<endl;
        cout<<"Identifiant : "<<ID<<endl;
        cout<<"Avancement : "<<avan<<endl;
        cout<<"Statut : "<<status<<endl;
        cout<<"Priorité : "<<prio<<endl;
        cout<<"Date de création : "<<dc<<endl;
        cout<<"Date de fin : "<<df<<endl;
        cout<<"Commentaires : "<<com<<endl<<endl<<endl;

        /*if (is_st==0){//s'affiche uniquement si l'on a une tache primaire
            cout<<"\t --- SOUS-TACHES --- "<<endl;
            cout<<"il y a "<<sth+1<<" sous-tache(s) en cours"<<endl<<endl;
            for (int i=0;i<sth+1;i++){
                cout<<endl;
                cout<<"Sous-tâche "<<i+1<<" : "<<endl;
                st[i]->afficher();
            }
            cout<<endl<<endl;}*/

        }
        


    string save(){
        string x;
        x=name+"\n"+des+"\n"+"\n"+to_string(ID)+"\n"+to_string(a_st)+"\n"+to_string(avan)+"\n"+prio+"\n"+status+"\n"+dc+"\n"+df+"\n"+com+"\n";
        return x;
    }
    
        
        
    

   

    void description(char a,string d=""){ //a definit r=read w=écrire (en supprimant celle existante a=add ajouter de la description)
        if (a=='r'){cout<<des<<endl;}
        else if (a=='w') {
            des=d;
            cout<<"Description : "<<des<<endl;
        }
        else if (a='a'){
            des+=d;
            cout<<"Description : "<<des<<endl;
            }

        
    }

    void statut(string s){
        
        if (s=="ouverte" or s=="fermée" or s=="en progession"){
            status=s;
            cout<<"Statut : "<<status<<endl;
        }
        else {cout<<"erreur : statut non modifié"<<endl;}
        
    }
        

    void priorite(string s){
        
        if (s=="normale" or s=="prioritaire"){
            prio=s;
            cout<<"Priorité : "<<prio<<endl;
        }
        else {cout<<"erreur : priorité non modifiée"<<endl;}
        
    }


    void avancement (int s){
        
        if (0<=s<=100){
            avan=s;
            cout<<"Avancement : "<<avan<<"%"<<endl;
        }
        else {cout<<"erreur : avancement non modifiée"<<endl;}
        
    }   

    void commentaire (string c){
        com=com+c;
        cout<<"Commentaires : "<<com<<endl;

    }

    int get_ID(){
        return ID;
    }

    string get_name(){
        return name;
    }
    /*void sous_tache (Task* st1){
        st.push_back(st1);
        sth++;
        cout<<"nouvelle sous_tâche ajoutée"<<endl;

    }*/


};

#endif