/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <apouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 12:24:48 by floblanc          #+#    #+#             */
/*   Updated: 2019/11/13 16:44:51 by apouchet         ###   ########.fr       */
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
	else if (fract->fract == 1 || fract->fract == 3)
		ft_init_julia(fract);
	else if (fract->fract == 2)
		ft_init_bns(fract);
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

int		print_usage(void)
{
	char	*str;

	str = "Usage : ./fractol Mandelbrot\n\t\t  Julia\n\t\t  Burning-Ship\n\t\t";
	write(2, str, ft_strlen(str));
	str = "  Burning-Julia\n\t\t  Newton\n\n\tFlag : -gl : open with OpenGL\n";
	write(2, str, ft_strlen(str));
	return (0);
}

int		ft_check_app(char *exe)
{
	int	i;

	i = ft_strlen(exe);
	while (i > 0 && exe[i] != '/')
		i--;
	if (i > 15 && !ft_strncmp(&exe[i - 15], "/Contents/MacOS/", 15))
		return (1);
	else
		return (0);
}

int		parsing(t_fract *fract, int ac, char **av)
{
	int i;

	i = 0;
	if (ac > 3 || (ac == 1 && !ft_check_app(av[0])) || ac < 1)
		return (0);
	fract->fract = (ac == 1 ? 1 : 0);
	while (++i < ac)
	{
		if (!(fract->fract) && !(ft_strcmp("Mandelbrot", av[i])))
			fract->fract = 1;
		else if (!(fract->fract) && !(ft_strcmp("Julia", av[i])))
			fract->fract = 2;
		else if (!(fract->fract) && !(ft_strcmp("Burning-Ship", av[i])))
			fract->fract = 3;
		else if (!(fract->fract) && !(ft_strcmp("Burning-Julia", av[i])))
			fract->fract = 4;
		else if (!(fract->fract) && !(ft_strcmp("Newton", av[i])))
			fract->fract = 5;
		else if (!(fract->opengl) && !(ft_strcmp("-gl", av[i])))
			fract->opengl = 1;
		else
			return (0);
	}
	fract->fract--;
	return (1);
}
