#include "push_swap.h"

////////////////////////////////////////////////////////////
// find target
t_entry *find_target(t_stacks *stacks, t_entry *num)
{
    int     i;
    t_entry *s;
    int     target;

    target = (num->num_index + 1) % stacks->full_size;
    i = -1;
    s = stacks->top_a;
    while (++i < stacks->full_size)
    {
        if (i == stacks->size_a)
            s = stacks->top_b;
        if (s->num_index == target)
            return (s);
        s = s->below;
    }
    return (num);
}

////////////////////////////////////////////////////////////
// if in order 1 (0 1)
// if reverse order -1 (3 2)
// else 0
int  help_modulo(t_stacks *s, t_entry *previous, t_entry *next)
{
    int size;

    size = next->num_index - previous->num_index;
    if (size == 1 || size == -s->full_size + 1)
        return (1);
    else if (size == -1 || size == s->full_size - 1)
        return (-1);
    else
        return (0);
}

////////////////////////////////////////////////////////////
//  #   SET: blk_num _ sizeb_n  __ blk_tar _ sizeb_t
// pb with B:[21-22] > a->sizeb_n == 0,1,0,1,0,1...
static void helper_block_size(t_stacks *stacks, t_algo *a)
{
    a->blk_num = a->num;
    while (++a->sizeb_n < a->blk_num->size_s && help_modulo(stacks, *((t_entry **)(a->blk_num) + (a->blk_num->pile == 'B')), a->blk_num))
        a->blk_num = *((t_entry **)(a->blk_num) + (a->blk_num->pile == 'B'));
    a->blk_tar = a->target;
    while (++a->sizeb_t < a->blk_tar->size_s && help_modulo(stacks, a->blk_tar, *((t_entry **)(a->blk_tar) + (a->blk_tar->pile == 'A'))) == 1)
        a->blk_tar = *((t_entry **)(a->blk_tar) + (a->blk_tar->pile == 'A'));
    if (help_modulo(stacks, *((t_entry **)(a->blk_tar) + (a->blk_tar->pile == 'B')), a->blk_tar) == -1)
    {
        a->sizeb_t = 0;
        while (++a->sizeb_t < a->blk_tar->size_s && help_modulo(stacks, *((t_entry **)(a->blk_tar) + (a->blk_tar->pile == 'B')), a->blk_tar) == -1)
            a->blk_tar = *((t_entry **)(a->blk_tar) + (a->blk_tar->pile == 'B'));
        a->sizeb_t *= -1;
    }
}

////////////////////////////////////////////////////////////
//  #    initialize algori struct
void    fill_stru_algo(t_stacks *stacks, t_algo *a, t_entry *num)
{
    ft_memset(a, 0, sizeof(t_algo));
    a->num = num;
    a->target = find_target(stacks, num);
//  blocks handling
    helper_block_size(stacks, a);
//  num_dist_target
    if ((num->position >> 31) == (a->target->position >> 31))
    {
        a->num_dist_target = -1;
        t_entry *temp = num;
        while (++(a->num_dist_target) < num->size_s && temp != a->target)
            temp = *((t_entry **)(temp) + (temp->pile == 'A'));
        a->num_d_tar_plus = a->num_dist_target;
        if (a->num_dist_target > num->size_s / 2)
            a->num_dist_target -= num->size_s;
        a->bt_dist_bn = -1;
        temp = a->blk_tar;
        while (++(a->bt_dist_bn) < num->size_s && temp != a->blk_num)
            temp = *((t_entry **)(temp) + (temp->pile == 'A'));
    }
}

////////////////////////////////////////////////////////////
t_entry *assign_str_all(t_stacks *stacks)
{
    int     i;
    t_entry *temp;
    t_entry *small = NULL;
    int     smaller = 0;

    free_algos(stacks);
    give_position(stacks);
    i = -1;
    temp = stacks->top_a;
    while (++i < stacks->full_size)
    {
        if (i == stacks->size_a)
            temp = stacks->top_b;
        temp->algo_sz = assign_str(stacks, temp);
        if (temp->algo_sz && (smaller == 0 || temp->algo_sz < smaller))
        {
            smaller = temp->algo_sz;
            small = temp;
        }
        temp = temp->below;
    }
    return (small);
}
