/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   T_tester.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalipso <kalipso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:09:40 by kalipso           #+#    #+#             */
/*   Updated: 2024/08/18 01:49:08 by kalipso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		tester(t_data *data);
static int	reading_cmd(char *raw, t_data *data);
static void	helper_73(t_data *data, char *raw, int *error, int *sw);
static int	wii_strikes_back(char *cmd, int *index);

///////////////////////////////////////////////////////////////////////////////]
//			TESTER
//	#	main tester, ask for raw, execute, loop out when [ctrl-D]
void	tester(t_data *data)
{
	char	*raw;
	int		sw;
	int		error;

	sw = 0;
	while (1)
	{
		raw = gnl(0);
		if (!raw)
			break ;
		error = wii_wrapper(raw[0]);
		if (error >= 0)
			exec_string(data, raw, 0);
		else if (error <= -4)
			error = reading_cmd(raw, data);
		helper_73(data, raw, &error, &sw);
		if (error == -1)
			put("\n\033[38;5;94mtrying:" RESET " %s\n" MSG_BADCMD, raw);
		free_s(raw);
	}
}

static void	helper_73(t_data *data, char *raw, int *error, int *sw)
{
	if (raw[0] == '*' && (*error)++)
		*sw ^= 1;
	print_header(data, 0b111, *sw);
	if (raw[0] == '-' && (*error)++)
		function1(data, atoi_v(&raw[1]), *sw);
	else if (raw[0] == '+' && (*error)++)
		function2(data, atoi_v(&raw[1]), *sw);
	else if (raw[0] == '.' && (*error)++)
		function3(data, *sw);
}

///////////////////////////////////////////////////////////////////////////////]
//	#	takes raw input, look for 'pb\n', execute
//	return -1 on bad command
//  return 0 on EOF
static int	reading_cmd(char *raw, t_data *data)
{
	int	i;
	int	cmd;

	i = -1;
	while (raw[++i])
	{
		cmd = wii_wrapper(raw[i]);
		if (cmd > -2)
			break ;
		if (cmd < -3)
		{
			cmd = wii_strikes_back(&raw[i], &i);
			if (cmd < 0)
				return (-1);
			data->controls[cmd](data, 0);
		}
	}
	return (0);
}

///////////////////////////////////////////////////////////////////////////////]
//  #   WhatIsIt - takes pointer to "pb\npa\n" and update index, return -1 error
//      return [0-10]
static int	wii_strikes_back(char *cmd, int *index)
{
	int	i;
	int	rtrn;

	i = 0;
	while (wii_wrapper(cmd[i]) < -3)
		i++;
	*index += i - 1;
	if (i == 2)
	{
		rtrn = find_str("pb\npa\nsa\nsb\nss\nra\nrb\nrr\n", cmd);
		if (rtrn >= 0)
			return (rtrn / 3);
	}
	else if (i == 3)
	{
		rtrn = find_str("rra\nrrb\nrrr\n", cmd);
		if (rtrn >= 0)
			return (rtrn / 4 + 8);
	}
	return (-1);
}
