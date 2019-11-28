/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 18:40:31 by srouhe            #+#    #+#             */
/*   Updated: 2019/11/28 14:38:38 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	octal_special_case(t_print **p, char *str)
{
	if ((*p)->ppad == 0 && (*p)->flags & F_HASH && \
	(*p)->c == 'o' && ft_atoi(str) == 0)
		return (1);
	return (0);
}

/*
** precision magic
*/

char		*precision(t_print **p, char *str)
{
	int		len;
	int		flag;

	if (octal_special_case(p, str))
		return (ft_memset(ft_strnew(1), '0', 1));
	if ((*p)->ppad == 0 && ft_strchr("diouxX", (*p)->c) && ft_atoi(str) == 0)
		return (ft_strnew(0));
	if ((*p)->ppad < (int)ft_strlen(str))
		return (str);
	flag = 0;
	len = (*p)->ppad - ft_strlen(str);
	if (str[0] == '-')
	{
		flag = 1;
		str = ft_strsub(str, 1, ft_strlen(str) - 1);
		len++;
	}
	if (len > 0 && (*p)->c == 'o' && (*p)->flags & F_HASH &&\
		check_if_zeros(str))
		str = ft_strjoin(ft_memset(ft_strnew(len), '0', len - 1), str);
	else
		str = ft_strjoin(ft_memset(ft_strnew(len), '0', len), str);
	if (flag)
		str = ft_strjoin(ft_strdup("-"), str);
	return (str);
}

/*
** adding space if space after %
*/

char		*space(t_print **p, char *str)
{
	int		flag;

	flag = 0;
	if (str[0] == '-' || str[0] == '+')
		flag = 1;
	if (flag == 0 && ((*p)->pad <= (int)ft_strlen(str) ||\
		(*p)->flags & F_MINUS || (*p)->flags & F_ZERO))
		return (ft_strjoin(ft_strdup(" "), str));
	return (str);
}

/*
** pad the buffer with zeros or spaces, first leading then trailing
*/

int			if_symbols_move(t_print **p, char **srcs, char *str, int len)
{
	char	*tmp;

	tmp = *srcs;
	if ((*p)->pad < len || ((*p)->pad > len &&\
	(*p)->ppad == 0) || (*p)->c == 'f')
	{
		if (tmp[0] == '-' || tmp[0] == '+')
		{
			str[0] = tmp[0] == '-' ? '-' : '+';
			return (1);
		}
		else if ((*p)->flags & F_SPACE)
		{
			str[0] = ' ';
			return (1);
		}
		else if (((*p)->c == 'x' || (*p)->c == 'X') &&\
		(*p)->flags & F_HASH && check_if_zeros(tmp))
		{
			str[0] = '0';
			str[1] = tmp[1] == 'x' ? 'x' : 'X';
			return (1);
		}
	}
	return (0);
}

/*
** adding prefix
*/

char		*ox_prefix(t_print **p, char *str)
{
	if (check_if_zeros(str) && (*p)->flags & F_HASH)
	{
		if ((*p)->c == 'x')
			str = ft_strjoin(ft_strdup("0x"), str);
		else if ((*p)->c == 'X')
			str = ft_strjoin(ft_strdup("0X"), str);
		else if ((*p)->c == 'o')
			str = ft_strjoin(ft_strdup("0"), str);
	}
	if ((*p)->c == 'X')
		str = ft_strupper(str);
	return (str);
}
