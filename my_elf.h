
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
