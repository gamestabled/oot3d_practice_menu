#ifndef _Z3D_H_
#define _Z3D_H_

#include "z3Dactor.h"
#include "z3Dvec.h"
#include "z3Dequipment.h"

#include "hid.h"

typedef struct {
    /* 0x00 */ u8 buttonItems[5];
    /* 0x05 */ u8 buttonSlots[4];
    /* 0x0A */ u16 equipment;
} ItemEquips; // size = 0x0C

typedef struct {
    /* 0x00 */ u32   chest;
    /* 0x04 */ u32   swch;
    /* 0x08 */ u32   clear;
    /* 0x0C */ u32   collect;
    /* 0x10 */ u32   unk;
    /* 0x14 */ u32   rooms1;
    /* 0x18 */ u32   rooms2;
} SaveSceneFlags; // size = 0x1C

typedef struct {
    /* 0x00 */ s16   scene;
    /* 0x02 */ Vec3s pos;
    /* 0x08 */ s16   angle;
} HorseData; // size = 0x0A

typedef struct {
    /* 0x00 */ Vec3f pos;
    /* 0x0C */ s16   yaw;
    /* 0x0E */ s16   playerParams;
    /* 0x10 */ s16   entranceIndex;
    /* 0x12 */ u8    roomIndex;
    /* 0x13 */ s8    data;
    /* 0x14 */ u32   tempSwchFlags;
    /* 0x18 */ u32   tempCollectFlags;
} RespawnData; // size = 0x1C

typedef enum {
    /* 0x00 */ RESPAWN_MODE_DOWN,   /* Normal Void Outs */
    /* 0x01 */ RESPAWN_MODE_RETURN, /* Grotto Returnpoints */
    /* 0x02 */ RESPAWN_MODE_TOP     /* Farore's Wind */
} RespawnMode;

typedef enum {
    /* 0x00 */ BTN_ENABLED,
    /* 0xFF */ BTN_DISABLED = 0xFF
} ButtonStatus;

