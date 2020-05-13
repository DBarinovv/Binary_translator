
//{============================================================================
//{                             BINARY TRANSLATOR                             ;
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

const elf::Elf64_Half	C_my_e_type      = 0x0002;
const elf::Elf64_Half	C_my_e_machine   = 0x003E;
const elf::Elf64_Word	C_my_e_version   = 0x00000001;
const elf::Elf64_Addr	C_my_e_entry     = 0x0000000000400078;
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
const elf::Elf64_Word	C_my_p_flags  = 0x00000005;
const elf::Elf64_Off 	C_my_p_offset = 0x0000000000000000;
const elf::Elf64_Addr	C_my_p_vaddr  = 0x0000000000400000;
const elf::Elf64_Addr	C_my_p_paddr  = 0x0000000000400000;
const elf::Elf64_Xword	C_my_p_filesz = 0x00000000000000B0; // TBA
const elf::Elf64_Xword	C_my_p_memsz  = 0x00000000000000B0; // TBA
const elf::Elf64_Xword	C_my_p_align  = 0x0000000000001000;

//=============================================================================

void Make_Default_ELF_Header (elf::Elf64_Ehdr *elf_header);

void Make_Default_Program_Header (elf::Elf64_Phdr *program_header);

//-----------------------------------------------------------------------------

inline void Move_Si_Ax (char *res, int *counter);

inline void Move_Di_Bx (char *res, int *counter);

inline void Pop_Reg    (char *res, int *counter, const int offset);

inline void Push_Reg   (char *res, int *counter, const int offset);

inline void Move_Ax_Si (char *res, int *counter);

inline void Move_Bx_Di (char *res, int *counter);

inline void Add_Ax_Bx  (char *res, int *counter);

inline void Sub_Ax_Bx  (char *res, int *counter);

inline void Mul_Bx     (char *res, int *counter);

inline void Div_Bx     (char *res, int *counter);

inline void Xor_Ah_Ah  (char *res, int *counter);

//=============================================================================

int main ()
{
    char *name_of_fin  = "output.txt";
    char *name_of_fout = "Elf_file";

    int sz_file = Find_Size_Of_File (name_of_fin);

    FILE* fin  = fopen (name_of_fin,  "rb");
    FILE* fout = fopen (name_of_fout, "wb");

    char *buf = (char *) calloc (sz_file + 1, sizeof (char));

    fread (buf, sizeof (char), sz_file + 1, fin);


    elf::Elf64_Ehdr elf_header = {};
    Make_Default_ELF_Header (&elf_header);


    elf::Elf64_Phdr program_header = {};
    Make_Default_Program_Header (&program_header);

    // ASSERTS!!!!!!

    const int c_offset_of_program = 0x78; // address start of the program

     #define DEF_CMD(name, num, code, arg)                                           \
        case CMD_##name:                                                             \
            code                                                                     \


    #define REALLOC_RES                                                              \
    {                                                                                \
        if (counter + 10 >= sz_res)                                                  \
        {                                                                            \
            sz_res *= 2;                                                             \
            res = (char *) realloc (res, sz_res * sizeof (char)); assert (res);      \
        }                                                                            \
    }


    // ax, cx, bx, dx
    char *res = (char *) calloc (sz_file + 1, sizeof (char));

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


    program_header.p_filesz = counter + 1;
    program_header.p_memsz  = counter + 1;

    fwrite (&elf_header,     sizeof (elf::Elf64_Ehdr), 1, fout);
    fwrite (&program_header, sizeof (elf::Elf64_Phdr), 1, fout);

    fwrite (res, counter, sizeof (char), fout);

    return 0;
}

//=============================================================================

void Make_Default_ELF_Header (elf::Elf64_Ehdr *elf_header)
{
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
    program_header->p_type	 = C_my_p_type;
    program_header->p_flags	 = C_my_p_flags;
    program_header->p_offset = C_my_p_offset;
    program_header->p_vaddr	 = C_my_p_vaddr;
    program_header->p_paddr	 = C_my_p_paddr;
    program_header->p_filesz = C_my_p_filesz;
    program_header->p_memsz	 = C_my_p_memsz;
    program_header->p_align  = C_my_p_align;
}

//=============================================================================

inline void Move_Si_Ax (char *res, int *counter)
{
    res[(*counter)++] = C_mov_si_ax[0];              //{
    res[(*counter)++] = C_mov_si_ax[1];              //| mov si, ax
    res[(*counter)++] = C_mov_si_ax[2];              //{
}

//-----------------------------------------------------------------------------

