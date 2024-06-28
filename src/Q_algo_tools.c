/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_algo_s.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 00:31:50 by kalipso           #+#    #+#             */
/*   Updated: 2024/06/25 00:31:50 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

char	*sublim(t_data *data);
char	*smallest_str(int nb, ...);
int		order(t_data *s, t_num *previous, t_num *next);
void	helper_num_dist_target(t_data *data, t_algo *a, t_num *num);
void	helper_block_size(t_data *data, t_algo *a);

///////////////////////////////////////////////////////////////////////////////]
// (0 pb)(1 pa)(2 sa)(3 sb)(4 ss)(5 ra)(6 rb)(7 rr)(8 rra)(9 rrb)(: rrr)
// once everything is in order, puts index 0 on top of A
char	*sublim(t_data *data)
{
	t_num	*zero;
	char	*string;

	zero = data->zero;
	give_position(data);
	if (zero->ab == 'B' && zero->up->num_i == 1)
		return (str("%.*c%.*c", abs(zero->dist + 1), '6' + 3 * (zero->dist < 0),
				data->size, '1'));
	else if (zero->ab == 'B' && zero->down->num_i == 1)
		return (str("%.*c%*s", abs(zero->dist), '6' + 3 * (zero->dist < 0),
				data->size, "91"));
	else if (zero->ab == 'A' && zero->up->num_i == 1)
	{
		if (data->size == 3)
			return (str("2%c", ('5' + 3 * (zero->dist_p == 2))
					* !(zero->dist_p == 1)));
		string = str("0%*s%.*c", data->size - 2, "06", data->size - 1, '1');
		exec_string(data, string, 1);
		free_s(string);
		give_position(data);
	}
	if (zero->ab == 'A' && zero->down->num_i == 1)
		return (str("%.*c", abs(zero->dist), '5' + 3 * (zero->dist < 0)));
	return (NULL);
}

///////////////////////////////////////////////////////////////////////////////]
char	*smallest_str(int nb, ...)
{
	va_list	args;
	int		small;
	int		size;
	char	*smallest;
	char	*string;

	smallest = NULL;
	small = INT_MAX;
	va_start(args, nb);
	while (--nb >= 0)
	{
		string = va_arg(args, char *);
		size = len(string);
		if (size && (size < small))
		{
			if (smallest)
				free_s(smallest);
			small = size;
			smallest = string;
		}
		else
			free_s(string);
	}
	va_end(args);
	return (smallest);
}

////////////////////////////////////////////////////////////
// if in order 1 (0 1)
// if reverse order -1 (3 2)
// else 0
int	order(t_data *s, t_num *previous, t_num *next)
{
	int	size;

	size = next->num_i - previous->num_i;
	if (size == 1 || size == -s->size + 1)
		return (1);
	else if (size == -1 || size == s->size - 1)
		return (-1);
	else
		return (0);
}

//  #	fill num_dist_target
void	helper_num_dist_target(t_data *data, t_algo *a, t_num *num)
{
	t_num	*temp;

	(void)data;
	if ((num->position >> 31) == (a->tar->position >> 31))
	{
		a->ndt = -1;
		temp = num;
		while (++(a->ndt) < num->size_s && temp != a->tar)
			temp = *((t_num **)(temp) + (temp->ab == 'A'));
		a->ndtp = a->ndt;
		if (a->ndt > num->size_s / 2)
			a->ndt -= num->size_s;
		a->btbn = -1;
		temp = a->btar;
		while (++(a->btbn) < num->size_s && temp != a->bnum)
			temp = *((t_num **)(temp) + (temp->ab == 'A'));
	}
}

///////////////////////////////////////////////////////////////////////////////]
//  #   SET: bnum _ sbn  __ btar _ sbt
// pb with B:[21-22] > a->sbn == 0,1,0,1,0,1...
void	helper_block_size(t_data *data, t_algo *a)
{
	a->bnum = a->num;
	while (++a->sbn < a->bnum->size_s && order(data, *((t_num **)(a->bnum)
			+ (a->bnum->ab == 'B')), a->bnum))
		a->bnum = *((t_num **)(a->bnum) + (a->bnum->ab == 'B'));
	a->btar = a->tar;
	while (++a->sbt < a->btar->size_s && order(data, a->btar,
			*((t_num **)(a->btar) + (a->btar->ab == 'A'))) == 1)
		a->btar = *((t_num **)(a->btar) + (a->btar->ab == 'A'));
	if (order(data, *((t_num **)(a->btar) + (a->btar->ab == 'B')),
		a->btar) == -1)
	{
		a->sbt = 0;
		while (++a->sbt < a->btar->size_s && order(data,
				*((t_num **)(a->btar) + (a->btar->ab == 'B')), a->btar) == -1)
			a->btar = *((t_num **)(a->btar) + (a->btar->ab == 'B'));
		a->sbt *= -1;
	}
}
