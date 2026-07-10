/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wgolbert <wgolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 20:25:46 by wgolbert          #+#    #+#             */
/*   Updated: 2026/07/10 11:21:00 by wgolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_list_fd
{
	int					fd;
	char				*buffer;
	int					mem_size;
	int					len;
	struct s_list_fd	*next;
}						t_list_fd;

char					*get_next_line(int fd);
int						ft_strchr(const char *s, int i);
size_t					ft_strlcpy(char *dst, const char *src, size_t size);
size_t					ft_strlen(const char *s);
char					*ft_substr(char const *s, unsigned int start,
							size_t len);
void					*ft_calloc(size_t nmemb, size_t size);

#endif