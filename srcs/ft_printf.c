/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 12:58:13 by srouhe            #+#    #+#             */
/*   Updated: 2019/11/28 16:22:31 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_print		*initialize(void)
{
	t_print		*p;

	if (!(p = ft_memalloc(sizeof(t_print))))
		return (NULL);
	p->buf = ft_strnew(0);
	p->flags = 0;
	p->c = 0;
	p->ppad = 0;
	p->pad = 0;
	p->len = 0;
	return (p);
}

static void			free_mem(t_print **p)
{
	if (p && *p)
	{
		free((*p)->buf);
		free(*p);
		*p = NULL;
	}
}

static void			parse(t_print **p)
{
	t_print	*tmp;

	tmp = parse_flags(p);
	if (*tmp->fmt == '%')
		tmp->buf = tmp->pad ? ft_memjoin(p, padding(&tmp, \
		ft_memset(ft_strnew(1), '%', 1)), tmp->pad) \
		: ft_memjoin(p, ft_strdup("%"), 1);
	else if (ft_strchr("csp", tmp->c))
		parse_csp(p);
	else if (ft_strchr("diouxXf", tmp->c))
		parse_diouxx(p);
	tmp->fmt++;
}

int					ft_printf(const char *restrict format, ...)
{
	t_print		*p;
	char		*tmp;
	int			i;

	if (!(p = initialize()))
		return (0);
	p->fmt = (char *)format;
	va_start(p->ap, format);
	while (ft_strchr(p->fmt, '%'))
	{
		tmp = ft_strsub(ft_strdup(p->fmt), 0, ft_strchr(p->fmt, '%') - p->fmt);
		p->buf = ft_memjoin(&p, tmp, ft_strlen(tmp));
		p->fmt = (p->fmt + ft_strchr_len(p->fmt, '%') + 1);
		parse(&p);
	}
	tmp = ft_strdup(p->fmt);
	p->buf = ft_memjoin(&p, tmp, ft_strlen(tmp));
	parse_colors(&p);
	write(1, p->buf, p->len);
	va_end(p->ap);
	i = p->len;
	free_mem(&p);
	return (i);
}
