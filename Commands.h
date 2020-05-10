// Commands.h

DEF_CMD(PUSH, 1,
                {
                counter++;

                int what_reg = -1;

                if ('a' <= buf[counter] && buf[counter] <= 'z')
                {
                    what_reg = Check_If_Reg (&buf[counter]);

                    if (what_reg == -1)
                    {
                        printf ("ERROR in DEF_CMD Push in Commands.h\n");
                    }
                    else
                    {
                        Stack_Push (stk, reg[what_reg]);
                    }

                    counter += 2;

                    break;
                }

                int sum = * (int*) (buf + counter);
                counter += sizeof (int);

                Stack_Push (stk, sum);

                break;
                }, 1)

DEF_CMD(POP, 2,
                {
                counter++;

                int what_reg = -1;

                if ('a' <= buf[counter] && buf[counter] <= 'z')
                {
                    what_reg = Check_If_Reg (&buf[counter]);

                    if (what_reg == -1)
                    {
                        printf ("ERROR in DEF_CMD Pop in Commands.h\n");
                    }
                    else
                    {
                        Stack_Pop (stk, &reg[what_reg]);
                    }

                    counter += 2;

                    break;
                }

                Stack_Pop (stk, &helper_1);
                counter += sizeof (int);

                break;
                }, 1)

DEF_CMD(ADD, 3,
                {
                Stack_Pop (stk, &helper_1);
                Stack_Pop (stk, &helper_2);

                Stack_Push (stk, (helper_1 + helper_2));
                counter++;

                break;
                }, 0)

DEF_CMD(SUB, 4,
                {
                Stack_Pop (stk, &helper_1);
                Stack_Pop (stk, &helper_2);

                Stack_Push (stk, (helper_2 - helper_1));
                counter++;

                break;
                }, 0)

DEF_CMD(MUL, 5,
                {
                Stack_Pop (stk, &helper_1);
                Stack_Pop (stk, &helper_2);

                Stack_Push (stk, (helper_1 * helper_2));
                counter++;

                break;
                }, 0)

DEF_CMD(DIV, 6,
                {
                Stack_Pop (stk, &helper_1);
                Stack_Pop (stk, &helper_2);

                Stack_Push (stk, (helper_1 / helper_2));
                counter++;

                break;
                }, 0)

DEF_CMD(SQRT, 7,
                {
                Stack_Pop (stk, &helper_1);

                Stack_Push (stk, sqrt (helper_1));
                counter++;

                break;
                }, 0)

DEF_CMD(CALL, 8,
                {
                counter++;

                Stack_Push (stk_for_func, counter + sizeof (int));

                int sum = * (int*) (buf + counter);
                counter = sum;
//                counter = buf[counter];

                break;
                }, 1)

DEF_CMD(RET, 9,
                {
                Stack_Pop (stk_for_func, &counter);

                break;
                }, 0)

DEF_CMD(JMP, 17,
                {
                counter++;

                int sum = * (int*) (buf + counter);
                counter = sum;

                break;
                }, 1)

DEF_CMD(JA, 11,
                {
                Stack_Pop (stk, &helper_1);
                Stack_Pop (stk, &helper_2);

                counter++;

                if (helper_1 > helper_2)
                {
                    int sum = * (int*) (buf + counter);
                    counter = sum;
                }
                else
                {
                    counter += sizeof (int);
                }

//                Stack_Push (stk, helper_2);
//                Stack_Push (stk, helper_1);

                break;
                }, 1)

DEF_CMD(JAE, 12,
                {
                Stack_Pop (stk, &helper_1);
                Stack_Pop (stk, &helper_2);

                counter++;

                if (helper_1 >= helper_2)
                {
                    int sum = * (int*) (buf + counter);
                    counter = sum;
                }
                else
                {
                    counter += sizeof (int);
                }

//                Stack_Push (stk, helper_2);
//                Stack_Push (stk, helper_1);

                break;
                }, 1)

DEF_CMD(JB, 13,
                {
                Stack_Pop (stk, &helper_1);
                Stack_Pop (stk, &helper_2);

                counter++;

                if (helper_1 < helper_2)
                {
                    int sum = * (int*) (buf + counter);
                    counter = sum;
                }
                else
                {
                    counter += sizeof (int);
                }

//                Stack_Push (stk, helper_2);
//                Stack_Push (stk, helper_1);

                break;
                }, 1)

DEF_CMD(JBE, 14,
                {
                Stack_Pop (stk, &helper_1);
                Stack_Pop (stk, &helper_2);

                counter++;

                if (helper_1 <= helper_2)
                {
                    int sum = * (int*) (buf + counter);
                    counter = sum;
                }
                else
                {
                    counter += sizeof (int);
                }

//                Stack_Push (stk, helper_2);
//                Stack_Push (stk, helper_1);

                break;
                }, 1)

DEF_CMD(JE, 15,
                {
                Stack_Pop (stk, &helper_1);
                Stack_Pop (stk, &helper_2);

                counter++;

                if (helper_1 == helper_2)
                {
                    int sum = * (int*) (buf + counter);
                    counter = sum;
                }
                else
                {
                    counter += sizeof (int);
                }

                Stack_Push (stk, helper_2);
                Stack_Push (stk, helper_1);

                break;
                }, 1)

