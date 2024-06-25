/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_struct_ini.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:34:23 by kalipso           #+#    #+#             */
/*   Updated: 2024/06/24 12:34:23 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ini_cmd(t_data *data);

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
