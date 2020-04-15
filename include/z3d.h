/*
 * This is a modified version of a file originally by n3rdswithgame
 * In the future, this will be heavily revamped
 */

#ifndef Z3D_H
#define Z3D_H

#include "hid.h"

typedef void* (*memcpy_proc) (void* dst, void* src, uint32_t size);

#if Z3D == MM3D

// #define real_hid_addr   0x10002000
// #define hid_ctx_addr    0x007b2d30
// #define z3d_rupee_addr  0x00775318
// #define memcpy_addr     0x001f28e8

#elif Z3D == OOT3D

#define real_hid_addr   0x10002000
#define hid_ctx_addr    0x005AEC58
#define z3d_rupee_addr  0x005879A0
// #define memcpy_addr     0x00371738
#define z3d_file_addr   0x00587958
#define collision_addr  0x08080e82
//positive linear velocity: 0x098f5070
//signed linear velocity: 0x098f722c
//static context: 0x08080010
//game mode: 0x00588E3C . 1 for attract. 2 for file select. 0 for regular.
//level geometry: 0x08080fe0. 1 for disable.

#endif

#define real_hid        (*(hid_mem_t *) real_hid_addr)
#define hid_ctx         (*(hid_ctx_t *) hid_ctx_addr)
// #define memcpy          ((memcpy_proc)  memcpy_addr)
#define z3d_rupee       (*(uint16_t *)  z3d_rupee_addr)
#define actor_collision (*(uint16_t *)  collision_addr)

typedef struct
{
    uint16_t magic;
    uint16_t free;
    uint32_t size;
    struct heap_node_t* next;
    struct heap_node_t* prev;
} heap_node_t;

typedef struct
{
    int16_t x;
    int16_t y;
    int16_t z;
} z3d_xyz_t;

typedef struct
{
    float x;
    float y;
    float z;
} z3d_xyzf_t;

typedef struct
{
    uint16_t pitch;
    uint16_t yaw;
    uint16_t roll;
} z3d_rot_t;

typedef struct
{
    uint16_t id;                    //0x0
    uint8_t type;                   //0x2
    uint8_t room_number;            //0x3
    uint32_t ukn_0x04;              //0x4
    z3d_xyzf_t pos_1;               //0x8, 0xc, 0x10: Not actually pos always?
    z3d_rot_t spawn_angle;          //0x14, 0x16, 0x18
    uint16_t ukn_0x1a;              //0x1a
    uint16_t variable;              //0x1c: https://wiki.cloudmodding.com/oot/Actor_List_(Variables) */
    int8_t ukn_0x1E;                //0x1e  objTableIndex?
    uint8_t ukn_0x1f;               //0x1f
    uint8_t ukn_0x20[0x8];          //0x20  soundEffect?
    z3d_xyzf_t pos_2;               //0x28, 0x2c, 0x30
    z3d_rot_t rot_1;                //0x34, 0x36, 0x38
    //note: ISG is offset 2227
    uint8_t ukn4[0xe]; //0x3a-0x47
    z3d_rot_t rot_2; //0x48, 0x4a, 0x4c
    uint8_t ukn5[0x1e]; //0x4e-6b
    float positive_linear_velocity; //0x6c
    uint8_t ukn55[0x4c]; //0x70-0xbb
    z3d_rot_t rot_3; //0xbc, 0xbe, 0xc0
    uint8_t ukn6[0x215a]; //0xc2-0x221b
    float signed_linear_velocity; //0x221c
    uint8_t ukn7[0x7]; //0x2220-2226
    uint8_t isg; //0x2227
} actor_t;

