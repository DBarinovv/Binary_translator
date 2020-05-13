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
                pos++;

                int sum = * (int*) (buf + pos);

                Pop_Reg (res, &counter, E_si);
                Pop_Reg (res, &counter, E_di);

                Cmp_Si_Di (res, &counter);

                res[counter++] = C_ja;
                * (int *) (res + counter) = offsets_arr[sum] - offsets_arr[pos - 1] - 2;

                counter++;
                pos += sizeof (int);

                break;
                }, 1, 2)

DEF_CMD(JAE, 12,
                {
                pos++;

                int sum = * (int*) (buf + pos);

                Pop_Reg (res, &counter, E_si);
                Pop_Reg (res, &counter, E_di);

                Cmp_Si_Di (res, &counter);

                res[counter++] = C_jae;
                * (int *) (res + counter) = offsets_arr[sum] - offsets_arr[pos - 1] - 2;

                counter++;
                pos += sizeof (int);

                break;
                }, 1, 2)

DEF_CMD(JB, 13,
                {
                pos++;

                int sum = * (int*) (buf + pos);

                Pop_Reg (res, &counter, E_si);
                Pop_Reg (res, &counter, E_di);

                Cmp_Si_Di (res, &counter);

                res[counter++] = C_jb;
                * (int *) (res + counter) = offsets_arr[sum] - offsets_arr[pos - 1] - 2;

                counter++;
                pos += sizeof (int);

                break;
                }, 1, 2)

DEF_CMD(JBE, 14,
                {
                pos++;

                int sum = * (int*) (buf + pos);

                Pop_Reg (res, &counter, E_si);
                Pop_Reg (res, &counter, E_di);

                Cmp_Si_Di (res, &counter);

                res[counter++] = C_jbe;
                * (int *) (res + counter) = offsets_arr[sum] - offsets_arr[pos - 1] - 2;

                counter++;
                pos += sizeof (int);

                break;
                }, 1, 2)

DEF_CMD(JE, 15,
                {
                pos++;

                int sum = * (int*) (buf + pos);

                Pop_Reg (res, &counter, E_si);
                Pop_Reg (res, &counter, E_di);

                Cmp_Si_Di (res, &counter);

                res[counter++] = C_je;
                * (int *) (res + counter) = offsets_arr[sum] - offsets_arr[pos - 1] - 2;

                counter++;
                pos += sizeof (int);

                break;
                }, 1, 2)

DEF_CMD(JNE, 16,
                {
                pos++;

                int sum = * (int*) (buf + pos);

                Pop_Reg (res, &counter, E_si);
                Pop_Reg (res, &counter, E_di);

                Cmp_Si_Di (res, &counter);

                res[counter++] = C_jne;
                * (int *) (res + counter) = offsets_arr[sum] - offsets_arr[pos - 1] - 2;

                counter++;
                pos += sizeof (int);

                break;
                }, 1, 2)


DEF_CMD(OUT, 22,
                {
                pos++;

//                helper_1 = Stack_Top (stk);
//                Stack_Pop (stk, &helper_1);

//                printf ("%d\n", helper_1);

                break;
                }, 0, 0)



DEF_CMD(PRT, 72,
                {
                pos++;

                char* helper = (buf + pos);
                pos += (strlen (helper));

//                printf ("%s ", helper);

                break;
                }, 1, 0)


DEF_CMD(END, 0,
                {

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
