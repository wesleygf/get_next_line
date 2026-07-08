/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wgolbert <wgolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 23:43:31 by wgolbert          #+#    #+#             */
/*   Updated: 2026/07/02 23:43:31 by wgolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
t_list_fd	*ft_lstnew(int fd, t_list_fd **list)
{
	t_list_fd	*node;

	node = malloc(sizeof(t_list_fd));
	if (!node)
		return (NULL);
    node->fd = fd;
    node->buffer = NULL;
    node->next = *list;
    *list = node;
	return (node);
}

t_list_fd	*ft_lstfind(t_list_fd *list, int fd)
{
    
    while (list && list->fd != fd)
        list = list->next;
    return (list);
}

int	ft_read(int fd, t_list_fd *node)
{
	char	*temp;
	int		len;

	temp = NULL;
	if (node->buffer)
		temp = node->buffer;
	node->buffer = malloc((node->len + BUFFER_SIZE + 1) * sizeof(char));
	if (!node->buffer)
	{
		free(temp);
		return (-1);
	}
	if (temp)
		ft_strlcpy(node->buffer, temp, node->len + 1);
	free(temp);
	len = read(fd, node->buffer + node->len, BUFFER_SIZE);
	if (len < 0)
		return (-1);
	node->buffer[node->len + len] = '\0';
	node->len += len;
	return (len);
}

char *ft_extract_line(t_list_fd *node)
{
    char *line;
    char *temp;

    if (ft_strchr(node->buffer, '\n') == -1)
    {
        line = ft_substr(node->buffer, 0, node->len);
        free(node->buffer);
        node->buffer = NULL;
        node->len = 0;
        return (line);
    }
    line = ft_substr(node->buffer, 0, ft_strchr(node->buffer, '\n'));
    temp = node->buffer;
    node->buffer = ft_substr(node->buffer, ft_strchr(node->buffer, '\n') , node->len);
    free(temp);
    node->len = ft_strlen(node->buffer);
    return (line);
}

char	*get_next_line(int fd)
{
    char                *r_line;
    static t_list_fd    **list;
    t_list_fd           *node;
    int                 len;
    
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    if (!list)
        list = malloc(sizeof(t_list_fd *));
    node = ft_lstfind(*list, fd);
    if (!node)
        node = ft_lstnew(fd , list); 
    len = ft_read(fd, node);
    while (len > 0 && len == BUFFER_SIZE && ft_strchr(node->buffer, '\n') == -1)
    {
        len = ft_read(fd, node);
    }
    r_line =  ft_substr(node->buffer, 0, ft_strchr(node->buffer, '\n'));
    node->buffer = ft_substr(node->buffer, ft_strchr(node->buffer, '\n') , node->len);
    
    node->len = ft_strlen(node->buffer);
    return (r_line);
}
