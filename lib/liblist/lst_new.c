/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lst_new.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/05 13:53:32 by nkuipers       #+#    #+#                */
/*   Updated: 2020/02/05 13:53:35 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "liblist.h"
#include <stdlib.h>

/*
**	Create a new node.
**
**	@param {void *} content - a pointer to the content of the node
**
**	@return {t_list *} - a pointer to the new node. NULL if an error occured
*/

t_list	*lst_new(void *content)
{
	t_list	*res;

	res = (t_list *)malloc(sizeof(t_list));
	if (!res)
		return (NULL);
	res->content = content;
	res->next = NULL;
	res->prev = NULL;
	return (res);
}
