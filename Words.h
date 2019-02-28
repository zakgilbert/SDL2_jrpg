#ifndef JRPG_WORDS_H
#define JRPG_WORDS_H
#define FOREACH_ITEM(ITEM) \
    ITEM(POTION) \
    ITEM(ETHER) \
    ITEM(SOFT) \
    ITEM(PHOENIX_DOWN) \

#define FOREACH_STAT(STAT) \
    STAT(HP)  \
    STAT(MP)  \
    STAT(EXP) \

#define GERERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING)  #STRING,

typedef enum  {    
    FOREACH_ITEM(GERERATE_ENUM)
}ITEM_ENUM;

static const char * ITEMS[] = {
    FOREACH_ITEM(GENERATE_STRING)
};

enum STAT_ENUM {
    FOREACH_STAT(GERERATE_ENUM)
};

static const char * STATS[] = {
    FOREACH_STAT(GENERATE_STRING)
};

extern int ITEM_QUANTITY;
#endif
