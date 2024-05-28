#include "push_swap.h"

static void push_helper(t_entry **push_to, t_entry **push_from, int size)
{
    if (size)
    {
        (*push_from)->above = (*push_to)->above;
        (*push_to)->above->below = (*push_from);
        (*push_to)->above = (*push_from);
        (*push_from) = (*push_from)->below;
        (*push_to)->above->below = (*push_to);
        (*push_to) = (*push_to)->above;
    }
    else
    {
        (*push_to) = (*push_from);
        (*push_from) = (*push_from)->below;
        (*push_to)->above = (*push_to);
        (*push_to)->below = (*push_to);
    }
}

//  pb (push b): Take the first element at the top of a and put it at the top of b.    Do nothing if a is empty.
//  #   PUSH B
int    pb(t_stacks *s, char sw)
{
    if (sw)
        put(PB"\n");
    if (s->size_a == 0)
        return (0);
    s->top_a->above->below = s->top_a->below;
    s->top_a->below->above = s->top_a->above;
    push_helper(&s->top_b, &s->top_a, s->size_b);
    if (s->size_a == 1)
        s->top_a = NULL;
    (s->size_a--, s->size_b++);
    return (1);
}

//  #   PUSH A
int    pa(t_stacks *s, char sw)
{
    if (sw)
        put(PA"\n");
    if (s->size_b == 0)
        return (0);
    s->top_b->above->below = s->top_b->below;
    s->top_b->below->above = s->top_b->above;
    push_helper(&s->top_a, &s->top_b, s->size_a);
    if (s->size_b == 1)
        s->top_b = NULL;
    (s->size_b--, s->size_a++);
    return (1);
}

//  ra (rotate a): Shift up all elements of stack a by 1.   The first element becomes the last one.
//  #   ROTATE A
int    ra(t_stacks *s, char sw)
{
    if (sw)
        put(RA"\n");
    if (s->size_a < 2)
        return (1);
    s->top_a = s->top_a->below;
    return (1);
}

//  #   ROTATE B
int    rb(t_stacks *s, char sw)
{
    if (sw)
        put(RB"\n");
    if (s->size_b < 2)
        return (1);
    s->top_b = s->top_b->below;
    return (1);
}