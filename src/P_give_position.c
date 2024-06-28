/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _give_position.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:43:28 by kalipso           #+#    #+#             */
/*   Updated: 2024/06/24 15:43:28 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		give_position(t_data *s);
static void	helper_962(t_num *current);
static void	helper_give_posi(t_data *s, t_num *current, char a, int i);

///////////////////////////////////////////////////////////////////////////////]
//  #  give each member of A & B its position
// 		[0 size of A] [-1 -size of B] [dist from origin]
void	give_position(t_data *s)
{
	int		i;
	t_num	*current;

	i = -1;
	current = s->top_a;
	while (++i < s->size_a)
	{
		helper_give_posi(s, current, 'A', i);
		current = current->down;
	}
	i = -1;
	current = s->top_b;
	while (++i < s->size_b)
	{
		helper_give_posi(s, current, 'B', i);
		current = current->down;
	}
}

///////////////////////////////////////////////////////////////////////////////]
//  #  give one member of A & B its position
// 		[0 size of A] [-1 -size of B] [dist from origin]
static void	helper_give_posi(t_data *s, t_num *current, char a, int i)
{
	if (a == 'A')
	{
		current->position = i;
		current->size_s = s->size_a;
	}
	else
	{
		current->position = -(i + 1);
		current->size_s = s->size_b;
	}
	current->ab = a;
	helper_962(current);
}

///////////////////////////////////////////////////////////////////////////////]
// #    fills in dist, dist_p, dist_n
static void	helper_962(t_num *current)
{
	int	abs_posi;

	abs_posi = abs(current->position) - 1;
	if (current->ab == 'A')
	{
		current->dist_p = current->position;
		current->dist_n = current->size_s - current->position;
	}
	else
	{
		current->dist_p = abs_posi;
		current->dist_n = current->size_s - abs_posi;
	}
	if (current->position > current->size_s / 2)
		current->dist = current->position - current->size_s;
	else if (current->position >= 0)
		current->dist = current->position;
	else if (current->position < 0 && abs_posi > current->size_s / 2)
		current->dist = abs_posi - current->size_s;
	else
		current->dist = abs_posi;
}
