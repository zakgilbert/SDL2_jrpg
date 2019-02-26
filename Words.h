#ifndef JRPG_WORDS_H
#define JRPH_WORDS_H

#define FOREACH_STAT(STAT) \
    STAT(HP)  \
    STAT(MP)  \
    STAT(EXP) \

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

enum STAT_ENUM {
    FOREACH_STAT(GERERATE_ENUM)
};

static const char * STATS[] = {
    FOREACH_STAT(GENERATE_STRING)
};

#endif