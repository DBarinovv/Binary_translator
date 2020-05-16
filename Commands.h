// Commands.h

DEF_CMD(PUSH, 1,
                {
                offsets_arr[pos] = counter;

                pos++;

                int what_reg = -1;

                if ('a' <= buf[pos] && buf[pos] <= 'z')
                {
                    what_reg = Check_If_Reg (&buf[pos]);

                    if (what_reg == -1)
                    {
                        printf ("ERROR in DEF_CMD Push in Commands.h\n");
                    }
                    else
                    {
                        REALLOC_RES

                        Push_Reg (res, &counter, what_reg);
                    }

                    pos += 2;

                    break;
                }

                int sum = * (int*) (buf + pos);
                pos += sizeof (int);

                Move_Si_Not_Reg (res, &counter);

                res[counter++] = sum % 256;
                sum /= 256;
                res[counter++] = sum % 256;

                Push_Reg (res, &counter, E_si);

                break;
                }, 1)

DEF_CMD(POP, 2,
                {
                offsets_arr[pos] = counter;

                pos++;

                int what_reg = -1;

                if ('a' <= buf[pos] && buf[pos] <= 'z')
                {
                    what_reg = Check_If_Reg (&buf[pos]);

                    if (what_reg == -1)
                    {
                        printf ("ERROR in DEF_CMD Pop in Commands.h\n");
                    }
                    else
                    {
                        REALLOC_RES

                        Pop_Reg (res, &counter, what_reg);
                    }

                    pos += 2;

                    break;
                }

                pos += sizeof (int);

//                res[counter++] = C_pop_not_reg;
//                * (int *) (res + counter) = sum;

                break;
                }, 1)

DEF_CMD(ADD, 3,
                {
                offsets_arr[pos] = counter;

                REALLOC_RES

                Pop_Reg (res, &counter, E_si);
                Pop_Reg (res, &counter, E_di);

                Add_Si_Di  (res, &counter);

                Push_Reg   (res, &counter, E_si);

                REALLOC_RES

                pos++;

                break;
                }, 0)

DEF_CMD(SUB, 4,
                {
                offsets_arr[pos] = counter;

                REALLOC_RES

                Pop_Reg (res, &counter, E_si);
                Pop_Reg (res, &counter, E_di);

                Sub_Si_Di  (res, &counter);

                Push_Reg   (res, &counter, E_si);

                REALLOC_RES

                pos++;

                break;
                }, 0)

DEF_CMD(MUL, 5,
                {
                offsets_arr[pos] = counter;

                REALLOC_RES

                Move_Si_Ax (res, &counter);
                Move_Di_Bx (res, &counter);

                Pop_Reg (res, &counter, E_ax);
                Pop_Reg (res, &counter, E_bx);

                REALLOC_RES

                Mul_Bx   (res, &counter);

                Push_Reg (res, &counter, E_ax);

                REALLOC_RES

                Move_Ax_Si (res, &counter);
                Move_Bx_Di (res, &counter);

                pos++;

                break;
                }, 0)

DEF_CMD(DIV, 6,
                {
                offsets_arr[pos] = counter;

                REALLOC_RES

                Move_Si_Ax (res, &counter);
                Move_Di_Bx (res, &counter);

                Pop_Reg (res, &counter, E_ax);
                Pop_Reg (res, &counter, E_bx);

                REALLOC_RES

                Push_Reg   (res, &counter, E_dx);

                Div_Bx     (res, &counter);

                Pop_Reg    (res, &counter, E_dx);

                REALLOC_RES

                Xor_Ah_Ah  (res, &counter);

                Push_Reg   (res, &counter, E_ax);

                REALLOC_RES

                Move_Ax_Si (res, &counter);
                Move_Bx_Di (res, &counter);

                pos++;

                break;
                }, 0)


DEF_CMD(JMP, 17,
                {
                offsets_arr[pos] = counter;

                REALLOC_RES
                pos++;

                int sum = * (int*) (buf + pos);

                res[counter++] = C_jmp;

                for (int i = 0; i < 4; i++)   //}
                    res[counter++] = 0;       //} TBA

                pos += sizeof (int);

                break;
                }, 1)


DEF_CMD(JA, 11,
                {
                offsets_arr[pos] = counter;

                REALLOC_RES
                pos++;

                int sum = * (int*) (buf + pos);

                Pop_Reg (res, &counter, E_si);
                Pop_Reg (res, &counter, E_di);

                Cmp_Si_Di (res, &counter);

                res[counter++] = C_jbe;
                res[counter++] = 0x05;

                REALLOC_RES

                res[counter++] = C_jmp;
                for (int i = 0; i < 4; i++)   //}
                    res[counter++] = 0;       //} TBA

                pos += sizeof (int);

                break;
                }, 1)

DEF_CMD(JAE, 12,
                {
                offsets_arr[pos] = counter;

                REALLOC_RES
                pos++;

                int sum = * (int*) (buf + pos);

                Pop_Reg (res, &counter, E_si);
                Pop_Reg (res, &counter, E_di);

                Cmp_Si_Di (res, &counter);

                res[counter++] = C_ja;
                res[counter++] = 0x05;

                REALLOC_RES

                res[counter++] = C_jmp;
                for (int i = 0; i < 4; i++)   //}
                    res[counter++] = 0;       //} TBA

                pos += sizeof (int);

                break;
                }, 1)

