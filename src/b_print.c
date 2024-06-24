#include "push_swap.h"

void    print_one_line(t_stacks *stacks, int sw, int bit);
void    print_stack(t_stacks *stacks, t_entry *s, int size_stack, char sw);
void    print_stack_b(t_stacks *stacks, t_entry *s, int size_stack, char sw);

//////////////////////////////////////////////////////
//  #   PRINNTING
//      switch 0 = real number
//      switch 1 = index number
void    print_one_line(t_stacks *stacks, int sw, int bit)
{
    if (!bit)
        put(CLEAR);
    put(UNDER_B"[ B ] ["RESET);
    print_stack_b(stacks, stacks->top_b, stacks->size_b, sw);
    put(UNDER_B" > "RESET"  "UNDER_R" < "RESET);
    print_stack(stacks, stacks->top_a, stacks->size_a, sw);
    put(UNDER_R"] [ A ]"RESET"\n");
}


//  #   print one stack
void    print_stack(t_stacks *stacks, t_entry *s, int size_stack, char sw)
{
    int     i;

    i = -1;
    while (++i < size_stack)
    {
        if (s->num_index == s->above->num_index - 1 || s->num_index == s->below->num_index + 1)
            put(BLUE);
        else if (s->num_index == s->below->num_index - 1 || s->num_index == s->above->num_index + 1)
            put(RED);
        else
            put(RESET);
        if (s->num_index == 0 || s->num_index == stacks->full_size - 1)
            put(PURPLE);
        if(sw)
            put("\033[4m""% 3d", s->num_index);
        else
            put("\033[4m""% 3d", s->num);
        s = s->below;
    }
    put(RESET);
}

//  #   print one stack
void    print_stack_b(t_stacks *stacks, t_entry *s, int size_stack, char sw)
{
    int     i;

    i = -1;
    if (size_stack)
        s = s->above;
    while (++i < size_stack)
    {
        if (s->num_index == s->above->num_index - 1 || s->num_index == s->below->num_index + 1)
            put(RED);
        else if (s->num_index == s->below->num_index - 1 || s->num_index == s->above->num_index + 1)
            put(BLUE);
        else
            put(RESET);
        if (s->num_index == 0 || s->num_index == stacks->full_size - 1)
            put(PURPLE);
        put("\033[4m""% 3d", sw * (s->num_index) + !sw * (s->num));
        s = s->above;
    }
    put(RESET);
}

