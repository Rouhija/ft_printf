/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_nbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 14:28:40 by vtran             #+#    #+#             */
/*   Updated: 2019/11/28 16:22:52 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*handle_signed(t_print **p)
{
	if ((*p)->flags & F_LONG)
		return (ft_itoa(va_arg((*p)->ap, long)));
	else if ((*p)->flags & F_LLONG)
		return (ft_itoa(va_arg((*p)->ap, long long)));
	else if ((*p)->flags & F_CHAR)
		return (ft_itoa((char)va_arg((*p)->ap, int)));
	else if ((*p)->flags & F_SHORT)
		return (ft_itoa((short)va_arg((*p)->ap, int)));
	else
		return (ft_itoa(va_arg((*p)->ap, int)));
}

char		*handle_unsigned(t_print **p)
{
	int			base;
	uint64_t	nb;

	if ((*p)->c == 'u')
		base = 10;
	else if ((*p)->c == 'b')
		base = 2;
	else if ((*p)->c == 'o')
		base = 8;
	else
		base = 16;
	if ((*p)->flags & F_LONG)
		nb = (uint64_t)va_arg((*p)->ap, unsigned long int);
	else if ((*p)->flags & F_LLONG)
		nb = (uint64_t)va_arg((*p)->ap, unsigned long long int);
	else if ((*p)->flags & F_CHAR)
		nb = (unsigned char)va_arg((*p)->ap, unsigned int);
	else if ((*p)->flags & F_SHORT)
		nb = (unsigned short)va_arg((*p)->ap, unsigned int);
	else
		nb = (uint64_t)va_arg((*p)->ap, unsigned int);
	return (ft_itoa_base(nb, base));
}

char		*handle_double(t_print **p)
{
	int flag;

	flag = 0;
	if (!((*p)->flags & F_DOT))
		(*p)->ppad = 6;
	if ((*p)->flags & F_DOUBLE)
		return (ftoa(va_arg((*p)->ap, long double), (*p)->ppad, p));
	else
		return (ftoa(va_arg((*p)->ap, double), (*p)->ppad, p));
}

int			ft_count_digits_s(int64_t n, int base)
{
	if (n < (int64_t)base)
		return (1);
	else
		return (ft_count_digits_s(n / base, base) + 1);
}
