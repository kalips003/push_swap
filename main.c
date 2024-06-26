/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:51:31 by kalipso           #+#    #+#             */
/*   Updated: 2024/06/28 14:43:30 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

///////////////////////////////////////////////////////////////////////////////]
/* * * * * * * * * * * * * * * * * * * * * * * * * * *
░█████╗░  ███████╗░█████╗░██╗██████╗░███████╗
██╔══██╗  ██╔════╝██╔══██╗██║██╔══██╗██╔════╝
███████║  █████╗░░███████║██║██████╔╝█████╗░░
██╔══██║  ██╔══╝░░██╔══██║██║██╔══██╗██╔══╝░░
██║░░██║  ██║░░░░░██║░░██║██║██║░░██║███████╗
╚═╝░░╚═╝  ╚═╝░░░░░╚═╝░░╚═╝╚═╝╚═╝░░╚═╝╚══════╝


* * * * * * * * * * * * * * * * * * * * * * * * * * * */
///////////////////////////////////////////////////////////////////////////////]
int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 2)
		return (put(MSG_NONUM "try 'make n' then 'make m'\n"), 0);
	ini_stacks(ac, av, &data);
	if (final_test(&data))
		end(&data, NULL, 0);
	if (data.size <= 15)
		algo_1(&data, 1);
	else
		algo_2(&data, 1);
	end(&data, NULL, !(final_test(&data)));
	return (0);
}

///////////////////////////////////////////////////////////////////////////////]
/*******************************************************************************
░█████╗░██████╗░░█████╗░██╗░░██╗██╗██╗░░░██╗███████╗░██████╗
██╔══██╗██╔══██╗██╔══██╗██║░░██║██║██║░░░██║██╔════╝██╔════╝
███████║██████╔╝██║░░╚═╝███████║██║╚██╗░██╔╝█████╗░░╚█████╗░
██╔══██║██╔══██╗██║░░██╗██╔══██║██║░╚████╔╝░██╔══╝░░░╚═══██╗
██║░░██║██║░░██║╚█████╔╝██║░░██║██║░░╚██╔╝░░███████╗██████╔╝
╚═╝░░╚═╝╚═╝░░╚═╝░╚════╝░╚═╝░░╚═╝╚═╝░░░╚═╝░░░╚══════╝╚═════╝░

*******************************************************************************/