inline void Move_Di_Bx (char *res, int *counter)
{
    res[(*counter)++] = C_mov_di_bx[0];              //{
    res[(*counter)++] = C_mov_di_bx[1];              //| mov di, bx
    res[(*counter)++] = C_mov_di_bx[2];              //{
}

//-----------------------------------------------------------------------------

inline void Pop_Reg (char *res, int *counter, const int offset)
{
    res[(*counter)++] = C_pop_reg;
    res[(*counter)++] = C_pop_start_reg + offset;
}

//-----------------------------------------------------------------------------

inline void Push_Reg (char *res, int *counter, const int offset)
{
    res[(*counter)++] = C_push_reg;
    res[(*counter)++] = C_push_start_reg + offset;
}

//-----------------------------------------------------------------------------

inline void Move_Ax_Si (char *res, int *counter)
{
    res[(*counter)++] = C_mov_ax_si[0];              //{
    res[(*counter)++] = C_mov_ax_si[1];              //| mov ax, si
    res[(*counter)++] = C_mov_ax_si[2];              //{
}

//-----------------------------------------------------------------------------

inline void Move_Bx_Di (char *res, int *counter)
{
    res[(*counter)++] = C_mov_bx_di[0];                 //{
    res[(*counter)++] = C_mov_bx_di[1];                 //| mov bx, di
    res[(*counter)++] = C_mov_bx_di[2];                 //{
}

//-----------------------------------------------------------------------------

inline void Add_Ax_Bx (char *res, int *counter)
{
    res[(*counter)++] = C_add_ax_bx[0];                 //{
    res[(*counter)++] = C_add_ax_bx[1];                 //| add ax, bx
    res[(*counter)++] = C_add_ax_bx[2];                 //{
}

//-----------------------------------------------------------------------------

inline void Sub_Ax_Bx (char *res, int *counter)
{
    res[(*counter)++] = C_sub_ax_bx[0];              //{
    res[(*counter)++] = C_sub_ax_bx[1];              //| sub ax, bx
    res[(*counter)++] = C_sub_ax_bx[2];              //{
}

//-----------------------------------------------------------------------------

inline void Mul_Bx (char *res, int *counter)
{
    res[(*counter)++] = C_mul_bx[0];                 //{
    res[(*counter)++] = C_mul_bx[1];                 //| mul bx
    res[(*counter)++] = C_mul_bx[2];                 //{
}

//-----------------------------------------------------------------------------

inline void Div_Bx (char *res, int *counter)
{
    res[(*counter)++] = C_div_bx[0];                 //{
    res[(*counter)++] = C_div_bx[1];                 //| div bx
    res[(*counter)++] = C_div_bx[2];                 //{
}

//-----------------------------------------------------------------------------

inline void Xor_Ah_Ah (char *res, int *counter)
{
    res[(*counter)++] = C_xor_ah_ah[0];              //{
    res[(*counter)++] = C_xor_ah_ah[1];              //{ xor ah, ah
}


//=============================================================================

//Name           Offset         NumValue            Value
//EI_MAG:        0x00000000     0x7F454C46          ELF
//EI_CLASS       0x00000004     0x02                64 BIT
//EI_DATA        0x00000005     0x01                DATA2LSB (Little-Endian)
//EI_VERSION     0x00000006     0x01                EV_CURRENT
//EI_OSABI       0x00000007     0x00                UNIX System V ABI
//EI_OSABIVER    0x00000008     0x00
//E_TYPE         0x00000010     0x0002              ET_EXEC (Executable file)
//E_MACHINE      0x00000012     0x003E              EM_X86_64 (AMD x86- 64 architecture)
//E_VERSION      0x00000014     0x00000001          EV_CURRENT
//E_ENTRY        0x00000018     0x0000000000401000
//E_PHOFF        0x00000020     0x0000000000000040
//E_SHOFF        0x00000028     0x0000000000001120
//E_FLAGS        0x00000030     0x00000000
//E_EHSIZE       0x00000034     0x0040
//E_PHENTSIZE    0x00000036     0x0038
//E_PHNUM        0x00000038     0x0002
//E_SHENTSIZE    0x0000003A     0x0040
//E_SHNUM        0x0000003C     0x0005
//E_SHSTRNDX     0x0000003E     0x0004

//-----------------------------------------------------------------------------

//P_TYPE         0x00000040     0x00000001          PT_LOAD (Loadable segment)
//P_FLAGS        0x00000044     0x00000004          Read
//P_OFFSET       0x00000048     0x0000000000000000
//P_VADDR        0x00000050     0x0000000000400000
//P_PADDR        0x00000058     0x0000000000400000
//P_FILESZ       0x00000060     0x00000000000000B0
//P_MEMSZ        0x00000068     0x00000000000000B0
//P_ALIGN        0x00000070     0x0000000000001000
