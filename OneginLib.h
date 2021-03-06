#include <stdio.h>
#include <stdlib.h>
#include <sys\stat.h>

#include <assert.h>

//=============================================================================

struct string_t
{
    char *str;
    int len;
};

struct file_t
{
    struct string_t* strings;
    char* *copies;
    int n_Lines;
    int sz_File;
    FILE *fout;
};

//=============================================================================

struct file_t Read_File_And_Make_Arrays (char *fin, char *fout);

void Make_Array_Of_Structs (char **strings_copy, struct string_t *strings_arr,
                            char **buf, int n_Lines, int sz_File);

int Find_Size_Of_File (const char *fin);

int Number_Of_Lines (const int sz_File, const char *buf);

//=============================================================================

struct file_t Read_File_And_Make_Arrays (char *fin, char *fout)
{
    int sz_File = Find_Size_Of_File (fin);

    FILE *file     = fopen (fin,  "r");  assert (file);
    FILE *file_out = fopen (fout, "w");  assert (file_out);

    char *buf = (char *) calloc (sz_File + 2, sizeof(char));  assert (buf);   // make buffer for text
    char *h_buf = buf + 1;                                    assert (h_buf);

    fread (h_buf, sizeof (char), sz_File, file);

    int n_Lines = Number_Of_Lines (sz_File, h_buf) + 1;  assert (n_Lines >= 0);

    struct string_t *strings_arr = (string_t *) calloc (n_Lines, sizeof (*strings_arr));  assert (strings_arr);     // array with pointers to string

    char* *strings_copy = (char **) calloc (n_Lines, sizeof (*strings_copy));  assert (strings_copy);     // array with pointers (to display original text)

    Make_Array_Of_Structs (strings_copy, strings_arr, &h_buf, n_Lines, sz_File);

    fclose (file);

    struct file_t res;
    res.strings = strings_arr;
    res.copies  = strings_copy;
    res.n_Lines = n_Lines;
    res.sz_File = sz_File;
    res.fout    = file_out;

    return res;
}

//{============================================================================
//! Make array (strings),
//! in which elem [i] is pointer to the start of string number [i] in the text
//}============================================================================

void Make_Array_Of_Structs (char* *strings_copy, struct string_t *strings_arr,
                            char* *buf, int n_Lines, int sz_File)
{
    int pos  = -1;
    int line = -1;

    while (pos < sz_File - 1 && line < n_Lines - 1)
    {
        if ((*buf)[pos] == '\0' || (*buf)[pos] == '\n')
        {
            (*buf)[pos] = '\0';

            line++;
            assert(0 <= line && line < n_Lines);

            strings_arr[line].str = (*buf + pos + 1);  assert (*buf + pos + 1);
            strings_copy[line]    = (*buf + pos + 1);

            if (strings_arr[line].str - strings_arr[line - 1].str == 1 ||
                strings_arr[line].str - strings_arr[line - 1].str == 0)
            {
                strings_arr[line - 1].len = 0;
            }
            else
                strings_arr[line - 1].len = strings_arr[line].str - strings_arr[line - 1].str - 2;
        }

        pos++;
    }

    if (*buf + pos - strings_arr[line].str == 1 ||
        *buf + pos - strings_arr[line].str == 0)
    {
        strings_arr[line].len = 0;
    }
    else
       strings_arr[line].len = *buf + pos - strings_arr[line].str - 1;
}

//{============================================================================
//! Read file and make buffer for text
//}============================================================================

int Find_Size_Of_File (const char *fin)
{
    struct stat text = {};

    stat (fin, &text);

    return text.st_size;
}

//=============================================================================

int Number_Of_Lines (const int sz_File, const char *buf)
{
    int cnt = 0;
    for (int i = 0; i < sz_File - 1; i++)
    {
        if (*(buf + i) == '\n')
        {
            cnt++;
        }
    }

    return cnt;
}
