
#ifndef ASSETS_H
#define ASSETS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"
#include "Item.h"
#include "Words.h"

Items * load_bag(Items * bag, int save_state);
void * save_bag(Items * bag, int save_state);


#endif /* ASSETS_H */

