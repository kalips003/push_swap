#include "push_swap.h"

static void modulo_s(t_entry *current);
static void helper_give_posi(t_stacks *s, t_entry *current, char a, int i);
void    give_position(t_stacks *s);
void    reevalue(t_stacks *s, t_entry *num);

// #    TAKES A VALUE posi? and return dist from origin
static void modulo_s(t_entry *current)
{
    int abs_posi;
    
    abs_posi = abs(current->position) - 1;
    if (current->pile == 'A')
    {
        current->dist_p = current->position;
        current->dist_n = current->size_s - current->position;
    }
    else
    {
        current->dist_p = abs_posi;
        current->dist_n = current->size_s - abs_posi;
    }
    if (current->position > current->size_s / 2)
        current->dist = current->position - current->size_s;
    else if (current->position >= 0)
        current->dist = current->position;
    else if (current->position  < 0 && abs_posi > current->size_s / 2)
       current->dist = abs_posi - current->size_s;
    else
       current->dist = abs_posi;
}

//////////////////////////////////////////////////////
//  #  give one member of A & B its position [0 size of A] [-1 -size of B] [dist from origin]
static void helper_give_posi(t_stacks *s, t_entry *current, char a, int i)
{
    if (a == 'A')
    {
        current->position = i;
        current->size_s = s->size_a;
    }
    else
    {
        current->position = -(i + 1);
        current->size_s = s->size_b;
    }
    current->pile = a;
    modulo_s(current);
}

// // #    TAKES A VALUE posi? and return dist from origin
// static int modulo_s2(int posi, int size_s)
// {
//     int abs_posi;
    
//     abs_posi = abs(posi) - 1;
//     if (posi > size_s / 2)
//         return (posi - size_s);
//     else if (posi >= 0)
//         return (posi);
//     else if (posi  < 0 && abs_posi > size_s / 2)
//        return (abs_posi - size_s);
//     else
//        return (abs_posi);
// }

//////////////////////////////////////////////////////
//  #  give each member of A & B its position [0 size of A] [-1 -size of B] [dist from origin]
void    give_position(t_stacks *s)
{
    int i;
    t_entry *current;

    i = -1;
    current = s->top_a;
    while (++i < s->size_a)
    {
        helper_give_posi(s, current, 'A', i);
        current = current->below;
    }
    i = -1;
    current = s->top_b;
    while (++i < s->size_b)
    {
        helper_give_posi(s, current, 'B', i);
        current = current->below;
    }
}

// reassignn value and char to num
void    reevalue(t_stacks *s, t_entry *num)
{
    int i;
    t_entry *current;

    i = -1;
    current = s->top_a->above;
    while (++i < s->size_a && (current = current->below))
        if (current == num)
            return (helper_give_posi(s, current, 'A', i));
    i = -1;
    current = s->top_b->above;
    while (++i < s->size_b && (current = current->below))
        if (current == num)
            return (helper_give_posi(s, current, 'B', i));
    //  assign_str(s, num);
}