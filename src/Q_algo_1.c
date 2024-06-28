/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Q_algo_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:08:35 by kalipso           #+#    #+#             */
/*   Updated: 2024/06/28 14:17:56 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		algo_1(t_data *data, int sw);
t_num	*assign_str_all(t_data *data);
int		ft_algo_1(t_data *s, t_num *num);
void	helper_1(t_data *data, t_algo *a, t_num *num);

///////////////////////////////////////////////////////////////////////////////]
// simplest algo
int	algo_1(t_data *data, int sw)
{
	t_num	*small;
	int		size;
	char	*last;

	small = assign_str_all(data);
	size = 0;
	while (small && small->algo)
	{
		size += exec_string(data, small->algo, sw);
		small = assign_str_all(data);
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
t_num	*assign_str_all(t_data *data)
{
	int		i;
	int		smaller;
	t_num	*temp;
	t_num	*small;

	small = NULL;
	smaller = 0;
	free_algos(data);
	give_position(data);
	i = -1;
	temp = data->top_a;
	while (++i < data->size)
	{
		if (i == data->size_a)
			temp = data->top_b;
		temp->algo_sz = ft_algo_1(data, temp);
		if (temp->algo_sz && (smaller == 0 || temp->algo_sz < smaller))
		{
			smaller = temp->algo_sz;
			small = temp;
		}
		temp = temp->down;
	}
	return (small);
}

///////////////////////////////////////////////////////////////////////////////]
//		give best string to 1 number
//		return the len of the best string
int	ft_algo_1(t_data *s, t_num *num)
{
	t_algo	a;
	int		bit;

	helper_1(s, &a, num);
	bit = (a.num->ab == 'A') << 1 | (a.tar->ab == 'A');
	if (a.ndt == 1)
		return (0);
	if (order(s, num, num->down) == -1 && order(s, num->up, num) == -1)
		return (0);
	if (bit == 0)
		return (algo_bb(&a));
	else if (bit == 1)
		return (algo_ba(&a));
	else if (bit == 2)
		return (algo_ab(&a));
	else
		return (algo_aa(&a));
	return (0);
}

///////////////////////////////////////////////////////////////////////////////]
//  #	initialize algori struct with num data
void	helper_1(t_data *data, t_algo *a, t_num *num)
{
	ft_memset(a, 0, sizeof(t_algo));
	a->num = num;
	a->tar = num->target;
	helper_block_size(data, a);
	helper_num_dist_target(data, a, num);
}
