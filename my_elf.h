
//{============================================================================
//{                            MINIMAL ELF FILE                               ;
//}============================================================================

// My_elf.h

//-----------------------------------------------------------------------------
// taken from:                                                                ;
// https://code.woboq.org/linux/include/elf.h.html#65                         ;
//-----------------------------------------------------------------------------

#include <stdint.h>

namespace elf
{

typedef uint16_t Elf64_Half;
typedef uint32_t Elf64_Word;
typedef uint64_t Elf64_Addr;
typedef uint64_t Elf64_Off;
typedef uint64_t Elf64_Xword;


//{============================================================================
//;                             ELF file header                               ;
//}============================================================================

struct Elf64_Ehdr
{
  unsigned char	e_ident[16];   	/* Magic number and other info       */
  Elf64_Half	e_type;		    /* Object file type                  */
  Elf64_Half	e_machine;	    /* Architecture                      */
  Elf64_Word	e_version;	   	/* Object file version               */
  Elf64_Addr	e_entry;    	/* Entry point virtual address       */
  Elf64_Off	    e_phoff;    	/* Program header table file offset  */
  Elf64_Off	    e_shoff;	    /* Section header table file offset  */
  Elf64_Word	e_flags;	    /* Processor-specific flags          */
  Elf64_Half	e_ehsize;		/* ELF header size in bytes          */
  Elf64_Half	e_phentsize;    /* Program header table entry size   */
  Elf64_Half	e_phnum;		/* Program header table entry count  */
  Elf64_Half	e_shentsize;	/* Section header table entry size   */
  Elf64_Half	e_shnum;		/* Section header table entry count  */
  Elf64_Half	e_shstrndx;		/* Section header string table index */
};


//{============================================================================
//;                          Program segment header                           ;
//}============================================================================

struct Elf64_Phdr
{
  Elf64_Word	p_type;	    	/* Segment type             */
  Elf64_Word	p_flags;    	/* Segment flags            */
  Elf64_Off 	p_offset;   	/* Segment file offset      */
  Elf64_Addr	p_vaddr;    	/* Segment virtual address  */
  Elf64_Addr	p_paddr;    	/* Segment physical address */
  Elf64_Xword	p_filesz;   	/* Segment size in file     */
  Elf64_Xword	p_memsz;	    /* Segment size in memory   */
  Elf64_Xword	p_align;	    /* Segment alignment        */
};

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
