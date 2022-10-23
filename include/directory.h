#ifndef _DIRECTORY_H_
#define _DIRECTORY_H_
#include <stdint.h>

struct dir;
extern void redimensionner_plus(struct dir *dir);
extern void redimensionner_moins(struct dir *dir);
extern struct dir *dir_create(uint32_t len);
extern char *dir_insert(struct dir *dir, const char *name, const char *num);
extern const char *dir_lookup_num(struct dir *dir, const char *name);
extern void dir_delete(struct dir *dir, const char *name);
extern void dir_free(struct dir *dir);
extern void dir_print(struct dir *dir);
#endif
