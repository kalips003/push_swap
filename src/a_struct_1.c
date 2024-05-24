#include "push_swap.h"

//////////////////////////////////////////////////////
//  #  FREE THE FULL STACK
void    free_stack(t_entry *first)
{
    t_entry *next;
    t_entry *current;

    if (first == NULL)
        return ;
    current = first;
    while (current->below && current->below != first)
    {
        next = current->below;
        free(current);
        current = next;
    }
    free(current);
}

//////////////////////////////////////////////////////
//  #   CREATE NEW NUMBER NODE,  ATTACH IT TO LAST_NODE
//  PUT THE NUMBER IN, CHECK IF VALABLE    //(char *"arg")
//  exit_code -5: number too big
//  exit_code -4: not a number
t_entry    *create_new_node(t_entry *last_node, char *arg, t_stacks *s)
{
    t_entry *new_node;
    int     error;

    new_node = (t_entry *)mem(0, sizeof(t_entry));
    if (!new_node)
        exit_all(s, MSG_MALLOC, -9, NULL);
    new_node->algo = NULL;
    new_node->above = last_node;
    error = 0;
    new_node->num = ft_atoi(arg, &error);
    if (error == -2)
        exit_all(s, MSG_TOOBIG, error, new_node);
    else if (error < 0)
        exit_all(s, MSG_NOTNUM, error, new_node);
    if (last_node)
        last_node->below = new_node;
    return (new_node);
}

///////////////////////////////////////////////////////
//  #   TAKES STACK A PAS ENCORE REFERME, ASSIGN 012345.. VALUE
//  #   CHECKS DUPLICATES
//  exit_code -3: duplicates number
void assign_value(t_stacks *stacks)
{
    t_entry *ptr_i;
    t_entry *ptr_k;

    ptr_i = stacks->top_a;
    while (ptr_i)
    {
        ptr_k = stacks->top_a;
        while (ptr_k)
        {
            if (ptr_i != ptr_k && ptr_i->num == ptr_k->num)
                exit_all(stacks, MSG_DUPLICATE, -3, NULL);
            if (ptr_i->num > ptr_k->num)
                ptr_i->num_index++;
            ptr_k = ptr_k->below;
        }
        ptr_i = ptr_i->below;
    }
}

//////////////////////////////////////////////////////
//  #   CREATE THE FULL 'A' STACK WITH NUMBER, CHECK ERRORS, RETURN POINTER TO TOP OF A
t_entry *create_stack_a(int ac, char **av, t_stacks *stacks, int j)
{
    int i;
    t_entry *a_end;

    a_end = NULL;
    i = 0;
    while (++i < ac)
    {
        a_end = create_new_node(a_end, av[i - j], stacks);
        if (i == 1)
            stacks->top_a = a_end;
    }
    assign_value(stacks);
    assign_target(stacks);
    stacks->top_a->above = a_end;
    a_end->below = stacks->top_a;
    return (stacks->top_a);
}

//////////////////////////////////////////////////////
//  #  CREATE THE FULL STACKS STRUCT
void    ini_stacks(int ac, char **av, t_stacks *stacks)
{

    ft_memset(stacks, 0, sizeof(t_stacks));
    stacks->full_size = ac - 1;
    stacks->size_a = stacks->full_size;
    stacks->top_b = NULL;
    stacks->top_a = NULL;
    stacks->args = NULL;
    // ini instru struct
    if (ac == 2)
    {
        stacks->args = split(av[1], " ");
        if (!stacks->args) {
            exit_all(stacks, MSG_MALLOC, -3, NULL);
        }
        stacks->full_size = tab_size(stacks->args);
        stacks->size_a = stacks->full_size;
        stacks->top_a = create_stack_a(stacks->full_size + 1, stacks->args, stacks, 1);
        return ;
    }
    stacks->top_a = create_stack_a(stacks->full_size + 1, av, stacks, 0);
}