#ifndef PARSE_S_H
#define PARSE_S_H

#define NO_FILE ""

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Index/index.h"
#include "Index/listcoll.h"
#include "search.h"

LinkedIndexObjListPtr readld(char *file_name);

#endif
