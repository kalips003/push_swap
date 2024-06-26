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

t_num	*assign_str_all(t_data *data, int (*best_str_algo)(t_data*, t_num*));

char	*sublim(t_data *data);
char	*smallest_str(int nb, ...);
int		is_in_order(t_data *s, t_num *previous, t_num *next);

// (0 pb)(1 pa)(2 sa)(3 sb)(4 ss)(5 ra)(6 rb)(7 rr)(8 rra)(9 rrb)(: rrr)





///////////////////////////////////////////////////////////////////////////////]
// once everything is in order, puts index 0 on top of A
char	*sublim(t_data *data)
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
int	is_in_order(t_data *s, t_num *previous, t_num *next)
{
	int	size;

	size = next->num_i - previous->num_i;
	if (size == 1 || size == -s->full_size + 1)
		return (1);
	else if (size == -1 || size == s->full_size - 1)
		return (-1);
	else
		return (0);
}

//  ! un seul block restant (of size 2!) dans B > NULL string?
//  if NUm end of negative blk? [(3) 2 1 0] ..........?
