
//{============================================================================
//{                             BINARY TRANSLATOR                             ;
//{                                                     (c) Barinov Denis     ;
//}============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "My_elf.h"
#include "Linux_opcodes.h"
#include "OneginLib.h"
#include "enum.h"
#include "Help_functions.h"

//=============================================================================
//                    CONSTANS FOR ELF AND PROGRAM HEADERS                    ;
//=============================================================================

const elf::Elf64_Half	C_my_e_type      = 0x0002;
const elf::Elf64_Half	C_my_e_machine   = 0x003E;
const elf::Elf64_Word	C_my_e_version   = 0x00000001;
const elf::Elf64_Addr	C_my_e_entry     = 0x0000000000400300;
const elf::Elf64_Off	C_my_e_phoff     = 0x0000000000000040;
const elf::Elf64_Off	C_my_e_shoff     = 0x00000000;
const elf::Elf64_Word	C_my_e_flags     = 0x00000000;
const elf::Elf64_Half	C_my_e_ehsize    = 0x0040; // 64 bit
const elf::Elf64_Half	C_my_e_phentsize = 0x0038; // 64 bit
const elf::Elf64_Half	C_my_e_phnum     = 0x0001; // default
const elf::Elf64_Half	C_my_e_shentsize = 0x0040; // 64 bit
const elf::Elf64_Half	C_my_e_shnum     = 0x0000; // because without any sections
const elf::Elf64_Half	C_my_e_shstrndx  = 0x0000; // because without any sections


const elf::Elf64_Word	C_my_p_type   = 0x00000001;
const elf::Elf64_Word	C_my_p_flags  = 0x00000007;
const elf::Elf64_Off 	C_my_p_offset = 0x0000000000000000;
const elf::Elf64_Addr	C_my_p_vaddr  = 0x0000000000400000;
const elf::Elf64_Addr	C_my_p_paddr  = 0x0000000000400000;
const elf::Elf64_Xword	C_my_p_filesz = 0x0000000000000000; // TBA
const elf::Elf64_Xword	C_my_p_memsz  = 0x0000000000000000; // TBA
const elf::Elf64_Xword	C_my_p_align  = 0x0000000000001000;

//=============================================================================
//                                PROTOTYPES                                  ;
//=============================================================================


void Make_Default_ELF_Header (elf::Elf64_Ehdr *elf_header);

void Make_Default_Program_Header (elf::Elf64_Phdr *program_header);

void Make_Res_File (const elf::Elf64_Ehdr *elf_header, elf::Elf64_Phdr *program_header, unsigned char *res,
                    const char * strings_arr, const int strings_arr_pos, const int counter, FILE *fout);

void Make_Right_Jumps (const char *buf, unsigned char *res, const int *offsets_arr, const int sz_file);

void Make_Right_Print (const char *buf, unsigned char *res, const int *offsets_arr,
                       const char *strings_arr, const int sz_file, const int counter);

//-----------------------------------------------------------------------------

inline void Move_Si_Ax (unsigned char *res, int *counter);

inline void Move_Di_Bx (unsigned char *res, int *counter);

inline void Pop_Reg    (unsigned char *res, int *counter, const int offset);

inline void Push_Reg   (unsigned char *res, int *counter, const int offset);

inline void Move_Ax_Si (unsigned char *res, int *counter);

inline void Move_Bx_Di (unsigned char *res, int *counter);

inline void Add_Ax_Bx  (unsigned char *res, int *counter);

inline void Sub_Ax_Bx  (unsigned char *res, int *counter);

inline void Mul_Bx     (unsigned char *res, int *counter);

inline void Idiv_Bl    (unsigned char *res, int *counter);

inline void Imul_Bl    (unsigned char *res, int *counter);

inline void Idiv_Bx    (unsigned char *res, int *counter);

inline void Div_Bx     (unsigned char *res, int *counter);

inline void Xor_Ah_Ah  (unsigned char *res, int *counter);

inline void Cmp_Si_Di  (unsigned char *res, int *counter);

inline void Add_Si_Di  (unsigned char *res, int *counter);

inline void Sub_Si_Di  (unsigned char *res, int *counter);

inline void Move_Si_Not_Reg (unsigned char *res, int *counter);

inline void Move_Rsi_Offset (unsigned char *res, int *counter);

inline void Syscall    (unsigned char *res, int *counter);

//=============================================================================

