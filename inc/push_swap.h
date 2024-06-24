/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 13:16:57 by agallon           #+#    #+#             */
/*   Updated: 2024/06/24 12:43:39 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"

//							//   CONTAINER FOR 1 NUMBER
typedef struct s_entry
{
//  const?
	struct s_entry	*above;
    struct s_entry	*below;

	struct s_entry	*target;
    struct s_entry	*hunter;

	int     num;
    int     num_index;
    
    int     size_s;//
    char    pile;//

    int     dist;//
    int     dist_p;
    int     dist_n;
    int     size_blk;// ??

    char    *algo;
    int     algo_sz;
    int     position;// give_position

}	t_entry;
//							//   STRUCT WITH BOTH A & B
typedef struct s_stacks
{
    struct s_entry *top_a;
    struct s_entry *top_b;
    struct s_entry *zero;

    char    **args;
    int     full_size;
    int     size_a;
    int     size_b;
}	t_stacks;
//							//   STRUCT FOR ALGORITHM
typedef struct s_algo
{
//  [B]------(T=b)(456)(d)---------><----(t=c)(0123)(N=a)--------------[A]
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


typedef int (*f_cmd)(t_stacks *stacks, char sw);
///////////////////////////////////////////////////////////////////////////////]
//	#	TOOLs - A - CREATE STRUCT
void	ini_stacks(int ac, char **av, t_stacks *stacks);
//	#	TOOLs - C - COMMANDS  
int		pb(t_stacks *s, char sw);
int		pa(t_stacks *s, char sw);
int		ra(t_stacks *s, char sw);
int		rb(t_stacks *s, char sw);
int		rr(t_stacks *s, char sw);
int		rra(t_stacks *s, char sw);
int		rrb(t_stacks *s, char sw);
int		rrr(t_stacks *s, char sw);
int		sa(t_stacks *s, char sw);
int		sb(t_stacks *s, char sw);
int		ss(t_stacks *s, char sw);

void    free_stack(t_entry *first);
void    assign_value(t_stacks *stacks);
t_entry *create_new_node(t_entry *last_node, char *arg, t_stacks *stacks);
t_entry *create_stack_a(int ac, char **av, t_stacks *stacks, int j);
void    ini_stacks(int ac, char **av, t_stacks *stacks);
//  2
// static void modulo_s(t_entry *current, int posi, int size_s);
// static void helper_give_posi(t_stacks *s, t_entry *current, char a, int i)

void    give_position(t_stacks *stacks);
//void static helper_give_posi(t_stacks *s, t_entry *current, char a, int i)
void    reevalue(t_stacks *s, t_entry *num);
void    assign_target(t_stacks *stacks);
////////////////////////////////////////////////////////////
//	#	TOOLs - B - PRINTING                              //
void    print_one_line(t_stacks *stacks, int sw, int bit);
void    print_stack(t_stacks *stacks, t_entry *s, int size_stack, char sw);
void    print_stack_b(t_stacks *stacks, t_entry *s, int size_stack, char sw);
void    print_header(t_stacks *stacks, int bit, int sw);
////////////////////////////////////////////////////////////
//	#	TOOLs - C - COMMANDS                              //
int    pb(t_stacks *s, char sw);
int    pa(t_stacks *s, char sw);
int    sa(t_stacks *s, char sw);
int    sb(t_stacks *s, char sw);
int    ss(t_stacks *s, char sw);
int    ra(t_stacks *s, char sw);
int    rb(t_stacks *s, char sw);
int    rr(t_stacks *s, char sw);
int    rra(t_stacks *s, char sw);
int    rrb(t_stacks *s, char sw);
int    rrr(t_stacks *s, char sw);
////////////////////////////////////////////////////////////
//	#	TOOLs - D - CONTROLS
int     function_cmd_string(t_stacks *stacks, char *instructions, char sw2);
void    function_cmd(t_stacks *stacks, int i, char sw2);
int     exit_all(t_stacks *s, char *message, int exit_code, void *ptr);

void    free_algos(t_stacks *stacks);
////////////////////////////////////////////////////////////
//	#	TOOLs - E - READING
int     reading_cmd(char *raw, t_stacks *stacks);
void    tester(t_stacks *stacks);
//////////////////////////////////////////////////////
//  #   TOOLs - F - TOOLS
int     wii_wrapper(char c);
int     wii_strikes_back(char *cmd, int *index);

int     ft_strchr(char *cmd_set, char *cmd);
int	    ft_atoi2(char *str, int *error);

char	*ft_strjoin(char *begin, char *append, int bit, t_stacks *s);
// char	*fjoin(int how_many_string, int bit_32, t_stacks *s, ...);

char    *string(char c, int num, t_stacks *s);
char    *str2(int c, int num, t_stacks *s);
//////////////////////////////////////////////////////
//  #   TOOLs - G - TESTING
int final_test(t_stacks *s);
void test_output(t_stacks *s);

//////////////////////////////////////////////////////
//  #   TOOLs - H - ALGO
t_entry    *find_target(t_stacks *stacks, t_entry *num);
// static int  help_modulo(t_stacks *s, t_entry *previous, t_entry *next);
// static void helper_block_size(t_stacks *stacks, t_algo *a);
void    fill_stru_algo(t_stacks *stacks, t_algo *a, t_entry *num);
void    print_stru_algo(t_algo *algo);
t_entry *assign_str_all(t_stacks *stacks);
int  help_modulo(t_stacks *s, t_entry *previous, t_entry *next);

//////////////////////////////////////////////////////
//  #   TOOLs - I - ALGO
int algo_aa(t_algo *a);
int algo_ab(t_algo *a);
int algo_ba(t_algo *a);
int algo_bb(t_algo *a);
int assign_str(t_stacks *s, t_entry *num);

//////////////////////////////////////////////////////
//  #   MAIN DEBUG
void    function1(t_stacks *stacks, int i);
void    function2(t_stacks *stacks, int i);
void    function3(t_stacks *stacks);
void    print_temp(t_stacks *stacks, t_entry *s, int size_stack);



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

#endif

