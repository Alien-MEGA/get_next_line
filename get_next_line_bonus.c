/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:49:42 by reben-ha          #+#    #+#             */
/*   Updated: 2022/11/28 20:50:30 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_read_join(int fd, char *save_area, int *fail)
{
	char		*buffer;

	buffer = (char *)malloc(BUFFER_SIZE * sizeof(char) + 1);
	if (!buffer)
		return (NULL);
	while ((*fail) > 0 && ft_strchr_cheack(save_area, '\n') == 0)
	{
		(*fail) = read(fd, buffer, BUFFER_SIZE);
		if ((*fail) == -1)
		{
			free(save_area);
			save_area = NULL;
			return (free(buffer), buffer = NULL);
		}
		buffer[(*fail)] = '\0';
		save_area = ft_strjoin(save_area, buffer);
	}
	free(buffer);
	return (save_area);
}

char	*get_next_line(int fd)
{
	static char	*save_area[OPEN_MAX];
	char		*result;
	char		*temp;
	int			fail;

	if (fd == -1 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	fail = 1;
	save_area[fd] = ft_read_join(fd, save_area[fd], &fail);
	if (fail == 0 && save_area[fd][0] == '\0')
		return (free(save_area[fd]), save_area[fd] = NULL);
	else if (fail == 0)
	{
		result = ft_strchr(save_area[fd], '\n', 3);
		free(save_area[fd]);
		save_area[fd] = NULL;
	}
	else
	{
		result = ft_strchr(save_area[fd], '\n', 1);
		temp = save_area[fd];
		save_area[fd] = ft_strchr(save_area[fd], '\n', 2);
		free(temp);
	}
	return (result);
}
