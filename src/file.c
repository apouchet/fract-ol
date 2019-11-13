/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <apouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 14:38:00 by apouchet          #+#    #+#             */
/*   Updated: 2019/11/13 16:49:37 by apouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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

	if (!(file = (char*)malloc(ft_size_file(name) + 1)) ||
		(fd = open(name, O_RDONLY)) < 0)
		return (NULL);
	j = 0;
	while ((rd = read(fd, &file[j], 1000)) > 0)
		j += rd;
	file[j] = '\0';
	close(fd);
	if (rd < 0)
		return (NULL);
	return (file);
}

void	ft_read_texture(GLuint program_id, char *texture)
{
	unsigned int	gl_texture;
	unsigned char	*data;
	int				info[3];

	gl_texture = glGetUniformLocation(program_id, "Texture");
	glGenTextures(1, &gl_texture);
	glBindTexture(GL_TEXTURE_2D, gl_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if ((data = stbi_load(texture, &info[0], &info[1], &info[2], 0)))
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, info[0], info[1], 0,
			((info[2] == 4) ? GL_RGBA : GL_RGB), GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		free(data);
	}
	else
	{
		ft_printf("Failed to load texture\n");
		exit(0);
	}
}
