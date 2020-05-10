// enum.h

#define DEF_CMD(name, num, code, arg) \
    CMD_##name = num,

enum commands
    {
    #include "Commands.h"
    };

#undef DEF_CMD
