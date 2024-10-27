#ifndef instructions_h
#define instructions_h

#include <stdlib.h>

const u_int32_t signatura = 82798384;

//TODO: массив структур для названия команды в ассемблере, в коде и ее номер 

enum instruction_t
{
    cmd_push  =  1,
    cmd_add   =  2,
    cmd_sub   =  3,
    cmd_mul   =  4,
    cmd_div   =  5,
    cmd_out   =  6,
    cmd_in    =  7,
    cmd_sqrt  =  8,
    cmd_sin   =  9,
    cmd_cos   = 10,
    cmd_dump  = 11,
    cmd_pop   = 12,
    cmd_jmp   = 13,
    cmd_ja    = 14,
    cmd_jae   = 15,
    cmd_jb    = 16,
    cmd_jbe   = 17,
    cmd_je    = 18,
    cmd_jne   = 19,
    cmd_pushr = 20,
    cmd_hlt   = -1

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