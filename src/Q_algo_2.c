/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Q_algo_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:08:35 by kalipso           #+#    #+#             */
/*   Updated: 2024/06/26 12:52:10 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int				algo_2(t_data *data, int sw);
t_num			*assign_str_b(t_data *data, int (*best_str_algo)(t_data*, t_num*));
int				ft_algo_2(t_data *s, t_num *num);
int				algo_ba_2(t_algo *a);
static t_num	*find_target(t_data *data, t_num *num);

///////////////////////////////////////////////////////////////////////////////]
// push all but 2, then put bacck where it should be
int	algo_2(t_data *data, int sw)
{
	t_num	*small;
	int		size;

	char *first_string = str("%.*c", data->size_a - 2, '0');
	size = exec_string(data, first_string, sw);
	free_s(first_string);

	small = assign_str_b(data, ft_algo_2);
	while (small && small->algo)
	{
		size += exec_string(data, small->algo, sw);
		small = assign_str_b(data, ft_algo_2);
	}

	char	*last;
	last = sublim(data);
	size += exec_string(data, last, sw);
	free_s(last);
	put("OK? (%d), in %d moves\n", final_test(data), size);
	return (size);
}

t_num	*assign_str_b(t_data *data, int (*best_str_algo)(t_data*, t_num*))
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
// 		the big if is to find the dist between hunter target
int	ft_algo_2(t_data *data, t_num *num)
{
	t_algo a;

	ft_memset(&a, 0, sizeof(t_algo));
	a.num = num;
	a.target = find_target(data, num);
	if ((num->position >> 31) == (a.target->position >> 31))
	{
		a.num_dist_target = -1;
		t_num *temp = num;
		while (++(a.num_dist_target) < num->size_s && temp != a.target)
			temp = *((t_num **)(temp) + (temp->pile_c == 'A'));
		a.num_d_tar_plus = a.num_dist_target;
		if (a.num_dist_target > num->size_s / 2)
			a.num_dist_target -= num->size_s;
		a.bt_dist_bn = -1;
		temp = a.blk_tar;
		while (++(a.bt_dist_bn) < num->size_s && temp != a.blk_num)
			temp = *((t_num **)(temp) + (temp->pile_c == 'A'));
	}
	return(algo_ba_2(&a));
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
// (0 pb)(1 pa)(2 sa)(3 sb)(4 ss)(5 ra)(6 rb)(7 rr)(8 rra)(9 rrb)(: rrr)
int algo_ba_2(t_algo *a)
{
	// str1 set
	lets_rrr(a, a->num, a->target, 0b00);
	a->num->algo = fjoin(2, 0b11, a->str1, str("1"));
	return (len(a->num->algo));
}