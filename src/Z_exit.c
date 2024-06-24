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

int			exit_all(t_stacks *s, char *message, int exit_code, void *ptr);
void		free_algos(t_stacks *stacks);
static void	free_stack(t_entry *first);
int			final_test(t_stacks *s);

///////////////////////////////////////////////////////////////////////////////]
//	#	EXIT FUNCTION
//  #   free ptr + stacks; if exit_code < 0, exit
int	exit_all(t_stacks *s, char *message, int exit_code, void *ptr)
{
	free_s(ptr);
	if (s)
	{
		free_algos(s);
		free_tab(s->args);
		if (s->size_a && s->top_a)
			free_stack(s->top_a);
		if (s->size_b && s->top_b)
			free_stack(s->top_b);
	}
	if (exit_code)
		put(RED "Some error happnd' honey:\n" RESET "\t%s", message);
	if (exit_code < 0)
		exit(exit_code);
	return (exit_code);
}

///////////////////////////////////////////////////////////////////////////////]
//  free all strings algo
void	free_algos(t_stacks *stacks)
{
	int		i;
	t_entry	*cursor;

	i = -1;
	cursor = stacks->top_a;
	while (++i < stacks->full_size)
	{
		if (i == stacks->size_a)
			cursor = stacks->top_b;
		if (!cursor)
			break ;
		cursor->algo = free_s(cursor->algo);
		cursor = cursor->below;
	}
}

///////////////////////////////////////////////////////////////////////////////]
//  #  FREE THE FULL STACK
static void	free_stack(t_entry *first)
{
	t_entry	*next;
	t_entry	*current;

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
int	final_test(t_stacks *s)
{
	t_entry	*temp;
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