int main ()
{
    char *name_of_fin  = "output.txt";
    char *name_of_fout = "Elf_file_quadratic";

    int sz_file = Find_Size_Of_File (name_of_fin);

    FILE* fin  = fopen (name_of_fin,  "rb"); assert (fin);
    FILE* fout = fopen (name_of_fout, "wb"); assert (fout);

    char *buf = (char *) calloc (sz_file + 1, sizeof (char)); assert (buf);
    fread (buf, sizeof (char), sz_file + 1, fin);

    elf::Elf64_Ehdr elf_header = {};
    Make_Default_ELF_Header (&elf_header);

    elf::Elf64_Phdr program_header = {};
    Make_Default_Program_Header (&program_header);


     #define DEF_CMD(name, num, code, arg)                                   \
        case CMD_##name:                                                     \
            code                                                             \


    #define REALLOC_RES                                                                             \
    {                                                                                               \
        if (counter + 10 >= sz_res)                                                                 \
        {                                                                                           \
            sz_res *= 2;                                                                            \
            res = (unsigned char *) realloc (res, sz_res * sizeof (unsigned char)); assert (res);   \
        }                                                                                           \
    }


    int *offsets_arr  = (int *)  calloc (sz_file + 1, sizeof (int));  assert (offsets_arr);
    char *strings_arr = (char *) calloc (0x101,       sizeof (char)); assert (strings_arr);

    unsigned char *res = (unsigned char *) calloc (sz_file * 10, sizeof (unsigned char)); assert (res);

    int strings_arr_pos = 0;
    int counter = 0;
    int pos = 0;
    int sz_res = sz_file;

    while (pos < sz_file)
    {
        switch (buf[pos])
        {
        #include "Commands.h"
        default:
            break;
        }
    }

    #undef DEF_CMD
    #undef REALLOC_RES


    res[7]  = 1;  // a }
    res[15] = 1;  // b | ax**2 + bx + c = 0 (for tests)
    res[23] = -6; // c }

    Make_Right_Jumps (buf, res, offsets_arr, sz_file);

    Make_Right_Print (buf, res, offsets_arr, strings_arr, sz_file, counter);

    Make_Res_File (&elf_header, &program_header, res, strings_arr, strings_arr_pos, counter, fout);

    return 0;
}

//=============================================================================

void Make_Default_ELF_Header (elf::Elf64_Ehdr *elf_header)
{
    assert (elf_header);

    elf_header->e_ident[0] = '';  // 0x7f
    elf_header->e_ident[1] = 'E';
    elf_header->e_ident[2] = 'L';
    elf_header->e_ident[3] = 'F';

    elf_header->e_ident[4] = 0x02;
    elf_header->e_ident[5] = 0x01;
    elf_header->e_ident[6] = 0x01;
    elf_header->e_ident[7] = 0x00;
    elf_header->e_ident[8] = 0x00;

    elf_header->e_type      = C_my_e_type;
    elf_header->e_machine   = C_my_e_machine;
    elf_header->e_version   = C_my_e_version;
    elf_header->e_entry     = C_my_e_entry;
    elf_header->e_phoff     = C_my_e_phoff;
    elf_header->e_shoff     = C_my_e_shoff;
    elf_header->e_flags     = C_my_e_flags;
    elf_header->e_ehsize    = C_my_e_ehsize;
    elf_header->e_phentsize = C_my_e_phentsize;
    elf_header->e_phnum     = C_my_e_phnum;
    elf_header->e_shentsize = C_my_e_shentsize;
    elf_header->e_shnum     = C_my_e_shnum;
    elf_header->e_shstrndx  = C_my_e_shstrndx;
}

//-----------------------------------------------------------------------------

void Make_Default_Program_Header (elf::Elf64_Phdr *program_header)
{
    assert (program_header);

    program_header->p_type	 = C_my_p_type;
    program_header->p_flags	 = C_my_p_flags;
    program_header->p_offset = C_my_p_offset;
    program_header->p_vaddr	 = C_my_p_vaddr;
    program_header->p_paddr	 = C_my_p_paddr;
    program_header->p_filesz = C_my_p_filesz;
    program_header->p_memsz	 = C_my_p_memsz;
    program_header->p_align  = C_my_p_align;
}

//-----------------------------------------------------------------------------

