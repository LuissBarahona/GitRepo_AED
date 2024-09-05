#include <iostream>
#include <cmath>
#include <string>
using namespace std;


struct Node {
    string web;      
    Node* next;
    Node* prev;
};

class BrowserHistory {

private:
    Node* head; // Atributo que sera homepage
    Node* tail; // Atributo que sera ultimo elemento de lista
    Node* punterotemp;

public:

    BrowserHistory(string homepage) {
        head=NULL;
        tail=NULL;

        Node* inicio=new Node;
        inicio->web=homepage;
        inicio->prev=NULL;
        inicio->next=NULL;

        head=inicio;
        tail=inicio;
        punterotemp=inicio;
    }

    void push_back(string valor){ // Agrega un elemento al final
        Node* nodo = new Node;
        nodo->web = valor;
        nodo->next=NULL;
        nodo->prev=tail;
        
        if(tail!=NULL){
            tail->next=nodo;
        }
        // Si era el primer elemento
        if(head==NULL && tail==NULL){
            head=nodo;
        }
        tail=nodo;
    }
    
    void visit(string url) {

        tail=punterotemp; // Cierro mi lista a donde apunta
        push_back(url);
        punterotemp=tail; //Hago update al puntero
        cout<<"Visite un nuevo lado, hago update y soy "<<punterotemp->web<<endl;  
    }
    
    string back(int steps) {
        int i=0;
        bool termino = true;
        bool final=true;
        while(punterotemp!=NULL && termino==true){

            if(punterotemp==head){
                final=false;
                termino=false;
            }else{
                punterotemp=punterotemp->prev;
                i++;
                if(i==steps){
                    // Llego a la cantidad de steps, ahora devuelvo la url
                    termino=false;

                }else if(punterotemp==head){
                    // No puedes moverte mas
                    termino=false;
                    cout<<"Entre aqui"<<endl;
                }else if(punterotemp==NULL){
                    final=false;
                    // No puedes moverte mas
                    termino=false;
                }
            }
        }

        if(final==false){
            cout<<"Estoy ahora en "<<head->web<<endl;
            punterotemp=head;
            return head->web;
        }else if(termino==false){
            cout<<"Estoy ahora en "<<punterotemp->web<<endl;
            return punterotemp->web;
        }else{
            return "";
        }
        
    }
    
    string forward(int steps) {
        int i=0;
        bool termino = true;
        bool final=true;
        while(punterotemp!=NULL && termino==true){
            if(punterotemp==tail){
                final=false;
                termino=false;
            }else{
                 punterotemp=punterotemp->next;
                 i++;
                if(i==steps){
                    // Llego a la cantidad de steps, ahora devuelvo la url
                    termino=false;
                    //return punterotemp->web;
                }else if(punterotemp==tail){
                    // No puedes moverte mas
                    termino=false;
                }else if(punterotemp==NULL){
                    final=false;
                    // No puedes moverte mas
                    termino=false;
                }
            }            
        }
        if(final==false){
            cout<<"Estoy ahora en "<<tail->web<<endl;
            punterotemp=tail;
            return tail->web;
        }else if(termino==false){
            cout<<"Estoy ahora en "<<punterotemp->web<<endl;
            return punterotemp->web;
        }else{
            return "";
        }
        
    }
};