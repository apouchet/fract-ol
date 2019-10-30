/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opengl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 13:39:00 by apouchet          #+#    #+#             */
/*   Updated: 2019/10/30 19:28:43 by apouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl.h"

static int	ft_init_glfw_gl(t_gl *gl)
{
	// glfwInit();
	// glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	// glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	// glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	// glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	// gl->w = glfwCreateWindow(FENETRE_X, FENETRE_X, "OpenGL", NULL, NULL);
	// glfwMakeContextCurrent(gl->w);
	// if (!(gl->w))
	// {
	// 	ft_printf("Error while opening windows\n");
	// 	glfwTerminate();
	// 	return (-1);
	// }
	// glewExperimental = GL_TRUE;
	// glewInit();


	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		ft_printf("Error initialisation of SDL :  %s\n", SDL_GetError());
		SDL_Quit();
		return (-1);
	}
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
		SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	printf("b\n");
	if ((gl->w = SDL_CreateWindow("Scop", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 1000, 1000,
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL)) == 0
		|| (gl->contexte_opengl = SDL_GL_CreateContext(gl->w)) == 0)
	{
		if (gl->w == 0)
			ft_printf("Error creation of the window : %s\n", SDL_GetError());
		else
			ft_printf("%s\n", SDL_GetError());
		SDL_Quit();
		return (-1);
	}
	// glEnable(GL_DEPTH_TEST); ??
	// glDepthFunc(GL_LESS); ??
	return (ft_shaders("./shader/shader.vs", "./shader/shader.fs", gl));
}

static void	ft_gl_buffer(t_gl *gl)
{
	static float points[] = {1.0f, 1.0f, 0.0f, -1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f};

	gl->vbo = 0;
	gl->vao = 0;
	glGenBuffers(1, &gl->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, gl->vbo);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), points, GL_STATIC_DRAW);
	glGenVertexArrays(1, &gl->vao);
	glBindVertexArray(gl->vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, gl->vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

void		ft_init_data(t_gldata *data, t_fract *fract, t_gl *gl)
{
	if (fract != NULL)
	{
		ft_gl_buffer(gl);
		ft_bzero(data, sizeof(t_gldata));
		data->c_r = fract->c_r;
		data->c_i = fract->c_i;
		data->fractal = fract->fract;
	}
	data->exit = 0;
	data->max_it = 100.0f;
	data->zoom = 2.0f;
	data->step = 0.01;
	data->nb_zoom = 2;
	if (data->fractal == 0 || data->fractal == 2)
		data->x = -0.5f;
	else
		data->x = 0;
	data->y = 0;
}

void		ft_send_data(t_gl *gl, t_gldata *data, int color)
{
	unsigned int matloc;

	matloc = glGetUniformLocation(gl->program_id, "MaxIterations");
	glUniform1f(matloc, data->max_it);
	matloc = glGetUniformLocation(gl->program_id, "zoom");
	glUniform1f(matloc, data->zoom);
	matloc = glGetUniformLocation(gl->program_id, "x");
	glUniform1f(matloc, data->x);
	matloc = glGetUniformLocation(gl->program_id, "y");
	glUniform1f(matloc, data->y);
	matloc = glGetUniformLocation(gl->program_id, "c_r");
	glUniform1f(matloc, data->c_r);
	matloc = glGetUniformLocation(gl->program_id, "c_i");
	glUniform1f(matloc, data->c_i);
	matloc = glGetUniformLocation(gl->program_id, "fractal");
	glUniform1f(matloc, data->fractal);
	matloc = glGetUniformLocation(gl->program_id, "color_switch");
	glUniform1f(matloc, color);
}

// int			touch(SDL_Event e)
// {
// 	int key = 0;
// 	// int test[256];
// 	// if (SDL_PollEvent(&e))
// 	if (SDL_WaitEvent(&e))
// 	{
// 		if (e.type == SDL_KEYDOWN)
// 			printf("e.keysym = %d\n", e.key.keysym.sym);
// 		key = e.key.keysym.sym;
// 	}
// 	printf("key = %d\n", key);
// 	if (key == SDL_WINDOWEVENT_CLOSE || key == SDLK_ESCAPE)
// 		return (0);
// 	return (1);
// }

int			main_opengl(t_fract *fract)
{
	t_gl		gl;
	t_gldata	data;

	if (ft_init_glfw_gl(&gl) < 0)
	{
		ft_printf("Error in the initialisation of OpenGL\n");
		return (0);
	}
	ft_printf("OpenGL version: %s\n", glGetString(GL_VERSION));
	ft_printf("Shader version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	ft_init_data(&data, fract, &gl);
	// while (glfwGetKey(gl.w, GLFW_KEY_ESCAPE) != GLFW_PRESS
	// 	&& !glfwWindowShouldClose(gl.w) && !data.exit)
	while (!data.exit)
	{
		glUseProgram(gl.program_id);
		// if (touch(gl.evenements) == 0)
		// 	exit (0);
		// ft_send_data(&gl, &data, 0);
		ft_control(&gl, &data);
		// ft_control(&gl, &data);
		glBindVertexArray(gl.vao);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		SDL_GL_SwapWindow(gl.w);
		// glfwPollEvents();
		// glfwSwapBuffers(gl.w);
	}
	fract->c_r = data.c_r;
	fract->c_i = data.c_i;
	fract->fract = data.fractal;
	SDL_DestroyWindow(gl.w);
	SDL_Quit();
	// glfwTerminate();
	return (data.exit);
}
