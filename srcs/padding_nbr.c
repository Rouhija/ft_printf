/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding_nbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 17:52:03 by vtran             #+#    #+#             */
/*   Updated: 2019/11/27 17:13:00 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*minus(t_print **p, char *str1, int len, char *str2)
{
	ft_memcpy(str1, str2, len);
	ft_memset(str1 + len, ' ', (*p)->pad - len);
	if (str2 != NULL)
		free(str2);
	return (str1);
}

static char	*zero_no_space(t_print **p, char *str1, int len, char *str2)
{
	ft_memset(str1, '0', (*p)->pad - len);
	ft_memcpy(str1 + (*p)->pad - len, str2, len);
	if (str2 != NULL)
		free(str2);
	return (str1);
}

static char	*normal_padding(t_print **p, char *str1, int len, char *str2)
{
	if ((*p)->c == 'o' && (*p)->flags & F_DOT && \
			!((*p)->flags & F_HASH) && (*p)->ppad == 0)
	{
		ft_memset(str1, ' ', (*p)->pad);
		free(str2);
		return (str1);
	}
	ft_memset(str1, ' ', (*p)->pad - len);
	ft_memcpy(str1 + (*p)->pad - len, str2, len);
	if (str2 != NULL)
		free(str2);
	return (str1);
}

static char	*padding_with_flag(t_print **p, char *str1, int len, char *str2)
{
	if ((*p)->c == 'x' || (*p)->c == 'X')
	{
		ft_memset(str1 + 2, '0', (*p)->pad - len);
		ft_memcpy(str1 + (*p)->pad - len + 2, str2 + 1, len);
	}
	else
	{
		ft_memset(str1 + 1, '0', (*p)->pad - len);
		ft_memcpy(str1 + (*p)->pad - len + 1, str2, len);
	}
	if (str2 != NULL)
	{
		str2--;
		free(str2);
	}
	return (str1);
}

char		*padding(t_print **p, char *pad_thai)
{
	int		len;
	char	*str;
	int		flag;

	flag = 0;
	len = ft_strlen(pad_thai);
	str = ft_strnew((*p)->pad);
	if ((*p)->flags & F_MINUS)
		return (minus(p, str, len, pad_thai));
	if ((*p)->flags & F_ZERO)
		flag = if_symbols_move(p, &pad_thai, str, len);
	flag == 1 ? pad_thai++ : pad_thai;
	if ((*p)->flags & F_ZERO && (*p)->flags & F_DOT && (*p)->c != 'f')
		return (normal_padding(p, str, len, pad_thai));
	if (flag == 1)
		return (padding_with_flag(p, str, len, pad_thai));
	else if ((*p)->flags & F_ZERO && !((*p)->flags & F_SPACE))
		return (zero_no_space(p, str, len, pad_thai));
	return (normal_padding(p, str, len, pad_thai));
}
