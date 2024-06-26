/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_pa_pb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:42:19 by kalipso           #+#    #+#             */
/*   Updated: 2024/06/24 12:42:19 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int			pb(t_data *s, char sw);
int			pa(t_data *s, char sw);
int			ra(t_data *s, char sw);
int			rb(t_data *s, char sw);
static void	push_helper(t_num **push_to, t_num **push_from, int size);

///////////////////////////////////////////////////////////////////////////////]
//  Push the first element at the top of a and put it at the top of b.
//  Do nothing if a is empty.
//  #   PUSH B
int	pb(t_data *s, char sw)
{
	if (sw)
		put(PB "\n");
	if (s->size_a == 0)
		return (0);
	s->top_a->up->down = s->top_a->down;
	s->top_a->down->up = s->top_a->up;
	push_helper(&s->top_b, &s->top_a, s->size_b);
	if (s->size_a == 1)
		s->top_a = NULL;
	s->size_a--;
	s->size_b++;
	return (1);
}

//  #   PUSH A
int	pa(t_data *s, char sw)
{
	if (sw)
		put(PA "\n");
	if (s->size_b == 0)
		return (0);
	s->top_b->up->down = s->top_b->down;
	s->top_b->down->up = s->top_b->up;
	push_helper(&s->top_a, &s->top_b, s->size_a);
	if (s->size_b == 1)
		s->top_b = NULL;
	s->size_b--;
	s->size_a++;
	return (1);
}

///////////////////////////////////////////////////////////////////////////////]
//  Shift up all elements of stack a by 1. The first element becomes the last
//  #   ROTATE A
int	ra(t_data *s, char sw)
{
	if (sw)
		put(RA "\n");
	if (s->size_a < 2)
		return (1);
	s->top_a = s->top_a->down;
	return (1);
}

//  #   ROTATE B
int	rb(t_data *s, char sw)
{
	if (sw)
		put(RB "\n");
	if (s->size_b < 2)
		return (1);
	s->top_b = s->top_b->down;
	return (1);
}

///////////////////////////////////////////////////////////////////////////////]
static void	push_helper(t_num **push_to, t_num **push_from, int size)
{
	if (size)
	{
		(*push_from)->up = (*push_to)->up;
		(*push_to)->up->down = (*push_from);
		(*push_to)->up = (*push_from);
		(*push_from) = (*push_from)->down;
		(*push_to)->up->down = (*push_to);
		(*push_to) = (*push_to)->up;
	}
	else
	{
		(*push_to) = (*push_from);
		(*push_from) = (*push_from)->down;
		(*push_to)->up = (*push_to);
		(*push_to)->down = (*push_to);
	}
}
