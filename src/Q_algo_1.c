/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Q_algo_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:08:35 by kalipso           #+#    #+#             */
/*   Updated: 2024/06/25 19:05:10 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		algo_1(t_data *data, int sw);
int		ft_algo_1(t_data *s, t_num *num);
void	helper_1(t_data *data, t_algo *a, t_num *num);
static char	*sublim(t_data *data);

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
//		give best string to 1 number
//		return the len of the best string
int	ft_algo_1(t_data *s, t_num *num)
{
	t_algo a;

	helper_1(s, &a, num);
	int bit = (a.num->pile_c == 'A') << 1 | (a.target->pile_c == 'A');
	// if  (num->dist == 1 && a.sizeb_n == -1) -> 'sa'
	if (a.num_dist_target == 1 || a.num_dist_target == -1)
		return (0);
	if (is_in_order(s, num, *((t_num **)(num) + (num->pile_c == 'A'))) == -1)
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