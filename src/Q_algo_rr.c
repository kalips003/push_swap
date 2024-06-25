/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Q_algo_rr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 00:23:54 by kalipso           #+#    #+#             */
/*   Updated: 2024/06/25 00:23:54 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		lets_rrr(t_algo *a, t_num *one, t_num *two, int bit);
static char	*lets_rr(char *s1, char *s2);
static void	lets_r(char *c1, char *c2);

///////////////////////////////////////////////////////////////////////////////]
// (0) pb  (1) pa  (2) sa  (3) sb  (4) ss  (5) ra  (6) rb  (7) rr  (8) rra  (9) rrb (:) rrr
//  bit 0b10 = one on -1
//  bit 0b00 = one on 0
//  bit 0b01 = one on -1
void	lets_rrr(t_algo *a, t_num *one, t_num *two, int bit)
{
	a->str1 = lets_rr(str("%.*c", one->dist_p + ((bit & 2) >> 1), '5'
				+ (one->pile_c == 'B')), str("%.*c", two->dist_p + (bit & 1),
				'5' + (two->pile_c == 'B')));
	a->str2 = lets_rr(str("%.*c", one->dist_n - ((bit & 2) >> 1), '8'
				+ (one->pile_c == 'B')), str("%.*c", two->dist_n - (bit & 1),
				'8' + (two->pile_c == 'B')));
	a->str3 = fjoin(2, 0b11, str("%.*c", one->dist_p + ((bit & 2) >> 1), '5'
				+ (one->pile_c == 'B')), str("%.*c", two->dist_n - (bit & 1),
				'8' + (two->pile_c == 'B')));
	a->str4 = fjoin(2, 0b11, str("%.*c", one->dist_n - ((bit & 2) >> 1), '8'
				+ (one->pile_c == 'B')), str("%.*c", two->dist_p + (bit & 1),
				'5' + (two->pile_c == 'B')));
	a->str1 = smallest_str(4, a->str1, a->str2, a->str3, a->str4);
}

static char	*lets_rr(char *s1, char *s2)
{
	int len1;
	int len2;
	int i;

	len1 = len(s1);
	len2 = len(s2);
	i = -1;
	while (++i < len1 && i < len2)
		lets_r(&s1[i], &s2[i]);
	if (!s1[i])
	{
		free(s1);
		return (s2);
	}
	else
	{
		free(s2);
		return (s1);
	}
}

static void	lets_r(char *c1, char *c2)
{
	if ((*c1 == '2' && *c2 == '3') || (*c1 == '3' && *c2 == '2'))
	{
		*c1 = '4';
		*c2 = '4';
	}
	else if ((*c1 == '5' && *c2 == '6') || (*c1 == '6' && *c2 == '5'))
	{
		*c1 = '7';
		*c2 = '7';
	}
	else if ((*c1 == '8' && *c2 == '9') || (*c1 == '9' && *c2 == '8'))
	{
		*c1 = ':';
		*c2 = ':';
	}
}
