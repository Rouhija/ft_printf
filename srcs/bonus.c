/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 12:42:46 by srouhe            #+#    #+#             */
/*   Updated: 2019/11/28 16:30:55 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		occurrences(char *s1, char *s2)
{
	int i;

	i = 0;
	while ((s1 = ft_strstr(s1, s2)))
	{
		i++;
		s1 += ft_strlen(s2);
	}
	return (i);
}

static char		*ft_replace(t_print **p, char *org, char *rep, char *wth)
{
	int		i;
	char	*r;
	char	*tmp;
	char	*head;

	tmp = org;
	head = org;
	i = occurrences(tmp, rep);
	r = ft_strnew(ft_strlen(org) + (ft_strlen(wth) - ft_strlen(rep)) * i);
	while ((tmp = ft_strstr(tmp, rep)))
	{
		r = ft_strncat(r, org, ft_strlen(org) - ft_strlen(tmp));
		r = ft_strcat(r, wth);
		tmp += ft_strlen(rep);
		org = tmp;
	}
	r = ft_strjoin(r, ft_strdup(org));
	(*p)->len = ft_strlen(r);
	free(head);
	return (r);
}

void			parse_colors(t_print **p)
{
	if (ft_strstr((*p)->buf, "{black}"))
		(*p)->buf = ft_replace(p, (*p)->buf, "{black}", BLACK);
	if (ft_strstr((*p)->buf, "{red}"))
		(*p)->buf = ft_replace(p, (*p)->buf, "{red}", RED);
	if (ft_strstr((*p)->buf, "{green}"))
		(*p)->buf = ft_replace(p, (*p)->buf, "{green}", GREEN);
	if (ft_strstr((*p)->buf, "{yellow}"))
		(*p)->buf = ft_replace(p, (*p)->buf, "{yellow}", YELLOW);
	if (ft_strstr((*p)->buf, "{blue}"))
		(*p)->buf = ft_replace(p, (*p)->buf, "{blue}", BLUE);
	if (ft_strstr((*p)->buf, "{magneta}"))
		(*p)->buf = ft_replace(p, (*p)->buf, "{magneta}", MAGNETA);
	if (ft_strstr((*p)->buf, "{cyan}"))
		(*p)->buf = ft_replace(p, (*p)->buf, "{cyan}", CYAN);
	if (ft_strstr((*p)->buf, "{white}"))
		(*p)->buf = ft_replace(p, (*p)->buf, "{white}", WHITE);
	if (ft_strstr((*p)->buf, "{normal}"))
		(*p)->buf = ft_replace(p, (*p)->buf, "{normal}", NORMAL);
}
