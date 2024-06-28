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

#define COLOR COLOR_2R_3G_5B
///////////////////////////////////////////////////////////////////////////////]
void	print(t_data *data, int sw, int bit)
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
//  if sw: num_i
void	print_header(t_data *data, int bit, int sw)
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
	if (s && s->ab == 'B')
		s = s->up;
	while (s && ++i < s->size_s)
	{
		if ((s->target == s->up && s->ab == 'A')
			|| (s->target == s->down && s->ab == 'B'))
			put(BLUE);
		else if ((s->target == s->down && s->ab == 'A')
			|| (s->target == s->up && s->ab == 'B'))
			put(RED);
		else
			put(RESET);
		if (s->num_i == 0 || s->num_i == data->size - 1)
			put(PURPLE);
		if (sw)
			put("\033[4m""% 3d", s->num_i);
		else
			put("\033[4m""% 3d", s->num);
		s = *((t_num **)s + (s->ab == 'A'));
	}
	put(RESET);
}

///////////////////////////////////////////////////////////////////////////////]
void	print_stru_algo(t_algo *a)
{
	put("N_blk  (%d => %d): position= %c.%d (distance= %d)\n", a->bnum->num,
		a->bnum->num_i, a->bnum->ab, a->bnum->position, a->bnum->dist);
	put("\tsize block = %d;\n", a->sbn);
	put("NUM   (%d => %d): position= %c.%d (distance= %d)\n", a->num->num,
		a->num->num_i, a->num->ab, a->num->position, a->num->dist);
	put("Num_dist_target = %d; ndtp =  %d; btbn = %d\n", a->ndt, a->ndtp,
		a->btbn);
	put("TARGET (%d => %d): position= %c.%d (distance= %d)\n", a->tar->num,
		a->tar->num_i, a->tar->ab, a->tar->position, a->tar->dist);
	put("\tsize block = %d;\n", a->sbt);
	put("T_blk  (%d => %d): position= %c.%d (distance= %d)\n", a->btar->num,
		a->btar->num_i, a->btar->ab, a->btar->position, a->btar->dist);
	put("\tSTRING = %s;\n", a->num->algo);
}
