#ifndef _Z3DACTOR_H_
#define _Z3DACTOR_H_

#include "z3Dvec.h"

struct Actor;
struct GlobalContext;

struct LightMapper;

typedef struct {
    Vec3f pos;
    Vec3s rot;
} PosRot; // size = 0x14

typedef struct {
    /* 0x00 */ char   unk_00[0x8];
    /* 0x08 */ Vec3s  norm;  // Normal vector
    /* 0x0E */ s16    dist;  // Plane distance from origin
} CollisionPoly; // size = 0x10

typedef void (*ActorFunc)(struct Actor*, struct GlobalContext*);

typedef struct {
    /* 0x00 */ s16 id;
    /* 0x02 */ u8  type; // Classifies actor and determines when actor will execute
    /* 0x03 */ u8  room; // Room instance was spawned in. If value set to FF in rom, instance does not despawn when swapping rooms
    /* 0x04 */ u32 flags;
    /* 0x08 */ s16 objectId;
    /* 0x0C */ u32 instanceSize;
    /* 0x10 */ ActorFunc init; // Constructor
    /* 0x14 */ ActorFunc destroy; // Destructor
    /* 0x18 */ ActorFunc update; // Main Update Function
    /* 0x1C */ ActorFunc draw; // Draw function
} ActorInit; // size = 0x20

typedef enum {
    ALLOCTYPE_NORMAL,
    ALLOCTYPE_ABSOLUTE,
    ALLOCTYPE_PERMANENT
} AllocType;

typedef struct {
    /* 0x00 */ u32   vromStart;     // unused?
    /* 0x04 */ u32   vromEnd;       // unused?
    /* 0x08 */ void* vramStart;     // unused?
    /* 0x0C */ void* vramEnd;       // unused?
    /* 0x10 */ void* loadedRamAddr; // unused?
    /* 0x14 */ ActorInit* initInfo;
    /* 0x18 */ char* name;          // unused?
    /* 0x1C */ u16   allocType;     // unused?
    /* 0x1E */ s8    nbLoaded;      // unused?
} ActorOverlay; // size = 0x20

typedef struct {
    struct {
        char damage : 4;
        char effect : 4;
    } attack[32];
} ActorDamageChart;

typedef struct {
    /* 0x00 */ ActorDamageChart* damageChart;  // For actors which contain a damage chart (example: Stalfos)...
    /* 0x04 */ Vec3f displacement; // Amount to correct velocity (0x5C) by when colliding into a body
    /* 0x10 */ s16   unk_10;
    /* 0x12 */ s16   unk_12;
    /* 0x14 */ u16   unk_14;
    /* 0x16 */ u8    mass; // Used to compute displacement, 50 is common value, 0xFF for infinite mass/unmoveable
    /* 0x17 */ u8    health;
    /* 0x18 */ u8    damage; // Amount to decrement health by
    /* 0x19 */ u8    damageEffect; // Stores what effect should occur when hit by a weapon
    /* 0x1A */ u8    impactEffect; // Maybe? set on deku nut when deku nut collides with gossip stone
    /* 0x1B */ u8    unk_1B;
} SubActorStructA0; // size = 0x1C

typedef struct {
    /* 0x00 */ Vec3s  rot; // Current actor shape rotation
    /* 0x06 */ u8     unk_06;
    /* 0x08 */ f32    unk_08; // Model y axis offset. Represents model space units. collision mesh related
    /* 0x0C */ void (*shadowDrawFunc)(struct Actor*, struct LightMapper*, struct GlobalContext*);
    /* 0x10 */ f32    unk_10;
    /* 0x14 */ u8     unk_14;
    /* 0x15 */ u8     unk_15;
} ActorShape; // size = 0x18

