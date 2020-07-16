/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/28 16:18:38 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/07/16 14:57:06 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t		i;
	const char	*cs;
	const char	*ptr;

	cs = s;
	i = 0;
	ptr = 0;
	while (i < n)
	{
		if (cs[i] == c)
		{
			ptr = &cs[i];
			break ;
		}
		i++;
	}
	return ((char *)ptr);
}
