/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 10:45:42 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/29 18:07:49 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>

# define BUFF_SIZE 32
# define MAX_FILES 10
# define OVER_WRITE 1
# define BUFF liste[i].buff
# define SIZE liste[i].size
# define FD liste[i].fd

typedef struct		s_buff
{
	int				fd;
	char			buff[BUFF_SIZE];
	int				size;
}					t_buff;

int					get_next_line(int const fd, char **line);

#endif
