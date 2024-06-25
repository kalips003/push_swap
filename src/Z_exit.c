/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_free.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:18:39 by kalipso           #+#    #+#             */
/*   Updated: 2024/06/24 13:18:39 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		ft_break(int num, char *string2, int cls, void *ptr);
int			end(t_data *s, char *message, int exit_code);
void		free_algos(t_data *data);
static void	free_stack(t_num *first);
int			final_test(t_data *s);

///////////////////////////////////////////////////////////////////////////////]
//	#	EXIT FUNCTION
//		bit[1, .] = cls
//		bit[., 1] = stops
void	ft_break(int num, char *string2, int cls, void *ptr)
{
	int	a;

	a = ft_print_cat(num, string2, cls);
	if (ptr)
		put("--->num = %p; algo = %s\n", ptr, ((t_num*)ptr)->algo);
	else
		put("--->num = %p\n", ptr);
	put(BLINK "\033[38;5;%dm\n\t\t>>>  続けましょう？  <<<\n" \
		RESET, a);
	free_s(gnl(0));
}

///////////////////////////////////////////////////////////////////////////////]
//	#	EXIT FUNCTION
//  #   free ptr + data; if exit_code < 0, exit
int	end(t_data *s, char *message, int exit_code)
{
	if (s)
	{
		free_algos(s);
		free_tab(s->args);
		// if (s->size_a && s->top_a)
		free_stack(s->top_a);
		// if (s->size_b && s->top_b)
		free_stack(s->top_b);
	}
	if (message && exit_code)
		put(RED "Some error happnd' honey:\n" RESET "\t%s", message);
	else if (message)
		put("\t%s", message);
	exit(exit_code);

}

///////////////////////////////////////////////////////////////////////////////]
//  free all strings algo
void	free_algos(t_data *data)
{
	int		i;
	t_num	*cursor;

	i = -1;
	cursor = data->top_a;
	ft_break(-1, "in free", 2, data->top_a);
	while (++i < data->full_size)
	{
		ft_break(10 * i + 1, "in free loop", 2, data->top_a);
		if (i == data->size_a)
			cursor = data->top_b;
		if (!cursor)
			break ;
		ft_break(10 * i + 2, "in free loop", 2, data->top_a);
		cursor->algo = free_s(cursor->algo);
		cursor = cursor->below;
	}
}

///////////////////////////////////////////////////////////////////////////////]
//  #  FREE THE FULL STACK
static void	free_stack(t_num *first)
{
	t_num	*next;
	t_num	*current;

	if (first == NULL)
		return ;
	current = first;
	while (current->below && current->below != first)
	{
		next = current->below;
		free_s(current);
		current = next;
	}
	free_s(current);
}

////////////////////////////////////////////////////////////
// final check, 0 = KO, 1 = OK
int	final_test(t_data *s)
{
	t_num	*temp;
	int		i;

	if (s->size_b || s->size_a != s->full_size)
		return(0);
	if (s->top_a->num_index || s->top_a->above->num_index != s->full_size - 1)
		return(0);
	temp = s->top_a;
	i = -1;
	while (++i < s->full_size)
	{
		if (temp->num_index != i)
			return (0);
		temp = temp->below;
	}
	return (i);
}