// Save Context (ram start: 0x00587958)
typedef struct {
    /* 0x0000 */ s32          entranceIndex;
    /* 0x0004 */ s32          linkAge; // 0: Adult; 1: Child
    /* 0x0008 */ s32          cutsceneIndex;
    /* 0x000C */ u16          dayTime; // "zelda_time"
    /* 0x000E */ u8           masterQuestFlag;
    /* 0x000F */ char         unk_F[0x0001];
    /* 0x0010 */ s32          nightFlag;
    /* 0x0014 */ s32          unk_14;
    /* 0x0018 */ s32          unk_18;
    /* 0x001C */ s16          playerName[0x8];
    /* 0x002C */ u8           playerNameLength;
    /* 0x002D */ u8           zTargetingSetting;
    /* 0x002E */ s16          unk_2E;
    /* 0x0030 */ char         newf[6]; // string "ZELDAZ"
    /* 0x0036 */ u16          saveCount;
    /* 0x0038 */ char         unk_38[0x000A];
    /* 0x0042 */ u16          healthCapacity; // "max_life"
    /* 0x0044 */ s16          health; // "now_life"
    /* 0x0046 */ s8           magicLevel;
    /* 0x0047 */ s8           magic;
    /* 0x0048 */ s16          rupees;
    /* 0x004A */ u16          bgsHitsLeft;
    /* 0x004C */ u16          naviTimer;
    /* 0x004E */ u8           magicAcquired;
    /* 0x004F */ char         unk_4F;
    /* 0x0050 */ u8           doubleMagic;
    /* 0x0051 */ u8           doubleDefense;
    /* 0x0052 */ s8           bgsFlag;
    /* 0x0054 */ ItemEquips   childEquips;
    /* 0x0060 */ ItemEquips   adultEquips;
    /* 0x006C */ char         unk_6C[0x0012];
    /* 0x007E */ u16          sceneIndex;
    /* 0x0080 */ ItemEquips   equips;
    /* 0x008C */ u8           items[26];
    /* 0x00A6 */ s8           ammo[16];
    /* 0x00B6 */ u16          equipment; //bits: swords 0-3, shields 4-6, tunics 8-10, boots 12-14
    /* 0x00B8 */ u32          upgrades; //bits: quiver 0-2, bombs 3-5, strength 6-8, dive 9-11, wallet 12-13, seeds 14-16, sticks 17-19, nuts 20-22
    /* 0x00BC */ u32          questItems; //bits: medallions 0-5, warp songs 6-11, songs 12-17, stones 18-20, shard 21, token 22, skull 23, heart pieces 24-31
    /* 0x00C0 */ u8           dungeonItems[20];
    /* 0x00D4 */ s8           dungeonKeys[19];
    /* 0x00E7 */ char         unk_E7[0x0001]; //in oot: defenseHearts. seems not here.
    /* 0x00E8 */ s16          gsTokens;
    /* 0x00EC */ SaveSceneFlags sceneFlags[124];
    struct {
        /* 0x0E7C */ Vec3i pos;
        /* 0x0E88 */ s32  yaw;
        /* 0x0E8C */ s32  playerParams;
        /* 0x0E90 */ s32  entranceIndex;
        /* 0x0E94 */ s32  roomIndex;
        /* 0x0E98 */ s32  set;
        /* 0x0E9C */ s32  tempSwchFlags;
        /* 0x0EA0 */ s32  tempCollectFlags;
    }                         fw;
    /* 0x0EA4 */ char         unk_EA4[0x0010];
    /* 0x0EB4 */ u8           gsFlags[22]; //due to reordering, array is smaller
    /* 0x0ECA */ char         unk_ECA[0x0006]; //the extra two bytes move here
    /* 0x0ED0 */ u32          unk_ED0; //horseback archery highscore?
    /* 0x0ED4 */ char         unk_ED4[0x0008];
    /* 0x0EDC */ u32          unk_EDC; //horse race record time?
    /* 0x0EE0 */ u32          unk_EE0; //marathon race record time?
    /* 0x0EE4 */ char         unk_EE4[0x0008];
    /* 0x0EEC */ u16          eventChkInf[14]; // "event_chk_inf"
    /* 0x0F08 */ u16          itemGetInf[4]; // "item_get_inf"
    /* 0x0F10 */ u16          infTable[30]; // "inf_table"
    /* 0x0F4C */ char         unk_F34[0x0004];
    /* 0x0F50 */ u32          worldMapAreaData; // "area_arrival"
    /* 0x0F54 */ char         unk_F54[0x0410]; // TODO: scarecrow's song
    /* 0x1364 */ HorseData    horseData;
    /* 0x136E */ char         unk_136E[0x0002];
    /* 0x1370 */ u8           itemSlotDataRecords[26];
    /* 0x138A */ u8           itemMenuChild[24];
    /* 0x13A2 */ u8           itemMenuAdult[24];
    /* 0x13BA */ char         unk_13BA[0x0002];
    struct {
        /* 0x13BC */ u32 year;
        /* 0x13C0 */ u32 month;
        /* 0x13C4 */ u32 day;
        /* 0x13C8 */ u32 hour;
        /* 0x13CC */ u32 minute;
    }                         saveTime;
    /* 0x13D0 */ char         unk_13D0[0x0080];
    /* 0x1450 */ u32          bossBattleVictories[9];
    /* 0x1474 */ u32          bossBattleScores[9];
    /* 0x1498 */ char         unk_1498[0x0040]; //sheikah stone flags?
    /* 0x14D8 */ u16          checksum; // "check_sum"
    /* 0x14DC */ s32          fileNum; // "file_no"
    /* 0x14E0 */ char         unk_14E0[0x0004];
    /* 0x14E4 */ s32          gameMode;
    /* 0x14E8 */ s32          sceneSetupIndex;
    /* 0x14EC */ s32          respawnFlag; // "restart_flag"
    /* 0x14F0 */ RespawnData  respawn[3]; // "restart_data"
    /* 0x1544 */ char         unk_1544[0x000E];
    /* 0x1552 */ s16          nayrusLoveTimer;
    /* 0x1554 */ char         unk_1554[0x0008];
    /* 0x155C */ s16          rupeeAccumulator;
    /* 0x155E */ s16          timer1State;
    /* 0x1560 */ s16          timer1Value;
    /* 0x1562 */ s16          timer2State;
    /* 0x1564 */ s16          timer2Value;
    /* 0x1566 */ s16          timerX[2]; //changing these doesn't seem to actually move the timer?
    /* 0x156A */ s16          timerY[2]; //changing these doesn't seem to actually move the timer?
    /* 0x156E */ char         unk_156E[0x0024];
    /* 0x1592 */ u16          dungeonIndex;
    /* 0x1594 */ char         unk_1594[0x001E];
    /* 0x15B2 */ s16          healthAccumulator;

//stuff below is from z64.h
/* skipped over */
    // /* 0x0022 */ s16          deaths;
    // /* 0x002C */ s16          n64ddFlag;
    // /* 0x0072 */ char         unk_72[0x0002];
    // /* 0x00CF */ s8           defenseHearts;
    // /* 0x0F3C */ char         unk_F3C[0x040C];
    // /* 0x13BC */ char         unk_13BC[0x0008];
    // /* 0x13C4 */ s16          dogParams;
    // /* 0x13C6 */ char         unk_13C6[0x0001];
    // /* 0x13C7 */ u8           unk_13C7;

/* still to compare */
    // /* 0x13CA */ char         unk_13CA[0x0002];

    // /* 0x13DE */ char         unk_13DE[0x0002];
    // /* 0x13E0 */ u8           seqIndex;
    // /* 0x13E1 */ u8           nightSeqIndex;
    // /* 0x13E2 */ u8           buttonStatus[5];
    // /* 0x13E7 */ u8           unk_13E7;
    // /* 0x13E8 */ u16          unk_13E8; // alpha type?
    // /* 0x13EA */ u16          unk_13EA; // also alpha type?
    // /* 0x13EC */ u16          unk_13EC; // alpha type counter?
    // /* 0x13EE */ u16          unk_13EE; // previous alpha type?
    // /* 0x13F0 */ s16          unk_13F0;
    // /* 0x13F2 */ s16          unk_13F2;
    // /* 0x13F4 */ s16          unk_13F4;
    // /* 0x13F6 */ s16          unk_13F6;
    // /* 0x13F8 */ s16          unk_13F8;
    // /* 0x13FA */ u16          eventInf[4]; // "event_inf"
    // /* 0x1404 */ u16          minigameState;
    // /* 0x1406 */ u16          minigameScore; // "yabusame_total"
    // /* 0x1408 */ char         unk_1408[0x0001];
    // /* 0x1409 */ u8           language;
    // /* 0x140A */ u8           audioSetting;
    // /* 0x140B */ char         unk_140B[0x0001];
    // /* 0x140C */ u8           zTargetingSetting; // 0: Switch; 1: Hold
    // /* 0x140E */ u16          unk_140E; // bgm related
    // /* 0x1410 */ u8           unk_1410;
    // /* 0x1411 */ u8           unk_1411;
    // /* 0x1412 */ u16          nextCutsceneIndex;
    // /* 0x1414 */ u8           cutsceneTrigger;
    // /* 0x1415 */ u8           chamberCutsceneNum;
    // /* 0x1416 */ u16          nextDayTime; // "next_zelda_time"
    // /* 0x1418 */ u8           fadeDuration;
    // /* 0x1419 */ u8           unk_1419; // transition related
    // /* 0x141A */ u16          environmentTime;
    // /* 0x141C */ u8           dogIsLost;
    // /* 0x141D */ u8           nextTransition;
    // /* 0x141E */ char         unk_141E[0x0002];
    // /* 0x1420 */ s16          worldMapArea;
    // /* 0x1422 */ s16          unk_1422; // day time related
} SaveContext; // size = 0x1428

