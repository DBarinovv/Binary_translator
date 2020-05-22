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

                break;
                }, 1)

DEF_CMD(ADD, 3,
                {
                offsets_arr[pos] = counter;

                REALLOC_RES

                Pop_Reg (res, &counter, E_di);
                Pop_Reg (res, &counter, E_si);

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

                Pop_Reg (res, &counter, E_di);
                Pop_Reg (res, &counter, E_si);

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

                Imul_Bl  (res, &counter);

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

                Pop_Reg (res, &counter, E_bx);
                Pop_Reg (res, &counter, E_ax);

                REALLOC_RES

                Push_Reg   (res, &counter, E_dx);

                Idiv_Bl     (res, &counter);

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



DEF_CMD(SQRT, 7,
                {
                offsets_arr[pos] = counter;

                REALLOC_RES

                Move_Si_Ax (res, &counter);
                Move_Di_Bx (res, &counter);

                Pop_Reg    (res, &counter, E_bx);

                res[counter++] = C_call;

                for (int i = 0; i < 4; i++)   //}
                    res[counter++] = 0;       //} TBA


                Push_Reg   (res, &counter, E_ax);


                Move_Ax_Si (res, &counter);
                Move_Bx_Di (res, &counter);

                pos++;

                break;
                }, 0)

DEF_CMD(CALL, 8,
                {
//                counter++;
//
//                Stack_Push (stk_for_func, counter + sizeof (int));
//
//                int sum = * (int*) (buf + counter);
//                counter = sum;
////                counter = buf[counter];
//
                break;
                }, 1)

DEF_CMD(RET, 9,
                {
//                Stack_Pop (stk_for_func, &counter);

                break;
                }, 0)



DEF_CMD(JMP, 17,
                {
                offsets_arr[pos] = counter;

                REALLOC_RES
                pos++;

                int sum = * (int *) (buf + pos);

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

                int sum = * (int *) (buf + pos);

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

                int sum = * (int *) (buf + pos);

                Pop_Reg (res, &counter, E_si);
                Pop_Reg (res, &counter, E_di);

                Cmp_Si_Di (res, &counter);

                res[counter++] = C_jb;
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

                int sum = * (int *) (buf + pos);

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

                int sum = * (int *) (buf + pos);

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

                int sum = * (int *) (buf + pos);

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

                int sum = * (int *) (buf + pos);

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
                offsets_arr[pos] = counter;

                REALLOC_RES
                pos++;

                Move_Si_Ax (res, &counter);

                Pop_Reg    (res, &counter, E_ax);

                res[counter++] = C_call;

                for (int i = 0; i < 4; i++)   //}
                    res[counter++] = 0;       //} TBA

                Move_Ax_Si (res, &counter);

                break;
                }, 0)



DEF_CMD(PRT, 72,
                {
                offsets_arr[pos] = counter;

                REALLOC_RES
                pos++;

                char* helper = (buf + pos);
                int len = strlen (helper);

                pos += (len);

                *(strings_arr + strings_arr_pos) = '\n';
                memmove (strings_arr + strings_arr_pos + 1, helper, len);

                strings_arr_pos += 20 - strings_arr_pos % 20;


                res[counter++] = C_mov_rax_not_reg;
                * (int *) (res + counter) = 1;
                counter += sizeof (int);

                res[counter++] = C_mov_rdi_not_reg;
                * (int *) (res + counter) = 1;
                counter += sizeof (int);;

                REALLOC_RES

                Move_Rsi_Offset (res, &counter);

                for (int i = 0; i < 8; i++)
                    res[counter++] = 0;     // TBA

                REALLOC_RES

                res[counter++] = C_mov_rdx_not_reg;

                for (int i = 0; i < 4; i++)
                    res[counter++] = 0;     // TBA

                Syscall (res, &counter);

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