struct z3d_save_ctx
{
    uint32_t entrance_index; //0x0
    uint32_t link_age; //0x4
    uint32_t cutscene_offset; //0x8
    uint16_t time_of_day; //0xc
    uint8_t  mq_flag; //0xe
    uint8_t  uknf1[0xd]; //0xf-0x1b
    uint16_t file_name[0x8]; //0x1c
    uint8_t  file_name_length; //0x2c
    uint8_t  targeting_mode; //0x2d
    uint16_t uknf2; //0x2e
    uint8_t  zeldaz[0x6]; //0x30
    uint16_t save_counter; //0x36
    uint8_t  uknf3[0xa]; //0x38
    uint16_t max_health; //0x42
    uint16_t cur_health; //0x44
    uint8_t  magic_meter_size; //0x46
    uint8_t  magic_amt; //0x47
    uint16_t rupee_count; //0x48
    uint8_t  uknf4[0xa]; //0x4a
    struct {
        uint8_t b_button;
        uint8_t y_button;
        uint8_t x_button;
        uint8_t I_button;
        uint8_t II_button;
        uint8_t y_button_slot;
        uint8_t x_button_slot;
        uint8_t I_button_slot;
        uint8_t II_button_slot;
        uint8_t unused;
        uint8_t sword_and_shield;
        uint8_t tunic_and_boots;
    }        equipment_data_child; //0x54
    struct {
        uint8_t b_button;
        uint8_t y_button;
        uint8_t x_button;
        uint8_t I_button;
        uint8_t II_button;
        uint8_t y_button_slot;
        uint8_t x_button_slot;
        uint8_t I_button_slot;
        uint8_t II_button_slot;
        uint8_t unused;
        uint8_t sword_and_shield;
        uint8_t tunic_and_boots;
    }        equipment_data_adult; //0x60
    uint8_t  uknf5[0x12]; //0x6c, unused
    uint16_t scene_index; //0x7e
    struct {
        uint8_t b_button;
        uint8_t y_button;
        uint8_t x_button;
        uint8_t I_button;
        uint8_t II_button;
        uint8_t y_button_slot;
        uint8_t x_button_slot;
        uint8_t I_button_slot;
        uint8_t II_button_slot;
        uint8_t unused_button;
        uint8_t sword_and_shield;
        uint8_t tunic_and_boots;
    }        equipment_data_current; //0x80
    uint8_t  item_slot_item[0x1a]; //0x8c
    uint8_t  item_slot_amount[0xf]; //0xa6
    uint8_t  magic_beans_available; //0xb5
    union {
        uint8_t  equipment_data[0x6];
        struct {
            uint16_t                     : 1;
            uint16_t mirror_shield       : 1;
            uint16_t hylian_shield       : 1;
            uint16_t deku_shield         : 1;
            uint16_t broken_giants_knife : 1;
            uint16_t giants_knife        : 1;
            uint16_t master_sword        : 1;
            uint16_t kokiri_sword        : 1;
            uint16_t                     : 1;
            uint16_t hover_boots         : 1;
            uint16_t iron_boots          : 1;
            uint16_t kokiri_boots        : 1;
            uint16_t                     : 1;
            uint16_t zora_tunic          : 1;
            uint16_t goron_tunic         : 1;
            uint16_t kokiri_tunic        : 1;
            uint16_t strength_upgrade    : 2;
            uint16_t bomb_bag            : 3;
            uint16_t quiver              : 3;
            uint16_t bullet_bag          : 2;
            uint16_t wallet_upgrade      : 2;
            uint16_t dive_meter          : 3;
            uint16_t glitched_strength   : 1;
            uint16_t unused_equipment    : 1;
            uint16_t deku_nut_capacity   : 3;
            uint16_t deku_stick_capacity : 3;
            uint16_t glitched_bullet_bag : 1;
            uint16_t unused_equipment2   : 8;
        };
    };  //0xb6
    union {
        uint32_t quest_status_data;
        struct {
            uint16_t bolero_of_fire      : 1;
            uint16_t minuet_of_forest    : 1;
            uint16_t light_medallion     : 1;
            uint16_t shadow_medallion    : 1;
            uint16_t spirit_medallion    : 1;
            uint16_t water_medallion     : 1;
            uint16_t fire_medallion      : 1;
            uint16_t forest_medallion    : 1;
            uint16_t suns_song           : 1;
            uint16_t sarias_song         : 1;
            uint16_t eponas_song         : 1;
            uint16_t zeldas_lullaby      : 1;
            uint16_t prelude_of_light    : 1;
            uint16_t nocturne_of_shadow  : 1;
            uint16_t requiem_of_spirit   : 1;
            uint16_t serenade_of_water   : 1;
            uint16_t gold_skulltula      : 1;
            uint16_t gerudos_card        : 1;
            uint16_t shard_of_agony      : 1;
            uint16_t zoras_sapphire      : 1;
            uint16_t gorons_ruby         : 1;
            uint16_t kokiris_emerald     : 1;
            uint16_t song_of_storms      : 1;
            uint16_t song_of_time        : 1;
            uint16_t heart_pieces        : 8;
        };
    };  //0xbc
    uint8_t  dungeon_items[0x14]; //0xc0
    uint8_t  small_key_amount[0x14]; //0xd4
    uint8_t  golden_skulls_amount; //0xe8
    uint8_t  uknf7[3]; //0xe9
    uint8_t  scene_data_records[0xb0c]; //0xec
    uint8_t  uknf8[0x284]; //0xbf8
    struct {
        uint32_t fw_pos_and_rot[0x5]; //TODO: figure this out
        uint32_t fw_entrance;
        uint32_t fw_room_number;
        uint32_t fw_is_set;
    }        fw_data; //0xe7c
    uint8_t  uknf9[0x18]; //0xe9c
    uint8_t  skulltula_flags[0x16]; //0xeb4
    uint8_t  uknf10[0x6]; //0xeca
    uint32_t horseback_archery_highscore; //0ed0
    uint8_t  uknf11[0x8]; //0xed4
    uint32_t horse_race_record_time; //0xedc
    uint32_t marathon_race_record_time; //0xee0
    uint8_t  uknf12[0x8]; //0xee4
    uint8_t  event_flags[0x64]; //0xeec
    uint32_t world_map_data; //0xf50
    uint8_t  uknf13[0x4]; //0xf54
    uint8_t  scarecrow_song[0x360]; //0xf58
    uint8_t  uknf14[0xb8]; //0x12b8
    uint8_t  item_slot_data_record[0x1a]; //0x1370
    uint8_t  inventory_grid_data_child[0x18]; //0x138a
    uint8_t  inventory_grid_data_adult[0x18]; //0x13a2
    uint16_t uknf15; //0x13ba
    struct {
        uint32_t year;
        uint32_t month;
        uint32_t day;
        uint32_t hour;
        uint32_t minute;
    }        save_timestamp; //0x13bc
    uint32_t uknf16; //0x13d0
    uint8_t  sheikah_interaction_flag; //0x13d4
    uint8_t  uknf17[0x7b]; //0x13d5
    struct {
        uint32_t gohma;
        uint32_t king_dodongo;
        uint32_t barinade;
        uint32_t phantom_ganon;
        uint32_t volvagia;
        uint32_t morpha;
        uint32_t bongo_bongo;
        uint32_t twinrova;
        uint32_t gauntlet;
    }        boss_battle_victories; //0x1450
    struct {
        uint32_t gohma;
        uint32_t king_dodongo;
        uint32_t barinade;
        uint32_t phantom_ganon;
        uint32_t volvagia;
        uint32_t morpha;
        uint32_t bongo_bongo;
        uint32_t twinrova;
        uint32_t gauntlet;
    }        boss_battle_record_times; //0x1474
    uint8_t  sheikah_stone_guide_flags[0x40]; //0x1498
    uint32_t uknf18; //0x14d8
    //more can be filled in here from
    //https://cloudmodding.com/zelda/oot3dsave
};

#define actor_heap_begin_addr_maybe 0x005a2E3C
#define link_addr ((*((void**)actor_heap_begin_addr_maybe)) + sizeof(heap_node_t)) //should always be 0x908f5010 but that is more slightly more proper
//#define link_addr 0x098f5010
//#define z3d_file_addr 0x00587958
//#define inventory_grid_addr 0x00588ce2

#define link (*((actor_t *)link_addr))
#define z3d_file (*(struct z3d_save_ctx*) z3d_file_addr)

#endif //Z3D_H