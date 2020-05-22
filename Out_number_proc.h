
//{============================================================================
//{                                 Output number                             ;
//}============================================================================

// Out_number_proc.h

// This proc take ax - number and output it
// Size of this code is 0x70


0x55,                                       //  push rbp
0x48, 0x89, 0xe5,                           //  mov rbp, rsp
                                            //
0x50,                                       //  push rax
0x57,                                       //  push rdi
0x56,                                       //  push rsi
0x52,                                       //  push rdx
                                            //
0x48, 0xbe, 0x80, 0x00, 0x40, 0x00,         // }mov rsi, 0x400080 (our free buf)
0x00, 0x00, 0x00, 0x00,                     // }
0x48, 0x83, 0xc6, 0x13,                     //  add rsi, 0x13   (0x13 - max length)
                                            //
0xb1, 0x0a,                                 //  mov cl, 0x0a
0xba, 0x00, 0x00, 0x00, 0x00,               //  mov rdx, 0
                                            //
0x66, 0x3d, 0x80, 0x00,                     //  cmp ax, 0x80
0x72, 0x11,                                 //  jb =============}
0x66, 0xbf, 0xff, 0x00,                     //  mov di, 0xff    |  (0xff - max)
0x66, 0xff, 0xc8,                           //  dec ax          |
0x66, 0x29, 0xc7,                           //  sub di, ax      |
0x66, 0x89, 0xf8,                           //  mov ax, di      |
0x66, 0xbf, 0x05, 0x00,                     //  mov di, 5       |
                                            //                  |
0xf6, 0xf1,                                 //  div cl <--------}--}
0x80, 0xfc, 0x09,                           //  cmp ah, 9          :
0x80, 0xc4, 0x30,                           //  add ah, '0'        :
0x88, 0x26,                                 //  mov [rsi], ah      :
0x48, 0xff, 0xce,                           //  dec rsi            :
0x48, 0xff, 0xc2,                           //  inc rdx            :
                                            //                     :
0x30, 0xe4,                                 //  xor ah, ah         :
0x66, 0x83, 0xf8, 0x00,                     //  cmp ax, 0          :
0x77, 0xe8,                                 //  ja ================}
                                            //
0x66, 0x83, 0xff, 0x05,                     //  cmp di, 5 (if ax was < 0)
0x75, 0x0a,                                 //  jne ============}
0xb4, 0x2d,                                 //  mov ah, '-'     |
0x88, 0x26,                                 //  mov [rsi], ah   |
0x48, 0xff, 0xce,                           //  dec rsi         |
0x48, 0xff, 0xc2,                           //  inc rdx         |
                                            //                  |
0xb8, 0x01, 0x00, 0x00, 0x00,               //  mov rax, 1 <----}
0xbf, 0x01, 0x00, 0x00, 0x00,               //  mov rdi, 1
0x48, 0xff, 0xc6,                           //  inc rsi
0x0f, 0x05,                                 //  syscall
                                            //
0x5a,                                       //  pop rdx
0x5e,                                       //  pop rsi
0x5f,                                       //  pop rdi
0x58,                                       //  pop rax
                                            //
0x48, 0x89, 0xec,                           //  mov rsp, rbp
0x5d,                                       //  pop rbp
                                            //
0xc3                                        //  ret


