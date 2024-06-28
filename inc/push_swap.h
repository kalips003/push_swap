/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 13:16:57 by agallon           #+#    #+#             */
/*   Updated: 2024/06/28 19:33:23 by agallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"

///////////////////////////////////////////////////////////////////////////////]
typedef struct s_stacks	t_data;
typedef struct s_entry	t_num;
typedef int				(*t_fcmd)(t_data *data, char sw);
///////////////////////////////////////////////////////////////////////////////]
//		MOTHER STRUCT WITH BOTH A & B
typedef struct s_stacks
{
	struct s_entry		*top_a;
	struct s_entry		*top_b;
	struct s_entry		*zero;

	t_fcmd				controls[11];
	char				**args;
	int					size;
	int					size_a;
	int					size_b;
}						t_data;

///////////////////////////////////////////////////////////////////////////////]
//		CONTAINER FOR 1 NUMBER
typedef struct s_entry
{
	struct s_entry		*up;
	struct s_entry		*down;

	struct s_entry		*target;
	struct s_entry		*hunter;

	int					num;
	int					num_i;

	int					size_s;

	char				ab;

	int					position;

	int					dist;
	int					dist_p;
	int					dist_n;

	char				*algo;
	int					algo_sz;

}						t_num;
///////////////////////////////////////////////////////////////////////////////]
//		STRUCT FOR ALGORITHM
// 	num_dist_target = ndt
// 	ndtp = ndtp
// 	btbn = bt_dist_bn
// 	sizeb_n = sbn
// 	sizeb_t = sbt
typedef struct s_algo
{
	struct s_entry		*num;
	struct s_entry		*tar;

	struct s_entry		*bnum;
	struct s_entry		*btar;

	char				*s1;
	char				*s2;
	char				*s3;
	char				*s4;

	int					ndt;
	int					ndtp;
	int					btbn;

	int					sbn;
	int					sbt;
}						t_algo;

///////////////////////////////////////////////////////////////////////////////]
//	A - CREATE STRUCT
void					ini_stacks(int ac, char **av, t_data *data);
//	B - COMMANDS
int						pb(t_data *s, char sw);
int						pa(t_data *s, char sw);
int						ra(t_data *s, char sw);
int						rb(t_data *s, char sw);
int						rr(t_data *s, char sw);
int						rra(t_data *s, char sw);
int						rrb(t_data *s, char sw);
int						rrr(t_data *s, char sw);
int						sa(t_data *s, char sw);
int						sb(t_data *s, char sw);
int						ss(t_data *s, char sw);
///////////////////////////////////////////////////////////////////////////////]
//	F - TOOLS
int						wii_wrapper(char c);
int						exec_string(t_data *data, char *instructions, char sw2);
void					ini_cmd(t_data *data);
///////////////////////////////////////////////////////////////////////////////]
// 3	P - GIVE POSITION
void					give_position(t_data *s);
///////////////////////////////////////////////////////////////////////////////]
//	Q - ALGO 1
int						algo_1(t_data *data, int sw);
t_num					*assign_str_all(t_data *data);
int						ft_algo_1(t_data *s, t_num *num);
void					helper_1(t_data *data, t_algo *a, t_num *num);
//	Q - ALGO 2
int						algo_2(t_data *data, int sw);
t_num					*assign_str_b(t_data *data);
int						ft_algo_2(t_data *data, t_num *num);
int						algo_ba_2(t_algo *a);
int						algo_ba_2(t_algo *a);
//	Q - ALGO
int						algo_aa(t_algo *a);
int						algo_bb(t_algo *a);
int						algo_ab(t_algo *a);
int						algo_ba(t_algo *a);
//	Q - ALGO
void					lets_rrr(t_algo *a, t_num *one, t_num *two, int bit);
//	Q - ALGO TOOLS
char					*sublim(t_data *data);
char					*smallest_str(int nb, ...);
int						order(t_data *s, t_num *previous, t_num *next);
void					helper_num_dist_target(t_data *data, t_algo *a,
							t_num *num);
void					helper_block_size(t_data *data, t_algo *a);
///////////////////////////////////////////////////////////////////////////////]
//	T - TESTER
void					tester(t_data *data);
//	U - TESTER FUNCTION
void					function1(t_data *data, int i, int sw);
void					function2(t_data *data, int i, int sw);
void					function3(t_data *data, int sw);
///////////////////////////////////////////////////////////////////////////////]
//	Y - PRINT
void					print(t_data *data, int sw, int bit);
void					print_header(t_data *data, int bit, int sw);
void					print_stru_algo(t_algo *a);
void					print_stack(t_data *data, t_num *s, char sw);
///////////////////////////////////////////////////////////////////////////////]
//	Z - EXIT
void					ft_break(int num, char *string2, int cls, void *ptr);
int						end(t_data *s, char *message, int exit_code);
void					free_algos(t_data *data);
int						final_test(t_data *s);

/*
///////////////////////////////////////////////////////////////////////////////]
// char	reverse_c(char c);
char	reverse_c(char c)
{
	if (c >= '1')
		c ^= 1;
	else if (c >= '4')
		return (c);
	else if (c >= '7')
		c += 3;
	else if (c >= ':')
		c -= 3;
	return (c);
}

// char	*reverse_str(char *cmd);
char	*reverse_str(char *cmd)
{
	int		size;
	char	*reverse;
	int		i;

	size = len(cmd);
	reverse = str("%s", cmd);
	if (!reverse)
		return (NULL);
	i = -1;
	while (cmd[++i])
		reverse[size - i - 1] = reverse_c(cmd[i]);
	return (reverse);
}
///////////////////////////////////////////////////////////////////////////////]
*/

