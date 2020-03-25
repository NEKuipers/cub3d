/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   liblist.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/05 13:53:14 by nkuipers       #+#    #+#                */
/*   Updated: 2020/02/05 13:53:15 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#ifndef LIBLIST_H
# define LIBLIST_H
#include <stddef.h>

typedef struct s_list	t_list;

struct					s_list
{
	void	*content;
	t_list	*next;
	t_list	*prev;
};

t_list	*lst_new(void *content);
t_list	*lst_new_back(t_list **node, void *content);
void	lst_new_front(t_list **node, void *content);
void	lst_remove(t_list *node, void (*free_func)(void *));
void	lst_reverse(t_list **node);
size_t	lst_size(t_list *node);
void	lst_foreach(t_list *node, void (*func)(void *));

#endif
