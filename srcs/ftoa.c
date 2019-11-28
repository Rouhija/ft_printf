/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 18:43:16 by srouhe            #+#    #+#             */
/*   Updated: 2019/11/28 16:10:05 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** check leading zeros after decimal point and return count
*/

static int			zp(double db, int prec)
{
	int			i;
	uint64_t	ints;

	i = 0;
	db = db < 0 ? -(db) : db;
	ints = (uint64_t)db;
	while (i < prec - 1)
	{
		db *= 10;
		ints *= 10;
		if ((uint64_t)db != ints)
			break ;
		i++;
	}
	return (i);
}

/*
** do rounding by getting the next decimal after defined precision
*/

static int			rounding(int prec, long double db)
{
	db = db < 0 ? -(db) : db;
	if (prec < 18)
		return ((int64_t)(db * ft_pow(10, prec + 1)) % 10 >= 5 ? 1 : 0);
	while (--prec && prec >= 5)
	{
		db *= 10;
		db -= (uint64_t)db;
	}
	return ((int)(db * ft_pow(10, prec + 1)) >= 5 ? 1 : 0);
}

/*
** handle doubles with over long precision
*/

static char			*long_db(long double db, int prec)
{
	int				i;
	int				init;
	char			*tmp;

	i = prec - 18;
	db *= ft_pow(10, 18);
	init = (long long)db;
	tmp = ft_itoa((long long)db);
	db -= (long long)db;
	if (i > 0)
		db *= ft_pow(10, i);
	if ((db - (long long)db) * 10 >= 5)
		db += 1;
	if (i > 0 && init == 0)
		tmp = ft_itoa((long long)db);
	else if (i > 0)
		tmp = ft_strjoin(tmp, ft_itoa((long long)db));
	return (tmp);
}

/*
** Special case when precision is explicitly set to 0
*/

static char			*zero_prec(long double nb, t_print **p)
{
	char	*r;

	r = ft_itoa(nb > 0 ? nb + 0.5 : nb - 0.5);
	r = nb < 0 && nb > -1 ? ft_strjoin(ft_strdup("-"), r) : r;
	if ((*p)->flags & F_HASH)
		r = ft_strjoin(r, ft_strdup("."));
	return (r);
}

char				*ftoa(long double nb, int prec, t_print **p)
{
	long long		ints;
	long double		dcml;
	long double		tmpdb;
	char			*r;

	if (((*p)->flags & F_DOT) && (*p)->ppad == 0)
		return (zero_prec(nb, p));
	ints = (int64_t)nb;
	dcml = ABS(nb - (long double)ints);
	tmpdb = dcml;
	r = ft_strjoin(ft_itoa(ints), ft_strdup("."));
	r = ft_strjoin(r, ft_memset(ft_strnew(zp(nb, prec)), '0', zp(nb, prec)));
	dcml *= ft_pow(10, prec);
	dcml += rounding(prec, tmpdb);
	if (ft_count_digits_s((int64_t)dcml, 10) > prec)
	{
		ints = ft_atoi(r) > 0 ? ft_atoi(r) + 1 : ft_atoi(r) - 1;
		r = ft_strjoin(ft_itoa(ints), ft_strdup("."));
		r = ft_strjoin(r, ft_memset(ft_strnew(prec), '0', prec));
	}
	else
		r = prec > 18 ? ft_strjoin(r, long_db(tmpdb, prec))
		: ft_strjoin(r, ft_itoa((uint64_t)dcml));
	r = nb < 0 && nb > -1 ? ft_strjoin(ft_strdup("-"), r) : r;
	return (r);
}
