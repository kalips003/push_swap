/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Q_algo_0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:08:35 by kalipso           #+#    #+#             */
/*   Updated: 2024/06/25 16:00:16 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int			algo_1(t_data *data, int sw);
static char	*sublim(t_data *data);

///////////////////////////////////////////////////////////////////////////////]
// simplest algo
int	algo_1(t_data *data, int sw)
{
	t_num	*small;
	int		size;
	char	*last;

	ft_break(data->top_a->num, "just enter algo_1", 2, data->top_a);
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
static char	*sublim(t_data *data)
{
	t_num	*zero;

	zero = data->zero;
	give_position(data);
	if (zero->pile_c == 'B' && zero->above->num_index == 1)
		return (str("%.*c%.*c", abs(zero->dist + 1), '6' + 3 * (zero->dist < 0),
				data->full_size, '1'));
	if (zero->pile_c == 'B' && zero->below->num_index == 1)
		return (str("%.*c%*s", abs(zero->dist), '6' + 3 * (zero->dist < 0),
				data->full_size, "91"));
	if (zero->pile_c == 'A' && zero->above->num_index == 1)
		return (str("%*s%.*c%.*c", data->full_size, "80", abs(zero->dist + 1),
				'6' + 3 * (zero->dist < 0), data->full_size, '1'));
	if (zero->pile_c == 'A' && zero->below->num_index == 1)
		return (str("%.*c", abs(zero->dist), '5' + 3 * (zero->dist < 0)));
	return (NULL);
}