# define PA "\033[38;5;1mpa\e[0m"
# define PB "\033[38;5;27mpb\e[0m"

# define SA "\033[38;5;178msa\e[0m"
# define SB "\033[38;5;210msb\e[0m"
# define SS "\033[38;5;202mss\e[0m"

# define RA "\033[38;5;40mra\e[0m"
# define RB "\033[38;5;64mrb\e[0m"
# define RR "\033[38;5;58mrr\e[0m"

# define RRA "\033[38;5;129mrra\e[0m"
# define RRB "\033[38;5;141mrrb\e[0m"
# define RRR "\033[38;5;153mrrr\e[0m"

# define MSG_TOOBIG "\033[0;31merror\033[0;32m - yeah, about that.. \
THAT wont fit, sorry.\n\e[0m"
# define MSG_NOTNUM "\033[0;31merror\033[0;32m - yeahhh.. that's not\
 a number.\n\e[0m"
# define MSG_DUPLICATE "\033[0;31merror\033[0;32m - DUPLICATE NUMBERS\n\e[0m"
# define MSG_BADCMD "\033[0;31merror\033[0;32m - That' aint no command \
i know of, boss..\n\e[0m"
# define MSG_NONUM "\033[0;31merror\033[0;32m - KRONK ! You forgot the \
numbers...\n> \e[0m"

# define UNDER_B "\033[48;5;4m\e[0m"
# define UNDER_R "\033[48;5;1m\e[0m"

# define MSG_KO "\e[5m\033[38;5;147m\n\
\t██╗░░██╗░█████╗░░░░░░░░░░\n\
\t██║░██╔╝██╔══██╗░░░░░░░░░\n\
\t█████═╝░██║░░██║░░░░░░░░░\n\
\t██╔═██╗░██║░░██║░░░░░░░░░\n\
\t██║░╚██╗╚█████╔╝██╗██╗██╗\n\
\t╚═╝░░╚═╝░╚════╝░╚═╝╚═╝╚═╝\e[0m\n"
# define MSG_OK "\e[5m\033[38;5;77m\n\
\t░█████╗░██╗░░██╗  ██╗\n\
\t██╔══██╗██║░██╔╝  ██║\n\
\t██║░░██║█████═╝░  ██║\n\
\t██║░░██║██╔═██╗░  ╚═╝\n\
\t╚█████╔╝██║░╚██╗  ██╗\n\
\t░╚════╝░╚═╝░░╚═╝  ╚═╝\e[0m\n"

#endif
