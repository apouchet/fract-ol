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

void	reset_fract(t_fract *data)
{
	data->zoom = 5;
	data->move_x = 0;
	data->move_y = 0;
	data->mouse_x = 0;
	data->mouse_y = 0;
	data->iteration_max = 20;
	if (data->fract == 0)
		ft_init_mandelbrot(data);
	else if (data->fract == 1)
		ft_init_julia(data);
	data->ratio_x = FENETRE_X / (data->x_b - data->x_a);
	data->ratio_y = FENETRE_Y / (data->y_b - data->y_a);
	data->div_q = 1;
	data->div = data->iteration_max / data->div_q;
	data->step_x = (data->x_b - data->x_a) * 0.01;
	data->step_y = (data->y_b - data->y_a) * 0.01;
	data->mouse_button = 0;
}

static int		ft_key_move(int key, t_fract *data)
{
	if (key == 126)
	{
		data->y_a -= data->step_y;
		data->y_b -= data->step_y;
	}
	else if (key == 125)
	{
		data->y_a += data->step_y;
		data->y_b += data->step_y;
	}
	else if (key == 123)
	{
		data->x_a -= data->step_x;
		data->x_b -= data->step_x;
	}
	else if (key == 124)
	{
		data->x_a += data->step_x;
		data->x_b += data->step_x;
	}
	else
		return (0);
	return (1);
}

static int		ft_key_switch_fractal(int key, t_fract *data)
{
	if (key == 22 && data->fract != 0)
	{
		data->fract = 0;
		ft_init_mandelbrot(data);
	}
	else if (key == 23  && data->fract != 1)
	{
		data->fract = 1;
		ft_init_julia(data);
	}
	else
		return (0);
	return (1);
}

static int		ft_key_color_and_mode(int key, t_fract *data)
{
	if (key == 18)
		data->mode = 0;
	else if (key == 19)
		data->mode = 1;
	else if (key == 20)
		data->mode = 2;
	else if (key == 21)
		data->mode = 3;
	else if (key == 8 && data->div_q < data->iteration_max)
	{
		data->div_q++;
		data->div = data->iteration_max / data->div_q;
	}
	else if (key == 9 && data->div_q > 1)
	{
		data->div_q--;
		data->div = data->iteration_max / data->div_q;
	}
	else
		return (0);
	return (1);
}

int		ft_key(int key, t_fract *data)
{
	printf("key = %d\n", key);
	printf("iteration_max = %d\n", data->iteration_max);
	printf("zoom = %d\n", data->zoom);
	if (key == 35)
		ft_screen(data);
	else if (key == 53)
		exit(0);
	else if (key == 257)
		data->iteration_max += 1;
	else if (key == 256 && data->iteration_max > 1)
		data->iteration_max -= 1;
	else if (key == 15)
		reset_fract(data);
	ft_key_move(key, data);
	ft_zoom(key, data);
	ft_key_switch_fractal(key, data);
	ft_key_color_and_mode(key, data);
	ft_affich(data);
	return (1);
}
