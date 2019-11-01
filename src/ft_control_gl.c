/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_control_gl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 18:40:39 by apouchet          #+#    #+#             */
/*   Updated: 2019/11/01 13:39:45 by floblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl.h"

static void		ft_send_data(t_gl *gl, t_gldata *data, int color)
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

static void		ft_color_fractal(t_gl *gl, const unsigned char *KeyStates, t_gldata *data, int *color)
{
	int			fract_pre;

	// printf("la\n");
	fract_pre = data->fractal;
	if (KeyStates[SDL_SCANCODE_R])
		*color = 0;
	else if (KeyStates[SDL_SCANCODE_B])
		*color = 1;
	else if (KeyStates[SDL_SCANCODE_G])
		*color = 2;
	else if (KeyStates[SDL_SCANCODE_1] || KeyStates[SDL_SCANCODE_KP_1])// || KeyStates[SDL_SCANCODE_AMPERSAND])
		data->fractal = 0;
	else if (KeyStates[SDL_SCANCODE_2] || KeyStates[SDL_SCANCODE_KP_2])
		data->fractal = 1;
	else if (KeyStates[SDL_SCANCODE_3] || KeyStates[SDL_SCANCODE_KP_3])// || KeyStates[SDL_SCANCODE_QUOTEDBL])
		data->fractal = 2;
	else if (KeyStates[SDL_SCANCODE_4] || KeyStates[SDL_SCANCODE_KP_4])// || KeyStates[SDL_SCANCODE_QUOTE])
		data->fractal = 3;
	else if (KeyStates[SDL_SCANCODE_5] || KeyStates[SDL_SCANCODE_KP_5])// || KeyStates[SDL_SCANCODE_LEFTPAREN])
		data->fractal = 4;
	if (fract_pre != data->fractal || KeyStates[SDL_SCANCODE_SPACE])
		ft_init_data(data, NULL, gl);
}

static void		ft_mouse(t_gldata *data)
{
	int	x;
	int	y;
	int state;

	// SDL_PumpEvents();
	state = SDL_GetMouseState(NULL, NULL);
	SDL_GetRelativeMouseState(&x, &y);
	if (state & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		data->x -= x * data->step / 3;
		data->y -= y * data->step / 3;
	}
	else if (state & SDL_BUTTON(SDL_BUTTON_RIGHT))
	{
		SDL_GetMouseState(&x, &y);
		data->c_r = ((float)x - FENETRE_X / 2) / (FENETRE_X / 2);
		data->c_i = ((float)y - FENETRE_X / 2) / (FENETRE_X / 2);
	}
}

// void		hud_print(t_gldata *data)
// {
// 	SDL_Surface *ecran = NULL, *texte = NULL, *fond = NULL;
//     SDL_Rect position;
//     SDL_Event event;
//     TTF_Font *police = NULL;
//     SDL_Color couleurNoire = {0, 0, 0};
//     int continuer = 1;

//     SDL_Init(SDL_INIT_VIDEO);
//     TTF_Init();

//     ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
//     SDL_WM_SetCaption("Gestion du texte avec SDL_ttf", NULL);

//     fond = IMG_Load("moraira.jpg");

//     /* Chargement de la police */
//     police = TTF_OpenFont("angelina.ttf", 65);
//     /* Écriture du texte dans la SDL_Surface texte en mode Blended (optimal) */
//     texte = TTF_RenderText_Blended(police, "Salut les Zér0s !", couleurNoire);

//     while (continuer)
//     {
//         SDL_WaitEvent(&event);
//         switch(event.type)
//         {
//             case SDL_QUIT:
//                 continuer = 0;
//                 break;
//         }

//         SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

//         position.x = 0;
//         position.y = 0;
//         SDL_BlitSurface(fond, NULL, ecran, &position); /* Blit du fond */

//         position.x = 60;
//         position.y = 370;
//         SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */
//         SDL_Flip(ecran);
//     }

//     TTF_CloseFont(police);
//     TTF_Quit();

//     SDL_FreeSurface(texte);
//     SDL_Quit();
// }

static void		ft_move_zoom(const unsigned char *KeyStates, t_gldata *data)
{
	if ((data->nb_zoom > 0 || (data->nb_zoom > -1000 && data->fractal == 4))
		&& KeyStates[SDL_SCANCODE_S])//( || (e.wheel.y > 0 && e.type == SDL_MOUSEWHEEL)))
	{
		data->zoom = data->zoom * 1.01;
		data->step *= 1.01;
		data->nb_zoom--;
		// hud_print(data);
	}
	else if (data->nb_zoom < 1200 && KeyStates[SDL_SCANCODE_W])//( || (e.wheel.y < 0 && e.type == SDL_MOUSEWHEEL)))
	{
		data->zoom = data->zoom / 1.01;
		data->step /= 1.01;
		data->nb_zoom++;
	}
	else if (KeyStates[SDL_SCANCODE_LEFT])
		data->x = data->x - data->step;
	else if (KeyStates[SDL_SCANCODE_RIGHT])
		data->x = data->x + data->step;
	else if (KeyStates[SDL_SCANCODE_UP])
		data->y = data->y - data->step;
	else if (KeyStates[SDL_SCANCODE_DOWN])
		data->y = data->y + data->step;
}

static	void	ft_iter_exit(const unsigned char *KeyStates, t_gldata *data)
{
	char		*buf;

	if (KeyStates[SDL_WINDOWEVENT_CLOSE] || KeyStates[SDL_SCANCODE_ESCAPE])
	{
		printf("exit\n");
		data->exit = 2;
	}
	if (KeyStates[SDL_SCANCODE_D])
	{
		ft_printf("MaxIterations = %f\n", data->max_it);
		data->max_it++;
	}
	else if (data->max_it > 2 && KeyStates[SDL_SCANCODE_A])
	{
		ft_printf("MaxIterations = %f\n", data->max_it);
		data->max_it--;
	}
	else if (KeyStates[SDL_SCANCODE_P])
	{
		if ((buf = (char*)malloc(sizeof(char) * (FENETRE_X * FENETRE_X * 3))))
		{
			glReadPixels(0, 0, FENETRE_X, FENETRE_X, GL_BGR, GL_UNSIGNED_BYTE, buf);
			ft_screen_gl(buf);
			free(buf);
		}
		else
			ft_printf("Error : fail to malloc for screenshot\n");
	}
	if (KeyStates[SDL_SCANCODE_RETURN])
	{
		printf("return\n");
		data->exit = 1;
	}
}

void			ft_control(t_gl *gl, t_gldata *data)
{
	static int	color;

	SDL_PumpEvents();
	SDL_Event e;
	SDL_PollEvent(&e);
	if (e.type == SDL_QUIT)
		data->exit = 2;
	const unsigned char *KeyStates = SDL_GetKeyboardState(NULL);
	ft_mouse(data);
	ft_iter_exit(KeyStates, data);
	ft_move_zoom(KeyStates, data);
	ft_color_fractal(gl, KeyStates, data, &color);
	ft_send_data(gl, data, color);
}
