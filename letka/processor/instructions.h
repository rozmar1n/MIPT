#ifndef instructions_h
#define instructions_h

enum instruction_t
{
    _cmd_push  =  1,
    _cmd_add   =  2,
    _cmd_sub   =  3,
    _cmd_mul   =  4,
    _cmd_div   =  5,
    _cmd_out   =  6,
    _cmd_in    =  7,
    _cmd_sqrt  =  8,
    _cmd_sin   =  9,
    _cmd_cos   = 10,
    _cmd_dump  = 11,
    _cmd_pop   = 12,
    _cmd_jmp   = 13,
    _cmd_ja    = 14,
    _cmd_jae   = 15,
    _cmd_jb    = 16,
    _cmd_jbe   = 17,
    _cmd_je    = 18,
    _cmd_jne   = 19,
    _cmd_pushr = 20,
    _cmd_hlt   = -1

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