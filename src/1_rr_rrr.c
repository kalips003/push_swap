#include "push_swap.h"

//  rr : ra and rb at the same time.
int    rr(t_stacks *s, char sw)
{
    if (sw)
        put(RR"\n");
    ra(s, 0);
    rb(s, 0);
    return (1);
}

//  rra (reverse rotate a): Shift down all elements of stack a by 1.    The last element becomes the first one.
//  #   REVERSE ROTATE A
int    rra(t_stacks *s, char sw)
{
    if (sw)
        put(RRA"\n");
    if (s->size_a < 2)
        return (1);
    s->top_a = s->top_a->above;
    return (1);
}

//  #   REVERSE ROTATE B
int    rrb(t_stacks *s, char sw)
{
    if (sw)
        put(RRB"\n");
    if (s->size_b < 2)
        return (1);
    s->top_b = s->top_b->above;
    return (1);
}

//  rrr : rra and rrb at the same time.
int    rrr(t_stacks *s, char sw)
{
    if (sw)
        put(RRR"\n");
    rra(s, 0);
    rrb(s, 0);
    return (1);
}