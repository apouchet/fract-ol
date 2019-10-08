#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>


#define FENETRE 800
#define R 0x00FF0000
#define G 0x0000FF00
#define B 0x000000FF

typedef struct	s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*p_image;
	char		*image;
}				t_data;

typedef struct	s_picture
{
	int			bpp;
	int			s_l;
	int			endian;
}				t_picture;

int		ft_mandelbrot(t_data *data)
{
int iteration_max = 50;

// on calcule la taille de l'image :
double zoom_x = FENETRE/(0.6 + 2.1) ;
double zoom_y = FENETRE/(1.2 + 1.2) ;

	for (int x = 0; x < FENETRE; x++)
	{
		for (int y = 0; y < FENETRE; y++)
		{
			double c_r = x / zoom_x - 2.1;
			double c_i = y / zoom_y - 1.2;
			double z_r = 0;
			double z_i = 0;
			int i = 0;

			do
			{
				double tmp = z_r;
				z_r = z_r * z_r - z_i * z_i + c_r;
				z_i = 2 * z_i * tmp + c_i;
				i++;
			}
			while (z_r * z_r + z_i * z_i < 4 && i < iteration_max);
			// printf("i = %d\n", i);
			if (i == iteration_max)
				data->image[4 * FENETRE * y + 4 * x] = 0xFF;
		}
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->p_image, 0, 0);
	return (0);
}

int		ft_affich(t_data *data)
{
	int x;
	int y;
	double a = 0, b = 0;
	char *img;

	// a = a * 2 – b * 2 + 1;
	// b = 2 a * b + 1;
	x = 0;
	y = 0;
	int c = 0, z = 0, i = 0;
	int iteration_max = 50;
	while (y <= FENETRE)
	{
		while (x <= FENETRE)
		{
			c = a + i * b;

			z = z * z + c;
			i = i + 1;
			// printf("i = %d, z = %d\n", i, z);
			if (z >= 2 || i > iteration_max)
				i = 0;
			if (i == iteration_max)
			{
				data->image[4 * FENETRE * y + 4 * x] = c;
				i = 0;
			}
			// Tant que module de z < 2 et i < iteration_max

			// si i = iteration_max
			// dessiner le pixel correspondant au point de coordonné (x; y)
			// finSi
			// finPour
			
			// data->image[4 * FENETRE * y + 4 * x] = 127;
			// data->image[4 * FENETRE * y + 4 * x + 1] = 0xFF;
			// data->image[4 * FENETRE * y + 4 * x + 2] = 0;
			// mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, (R));
			x++;
			a = x / FENETRE;
		}
		x = 0;
		y++;
		b = y / FENETRE;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->p_image, 0, 0);
	return (0);
}

int		ft_key(int key,	t_data *data)
{
	printf("key = %d\n", key);
	if (key == 53)
		exit(0);
	ft_mandelbrot(data);
	return (1);
}

int		main(int argc, char **argv)
{
	
	t_picture	p;
	t_data		data;

	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, FENETRE, FENETRE, "mlx");
	data.p_image = mlx_new_image(data.mlx_ptr, FENETRE, FENETRE);
	data.image = mlx_get_data_addr(data.p_image, &p.bpp, &p.s_l, &p.endian);
	// ft_base(argv[1], &val);
	// mlx_hook(val.mlx[1], 2, 0, &ft_key_on, &val);
	mlx_key_hook(data.win_ptr, &ft_key, &data);
	mlx_loop_hook(data.mlx_ptr, &ft_mandelbrot, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}

// -lmlx -framework OpenGL -framwork AppKit
// man /usr/share/man/man3/