void Make_Res_File (const elf::Elf64_Ehdr *elf_header, elf::Elf64_Phdr *program_header, unsigned char *res,
                    const char * strings_arr, const int strings_arr_pos, const int counter, FILE *fout)
{
    assert (elf_header);
    assert (program_header);
    assert (res);
    assert (strings_arr);
    assert (fout);


    program_header->p_filesz = 0x300 + counter + 1;
    program_header->p_memsz  = 0x300 + counter + 1;


    fwrite (elf_header,     sizeof (elf::Elf64_Ehdr), 1, fout);
    fwrite (program_header, sizeof (elf::Elf64_Phdr), 1, fout);


    unsigned char jump_to_start[0x100 - 0x78] = {C_jmp};
    * (int *) (jump_to_start + 1) = 0x400300 - 0x400078 - 5;

    jump_to_start[0x80 - 0x78 + 0x13] = ' '; // for OUT

    fwrite (jump_to_start, 0x100 - 0x78, 1, fout);


    unsigned char helper[0x100] = {
                                  #include "Out_number_proc.h"
                                  ,
                                  #include "Sqrt_proc.h"
                                  };

    fwrite (helper, 0x100, 1, fout);


    fwrite (strings_arr, 0x100, sizeof (char), fout);

    fwrite (res, counter, sizeof (unsigned char), fout);
}

//-----------------------------------------------------------------------------

void Make_Right_Jumps (const char *buf, unsigned char *res, const int *offsets_arr, const int sz_file)
{
    assert (buf);
    assert (res);
    assert (offsets_arr);


    int ind = 0;
    while (ind < sz_file)
    {
        if (11 <= buf[ind] && buf[ind] <= 16) // ja, je, jae, jbe, jne, je
        {
            int dif = offsets_arr[(* (int *) (buf + ind + 1))] - offsets_arr[ind] - 14;

            * (int *) (res + offsets_arr[ind] + 10) = dif;
        }
        else if (buf[ind] == 17) // jmp
        {
            int dif = offsets_arr[(* (int *) (buf + ind + 1))] - offsets_arr[ind] - 5; // 5 = len (jump)

            * (int *) (res + offsets_arr[ind] + 1) = dif;
        }

        ind++;
    }
}

//-----------------------------------------------------------------------------

void Make_Right_Print (const char *buf, unsigned char *res, const int *offsets_arr,
                       const char *strings_arr, const int sz_file, const int counter)
{
    assert (buf);
    assert (res);
    assert (offsets_arr);
    assert (strings_arr);


    int ind = 0;
    int cnt = 0;

    while (ind < sz_file)
    {
        if (buf[ind] == CMD_OUT)
        {
            * (int *) (res + offsets_arr[ind] + 6) = 0x100 - 0x300 - offsets_arr[ind] - 10;
        }
        else if (buf[ind] == CMD_PRT)
        {
            int global_offset = 0x400200 + cnt * 20;

            * (int *) (res + offsets_arr[ind] + 12) = global_offset;

            * (int *) (res + offsets_arr[ind] + 21) = strlen (buf + ind + 1);

            cnt++;
        }
        else if (buf[ind] == CMD_SQRT)
        {
            * (int *) (res + offsets_arr[ind] + 9) = 0x171 - 0x300 - offsets_arr[ind] - 10;
        }

        ind++;
    }
}

//=============================================================================

inline void Move_Si_Ax (unsigned char *res, int *counter)
{
    assert (res);

    res[(*counter)++] = C_mov_si_ax[0];              //}
    res[(*counter)++] = C_mov_si_ax[1];              //| mov si, ax
    res[(*counter)++] = C_mov_si_ax[2];              //}
}

//-----------------------------------------------------------------------------

inline void Move_Di_Bx (unsigned char *res, int *counter)
{
    assert (res);

    res[(*counter)++] = C_mov_di_bx[0];              //}
    res[(*counter)++] = C_mov_di_bx[1];              //| mov di, bx
    res[(*counter)++] = C_mov_di_bx[2];              //}
}

//-----------------------------------------------------------------------------

inline void Pop_Reg (unsigned char *res, int *counter, const int offset)
{
    assert (res);

    res[(*counter)++] = C_pop_reg;                   //}
    res[(*counter)++] = C_pop_start_reg + offset;    //} pop REGISTER
}

//-----------------------------------------------------------------------------

inline void Push_Reg (unsigned char *res, int *counter, const int offset)
{
    assert (res);

    res[(*counter)++] = C_push_reg;                  //}
    res[(*counter)++] = C_push_start_reg + offset;   //} push REGISTER
}

//-----------------------------------------------------------------------------

inline void Move_Ax_Si (unsigned char *res, int *counter)
{
    assert (res);

    res[(*counter)++] = C_mov_ax_si[0];              //}
    res[(*counter)++] = C_mov_ax_si[1];              //| mov ax, si
    res[(*counter)++] = C_mov_ax_si[2];              //}
}

//-----------------------------------------------------------------------------

inline void Move_Bx_Di (unsigned char *res, int *counter)
{
    assert (res);

    res[(*counter)++] = C_mov_bx_di[0];              //}
    res[(*counter)++] = C_mov_bx_di[1];              //| mov bx, di
    res[(*counter)++] = C_mov_bx_di[2];              //}
}

