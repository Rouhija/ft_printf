/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 18:46:11 by srouhe            #+#    #+#             */
/*   Updated: 2019/11/28 16:23:05 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int			check(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

static void			parser(t_print **p, char *args)
{
	while (*args)
	{
		if (*args == '#' || *args == ' ')
			(*p)->flags |= *args == '#' ? F_HASH : F_SPACE;
		else if (*args == '0' && (*p)->pad == 0)
			(*p)->flags |= F_ZERO;
		else if (*args == '-' || *args == '+')
			(*p)->flags |= *args == '-' ? F_MINUS : F_PLUS;
		else if (*args == '*')
			(*p)->flags |= (*p)->flags & F_DOT ? F_DWILD : F_PWILD;
		else if (*args == 'h' && !((*p)->flags & F_CHAR))
			(*p)->flags |= *(args + 1) == 'h' ? F_CHAR : F_SHORT;
		else if (*args == 'l' && !((*p)->flags & F_LLONG))
			(*p)->flags |= *(args + 1) == 'l' ? F_LLONG : F_LONG;
		else if (*args == 'L')
			(*p)->flags |= F_DOUBLE;
		else if (*args == '.')
		{
			(*p)->flags |= F_DOT;
			(*p)->ppad = ft_atoi(args + 1);
		}
		else if (ft_isdigit(*args) && (*p)->pad == 0 && !((*p)->flags & F_DOT))
			(*p)->pad = ft_atoi(args);
		args++;
	}
}

t_print				*parse_flags(t_print **p)
{
	int		i;
	t_print	*tmp;
	char	*args;

	i = 0;
	tmp = *p;
	while (!check(tmp->fmt[i], CONVERSION) && tmp->fmt[i + 1])
		i++;
	tmp->c = tmp->fmt[i];
	args = ft_strsub(ft_strdup(tmp->fmt), 0, i);
	(*p)->flags = 0;
	parser(p, args);
	free(args);
	tmp->fmt += i;
	return (tmp);
}

void				parse_csp(t_print **p)
{
	t_print	*tmp;

	if ((*p)->flags & F_PWILD || (*p)->flags & F_DWILD)
		wildcard(p);
	tmp = *p;
	if (tmp->c == 'p')
		pointer(&tmp);
	else if (tmp->c == 's' && tmp->flags & F_LONG)
		add_wstring(p);
	else if (tmp->c == 's')
		add_string(p);
	else if (tmp->c == 'c' && tmp->flags & F_LONG)
		add_wchar(p);
	else
		add_char(p);
}

void				parse_diouxx(t_print **p)
{
	char			*r;

	if ((*p)->flags & F_PWILD || (*p)->flags & F_DWILD)
		wildcard(p);
	if (check((*p)->c, "di"))
		r = handle_signed(p);
	else if (check((*p)->c, "ouxXb"))
		r = handle_unsigned(p);
	else if ((*p)->c == 'f')
		r = handle_double(p);
	if ((*p)->flags & F_DOT)
		r = precision(p, r);
	if (check((*p)->c, "oxX"))
		r = ox_prefix(p, r);
	if ((*p)->flags & F_PLUS && !(check((*p)->c, "ouxXb")))
		r = add_sign(r);
	if ((*p)->flags & F_SPACE && !(check((*p)->c, "ouxXb")))
		r = space(p, r);
	if ((*p)->pad > (int)ft_strlen(r))
		r = padding(p, r);
	append_buffer(p, r, ft_strlen(r));
}
