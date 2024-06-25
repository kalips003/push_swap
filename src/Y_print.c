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

void	print(t_data *data, int sw, int bit);
void	print_header(t_data *data, int bit, int sw);
void	print_stru_algo(t_algo *a);
void	print_stack(t_data *data, t_num *s, char sw);

# define COLOR COLOR_2R_3G_5B
///////////////////////////////////////////////////////////////////////////////]
void    print(t_data *data, int sw, int bit)
{
    if (!bit)
        put(CLEAR);
    put(UNDER_B"[ B ] ["RESET);
    print_stack(data, data->top_b, sw);
    put(UNDER_B" > "RESET"  "UNDER_R" < "RESET);
    print_stack(data, data->top_a, sw);
    put(UNDER_R"] [ A ]"RESET"\n");
}

///////////////////////////////////////////////////////////////////////////////]
//  #   print commands header, bit = [0-3]
//  [ - , - , 1] = clear
//  [ - , 1, - ] = print data
//  [ 1, - , - ] = print header
//  if sw: num_index
void    print_header(t_data *data, int bit, int sw)
{
	if ((bit & 1) == 1)
		put(CLEAR);
	if (((bit >> 2) & 1) == 1)
		put(RESET "\n(8) "RRA" (9) "RRB" (:) "RRR"  "
		"\n(5) "RA"  (6) "RB"  (7) "RR"  "
		"\n(2) "SA"  (3) "SB"  (4) "SS"  "
		"\n(0) "PB"  (1) "PA"\n\n"
		COLOR" ["RESET"-n"COLOR"] F1 "
		"["RESET"+n"COLOR"] F2 "
		"["RESET"."COLOR"] F3 "
		"["RESET"*"COLOR"] TOOGLE  "
		"["RESET"^D"COLOR"] grade me\n\n"RESET);
	if (((bit >> 1) & 1) == 1)
		print(data, sw, bit);
	put("\n");
}

//  #   print one stack
void	print_stack(t_data *data, t_num *s, char sw)
{
	int	i;

	i = -1;
	give_position(data);
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
		if (s->num_index == 0 || s->num_index == data->full_size - 1)
			put(PURPLE);
		if(sw)
			put("\033[4m""% 3d", s->num_index);
		else
			put("\033[4m""% 3d", s->num);
		s = *((t_num **)s + (s->pile_c == 'A'));
	}
	put(RESET);
}

///////////////////////////////////////////////////////////////////////////////]
void	print_stru_algo(t_algo *a)
{
	put("N_blk  (%d => %d): position= %c.%d (distance= %d)\n", a->blk_num->num, a->blk_num->num_index, a->blk_num->pile_c, a->blk_num->position, a->blk_num->dist);
	put("\tsize block = %d;\n", a->sizeb_n);
	put("NUM   (%d => %d): position= %c.%d (distance= %d)\n", a->num->num, a->num->num_index, a->num->pile_c, a->num->position, a->num->dist);
	put("\nNum_dist_target = %d; num_d_tar_plus =  %d; bt_dist_bn = %d\n", a->num_dist_target, a->num_d_tar_plus, a->bt_dist_bn);

	put("\nTARGET (%d => %d): position= %c.%d (distance= %d)\n", a->target->num, a->target->num_index, a->target->pile_c, a->target->position, a->target->dist);
	put("\tsize block = %d;\n", a->sizeb_t);
	put("T_blk  (%d => %d): position= %c.%d (distance= %d)\n", a->blk_tar->num, a->blk_tar->num_index, a->blk_tar->pile_c, a->blk_tar->position, a->blk_tar->dist);
	put("\tSTRING = %s;\n", a->num->algo);
}
