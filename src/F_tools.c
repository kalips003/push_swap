/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_tools.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 00:48:21 by kalipso           #+#    #+#             */
/*   Updated: 2024/06/25 00:48:21 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		wii_wrapper(char c);
int		exec_string(t_stacks *stacks, char *instructions, char sw2);
///////////////////////////////////////////////////////////////////////////////]
/*******************************************************************************
 * 		takes in "0123456789: \nabpsr"
 * 		[0-9x] -> [0-10]
 * 		[ \nabpsr] ->[-2... -7]
 * 		else -1
 *******************************************************************************/
int	wii_wrapper(char c)
{
	int	i;

	if (c == 'A')
		return (0);
	if (c == 'B')
		return (1);
	i = wii(c, "0123456789: \nabpsr");
	if (i < 11)
		return (i);
	return (9 - i);
}

///////////////////////////////////////////////////////////////////////////////]
//	#	takes in "0123456789a11", and do it, instructions can be NULL
//  if sw2: print instructions beeing executed
int	exec_string(t_stacks *stacks, char *instructions, char sw2)
{
	int i = -1;
	int b;

	if (!instructions)
		return (0);
	while (instructions[++i])
	{
		b = wii_wrapper(instructions[i]);
		if (b >= 0)
			stacks->controls[b](stacks, sw2);
	}
	return (len(instructions));
}

