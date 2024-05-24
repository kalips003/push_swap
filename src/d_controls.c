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

////////////////////////////////////////////////////////////
//	#	EXIT FUNCTION
//  #   free ptr + stacks; if exit_code < 0, exit
int    exit_all(t_stacks *s, char *message, int exit_code, void *ptr)
{
    if (s)
        free_algos(s);
    if (s && s->args)
        free_tab(s->args);
    if (ptr)
        free(ptr);
    if (s && s->size_a && s->top_a)
        free_stack(s->top_a);
    if (s && s->size_b && s->top_b)
        free_stack(s->top_b);
    if (exit_code)
        put("%s" RESET, message);//  "some error happnd' honey\n"
    if (exit_code < 0)
        exit(exit_code);
    return (exit_code);
}

////////////////////////////////////////////////////////////
//	#	EXIT FUNCTION
//  free all strings algo
void    free_algos(t_stacks *stacks)
{
    int i;
    t_entry *cursor;

    i = -1;
    cursor = stacks->top_a;
    while (++i < stacks->full_size)
    {
        if (i == stacks->size_a)
            cursor = stacks->top_b;
        if (!cursor)
            break ;
        if (cursor->algo)
            free(cursor->algo);
        cursor->algo = NULL;
        cursor = cursor->below;
    }
}