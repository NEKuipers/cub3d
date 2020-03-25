/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lst_remove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/05 13:53:38 by nkuipers       #+#    #+#                */
/*   Updated: 2020/02/05 13:53:40 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "liblist.h"
#include <stdlib.h>

/*
**	Remove a node from a list.
**
**	@param {t_list *} node - the node to remove
**	@param {void (*)(void *)} free_func - the function which is called with the
**		nodes content as argument, to free it properly.
*/

void	lst_remove(t_list *node, void (*free_func)(void *))
{
	if (!node)
		return ;
	free_func(node->content);
	if (node->prev)
		node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;
	free(node);
}
