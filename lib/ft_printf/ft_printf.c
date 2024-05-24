/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:06:22 by agallon           #+#    #+#             */
/*   Updated: 2024/05/13 19:14:14 by agallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

////////////////////////////////////////////////////////////
//	#	[scpiduxX%bofeESt]
t_func		g_function_pointer[] = {NULL,
	ft_string,
	ft_char,
	ft_pointer,
	ft_int,
	ft_int,
	ft_unsigned,
	ft_hexa,
	ft_hexa,
	ft_percent,
	ft_binary,
	ft_octal,
	ft_float,
	ft_scientific,
	ft_scientific,
	ft_string_hexa,
	ft_tab,
	NULL};

////////////////////////////////////////////////////////////
//	#	CREATE STRUCT
static int	f_1(const char *str, int *i, va_list args, int fd)
{
	t_flags	f;
	int		rtrn;

	if (fd < 0 || fd > 1024)
		return (-1);
	f_ini_struct(&f, fd);
	f_fill_struct(&str[*i + 1], &f, args);
	f_error_check(&f);
	if (f.error)
	{
		if (f.error == -2)
			return (-1);
		*i += write(fd, "%", 1);
		return (1);
	}
	if (g_function_pointer[wii_print(f.flag)])
		rtrn = g_function_pointer[wii_print(f.flag)](args, &f);
	*i += f.increment;
	return (rtrn);
}

////////////////////////////////////////////////////////////
//	#
int	put(const char *str, ...)
{
	va_list	args;
	int		i;
	int		sum;
	int		r;

	if (!str)
		return (-1);
	va_start(args, str);
	i = 0;
	sum = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			r = f_1(str, &i, args, 1);
			if (r < 0)
				return (-1);
			sum += r;
		}
		else
			sum += write(1, &str[i++], 1);
	}
	va_end(args);
	return (sum);
}

////////////////////////////////////////////////////////////
//	#
int	print_fd(int fd, const char *str, ...)
{
	va_list	args;
	int		i;
	int		sum;
	int		r;

	if (!str || fd < 0)
		return (-1);
	va_start(args, str);
	i = 0;
	sum = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			r = f_1(str, &i, args, fd);
			if (r < 0)
				return (-1);
			sum += r;
		}
		else
			sum += write(fd, &str[i++], 1);
	}
	va_end(args);
	return (sum);
}
