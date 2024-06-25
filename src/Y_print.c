/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_print.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:23:01 by kalipso           #+#    #+#             */
/*   Updated: 2024/06/24 12:23:01 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print(t_stacks *stacks, int sw, int bit);
void	print_header(t_stacks *stacks, int bit, int sw);
void	print_stru_algo(t_algo *a);
void	print_stack(t_stacks *stacks, t_entry *s, char sw);

# define COLOR "\033[38;5;166m"
///////////////////////////////////////////////////////////////////////////////]
void    print(t_stacks *stacks, int sw, int bit)
{
    if (!bit)
        put(CLEAR);
    put(UNDER_B"[ B ] ["RESET);
    print_stack(stacks, stacks->top_b, sw);
    put(UNDER_B" > "RESET"  "UNDER_R" < "RESET);
    print_stack(stacks, stacks->top_a, sw);
    put(UNDER_R"] [ A ]"RESET"\n");
}

///////////////////////////////////////////////////////////////////////////////]
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
        "[ "RESET"-"COLOR" ] USE MAGIC 1 "
        "[ "RESET"+"COLOR" ] USE MAGIC 2 "
        "[ "RESET"."COLOR" ] USE MAGIC 3  "
        "[ "RESET"^D"COLOR" ] grade me\n\n"RESET);
    if (((bit >> 1) & 1) == 1)
        print(stacks, sw, bit);
}

//  #   print one stack
void	print_stack(t_stacks *stacks, t_entry *s, char sw)
{
	int	i;

	i = -1;
	give_position(stacks);
	if (s && s->pile_c == 'B')
		s = s->above;
	while (s && ++i < s->size_s)
	{
		// put("(->%d:%d)\n", i, s->size_s);
		// if (s->num_index == s->above->num_index - 1 || s->num_index == s->below->num_index + 1)
		if ((s->target == s->above && s->pile_c == 'A') || (s->target == s->below && s->pile_c == 'B'))
			put(BLUE);
		else if ((s->target == s->below && s->pile_c == 'A') || (s->target == s->above && s->pile_c == 'B'))
			put(RED);
		else
			put(RESET);
		if (s->num_index == 0 || s->num_index == stacks->full_size - 1)
			put(PURPLE);
		if(sw)
			put("\033[4m""% 3d", s->num_index);
		else
			put("\033[4m""% 3d", s->num);
		s = *((t_entry **)s + (s->pile_c == 'A'));
	}
	put(RESET);
}

///////////////////////////////////////////////////////////////////////////////]
void    print_stru_algo(t_algo *a)
{
    put("N_blk  (%d => %d): position= %c.%d (distance= %d)\n", a->blk_num->num, a->blk_num->num_index, a->blk_num->pile_c, a->blk_num->position, a->blk_num->dist);
    put("\tsize block = %d;\n", a->sizeb_n);
    put("NUM    (%d => %d): position= %c.%d (distance= %d)\n", a->num->num, a->num->num_index, a->num->pile_c, a->num->position, a->num->dist);
    put("\nNum_dist_target = %d; num_d_tar_plus =  %d; bt_dist_bn = %d\n", a->num_dist_target, a->num_d_tar_plus, a->bt_dist_bn);

    put("\nTARGET (%d => %d): position= %c.%d (distance= %d)\n", a->target->num, a->target->num_index, a->target->pile_c, a->target->position, a->target->dist);
    put("\tsize block = %d;\n", a->sizeb_t);
    put("T_blk  (%d => %d): position= %c.%d (distance= %d)\n", a->blk_tar->num, a->blk_tar->num_index, a->blk_tar->pile_c, a->blk_tar->position, a->blk_tar->dist);
    put("\tSTRING = %s;\n", a->num->algo);
}
