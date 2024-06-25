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

void			ini_stacks(int ac, char **av, t_data *data);
static t_num	*create_stack_a(int ac, char **av, t_data *data, int j);
static t_num	*create_new_node(t_num *last_node, char *arg, t_data *s);
static void		assign_value(t_data *data);
static void		assign_target(t_data *data);

///////////////////////////////////////////////////////////////////////////////]
//  #  CREATE THE FULL data STRUCT
void	ini_stacks(int ac, char **av, t_data *data)
{
	ft_memset(data, 0, sizeof(t_data));
	ini_cmd(data);
	data->full_size = ac - 1;
	data->size_a = data->full_size;
	// ini instru struct
	if (ac == 2)
	{
		data->args = split(av[1], " ");
		if (!data->args)
			end(data, MSG_MALLOC, 1);
		data->full_size = tab_size(data->args);
		data->size_a = data->full_size;
		data->top_a = create_stack_a(data->full_size + 1, data->args, data, 1);
		return ;
	}
	data->top_a = create_stack_a(data->full_size + 1, av, data, 0);
}

///////////////////////////////////////////////////////////////////////////////]
//  #   CREATE THE FULL 'A' STACK WITH NUMBER, CHECK ERRORS, RETURN POINTER TO TOP OF A
static t_num	*create_stack_a(int ac, char **av, t_data *data, int j)
{
	int		i;
	t_num	*a_end;

	a_end = NULL;
	i = 0;
	while (++i < ac)
	{
		a_end = create_new_node(a_end, av[i - j], data);
		ft_break(10000 * i + a_end->num, "in create_stack_a loop", 2, a_end);
		if (i == 1)
			data->top_a = a_end;
	}
	assign_value(data);
	assign_target(data);
	data->top_a->above = a_end;
	a_end->below = data->top_a;
	ft_break(data->top_a->num, "after finishing A: adrss of top of a", 2, data->top_a);
	return (data->top_a);
}

///////////////////////////////////////////////////////////////////////////////]
//  #   CREATE NEW NUMBER NODE,  ATTACH IT TO LAST_NODE
//  PUT THE NUMBER IN, CHECK IF VALABLE    //(char *"arg")
//  exit_code -5: number too big
//  exit_code -4: not a number
static t_num	*create_new_node(t_num *last_node, char *arg, t_data *s)
{
	t_num	*new_node;
	int		error;

	new_node = (t_num *)mem(0, sizeof(t_num));
	if (!new_node)
		end(s, MSG_MALLOC, 1);
	new_node->algo = NULL;
	new_node->above = last_node;
	error = 0;
	new_node->num = ft_atoi(arg, &error);
	if (error == -2)
		(free_s(new_node), end(s, MSG_TOOBIG, 0));
	else if (error < 0)
		(free_s(new_node), end(s, MSG_NOTNUM, 0));
	if (last_node)
		last_node->below = new_node;
	return (new_node);
}

///////////////////////////////////////////////////////////////////////////////]
//  #   TAKES STACK A PAS ENCORE REFERME, ASSIGN 012345.. VALUE
//  #   CHECKS DUPLICATES
//  exit_code -3: duplicates number
static void	assign_value(t_data *data)
{
	t_num	*ptr_i;
	t_num	*ptr_k;

	ptr_i = data->top_a;
	while (ptr_i)
	{
		ptr_k = data->top_a;
		while (ptr_k)
		{
			if (ptr_i != ptr_k && ptr_i->num == ptr_k->num)
				end(data, MSG_DUPLICATE, 0);
			if (ptr_i->num > ptr_k->num)
				ptr_i->num_index++;
			ptr_k = ptr_k->below;
		}
		if (!ptr_i->num_index)
			data->zero = ptr_i;
		ptr_i = ptr_i->below;
	}
}

///////////////////////////////////////////////////////////////////////////////]
static void	assign_target(t_data *data)
{
	t_num	*ptr_i;
	t_num	*ptr_k;
	int		target;

	ptr_i = data->top_a;
	while (ptr_i)
	{
		target = (ptr_i->num_index + 1) % data->full_size;
		ptr_k = data->top_a;
		while (ptr_k)
		{
			if (ptr_k->num_index == target)
			{
				ptr_i->target = ptr_k;
				ptr_k->hunter = ptr_i;
				break ;
			}
			ptr_k = ptr_k->below;
		}
		ptr_i = ptr_i->below;
	}
}
