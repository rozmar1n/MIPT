#ifndef instructions_h
#define instructions_h

#include <stdlib.h>

const u_int32_t signatura = 82798384;

//TODO: массив структур для названия команды в ассемблере, в коде и ее номер 

enum instruction_t
{
    cmd_push           =  1,
    cmd_pushr          =  2,
    cmd_push_pushr     =  3,
    cmd_ram_push       =  5,
    cmd_ram_pushr      =  6,
    cmd_ram_push_pushr =  7,

    cmd_pop_r          = 8,
    cmd_pop_m          = 12,
    cmd_pop_m_r        = 14,
    cmd_pop_mpr        = 13,
    cmd_pop_mpm        = 15,

    cmd_add            =  28,
    cmd_sub            =  29,
    cmd_mul            =  30,
    cmd_div            =  31,
    cmd_out            =  32,
    cmd_in             =  33,
    cmd_sqrt           =  34,
    cmd_sin            =  35,
    cmd_cos            =  36,
    cmd_dump           =  37,
    cmd_jmp            =  39 ,
    cmd_ja             =  40,
    cmd_jae            =  41,
    cmd_jb             =  42,
    cmd_jbe            =  43,
    cmd_je             =  44,
    cmd_jne            =  45,
    cmd_hlt            = -1
};

enum registr_t
{
    ax = 0,
    bx = 1,
    cx = 2,
    dx = 3,
    ex = 4,
    fx = 5,
    gx = 6,
    hx = 7
};

#endif //instructions_h