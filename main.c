/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:51:31 by kalipso           #+#    #+#             */
/*   Updated: 2024/06/25 02:45:32 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static char *sublim(t_stacks *stacks)
{
    t_entry *zero;
    int     i;

    zero = stacks->top_a;
    i = -1;
    while (++i < stacks->full_size)
    {
        if (i == stacks->size_a)
            zero = stacks->top_b;
        if (zero->num_index == 0)
            break ;
        zero = zero->below;
    }
    give_position(stacks);
    if (zero->pile_c == 'B' && zero->above->num_index == 1)
        //  in order
        return (str("%.*c%.*c", abs(zero->dist + 1), '6' + 3 * (zero->dist < 0), stacks->full_size, '1'));
    if (zero->pile_c == 'B' && zero->below->num_index == 1)
        //  reverse
        return (str("%.*c%*s", abs(zero->dist), '6' + 3 * (zero->dist < 0), stacks->full_size, "91"));
    if (zero->pile_c == 'A' && zero->above->num_index == 1)
        //  reverse
        return (str("%*s%.*c%.*c", stacks->full_size, "80", abs(zero->dist + 1), '6' + 3 * (zero->dist < 0), stacks->full_size, '1'));
    if (zero->pile_c == 'A' && zero->below->num_index == 1)
        //  in order
        return (str("%.*c", abs(zero->dist), '5' + 3 * (zero->dist < 0)));
    return (NULL);
}
///////////////////////////////////////////////////////////////////////////////]
int main(int ac, char **av)
{
	t_stacks	stacks;

	if (ac < 2)
		return (put(MSG_NONUM));
	ini_stacks(ac, av, &stacks);
///////////////////////////
	t_entry *small;

	small = assign_str_all(&stacks);
	int i = 0;
	while (small && small->algo)
	{
		i += exec_string(&stacks, small->algo, 1);
		small = assign_str_all(&stacks);
	}
	char *last = sublim(&stacks);
	i += len(last);
	exec_string(&stacks, last, 1);
	free_s(last);
	// print(&stacks, 1, 1);
	// put("\talgo cost = %d\n", i);
////    FOOTER      ////
	//test_output(&stacks);
	end(&stacks, NULL, 0);
	return (0);
}
