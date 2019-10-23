/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:04:17 by apouchet          #+#    #+#             */
/*   Updated: 2019/10/23 14:27:32 by floblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

int		print_usage(void)
{
	char	*str;

	str = "Usage : ./fractol Mandelbrot\n\t\t  Julia\n\t\t  Burning-Ship\n\t\t  Burning-Julia\n\t\t  Newton\n\n\tFlag : -gl : open with OpenGL\n";
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
	fract->x_a = -1.9965;
	fract->x_b = 1.9965;
	fract->y_a = -1.5972;
	fract->y_b = 1.5972;
}

void	ft_init_bns(t_fract *fract)
{
	fract->x_a = -2.041;
	fract->x_b = 1.226;
	fract->y_a = -1.952;
	fract->y_b = 0.952;
}

void	ft_init_newton(t_fract *fract)
{
	fract->x_a = -1.5;
	fract->x_b = 1.5;
	fract->y_a = -1;
	fract->y_b = 1;
}

void	ft_start_fract(t_fract *fract)
{
	fract->mlx_ptr = mlx_init();
	fract->win_ptr =
	mlx_new_window(fract->mlx_ptr, FENETRE_X, FENETRE_Y, "mlx");
	fract->p_img = mlx_new_image(fract->mlx_ptr, FENETRE_X, FENETRE_Y);
	fract->img = (int*)mlx_get_data_addr(fract->p_img, &fract->p.bpp,
		&fract->p.sl, &fract->p.endian);
	fract->p.bpp /= 4;
	fract->p.sl /= 4;
	fract->mode = 0;
	fract->fix = 1;
	fract->fdf = 0;
	fract->nb_thread = 8;
	fract->info = 1;
	reset_fract(fract);
	if (fract->opengl)
		ft_key(36, fract);
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
	fract.fract = 1;
	if (!(parsing(&fract, argc, argv)))
		return (print_usage());
	ft_start_fract(&fract);
	main_mlx(&fract);
	mlx_loop(fract.mlx_ptr);
}

// gcc -lmlx -framework OpenGL -framework AppKit main.c ft_mandelbrot.c
// man /usr/share/man/man3/