typedef struct Actor {
    /* 0x000 */ s16     id; // Actor Id
    /* 0x002 */ u8      type; // Actor Type. Refer to the corresponding enum for values
    /* 0x003 */ s8      room; // Room number the actor is part of. FF denotes that the actor won't despawn on a room change
    /* 0x004 */ u32     flags; // Flags used for various purposes
    /* 0x008 */ PosRot  initPosRot; // Contains Initial Rotation when Object is Spawned
    /* 0x01C */ s16     params; // original name: "args_data"; Configurable variable set by an actor's spawn data
    /* 0x01E */ char    unk_1E[0xA];
    /* 0x028 */ PosRot  posRot; // Current coordinates
    /* 0x03C */ PosRot  posRot2; // Related to camera
    /* 0x050 */ f32     unk_4C;
    /* 0x054 */ Vec3f   scale; // Sets x,y,z scaling factor. Typically, a factor of 0.01 is used for each axis
    /* 0x060 */ Vec3f   velocity;
    /* 0x06C */ f32     speedXZ; // Always positive, stores how fast the actor is traveling along the XZ plane
    /* 0x070 */ f32     gravity; // Acceleration due to gravity; value is added to Y velocity every frame
    /* 0x074 */ f32     minVelocityY; // Sets the lower bounds cap on velocity along the Y axis
    /* 0x078 */ CollisionPoly* wallPoly; // Wall polygon an actor is touching
    /* 0x07C */ CollisionPoly* floorPoly; // Floor polygon an actor is over/touching
    /* 0x080 */ u8      wallPolySource; // Complex Poly Surface Source. 0x32 = Scene
    /* 0x081 */ u8      floorPolySource; // Complex Poly Surface Source. 0x32 = Scene. related to 0x80/88
    /* 0x082 */ char    unk_82[0x12];
    /* 0x094 */ f32     xzDistanceFromLink;
    /* 0x098 */ f32     yDistanceFromLink;
    /* 0x09C */ f32     unk_9C;
    /* 0x0A0 */ SubActorStructA0 sub_A0;
    /* 0x0BC */ ActorShape shape;
    /* 0x0D4 */ Vec3f   unk_D4[2];
    /* 0x0EC */ Vec3f   unk_EC; // Stores result of some vector transformation involving actor xyz vector, and a matrix at Global Context + 11D60
    /* 0x0F8 */ f32     unk_F8; // Related to above
    /* 0x0FC */ f32     unk_FC;
    /* 0x100 */ f32     unk_100;
    /* 0x104 */ f32     unk_104;
    /* 0x108 */ Vec3f   pos4; // Final Coordinates last frame
    /* 0x114 */ u8      unk_114; // Z-Target related
    /* 0x115 */ u8      unk_115; // Z-Target related
    /* 0x116 */ u16     textId; // Text id to pass to link/display when interacting with an actor (navi text, probably others)
    /* 0x118 */ char    unk_118[0x9];
    /* 0x121 */ u8      activelyDrawn; // Indicates whether the actor is currently being drawn (but not through lens). 01 for yes, 00 for no
    /* 0x122 */ u8      unk_122; // Set within a routine that deals with collision
    /* 0x123 */ u8      naviEnemyId; // Sets what 0600 dialog to display when talking to navi. Default 0xFF

    /* 0x124 */ struct Actor* attachedA; // Interfacing Actor?
    // e.g. Link holding chu, Chu instance stores ptr to Link instance here;
    //      Anju having Link's ptr when giving an item
    //      Volvagia Hole stores Volvagia Flying here

    /* 0x128 */ struct Actor* attachedB; // Attached to Actor
    // e.g. Link holding chu, Link instance stores ptr to Bombchu instance here

    /* 0x12C */ struct Actor* next; // Next Actor of this type
    /* 0x130 */ struct Actor* prev; // Previous Actor of this type

    /* 0x134 */ ActorFunc init; // Initialization Routine. Mandatory
    /* 0x138 */ ActorFunc destroy; // Destruction Routine
    /* 0x13C */ ActorFunc update; // Main Update Routine, called every frame the actor is to be updated
    /* 0x140 */ ActorFunc draw; // Draw Routine, writes necessary display lists

    /* 0x144 */ ActorOverlay* overlayEntry; // Pointer to the overlay table entry for this actor
   /* From here on, the structure and size varies for each actor */
} Actor; // size = 0x148

typedef struct {
    /* 0x00 */ Actor* actor;
    /* 0x04 */ char unk_04[0x10];
    /* 0x14 */ Vec3f scale1;
    /* 0x20 */ Vec3s rot1;
    /* 0x28 */ Vec3f pos1;
    /* 0x34 */ Vec3f scale2;
    /* 0x40 */ Vec3s rot2;
    /* 0x48 */ Vec3f pos2;
    /* 0x54 */ char unk_54[0x18];
} ActorMesh; // size = 0x6C

typedef struct {
    /* 0x0000 */ Actor actor;
    /* 0x0148 */ char  unk_148[0x20D4];
    /* 0x221C */ float xzSpeed; //probably
    /* 0x2220 */ char  unk_2220[0x0007];
    /* 0x2227 */ u8    isg;
} Player; //total size (from init vars): 2A4C

typedef enum {
    /* 0x00 */ ACTORTYPE_SWITCH,
    /* 0x01 */ ACTORTYPE_BG,
    /* 0x02 */ ACTORTYPE_PLAYER,
    /* 0x03 */ ACTORTYPE_EXPLOSIVES,
    /* 0x04 */ ACTORTYPE_NPC,
    /* 0x05 */ ACTORTYPE_ENEMY,
    /* 0x06 */ ACTORTYPE_PROP,
    /* 0x07 */ ACTORTYPE_ITEMACTION,
    /* 0x08 */ ACTORTYPE_MISC,
    /* 0x09 */ ACTORTYPE_BOSS,
    /* 0x0A */ ACTORTYPE_DOOR,
    /* 0x0B */ ACTORTYPE_CHEST
} ActorType;

typedef struct ActorHeapNode {
    u16 magic;
    u16 free;
    u32 size;
    struct ActorHeapNode* next;
    struct ActorHeapNode* prev;
} ActorHeapNode;

void Actor_Kill(Actor* actor);

#endif
