#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>

/*
la sructure contact:
c'est une liste chainée, dont chaque contact 
*/
struct contact{
    const char *nom;
    const char *num;
    struct contact *suivant;
};

/*
affiche sur la sortie la liste chainée des contact  
*/
void affiche_liste(struct contact *cont){
    while( cont != NULL){
        printf(" %s  : %s\n", cont->nom, cont->num);
        cont = cont->suivant;
    }
}
/*
insere un contact dans la tete de la liste chainnee
*/
void insere_tete(struct contact **cont, const char *nom,const char *num ){
    /*
        Allocation
    */
    struct contact *nouveau_contact = malloc(sizeof(struct contact));
    /*
    on fixe le nom, le numero et le suivant dans le nouveau contact
    */
    nouveau_contact -> nom = nom;
    nouveau_contact -> num = num;
    nouveau_contact -> suivant = *cont;
    /*
    on fait pointer le pointeur cont vers la nouvelle liste de contacts
    */
    *cont = nouveau_contact; 
}

/*
insere un contact dans la queue de la liste pointée par cont 
*/

void insere_queue(struct contact **cont,const char *nom,const char *num){
    /*
        Allocation
    */
     struct contact *nouveau_contact = malloc(sizeof(struct contact *));
     /*
     on fixe les valeurs du nouveau contact
     */
     nouveau_contact -> nom = nom;
     nouveau_contact -> num = num;
     /*
     on place une sentinelle pour  gérer tous les cas 
     */
     struct contact sentinelle = {"toto", "0000000000", *cont};
     struct contact *queue = &sentinelle;
     /*
     on parcours la liste jusqu'au dernier contact
     */
     while (queue -> suivant != NULL){
         queue = queue -> suivant; 
     }
     /*
        Allocation
     */
     queue -> suivant = malloc(sizeof(struct contact));
     queue -> suivant = nouveau_contact;
     queue -> suivant -> suivant = NULL;
     /*
     on fait pointer cont vesr la noouvelle liste
     */
     *cont = sentinelle.suivant;
 }
 

/*  
supprime la premiere occurence d'un contact dans la liste 
*/
void supprime_contact(struct contact **cont, const char *nom){
    struct contact sentinelle = {"toto", "0000000000", *cont};
    struct contact *p = &sentinelle;
    while ( p->suivant != NULL && p->suivant->nom != nom){
        p = p->suivant; 
    }
    /*
    si p->suivant->nom == nom
    */
    if (p->suivant != NULL){
        /*
        on rechaine les deux contact qui entourent le contact qu'on veut supprimer, 
        puis on le libère
        */
        struct contact *style = p->suivant;
        p->suivant = style->suivant;
        free(style); 
    }
    /*
    on fait pointer cont vers la nouvelle liste
    */
    *cont = sentinelle.suivant;
}
    /*
    libère la mémoire allouée à la liste des contacts
    */
void contact_free(struct contact *cont){
    /*
    on parcours tous les contact de la liste
    */
    while (cont != NULL){
        /*
        temp est un pointeur vers le contact suivant parce qu'on va libèrer le contact cont
        */
      struct contact *temp = cont->suivant;
      free(cont);
      cont = temp;
    }
}
