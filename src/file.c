/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 14:38:00 by apouchet          #+#    #+#             */
/*   Updated: 2019/10/24 16:40:44 by apouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl.h"

int		ft_size_file(char *name)
{
	int		fd;
	int		rd;
	long	len;
	char	buff[1001];

	len = 0;
	if ((fd = open(name, O_RDONLY)) < 0)
	{
		ft_printf("Error fail to open file - %s\n", name);
		return (-1);
	}
	while ((rd = read(fd, buff, 1000)) > 0)
		len += rd;
	close(fd);
	return (rd < 0 ? rd : len);
}

char	*ft_get_file(char *name, char *file)
{
	int		fd;
	int		rd;
	int		j;

	printf("a\n");
	if (!(file = (char*)malloc(ft_size_file(name) + 1)) ||
		(fd = open(name, O_RDONLY)) < 0)
		return (NULL);
	printf("b\n");
	j = 0;
	while ((rd = read(fd, &file[j], 1000)) > 0)
		j += rd;
	printf("c\n");
	file[j] = '\0';
	close(fd);
	if (rd < 0)
		return (NULL);
	return (file);
}
