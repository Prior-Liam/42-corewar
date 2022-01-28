/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfeng <zfeng@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 13:07:57 by zfeng             #+#    #+#             */
/*   Updated: 2018/04/20 14:02:54 by zfeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line.h"

int		locate_nl(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int		check_eof(int fd, char **line, char *rest[MAX_FD])
{
	if (rest[fd] && *rest[fd])
	{
		*line = ft_strdup(rest[fd]);
		ft_memdel(((void**)&rest[fd]));
		return (1);
	}
	else
		return (0);
}

int		read_content(int fd, char **line, char *rest[MAX_FD])
{
	VARS;
	while ((n = read(fd, buf, BUFF_SIZE)) >= 0)
	{
		if (n == 0)
			return (check_eof(fd, line, rest));
		buf[n] = '\0';
		if (!rest[fd])
			rest[fd] = ft_strdup(buf);
		else
		{
			tmp = rest[fd];
			rest[fd] = ft_strjoin(tmp, buf);
			ft_memdel((void**)&tmp);
		}
		if ((nl_idx = locate_nl(rest[fd])) >= 0)
		{
			*line = ft_strndup(rest[fd], nl_idx);
			tmp = rest[fd];
			rest[fd] = ft_strdup(&rest[fd][nl_idx + 1]);
			ft_memdel((void**)&tmp);
			return (1);
		}
	}
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static char	*rest[MAX_FD];

	VARS;
	CHECK(fd == -1 || read(fd, buf, 0) < 0 || !line, -1);
	if (rest[fd] && (nl_idx = locate_nl(rest[fd])) >= 0)
	{
		*line = ft_strndup(rest[fd], nl_idx);
		tmp = rest[fd];
		rest[fd] = ft_strdup(&rest[fd][nl_idx + 1]);
		ft_memdel((void**)&tmp);
		return (1);
	}
	n = read_content(fd, line, rest);
	if (n == 0 || (line && *line == 0))
		return (0);
	return (1);
}
