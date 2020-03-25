/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lst_size.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/05 13:53:50 by nkuipers       #+#    #+#                */
/*   Updated: 2020/02/05 13:53:52 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "liblist.h"

/*
**	Count the amount of nodes in a list.
**
**	@param {t_list *} node - the first node of the list
**
**	@return {size_t}
*/

size_t	lst_size(t_list *node)
{
	size_t	res;

	res = 0;
	while (node)
	{
		node = node->next;
		res++;
	}
	return (res);
}
