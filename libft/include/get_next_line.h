/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfeng <zfeng@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 13:53:50 by zfeng             #+#    #+#             */
/*   Updated: 2018/03/28 13:53:59 by zfeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include "libft.h"

# define MAX_FD 4242
# define BUFF_SIZE 8
# define VARS int n; int nl_idx; char buf[BUFF_SIZE + 1]; char *tmp
# define CHECK(x, y)if(x)return(y)

int				get_next_line(const int fd, char **line);

#endif