typedef struct GraphicsContext GraphicsContext; //TODO

typedef struct {
    /* 0x00 */ u32    length; // number of actors loaded of this type
    /* 0x04 */ Actor* first;  // pointer to first actor of this type
} ActorListEntry; // size = 0x08

typedef struct {
    /* 0x0000 */ u8     unk_00;
    /* 0x0001 */ char   unk_01[0x01];
    /* 0x0002 */ u8     unk_02;
    /* 0x0003 */ u8     unk_03;
    /* 0x0004 */ char   unk_04[0x04];
    /* 0x0008 */ u8     total; // total number of actors loaded
    /* 0x0009 */ char   unk_09[0x03];
    /* 0x000C */ ActorListEntry actorList[12];
    // /* 0x006C */ TargetContext targetCtx;
    // struct {
    //     /* 0x0104 */ u32    swch;
    //     /* 0x0108 */ u32    tempSwch;
    //     /* 0x010C */ u32    unk0;
    //     /* 0x0110 */ u32    unk1;
    //     /* 0x0114 */ u32    chest;
    //     /* 0x0118 */ u32    clear;
    //     /* 0x011C */ u32    tempClear;
    //     /* 0x0120 */ u32    collect;
    //     /* 0x0124 */ u32    tempCollect;
    // }                   flags;
    // /* 0x0128 */ TitleCardContext titleCtx;
    // /* 0x0138 */ char   unk_138[0x04];
    // /* 0x013C */ void*  absoluteSpace; // Space used to allocate actor overlays of alloc type 1
} ActorContext; // TODO: size = 0x140

