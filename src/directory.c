#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "directory.h"
#include "contact.h"
#include "hash.h"
/*
structure  de directory
*/
struct dir{
  uint32_t taille;
  uint32_t nb_contact;
  struct contact **tableau;
};

/*
  Crée un nouvel annuaire contenant _len_ listes vides.
*/
struct dir *dir_create(uint32_t len)
{
  /*
  Allocation 
  */
  struct dir *directory = malloc(sizeof(struct dir));
  /*
  Allocation de memoire pour un tableau plein de NULL d'un longueur len
  */
  directory->tableau = calloc(len,sizeof(struct contact *));
  /*
  on fixe es valeurs de taille et le nombre de contact(0 pour le moment)
  */
  directory->taille = len;
  directory->nb_contact = 0;
  return directory;
}
/*
redimensionnement: agrandissement
*/
void redimensionner_plus(struct dir *dir){
  /*
  On alloue au nouveau tableau le double de la taille du tableau qu'on a déjà
  */
    struct contact **nouveau_tableau = calloc(2* dir->taille, sizeof(struct contact *));
    /*
    on parcours tous les contacts (les listes) pour les stocker dans le nouveau tableau
    */
    for (uint32_t i = 0; i<dir->taille; i++){
        /* current c'est la liste courante */
        struct contact *current = dir->tableau[i];
        /*on parcours tous les contacts*/
        while( current != NULL){
          uint32_t taille =  2 * dir->taille;
          /* le nouveau emplacement du contact dans le tableau de nouvelle taille (2 * ancienne taille) */
          uint32_t emplacement = hash(current->nom) % taille;
          /* on insère le contact dans le nouveau tableau */
          insere_tete(&nouveau_tableau[emplacement], current->nom, current->num);
          /* on passe au contact suivant*/
          current = current->suivant;
        }
        /* on libère la mémoire allouée pour la liste dans l'ancien tableau */
        contact_free(dir->tableau[i]);
    }
    /* on libère la mémoire allouée pour l'ancien tableau */
    free(dir->tableau);
    /* on place le nouveau tableau dans dir->tableau*/
    dir->tableau = nouveau_tableau;
    /* on multiplie la taille par 2 */
    dir->taille = dir->taille * 2;
}

/*
redimensionnement : retrecissement
*/
void redimmensionner_moins(struct dir *dir){
  /* on alloue au nouveau tableau la moitié de la taille du tableau courant*/
  struct contact **nouveau_tableau = calloc(dir->taille / 2, sizeof(struct contact *));
  /* on parcours les listes pour les stocker dans le nouveau tableau */
  for( uint32_t i=0; i<dir->taille; i++){
    /* liste courante */
    struct contact *current = dir->tableau[i];
    /* on parcours tous les contacts */
    while(current != NULL){
      /* la nouvelle taille */
      uint32_t taille = dir->taille/2;
      /* emplacement du contact dans le nouveau tableau*/
      uint32_t emplacement = hash(current->nom) % taille;
      /* on insere le contact dans le nouveau tableau */
      insere_tete(&nouveau_tableau[emplacement], current->nom, current->num);
      /* on passe au contact suivant*/
      current = current->suivant;
    }
    /* on libère la mémoire allouée pour la liste courante */
    contact_free(dir->tableau[i]);
  }
  /* on libère la mémoire allouée au tableau*/
  free(dir->tableau);
  /* on place le nouveau tableau dans dir->tableau */
  dir->tableau = nouveau_tableau;
  /*  on divise la taille par 2*/
  dir->taille = dir->taille / 2;
}

