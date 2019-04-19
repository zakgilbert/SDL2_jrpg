#ifndef JRPG_WORDS_H
#define JRPG_WORDS_H

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

#define FOREACH_ITEM(ITEM) \
    ITEM(POTION)           \
    ITEM(ETHER)            \
    ITEM(SOFT)             \
    ITEM(PHOENIXDOWN)

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

#define FOREACH_ACTION_OPTION(ACTION_OPTION) \
    ACTION_OPTION(Attack)                    \
    ACTION_OPTION(Spell)                     \
    ACTION_OPTION(Quaff)

#define FOREACH_SPELL(SPELL) \
    SPELL(Fire)              \
    SPELL(Ice)               \
    SPELL(Bolt)

#define FOREACH_CHARACTER_BATTLE_FRAME(FRAME) \
    FRAME(stand)                              \
    FRAME(pray_1)                             \
    FRAME(cast)                               \
    FRAME(step)                               \
    FRAME(hit)                                \
    FRAME(defend)                             \
    FRAME(pray_2)                             \
    FRAME(cast_step)                          \
    FRAME(wound)                              \
    FRAME(dead)

typedef enum
{
    FOREACH_ITEM(GENERATE_ENUM)
} ITEM_ENUM;

enum STAT_ENUM
{
    FOREACH_STAT(GENERATE_ENUM)
};

typedef enum
{
    FOREACH_MENU_OPTION(GENERATE_ENUM)
} MENU_OPTION_ENUM;

typedef enum
{
    FOREACH_ACTION_OPTION(GENERATE_ENUM)
} ACTION_OPTION_ENUM;

enum SPELL_ENUM
{
    FOREACH_SPELL(GENERATE_ENUM)
};

typedef enum
{
    FOREACH_CHARACTER_BATTLE_FRAME(GENERATE_ENUM)
};

extern int ITEM_QUANTITY;
#endif
