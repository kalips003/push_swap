#include "push_swap.h"

static char *sublim(t_stacks *stacks)
{
    t_entry *zero;
    int     i;

    zero = stacks->top_a;
    i = -1;
    while (++i < stacks->full_size)
    {
        if (i == stacks->size_a)
            zero = stacks->top_b;
        if (zero->num_index == 0)
            break ;
        zero = zero->below;
    }
    give_position(stacks);
    if (zero->pile == 'B' && zero->above->num_index == 1)
        //  in order
        return (str("%.*c%.*c", abs(zero->dist + 1), '6' + 3 * (zero->dist < 0), stacks->full_size, '1'));
    if (zero->pile == 'B' && zero->below->num_index == 1)
        //  reverse
        return (str("%.*c%*s", abs(zero->dist), '6' + 3 * (zero->dist < 0), stacks->full_size, "91"));
    if (zero->pile == 'A' && zero->above->num_index == 1)
        //  reverse
        return (str("%*s%.*c%.*c", stacks->full_size, "80", abs(zero->dist + 1), '6' + 3 * (zero->dist < 0), stacks->full_size, '1'));
    if (zero->pile == 'A' && zero->below->num_index == 1)
        //  in order
        return (str("%.*c", abs(zero->dist), '5' + 3 * (zero->dist < 0)));
    return (NULL);
}
///////////////////////////////////////////////////////////////////////////////]
int main(int ac, char **av)
{
    t_stacks    stacks;

    if (ac < 2)
        return (put(MSG_NONUM));
    ini_stacks(ac, av, &stacks);
///////////////////////////
    t_entry *small;

    small = assign_str_all(&stacks);
    int i = 0;
    // i += function_cmd_string(&stacks, str("%*.c", stacks.full_size / 2, '0'), 1);
    while (small && small->algo)
    {
        i += function_cmd_string(&stacks, small->algo, 1);
        small = assign_str_all(&stacks);
    }
    char *last = sublim(&stacks);
    i += len(last);
    function_cmd_string(&stacks, last, 1);
    free_s(last);
    print_one_line(&stacks, 1, 1);
    put("\talgo cost = %d\n", i);
////    FOOTER      ////
    //test_output(&stacks);
    exit_all(&stacks, NULL, 0, NULL);
    return (0);
}
