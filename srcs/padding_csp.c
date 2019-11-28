/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding_csp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 14:26:28 by vtran             #+#    #+#             */
/*   Updated: 2019/11/28 16:15:10 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*padding_with_minus(t_print **p, int len, char *src)
{
	t_print	*tmp;
	char	*ret;

	tmp = *p;
	ret = ft_strnew(tmp->pad);
	ft_memset(ret + len, ' ', tmp->pad - len);
	ft_memcpy(ret, src, len);
	free(src);
	return (ret);
}

char		*padding_with_dot(t_print **p, char *src)
{
	t_print	*tmp;
	char	*ret;

	tmp = *p;
	ret = ft_strnew(tmp->ppad);
	ft_memcpy(ret, src, tmp->ppad);
	free(src);
	return (ret);
}

char		*padding_no_flag(t_print **p, int len, char *src)
{
	t_print	*tmp;
	char	*ret;

	tmp = *p;
	ret = ft_strnew(tmp->pad);
	ft_memset(ret, ' ', tmp->pad - len);
	ft_memcpy(ret + tmp->pad - len, src, len);
	free(src);
	return (ret);
}