DEF_CMD(JB, 13,
                {
                offsets_arr[pos] = counter;

                REALLOC_RES
                pos++;

                int sum = * (int*) (buf + pos);

                Pop_Reg (res, &counter, E_si);
                Pop_Reg (res, &counter, E_di);

                Cmp_Si_Di (res, &counter);

                res[counter++] = C_jae;
                res[counter++] = 0x05;

                REALLOC_RES

                res[counter++] = C_jmp;
                for (int i = 0; i < 4; i++)   //}
                    res[counter++] = 0;       //} TBA

                pos += sizeof (int);

                break;
                }, 1)

DEF_CMD(JBE, 14,
                {
                offsets_arr[pos] = counter;

                REALLOC_RES
                pos++;

                int sum = * (int*) (buf + pos);

                Pop_Reg (res, &counter, E_si);
                Pop_Reg (res, &counter, E_di);

                Cmp_Si_Di (res, &counter);

                res[counter++] = C_ja;
                res[counter++] = 0x05;

                REALLOC_RES

                res[counter++] = C_jmp;
                for (int i = 0; i < 4; i++)   //}
                    res[counter++] = 0;       //} TBA

                pos += sizeof (int);

                break;
                }, 1)

DEF_CMD(JE, 15,
                {
                offsets_arr[pos] = counter;

                REALLOC_RES
                pos++;

                int sum = * (int*) (buf + pos);

                Pop_Reg (res, &counter, E_si);
                Pop_Reg (res, &counter, E_di);

                Cmp_Si_Di (res, &counter);

                res[counter++] = C_jne;
                res[counter++] = 0x05;

                REALLOC_RES

                res[counter++] = C_jmp;
                for (int i = 0; i < 4; i++)   //}
                    res[counter++] = 0;       //} TBA

                pos += sizeof (int);

                break;
                }, 1)

DEF_CMD(JNE, 16,
                {
                offsets_arr[pos] = counter;

                REALLOC_RES
                pos++;

                int sum = * (int*) (buf + pos);

                Pop_Reg (res, &counter, E_si);
                Pop_Reg (res, &counter, E_di);

                Cmp_Si_Di (res, &counter);

                res[counter++] = C_je;
                res[counter++] = 0x05;

                REALLOC_RES

                res[counter++] = C_jmp;
                for (int i = 0; i < 4; i++)   //}
                    res[counter++] = 0;       //} TBA

                pos += sizeof (int);

                break;
                }, 1)


DEF_CMD(OUT, 22,
                {
//                offsets_arr[pos] = counter;

                REALLOC_RES
                pos++;

//                Pop_Reg (res, &counter, E_si);
//
//                res[counter++] = C_mov_offset_si[0];
//                res[counter++] = C_mov_offset_si[1];
//                res[counter++] = C_mov_offset_si[2];
//                res[counter++] = C_mov_offset_si[3];
//
//                int full_offset = 0x400000 + 0x78 + pos_offset + 1;
//
//                res[counter++] = full_offset % 256;
//                full_offset /= 256;
//                res[counter++] = full_offset % 256;
//                full_offset /= 256;
//                res[counter++] = full_offset % 256;
//                full_offset /= 256;
//                res[counter++] = 0;
//
//                res[pos_offset] += 2;
//                res[pos_offset + 1] = buf[pos] + '0';
//                res[pos_offset + 2] = ' ';

                break;
                }, 0)



DEF_CMD(PRT, 72,
                {
//                offsets_arr[pos] = counter;

                REALLOC_RES
                pos++;

                char* helper = (buf + pos);
                int len = strlen (helper);

                pos += (len);


//                for (int i = 0; i < len; i++)
//                {
//                    res[pos_offset + res[pos_offset] + 1] = helper[i];
//                }
//
//                res[pos_offset] += strlen (helper);
//
//                res[counter++] = C_mov_rax_not_reg;
//                res[counter++] = 1;
//                res[counter++] = 0;
//                res[counter++] = 0;
//
//                res[counter++] = C_mov_rdi_not_reg;
//                res[counter++] = 1;
//                res[counter++] = 0;
//                res[counter++] = 0;
//
//                REALLOC_RES
//
//                res[counter++] = C_mov_rdx_offset[0];
//                res[counter++] = C_mov_rdx_offset[1];
//                res[counter++] = C_mov_rdx_offset[2];
//                res[counter++] = C_mov_rdx_offset[3];
//
//                int full_offset =  0x400000 + 0x78 + pos_offset;
//
//                res[counter++] = full_offset % 256;
//                full_offset /= 256;
//                res[counter++] = full_offset % 256;
//                full_offset /= 256;
//                res[counter++] = full_offset % 256;
//                full_offset /= 256;
//                res[counter++] = 0;
//
//                REALLOC_RES
//
//                res[counter++] = C_mov_rsi_offset[0];
//                res[counter++] = C_mov_rsi_offset[1];
//
//                int ful_offset =  0x400000 + 0x78 + pos_offset + 1;
//
//                res[counter++] = full_offset % 256;
//                full_offset /= 256;
//                res[counter++] = full_offset % 256;
//                full_offset /= 256;
//                res[counter++] = full_offset % 256;
//                full_offset /= 256;
//                res[counter++] = 0;
//                res[counter++] = 0;
//                res[counter++] = 0;
//
//
//                pos_offset += res[pos_offset] + 1;

                break;
                }, 1)


DEF_CMD(END, 0,
                {
                offsets_arr[pos] = counter;

                REALLOC_RES

                for (int i = 0; i < 6; i++)
                {
                    res[counter++] = C_end[i];
                }

                REALLOC_RES

                for (int i = 6; i < 12; i++)
                {
                    res[counter++] = C_end[i];
                }

                pos += 1;
                }, 0)
