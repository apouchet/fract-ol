/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 14:31:32 by apouchet          #+#    #+#             */
/*   Updated: 2019/11/15 15:03:15 by apouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

static int	ft_key_move(int key, t_fract *fract)
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

static void	ft_key_switch_fractal(int key, t_fract *fract)
{
	if ((key == 18 || key == 83) && fract->fract != 0)
	{
		fract->fract = 0;
		ft_init_mandelbrot(fract);
	}
	else if ((key == 19 || key == 84) && fract->fract != 1)
	{
		fract->fract = 1;
		ft_init_julia(fract);
	}
	else if ((key == 20 || key == 85) && fract->fract != 2)
	{
		fract->fract = 2;
		ft_init_bns(fract);
	}
	else if ((key == 21 || key == 86) && fract->fract != 3)
	{
		fract->fract = 3;
		ft_init_julia(fract);
	}
	else if ((key == 23 || key == 87) && fract->fract != 4)
	{
		fract->fract = 4;
		ft_init_newton(fract);
	}
}

static int	ft_key_color_and_mode(int key, t_fract *fract)
{
	if (key == 22 || key == 88)
		fract->mode = 0;
	else if (key == 26 || key == 89)
		fract->mode = 1;
	else if (key == 28 || key == 91)
		fract->mode = 2;
	else if (key == 25 || key == 92)
		fract->mode = 3;
	else if (key == 29 || key == 82)
		fract->mode = 4;
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

static int	ft_key2(int key, t_fract *fract)
{
	if (key == 3 && fract->fract != 4)
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

int			ft_key(int key, t_fract *fract)
{
	if (key == 12 && fract->nb_thread > 1)
		fract->nb_thread--;
	if (key == 14 && fract->nb_thread < 64)
		fract->nb_thread++;
	if (key == 35)
		ft_screen(fract);
	if (key == 49 && (fract->fract == 1 || fract->fract == 3))
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
		reset_fract(fract);
		fract->opengl = 0;
	}
	else if (key == 53)
		exit(0);
	else
		return (ft_key2(key, fract));
	return (1);
}
