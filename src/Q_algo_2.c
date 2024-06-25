/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Q_algo_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:08:35 by kalipso           #+#    #+#             */
/*   Updated: 2024/06/25 22:22:44 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		algo_2(t_data *data, int sw);
int		ft_algo_2(t_data *s, t_num *num);
void	helper_2(t_data *data, t_algo *a, t_num *num);
static t_num	*find_target(t_data *data, t_num *num);
static char	*sublim(t_data *data);
t_num	*assign_str_all_v2(t_data *data, int (*best_str_algo)(t_data*, t_num*));
int algo_ba_2(t_algo *a);

///////////////////////////////////////////////////////////////////////////////]
// push all but 2, then put bacck where it should be
int	algo_2(t_data *data, int sw)
{
	t_num	*small;
	int		size;

	char *first_string = str("%.*c", data->size_a - 2, '0');
	size = exec_string(data, first_string, sw);
	free_s(first_string);

	small = assign_str_all_v2(data, ft_algo_2);
	while (small && small->algo)
	{
		size += exec_string(data, small->algo, sw);
		small = assign_str_all_v2(data, ft_algo_2);
	}

	char	*last;
	last = sublim(data);
	size += exec_string(data, last, sw);
	free_s(last);
	put("OK? (%d), in %d moves\n", final_test(data), size);
	return (size);
}

t_num	*assign_str_all_v2(t_data *data, int (*best_str_algo)(t_data*, t_num*))
{
	int		i;
	int		smaller = 0;
	t_num	*temp;
	t_num	*small;

	small = NULL;
	free_algos(data);
	give_position(data);
	i = -1;
	temp = data->top_b;
	while (++i < data->size_b)
	{
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
int	ft_algo_2(t_data *s, t_num *num)
{
	t_algo a;

	helper_2(s, &a, num);
	return(algo_ba_2(&a));
}

///////////////////////////////////////////////////////////////////////////////]
//  #	initialize algori struct with num data
void	helper_2(t_data *data, t_algo *a, t_num *num)
{
	ft_memset(a, 0, sizeof(t_algo));
	a->num = num;
	a->target = find_target(data, num);
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

static t_num	*find_target(t_data *data, t_num *num)
{
	t_num *n;

	n = data->top_a;
	while (n->above->num_i < n->num_i)
		n = n->above;
	if (num->num_i > n->above->num_i)
		return (n);
	while (num->num_i > n->num_i)
		n = n->below;
	return (n);
}

///////////////////////////////////////////////////////////////////////////////]
static char	*sublim(t_data *data)
{
	t_num	*zero;

	zero = data->zero;
	give_position(data);
	if (zero->pile_c == 'B' && zero->above->num_i == 1)
		return (str("%.*c%.*c", abs(zero->dist + 1), '6' + 3 * (zero->dist < 0),
				data->full_size, '1'));
	if (zero->pile_c == 'B' && zero->below->num_i == 1)
		return (str("%.*c%*s", abs(zero->dist), '6' + 3 * (zero->dist < 0),
				data->full_size, "91"));
	if (zero->pile_c == 'A' && zero->above->num_i == 1)
		return (str("%*s%.*c%.*c", data->full_size, "80", abs(zero->dist + 1),
				'6' + 3 * (zero->dist < 0), data->full_size, '1'));
	if (zero->pile_c == 'A' && zero->below->num_i == 1)
		return (str("%.*c", abs(zero->dist), '5' + 3 * (zero->dist < 0)));
	return (NULL);
}


///////////////////////////////////////////////////////////////////////////////]
// (0) pb  (1) pa  (2) sa  (3) sb  (4) ss  (5) ra  (6) rb  (7) rr  (8) rra  (9) rrb (:) rrr
int algo_ba_2(t_algo *a)
{
	// str1 set
	lets_rrr(a, a->num, a->target, 0b00);
	a->num->algo = fjoin(2, 0b11, a->str1, str("1"));
	return (len(a->num->algo));
}