/*
  Insère un nouveau contact dans l'annuaire _dir_, construit à partir des nom et
  numéro passés en paramètre. Si il existait déjà un contact du même nom, son
  numéro est remplacé et la fonction retourne une copie de l'ancien numéro.
  Sinon, la fonction retourne NULL.
*/
char *dir_insert(struct dir *dir, const char *name, const char *num)
{  
  /* on incrémente le nombre de contact par 1*/
  dir->nb_contact++;
  /* test pour l'agrandissement, s'il est vérifié, on agrandi l'annuaire*/
  if (dir->nb_contact >= 0.75 * dir->taille){
    redimensionner_plus(dir);
  }
  /* test de retrecissement: s'il est vérifié, on divise la taille du tableau par 2*/
  else if (dir->nb_contact <= 0.15 * dir->taille && dir->taille >= 20){
    redimmensionner_moins(dir);
  }
  /* emplacement du contact dans le tabeau suivant la valeur du hash*/
  uint32_t emplacement = hash(name) % dir->taille;
  /* liste c'est contact qui est dans l'emplacement du nom à inserer*/
  struct contact *liste = dir->tableau[emplacement];
  /* on parcours la liste des contact jusqu'à trouver le nom eventuellement */
  while( liste != NULL && liste->nom != name){
    liste = liste->suivant;
    }
    /* si le nom n'existe pas déjà */
  if(liste == NULL){
    /* on insère le nouveau contact */
    insere_tete(&dir->tableau[emplacement], name, num);
    return NULL;
    }
    /* cas si le nom existe déjà */
  else{
    /* on a déjà incrémenté, mais maintenant on va pas ajouter le contact, donc on décremente */
    dir->nb_contact--;
    /* on stock l'ancien numero dans acien_num */
    const char *ancien_num = dir->tableau[emplacement]->num;
    /* on change le numéro par le nouveau */
    dir->tableau[emplacement]->num =(char *) num;
    return (char *) ancien_num;
    }
  }
/*
  Retourne le numéro associé au nom _name_ dans l'annuaire _dir_. Si aucun contact
  ne correspond, retourne NULL.
*/
const char *dir_lookup_num(struct dir *dir, const char *name)
{   /* emplacement du contact dans le tableau suivant la valeur de hash */
    uint32_t emplacement = hash(name) % dir->taille;
    /* liste qui contient les contacts dont le hash est $emplacement */
    struct contact *liste = dir->tableau[emplacement];
    /* on parcours la liste jusqu'à trouver le contact dont le nome est *$name */ 
    while(liste != NULL && strcmp(liste->nom, name) != 0){
      liste = liste->suivant;
    }
    /* si le nom n'existe pas*/
    if (liste == NULL){
      return NULL;
    }
    /* si le nom existe */
    else{
      return (char *) liste->num;
    }
}

/*
  Supprime le contact de nom _name_ de l'annuaire _dir_. Si aucun contact ne
  correspond, ne fait rien.
*/
void dir_delete(struct dir *dir, const char *name)
{
    /* on décremente le nb de contact si le contact qu'on a voulu supprimé existait dans le tableau */
    const char *resultat = dir_lookup_num(dir, name);
    if( resultat != NULL){
      dir->nb_contact--;
    }
    /* emplacement du contact à supprimer dans le tableau*/
    uint32_t emplacement = hash(name) % dir->taille;
    /* on le supprime */
    supprime_contact(&dir->tableau[emplacement], name);
}
    
    


/*
  Libère la mémoire associée à l'annuaire _dir_.
*/
void dir_free(struct dir *dir)
{   
  /* on parcours toutes les listes pour libérer la mémoire allouée pour elles  */
  for(uint32_t i=0; i<dir->taille; i++){
    struct contact *current = dir->tableau[i];
    /* on libère la mémoire de la liste des contacts */
    contact_free(current);
  }
  /* on libère la mémoire allouée pour le tableau  */
  free(dir->tableau);
  /* on libère la mémoire allouée pour l'annuaire */
  free(dir);
}

/*
  Affiche sur la sortie standard le contenu de l'annuaire _dir_.
*/
void dir_print(struct dir *dir)
{
    /* on parcours toutes les listes pour les afficher*/
    for(uint32_t i = 0; i < dir->taille; i++){
        printf("----------case %i ------------ \n", i);
        affiche_liste(dir->tableau[i]);
        printf("----------------------------- \n");
    }
    printf("la taille de dir est %i\n", dir->taille);
    printf("le nb de contact est %i\n", dir->nb_contact);
    printf("FIN_dir\n");
}




