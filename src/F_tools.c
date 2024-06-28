/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   F_tools.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:54:41 by kalipso           #+#    #+#             */
/*   Updated: 2024/06/28 13:54:41 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		wii_wrapper(char c);
int		exec_string(t_data *data, char *instructions, char sw2);
void	ini_cmd(t_data *data);

///////////////////////////////////////////////////////////////////////////////]
/*******************************************************************************
 * 		takes in "0123456789: \nabpsr"
 * 		[0-9x] -> [0-10]
 * 		[ \nabpsr] ->[-2... -7]
 * 		else -1
 *****************************************************************************/
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
int	exec_string(t_data *data, char *instructions, char sw2)
{
	int	i;
	int	b;

	i = -1;
	if (!instructions)
		return (0);
	while (instructions[++i])
	{
		b = wii_wrapper(instructions[i]);
		if (b >= 0)
			data->controls[b](data, sw2);
	}
	return (len(instructions));
}

///////////////////////////////////////////////////////////////////////////////]
void	ini_cmd(t_data *data)
{
	data->controls[0] = pb;
	data->controls[1] = pa;
	data->controls[2] = sa;
	data->controls[3] = sb;
	data->controls[4] = ss;
	data->controls[5] = ra;
	data->controls[6] = rb;
	data->controls[7] = rr;
	data->controls[8] = rra;
	data->controls[9] = rrb;
	data->controls[10] = rrr;
}