typedef struct GameState {
    /* 0x00 */ GraphicsContext* gfxCtx;
    /* 0x04 */ void (*main)(struct GameState*);
    /* 0x08 */ void (*destroy)(struct GameState*); // "cleanup"
    /* 0x0C */ void (*init)(struct GameState*);
    //TODO
} GameState;

// Global Context (ram start: 0871E840)
typedef struct GlobalContext {
    // /* 0x00000 */ GameState state;
    /* 0x00000 */ char         unk_0[0x05C00];
    /* 0x0208C */ ActorContext actorCtx;
    /* 0x020F8 */ char         unk_20F0[0x3B08];
    /* 0x05C00 */ u8           linkAgeOnLoad;
    /* 0x05C01 */ char         unk_5C01[0x0002C];
    /* 0x05C2D */ s8           sceneLoadFlag; //fade_direction"
    /* 0x05C2E */ char         unk_5C2E[0x00004];
    /* 0x05C32 */ s16          nextEntranceIndex;
    /* 0x05C34 */ char         unk_5C34[0x00042];
    /* 0x05C76 */ u8           fadeOutTransition;
    //TODO
} GlobalContext;

extern GlobalContext* gGlobalContext;
extern const u32 ItemSlots[];
#define gSaveContext (*(SaveContext*)0x00587958)
#define PLAYER ((Player*)gGlobalContext->actorCtx.actorList[ACTORTYPE_PLAYER].first)

