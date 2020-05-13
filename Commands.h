// Commands.h

DEF_CMD(PUSH, 1,
                {
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

                res[counter++] = C_push_not_reg;
                res[counter++] = sum;

                break;
                }, 1, 2)

DEF_CMD(POP, 2,
                {
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
                }, 1, 2)

DEF_CMD(ADD, 3,
                {
                REALLOC_RES

                Move_Si_Ax (res, &counter);
                Move_Di_Bx (res, &counter);

                Pop_Reg (res, &counter, E_ax);
                Pop_Reg (res, &counter, E_bx);

                REALLOC_RES

                Add_Ax_Bx  (res, &counter);

                Push_Reg   (res, &counter, E_ax);

                REALLOC_RES

                Move_Ax_Si (res, &counter);
                Move_Bx_Di (res, &counter);

                pos++;

                break;
                }, 0, 21)

DEF_CMD(SUB, 4,
                {
                REALLOC_RES

                Move_Si_Ax (res, &counter);
                Move_Di_Bx (res, &counter);

                Pop_Reg (res, &counter, E_ax);
                Pop_Reg (res, &counter, E_bx);

                REALLOC_RES

                Sub_Ax_Bx  (res, &counter);

                Push_Reg   (res, &counter, E_ax);

                REALLOC_RES

                Move_Ax_Si (res, &counter);
                Move_Bx_Di (res, &counter);

                pos++;

                break;
                }, 0, 21)

DEF_CMD(MUL, 5,
                {
                REALLOC_RES

                Move_Si_Ax (res, &counter);
                Move_Di_Bx (res, &counter);

                Pop_Reg (res, &counter, E_ax);
                Pop_Reg (res, &counter, E_bx);

                REALLOC_RES

                Mul_Bx     (res, &counter);

                Push_Reg   (res, &counter, E_ax);

                REALLOC_RES

                Move_Ax_Si (res, &counter);
                Move_Bx_Di (res, &counter);

                pos++;

                break;
                }, 0, 21)

DEF_CMD(DIV, 6,
                {
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
                }, 0, 27)


DEF_CMD(JMP, 17,
                {
                REALLOC_RES
                pos++;

                int sum = * (int*) (buf + pos);

                res[counter++] = C_jmp;
                * (int *) (res + counter) = offsets_arr[sum] - offsets_arr[pos - 1] - 2;

                counter++;
                pos += sizeof (int);

                break;
                }, 1, 2)

DEF_CMD(JA, 11,
                {
                REALLOC_RES
                pos++;

                int sum = * (int*) (buf + pos);

                Pop_Reg (res, &counter, E_si);
                Pop_Reg (res, &counter, E_di);

                Cmp_Si_Di (res, &counter);

                res[counter++] = C_ja[0];
                res[counter++] = C_ja[1];
                * (int *) (res + counter) = offsets_arr[sum] - offsets_arr[pos - 1] - 2;

                counter++;
                pos += sizeof (int);

                break;
                }, 1, 9)

DEF_CMD(JAE, 12,
                {
                REALLOC_RES
                pos++;

                int sum = * (int*) (buf + pos);

                Pop_Reg (res, &counter, E_si);
                Pop_Reg (res, &counter, E_di);

                Cmp_Si_Di (res, &counter);

                res[counter++] = C_jae[0];
                res[counter++] = C_jae[1];
                * (int *) (res + counter) = offsets_arr[sum] - offsets_arr[pos - 1] - 2;

                counter++;
                pos += sizeof (int);

                break;
                }, 1, 9)

DEF_CMD(JB, 13,
                {
                REALLOC_RES
                pos++;

                int sum = * (int*) (buf + pos);

                Pop_Reg (res, &counter, E_si);
                Pop_Reg (res, &counter, E_di);

                Cmp_Si_Di (res, &counter);

                res[counter++] = C_jb[0];
                res[counter++] = C_jb[1];
                * (int *) (res + counter) = offsets_arr[sum] - offsets_arr[pos - 1] - 2;

                counter++;
                pos += sizeof (int);

                break;
                }, 1, 9)

