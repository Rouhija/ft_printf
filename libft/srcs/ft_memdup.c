/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 14:11:15 by srouhe            #+#    #+#             */
/*   Updated: 2019/10/18 14:17:10 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memdup(void const *content, size_t content_size)
{
	unsigned char	*p1;
	unsigned char	*p2;
	void			*r;

	if (!(r = ft_memalloc(content_size)))
		return (NULL);
	p1 = (unsigned char *)content;
	p2 = (unsigned char *)r;
	while (*p1)
		*p2++ = *p1++;
	return (r);
}
