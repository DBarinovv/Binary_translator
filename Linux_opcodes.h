
//{============================================================================
//{                   LINUX OPCODES FOR BINARY TRANSLATOR                     ;
//}============================================================================

// Linux_opcodes.h

const unsigned char C_push_not_reg   = 0x6a;
const unsigned char C_push_reg       = 0x66;
const unsigned char C_push_start_reg = 0x50;

const unsigned char C_pop_reg        = 0x66;
const unsigned char C_pop_start_reg  = 0x58;

const unsigned char C_end[12] = {0xb8, 0x3c, 0, 0, 0,
                                 0xbf, 0, 0, 0, 0,
                                 0x0f, 0x05};

const unsigned char C_add_ax_bx[3] = {0x66, 0x01, 0xd8};

const unsigned char C_sub_ax_bx[3] = {0x66, 0x29, 0xd8};

const unsigned char C_mov_si_ax[3] = {0x66, 0x89, 0xc6};

const unsigned char C_mov_di_bx[3] = {0x66, 0x89, 0xdf};

const unsigned char C_mov_ax_si[3] = {0x66, 0x89, 0xf0};

const unsigned char C_mov_bx_di[3] = {0x66, 0x89, 0xfb};

const unsigned char C_xor_ah_ah[2] = {0x30, 0xe4};

const unsigned char C_div_bx[3]    = {0x66, 0xf7, 0xf3};

const unsigned char C_mul_bx[3]    = {0x66, 0xf7, 0xe3};

const unsigned char C_cmp_si_di[3] = {0x66, 0x39, 0xfe};

const unsigned char C_mov_offset_si[4]  = {0x66, 0x89, 0x34, 0x25};

const unsigned char C_mov_rdx_offset[4] = {0x48, 0x8b, 0x14, 0x25};

const unsigned char C_mov_rdi_not_reg = 0xbf;

const unsigned char C_mov_rax_not_reg = 0xb8;

const unsigned char C_mov_rsi_offset[2] = {0x48, 0xbe};

const unsigned char C_jmp = 0xe9;

const unsigned char C_je[2]   = {0x0f, 0x84};
const unsigned char C_ja[2]   = {0x0f, 0x87};
const unsigned char C_jae[2]  = {0x0f, 0x83};
const unsigned char C_jne[2]  = {0x0f, 0x85};
const unsigned char C_jb[2]   = {0x0f, 0x82};
const unsigned char C_jbe[2]  = {0x0f, 0x86};

enum reg_offsets {
                    E_ax = 0,
                    E_bx = 3,
                    E_cx = 1,
                    E_dx = 2,
                    E_si = 6,
                    E_di = 7,
                    };
