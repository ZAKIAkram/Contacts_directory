#ifndef _CONTACT_H_
#define _CONTACT_H_
#include <stdint.h>
#include <stdbool.h>

struct contact{
	char *nom;
	char *num;
	struct contact *suivant;
};
extern void affiche_liste(struct contact *cont);
extern void insere_tete(struct contact **contact,const char *nom,const char *num);
extern void insere_queue(struct contact **cont,const char *nom,const char *num);
extern void supprime_contact(struct contact **cont,const char *nom);
extern void contact_free(struct contact *cont);
#endif
