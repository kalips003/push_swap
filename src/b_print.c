#include "push_swap.h"
//////////////////////////////////////////////////////
//  #   PRINNTING
//      switch 0 = real number
//      switch 1 = index number
void    print_one_line(t_stacks *stacks, int sw, int bit)
{
    if (!bit)
        put(CLEAR);
    put(" \033[48;5;4m" "[ B ] [" RESET);
    print_stack_b(stacks, stacks->top_b, stacks->size_b, sw);
    put("\033[48;5;4m" " > "RESET"  ""\033[48;5;1m" " < "RESET);
    print_stack(stacks, stacks->top_a, stacks->size_a, sw);
    put("\033[48;5;1m" "] [ A ]"RESET"\n");
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

# define COLOR "\033[38;5;166m"

//  #   print commands header, bit = [0-3]
//  [ - , - , 1] = clear
//  [ - , 1, - ] = print stacks
//  [ 1, - , - ] = print header
void    print_header(t_stacks *stacks, int bit, int sw)
{
    if ((bit & 1) == 1)
        put(CLEAR);
    if (((bit >> 2) & 1) == 1)
        put(RESET "\n\t[ 0 ] "PB"  [ 1 ] "PA"  "
        "\n\t[ 2 ] "SA"  [ 3 ] "SB"  [ 4 ] "SS"  "
        "\n\t[ 5 ] "RA"  [ 6 ] "RB"  [ 7 ] "RR"  "
        "\n\t[ 8 ] "RRA" [ 9 ] "RRB" [ : ] "RRR"\n\n"
        COLOR" [ "RESET"*"COLOR" ] TOOGLE  "
        "[ "RESET"+"COLOR" ] USE MAGIC  "
        "[ "RESET"-"COLOR" ] USE MAGIC 2  "
        "[ "RESET"^D"COLOR" ] grade me\n\n"RESET);
    if (((bit >> 1) & 1) == 1)
        print_one_line(stacks, sw, bit);
}

void    print_stru_algo(t_algo *a)
{
    put("N_blk  (%d => %d): position= %c.%d (distance= %d)\n", a->blk_num->num, a->blk_num->num_index, a->blk_num->pile, a->blk_num->position, a->blk_num->dist);
    put("\tsize block = %d;\n", a->sizeb_n);
    put("NUM    (%d => %d): position= %c.%d (distance= %d)\n", a->num->num, a->num->num_index, a->num->pile, a->num->position, a->num->dist);
    put("\nNum_dist_target = %d; num_d_tar_plus =  %d; bt_dist_bn = %d\n", a->num_dist_target, a->num_d_tar_plus, a->bt_dist_bn);

    put("\nTARGET (%d => %d): position= %c.%d (distance= %d)\n", a->target->num, a->target->num_index, a->target->pile, a->target->position, a->target->dist);
    put("\tsize block = %d;\n", a->sizeb_t);
    put("T_blk  (%d => %d): position= %c.%d (distance= %d)\n", a->blk_tar->num, a->blk_tar->num_index, a->blk_tar->pile, a->blk_tar->position, a->blk_tar->dist);
    put("\tSTRING = %s;\n", a->num->algo);
}
