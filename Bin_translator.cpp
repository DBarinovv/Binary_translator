
//{============================================================================
//{                             BINARY TRANSLATOR                             ;
//}============================================================================

#include <stdio.h>

#include "my_elf.h"
#include "OneginLib.h"
#include "enum.h"

//=============================================================================

const elf::Elf64_Half	C_my_e_type      = 0x0002;
const elf::Elf64_Half	C_my_e_machine   = 0x003E;
const elf::Elf64_Word	C_my_e_version   = 0x00000001;
const elf::Elf64_Addr	C_my_e_entry     = 0x0000000000401000; // ch
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
const elf::Elf64_Off 	C_my_p_offset = 0x0000000000001000; // ch
const elf::Elf64_Addr	C_my_p_vaddr  = 0x0000000000401000; // ch
const elf::Elf64_Addr	C_my_p_paddr  = 0x0000000000401000; // ch
const elf::Elf64_Xword	C_my_p_filesz = 0x00000000000000B0; // TBA
const elf::Elf64_Xword	C_my_p_memsz  = 0x00000000000000B0; // TBA
const elf::Elf64_Xword	C_my_p_align  = 0x0000000000001000; // ch

//=============================================================================

void Make_Default_ELF_Header (elf::Elf64_Ehdr *elf_header);

void Make_Default_Program_Header (elf::Elf64_Phdr *program_header);

//-----------------------------------------------------------------------------

void Un_Fold_If_Have_Arg (char *res, int *pos, const char opcode);

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

//    const int c_offset_of_program = 0x78; // address start of the program

//    elf::Elf64_Phdr text_header = {};
//    Make_Default_Program_Header (&text_header);
//
//    text_header.p_flags  = 0x00000005;
//    text_header.p_offset = 0x0000000000001000;
//    text_header.p_vaddr  = 0x0000000000401000;
//    text_header.p_paddr  = 0x0000000000401000;
//    text_header.p_filesz = 12;
//    text_header.p_memsz  = 12;


//     #define DEF_CMD(name, num, code, arg, opcode)                                             \
//        case CMD_##name:                                                                       \
//            if (arg == 1)                                                                      \
//            {                                                                                  \
//                Un_Fold_If_Have_Arg (res, &pos, opcode);                                       \
//            }                                                                                  \
//            else
//            {
//
//            }
//                                                                                               \
//            break;
//
//
//    char *res = (char *) calloc (sz_file + 1, sizeof (char));
//
//    int pos = 0;
//
//    while (pos < sz_file)
//    {
//        switch (buf[pos])
//        {
//        #include "Commands.h"
//        default:
//            break;
//        }
//
//        pos++;
//    }
//
//
//
//    #indef DEF_CMD


    program_header.p_filesz = 0xD0;
    program_header.p_memsz  = 0xD0;

    fwrite (&elf_header,     sizeof (elf::Elf64_Ehdr), 1, fout);
    fwrite (&program_header, sizeof (elf::Elf64_Phdr), 1, fout);
//    fwrite (&text_header,    sizeof (elf::Elf64_Phdr), 1, fout);

    char res[] = {0x90, 0xb8, 0x3c, 0, 0, 0, 0xbf, 0, 0, 0, 0, 0x0f, 0x05};
    fwrite (res, 13, sizeof (char), fout);

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

void Un_Fold_If_Have_Arg (char *res, int *pos, const char opcode)
{


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
