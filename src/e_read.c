#include "push_swap.h"

char    reverse_c(char c);
char    *reverse_str(char *cmd);



char    reverse_c(char c)
{
    if (c >= '1')
        c ^= 1;
    else if (c >= '4')
        return (c);
    else if (c >= '7')
        c += 3;
    else if (c >= ':')
        c -= 3;
    return (c);
}

char    *reverse_str(char *cmd)
{
    char    *reverse = str("%s", cmd);
    int     size = len(cmd);
    if (!reverse)
        return (NULL);
    int i = -1;
    while (cmd[++i])
        reverse[size - i - 1] = reverse_c(cmd[i]);
    return (reverse);
}



// [ 0 ] pb  [ 1 ] pa  [ 2 ] sa  [ 3 ] sb  [ 4 ] ss  [ 5 ] ra  [ 6 ] rb  [ 7 ] rr  [ 8 ] rra  [ 9 ] rrb






// if (wiii("+-.=", raw[0]) && !(error = 0))
//     function_test[wiii("+-.=")](stacks, atoi_v(&raw[1]));
