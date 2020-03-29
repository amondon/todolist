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

// ce fichier est le fichier principal, il decrit les menus et actions sur la liste de tâches


class Editor{
    //prend un fichier et lit les données pour avoir une liste de taches
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
        cout<<"-------------- LISTE DES TACHES -----------------"<<endl;
        int n=tab.size();
        int ID;
        int avantp;
        int avanst;
        for(int i=0;i<n;i++){
            int k;
            
            k=tab[i]->is_st(); // permet de n'afficher que les tâches primaires (les tâches secondaires sont affichées avce leur tache associée)
            if(k==0){
                ID=tab[i]->get_ID();
                
                avantp=tab[i]->get_avancement();
                
                if(avantp==100){

                    cout<<i<<" - "<<tab[i]->get_name()<<"\t (fait)"<<endl;
                }
                else{
                    cout<<i<<" - "<<tab[i]->get_name()<<endl;
                }
                
                for (int j=0;j<n;j++){
                    if (tab[j]->st_de(ID)){
                        avanst=tab[j]->get_avancement();
                        
                        if(avanst==100){
                            cout<<"\t - "<<tab[j]->get_name()<<"\t (fait)"<<endl;
                        }
                        else{
                            cout<<"\t - "<<tab[j]->get_name()<<endl;
                        }
                    }
                }
            }
        }
        cout<<endl<<"--------------------------------"<<endl;
        cout<<" - tâche en cours"<<endl;
        cout<<" x tache effectuée"<<endl;
        cout<<"--------------------------------"<<endl;
        cout<<"taper le numéro d'un tâche pour avoir plus d'informations"<<endl;
        cout<<"Q ou q pour quitter"<<endl;

        string reponse;

        //cin.ignore();
        getline(cin,reponse);

