#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>

extern void set_sortie_debug(FILE*);
extern void flog(const char*);
extern void flogf(const char*, ...);
extern void fermer_sortie_debug(void);

#endif
