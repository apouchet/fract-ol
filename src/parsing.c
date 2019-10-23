/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 12:24:48 by floblanc          #+#    #+#             */
/*   Updated: 2019/10/23 15:01:13 by floblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

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
