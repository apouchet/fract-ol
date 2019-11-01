/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 14:34:53 by apouchet          #+#    #+#             */
/*   Updated: 2019/11/01 12:09:46 by floblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GL_H
# define GL_H

# include <fcntl.h>
# include <OpenGL/gl3.h>
# include <SDL2/SDL.h>

// # include <GL/glew.h>
// # include <GLFW/glfw3.h>
# include "fract.h"
# include "../libftprintf/include/libprintf.h"

typedef struct		s_gl
{
	GLuint			vertex_id;
	GLuint			fragment_id;
	GLuint			program_id;
	GLint			attribute_id;
	GLint			log_size;
	GLchar			*log;
	GLuint			vbo;
	GLuint			vao;
	// GLFWwindow		*w;
	SDL_Window		*w;
	SDL_GLContext	contexte_opengl;
	SDL_Event		evenements;
}					t_gl;

typedef struct		s_gldata
{
	double			c_r;
	double			c_i;
	double			zoom;
	double			max_it;
	double			x;
	double			y;
	double			step;
	int				nb_zoom;
	int				fractal;
	int				exit;
}					t_gldata;

typedef struct		s_shd
{
	GLchar			*vertex_s;
	GLchar			*fragment_s;
	GLint			program_state;
	GLint			vertex_size;
	GLint			fragment_size;
}					t_shd;

int					ft_delete_shader(t_gl *gl);

int					ft_shaders(char *name_vs, char *name_fs, t_gl *gl);

int					ft_size_file(char *name);

char				*ft_get_file(char *name, char *file);

void				ft_control(t_gl *gl, t_gldata *data);

void				ft_init_data(t_gldata *data, t_fract *fract, t_gl *gl);

#endif
