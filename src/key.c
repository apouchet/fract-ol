/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 14:31:32 by apouchet          #+#    #+#             */
/*   Updated: 2019/10/21 15:57:42 by floblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

void	reset_fract(t_fract *fract)
{
	fract->zoom = 5;
	fract->move_x = 0;
	fract->move_y = 0;
	fract->mouse_x = 0;
	fract->mouse_y = 0;
	fract->iteration_max = 20;
	if (fract->fract == 0  || fract->fract == 2)
		ft_init_mandelbrot(fract);
	else if (fract->fract == 1 || fract->fract == 3)
		ft_init_julia(fract);
	else if (fract->fract == 4)
		ft_init_newton(fract);
	fract->ratio_x = FENETRE_X / (fract->x_b - fract->x_a);
	fract->ratio_y = FENETRE_Y / (fract->y_b - fract->y_a);
	fract->div_q = 1;
	fract->div = fract->iteration_max / fract->div_q;
	fract->step_x = (fract->x_b - fract->x_a) * 0.01;
	fract->step_y = (fract->y_b - fract->y_a) * 0.01;
	fract->mouse_button = 0;
}

static int		ft_key_move(int key, t_fract *fract)
{
	if (key == 126)
	{
		fract->y_a -= fract->step_y;
		fract->y_b -= fract->step_y;
	}
	else if (key == 125)
	{
		fract->y_a += fract->step_y;
		fract->y_b += fract->step_y;
	}
	else if (key == 123)
	{
		fract->x_a -= fract->step_x;
		fract->x_b -= fract->step_x;
	}
	else if (key == 124)
	{
		fract->x_a += fract->step_x;
		fract->x_b += fract->step_x;
	}
	else
		return (0);
	return (1);
}

static int		ft_key_switch_fractal(int key, t_fract *fract)
{
	if (key == 22 && fract->fract != 0)
	{
		fract->fract = 0;
		ft_init_mandelbrot(fract);
	}
	else if (key == 23  && fract->fract != 1)
	{
		fract->fract = 1;
		ft_init_julia(fract);
	}
	else if (key == 28  && fract->fract != 2)
	{
		fract->fract = 2;
		ft_init_mandelbrot(fract);
	}
	else if (key == 26  && fract->fract != 3)
	{
		fract->fract = 3;
		ft_init_julia(fract);
	}
	else if (key == 25  && fract->fract != 4)
	{
		fract->fract = 4;
		ft_init_newton(fract);
	}
	else
		return (0);
	return (1);
}

static int		ft_key_color_and_mode(int key, t_fract *fract)
{
	if (key == 18 || key == 83)
		fract->mode = 0;
	else if (key == 19 || key == 84)
		fract->mode = 1;
	else if (key == 20 || key == 85)
		fract->mode = 2;
	// else if (key == 21)
	// 	fract->mode = 3;
	else if (key == 8 && fract->div_q < fract->iteration_max)
	{
		fract->div_q++;
		fract->div = fract->iteration_max / fract->div_q;
	}
	else if (key == 9 && fract->div_q > 1)
	{
		fract->div_q--;
		fract->div = fract->iteration_max / fract->div_q;
	}
	else
		return (0);
	return (1);
}

void	ft_build_fdf(t_fract *f)
{
	int		fd;
	int		i;
	int		mode_tmp;
	int		info_tmp;
	char	*tmp;
	
	time_t curtime;
	time(&curtime);
	printf("Current time = %s", ctime(&curtime));

	if (!(fd = open(ft_strcat(&ctime(&curtime)[4], ".fdf")
		, O_RDWR | O_CREAT, 0777)))
		perror("Error ");
	f->fdf = 1;
	info_tmp = f->info;
	mode_tmp = f->mode;
	f->info = 0;
	f->mode = 0;
	ft_affich(f);
	f->info = info_tmp;
	f->mode = mode_tmp;
	f->fdf = 0;
	i = -1;
	while (++i / FENETRE_X < FENETRE_Y)
	{
			tmp = ft_itoa(f->img[i]);
			write(fd, tmp, ft_strlen(tmp));
			ft_strdel(&tmp);
			write(fd, ",0x", 3);
			tmp = ft_itoa_base(ft_color(f->img[i], *f, i % FENETRE_X, i / FENETRE_X), "0123456789ABCDEF");
			write(fd, tmp, ft_strlen(tmp));
			ft_strdel(&tmp);
			write(fd, (i % FENETRE_X == FENETRE_X - 1 ? "\n" : " "), 1);
	}
	close(fd);
}

int		ft_key(int key, t_fract *fract)
{
	printf("key = %d\n", key);
	//printf("%d\n", key);
	// printf("iteration_max = %d\n", fract->iteration_max);
	// printf("nb thread = %d\n", fract->nb_thread);
	// printf("zoom = %d\n", fract->zoom);
	if (key == 12 && fract->nb_thread > 1)
		fract->nb_thread--;
	if (key == 14 && fract->nb_thread < 64)
		fract->nb_thread++;	
	if (key == 35)
		ft_screen(fract);
	if (key == 49)
		fract->fix = (fract->fix + 1) % 2;
	else if (key == 36)
	{
		fract->opengl = 1;
		mlx_destroy_window(fract->mlx_ptr, fract->win_ptr);
		if (main_opengl(fract) == 0)
			exit(0);
		fract->win_ptr =
		mlx_new_window(fract->mlx_ptr, FENETRE_X, FENETRE_Y, "mlx");
		main_mlx(fract);
		fract->opengl = 0;
	}
	else if (key == 53)
		exit(0);
	else if (key == 3)
		ft_build_fdf(fract);
	else if (key == 2)
		fract->iteration_max += 1;
	else if (key == 0 && fract->iteration_max > 1)
		fract->iteration_max -= 1;
	else if (key == 15)
		reset_fract(fract);
	else if (key == 34)
		fract->info = (fract->info % 2) + 1;
	ft_key_move(key, fract);
	ft_zoom(key, fract);
	ft_key_switch_fractal(key, fract);
	ft_key_color_and_mode(key, fract);
	ft_affich(fract);
	return (1);
}
