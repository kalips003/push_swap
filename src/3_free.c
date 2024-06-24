/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_free.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:22:35 by kalipso           #+#    #+#             */
/*   Updated: 2024/06/24 12:22:35 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_algos(t_stacks *stacks);
void	free_stack(t_entry *first);
int		exit_all(t_stacks *s, char *message, int exit_code, void *ptr);

////////////////////////////////////////////////////////////
//	#	EXIT FUNCTION
//  free all strings algo
void    free_algos(t_stacks *stacks)
{
    int i;
    t_entry *cursor;

    i = -1;
    cursor = stacks->top_a;
    while (++i < stacks->full_size)
    {
        if (i == stacks->size_a)
            cursor = stacks->top_b;
        if (!cursor)
            break ;
        if (cursor->algo)
            free(cursor->algo);
        cursor->algo = NULL;
        cursor = cursor->below;
    }
}

//////////////////////////////////////////////////////
//  #  FREE THE FULL STACK
void    free_stack(t_entry *first)
{
    t_entry *next;
    t_entry *current;

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
//	#	EXIT FUNCTION
//  #   free ptr + stacks; if exit_code < 0, exit
int    exit_all(t_stacks *s, char *message, int exit_code, void *ptr)
{
    if (s)
        free_algos(s);
    if (s && s->args)
        free_tab(s->args);
    if (ptr)
        free(ptr);
    if (s && s->size_a && s->top_a)
        free_stack(s->top_a);
    if (s && s->size_b && s->top_b)
        free_stack(s->top_b);
    if (exit_code)
        put("%s" RESET, message);//  "some error happnd' honey\n"
    if (exit_code < 0)
        exit(exit_code);
    return (exit_code);
}
