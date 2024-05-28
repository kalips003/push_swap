#include "push_swap.h"

////////////////////////////////////////////////////////////
//	#	takes in "0123456789a11", and do it, instructions can be NULL
//  sw2 = print > no_print (instructions beeing executed)
int    function_cmd_string(t_stacks *stacks, char *instructions, char sw2)
{
    int i = -1;
    int b;

    if (!instructions)
        return (0);
    while (instructions[++i])
    {
        b = wii_wrapper(instructions[i]);
        if (b >= 0)
            function_cmd(stacks, b, sw2);
    }
    return (len(instructions));
}

////////////////////////////////////////////////////////////
//	#	COMMANDS FUNCTION
//  sw2: 0 = execute; 1 = execute and print
void    function_cmd(t_stacks *stacks, int i, char sw2)
{
    f_cmd    function_cmd[] = {
        pb,// 0
        pa,
        sa,
        sb,
        ss,
        ra,// 5
        rb,
        rr,
        rra,
        rrb,
        rrr// x = 10
    };
    function_cmd[i](stacks, sw2);
}