        if(reponse=="q" or reponse=="Q"){
            menu_liste();
        }
        else{
            for (int i=0;i<n;i++){
                if(reponse==to_string(i)){
                    // il faut que ca n'affiche que si c'est une tâche primaire
                    if (tab[i]->is_st()==0){
                        tab[i]->afficher(tab);
                    }
                    
                    
                }
            }
            afficher();
        } 
            
        }
    

    

    void save(){
        save_data(tab,adress);
    }

    void ajout(){ //n indique si on créer une tâche ou une sous tâche

        string name;
        string des;
        string dc;
        string df;
        string status;
        int avan;
        string prio;
        string com;
        int a_st=0;
        int ID_st=0;
        
        int ID=1; //On cherche un ID qui est disponible
        
        int flag=1;
        int flag2=1;
        int m=IDs.size();
        while(flag){
            int i=0;
            while(i<m){
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

        IDs.push_back(ID); //dans le cas d'une sous tâche pour ne pas qu'elle ait le même id

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
        
        
        dc=get_time();
        status="ouverte";

        Task* pt = new Task{name,dc,df,a_st,ID_st,0,des,prio,ID};
        pt->commentaire(com);
        tab.push_back(pt);
        cout<<"nouvelle tâche ajoutée à la liste"<<endl;

        menu_sous_tache(ID);

    }

        
    void menu_sous_tache(int ID) {
        string rst;
        
        cout<<endl<<"Ajouter une sous-tâche ?"<<endl;
        //cout<<"l'id de la tâche primaire est :"<<ID<<endl;
        cout<<"1 - Oui"<<endl;
        cout<<"2 - Non"<<endl;
        
        getline(cin,rst);
        if(rst=="1"){//on veut créer des sous-taches : il faut faire apparaitre un nouveau menu qui permet d'en créer un
            ajout_sous_tache(ID);
            }
        else{
            menu_liste();
        }
              
    }


    void ajout_sous_tache(int id_tache_primaire){ //n indique si on créer une tâche ou une sous tâche

        string name;
        string des;
        string dc;
        string df;
        string status;
        int avan;
        string prio;
        string com;
        int a_st=1;
        int ID_st=id_tache_primaire; //car on a une sous-tâche
        
        int ID=1; //On cherche un ID qui est disponible
        
        int flag=1;
        int flag2=1;
        int m=IDs.size();
        while(flag){
            int i=0;
            while(i<m){
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

        IDs.push_back(ID); //dans le cas d'une sous tâche pour ne pas qu'elle ait le même id

        cout<<"Nom :"<<endl;
        //cin.ignore();
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
        
        
        dc=get_time();
        status="ouverte";

        Task* pt = new Task{name,dc,df,a_st,ID_st,0,des,prio,ID};
        pt->commentaire(com);
        tab.push_back(pt);
        cout<<"nouvelle sous-tâche ajoutée à la liste"<<endl;

        menu_sous_tache(id_tache_primaire);
    }

    void menu_valider(){
        cout<< "---------------Avancement--------------"<<endl;
        
        int n=tab.size();
        for (int i=0;i<n;i++){
            int k = tab[i]->is_st();
            if(k==0){
                cout<<i<<" - "<<tab[i]->get_name()<<" : "<<tab[i]->get_avancement()<<"%"<<endl;
            }
            
        }
        cout<<"---------------------------------------------"<<endl;
        cout<<"taper le numéro de la tâche pour modifier son avancement"<<endl;

        string res;
        cin>>res;
        
        valider(res);
    }


    void valider(string res){
        vector <int> st;
        int n=tab.size();
        for (int i=0;i<n;i++){
            
        }
    }

    void menu(){
        cout<<"----------- Menu-------------"<<endl<<endl;
        cout<<"1 - Nouvelle liste de tâches"<<endl;
        cout<<"2 - Ouvrir une liste de tâches"<<endl;
        cout<<"q - Quitter"<<endl;
        cout<<endl<<"     ----     "<<endl;

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
        cout<<"4 - valider une tâche"<<endl;
        cout<<"5 - Sauvegarder"<<endl;
        cout<<"Q - quitter"<<endl;
        cout<<endl<<"     ----  "<<endl;

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
            menu_valider();
        }
        if(rep=="5"){
            save();
            menu_liste();
        }

        if (rep=="q" or rep=="Q"){
            throw invalid_argument("fin du programme");

        }
    }
    
    
    void menu_modifier(string ntask){

        cout<<"----------------Elément à modifier ------------"<<endl;
        cout<<"1 - Nom"<<endl;
        cout<<"2 - Date de fin"<<endl;
        cout<<"3 - Priorité"<<endl;
        cout<<"4 - Ajouter un commentaire"<<endl;
        cout<<"5 - Description"<<endl;
        cout<<"Q - Menu"<<endl;

        cout<<ntask<<endl;

        string newres;
        int n;
        n=stoi(ntask);
        Task* pt = tab[n-1]; //pointeur qui pointe vers la tâche à modifier
        cin>>newres;
        cout<<endl;
        string rep;

        if (newres=="1"){
            cout<<"nouveau nom :"<<endl;
            cin.ignore();
            getline(cin,rep);
            cout<<endl;
            pt-> change_name(rep);
            cout<<"le nom de la tâche a été changé"<<endl;
            menu_modifier(ntask);

        }

        else if (newres=="2"){
            cout<<"nouvelle date de fin :"<<endl;
            cin.ignore();

            getline(cin,rep);
            cout<<endl;
            pt-> change_df(rep);
            menu_modifier(ntask);

        }

        else if (newres=="3"){
            cout<<"changement de priorité"<<endl;
            cout<<"----------------Priorité ------------"<<endl;
            cout<<"1 - Normale"<<endl;
            cout<<"2 - Prioritaire"<<endl;
            cout<<"Q - Retour"<<endl;

            cin.ignore();

            getline(cin,rep);
            
            if (rep=="1"){
                pt->change_prio("normale");

            }

            else if(rep=="2"){
                pt->change_prio("prioritaire");
            }
            else if(rep=="q" or rep=="Q"){
                menu_modifier(ntask);
            }
            else{
                cout<<"erreur"<<endl;
                menu_modifier(ntask);
            }
            
            cout<<"la priorité a été changée"<<endl;
            menu_modifier(ntask);
        }

        else if (newres=="4"){
            cout<<"Commentaires à ajouter : "<<endl;
            cin.ignore();

            getline(cin,rep);

            pt->commentaire("-" + rep);
            menu_modifier(ntask);
        }

        

        else if (newres=="5"){
            cout<<"------Menu - Description--------"<<endl;
            cout<<"1 - ajout de descriptions"<<endl;
            cout<<"2 - remplacer la description"<<endl;
            cout<<"Q - Retour"<<endl;
            
            cin.ignore();

            getline(cin,rep);
            

            if (rep=="1"){
                cout<<"description à ajouter : "<<endl;
                cin.ignore();
                getline(cin,rep);
                pt->description('a',"\n"+ rep);
                menu_modifier(ntask);
            }

            else if (rep=="2"){
                cout<<"nouvelle description : "<<endl;
                cin.ignore();
                getline(cin,rep);
                pt->description('w',rep);
                menu_modifier(ntask);}

            else if(rep=="q" or rep=="Q"){
                menu_modifier(ntask);
            }
            else{
                cout<<"erreur"<<endl;
                menu_modifier(ntask);
            }

        }

        else if (newres=="Q" or newres=="q"){
            menu_liste();
        }

        else{
            cout<<"erreur"<<endl;
            menu_modifier(ntask);
        }

    }

    void modifier(){
        cout<< "---------------Tâche à modifier--------------"<<endl;
        int n=tab.size();
        for (int i=0;i<n;i++){
            cout<<i+1<<" - "<<tab[i]->get_name()<<endl;
        }
        string res;
        cin>>res;
        
         //numéro de la tâche à modifier, on la passe en argument de la fonction suivante
        menu_modifier(res);
    }   


};







#endif