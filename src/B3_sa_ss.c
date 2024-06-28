/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_sa_ss.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:43:59 by kalipso           #+#    #+#             */
/*   Updated: 2024/06/24 12:43:59 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	sa(t_data *s, char sw);
int	sb(t_data *s, char sw);
int	ss(t_data *s, char sw);

///////////////////////////////////////////////////////////////////////////////]
//  Swap the first 2 elements of stack a. Do nothing if only one or no elements.
//  #   SWAP A
int	sa(t_data *s, char sw)
{
	if (sw)
		put(SA "\n");
	if (s->size_a < 2)
		return (1);
	s->top_a->up->down = s->top_a->down;
	s->top_a->down->up = s->top_a->up;
	s->top_a->up = s->top_a->down;
	s->top_a->down = s->top_a->down->down;
	s->top_a->up->down = s->top_a;
	s->top_a->down->up = s->top_a;
	s->top_a = s->top_a->up;
	return (1);
}

//  #   SWAP B
int	sb(t_data *s, char sw)
{
	if (sw)
		put(SB "\n");
	if (s->size_b < 2)
		return (1);
	s->top_b->up->down = s->top_b->down;
	s->top_b->down->up = s->top_b->up;
	s->top_b->up = s->top_b->down;
	s->top_b->down = s->top_b->down->down;
	s->top_b->up->down = s->top_b;
	s->top_b->down->up = s->top_b;
	s->top_b = s->top_b->up;
	return (1);
}

int	ss(t_data *s, char sw)
{
	if (sw)
		put(SS);
	sa(s, 0);
	sb(s, 0);
	return (1);
}
