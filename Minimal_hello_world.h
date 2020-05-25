'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '!',    //  text
                                                               //
0xb8, 0x01, 0, 0, 0,                                           //  mov eax, 1
0xbf, 0x01, 0, 0, 0,                                           //  mov edi, 1
0x48, 0xbe, 0x78, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00,    //  mov rsi, text
0xba, 0x0c, 0x00, 0x00, 0x00,                                  //  mov edx, 0x0d
0x0f, 0x05,                                                    //  syscall
                                                               //
0xb8, 0x3c, 0x00, 0x00, 0x00,                                  //  mov eax, 0x3c
0xbf, 0x00, 0x00, 0x00, 0x00,                                  //  mov edi, 0
0x0f, 0x05                                                     //  syscall
