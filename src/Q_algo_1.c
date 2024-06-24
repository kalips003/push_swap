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

t_entry	*assign_str_all(t_stacks *stacks);
int		assign_str(t_stacks *s, t_entry *num);
void	fill_stru_algo(t_stacks *stacks, t_algo *a, t_entry *num);
static void	helper_block_size(t_stacks *stacks, t_algo *a);
char	*smallest_str(int nb, ...);
int		is_in_order(t_stacks *s, t_entry *previous, t_entry *next);

///////////////////////////////////////////////////////////////////////////////]
// (0) pb  (1) pa  (2) sa  (3) sb  (4) ss  (5) ra  (6) rb  (7) rr  (8) rra  (9) rrb (:) rrr
t_entry	*assign_str_all(t_stacks *stacks)
{
	int		i;
	int		smaller = 0;
	t_entry	*temp;
	t_entry	*small;

	small = NULL;
	free_algos(stacks);
	give_position(stacks);
	i = -1;
	temp = stacks->top_a;
	while (++i < stacks->full_size)
	{
		if (i == stacks->size_a)
			temp = stacks->top_b;
		temp->algo_sz = assign_str(stacks, temp);
		if (temp->algo_sz && (smaller == 0 || temp->algo_sz < smaller))
		{
			smaller = temp->algo_sz;
			small = temp;
		}
		temp = temp->below;
	}
	return (small);
}

///////////////////////////////////////////////////////////////////////////////]
//		give best string to 1 number
//		return the len of the best string
int	assign_str(t_stacks *s, t_entry *num)
{
	t_algo a;

	fill_stru_algo(s, &a, num);
	int bit = (a.num->pile_c == 'A') << 1 | (a.target->pile_c == 'A');
	// if  (num->dist == 1 && a.sizeb_n == -1) -> 'sa'
	if (a.num_dist_target == 1 || a.num_dist_target == -1)
		return (0);
	if (is_in_order(s, num, *((t_entry **)(num) + (num->pile_c == 'A'))) == -1)
		return (0);
	if (bit == 0)// num top stack, swap !! 7-10-8-11 > 10-7-8-11
		return(algo_bb(&a));
	else if (bit == 1)
		return(algo_ba(&a));
	else if (bit == 2)
		return(algo_ab(&a));
	else
		return(algo_aa(&a));
	return (0);
}

///////////////////////////////////////////////////////////////////////////////]
//  #	initialize algori struct
void	fill_stru_algo(t_stacks *stacks, t_algo *a, t_entry *num)
{
	ft_memset(a, 0, sizeof(t_algo));
	a->num = num;
	a->target = num->target;
//  blocks handling
	helper_block_size(stacks, a);
//  num_dist_target
	if ((num->position >> 31) == (a->target->position >> 31))
	{
		a->num_dist_target = -1;
		t_entry *temp = num;
		while (++(a->num_dist_target) < num->size_s && temp != a->target)
			temp = *((t_entry **)(temp) + (temp->pile_c == 'A'));
		a->num_d_tar_plus = a->num_dist_target;
		if (a->num_dist_target > num->size_s / 2)
			a->num_dist_target -= num->size_s;
		a->bt_dist_bn = -1;
		temp = a->blk_tar;
		while (++(a->bt_dist_bn) < num->size_s && temp != a->blk_num)
			temp = *((t_entry **)(temp) + (temp->pile_c == 'A'));
	}
}

//  #   SET: blk_num _ sizeb_n  __ blk_tar _ sizeb_t
// pb with B:[21-22] > a->sizeb_n == 0,1,0,1,0,1...
static void	helper_block_size(t_stacks *stacks, t_algo *a)
{
	a->blk_num = a->num;
	while (++a->sizeb_n < a->blk_num->size_s && is_in_order(stacks, *((t_entry **)(a->blk_num) + (a->blk_num->pile_c == 'B')), a->blk_num))
		a->blk_num = *((t_entry **)(a->blk_num) + (a->blk_num->pile_c == 'B'));
	a->blk_tar = a->target;
	while (++a->sizeb_t < a->blk_tar->size_s && is_in_order(stacks, a->blk_tar, *((t_entry **)(a->blk_tar) + (a->blk_tar->pile_c == 'A'))) == 1)
		a->blk_tar = *((t_entry **)(a->blk_tar) + (a->blk_tar->pile_c == 'A'));
	if (is_in_order(stacks, *((t_entry **)(a->blk_tar) + (a->blk_tar->pile_c == 'B')), a->blk_tar) == -1)
	{
		a->sizeb_t = 0;
		while (++a->sizeb_t < a->blk_tar->size_s && is_in_order(stacks, *((t_entry **)(a->blk_tar) + (a->blk_tar->pile_c == 'B')), a->blk_tar) == -1)
			a->blk_tar = *((t_entry **)(a->blk_tar) + (a->blk_tar->pile_c == 'B'));
		a->sizeb_t *= -1;
	}
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
int	is_in_order(t_stacks *s, t_entry *previous, t_entry *next)
{
	int	size;

	size = next->num_index - previous->num_index;
	if (size == 1 || size == -s->full_size + 1)
		return (1);
	else if (size == -1 || size == s->full_size - 1)
		return (-1);
	else
		return (0);
}

//  ! un seul block restant (of size 2!) dans B > NULL string?
//  if NUm end of negative blk? [(3) 2 1 0] ..........?
