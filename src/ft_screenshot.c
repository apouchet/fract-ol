/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_screenshot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 18:13:00 by apouchet          #+#    #+#             */
/*   Updated: 2019/10/21 18:13:01 by apouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fract.h"

char	*ft_create_path(char *target, char *type, char *name, int offset)
{
	char	*path;
	size_t len;

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

void	ft_init_screenshot(t_tga *tga, t_fract *fract)
{
	int		mode_tmp;
	int		info_tmp;

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
	tga->data_type = 2;
	tga->width = FENETRE_X;
	if (fract == NULL)
		tga->height = FENETRE_X;
	else
		tga->height = FENETRE_Y;
}

void	ft_screen_gl(char *buff)
{
	t_tga	tga;
	int		fd;
	char	*name;
	time_t	curtime;
	
	time(&curtime);
	ft_init_screenshot(&tga, NULL);
	tga.bpp = 8 * 3;
	tga.imagedescriptor = 16;
	if (!(name = ft_create_path(SCREENSHOT, ".tga", &ctime(&curtime)[4], 0)))
	{
		printf("fail to malloc for screenshot\n");
		return ;
	}
	if ((fd = open(name, O_RDWR | O_CREAT, 0777)) < 0
		|| write(fd, &tga, 7) < 0 || write(fd, &tga.colour_depth, 1) < 0
		|| write(fd, &tga.x_origin, 10) < 0
		|| write(fd, buff, FENETRE_X * FENETRE_X * 3) < 0)
		perror("2 Error ");
	close(fd);
	free(name);
}

void	ft_screen(t_fract *fract)
{
	t_tga	tga;
	int		fd;
	char	*name;
	time_t	curtime;
	int 	i;

	i = -1;
	time(&curtime);
	ft_init_screenshot(&tga, fract);
	tga.bpp = 8 * 4;
	tga.imagedescriptor = 32;
	if (!(name = ft_create_path(SCREENSHOT, ".tga", &ctime(&curtime)[4], 0)))
	{
		printf("fail to malloc for screenshot\n");
		return ;
	}
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
