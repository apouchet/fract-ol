/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 14:31:35 by apouchet          #+#    #+#             */
/*   Updated: 2019/10/15 14:31:38 by apouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

int		mouse_release_hook(int x, int y, t_data *data)
{
	static int x_prec;
	static int y_prec;
	static int mouse_prec;

	if (data->mouse_button != 1)
	{
		x_prec = x;
		y_prec = y;
	}
	if (data->mouse_button == 1)
	{
		double tmp;
		tmp = (x - x_prec) / (FENETRE_X / (data->x_b - data->x_a));
		data->x_a -= (x - x_prec) / (FENETRE_X / (data->x_b - data->x_a));
		data->x_b -= tmp;

		tmp = (y - y_prec) / (FENETRE_Y / (data->y_b - data->y_a));
		data->y_a -= (y - y_prec) / (FENETRE_Y / (data->y_b - data->y_a));
		data->y_b -= tmp;
		x_prec = x;
		y_prec = y;
	}
	if (!(data->fix) && data->mouse_button == 2)
	{
		data->c_r = (x - FENETRE_X / 2) / (FENETRE_X / (data->x_b - data->x_a));
		data->c_i = (y - FENETRE_Y / 2) / (FENETRE_Y / (data->y_b - data->y_a));
	}
	// if (data->mouse_z)
	{
		data->mouse_x = (x - FENETRE_X / 2) / (FENETRE_X / (data->x_b - data->x_a));
		data->mouse_y = (y - FENETRE_Y / 2) / (FENETRE_Y / (data->y_b - data->y_a));
	}
	return (0);
}


int		mouse_hook(int button, int x, int y, t_data *data)
{
	// if (button == 1)
	// printf("button = %d\n", button);
	// printf("x = %d, y = %d\n", x, y);

	data->mouse_button = button;
	if (button == 5 || button == 4)
		ft_key(-button, data);
	if (!(data->fix) && (data->mouse_button == 1))
	{
		data->c_r = (x - FENETRE_X / 2) / (FENETRE_X / 2.4);
		data->c_i = (y - FENETRE_Y / 2) / (FENETRE_Y / 2.7);
	}
	return (0);
}

int		mouse_release(int button, int x, int y, t_data *data)
{
	data->mouse_button = 0;
	return (0);
}
