//
// sdl.cpp for sdl in /home/scutar_n/rendu/CPP/cpp_arcade
//
// Made by Nathan Scutari
// Login   <scutar_n@epitech.net>
//
// Started on  Thu Mar 23 13:36:00 2017 Nathan Scutari
// Last update Mon Apr  3 15:34:56 2017 Nathan Scutari
//

#include <unistd.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

typedef struct	s_pos
{
  double	x;
  double	y;
}		t_pos;

void	move(t_pos *speed, SDL_Event event)
{
  double	value;

  value = 0.6;
  if (event.key.keysym.sym == SDLK_RIGHT)
    speed->x += value;
  else if (event.key.keysym.sym == SDLK_LEFT)
    speed->x -= value;
  else if (event.key.keysym.sym == SDLK_UP)
    speed->y -= value;
  else if (event.key.keysym.sym == SDLK_DOWN)
    speed->y += value;
}

void	unmove(t_pos *speed)
{
  double	value;

  value = 0.2;
  if (speed->x > value / 2)
    speed->x -= value;
  else if (speed->x <= value / 2 && speed->x > 0)
    speed->x = 0;
  if (speed->x < -(value / 2))
    speed->x += value;
  else if (speed->x >= -(value / 2) && speed->x < 0)
    speed->x = 0;
  if (speed->y > value / 2)
    speed->y -= value;
  else if (speed->y <= value / 2 && speed->y > 0)
    speed->y = 0;
  if (speed->y < -(value / 2))
    speed->y += value;
  else if (speed->y >= -(value / 2) && speed->y < 0)
    speed->y = 0;
}

void	loop_fps(int fps, int &prevtime, int &time)
{
  time = SDL_GetTicks();
  if (time - prevtime < fps)
    usleep((fps - (time - prevtime)) * 1000);
  prevtime = time;
}

int	game_loop(SDL_Surface *img, SDL_Surface *win, SDL_Rect *pos,
		  SDL_Surface *win_rect)
{
  t_pos		speed;
  int		fps;
  int		loop;
  int		prevtime;
  int		time;
  SDL_Event	event;
  SDL_Rect	posa;

  loop = 1;
  fps = 1000 / 60;
  SDL_EnableKeyRepeat(10, 10);
  posa.x = pos->x;
  posa.y = pos->y;
  speed.x = 0;
  speed.y = 0;
  prevtime = SDL_GetTicks();
  while (loop)
    {
      SDL_PollEvent(&event);
      if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
	loop = 0;
      else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_r)
	{
	  speed.x = 0;
	  speed.y = 0;
	  pos->x = 0;
	  pos->y = 0;
	}
      else if (event.type == SDL_KEYDOWN)
	move(&speed, event);
      else
	unmove(&speed);
      SDL_BlitSurface(win_rect, NULL, win, 0);
      pos->x += speed.x;
      pos->y += speed.y;
      posa.x = pos->x;
      posa.y = pos->y;
      SDL_BlitSurface(img, NULL, win, &posa);
      SDL_Flip(win);
      loop_fps(fps, prevtime, time);
    }
  return (0);
}

int	main(int ac, char **av)
{
  SDL_Surface	*win;
  SDL_Surface	*win2;
  SDL_Surface	*rect[720];
  SDL_Surface	*win_rect;
  SDL_Surface	*img;
  SDL_Event	event;
  SDL_Rect	pos;
  int		i;
  int		a;
  int		b;

  if ((SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1))
    return (1);
  win = SDL_SetVideoMode(1280, 720, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
  SDL_WM_SetCaption("La terreur m'habite", NULL);
  i = -1;
  pos.x = 0;
  SDL_FillRect(win, NULL, 0x00FFFF);
  win_rect = SDL_CreateRGBSurface(SDL_HWSURFACE, 1280, 720, 32, 0, 0, 0, 0);
  while (++i < 360)
    {
      a = i * 255 / 360;
      b = 255 - a;
      rect[i] = SDL_CreateRGBSurface(SDL_HWSURFACE, 1280, 1, 32, 0, 0, 0, 0);
      rect[i + 360] = SDL_CreateRGBSurface(SDL_HWSURFACE, 1280, 1, 32, 0, 0, 0, 0);
      SDL_FillRect(rect[i], 0, SDL_MapRGB(win->format, a, a, a));
      SDL_FillRect(rect[i + 360], 0, SDL_MapRGB(win->format, b, b, b));
      pos.y = i;
      SDL_BlitSurface(rect[i], 0, win_rect, &pos);
      pos.y = i + 360;
      SDL_BlitSurface(rect[i + 360], 0, win_rect, &pos);
    }
  pos.x = 0;
  pos.y = 0;
  SDL_BlitSurface(win_rect, 0, win, &pos);
  img = IMG_Load("/home/scutar_n/Desktop/perry.png");
  pos.x = (win->w / 2) - (img->w / 2);
  pos.y = (win->h / 2) - (img->h / 2);
  SDL_BlitSurface(img, 0, win, &pos);
  SDL_Flip(win);
  game_loop(img, win, &pos, win_rect);
  i = -1;
  while (++i < 360)
    {
      SDL_FreeSurface(rect[i]);
      SDL_FreeSurface(rect[i + 360]);
    }
  SDL_Quit();
  return (0);
}


//SDL_SetColorKey(surface, SDL_SRCCOLORKEY, color);
//blit
//SDL_SetColorKey(surafece, 0, color);

//SDL_SetAlpha(zozor, SDL_SRCALPHA, 128);
