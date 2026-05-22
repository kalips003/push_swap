/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Q_algo_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:08:35 by kalipso           #+#    #+#             */
/*   Updated: 2024/06/28 14:02:54 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int				algo_2(t_data *data, int sw);
t_num			*assign_str_b(t_data *data);
int				ft_algo_2(t_data *data, t_num *num);
static t_num	*find_target(t_data *data, t_num *num);
int				algo_ba_2(t_algo *a);

///////////////////////////////////////////////////////////////////////////////]
// push all but 2, then put bacck where it should be
int	algo_2(t_data *data, int sw)
{
	t_num	*small;
	int		size;
	char	*first_string;
	char	*last;

	first_string = str("%.*c", data->size_a - 2, '0');
	size = exec_string(data, first_string, sw);
	free_s(first_string);
	small = assign_str_b(data);
	while (small && small->algo)
	{
		size += exec_string(data, small->algo, sw);
		small = assign_str_b(data);
	}
	last = sublim(data);
	size += exec_string(data, last, sw);
	free_s(last);
	return (size);
}

t_num	*assign_str_b(t_data *data)
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
	temp = data->top_b;
	while (++i < data->size_b)
	{
		temp->algo_sz = ft_algo_2(data, temp);
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
// 		the big if is to find the dist between hunter target
int	ft_algo_2(t_data *data, t_num *num)
{
	t_algo	a;
	t_num	*temp;

	ft_memset(&a, 0, sizeof(t_algo));
	a.num = num;
	a.tar = find_target(data, num);
	if ((num->position >> 31) == (a.tar->position >> 31))
	{
		a.ndt = -1;
		temp = num;
		while (++(a.ndt) < num->size_s && temp != a.tar)
			temp = *((t_num **)(temp) + (temp->ab == 'A'));
		a.ndtp = a.ndt;
		if (a.ndt > num->size_s / 2)
			a.ndt -= num->size_s;
		a.btbn = -1;
		temp = a.btar;
		while (++(a.btbn) < num->size_s && temp != a.bnum)
			temp = *((t_num **)(temp) + (temp->ab == 'A'));
	}
	return (algo_ba_2(&a));
}

static t_num	*find_target(t_data *data, t_num *num)
{
	t_num	*n;

	n = data->top_a;
	while (n->up->num_i < n->num_i)
		n = n->up;
	if (num->num_i > n->up->num_i)
		return (n);
	while (num->num_i > n->num_i)
		n = n->down;
	return (n);
}

///////////////////////////////////////////////////////////////////////////////]
// (0 pb)(1 pa)(2 sa)(3 sb)(4 ss)(5 ra)(6 rb)(7 rr)(8 rra)(9 rrb)(: rrr)
int	algo_ba_2(t_algo *a)
{
	lets_rrr(a, a->num, a->tar, 0b00);
	a->num->algo = fjoin(2, 0b11, a->s1, str("1"));
	return (len(a->num->algo));
}
