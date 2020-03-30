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
        
        //gestion des sous-tâches
        int a_st{};//permet de savoir si notre tache est une sous-tache d'une autre tache 0=tache, 1=sous-tache
        int ID_st;//ID de la tâche primaire associée
    public :

    Task(){}
    Task(string n,string datec ,string datef,int s =0,int id_st=0,int avancement=0,string d="",string p="normale",int i=0):name(n),des(d),prio(p),a_st(s),ID_st(id_st),ID(i),avan(avancement){
        
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
        
        
        //cout<<"nouvelle tache ajoutée"<<endl;
        }

    /*Task(const Task& t){ //constructeur de copie (sert pour le cas pù l'on a des sous-tâches, la copie n'est alors pas immédiate)
        name=t.name;
        ID=t.ID;
        dc=t.dc;
        df=t.df;
        status=t.status;
        avan=t.avan;
        prio=t.prio;
        com=t.com;
        a_st=t.a_st;
        int n=st.size();
        for (int i=0;i<n;i++){
            t.st[i]=st[i]
        }

    }*/

    void afficher( vector <Task*> tab){ // affichage d'une tache dans le terminal
        cout<<endl<<endl;
        
        if(a_st==0){
            cout<<"-------------- DESCRIPTION DETAILLEE -----------------"<<endl;}
        cout<<"Nom :              "<<name<<endl;
        cout<<"Description :      "<<des<<endl;
        cout<<"Identifiant :      "<<ID<<endl;
        cout<<"Avancement :       "<<avan<<endl;
        cout<<"Statut :           "<<status<<endl;
        cout<<"Priorité :         "<<prio<<endl;
        cout<<"Date de création : "<<dc<<endl;
        cout<<"Date de fin :      "<<df<<endl;
        cout<<"Commentaires :     "<<com<<endl;
        cout<<"      ----------------------------------------      "<<endl;

        if (a_st==0){ //si ce n'est pas une sous tâche :
            cout<<"\t --- SOUS-TACHES --- "<<endl;
            int bo=1;
            int n;
            int k;
            n=tab.size();
            for (int i=0;i<n;i++){
                k=tab[i]->st_de(ID); //on regarde si c'est une sous tâche de notre tâche
                if(k==1){
                    cout<<endl;
                    bo=0;
                    tab[i]->afficher(tab);
                    }
                
                }
            if (bo==1){
                    cout<<"pas de sous-tâche"<<endl;}
            cout<<endl<<endl;
            
            }
        }
       
    


    string save(){ //créer une chaine de caractère au bon format pour être sauvegarder dans un fichier texte
        string x;
        x=name+"\n"+des+"\n"+"\n"+to_string(ID)+"\n"+to_string(a_st)+"\n"+to_string(ID_st)+"\n"+to_string(avan)+"\n"+prio+"\n"+status+"\n"+dc+"\n"+df+"\n"+com+"\n";
        return x;
    }
    
        
        
    // les méthodes ci-dessous permettent la modification et la lecture des attributs

   

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

    int get_avancement(){
        return avan;
    } 

    void avancement (int s){
        avan=s;       
        
    }  

    
    void commentaire (string c){
        com=com+"\n"+c;
        //cout<<"Commentaires : "<<com<<endl;

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

    void change_name (string new_name){
        name=new_name;
    }

    void change_df (string new_df){
        if (new_df[2]=='/' and new_df[5]=='/'){
            df=new_df;
            cout<<"la date de fin a été changée"<<endl;
            
            }
        else { 
            cout<<"date de fin de tâche au mauvais format"<<endl;
            }
    }

    void change_prio(string new_prio){
        prio=new_prio;
    }
    
    int st_de(int id){ // est ce que la tâche est sous tache de la tache id
        if (ID_st==id){
            return 1;
        }
        else{
            return 0;
        }
    }
    int is_st(){
        return a_st;
    }

    void ID_tp(int ID){
        ID_st=ID;
    }


};

#endif