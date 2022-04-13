/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/12 17:20:59 by pvan-dij      #+#    #+#                 */
/*   Updated: 2021/10/12 20:17:28 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*l_list;

	l_list = (t_list *)malloc(sizeof(t_list));
	if (!l_list)
		return (NULL);
	l_list->content = content;
	l_list->next = NULL;
	return (l_list);
}
