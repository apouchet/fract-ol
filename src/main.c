/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:04:17 by apouchet          #+#    #+#             */
/*   Updated: 2019/10/21 11:12:30 by apouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

int		print_usage(void)
{
	char	*str;

	str = "Usage : ./fractol Mandelbrot\n\t\t  Julia\n\t\t  Burning-Ship\n\t\t  Burning-Julia\n\t\t  Newton\n";
	write(2, str, ft_strlen(str));
	return (0);
}

int		ft_affich(t_fract *fract)
{
	int	i;
	pthread_t	thread[64];

	if (fract->opengl == 1)
		return (1);
	fract->ratio_x = FENETRE_X / (fract->x_b - fract->x_a);
	fract->ratio_y = FENETRE_Y / (fract->y_b - fract->y_a);
	fract->x = 0;
	i = -1;
	while (++i < fract->nb_thread)
		pthread_create(&thread[i], NULL, ft_mandelbrot_julia, (void*)fract);
	i = -1;
	while (++i < fract->nb_thread)
			pthread_join(thread[i], NULL);
	if (fract->mode == 1 || fract->mode == 2)
		ft_mdb_julia_semi_opti(fract);
	mlx_put_image_to_window(fract->mlx_ptr, fract->win_ptr, fract->p_img, 0, 0);
	ft_hud(fract);
	return (0);
}

// void	ft_init_screenshot(t_fract)

char	*ft_create_path(char *target, char *type, char *name, int offset)
{
	char	*path;
	size_t len;
	len = ft_strlen("/Users/") + ft_strlen(getlogin()) + ft_strlen(target)
	+ ft_strlen(name) + ft_strlen(type);
	if (!(path = (char*)ft_memalloc(sizeof(char) * len)))
		return (NULL);
	path = ft_strcat(path, "/Users/");
	path = ft_strcat(ft_strcat(path, getlogin()), "/");
	path = ft_strcat(ft_strcat(ft_strcat(path, target), "/"), name);
	path[len - ft_strlen(type) - offset] = 0;
	path = ft_strcat(path, ".tga");
	return (path);
}

void	ft_init_screenshot(t_tga *tga, t_fract *fract)
{
	int		mode_tmp;
	int		info_tmp;

	info_tmp = fract->info;
	mode_tmp = fract->mode;
	fract->info = 0;
	fract->mode = 0;
	ft_affich(fract);
	fract->info = info_tmp;
	fract->mode = mode_tmp;

	ft_bzero(tga, sizeof(t_tga));
	tga->data_type = 2;
	tga->width = FENETRE_X;
	tga->height = FENETRE_Y;
	tga->bpp = 8 * 4;
	tga->imagedescriptor = 32;
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

int		red_cross(void)
{
	exit(0);
	return (0);
}

void	ft_init_mandelbrot(t_fract *fract)
{
	fract->x_a = -2.1;
	fract->x_b = 0.6;
	fract->y_a = -1.2;
	fract->y_b = 1.2;
}

void	ft_init_julia(t_fract *fract)
{
	fract->x_a = -1.5;
	fract->x_b = 1.5;
	fract->y_a = -1.2;
	fract->y_b = 1.2;
}

void	ft_init_newton(t_fract *fract)
{
	fract->x_a = -2;
	fract->x_b = 1.5;
	fract->y_a = -1;
	fract->y_b = 1;
}

void	ft_start_fract(t_fract *fract)
{
	fract->opengl = 0;
	fract->mlx_ptr = mlx_init();
	fract->win_ptr =
	mlx_new_window(fract->mlx_ptr, FENETRE_X, FENETRE_Y, "mlx");
	fract->p_img = mlx_new_image(fract->mlx_ptr, FENETRE_X, FENETRE_Y);
	fract->img = (int*)mlx_get_data_addr(fract->p_img, &fract->p.bpp,
		&fract->p.sl, &fract->p.endian);
	fract->p.bpp /= 4;
	fract->p.sl /= 4;
	fract->mode = 0;
	fract->nb_thread = 8;
	fract->info = 1;
	reset_fract(fract);
	
}

int		main_mlx(t_fract *fract)
{
	mlx_loop_hook(fract->mlx_ptr, &ft_affich, fract);
	mlx_hook(fract->win_ptr, 6, 0, mouse_release_hook, fract);
	mlx_hook(fract->win_ptr, 5, 0, &mouse_release, fract);
	mlx_mouse_hook(fract->win_ptr, &mouse_hook, fract);
	mlx_hook(fract->win_ptr, 17, 0, red_cross, NULL);
	mlx_hook(fract->win_ptr, 2, 0, &ft_key, fract);
	return (0);
}

int		main(int argc, char **argv)
{
	t_fract		fract;

	fract.opengl = 0;
	if (!(parsing(&fract, argc, argv)))
		return (print_usage());
	ft_start_fract(&fract);
	main_mlx(&fract);
	mlx_loop(fract.mlx_ptr);
}

// gcc -lmlx -framework OpenGL -framework AppKit main.c ft_mandelbrot.c
// man /usr/share/man/man3/
