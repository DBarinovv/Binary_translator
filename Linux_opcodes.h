
//{============================================================================
//{                   LINUX OPCODES FOR BINARY TRANSLATOR                     ;
//}============================================================================

// Linux_opcodes.h

const char C_push_not_reg   = 0x6a;
const char C_push_reg       = 0x66;
const char C_push_start_reg = 0x50;

const char C_pop_reg        = 0x66;
const char C_pop_start_reg  = 0x58;

const char C_end[12] = {0xb8, 0x3c, 0, 0, 0,
                        0xbf, 0, 0, 0, 0,
                        0x0f, 0x05};

const char C_add_ax_bx[3] = {0x66, 0x01, 0xd8};

const char C_sub_ax_bx[3] = {0x66, 0x29, 0xd8};

const char C_mov_si_ax[3] = {0x66, 0x89, 0xc6};

const char C_mov_di_bx[3] = {0x66, 0x89, 0xdf};

const char C_mov_ax_si[3] = {0x66, 0x89, 0xf0};

const char C_mov_bx_di[3] = {0x66, 0x89, 0xfb};

const char C_xor_ah_ah[2] = {0x30, 0xe4};

const char C_div_bx[3]    = {0x66, 0xf7, 0xf3};

const char C_mul_bx[3]    = {0x66, 0xf7, 0xe3};

enum reg_offsets {
                    E_ax = 0,
                    E_bx = 3,
                    E_cx = 1,
                    E_dx = 2,
                    };
