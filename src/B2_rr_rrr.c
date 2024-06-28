/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_rr_rrr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:42:52 by kalipso           #+#    #+#             */
/*   Updated: 2024/06/24 12:42:52 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	rr(t_data *s, char sw);
int	rra(t_data *s, char sw);
int	rrb(t_data *s, char sw);
int	rrr(t_data *s, char sw);

///////////////////////////////////////////////////////////////////////////////]
//  rr : ra and rb at the same time.
int	rr(t_data *s, char sw)
{
	if (sw)
		put(RR "\n");
	ra(s, 0);
	rb(s, 0);
	return (1);
}

///////////////////////////////////////////////////////////////////////////////]
//  Shift down all elements of stack a by 1. The last element becomes the first
//  #   REVERSE ROTATE A
int	rra(t_data *s, char sw)
{
	if (sw)
		put(RRA "\n");
	if (s->size_a < 2)
		return (1);
	s->top_a = s->top_a->up;
	return (1);
}

//  #   REVERSE ROTATE B
int	rrb(t_data *s, char sw)
{
	if (sw)
		put(RRB "\n");
	if (s->size_b < 2)
		return (1);
	s->top_b = s->top_b->up;
	return (1);
}

//  rrr : rra and rrb at the same time.
int	rrr(t_data *s, char sw)
{
	if (sw)
		put(RRR "\n");
	rra(s, 0);
	rrb(s, 0);
	return (1);
}