DEF_CMD(JNE, 16,
                {
                Stack_Pop (stk, &helper_1);
                Stack_Pop (stk, &helper_2);

                counter++;

                if (helper_1 != helper_2)
                {
                    int sum = * (int*) (buf + counter);
                    counter = sum;
                }
                else
                {
                    counter += sizeof (int);
                }

                Stack_Push (stk, helper_2);
                Stack_Push (stk, helper_1);

                break;
                }, 1)

DEF_CMD(POW, 20,
                {
                counter++;

                Stack_Pop  (stk, &helper_1);
                Stack_Push (stk, (int) round (pow (helper_1, buf[counter])));

                counter += sizeof (int);

                break;
                }, 1)

DEF_CMD(MLN, 21,
                {
                counter++;

                Stack_Pop  (stk, &helper_1);

                int sum = * (int*) (buf + counter);
                counter += sizeof (int);

                Stack_Push (stk, helper_1 * sum);

                break;
                }, 1)

DEF_CMD(OUT, 22,
                {
                counter++;

//                helper_1 = Stack_Top (stk);
                Stack_Pop (stk, &helper_1);

                printf ("%d\n", helper_1);

                break;
                }, 0)

DEF_CMD(CLON, 23,
                {
                counter++;

                Stack_Pop  (stk, &helper_1);
                Stack_Push (stk,  helper_1);
                Stack_Push (stk,  helper_1);

                break;
                }, 0)

DEF_CMD(PURM, 24,
                {
                counter++;

                int what_reg = -1;

                if ('a' <= buf[counter] && buf[counter] <= 'z')
                {
                    what_reg = Check_If_Reg (&buf[counter]);

                    if (what_reg == -1)
                    {
                        printf ("ERROR in DEF_CMD PURM in Commands.h\n");
                    }
                    else
                    {
                        Stack_Push (stk, RAM[reg[what_reg]]);
                    }

                    counter += 2;

                    break;
                }

                int sum = * (int*) (buf + counter);
                counter += sizeof (int);

                Stack_Push (stk, RAM[sum]);

                break;
                }, 1)

DEF_CMD(PORM, 25,
                {
                counter++;

                int what_reg = -1;

                if ('a' <= buf[counter] && buf[counter] <= 'z')
                {
                    what_reg = Check_If_Reg (&buf[counter]);

                    if (what_reg == -1)
                    {
                        printf ("ERROR in DEF_CMD PURM in Commands.h\n");
                    }
                    else
                    {
                        Stack_Pop (stk, &RAM[reg[what_reg]]);
                    }

                    counter += 2;

                    break;
                }

                int sum = * (int*) (buf + counter);
                counter += sizeof (int);

                Stack_Pop (stk, &RAM[sum]);

                break;
                }, 1)

DEF_CMD(DMPF, 26,
                {
                counter++;

                Dump (stk_for_func, 100, 0, "Prosto");

                break;
                }, 0)

DEF_CMD(OTRM, 27,
                {
                counter++;

                for (int i = C_max_size / 2; i < C_max_size; i++)
                {
                    if (RAM[i] == 1)
                    {
                        printf ("*");
                    }
                    else if (RAM[i] == 0)
                    {
                        printf (" ");
                    }
                    else if (RAM[i] == 8)
                    {
                        printf ("\n");
                    }
                    else if (RAM[i] == -1)
                    {
                        break;
                    }
                    else
                    {
                        printf ("%d", RAM[i]);
                    }
                }

                break;
                }, 0)

DEF_CMD(SNOW, 117,
                {
                counter++;

                CH(White)

                printf ("*  *  *\n");
                printf (" * * * \n");
                printf ("  ***  \n");
                printf ("*******\n");
                printf ("  ***  \n");
                printf (" * * * \n");
                printf ("*  *  *\n");

                printf ("\noooooooooooooooooooooooooooooooooo\n\n");

                break;
                }, 0)

DEF_CMD(TORT, 38,
                {
                counter++;

                printf ("THIS IS CHEREPAXA!!!!\n");

                CH(Purple)

                printf ("   nn oo\n");
                printf ("  nnnnoo\n");
                printf ("_nnnnnn \n");
                printf ("  o  o  \n\n");

                CH_S

                break;
                }, 0)

DEF_CMD(SUN, 49,
                {
                counter++;

                CH(Yellow)

                printf ("\\ / \n");
                printf (" O  \n");
                printf ("/ \\ \n\n");

                CH_S

                break;
                }, 0)

DEF_CMD(CAT, 53,
                {
                counter++;

                CH(Green)

                printf (" /\\ /\\ \n");
                printf ("   W     \n");

                printf (" \\____/ \n\n\n");
                CH_S

                break;
                }, 0)

DEF_CMD(CHC, 80,
                {
                counter++;

                int sum = * (int*) (buf + counter);
                counter += sizeof (int);

                CH(sum)

                break;
                }, 1)

DEF_CMD(SND, 70,
                {
                counter++;

                int sum = * (int*) (buf + counter);
                counter += sizeof (int);

//                if (!txPlaySound (sound[sum], SND_SYNC))
//                    printf ("VVODI PRAVILNO!\n");

                break;
                }, 1)

DEF_CMD(SLP, 71,
                {
                counter++;

                int sum = * (int *) (buf + counter);
                counter += sizeof (int);

                Sleep (sum * 100);

                break;
                }, 1)

DEF_CMD(PRT, 72,
                {
                counter++;

                char* helper = (buf + counter);
                counter += (strlen (helper));

                printf ("%s ", helper);

                break;
                }, 1)


DEF_CMD(END, 0,
                {
                printf ("\nEND?\n");
                counter = sz_file + 1;
                }, 0)
