#include"ImageFormatLookup.h"


int FormatLookup::addrForName(const char* name) {
    FormatLookup* lptr;

    for (lptr = ImgFormTable; lptr->name != NULL; lptr++)
        if (strcmp(lptr->name, name) == 0)
            break;

    return(lptr->value);
}