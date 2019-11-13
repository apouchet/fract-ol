/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <apouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:04:17 by apouchet          #+#    #+#             */
/*   Updated: 2019/11/13 16:33:43 by apouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

int		ft_affich(t_fract *fract)
{
	int			i;
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
	if (fract->mode > 0)
		ft_mdb_julia_semi_opti(fract);
	mlx_put_image_to_window(fract->mlx_ptr, fract->win_ptr, fract->p_img, 0, 0);
	if (fract->info)
		ft_hud(fract);
	return (0);
}

int		red_cross(void)
{
	exit(0);
	return (0);
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
