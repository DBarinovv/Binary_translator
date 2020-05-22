
//{============================================================================
//{                              Find sqrt of bx                              ;
//}============================================================================

// Sqrt_proc.h

// This proc find sqrt(bx) and mov it to ax
// Size of this code is 0x20

0x55,                 //  push rbp
0x48, 0x89, 0xe5,     //  mov rbp, rsp
                      //
0x66, 0x56,           //  push si
0x66, 0x31, 0xf6,     //  xor si, si
                      //
0x66, 0xff, 0xc6,     //  inc si <-----}
0x66, 0x89, 0xf0,     //  mov ax, si   :
0xf6, 0xe8,           //  imul al      :
0x66, 0x39, 0xd8,     //  cmp ax, bx   :
0x72, 0xf3,           //  jb ==========}
                      //
0x66, 0x89, 0xf0,     //  mov ax, si
0x66, 0x5e,           //  pop si
                      //
0x48, 0x89, 0xec,     //  mov rsp, rbp
0x5d,                 //  pop rbp
                      //
0xc3                  //  ret
