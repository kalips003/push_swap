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

static void	assign_blk(t_stacks *stacks);
void	ini_cmd(t_stacks *stacks);

///////////////////////////////////////////////////////////////////////////////]
static void	assign_blk(t_stacks *stacks)
{
	
}

void	ini_cmd(t_stacks *stacks)
{
	stacks->controls[0] = pb;
	stacks->controls[1] = pa;
	stacks->controls[2] = sa;
	stacks->controls[3] = sb;
	stacks->controls[4] = ss;
	stacks->controls[5] = ra;
	stacks->controls[6] = rb;
	stacks->controls[7] = rr;
	stacks->controls[8] = rra;
	stacks->controls[9] = rrb;
	stacks->controls[10] = rrr;
}