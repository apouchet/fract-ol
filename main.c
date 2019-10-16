/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:04:17 by apouchet          #+#    #+#             */
/*   Updated: 2019/10/16 13:53:47 by floblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

int		print_usage(void)
{
	write(2, "Usage : ./fract-ol Mandelbrot\n\t\t   Julia\n", 41);
	return (0);
}

int		ft_affich(t_fract *data)
{
	data->ratio_x = FENETRE_X / (data->x_b - data->x_a);
	data->ratio_y = FENETRE_Y / (data->y_b - data->y_a);
	ft_mandelbrot_julia(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->p_img, 0, 0);
	return (0);
}

void	ft_screen(t_fract *data)
{
	t_tga	tga;
	int		fd;
	int		*print;
	int		mode_tmp;

	if (!(print = (int*)malloc(sizeof(int) * (FENETRE_X * FENETRE_Y * 4))))
		return ;
	mode_tmp = data->mode;
	data->mode = 0;
	ft_affich(data);
	data->mode = mode_tmp;

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
		print[i] = data->img[i] + 0xFF000000;
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

void	ft_init_mandelbrot(t_fract *data)
{
	data->x_a = -2.1;
	data->x_b = 0.6;
	data->y_a = -1.2;
	data->y_b = 1.2;
}

void	ft_init_julia(t_fract *data)
{
	data->x_a = -1.5;
	data->x_b = 1.5;
	data->y_a = -1.2;
	data->y_b = 1.2;
}

static void	ft_start_fract(t_fract *data)
{
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, FENETRE_X, FENETRE_Y, "mlx");
	data->p_img = mlx_new_image(data->mlx_ptr, FENETRE_X, FENETRE_Y);
	data->img = (int*)mlx_get_data_addr(data->p_img, &data->p.bpp,
		&data->p.sl, &data->p.endian);
	data->p.bpp /= 4;
	data->p.sl /= 4;
	data->mode = 0;
	reset_fract(data);
	
}

int		main(int argc, char **argv)
{
	t_fract		data;

	data.fract = 0;
	if (!(parsing(&data, argc, argv)))
		return (print_usage());
	ft_start_fract(&data);	
	mlx_hook(data.win_ptr, 2, 0, &ft_key, &data);
	mlx_loop_hook(data.mlx_ptr, &ft_affich, &data);
	mlx_hook(data.win_ptr, 6, 0, mouse_release_hook, &data);
	mlx_hook(data.win_ptr, 5, 0, &mouse_release, &data);
	mlx_mouse_hook(data.win_ptr, &mouse_hook, &data);
	mlx_hook(data.win_ptr, 17, 0, red_cross, NULL);
	mlx_loop(data.mlx_ptr);
	return (0);
}

// gcc -lmlx -framework OpenGL -framework AppKit main.c ft_mandelbrot.c
// man /usr/share/man/man3/
