/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opengl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 13:39:00 by apouchet          #+#    #+#             */
/*   Updated: 2019/10/21 13:24:52 by floblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl.h"

static int		ft_init_glfw_gl(t_gl *gl)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	gl->window = glfwCreateWindow(FENETRE_X, FENETRE_Y, "OpenGL", NULL, NULL);
	glfwMakeContextCurrent(gl->window);
	if (!(gl->window))
	{
		ft_printf("Error while opening windows\n");
		glfwTerminate();
		return (-1);
	}
	glewExperimental = GL_TRUE;
	glewInit();
	ft_printf("OpenGL version: %s\n", glGetString(GL_VERSION));
	ft_printf("Shader version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	return (ft_shaders("shader.vs", "shader.fs", gl));
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

void	ft_init_data(t_gldata *data)
{
	data->maxIt = 100.0f;
	data->zoom = 2.0f;
	data->step = 0.01;
	data->nb_zoom = 2;
	if (data->fractal == 0 || data->fractal == 2)
		data->x = -0.5f;
	else
		data->x = 0;
	data->y = 0;
}

int		main_opengl(void)
{
	t_gl		gl;
	t_gldata	data;
	int			exit;

	exit = 0;
	if (ft_init_glfw_gl(&gl) < 0)
		return (-1);
	ft_gl_buffer(&gl);
	ft_bzero(&data, sizeof(t_gldata));
	ft_init_data(&data);
	while (glfwGetKey(gl.window, GLFW_KEY_ESCAPE) != GLFW_PRESS
		&& !glfwWindowShouldClose(gl.window) && !exit)
	{
		glUseProgram(gl.program_id);
		if (ft_control(&gl, &data) == 1)
			exit = 1;
		glBindVertexArray(gl.vao);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		glfwPollEvents();
		glfwSwapBuffers(gl.window);
	}
	glfwTerminate();
	return (exit);
}
