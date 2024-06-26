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
//  function 1 to test [ - ]
void	function1(t_data *data, int i, int sw)
{
	t_num *small;

	give_position(data);
	if (i > 0)
		small = data->top_a;
	else if (i < 0)
	{
		small = data->top_b;
		i = abs(i) - 1;
	}
	else
		small = assign_str_b(data, ft_algo_2);
	if (!small)
		return ((void)put("Nothing to be done\n"));
	while (--i >= 0)
		small = small->below;
	exec_string(data, small->algo, 0);
	print_header(data, 0b111, sw);
	put("\n\t[F1] \e[4mExecuting the best string, or your choice"RESET"\n\n");
	put("Hunter = (n: %d)[i: %d]\n", small->num, small->num_i);
	put("Last cmd:\n\t%s\n\n", small->algo);
}
///////////////////////////////////////////////////////////////////////////////]
//  function 2 to test [ + ]
void	function2(t_data *data, int i, int sw)
{
	int	a;

	put("\n\t[F3] \e[4mExecute algo 1"RESET"\n\n");
	a = algo_2(data, 1);
	put("how many moves: %d\n", a);
	print_header(data, 0b010, sw);
}
// void	function2(t_data *data, int i, int sw)
// {
// 	t_num *temp;
// 	t_algo algo;

// 	put("\n\t[F2] \e[4mPrint algo struct for number at position (%d)"RESET"\n\n", i);
// 	give_position(data);
// 	if (i >= 0)
// 		temp = data->top_a;
// 	else
// 	{
// 		temp = data->top_b;
// 		i = abs(i) - 1;
// 	}
// 	if (!temp)
// 		return ((void)put("Stack empty\n"));
// 	while (--i >= 0)
// 		temp = temp->below;
// 	put("(num: %d)[index: %d]\n\n\n", temp->num, temp->num_i);
// 	helper_2(data, &algo, temp);
// 	print_stru_algo(&algo);
// }
///////////////////////////////////////////////////////////////////////////////]
//  function 3 to test [ . ]
// void	function3(t_data *data, int sw)
// {
// 	t_num *temp;
// 	t_num *small;
// 	int i;
	
// 	put("\n\t[F3] \e[4mPrint the best string for all numbers"RESET"\n\n");
// 	// put("\n\t[F3] \e[4mPrint block data for all numbers"RESET"\n\n");
// 	small = assign_str_b(data, ft_algo_2);
// 	// put("---------->%p\n", small);
// 	if (small)
// 		put("Smallest string[%d] (%c %d): %s\n\n", small->position, small->pile_c, small->num_i, small->algo);
// 	else
// 		put("No string: (%p)\n\n", small);
// 	i = -1;
// 	temp = data->top_a;
// 	while (++i < data->full_size)
// 	{
// 		if (i == data->size_a && put("\n"))
// 			temp = data->top_b;
// 		put("%c) -%d- = %s\n", temp->pile_c, temp->num_i, temp->algo);
// 		// put("num=%d; size_blk=%d; blk_start=%d; blk_end=%d\n", temp->num, temp->size_blk, temp->blk_start->num, temp->blk_end->num);
// 		temp = temp->below;
// 	}
// }
void	function3(t_data *data, int sw)
{
	int	a;

	put("\n\t[F3] \e[4mExecute algo 1"RESET"\n\n");
	a = algo_2(data, 1);
	put("how many moves: %d\n", a);
	print_header(data, 0b010, sw);
}