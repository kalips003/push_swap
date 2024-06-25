/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:51:31 by kalipso           #+#    #+#             */
/*   Updated: 2024/06/25 15:58:20 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

///////////////////////////////////////////////////////////////////////////////]
int main(int ac, char **av)
{
	t_data	data;

	if (ac < 2)
		return (put(MSG_NONUM));
	ini_stacks(ac, av, &data);
	ft_break(data.top_a->num, "just exit ini_stacks", 2, data.top_a);
	algo_1(&data, 1);
	end(&data, NULL, 0);
	return (0);
}
