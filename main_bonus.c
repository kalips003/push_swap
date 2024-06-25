/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:07:11 by kalipso           #+#    #+#             */
/*   Updated: 2024/06/25 18:19:31 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

////////////////////////////////////////////////////////////
int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 2)
		return (put(MSG_NONUM), 0);
	ini_stacks(ac, av, &data);
	print_header(&data, 0b111, 0);
	tester(&data);
	if (!final_test(&data))
		end(&data, MSG_KO, 0);
	end(&data, MSG_OK, 0);
	return (0);
}
////////////////////////////////////////////////////////////