DEF_CMD(JBE, 14,
                {
                REALLOC_RES
                pos++;

                int sum = * (int*) (buf + pos);

                Pop_Reg (res, &counter, E_si);
                Pop_Reg (res, &counter, E_di);

                Cmp_Si_Di (res, &counter);

                res[counter++] = C_jbe[0];
                res[counter++] = C_jbe[1];
                * (int *) (res + counter) = offsets_arr[sum] - offsets_arr[pos - 1] - 2;

                counter++;
                pos += sizeof (int);

                break;
                }, 1, 9)

DEF_CMD(JE, 15,
                {
                REALLOC_RES
                pos++;

                int sum = * (int*) (buf + pos);

                Pop_Reg (res, &counter, E_si);
                Pop_Reg (res, &counter, E_di);

                Cmp_Si_Di (res, &counter);

                res[counter++] = C_je[0];
                res[counter++] = C_je[1];
                * (int *) (res + counter) = offsets_arr[sum] - offsets_arr[pos - 1] - 2;

                counter++;
                pos += sizeof (int);

                break;
                }, 1, 9)

DEF_CMD(JNE, 16,
                {
                REALLOC_RES
                pos++;

                int sum = * (int*) (buf + pos);

                Pop_Reg (res, &counter, E_si);
                Pop_Reg (res, &counter, E_di);

                Cmp_Si_Di (res, &counter);

//                if (offsets_arr[sum] - offsets_arr[pos - 1] - 2 >= 256)
//                {
                res[counter++] = C_jne[0];
                res[counter++] = C_jne[1];

                int offset = offsets_arr[sum] - offsets_arr[pos - 1] - 2;

                res[counter++] = offset % 256;
                offset /= 256;
                res[counter++] = offset % 256;
                res[counter++] = 0;
                res[counter++] = 0;

                pos += sizeof (int);

                break;
                }, 1, 13)


DEF_CMD(OUT, 22,
                {
                REALLOC_RES
                pos++;

                Pop_Reg (res, &counter, E_si);

                res[counter++] = C_mov_offset_si[0];
                res[counter++] = C_mov_offset_si[1];
                res[counter++] = C_mov_offset_si[2];
                res[counter++] = C_mov_offset_si[3];

                int full_offset = 0x400000 + 0x78 + pos_offset + 1;

                res[counter++] = full_offset % 256;
                full_offset /= 256;
                res[counter++] = full_offset % 256;
                full_offset /= 256;
                res[counter++] = full_offset % 256;
                full_offset /= 256;
                res[counter++] = 0;

                res[pos_offset] += 2;
                res[pos_offset + 1] = buf[pos] + '0';
                res[pos_offset + 2] = ' ';

                break;
                }, 0, 10)



DEF_CMD(PRT, 72,
                {
                REALLOC_RES
                pos++;

                char* helper = (buf + pos);
                int len = strlen (helper);

                pos += (len);


                for (int i = 0; i < len; i++)
                {
                    res[pos_offset + res[pos_offset] + 1] = helper[i];
                }

                res[pos_offset] += strlen (helper);

                res[counter++] = C_mov_rax_not_reg;
                res[counter++] = 1;
                res[counter++] = 0;
                res[counter++] = 0;

                res[counter++] = C_mov_rdi_not_reg;
                res[counter++] = 1;
                res[counter++] = 0;
                res[counter++] = 0;

                REALLOC_RES

                res[counter++] = C_mov_rdx_offset[0];
                res[counter++] = C_mov_rdx_offset[1];
                res[counter++] = C_mov_rdx_offset[2];
                res[counter++] = C_mov_rdx_offset[3];

                int full_offset =  0x400000 + 0x78 + pos_offset;

                res[counter++] = full_offset % 256;
                full_offset /= 256;
                res[counter++] = full_offset % 256;
                full_offset /= 256;
                res[counter++] = full_offset % 256;
                full_offset /= 256;
                res[counter++] = 0;

                REALLOC_RES

                res[counter++] = C_mov_rsi_offset[0];
                res[counter++] = C_mov_rsi_offset[1];

                int ful_offset =  0x400000 + 0x78 + pos_offset + 1;

                res[counter++] = full_offset % 256;
                full_offset /= 256;
                res[counter++] = full_offset % 256;
                full_offset /= 256;
                res[counter++] = full_offset % 256;
                full_offset /= 256;
                res[counter++] = 0;
                res[counter++] = 0;
                res[counter++] = 0;


                pos_offset += res[pos_offset] + 1;

                break;
                }, 1, 24)


DEF_CMD(END, 0,
                {
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
                }, 0, 12)
