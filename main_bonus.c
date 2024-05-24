#include "push_swap.h"

////////////////////////////////////////////////////////////
int main(int ac, char **av)
{
    t_stacks    stacks;

    if (ac < 2)
        return (put(MSG_NONUM));
    ini_stacks(ac, av, &stacks);
//////////////////////////////

    print_header(&stacks, 0b111, 0);
    tester(&stacks);
    test_output(&stacks);


//////////////////////////////
    exit_all(&stacks, NULL, 0, NULL);
    return (0);
}
////////////////////////////////////////////////////////////
