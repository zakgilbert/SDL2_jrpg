#ifndef JRPG_WORDS_H
#define JRPG_WORDS_H
#define FOREACH_ITEM(ITEM) \
    ITEM(POTION)           \
    ITEM(ETHER)            \
    ITEM(SOFT)             \
    ITEM(PHOENIX_DOWN)

#define FOREACH_STAT(STAT) \
    STAT(HP)               \
    STAT(MP)               \
    STAT(EXP)

#define FOREACH_MENU_OPTION(MENU_OPTION) \
    MENU_OPTION(Items)                   \
    MENU_OPTION(Skills)                  \
    MENU_OPTION(Magic)                   \
    MENU_OPTION(Status)                  \
    MENU_OPTION(Config)                  \
    MENU_OPTION(Save)                    \
    MENU_OPTION(Exit)

#define GERERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

typedef enum
{
    FOREACH_ITEM(GERERATE_ENUM)
} ITEM_ENUM;

enum STAT_ENUM
{
    FOREACH_STAT(GERERATE_ENUM)
};

typedef enum
{
    FOREACH_MENU_OPTION(GERERATE_ENUM)
} MENU_OPTIONS;

extern int ITEM_QUANTITY;
#endif
