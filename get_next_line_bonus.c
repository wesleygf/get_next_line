/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wgolbert <wgolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 20:25:39 by wgolbert          #+#    #+#             */
/*   Updated: 2026/07/10 11:20:47 by wgolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	ft_lstdel(t_list_fd **list, int fd)
{
	t_list_fd	*node;
	t_list_fd	*temp;

	node = *list;
	if (!node->next)
	{
		free(node->buffer);
		free(node);
		*list = NULL;
		return ;
	}
	while (node && node->fd != fd)
	{
		temp = node;
		node = node->next;
	}
	if (node)
	{
		temp->next = node->next;
		free(node->buffer);
		free(node);
	}
}

static t_list_fd	*ft_lstfind(t_list_fd **list, int fd)
{
	t_list_fd	*node;

	node = *list;
	while (node && node->fd != fd)
		node = node->next;
	if (!node)
	{
		node = malloc(sizeof(t_list_fd));
		if (!node)
			return (NULL);
		node->fd = fd;
		node->buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!node->buffer)
		{
			free(node);
			return (NULL);
		}
		node->mem_size = BUFFER_SIZE + 1;
		node->len = 0;
		node->next = *list;
		*list = node;
		return (node);
	}
	return (node);
}

static int	ft_read(int fd, t_list_fd *node)
{
	char	*temp;
	int		len;

	temp = NULL;
	if (!node->buffer || node->mem_size <= node->len + BUFFER_SIZE + 1)
	{
		temp = node->buffer;
		node->mem_size = ((node->len + BUFFER_SIZE + 1) * 2);
		node->buffer = malloc(node->mem_size);
		if (!node->buffer)
		{
			free(temp);
			return (-1);
		}
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

static char	*ft_extract_line(t_list_fd *node)
{
	char	*line;
	char	*temp;
	int		pos;

	pos = ft_strchr(node->buffer, 0);
	if (pos == -1)
	{
		line = ft_substr(node->buffer, 0, node->len);
		free(node->buffer);
		node->buffer = NULL;
		node->mem_size = 0;
		node->len = 0;
		return (line);
	}
	line = ft_substr(node->buffer, 0, pos + 1);
	temp = node->buffer;
	node->buffer = ft_substr(node->buffer, pos + 1, node->len - pos - 1);
	free(temp);
	node->len = node->len - pos - 1;
	node->mem_size = node->len;
	return (line);
}

char	*get_next_line(int fd)
{
	static t_list_fd	*list;
	t_list_fd			*node;
	int					len;
	int					i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	node = ft_lstfind(&list, fd);
	if (!node)
		return (NULL);
	len = 1;
	i = 0;
	while ((!node->buffer || ft_strchr(node->buffer, i) == -1) && len > 0)
	{
		i = node->len;
		len = ft_read(fd, node);
		if (len == -1)
			return (NULL);
	}
	if (node->len == 0)
	{
		ft_lstdel(&list, fd);
		return (NULL);
	}
	return (ft_extract_line(node));
}
