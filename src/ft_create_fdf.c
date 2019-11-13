/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_fdf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <apouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:45:43 by apouchet          #+#    #+#             */
/*   Updated: 2019/11/13 16:46:23 by apouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

static void	build_fdf_loop(t_fract *f, int i, int fd)
{
	static char *tmp;

	tmp = ft_itoa(f->img[i]);
	write(fd, tmp, ft_strlen(tmp));
	ft_strdel(&tmp);
	write(fd, ",0x", 3);
	tmp = ft_itoa_base(ft_color(f->img[i], *f, i % FENETRE_X, i / FENETRE_X)
	, "0123456789ABCDEF");
	write(fd, tmp, ft_strlen(tmp));
	ft_strdel(&tmp);
	write(fd, (i % FENETRE_X == FENETRE_X - 1 ? "\n" : " "), 1);
}

void		ft_build_fdf(t_fract *f)
{
	int		fd;
	int		i;
	char	*name;
	time_t	curtime;

	time(&curtime);
	if (!(name = ft_create_path(BUILD_FDF, ".fdf", &ctime(&curtime)[4], 0)))
	{
		ft_printf("fail to malloc for fdf\n");
		return ;
	}
	if (!(fd = open(name, O_RDWR | O_CREAT, 0777)))
		perror("Error ");
	f->fdf = 1;
	ft_affich(f);
	f->fdf = 0;
	i = -1;
	while (++i / FENETRE_X < FENETRE_Y)
		build_fdf_loop(f, i, fd);
	ft_strdel(&name);
	close(fd);
}
