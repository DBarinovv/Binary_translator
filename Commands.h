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
                * (int *) (res + counter) = sum;

                counter += sizeof (int);

                break;
                }, 1)

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
                }, 1)

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
                }, 0)

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
                }, 0)

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
                }, 0)

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
                }, 0)


DEF_CMD(JMP, 17,
                {
                pos++;

                int sum = * (int*) (buf + pos);
                pos = sum;

                break;
                }, 1)

DEF_CMD(JA, 11,
                {
//                Stack_Pop (stk, &helper_1);
//                Stack_Pop (stk, &helper_2);
//
//                pos++;
//
//                if (helper_1 > helper_2)
//                {
//                    int sum = * (int*) (buf + pos);
//                    pos = sum;
//                }
//                else
//                {
                    pos += sizeof (int);
//                }

//                Stack_Push (stk, helper_2);
//                Stack_Push (stk, helper_1);

                break;
                }, 1)

DEF_CMD(JAE, 12,
                {
//                Stack_Pop (stk, &helper_1);
//                Stack_Pop (stk, &helper_2);
//
                pos++;
//
//                if (helper_1 >= helper_2)
//                {
//                    int sum = * (int*) (buf + pos);
//                    pos = sum;
//                }
//                else
//                {
                    pos += sizeof (int);
//                }

//                Stack_Push (stk, helper_2);
//                Stack_Push (stk, helper_1);

                break;
                }, 1)

DEF_CMD(JB, 13,
                {
//                Stack_Pop (stk, &helper_1);
//                Stack_Pop (stk, &helper_2);
//
                pos++;
//
//                if (helper_1 < helper_2)
//                {
//                    int sum = * (int*) (buf + pos);
//                    pos = sum;
//                }
//                else
//                {
                    pos += sizeof (int);
//                }

//                Stack_Push (stk, helper_2);
//                Stack_Push (stk, helper_1);

                break;
                }, 1)

DEF_CMD(JBE, 14,
                {
//                Stack_Pop (stk, &helper_1);
//                Stack_Pop (stk, &helper_2);

                pos++;

//                if (helper_1 <= helper_2)
//                {
//                    int sum = * (int*) (buf + pos);
//                    pos = sum;
//                }
//                else
//                {
                    pos += sizeof (int);
//                }

//                Stack_Push (stk, helper_2);
//                Stack_Push (stk, helper_1);

                break;
                }, 1)

DEF_CMD(JE, 15,
                {
//                Stack_Pop (stk, &helper_1);
//                Stack_Pop (stk, &helper_2);

                pos++;

//                if (helper_1 == helper_2)
//                {
//                    int sum = * (int*) (buf + pos);
//                    pos = sum;
//                }
//                else
//                {
                    pos += sizeof (int);
//                }
//
//                Stack_Push (stk, helper_2);
//                Stack_Push (stk, helper_1);

                break;
                }, 1)

DEF_CMD(JNE, 16,
                {
//                Stack_Pop (stk, &helper_1);
//                Stack_Pop (stk, &helper_2);

                pos++;

//                if (helper_1 != helper_2)
//                {
//                    int sum = * (int*) (buf + pos);
//                    pos = sum;
//                }
//                else
//                {
                    pos += sizeof (int);
//                }

//                Stack_Push (stk, helper_2);
//                Stack_Push (stk, helper_1);

                break;
                }, 1)


DEF_CMD(OUT, 22,
                {
                pos++;

//                helper_1 = Stack_Top (stk);
//                Stack_Pop (stk, &helper_1);

//                printf ("%d\n", helper_1);

                break;
                }, 0)



DEF_CMD(PRT, 72,
                {
                pos++;

                char* helper = (buf + pos);
                pos += (strlen (helper));

//                printf ("%s ", helper);

                break;
                }, 1)


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

                pos = sz_file + 1;
                }, 0)