enum Item {
    ITEM_DEKU_STICK = 0,
    ITEM_DEKU_NUT,
    ITEM_BOMB,
    ITEM_FAIRY_BOW,
    ITEM_FIRE_ARROW,
    ITEM_DINS_FIRE,
    ITEM_FAIRY_SLINGSHOT,
    ITEM_FAIRY_OCARINA,
    ITEM_OCARINA_OF_TIME,
    ITEM_BOMBCHU,
    ITEM_HOOKSHOT,
    ITEM_LONGSHOT,
    ITEM_ICE_ARROW,
    ITEM_FARORES_WIND,
    ITEM_BOOMERANG,
    ITEM_LENS_OF_TRUTH,
    ITEM_MAGIC_BEANS,
    ITEM_MEGATON_HAMMER,
    ITEM_LIGHT_ARROW,
    ITEM_NAYRUS_LOVE,
    ITEM_EMPTY_BOTTLE,
    ITEM_RED_POTION,
    ITEM_GREEN_POTION,
    ITEM_BLUE_POTION,
    ITEM_BOTTLE_FAIRY,
    ITEM_FISH,
    ITEM_LON_LON_MILK,
    ITEM_LETTER,
    ITEM_BLUE_FIRE,
    ITEM_BUG,
    ITEM_BIG_POE,
    ITEM_LON_LON_MILK_HALF,
    ITEM_POE, //to be continued...
    ITEM_WEIRD_EGG,
    ITEM_CUCCO,
    ITEM_ZELDAS_LETTER,
    ITEM_KEATON_MASK,
    ITEM_SKULL_MASK,
    ITEM_SPOOKY_MASK,
    ITEM_BUNNY_HOOD,
    ITEM_GORON_MASK,
    ITEM_ZORA_MASK,
    ITEM_GERUDO_MASK,
    ITEM_MASK_OF_TRUTH,
    ITEM_NO_MASK,
    ITEM_POCKET_EGG,
    ITEM_POCKET_CUCCO,
    ITEM_COJIRO,
    ITEM_ODD_MUSHROOM,
    ITEM_ODD_POULTICE,
    ITEM_POACHERS_SAW,
    ITEM_GORONS_SWORD_BROKEN,
    ITEM_PRESCRIPTION,
    ITEM_EYE_BALL_FROG,
    ITEM_EYE_DROPS,
    ITEM_CLAIM_CHECK,
    ITEM_FAIRY_BOW_PLUS_FIRE_ARROW,
    ITEM_FAIRY_BOW_PLUS_ICE_ARROW,
    ITEM_FAIRY_BOW_PLUS_LIGHT_ARROW,
    ITEM_KOKIRI_SWORD,
    ITEM_MASTER_SWORD,
    ITEM_GIANTS_KNIFE,
    ITEM_DEKU_SHIELD,
    ITEM_HYLIAN_SHIELD,
    ITEM_MIRROR_SHIELD,
    ITEM_KOKIRI_TUNIC,
    ITEM_GORON_TUNIC,
    ITEM_ZORA_TUNIC,
    ITEM_KOKIRI_BOOTS,
    ITEM_IRON_BOOTS,
    ITEM_HOVER_BOOTS,
    ITEM_EMPTY = 0xFF,
};

enum Dungeon {
    DUNGEON_DEKU_TREE = 0,
    DUNGEON_DODONGOS_CAVERN,
    DUNGEON_JABUJABUS_BELLY,
    DUNGEON_FOREST_TEMPLE,
    DUNGEON_FIRE_TEMPLE,
    DUNGEON_WATER_TEMPLE,
    DUNGEON_SPIRIT_TEMPLE,
    DUNGEON_SHADOW_TEMPLE,
    DUNGEON_BOTTOM_OF_THE_WELL,
    DUNGEON_ICE_CAVERN,
    DUNGEON_GANONS_CASTLE_SECOND_PART,
    DUNGEON_GERUDO_TRAINING_GROUNDS,
    DUNGEON_GERUDO_FORTRESS,
    DUNGEON_GANONS_CASTLE_FIRST_PART,
    DUNGEON_GANONS_CASTLE_FLOOR_BENEATH_BOSS_CHAMBER,
    DUNGEON_GANONS_CASTLE_CRUMBLING,
    DUNGEON_TREASURE_CHEST_SHOP,
    DUNGEON_DEKU_TREE_BOSS_ROOM,
    DUNGEON_DODONGOS_CAVERN_BOSS_ROOM,
    DUNGEON_JABUJABUS_BELLY_BOSS_ROOM,
};

/* TODO: figure out what to do with this stuff */
#define real_hid_addr   0x10002000
#define real_hid        (*(hid_mem_t *) real_hid_addr)

#define Z3D_TOP_SCREEN_LEFT_1 0x14313890
#define Z3D_TOP_SCREEN_LEFT_2 0x14359DA0
#define Z3D_TOP_SCREEN_RIGHT_1 0x14410AD0
#define Z3D_TOP_SCREEN_RIGHT_2 0x14456FE0
#define Z3D_BOTTOM_SCREEN_1 0x143A02B0
#define Z3D_BOTTOM_SCREEN_2 0x143D86C0

#endif //_Z3D_H_