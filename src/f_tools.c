#include "push_swap.h"

int wii_wrapper(char c);
int wii_strikes_back(char *cmd, int *index);
int ft_strchr(char *cmd_set, char *cmd);
int	ft_atoi2(char *str, int *error);
char	*ft_strjoin(char *begin, char *append, int bit, t_stacks *s);

//////////////////////////////////////////////////////
//  #   takes in "0123456789a " -> return index
//  #   [0-9x] -> [0-10]
//  #   [ \nabpsr] ->[-2... -7]
//  #   else -1
int wii_wrapper(char c)
{
    int i;

    if (c == 'A')
        return (0);
    if (c == 'B')
        return (1);
    i = wii(c, "0123456789: \nabpsr");// '9'  + 1 = ':'
    if (i < 11)
        return (i);
    return (9 - i);
}

//////////////////////////////////////////////////////
//  #   WhatIsIt - takes pointer to "pb\npa\n" and update index, return -1 error
//      return [0-10]
int wii_strikes_back(char *cmd, int *index)
{
    int i;
    int rtrn;

    i = 0;
    while (wii_wrapper(cmd[i]) < -3)
        i++;
    *index += i - 1;
    if (i == 2 && (rtrn = ft_strchr("pb\npa\nsa\nsb\nss\nra\nrb\nrr\n", cmd)) >= 0)
        return (rtrn / 3);
    else if (i == 3 && (rtrn = ft_strchr("rra\nrrb\nrrr\n", cmd)) >= 0)
        return (rtrn / 4 + 8);
    return (-1);
}


//////////////////////////////////////////////////////
//  #   STRCHR - expects a single "pb\n"
int ft_strchr(char *cmd_set, char *cmd)
{
	int		i;
    int     j;
	int     ptr;

	i = 0;
	while (cmd_set[i])
	{
		ptr = i;
        j = 0;
        while (cmd[j] && cmd_set[i] == cmd[j])
		{
            (i++, j++);
            if (!cmd[j] || cmd[j] == ' ' || cmd[j] == '\n')
                return (ptr);
        }
		i++;
	}
	return (-1);
}

//////////////////////////////////////////////////////
//  #   ATOI, CHECKS UNVALID NUMBER ARGUMENTS
//  return &error = -5; number too big
//  return &error = -4; not a number
int	ft_atoi2(char *str, int *error)
{
	long long	rtrn;
    int		    i;
	int         sign;

	i = 0;
	rtrn = 0;
    sign = 1;
    if (str[0] == '-')
        (sign = -1, i++);
    while (str[i] >= '0' && str[i] <= '9')
        rtrn = rtrn * 10 + (str[i++] - '0');
    rtrn *= sign;
    if (rtrn > 2147483647 || rtrn < -2147483648)
        *error = -5;
    if (!(!str[i] || str[i] == ' ' || str[i] == '\n'))
         *error = -4;
	return ((int)rtrn);
}

//////////////////////////////////////////////////////
//  #   join the read bits
//  bit 1 = begin malloc'd
//  bit 2 = append malloc'd
char	*ft_strjoin(char *begin, char *append, int bit, t_stacks *s)
{
	int 	i;
	int 	ptr;
	char	*str;

    ptr = 0;
    if ((str = (char *)malloc(len(begin) + len(append) + 1)))
    {
        if (!(i = 0) && begin && (--ptr))
            while (begin[++ptr])
                str[ptr] = begin[ptr];
        if (append && (i = -1))
            while (append[++i])
                str[ptr + i] = append[i];
        str[ptr + i] = '\0';
    }
    if (bit & 1 && begin)
        free(begin);
    if ((bit >> 1) & 1 && append)
        free(append);
    if (!str)
        exit_all(s, MSG_MALLOC, -2, NULL);
    return(str);
}
