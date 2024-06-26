/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   R_aglo_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:17:41 by kalipso           #+#    #+#             */
/*   Updated: 2024/06/26 12:52:06 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_in_order(t_data *s, t_num *previous, t_num *next);
t_num	*assign_str_all(t_data *data, int (*best_str_algo)(t_data*, t_num*));
void	helper_block_size(t_data *data, t_algo *a);
int algo_aa(t_algo *a);
int algo_bb(t_algo *a);
int algo_ab(t_algo *a);
int algo_ba(t_algo *a);
int	algo_1(t_data *data, int sw);
int	ft_algo_1(t_data *s, t_num *num);
void	helper_1(t_data *data, t_algo *a, t_num *num);
static void	helper_give_blk(t_data *s, t_num *num);
void	helper_give_blk_wrapper(t_data *s);
void	reevalue(t_data *s, t_num *num);

///////////////////////////////////////////////////////////////////////////////]
/*******************************************************************************
░█████╗░██████╗░░█████╗░██╗░░██╗██╗██╗░░░██╗███████╗░██████╗
██╔══██╗██╔══██╗██╔══██╗██║░░██║██║██║░░░██║██╔════╝██╔════╝
███████║██████╔╝██║░░╚═╝███████║██║╚██╗░██╔╝█████╗░░╚█████╗░
██╔══██║██╔══██╗██║░░██╗██╔══██║██║░╚████╔╝░██╔══╝░░░╚═══██╗
██║░░██║██║░░██║╚█████╔╝██║░░██║██║░░╚██╔╝░░███████╗██████╔╝
╚═╝░░╚═╝╚═╝░░╚═╝░╚════╝░╚═╝░░╚═╝╚═╝░░░╚═╝░░░╚══════╝╚═════╝░

// if in order 1 (0 1)
// if reverse order -1 (3 2)
// else 0
int	is_in_order(t_data *s, t_num *previous, t_num *next)
{
	int	size;

	size = next->num_i - previous->num_i;
	if (size == 1 || size == -s->full_size + 1)
		return (1);
	else if (size == -1 || size == s->full_size - 1)
		return (-1);
	else
		return (0);
}

///////////////////////////////////////////////////////////////////////////////]
//		give str to all nuber based on best_str_algo0
// 		return the number with smallest string
t_num	*assign_str_all(t_data *data, int (*best_str_algo)(t_data*, t_num*))
{
	int		i;
	int		smaller = 0;
	t_num	*temp;
	t_num	*small;

	small = NULL;
	free_algos(data);
	give_position(data);
	i = -1;
	temp = data->top_a;
	while (++i < data->full_size)
	{
		if (i == data->size_a)
			temp = data->top_b;
		temp->algo_sz = best_str_algo(data, temp);
		if (temp->algo_sz && (smaller == 0 || temp->algo_sz < smaller))
		{
			smaller = temp->algo_sz;
			small = temp;
		}
		temp = temp->below;
	}
	return (small);
}

//  #   SET: blk_num _ sizeb_n  __ blk_tar _ sizeb_t
// pb with B:[21-22] > a->sizeb_n == 0,1,0,1,0,1...
void	helper_block_size(t_data *data, t_algo *a)
{
	a->blk_num = a->num;
	while (++a->sizeb_n < a->blk_num->size_s && is_in_order(data, *((t_num **)(a->blk_num) + (a->blk_num->pile_c == 'B')), a->blk_num))
		a->blk_num = *((t_num **)(a->blk_num) + (a->blk_num->pile_c == 'B'));
	a->blk_tar = a->target;
	while (++a->sizeb_t < a->blk_tar->size_s && is_in_order(data, a->blk_tar, *((t_num **)(a->blk_tar) + (a->blk_tar->pile_c == 'A'))) == 1)
		a->blk_tar = *((t_num **)(a->blk_tar) + (a->blk_tar->pile_c == 'A'));
	if (is_in_order(data, *((t_num **)(a->blk_tar) + (a->blk_tar->pile_c == 'B')), a->blk_tar) == -1)
	{
		a->sizeb_t = 0;
		while (++a->sizeb_t < a->blk_tar->size_s && is_in_order(data, *((t_num **)(a->blk_tar) + (a->blk_tar->pile_c == 'B')), a->blk_tar) == -1)
			a->blk_tar = *((t_num **)(a->blk_tar) + (a->blk_tar->pile_c == 'B'));
		a->sizeb_t *= -1;
	}
}

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

int algo_ab(t_algo *a)
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

int algo_ba(t_algo *a)
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

///////////////////////////////////////////////////////////////////////////////]
// simplest algo
int	algo_1(t_data *data, int sw)
{
	t_num	*small;
	int		size;
	char	*last;

	small = assign_str_all(data, ft_algo_1);
	size = 0;
	while (small && small->algo)
	{
		size += exec_string(data, small->algo, sw);
		small = assign_str_all(data, ft_algo_1);
	}
	last = sublim(data);
	size += len(last);
	exec_string(data, last, sw);
	free_s(last);
	return (size);
}

//		give best string to 1 number
//		return the len of the best string
int	ft_algo_1(t_data *s, t_num *num)
{
	t_algo a;

	helper_1(s, &a, num);
	int bit = (a.num->pile_c == 'A') << 1 | (a.target->pile_c == 'A');
	// if  (num->dist == 1 && a.sizeb_n == -1) -> 'sa'
	if (a.num_dist_target == 1 || a.num_dist_target == -1)
		return (0);
	if (is_in_order(s, num, *((t_num **)(num) + (num->pile_c == 'A'))) == -1)
		return (0);
	if (bit == 0)// num top stack, swap !! 7-10-8-11 > 10-7-8-11
		return(algo_bb(&a));
	else if (bit == 1)
		return(algo_ba(&a));
	else if (bit == 2)
		return(algo_ab(&a));
	else
		return(algo_aa(&a));
	return (0);
}

//  #	initialize algori struct with num data
void	helper_1(t_data *data, t_algo *a, t_num *num)
{
	ft_memset(a, 0, sizeof(t_algo));
	a->num = num;
	a->target = num->target;
//  blocks handling
	helper_block_size(data, a);
//  num_dist_target
	if ((num->position >> 31) == (a->target->position >> 31))
	{
		a->num_dist_target = -1;
		t_num *temp = num;
		while (++(a->num_dist_target) < num->size_s && temp != a->target)
			temp = *((t_num **)(temp) + (temp->pile_c == 'A'));
		a->num_d_tar_plus = a->num_dist_target;
		if (a->num_dist_target > num->size_s / 2)
			a->num_dist_target -= num->size_s;
		a->bt_dist_bn = -1;
		temp = a->blk_tar;
		while (++(a->bt_dist_bn) < num->size_s && temp != a->blk_num)
			temp = *((t_num **)(temp) + (temp->pile_c == 'A'));
	}
}
///////////////////////////////////////////////////////////////////////////////]
static void	helper_give_blk(t_data *s, t_num *num)
{
	t_num	*ptr;
	int		i;

	ptr = num;
	i = 0;
	while (--i > -num->size_s && ptr->target == ptr->above)
		ptr = ptr->above;
	if (i == -1 && i++)
	{
		ptr = num;
		while (++i < num->size_s && ptr->target == ptr->below)
			ptr = ptr->below;
	}
	// size blk toward target
	num->size_blk = i;
	if (i != 1)
		num->size_blk *= -1 + 2 * (num->pile_c == 'A');
	num->blk_end = ptr;
	// put("--->%d", num->size_blk);

	ptr = num;
	i = 0;
	while (--i > -num->size_s && ptr->hunter == ptr->below)
			ptr = ptr->below;
	if (i == -1 && i++)
	{
		ptr = num;
		while (++i < num->size_s && ptr->hunter == ptr->above)
			ptr = ptr->above;
	}
	// size blk toward hunter
	if (i != 1)
		num->size_blk += i * (-1 + 2 * (num->pile_c == 'A'));
	num->blk_start = ptr;
}

void	helper_give_blk_wrapper(t_data *s)
{
	int		i;
	t_num	*ptr;

	i = -1;
	ptr = s->top_a;
	while (++i < s->full_size)
	{
		if (i == s->size_a)
			ptr = s->top_b;
		helper_give_blk(s, ptr);
		ptr = ptr->below;
	}
}
///////////////////////////////////////////////////////////////////////////////]
// reassignn value and char to num
void	reevalue(t_data *s, t_num *num)
{
	int		i;
	t_num	*current;

	i = -1;
	current = s->top_a->above;
	while (++i < s->size_a && current)
	{
		if (current == num)
			return (helper_give_posi(s, current, 'A', i));
		current = current->below;
	}
	i = -1;
	current = s->top_b->above;
	while (++i < s->size_b && current)
	{
		if (current == num)
			return (helper_give_posi(s, current, 'B', i));
		current = current->below;
	}
}
*******************************************************************************/