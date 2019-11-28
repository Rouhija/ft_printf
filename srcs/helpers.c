/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 18:06:55 by vtran             #+#    #+#             */
/*   Updated: 2019/11/28 14:37:26 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_memjoin(t_print **p, char *append_this, int len)
{
	char	*tmp;

	tmp = ft_strnew((*p)->len + len);
	ft_memcpy(tmp, (*p)->buf, (*p)->len);
	ft_memcpy(tmp + (*p)->len, append_this, len);
	(*p)->len += len;
	free((*p)->buf);
	free(append_this);
	return (tmp);
}

int			check_if_zeros(char *str)
{
	while (*str)
	{
		if (*str != '0')
			return (1);
		str++;
	}
	return (0);
}

void		append_buffer(t_print **p, char *append_this, int len)
{
	(*p)->buf = ft_memjoin(p, append_this, len);
	(*p)->pad = 0;
	(*p)->ppad = 0;
}

void		wildcard(t_print **p)
{
	int		nb;

	if ((*p)->flags & F_PWILD)
	{
		nb = va_arg((*p)->ap, int);
		if (nb < 0)
		{
			(*p)->flags |= F_MINUS;
			nb *= -1;
		}
		(*p)->pad = (*p)->pad == 0 ? nb : (*p)->pad;
	}
	if ((*p)->flags & F_DWILD)
	{
		nb = va_arg((*p)->ap, int);
		if (nb < 0)
		{
			(*p)->flags ^= F_DOT;
			nb = 0;
		}
		(*p)->ppad = nb;
	}
}

char		*add_sign(char *str)
{
	if (*str != '-')
	{
		str = ft_strjoin(ft_strdup("+"), str);
		return (str);
	}
	return (str);
}
