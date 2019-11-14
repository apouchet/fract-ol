/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <apouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 14:47:46 by floblanc          #+#    #+#             */
/*   Updated: 2019/11/14 13:33:03 by apouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

void	ft_init_mandelbrot(t_fract *fract)
{
	fract->x_a = -2.1;
	fract->x_b = 0.6;
	fract->y_a = -1.2;
	fract->y_b = 1.2;
	fract->fix = 1;
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
	fract->fix = 1;
}

void	ft_init_newton(t_fract *fract)
{
	fract->x_a = -1.5;
	fract->x_b = 1.5;
	fract->y_a = -1;
	fract->y_b = 1;
	fract->fix = 1;
}