//-----------------------------------------------------------------------------

inline void Add_Ax_Bx (unsigned char *res, int *counter)
{
    assert (res);

    res[(*counter)++] = C_add_ax_bx[0];              //}
    res[(*counter)++] = C_add_ax_bx[1];              //| add ax, bx
    res[(*counter)++] = C_add_ax_bx[2];              //}
}

//-----------------------------------------------------------------------------

inline void Sub_Ax_Bx (unsigned char *res, int *counter)
{
    assert (res);

    res[(*counter)++] = C_sub_ax_bx[0];              //}
    res[(*counter)++] = C_sub_ax_bx[1];              //| sub ax, bx
    res[(*counter)++] = C_sub_ax_bx[2];              //}
}

//-----------------------------------------------------------------------------

inline void Mul_Bx (unsigned char *res, int *counter)
{
    assert (res);

    res[(*counter)++] = C_mul_bx[0];                 //}
    res[(*counter)++] = C_mul_bx[1];                 //| mul bx
    res[(*counter)++] = C_mul_bx[2];                 //}
}

//-----------------------------------------------------------------------------

inline void Idiv_Bl (unsigned char *res, int *counter)
{
    assert (res);

    res[(*counter)++] = C_idiv_bl[0];                //}
    res[(*counter)++] = C_idiv_bl[1];                //} idiv bl
}

//-----------------------------------------------------------------------------

inline void Imul_Bl (unsigned char *res, int *counter)
{
    assert (res);

    res[(*counter)++] = C_imul_bl[0];                //}
    res[(*counter)++] = C_imul_bl[1];                //} imul bl
}

//-----------------------------------------------------------------------------

inline void Idiv_Bx (unsigned char *res, int *counter)
{
    assert (res);

    res[(*counter)++] = C_idiv_bx[0];                //}
    res[(*counter)++] = C_idiv_bx[1];                //| idiv bx
    res[(*counter)++] = C_idiv_bx[2];                //}
}

//-----------------------------------------------------------------------------

inline void Div_Bx (unsigned char *res, int *counter)
{
    assert (res);

    res[(*counter)++] = C_div_bx[0];                 //}
    res[(*counter)++] = C_div_bx[1];                 //| div bx
    res[(*counter)++] = C_div_bx[2];                 //}
}

//-----------------------------------------------------------------------------

inline void Xor_Ah_Ah (unsigned char *res, int *counter)
{
    assert (res);

    res[(*counter)++] = C_xor_ah_ah[0];              //}
    res[(*counter)++] = C_xor_ah_ah[1];              //} xor ah, ah
}

//-----------------------------------------------------------------------------

inline void Cmp_Si_Di (unsigned char *res, int *counter)
{
    assert (res);

    res[(*counter)++] = C_cmp_si_di[0];              //}
    res[(*counter)++] = C_cmp_si_di[1];              //| cmp si, di
    res[(*counter)++] = C_cmp_si_di[2];              //}
}

//-----------------------------------------------------------------------------

inline void Move_Si_Not_Reg (unsigned char *res, int *counter)
{
    assert (res);

    res[(*counter)++] = C_mov_si_not_reg[0];         //}
    res[(*counter)++] = C_mov_si_not_reg[1];         //} mov si, const
}

//-----------------------------------------------------------------------------

inline void Move_Rsi_Offset (unsigned char *res, int *counter)
{
    assert (res);

    res[(*counter)++] = C_mov_rsi_offset[0];         //}
    res[(*counter)++] = C_mov_rsi_offset[1];         //} mov rsi, OFFSET
}

//-----------------------------------------------------------------------------

inline void Add_Si_Di (unsigned char *res, int *counter)
{
    assert (res);

    res[(*counter)++] = C_add_si_di[0];              //}
    res[(*counter)++] = C_add_si_di[1];              //| add si, di
    res[(*counter)++] = C_add_si_di[2];              //}
}

//-----------------------------------------------------------------------------

inline void Sub_Si_Di (unsigned char *res, int *counter)
{
    assert (res);

    res[(*counter)++] = C_sub_si_di[0];              //}
    res[(*counter)++] = C_sub_si_di[1];              //| sub si, di
    res[(*counter)++] = C_sub_si_di[2];              //}
}

//-----------------------------------------------------------------------------

inline void Syscall (unsigned char *res, int *counter)
{
    assert (res);

    res[(*counter)++] = C_syscall[0];                //}
    res[(*counter)++] = C_syscall[1];                //} syscall
}
