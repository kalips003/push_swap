#include "push_swap.h"

int    reading_cmd(char *raw, t_stacks *stacks);
char    reverse_c(char c);
char    *reverse_str(char *cmd);
void    tester(t_stacks *stacks);

////////////////////////////////////////////////////////////
//	#	takes raw input, look for 'pb\n', execute
//	return -1 on bad command
//  return 0 on EOF
int    reading_cmd(char *raw, t_stacks *stacks)
{
    int i;
    int cmd;

    i = -1;
    while (raw[++i] && (cmd = wii_wrapper(raw[i])) <= -2)
    {
        if (cmd < -3)
        {
            if ((cmd = wii_strikes_back(&raw[i], &i)) < 0)
                return (-1);
            function_cmd(stacks, cmd, 0);
        }
    }
    return (0);
}

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




////////////////////////////////////////////////////////////
//      TESTER
////////////////////////////////////////////////////////////
//	#	main tester, ask for raw, execute, loop out when [ctrl-D]
void    tester(t_stacks *stacks)
{
    char    *raw;
    char    sw;
    int     error;

    sw = 0;
    while ((raw = gnl(0)))
    {
        if ((error = wii_wrapper(raw[0])) >= 0)
            function_cmd_string(stacks, raw, 0);
        else if (error <= -4)
            error = reading_cmd(raw, stacks);
        if (raw[0] == '*' && !(error = 0))
            sw ^= 1;
        print_header(stacks, 0b111, sw);
        if (raw[0] == '.' && !(error = 0))
            function3(stacks);
        if (raw[0] == '+' && !(error = 0))
            function2(stacks, atoi_v(&raw[0]));//         <<<
        if (raw[0] == '-' && !(error = 0))
            function1(stacks, atoi_v(&raw[1]));//         <<<
        if (error == -1)
            put("\033[38;5;94m""trying:" RESET" %s\n" MSG_BADCMD, raw);
        put("\033[38;5;58;4m""\n>input"RESET"\n");
        free(raw);
    }
}

// if (wiii("+-.=", raw[0]) && !(error = 0))
//     function_test[wiii("+-.=")](stacks, atoi_v(&raw[1]));
