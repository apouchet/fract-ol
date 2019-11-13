/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_screenshot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <apouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 18:13:00 by apouchet          #+#    #+#             */
/*   Updated: 2019/11/13 16:25:45 by apouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"
#include "gl.h"

char		*ft_create_path(char *target, char *type, char *name, int offset)
{
	char	*path;
	size_t	len;

	if (target[0] != '.')
		len = ft_strlen("/Users/") + ft_strlen(getlogin()) + ft_strlen(target)
		+ ft_strlen(name) + ft_strlen(type);
	else
		len = ft_strlen(target) + ft_strlen(name) + ft_strlen(type);
	if (!(path = (char*)ft_memalloc(sizeof(char) * len)))
		return (NULL);
	if (target[0] != '.')
	{
		path = ft_strcat(path, "/Users/");
		path = ft_strcat(ft_strcat(path, getlogin()), "/");
	}
	path = ft_strcat(ft_strcat(ft_strcat(path, target), "/"), name);
	path[len - ft_strlen(type) - offset] = 0;
	path = ft_strcat(path, type);
	return (path);
}

static void	ft_init_screenshot(t_tga *tga, t_fract *fract, char **name)
{
	int		mode_tmp;
	int		info_tmp;
	time_t	curtime;

	time(&curtime);
	if (fract != NULL)
	{
		info_tmp = fract->info;
		mode_tmp = fract->mode;
		fract->info = 0;
		fract->mode = 0;
		ft_affich(fract);
		fract->info = info_tmp;
		fract->mode = mode_tmp;
	}
	ft_bzero(tga, sizeof(t_tga));
	tga->bpp = 8 * 4;
	tga->data_type = 2;
	tga->width = FENETRE_X;
	tga->height = FENETRE_Y;
	if (!(*name = ft_create_path(SCREENSHOT, ".tga", &ctime(&curtime)[4], 0)))
	{
		printf("fail to malloc for screenshot\n");
		return ;
	}
}

static void	ft_clear_hud(unsigned char **buff)
{
	int i;

	i = 0;
	while (i < FENETRE_X * FENETRE_Y * 4)
	{
		if ((*buff)[i + 3] != 255)
		{
			(*buff)[i] = 255 - (*buff)[i];
			(*buff)[i + 1] = 255 - (*buff)[i + 1];
			(*buff)[i + 2] = 255 - (*buff)[i + 2];
			(*buff)[i + 3] = 255;
		}
		i += 4;
	}
}

void		ft_screen_gl(void)
{
	t_tga			tga;
	int				fd;
	char			*name;
	unsigned char	*buff;

	if (!(buff = (unsigned char*)malloc((FENETRE_X * FENETRE_Y * 4))))
	{
		ft_printf("Error : can't take a screenshot\n");
		return ;
	}
	glReadPixels(0, 0, FENETRE_X, FENETRE_Y, GL_BGRA, GL_UNSIGNED_BYTE, buff);
	ft_init_screenshot(&tga, NULL, &name);
	tga.imagedescriptor = 16;
	ft_clear_hud(&buff);
	if ((fd = open(name, O_RDWR | O_CREAT, 0777)) < 0
		|| write(fd, &tga, 7) < 0 || write(fd, &tga.colour_depth, 1) < 0
		|| write(fd, &tga.x_origin, 10) < 0
		|| write(fd, buff, FENETRE_X * FENETRE_Y * 4) < 0)
		perror("2 Error ");
	close(fd);
	free(name);
	free(buff);
}

void		ft_screen(t_fract *fract)
{
	t_tga	tga;
	int		fd;
	char	*name;
	int		i;

	i = -1;
	ft_init_screenshot(&tga, fract, &name);
	tga.imagedescriptor = 32;
	while (++i < FENETRE_X * FENETRE_Y)
		fract->img[i] += 0xFF000000;
	if ((fd = open(name, O_RDWR | O_CREAT, 0777)) < 0
		|| write(fd, &tga, 7) < 0 || write(fd, &tga.colour_depth, 1) < 0
		|| write(fd, &tga.x_origin, 10) < 0
		|| write(fd, fract->img, FENETRE_X * FENETRE_Y * 4) < 0)
		perror("2 Error ");
	close(fd);
	free(name);
}
