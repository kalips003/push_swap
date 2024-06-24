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

int	sa(t_stacks *s, char sw);
int	sb(t_stacks *s, char sw);
int	ss(t_stacks *s, char sw);

///////////////////////////////////////////////////////////////////////////////]
//  Swap the first 2 elements of stack a. Do nothing if only one or no elements.
//  #   SWAP A
int	sa(t_stacks *s, char sw)
{
	if (sw)
		put(SA "\n");
	if (s->size_a < 2)
		return (1);
	s->top_a->above->below = s->top_a->below;
	s->top_a->below->above = s->top_a->above;
	s->top_a->above = s->top_a->below;
	s->top_a->below = s->top_a->below->below;
	s->top_a->above->below = s->top_a;
	s->top_a->below->above = s->top_a;
	s->top_a = s->top_a->above;
	return (1);
}

//  #   SWAP B
int	sb(t_stacks *s, char sw)
{
	if (sw)
		put(SB "\n");
	if (s->size_b < 2)
		return (1);
	s->top_b->above->below = s->top_b->below;
	s->top_b->below->above = s->top_b->above;
	s->top_b->above = s->top_b->below;
	s->top_b->below = s->top_b->below->below;
	s->top_b->above->below = s->top_b;
	s->top_b->below->above = s->top_b;
	s->top_b = s->top_b->above;
	return (1);
}

int	ss(t_stacks *s, char sw)
{
	if (sw)
		put(SS);
	sa(s, 0);
	sb(s, 0);
	return (1);
}
