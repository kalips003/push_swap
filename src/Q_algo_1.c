/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Q_algo_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:08:35 by kalipso           #+#    #+#             */
/*   Updated: 2024/06/26 12:59:47 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		algo_1(t_data *data, int sw);
t_num	*assign_str_all(t_data *data, int (*best_str_algo)(t_data*, t_num*));
int		ft_algo_1(t_data *s, t_num *num);
void	helper_1(t_data *data, t_algo *a, t_num *num);
void	helper_block_size(t_data *data, t_algo *a);;

///////////////////////////////////////////////////////////////////////////////]
// simplest algo
int	algo_1(t_data *data, int sw)
{
	t_num	*small;
	int		size;
	char	*last;

	small = assign_str_all(data, ft_algo_1);
	size = 0;
	while (small && small->algo)
	{
		size += exec_string(data, small->algo, sw);
		small = assign_str_all(data, ft_algo_1);
	}
	last = sublim(data);
	size += len(last);
	exec_string(data, last, sw);
	free_s(last);
	return (size);
}

///////////////////////////////////////////////////////////////////////////////]
// (0 pb)(1 pa)(2 sa)(3 sb)(4 ss)(5 ra)(6 rb)(7 rr)(8 rra)(9 rrb)(: rrr)
//		give str to all nuber based on best_str_algo0
// 		return the number with smallest string
t_num	*assign_str_all(t_data *data, int (*best_str_algo)(t_data*, t_num*))
{
	int		i;
	int		smaller = 0;
	t_num	*temp;
	t_num	*small;

	small = NULL;
	free_algos(data);
	give_position(data);
	i = -1;
	temp = data->top_a;
	while (++i < data->full_size)
	{
		if (i == data->size_a)
			temp = data->top_b;
		temp->algo_sz = best_str_algo(data, temp);
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
int	ft_algo_1(t_data *s, t_num *num)
{
	t_algo a;

	helper_1(s, &a, num);
	int bit = (a.num->pile_c == 'A') << 1 | (a.target->pile_c == 'A');
	if (a.num_dist_target == 1 || a.num_dist_target == -1)
		return (0);
	if (is_in_order(s, num, *((t_num **)(num) + (num->pile_c == 'A'))) == -1)
		return (0);
	if (bit == 0)
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
//  #	initialize algori struct with num data
void	helper_1(t_data *data, t_algo *a, t_num *num)
{
	ft_memset(a, 0, sizeof(t_algo));
	a->num = num;
	a->target = num->target;
//  blocks handling
	helper_block_size(data, a);
//  num_dist_target
	if ((num->position >> 31) == (a->target->position >> 31))
	{
		a->num_dist_target = -1;
		t_num *temp = num;
		while (++(a->num_dist_target) < num->size_s && temp != a->target)
			temp = *((t_num **)(temp) + (temp->pile_c == 'A'));
		a->num_d_tar_plus = a->num_dist_target;
		if (a->num_dist_target > num->size_s / 2)
			a->num_dist_target -= num->size_s;
		a->bt_dist_bn = -1;
		temp = a->blk_tar;
		while (++(a->bt_dist_bn) < num->size_s && temp != a->blk_num)
			temp = *((t_num **)(temp) + (temp->pile_c == 'A'));
	}
}

///////////////////////////////////////////////////////////////////////////////]
//  #   SET: blk_num _ sizeb_n  __ blk_tar _ sizeb_t
// pb with B:[21-22] > a->sizeb_n == 0,1,0,1,0,1...
void	helper_block_size(t_data *data, t_algo *a)
{
	a->blk_num = a->num;
	while (++a->sizeb_n < a->blk_num->size_s && is_in_order(data, *((t_num **)(a->blk_num) + (a->blk_num->pile_c == 'B')), a->blk_num))
		a->blk_num = *((t_num **)(a->blk_num) + (a->blk_num->pile_c == 'B'));
	a->blk_tar = a->target;
	while (++a->sizeb_t < a->blk_tar->size_s && is_in_order(data, a->blk_tar, *((t_num **)(a->blk_tar) + (a->blk_tar->pile_c == 'A'))) == 1)
		a->blk_tar = *((t_num **)(a->blk_tar) + (a->blk_tar->pile_c == 'A'));
	if (is_in_order(data, *((t_num **)(a->blk_tar) + (a->blk_tar->pile_c == 'B')), a->blk_tar) == -1)
	{
		a->sizeb_t = 0;
		while (++a->sizeb_t < a->blk_tar->size_s && is_in_order(data, *((t_num **)(a->blk_tar) + (a->blk_tar->pile_c == 'B')), a->blk_tar) == -1)
			a->blk_tar = *((t_num **)(a->blk_tar) + (a->blk_tar->pile_c == 'B'));
		a->sizeb_t *= -1;
	}
}