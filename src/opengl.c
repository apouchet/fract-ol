#include "gl.h"

// void render_text(const char *text, float x, float y, float sx, float sy) {
//   const char *p;

//   for(p = text; *p; p++) {
//     if(FT_Load_Char(face, *p, FT_LOAD_RENDER))
//         continue;
 
//     glTexImage2D(
//       GL_TEXTURE_2D,
//       0,
//       GL_RED,
//       g->bitmap.width,
//       g->bitmap.rows,
//       0,
//       GL_RED,
//       GL_UNSIGNED_BYTE,
//       g->bitmap.buffer
//     );
 
//     float x2 = x + g->bitmap_left * sx;
//     float y2 = -y - g->bitmap_top * sy;
//     float w = g->bitmap.width * sx;
//     float h = g->bitmap.rows * sy;
 
//     GLfloat box[4][4] = {
//         {x2,     -y2    , 0, 0},
//         {x2 + w, -y2    , 1, 0},
//         {x2,     -y2 - h, 0, 1},
//         {x2 + w, -y2 - h, 1, 1},
//     };
 
//     glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
//     glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
 
//     x += (g->advance.x/64) * sx;
//     y += (g->advance.y/64) * sy;
//   }
// }

static int	ft_init_glfw_gl(t_gl *gl)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	// glEnable(GL_BLEND);
	// glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	gl->w = glfwCreateWindow(FENETRE_X, FENETRE_X, "OpenGL", NULL, NULL);
	glfwMakeContextCurrent(gl->w);
	if (!(gl->w))
	{
		ft_printf("Error while opening windows\n");
		glfwTerminate();
		return (-1);
	}
	glewExperimental = GL_TRUE;
	glewInit();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	ft_printf("OpenGL version: %s\n", glGetString(GL_VERSION));
	ft_printf("Shader version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	return (ft_shaders("./shader/shader.vs", "./shader/shader.fs", gl));
}

static void	ft_gl_buffer(t_gl *gl)
{
	static float points[] = {
		1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 0.0f, 1.0f, 0.0f};
	// static float textcoord[] = {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f};

	gl->vbo = 0;
	gl->vao = 0;
	glGenBuffers(1, &gl->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, gl->vbo);
	glBufferData(GL_ARRAY_BUFFER, 20 * sizeof(float), points, GL_STATIC_DRAW);
	glGenVertexArrays(1, &gl->vao);
	glBindVertexArray(gl->vao);
	glBindBuffer(GL_ARRAY_BUFFER, gl->vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), textcoord, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
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
		data->info = 1;
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

int			main_opengl(t_fract *fract)
{
	t_gl		gl;
	t_gldata	data;

	if (ft_init_glfw_gl(&gl) < 0)
	{
		ft_printf("Error in the initialisation of OpenGL\n");
		return (0);
	}
	ft_init_data(&data, fract, &gl);
	ft_read_texture(gl.program_id, "hud.png");
	while (glfwGetKey(gl.w, GLFW_KEY_ESCAPE) != GLFW_PRESS
		&& !glfwWindowShouldClose(gl.w) && !data.exit)
	{
		glUseProgram(gl.program_id);
		ft_control(&gl, &data);
		glActiveTexture(GL_TEXTURE);
		glBindVertexArray(gl.vao);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		glfwPollEvents();
		glfwSwapBuffers(gl.w);
	}
	fract->c_r = data.c_r;
	fract->c_i = data.c_i;
	fract->fract = data.fractal;
	glfwTerminate();
	return (data.exit);
}