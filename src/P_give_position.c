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

void		give_position(t_stacks *s);
void		reevalue(t_stacks *s, t_entry *num);
static void	helper_962(t_entry *current);
static void	helper_give_posi(t_stacks *s, t_entry *current, char a, int i);

///////////////////////////////////////////////////////////////////////////////]
// 
static void	helper_give_blk(t_stacks *s, t_entry *num);
static void	helper_give_blk(t_stacks *s, t_entry *num)
{
	t_entry	*ptr;
	int		i;

	ptr = num;
	i = 0;
	while (--i > -num->size_s && ptr->target == ptr->above)
		ptr = ptr->above;
	if (i == -1 && i++)
	{
		ptr = num;
		while (++i < num->size_s && ptr->target == ptr->below)
			ptr = ptr->below;
	}
	// size blk toward target
	num->size_blk = i;
	if (i != 1)
		num->size_blk *= -1 + 2 * (num->pile_c == 'A');
	num->blk_end = ptr;
	// put("--->%d", num->size_blk);

	ptr = num;
	i = 0;
	while (--i > -num->size_s && ptr->hunter == ptr->below)
			ptr = ptr->below;
	if (i == -1 && i++)
	{
		ptr = num;
		while (++i < num->size_s && ptr->hunter == ptr->above)
			ptr = ptr->above;
	}
	// size blk toward hunter
	if (i != 1)
		num->size_blk += i * (-1 + 2 * (num->pile_c == 'A'));
	num->blk_start = ptr;
}

void	helper_give_blk_wrapper(t_stacks *s);
void	helper_give_blk_wrapper(t_stacks *s)
{
	int		i;
	t_entry	*ptr;

	i = -1;
	ptr = s->top_a;
	while (++i < s->full_size)
	{
		if (i == s->size_a)
			ptr = s->top_b;
		helper_give_blk(s, ptr);
		// put("(%d) %p: %d :%p\n", ptr->num_index, ptr->blk_start, ptr->size_blk, ptr->blk_end);
		ptr = ptr->below;
	}
}
///////////////////////////////////////////////////////////////////////////////]
//  #  give each member of A & B its position
// 		[0 size of A] [-1 -size of B] [dist from origin]
void	give_position(t_stacks *s)
{
	int i;
	t_entry *current;

	i = -1;
	current = s->top_a;
	while (++i < s->size_a)
	{
		helper_give_posi(s, current, 'A', i);
		current = current->below;
	}
	i = -1;
	current = s->top_b;
	while (++i < s->size_b)
	{
		helper_give_posi(s, current, 'B', i);
		current = current->below;
	}
	helper_give_blk_wrapper(s);
}

///////////////////////////////////////////////////////////////////////////////]
// reassignn value and char to num
void	reevalue(t_stacks *s, t_entry *num)
{
	int		i;
	t_entry	*current;

	i = -1;
	current = s->top_a->above;
	while (++i < s->size_a && current)
	{
		if (current == num)
			return (helper_give_posi(s, current, 'A', i));
		current = current->below;
	}
	i = -1;
	current = s->top_b->above;
	while (++i < s->size_b && current)
	{
		if (current == num)
			return (helper_give_posi(s, current, 'B', i));
		current = current->below;
	}
}

///////////////////////////////////////////////////////////////////////////////]
//  #  give one member of A & B its position
// 		[0 size of A] [-1 -size of B] [dist from origin]
static void	helper_give_posi(t_stacks *s, t_entry *current, char a, int i)
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
	current->pile_c = a;
	helper_962(current);
}

///////////////////////////////////////////////////////////////////////////////]
// #    fills in dist, dist_p, dist_n
static void	helper_962(t_entry *current)
{
	int	abs_posi;

	abs_posi = abs(current->position) - 1;
	if (current->pile_c == 'A')
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
