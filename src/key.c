/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 14:31:32 by apouchet          #+#    #+#             */
/*   Updated: 2019/10/16 13:44:56 by floblanc         ###   ########.fr       */
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
	if (fract->fract == 0)
		ft_init_mandelbrot(fract);
	else if (fract->fract == 1)
		ft_init_julia(fract);
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
	else
		return (0);
	return (1);
}

static int		ft_key_color_and_mode(int key, t_fract *fract)
{
	if (key == 18)
		fract->mode = 0;
	else if (key == 19)
		fract->mode = 1;
	else if (key == 20)
		fract->mode = 2;
	else if (key == 21 && fract->nb_thread == 1)
		fract->mode = 3;
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

int		ft_key(int key, t_fract *fract)
{
	printf("key = %d\n", key);
	printf("iteration_max = %d\n", fract->iteration_max);
	printf("nb thread = %d\n", fract->nb_thread);
	// printf("zoom = %d\n", fract->zoom);
	if (key == 0 && fract->nb_thread > 1)
		fract->nb_thread--;
	if (key == 1 && fract->nb_thread < 64)
		fract->nb_thread++;	
	if (key == 35)
		ft_screen(fract);
	else if (key == 53)
		exit(0);
	else if (key == 257)
		fract->iteration_max += 1;
	else if (key == 256 && fract->iteration_max > 1)
		fract->iteration_max -= 1;
	else if (key == 15)
		reset_fract(fract);
	ft_key_move(key, fract);
	ft_zoom(key, fract);
	ft_key_switch_fractal(key, fract);
	ft_key_color_and_mode(key, fract);
	ft_affich(fract);
	return (1);
}