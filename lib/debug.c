#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "debug.h"

static FILE* SORTIE_DEBUG;

void flog(const char* message) {
	if (SORTIE_DEBUG == NULL) return;
	fputs(message, SORTIE_DEBUG);
	fputs("\n", SORTIE_DEBUG);
}

void flogf(const char *message, ...) {
	if (SORTIE_DEBUG == NULL) return;
	va_list args;

	va_start(args, message);
	vfprintf(SORTIE_DEBUG, message, args);
	va_end(args);
}

void set_sortie_debug(FILE* sortie) {
	fermer_sortie_debug();
	SORTIE_DEBUG = sortie;
}

void fermer_sortie_debug() {
	if (SORTIE_DEBUG != NULL) {
		fclose(SORTIE_DEBUG);
	}
}
