/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_csp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 18:43:07 by srouhe            #+#    #+#             */
/*   Updated: 2019/11/27 21:00:05 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			pointer(t_print **p)
{
	t_print		*tmp;
	char		*str;
	int			len;
	char		*temp;

	str = ft_strdup("0x");
	tmp = *p;
	temp = ft_itoa_base(va_arg(tmp->ap, long long), 16);
	len = (int)ft_strlen(temp);
	if (tmp->ppad > len)
		str = ft_strjoin(str, ft_memset(ft_strnew(tmp->ppad - len),
						'0', tmp->ppad - len));
	if (!((*p)->ppad == 0 && tmp->flags & F_DOT && ft_atoi(temp) == 0))
		str = ft_strjoin(str, temp);
	len = (int)ft_strlen(str);
	if (tmp->flags & F_MINUS && tmp->pad > len)
		str = padding_with_minus(p, len, str);
	else if (tmp->pad > len)
		str = padding_no_flag(p, len, str);
	append_buffer(p, str, ft_strlen(str));
}

void			add_string(t_print **p)
{
	t_print		*tmp;
	char		*str1;
	char		*str;
	int			len;

	tmp = *p;
	if (!(str1 = va_arg(tmp->ap, char *)))
		str1 = "(null)";
	str = ft_strdup(str1);
	len = (int)ft_strlen(str);
	if (tmp->flags & F_DOT && tmp->ppad < len)
	{
		str = padding_with_dot(p, str);
		len = ft_strlen(str);
	}
	if (tmp->flags & F_MINUS && tmp->pad > len)
		str = padding_with_minus(p, len, str);
	else if (tmp->pad > len)
		str = padding_no_flag(p, len, str);
	append_buffer(p, str, ft_strlen(str));
}

void			add_char(t_print **p)
{
	char		c;
	char		*str;
	t_print		*tmp;
	int			len;

	tmp = *p;
	c = va_arg(tmp->ap, int);
	str = (char *)malloc(sizeof(char) * 2);
	str[0] = c;
	str[1] = '\0';
	if (tmp->flags == 0 && 1 < tmp->pad)
		str = padding_no_flag(p, 1, str);
	else if (tmp->flags & F_MINUS && tmp->pad > 1)
		str = padding_with_minus(p, 1, str);
	len = (*p)->pad > 1 ? (*p)->pad : 1;
	append_buffer(p, str, len);
}

void			add_wchar(t_print **p)
{
	t_print		*tmp;
	char		*str;
	int			len;

	tmp = *p;
	str = ft_putchar_w(va_arg(tmp->ap, wint_t));
	len = ft_strlen(str);
	if (tmp->flags & F_MINUS && tmp->pad > len)
		str = padding_with_minus(p, len, str);
	else if (len < tmp->pad)
		str = padding_no_flag(p, len, str);
	append_buffer(p, str, ft_strlen(str));
}

void			add_wstring(t_print **p)
{
	t_print		*tmp;
	char		*str;
	int			len;

	tmp = *p;
	if (!(str = ft_putstr_w(va_arg(tmp->ap, void *))))
	{
		str = ft_strnew(6);
		ft_memcpy(str, "(null)", 6);
	}
	len = ft_strlen(str);
	if (tmp->flags & F_DOT && tmp->ppad < len)
	{
		str = padding_with_dot(p, str);
		len = ft_strlen(str);
	}
	if (tmp->flags & F_MINUS && tmp->pad > len)
		str = padding_with_minus(p, len, str);
	else if (len < tmp->pad)
		str = padding_no_flag(p, len, str);
	append_buffer(p, str, ft_strlen(str));
}
