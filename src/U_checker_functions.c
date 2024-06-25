/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   U_checker_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 03:08:25 by kalipso           #+#    #+#             */
/*   Updated: 2024/06/25 03:08:25 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	function1(t_stacks *stacks, int i);
void	function2(t_stacks *stacks, int i);
void	function3(t_stacks *stacks);

///////////////////////////////////////////////////////////////////////////////]
//  function 1 to test [ - ]
void	function1(t_stacks *stacks, int i)
{
	t_entry *small;

	small = assign_str_all(stacks);
	if (!small)
		return ;
	if (!i)
		exec_string(stacks, small->algo, 0);
	else
		put("%s\n", small->algo);
	print_header(stacks, 0b111, 1);
	put("\t(%d) %s\n", small->num_index, small->algo);
}
///////////////////////////////////////////////////////////////////////////////]
//  function 2 to test [ + ]
void	function2(t_stacks *stacks, int i)
{
	t_entry *temp;
	int j = i;

	give_position(stacks);
	if (i >= 0)
		temp = stacks->top_a;
	else
	{
		temp = stacks->top_b;
		j = abs(i) - 1;
	}
	while (--j >= 0)
		temp = temp->below;
	t_algo algo;
	fill_stru_algo(stacks, &algo, temp);
	print_stru_algo(&algo);
}
///////////////////////////////////////////////////////////////////////////////]
//  function 3 to test [ . ]
void	function3(t_stacks *stacks)
{
	t_entry *temp;
	int i;
	t_entry *small = assign_str_all(stacks);
	print_header(stacks, 0b111, 1);
	if (small && small->algo)
		put("%s\n", small->algo);
	i = -1;
	temp = stacks->top_a;
	while (++i < stacks->full_size)
	{
		if (i == stacks->size_a)
			temp = stacks->top_b;
		put("%c) -%d- = %s\n", temp->pile_c, temp->num_index, temp->algo);
		temp = temp->below;
	}
}
