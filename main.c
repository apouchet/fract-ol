/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:04:17 by apouchet          #+#    #+#             */
/*   Updated: 2019/10/09 16:04:19 by apouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"


int		ft_affich(t_data *data)
{
	ft_mandelbrot(data, (0.6 + 2.1), (1.2 + 1.2));
	return (0);
}

int		ft_key(int key,	t_data *data)
{
	printf("key = %d\n", key);
	printf("iteration_max = %d\n", data->scale + 20);
	if (key == 12)
		data->fix = (data->fix + 1) % 2;
	if (key == 53)
		exit(0);
	if (data->fix && key == 126)
		data->move_y -= 20;
	if (data->fix && key == 125)
		data->move_y += 20;
	if (data->fix && key == 123)
		data->move_x -= 20;
	if (data->fix && key == 124)
		data->move_x += 20;
	if (data->fix && key == 78)
		data->zoom *= 1.1;
	if (data->fix && key == 69)
		data->zoom *= 0.9;
	if (data->fix && key == 83)
		data->iteration_max++;
	if (data->fix && key == 82 && data->iteration_max > 1)
		data->iteration_max--;

	if (key == 18)
		data->mode = 0;
	if (key == 19)
		data->mode = 1;
	if (key == 20)
		data->mode = 2;
	if (key == 21)
		data->mode = 3;
	if (key == 22)
		data->fract = 0;
	if (key == 23)
		data->fract = 1;
	if (key == 24)
		b += 0.25;
	if (key == 25)
		b -= 0.25;
	ft_affich(data);
	return (1);
}

int		mouse_release_hook(int x, int y, t_data *data)
{
	if (!(data->fix))
	{
		data->c_r = (x - FENETRE_X / 2) / (FENETRE_X / 2.4);
		data->c_i = (y - FENETRE_Y / 2) / (FENETRE_Y / 2.7);
	}
	return (0);
}

int		red_cross(t_data *data)
{
	exit(0);
	return (0);
}


void	ft_start_data(t_data *data)
{
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, FENETRE_X, FENETRE_Y, "mlx");
	data->p_img = mlx_new_image(data->mlx_ptr, FENETRE_X, FENETRE_Y);
	data->img = (int*)mlx_get_data_addr(data->p_img, &data->p.bpp, &data->p.sl, &data->p.endian);
	data->p.bpp /= 4;
	data->p.sl /= 4;
	data->zoom = 1;
	data->move_x = 0;
	data->move_y = 0;
	data->iteration_max = 20;
	data->mode = 0;
	data->fix = 0;
	data->x = 0;
	data->y = 0;
}

int		main(int argc, char **argv)
{
	t_data		data;

	a = 0.5;
	b = 0.5;
	data.fract = 0;
	ft_start_data(&data);
	// ft_base(argv[1], &val);
	// mlx_hook(val.mlx[1], 2, 0, &ft_key_on, &val);
	mlx_hook(data.win_ptr, 2, 0, &ft_key, &data);
	mlx_loop_hook(data.mlx_ptr, &ft_affich, &data);
	mlx_hook(data.win_ptr, 6, 0, mouse_release_hook, &data);
	mlx_hook(data.win_ptr, 17, 0, red_cross, &data);
	
	mlx_loop(data.mlx_ptr);
	return (0);
}

// gcc -lmlx -framework OpenGL -framework AppKit main.c
// man /usr/share/man/man3/
