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

void	function1(t_data *data, int i, int sw);
void	function2(t_data *data, int i, int sw);
void	function3(t_data *data, int sw);

///////////////////////////////////////////////////////////////////////////////]
/*
	function test [ -(nth number) ]
	Execute the best string from numbers in stack B
		(if an index is given, execute string for that number)
*/
void	function1(t_data *data, int i, int sw)
{
	t_num	*small;

	give_position(data);
	if (i > 0)
		small = data->top_a;
	else if (i < 0)
	{
		small = data->top_b;
		i = abs(i) - 1;
	}
	else
		small = assign_str_b(data);
	if (!small)
		return ((void)put(COLOR"Nothing to be done\n"RESET));
	while (--i >= 0)
		small = small->down;
	exec_string(data, small->algo, 0);
	print_header(data, 0b111, sw);
	put(COLOR"\n\t\e[4mLast executed string for:"RESET \
		COLOR" ["RESET"%d"COLOR"]\n\n"RESET"   %s", small->num_i * sw + \
		small->num * !sw, small->algo);
}

///////////////////////////////////////////////////////////////////////////////]
/*
	function test [ +(nth number) ]
	Print info for the nth number
		index 0 ... n for stack A
		index -1 ... -n for stack B
*/
void	function2(t_data *data, int i, int sw)
{
	t_num	*temp;
	t_algo	a;

	(void)sw;
	put("\n\t[F2] \e[4mPrint algo struct for num at posi: (%d)"RESET"\n\n", i);
	give_position(data);
	if (i >= 0)
		temp = data->top_a;
	else
	{
		temp = data->top_b;
		i = abs(i) - 1;
	}
	if (!temp)
		return ((void)put("Stack empty\n"));
	while (--i >= 0)
		temp = temp->down;
	put("(num: %d)[index: %d]\n", temp->num, temp->num_i);
	put("hunter=%d, target=%d\n\n\n", temp->hunter->num_i, temp->target->num_i);
	helper_1(data, &a, temp);
	print_stru_algo(&a);
}

///////////////////////////////////////////////////////////////////////////////]
/*
	function test [ . ]
	print strings for all numbers
*/
void	function3(t_data *data, int sw)
{
	t_num	*temp;
	t_num	*small;
	int		i;

	put(COLOR "\n\t\e[4mBest movement string for all numbers:"RESET"\n\n");
	small = assign_str_all(data);
	if (small)
		put(COLOR"Smallest string for ["RESET"%d"COLOR"]: "RESET"%s\n\n", small->num_i * sw + small->num * !sw, small->algo);
	i = -1;
	temp = data->top_a;
	while (++i < data->size)
	{
		if (i == data->size_a && put("\n"))
			temp = data->top_b;
		if (temp->ab == 'A')
			put(B_STACK_A C_STACK_A"[ % 3d ]"RESET" %s\n", temp->num_i * sw + temp->num * !sw, temp->algo);
		else
			put(B_STACK_B C_STACK_B"[ % 3d ]"RESET" %s\n", temp->num_i * sw + temp->num * !sw, temp->algo);
		temp = temp->down;
	}
}
