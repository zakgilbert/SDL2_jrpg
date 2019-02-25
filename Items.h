#ifndef JRPG_ITEMS_H
#define JRPH_ITEMS_H

#define FOREACH_ITEM(ITEM) \
    ITEM(Potion) \
    ITEM(Ether)  \
    ITEM(Phoinex_Down) \
    ITEM(Soft)          \

#define GERERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING)  #STRING,

enum ITEM_ENUM {
    FOREACH_ITEM(GERERATE_ENUM)
};

static const char * ITEMS[] = {
    FOREACH_ITEM(GENERATE_STRING)
};

#endif