/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 13:16:57 by agallon           #+#    #+#             */
/*   Updated: 2024/06/25 15:25:32 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"

///////////////////////////////////////////////////////////////////////////////]
typedef struct s_stacks t_data;
typedef struct s_entry t_num;
typedef int (*f_cmd)(t_data *data, char sw);
///////////////////////////////////////////////////////////////////////////////]
//		MOTHER STRUCT WITH BOTH A & B
typedef struct s_stacks
{
	struct s_entry	*top_a;
	struct s_entry	*top_b;
	struct s_entry	*zero;

	f_cmd			controls[11];
	char			**args;
	int				full_size;
	int				size_a;
	int				size_b;
}	t_data;

///////////////////////////////////////////////////////////////////////////////]
//		CONTAINER FOR 1 NUMBER
typedef struct s_entry
{
//  const?
	struct s_entry	*above;
    struct s_entry	*below;

	struct s_entry	*target;
	struct s_entry	*hunter;

	int     num;
    int     num_index;
//	size of current stack
    int     size_s;
//	A or B
    char    pile_c;
// (A2)> 2; (B5)> -6
    int     position;
// (1/15) > 0; (14/15) > -2
    int     dist;
    int     dist_p;
    int     dist_n;

    int     size_blk;
	struct s_entry	*blk_start;
	struct s_entry	*blk_end;

    char    *algo;
    int     algo_sz;

}	t_num;
///////////////////////////////////////////////////////////////////////////////]
//		STRUCT FOR ALGORITHM
typedef struct s_algo
{
	struct s_entry	*num;
	struct s_entry	*target;

	struct s_entry	*blk_num;
	struct s_entry	*blk_tar;

    char *str1;
    char *str2;
    char *str3;
    char *str4;

    int num_dist_target;// ->below A, above B (+\-)
    int num_d_tar_plus;// ->below A, above B (+)
    int bt_dist_bn;// ->below A, above B (+)

    int sizeb_n;
    int sizeb_t;
}	t_algo;



///////////////////////////////////////////////////////////////////////////////]
//	A - CREATE STRUCT
void	ini_stacks(int ac, char **av, t_data *data);
//	A - INITIALIZATION 2
void	ini_cmd(t_data *data);
//	B - COMMANDS
int		pb(t_data *s, char sw);
int		pa(t_data *s, char sw);
int		ra(t_data *s, char sw);
int		rb(t_data *s, char sw);
int		rr(t_data *s, char sw);
int		rra(t_data *s, char sw);
int		rrb(t_data *s, char sw);
int		rrr(t_data *s, char sw);
int		sa(t_data *s, char sw);
int		sb(t_data *s, char sw);
int		ss(t_data *s, char sw);
///////////////////////////////////////////////////////////////////////////////]
//	F - TOOLS
int		wii_wrapper(char c);
int		exec_string(t_data *data, char *instructions, char sw2);
///////////////////////////////////////////////////////////////////////////////]
//	P - GIVE POSITION
void	give_position(t_data *s);
void	reevalue(t_data *s, t_num *num);
///////////////////////////////////////////////////////////////////////////////]
//	Q - ALGO 1
int		algo_1(t_data *data, int sw);
//	Q - ALGO
int		algo_aa(t_algo *a);
int		algo_bb(t_algo *a);
int		algo_ab(t_algo *a);
int		algo_ba(t_algo *a);
//	Q - ALGO
void	lets_rrr(t_algo *a, t_num *one, t_num *two, int bit);
//	Q - ALGO TOOLS
t_num	*assign_str_all(t_data *data);
int		assign_str(t_data *s, t_num *num);
void	fill_stru_algo(t_data *data, t_algo *a, t_num *num);
char	*smallest_str(int nb, ...);
int		is_in_order(t_data *s, t_num *previous, t_num *next);
///////////////////////////////////////////////////////////////////////////////]
//	T - TESTER
void	tester(t_data *data);
//	U - TESTER FUNCTION
void	function1(t_data *data, int i, int sw);
void	function2(t_data *data, int i, int sw);
void	function3(t_data *data, int sw);
///////////////////////////////////////////////////////////////////////////////]
//	Y - PRINT
void	print(t_data *data, int sw, int bit);
void	print_header(t_data *data, int bit, int sw);
void	print_stru_algo(t_algo *a);
void	print_stack(t_data *data, t_num *s, char sw);
///////////////////////////////////////////////////////////////////////////////]
//	Z - EXIT
void	ft_break(int num, char *string2, int cls, void *ptr);
int		end(t_data *s, char *message, int exit_code);
void	free_algos(t_data *data);
int		final_test(t_data *s);











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

	size = len(cmd);
	reverse = str("%s", cmd);
	if (!reverse)
		return (NULL);
	int i = -1;
	while (cmd[++i])
		reverse[size - i - 1] = reverse_c(cmd[i]);
	return (reverse);
}
///////////////////////////////////////////////////////////////////////////////]
*/











# define PA "\033[38;5;1mpa" RESET
# define PB "\033[38;5;27mpb" RESET

# define SA "\033[38;5;178msa" RESET
# define SB "\033[38;5;210msb" RESET
# define SS "\033[38;5;202mss" RESET

# define RA "\033[38;5;40mra" RESET
# define RB "\033[38;5;64mrb" RESET
# define RR "\033[38;5;58mrr" RESET

# define RRA "\033[38;5;129mrra" RESET
# define RRB "\033[38;5;141mrrb" RESET
# define RRR "\033[38;5;153mrrr" RESET

# define MSG_TOOBIG RED "error" GREEN " - yeah, about that.. THAT wont fit, sorry.\n" RESET
# define MSG_NOTNUM RED "error" GREEN " - yeahhh.. that's not a number.\n" RESET
# define MSG_DUPLICATE RED "error" GREEN " - DUPLICATE NUMBERS\n" RESET
# define MSG_BADCMD RED "error" GREEN " - That' aint no command i know of, boss..\n" RESET
# define MSG_NONUM RED "error" GREEN " - KRONK ! You forgot the numbers...\n> " RESET\
        "\e[7m""seq 25 99 | shuf -n 25 | tr '\\n' ' ' | sed -r 's/.$//'" RESET "\n"

# define UNDER_B "\033[48;5;4m" RESET
# define UNDER_R "\033[48;5;1m" RESET

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

