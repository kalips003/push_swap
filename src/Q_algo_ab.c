/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Q_algo_ab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 00:17:38 by kalipso           #+#    #+#             */
/*   Updated: 2024/06/26 12:52:06 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	algo_aa(t_algo *a);
int	algo_bb(t_algo *a);
int	algo_ab(t_algo *a);
int	algo_ba(t_algo *a);

///////////////////////////////////////////////////////////////////////////////]
// (0 pb)(1 pa)(2 sa)(3 sb)(4 ss)(5 ra)(6 rb)(7 rr)(8 rra)(9 rrb)(: rrr)
int algo_aa(t_algo *a)
{
	if (a->sizeb_t > 0)
	{
		a->str1 = str("%.*c%.*c%.*c", abs(a->num->dist + 1), '5' + 3 * (a->num->dist < 0), a->num_d_tar_plus - 1, '0', min(a->sizeb_n, a->sizeb_t), '5' + 3 * (a->sizeb_n < a->sizeb_t));

		a->str2 = str("%.*c%.*c%.*c%.*c", abs(a->blk_num->dist), '5' + 3 * (a->blk_num->dist < 0), a->sizeb_n, '0' \
					, min(a->num_d_tar_plus, a->bt_dist_bn + a->sizeb_t) - 1, '5' + 3 * (a->bt_dist_bn + a->sizeb_t < a->num_d_tar_plus), min(a->sizeb_n, a->sizeb_t), '0' + (a->sizeb_t > a->sizeb_n));

		a->str3 = str("%.*c%.*c%.*c5%.*c%.*c", abs(a->target->dist), '5' + 3 * (a->target->dist < 0), a->sizeb_t, '0' \
					, min(a->num_d_tar_plus, a->bt_dist_bn + a->sizeb_n) - 1, '5' + 3 * (a->bt_dist_bn + a->sizeb_n > a->num_d_tar_plus) \
					, a->sizeb_t, '1', min(a->sizeb_n, a->sizeb_t), '5' + 3 * (a->sizeb_n < a->sizeb_t));
		a->num->algo = smallest_str(3, a->str1, a->str2, a->str3);

	}
	else if (a->sizeb_t == -2)
		a->num->algo = str("%.*c2", abs(a->blk_tar->dist), '5' + 3 * (a->blk_tar->dist < 0));
	else if (a->sizeb_t < 0)
	{
		a->str1 = str("%.*c%*s", abs(a->blk_tar->dist), '5' + 3 * (a->blk_tar->dist < 0), -a->sizeb_t, "09");
		a->str2 = str("%.*c0%*s", abs(a->target->dist), '5' + 3 * (a->target->dist < 0), -a->sizeb_t - 1, "80");
		a->num->algo = smallest_str(2, a->str1, a->str2);
	}
	if (a->sizeb_n == 1 && (a->sizeb_t == 1 || a->sizeb_t < -2))
	{
		a->str1 = str("%.*c%.*c5", abs(a->target->dist + 1), '5' + 3 * (a->target->dist < 0), a->bt_dist_bn - abs(a->sizeb_t), '0');
		a->str2 = str("%.*c%.*c%.*c0", abs(a->blk_tar->dist), '5' + 3 * (a->blk_tar->dist < 0), abs(a->sizeb_t), '0', min(a->num_d_tar_plus - abs(a->sizeb_t) + 1, a->bt_dist_bn - abs(a->sizeb_t))
				, '5' + 3 * (a->num_d_tar_plus - abs(a->sizeb_t) < a->bt_dist_bn - abs(a->sizeb_t)));
		a->str3 = str("%.*c0%.*c15", abs(a->num->dist), '5' + 3 * (a->num->dist < 0) \
				, min(a->num_d_tar_plus - 1, a->bt_dist_bn - abs(a->sizeb_t) - 1) + 1\
				, '5' + 3 * (a->num_d_tar_plus - 1 > a->bt_dist_bn - abs(a->sizeb_t) - 1));
		a->num->algo = smallest_str(4, a->num->algo, a->str1, a->str2, a->str3);
	}

	// (free(a->num->algo), a->num->algo = NULL);
	return (len(a->num->algo));
}

///////////////////////////////////////////////////////////////////////////////]
// (0 pb)(1 pa)(2 sa)(3 sb)(4 ss)(5 ra)(6 rb)(7 rr)(8 rra)(9 rrb)(: rrr)
int algo_bb(t_algo *a)
{
	if (a->sizeb_t > 0)
	{
		a->str1 = str("%.*c%.*c%.*c", abs(a->target->dist + 1), '6' + 3 * (a->target->dist < 0), a->num_d_tar_plus - 1, '1', min(a->sizeb_n, abs(a->sizeb_t)), '6' + 3 * (a->sizeb_n > a->sizeb_t));

		a->str2 = str("%.*c%.*c%.*c%.*c", abs(a->blk_tar->dist), '6' + 3 * (a->blk_tar->dist < 0), abs(a->sizeb_t), '1' 
					, min(a->num_d_tar_plus, a->bt_dist_bn + a->sizeb_n) - 1, '6' + 3 * (a->bt_dist_bn + a->sizeb_n < a->num_d_tar_plus), min(a->sizeb_n, abs(a->sizeb_t)), '0' + (a->sizeb_t > a->sizeb_n));

		a->str3 = str("%.*c%.*c%.*c6%.*c%.*c", abs(a->num->dist), '6' + 3 * (a->num->dist < 0), a->sizeb_n, '1' \
					, min(a->num_d_tar_plus, a->bt_dist_bn + abs(a->sizeb_t)) - 1, '6' + 3 * (a->bt_dist_bn + abs(a->sizeb_t) > a->num_d_tar_plus) \
					, a->sizeb_n, '0', min(a->sizeb_n, abs(a->sizeb_t)), '6' + 3 * (a->sizeb_n > a->sizeb_t));
		a->num->algo = smallest_str(3, a->str1, a->str2, a->str3);
	}
	else if (a->sizeb_t == -2)
		a->num->algo = str("%.*c3", abs(a->target->dist), '6' + 3 * (a->target->dist < 0));
	else if (a->sizeb_t < 0)
	{
		a->str1 = str("%.*c%*s", abs(a->target->dist), '5' + 3 * (a->target->dist < 0), -a->sizeb_t, "18");
		a->str2 = str("%.*c1%*s", abs(a->blk_tar->dist), '5' + 3 * (a->blk_tar->dist < 0), -a->sizeb_t - 1, "91");
		a->num->algo = smallest_str(2, a->str1, a->str2);
	}
	if (a->sizeb_n == 1 && (a->sizeb_t == 1 || a->sizeb_t < -2))
	{
		a->str1 = str("%.*c%.*c6", abs(a->num->dist + 1), '6' + 3 * (a->num->dist < 0), a->bt_dist_bn - abs(a->sizeb_t), '1');
		// a->num->algo = str("%.*c%.*c%.*c1", abs(a->target->dist), '6' + 3 * (a->target->dist < 0), abs(a->sizeb_t), '1', min(a->num_d_tar_plus - abs(a->sizeb_t) + 1, a->bt_dist_bn - abs(a->sizeb_t))
		//		 , '6' + 3 * (a->num_d_tar_plus - abs(a->sizeb_t) < a->bt_dist_bn - abs(a->sizeb_t)));
		// a->str3 = str("%.*c0%.*c15", abs(a->num->dist), '5' + 3 * (a->num->dist < 0) 
		//		 , min(a->num_d_tar_plus - 1, a->bt_dist_bn - abs(a->sizeb_t) - 1) + 1
		//		 , '5' + 3 * (a->num_d_tar_plus - 1 > a->bt_dist_bn - abs(a->sizeb_t) - 1));
		a->num->algo = smallest_str(2, a->num->algo, a->str1);
	}


	// (free(a->num->algo), a->num->algo = NULL);
	return (len(a->num->algo));
}

///////////////////////////////////////////////////////////////////////////////]
// (0 pb)(1 pa)(2 sa)(3 sb)(4 ss)(5 ra)(6 rb)(7 rr)(8 rra)(9 rrb)(: rrr)
int algo_ab(t_algo *a)
//		OK!
{
	if (a->sizeb_t > 0)
	{
		lets_rrr(a, a->num, a->blk_tar, 0b10);
		a->num->algo = fjoin(2, 0b11, a->str1, str("%.*c%.*c", a->sizeb_t, '1', min(a->sizeb_n, a->sizeb_t), '5' + 3 * (a->sizeb_t > a->sizeb_n)));
		lets_rrr(a, a->blk_num, a->target, 0b01);
		a->str1 = fjoin(2, 0b11, a->str1, str("%.*c%.*c", a->sizeb_n, '0', min(a->sizeb_n, a->sizeb_t), '6' + 3 * (a->sizeb_t < a->sizeb_n)));
		a->num->algo = smallest_str(2, a->str1, a->num->algo);
	}
	else if (a->sizeb_t == -2)
	{
		lets_rrr(a, a->num, a->target, 0b10);
		a->num->algo = fjoin(2, 0b11, a->str1, str("112%.*c", min(a->sizeb_n, -a->sizeb_t), '5' + 3 * (-a->sizeb_t < a->sizeb_n)));
	}
	else if (a->sizeb_t < 0)
	{
		lets_rrr(a, a->num, a->target, 0b10);
		a->num->algo = fjoin(2, 0b11, a->str1, str("%*s", -a->sizeb_t, "15"));
		lets_rrr(a, a->num, a->blk_tar, 0b10);
		a->str1 = fjoin(2, 0b11, a->str1, str("%*s%.*c", -a->sizeb_t, "91", min(a->sizeb_n, -a->sizeb_t), '5' + 3 * (-a->sizeb_t > a->sizeb_n)));
	}
	if (a->sizeb_n == 1 && (a->sizeb_t == 1 || a->sizeb_t < -2))
	{
		lets_rrr(a, a->num, a->target, 0b00);
		a->num->algo = smallest_str(2, a->num->algo, fjoin(2, 0b11, a->str1, str("0")));
	}

	// (free(a->num->algo), a->num->algo = NULL);
	return (len(a->num->algo));
}

///////////////////////////////////////////////////////////////////////////////]
// (0 pb)(1 pa)(2 sa)(3 sb)(4 ss)(5 ra)(6 rb)(7 rr)(8 rra)(9 rrb)(: rrr)
int algo_ba(t_algo *a)
//		OK!
{
	if (a->sizeb_t > 0)
	{
		lets_rrr(a, a->num, a->target, 0b00);
		a->num->algo = fjoin(2, 0b11, a->str1, str("%.*c", min(a->sizeb_n, a->sizeb_t), '1' - (a->sizeb_n > a->sizeb_t)));
	}
	else if (a->sizeb_t == -2)
	{
		lets_rrr(a, a->num, a->blk_tar, 0b00);
		a->num->algo = fjoin(2, 0b11, a->str1, str("2%.*c", min(a->sizeb_n, 2), '1' - (a->sizeb_n > 2)));
	}
	else if (a->sizeb_t < 0)
	{
		lets_rrr(a, a->num, a->target, 0b00);
		a->num->algo = fjoin(2, 0b11, a->str1, str("0%*s", -a->sizeb_t - 1, "80"));
		lets_rrr(a, a->num, a->blk_tar, 0b00);
		a->str1 = fjoin(2, 0b11, a->str1, str("%*s0%.*c", -a->sizeb_t - 1, "06", min(a->sizeb_n + 1, -a->sizeb_t - 1), '6' + 3 * (a->sizeb_n + 1 > -a->sizeb_t - 1)));
		a->num->algo = smallest_str(2, a->num->algo, a->str1);
	}
	if (a->sizeb_n == 1 && (a->sizeb_t == 1 || a->sizeb_t < -2))
	{
		lets_rrr(a, a->num, a->target, 0b01);
		a->num->algo = smallest_str(2, a->num->algo, fjoin(2, 0b11, a->str1, str("15")));
	}
	// (free(a->num->algo), a->num->algo = NULL);
	return (len(a->num->algo));
}
