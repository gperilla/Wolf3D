/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 23:46:50 by gperilla          #+#    #+#             */
/*   Updated: 2017/11/13 10:42:56 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new;

	if (!(new = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	new->content = (void *)malloc(content_size);
	if (content == NULL)
		new->content = NULL;
	else
		ft_memcpy(new->content, content, content_size);
	if (!new->content)
		new->content_size = 0;
	else
		new->content_size = content_size;
	new->next = NULL;
	return (new);
}
