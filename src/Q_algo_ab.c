/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Q_algo_ab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 00:17:38 by kalipso           #+#    #+#             */
/*   Updated: 2024/06/28 14:43:04 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	algo_aa(t_algo *a);
int	algo_bb(t_algo *a);
int	algo_ab(t_algo *a);
int	algo_ba(t_algo *a);

///////////////////////////////////////////////////////////////////////////////]
// (0 pb)(1 pa)(2 sa)(3 sb)(4 ss)(5 ra)(6 rb)(7 rr)(8 rra)(9 rrb)(: rrr)
int	algo_aa(t_algo *a)
{
	if (a->sbt > 0)
	{
		a->s1 = str("%.*c%.*c%.*c", abs(a->num->dist + 1), '5' + 3
				* (a->num->dist < 0), a->ndtp - 1, '0', min(a->sbn, a->sbt), '5'
				+ 3 * (a->sbn < a->sbt));
		a->s2 = str("%.*c%.*c%.*c%.*c", abs(a->bnum->dist), '5' + 3
				* (a->bnum->dist < 0), a->sbn, '0', min(a->ndtp, a->btbn
					+ a->sbt) - 1, '5' + 3 * (a->btbn + a->sbt < a->ndtp),
				min(a->sbn, a->sbt), '0' + (a->sbt > a->sbn));
		a->s3 = str("%.*c%.*c%.*c5%.*c%.*c", abs(a->tar->dist), '5' + 3
				* (a->tar->dist < 0), a->sbt, '0', min(a->ndtp, a->btbn
					+ a->sbn) - 1, '5' + 3 * (a->btbn + a->sbn > a->ndtp),
				a->sbt, '1', min(a->sbn, a->sbt), '5' + 3 * (a->sbn < a->sbt));
		a->num->algo = smallest_str(3, a->s1, a->s2, a->s3);
	}
	else if (a->sbt == -2)
		a->num->algo = str("%.*c2", abs(a->btar->dist), '5' + 3
				* (a->btar->dist < 0));
	else if (a->sbt < 0)
		a->num->algo = smallest_str(2, str("%.*c%*s", abs(a->btar->dist), '5'
					+ 3 * (a->btar->dist < 0), -a->sbt, "09"), str("%.*c0%*s",
					abs(a->tar->dist), '5' + 3 * (a->tar->dist < 0), -a->sbt
					- 1, "80"));
	return (len(a->num->algo));
}

///////////////////////////////////////////////////////////////////////////////]
// (0 pb)(1 pa)(2 sa)(3 sb)(4 ss)(5 ra)(6 rb)(7 rr)(8 rra)(9 rrb)(: rrr)
int	algo_bb(t_algo *a)
{
	if (a->sbt > 0)
	{
		a->s1 = str("%.*c%.*c%.*c", abs(a->tar->dist + 1), '6' + 3
				* (a->tar->dist < 0), a->ndtp - 1, '1', min(a->sbn,
					abs(a->sbt)), '6' + 3 * (a->sbn > a->sbt));
		a->s2 = str("%.*c%.*c%.*c%.*c", abs(a->btar->dist), '6' + 3
				* (a->btar->dist < 0), abs(a->sbt), '1', min(a->ndtp, a->btbn
					+ a->sbn) - 1, '6' + 3 * (a->btbn + a->sbn < a->ndtp),
				min(a->sbn, abs(a->sbt)), '0' + (a->sbt > a->sbn));
		a->s3 = str("%.*c%.*c%.*c6%.*c%.*c", abs(a->num->dist), '6' + 3
				* (a->num->dist < 0), a->sbn, '1', min(a->ndtp, a->btbn
					+ abs(a->sbt)) - 1, '6' + 3 * (a->btbn
					+ abs(a->sbt) > a->ndtp), a->sbn, '0', min(a->sbn,
					abs(a->sbt)), '6' + 3 * (a->sbn > a->sbt));
		a->num->algo = smallest_str(3, a->s1, a->s2, a->s3);
	}
	else if (a->sbt == -2)
		a->num->algo = str("%.*c3", abs(a->tar->dist), '6' + 3
				* (a->tar->dist < 0));
	else if (a->sbt < 0)
		a->num->algo = smallest_str(2, str("%.*c%*s", abs(a->tar->dist), '5' + 3
					* (a->tar->dist < 0), -a->sbt, "18"), str("%.*c1%*s",
					abs(a->btar->dist), '5' + 3 * (a->btar->dist < 0), -a->sbt
					- 1, "91"));
	return (len(a->num->algo));
}

///////////////////////////////////////////////////////////////////////////////]
// (0 pb)(1 pa)(2 sa)(3 sb)(4 ss)(5 ra)(6 rb)(7 rr)(8 rra)(9 rrb)(: rrr)
int	algo_ab(t_algo *a)
//		OK!
{
	if (a->sbt > 0)
	{
		lets_rrr(a, a->num, a->btar, 0b10);
		a->num->algo = fjoin(2, 0b11, a->s1, str("%.*c%.*c", a->sbt, '1',
					min(a->sbn, a->sbt), '5' + 3 * (a->sbt > a->sbn)));
		lets_rrr(a, a->bnum, a->tar, 0b01);
		a->s1 = fjoin(2, 0b11, a->s1, str("%.*c%.*c", a->sbn, '0', min(a->sbn,
						a->sbt), '6' + 3 * (a->sbt < a->sbn)));
		a->num->algo = smallest_str(2, a->s1, a->num->algo);
	}
	else if (a->sbt == -2)
	{
		lets_rrr(a, a->num, a->tar, 0b10);
		a->num->algo = fjoin(2, 0b11, a->s1, str("112%.*c", min(a->sbn,
						-a->sbt), '5' + 3 * (-a->sbt < a->sbn)));
	}
	else if (a->sbt < 0)
	{
		lets_rrr(a, a->num, a->tar, 0b10);
		a->num->algo = fjoin(2, 0b11, a->s1, str("%*s", -a->sbt, "15"));
		lets_rrr(a, a->num, a->btar, 0b10);
		a->s1 = fjoin(2, 0b11, a->s1, str("%*s%.*c", -a->sbt, "91", min(a->sbn,
						-a->sbt), '5' + 3 * (-a->sbt > a->sbn)));
	}
	return (len(a->num->algo));
}

///////////////////////////////////////////////////////////////////////////////]
// (0 pb)(1 pa)(2 sa)(3 sb)(4 ss)(5 ra)(6 rb)(7 rr)(8 rra)(9 rrb)(: rrr)
int	algo_ba(t_algo *a)
//		OK!
{
	if (a->sbt > 0)
	{
		lets_rrr(a, a->num, a->tar, 0b00);
		a->num->algo = fjoin(2, 0b11, a->s1, str("%.*c", min(a->sbn, a->sbt),
					'1' - (a->sbn > a->sbt)));
	}
	else if (a->sbt == -2)
	{
		lets_rrr(a, a->num, a->btar, 0b00);
		a->num->algo = fjoin(2, 0b11, a->s1, str("2%.*c", min(a->sbn, 2), '1'
					- (a->sbn > 2)));
	}
	else if (a->sbt < 0)
	{
		lets_rrr(a, a->num, a->tar, 0b00);
		a->num->algo = fjoin(2, 0b11, a->s1, str("0%*s", -a->sbt - 1, "80"));
		lets_rrr(a, a->num, a->btar, 0b00);
		a->s1 = fjoin(2, 0b11, a->s1, str("%*s0%.*c", -a->sbt - 1, "06",
					min(a->sbn + 1, -a->sbt - 1), '6' + 3 * (a->sbn + 1
						> -a->sbt - 1)));
		a->num->algo = smallest_str(2, a->num->algo, a->s1);
	}
	return (len(a->num->algo));
}
