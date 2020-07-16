/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/28 16:13:02 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/07/16 14:57:21 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const unsigned char	*csrc;
	unsigned char		*cdst;
	size_t				i;

	cdst = dst;
	csrc = src;
	if (cdst < csrc)
	{
		i = 0;
		while (i < len)
		{
			cdst[i] = csrc[i];
			i++;
		}
	}
	else if (cdst > csrc)
	{
		i = len;
		while (i > 0)
		{
			cdst[i - 1] = csrc[i - 1];
			i--;
		}
	}
	return (dst);
}
