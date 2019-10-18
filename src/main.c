/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:04:17 by apouchet          #+#    #+#             */
/*   Updated: 2019/10/18 14:38:38 by floblanc         ###   ########.fr       */
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
	fract->ratio_x = FENETRE_X / (fract->x_b - fract->x_a);
	fract->ratio_y = FENETRE_Y / (fract->y_b - fract->y_a);

	pthread_t	thread[64];

	fract->x = 0;
	for (int i = 0; i < fract->nb_thread; i++)
		pthread_create(&thread[i], NULL, ft_mandelbrot_julia, (void*)fract);
	for (int i = 0; i < fract->nb_thread; i++)
			pthread_join(thread[i], NULL);
	if (fract->mode == 1 || fract->mode == 2)
		ft_mdb_julia_semi_opti(fract);
	mlx_put_image_to_window(fract->mlx_ptr, fract->win_ptr, fract->p_img, 0, 0);
	return (0);
}

void	ft_screen(t_fract *fract)
{
	t_tga	tga;
	int		fd;
	int		*print;
	int		mode_tmp;

	if (!(print = (int*)malloc(sizeof(int) * (FENETRE_X * FENETRE_Y * 4))))
		return ;
	mode_tmp = fract->mode;
	fract->mode = 0;
	ft_affich(fract);
	fract->mode = mode_tmp;

	tga.id_length = 0;
	tga.colour_map = 0;
	tga.data_type = 2;
	tga.colour_origin = 0;
	tga.colour_length = 0;
	tga.colour_depth = 0;
	tga.x_origin = 0;
	tga.y_origin = 0;
	tga.width = FENETRE_X;
	tga.height = FENETRE_Y;
	tga.bpp = 8 * 4;
	tga.imagedescriptor = 32;
	fd = open("a.tga", O_RDWR | O_CREAT , 0777);
	write(fd, &tga, 7);
	write(fd, &tga.colour_depth, 1);
	write(fd, &tga.x_origin, 10);
	for (int i = 0; i < FENETRE_X * FENETRE_Y; i++)
		print[i] = fract->img[i] + 0xFF000000;
	if (write(fd, print, FENETRE_X * FENETRE_Y * 4) == -1)
		perror("Error : ");
	close(fd);
	free(print);
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

static void	ft_start_fract(t_fract *fract)
{
	fract->mlx_ptr = mlx_init();
	fract->win_ptr = mlx_new_window(fract->mlx_ptr, FENETRE_X, FENETRE_Y, "mlx");
	fract->p_img = mlx_new_image(fract->mlx_ptr, FENETRE_X, FENETRE_Y);
	fract->img = (int*)mlx_get_data_addr(fract->p_img, &fract->p.bpp,
		&fract->p.sl, &fract->p.endian);
	fract->p.bpp /= 4;
	fract->p.sl /= 4;
	fract->mode = 0;
	fract->nb_thread = 8;
	reset_fract(fract);
	
}

int		main(int argc, char **argv)
{
	t_fract		fract;

	fract.fract = 0;
	if (!(parsing(&fract, argc, argv)))
		return (print_usage());
	ft_start_fract(&fract);	
	mlx_hook(fract.win_ptr, 2, 0, &ft_key, &fract);
	mlx_loop_hook(fract.mlx_ptr, &ft_affich, &fract);
	mlx_hook(fract.win_ptr, 6, 0, mouse_release_hook, &fract);
	mlx_hook(fract.win_ptr, 5, 0, &mouse_release, &fract);
	mlx_mouse_hook(fract.win_ptr, &mouse_hook, &fract);
	mlx_hook(fract.win_ptr, 17, 0, red_cross, NULL);
	mlx_loop(fract.mlx_ptr);
	return (0);
}

// gcc -lmlx -framework OpenGL -framework AppKit main.c ft_mandelbrot.c
// man /usr/share/man/man3/
