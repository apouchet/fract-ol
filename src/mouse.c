/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 14:31:35 by apouchet          #+#    #+#             */
/*   Updated: 2019/10/16 13:44:56 by floblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

int		mouse_release_hook(int x, int y, t_fract *fract)
{
	static int x_prec;
	static int y_prec;
	double tmp;

	if (fract->mouse_button == 1)
	{
		tmp = (x - x_prec) / (FENETRE_X / (fract->x_b - fract->x_a));
		fract->x_a -= (x - x_prec) / (FENETRE_X / (fract->x_b - fract->x_a));
		fract->x_b -= tmp;
		tmp = (y - y_prec) / (FENETRE_Y / (fract->y_b - fract->y_a));
		fract->y_a -= (y - y_prec) / (FENETRE_Y / (fract->y_b - fract->y_a));
		fract->y_b -= tmp;
	}
	x_prec = x;
	y_prec = y;
	if (fract->mouse_button == 2)
	{
		fract->c_r = (x - FENETRE_X / 2) / (FENETRE_X / (fract->x_b - fract->x_a));
		fract->c_i = (y - FENETRE_Y / 2) / (FENETRE_Y / (fract->y_b - fract->y_a));
		printf("fract->c_r = %lf, fract->c_i = %lf\n", fract->c_r, fract->c_i);

	}
	fract->mouse_x = (x - FENETRE_X / 2) / (FENETRE_X / (fract->x_b - fract->x_a));
	fract->mouse_y = (y - FENETRE_Y / 2) / (FENETRE_Y / (fract->y_b - fract->y_a));
	return (0);
}


int		mouse_hook(int button, int x, int y, t_fract *fract)
{
	// if (button == 1)
	// printf("button = %d\n", button);
	// printf("x = %d, y = %d\n", x, y);
	x++;
	y++;
	fract->mouse_button = button;
	if (button == 5 || button == 4)
		ft_key(-button, fract);
	return (0);
}

int		mouse_release(int button, int x, int y, t_fract *fract)
{
	x++;
	y++;
	button++;
	fract->mouse_button = 0;
	return (0);
}
