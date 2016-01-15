#include<SDL.h>
#include<SDL_ttf.h>
#include<stdio.h>
#include<math.h>
#undef main


#define LEFT_BOUNDARY 0
#define RIGHT_BOUNDARY 640
#define TOP_BOUNDARY 0
#define BOTTOM_BOUNDARY 470

#define BRICK_ROWS 10
#define BRICK_COLS 10
int ShowMenu(SDL_Window *window);
int PlayGame(SDL_Window *window);
int ShowAbout(SDL_Window *window);
int ShowWelcomeScreen(SDL_Window *window);
int ShowHelp(SDL_Window * window);
int main()
{


	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		printf("SDL_Init Error: %s\n", SDL_GetError());
		return 1;
	}
	TTF_Init();
	TTF_Font* font = TTF_OpenFont("ARIAL.TTF", 12);

	SDL_Window *window = SDL_CreateWindow("Bricks and Ball", 10, 100, 640, 480, SDL_WINDOW_SHOWN);
	ShowWelcomeScreen(window);
	ShowMenu(window);
	SDL_Quit();//Should be called last

	return 0;
}
int ShowWelcomeScreen(SDL_Window *window)
{
	SDL_Surface* screen = SDL_GetWindowSurface(window);
	SDL_Renderer * ren = SDL_CreateSoftwareRenderer(screen);
	TTF_Font* font = TTF_OpenFont("ARIAL.TTF", 50);
	TTF_Font* smallFont = TTF_OpenFont("ARIAL.TTF", 20);
	char author[] = "Made by Joji Joseph";
	char str[50];
	SDL_Color fg = { 128, 0, 128, 50 };
	SDL_Surface *text_surface = TTF_RenderText_Solid(font, "Bricks And Ball", fg);
	int titleHeight = text_surface->h;
	int titleWidth = text_surface->w;

	SDL_Event event;
	SDL_Rect titleRect = { (640 - titleWidth) >> 1, 480, 0, 0 };
	for (int i = 480; i > 240 - titleHeight / 2; i -= 5)
	{
		SDL_RenderClear(ren);
		SDL_BlitSurface(text_surface, NULL, screen, &titleRect);

		SDL_UpdateWindowSurface(window);
		SDL_Delay(1);
		titleRect.y = i;
	}
	SDL_Rect authorRect = { 340, titleRect.y + text_surface->h + 10, 0, 0 };
	for (int i = 0; author[i] != NULL; ++i)
	{
		str[i] = author[i];
		str[i + 1] = 0;
		SDL_Surface *textAuthor = TTF_RenderText_Solid(smallFont, str, fg);
		authorRect.x = (340 - (textAuthor->w) / 2);
		SDL_RenderClear(ren);
		SDL_BlitSurface(text_surface, NULL, screen, &titleRect);
		SDL_BlitSurface(textAuthor, NULL, screen, &authorRect);
		SDL_UpdateWindowSurface(window);
		SDL_Delay(50);
	}
	while (1)
	{
		if (SDL_PollEvent(&event) == NULL)
		{

		}
		else
		{
			if (event.type == SDL_KEYUP || event.type == SDL_MOUSEBUTTONUP)
				return 0;
		}
	}
}
int ShowMenu(SDL_Window *window)
{
	SDL_Surface* screen = SDL_GetWindowSurface(window);
	SDL_Rect textLocation = { 200, 0, 0, 0 };
	int menu_index = -1;
	char menuItems[][20] = { "Play", "Help", "About", "Quit" };
	SDL_Event event;
	SDL_Color fg = { 128, 0, 128, 50 };
	SDL_Surface *text_surface;
	TTF_Font* font = TTF_OpenFont("ARIAL.TTF", 24);

	for (;;)
	{
		if (SDL_PollEvent(&event) == 0)
		{
			SDL_Renderer *ren = SDL_CreateSoftwareRenderer(screen);
			SDL_RenderClear(ren);
			for (int i = 0; i < 4; ++i){//This loop will print menu items
				textLocation.y = 100 + 30 * i;
				text_surface = TTF_RenderText_Solid(font, menuItems[i], fg);
				SDL_BlitSurface(text_surface, NULL, screen, &textLocation);
				SDL_FreeSurface(text_surface);
			}
			if (menu_index != -1)
			{
				fg = { 255, 0, 128, 50 };
				textLocation.y = 100 + 30 * menu_index;
				text_surface = TTF_RenderText_Solid(font, menuItems[menu_index], fg);
				SDL_BlitSurface(text_surface, NULL, screen, &textLocation);
				SDL_FreeSurface(text_surface);
				fg = { 128, 0, 128, 50 };
			}
			SDL_UpdateWindowSurface(window);
		}
		else
		{
			if (event.type == SDL_MOUSEMOTION)
			{
				int x = event.motion.x;
				int y = event.motion.y;
				int flag = -1;
				for (int i = 0; i < 4; ++i){

					if (x >= 150 && x <= 350 && y >= 100 + 30 * i && y <= 130 + 30 * i)
					{
						flag = i;

					}
				}
				menu_index = flag;

			}
			if (event.type == SDL_QUIT)
				return 0;
			if (event.type == SDL_MOUSEBUTTONUP)
			{

				int x = event.motion.x;
				int y = event.motion.y;
				int flag = -1;
				for (int i = 0; i < 4; ++i){

					if (x >= 150 && x <= 350 && y >= 100 + 30 * i && y <= 130 + 30 * i)
					{
						flag = i;

					}
				}
				switch (flag)
				{
				case 1:ShowHelp(window); break;
				case 3:return 0;
				case 2:ShowAbout(window);
					break;
				case 0:PlayGame(window);
				}
			}
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					return 0;
			}
		}
	}
}
int ShowAbout(SDL_Window *window)
{

	SDL_Surface * screen = SDL_GetWindowSurface(window);
	SDL_Renderer *ren = SDL_CreateSoftwareRenderer(screen);
	SDL_RenderClear(ren);
	char about[] = "This program is made by Joji Joseph";
	char str[50];
	SDL_Color fg = { 255, 0, 0 };
	SDL_Rect rect = { 120, 120, 0, 0 };
	TTF_Font *font = TTF_OpenFont("ARIAL.TTF", 20);//Case sensitive
	SDL_Event event;
	for (int i = 0; about[i] != 0; ++i)
	{
		str[i] = about[i];
		str[i + 1] = '\0';
		SDL_Surface *textArea = TTF_RenderText_Solid(font, str, fg);
		SDL_Delay(100);
		SDL_BlitSurface(textArea, NULL, screen, &rect);
		SDL_UpdateWindowSurface(window);
	}
	while (1)
	{
		if (SDL_PollEvent(&event) != 0 && (event.type == SDL_KEYUP || event.type == SDL_MOUSEBUTTONUP))
			break;
	}

}
int ShowHelp(SDL_Window *window)
{

	SDL_Surface * screen = SDL_GetWindowSurface(window);
	SDL_Renderer *ren = SDL_CreateSoftwareRenderer(screen);
	SDL_RenderClear(ren);
	char help[] = "Help is not completed. Please edit when you get time.";
	char str[100];
	SDL_Color fg = { 255, 0, 0 };
	SDL_Rect rect = { 120, 120, 0, 0 };
	TTF_Font *font = TTF_OpenFont("ARIAL.TTF", 20);//Case sensitive
	SDL_Event event;
	for (int i = 0; help[i] != 0; ++i)
	{
		str[i] = help[i];
		str[i + 1] = '\0';
		SDL_Surface *textArea = TTF_RenderText_Solid(font, str, fg);
		SDL_Delay(100);
		SDL_BlitSurface(textArea, NULL, screen, &rect);
		SDL_UpdateWindowSurface(window);
	}
	while (1)
	{
		if (SDL_PollEvent(&event) != 0 && (event.type == SDL_KEYUP || event.type == SDL_MOUSEBUTTONUP))
			break;
	}

}

int PlayGame(SDL_Window *window)
{
	int onPlay = 0;
	SDL_Surface * screen = SDL_GetWindowSurface(window);

	SDL_Surface *ballImage = SDL_LoadBMP("ball.bmp");
	SDL_Surface *brickImage = SDL_LoadBMP("brick.bmp");
	SDL_Surface *brickImage2 = SDL_LoadBMP("brick2.bmp");
	SDL_Surface *boardImage = SDL_LoadBMP("board.bmp");
	Uint32 colorKey = SDL_MapRGB(ballImage->format, 0, 0, 0);
	SDL_SetColorKey(ballImage, 1, colorKey);
	SDL_Renderer *ren = SDL_CreateSoftwareRenderer(screen);

	int state = 1, stop_action = 0;
	SDL_RenderClear(ren);
	SDL_SetRenderDrawColor(ren, 255, 0, 0, 100);
	float speed2 = 4;
	float speed = 2;
	SDL_Event event;
	SDL_Rect board = { 0, 450, 100, 20 };
	SDL_Rect ball = { 0, 430, 20, 20 };
	int bricks[10][10] = {
		{ 1, 0, 2, 0, 1, 0, 2, 0, 1, 0 },
		{ 0, 2, 0, 1, 0, 2, 0, 1, 0, 2 },
		{ 1, 0, 2, 0, 1, 0, 2, 0, 1, 0 },
		{ 0, 2, 0, 1, 0, 2, 0, 1, 0, 2 },
		{ 1, 0, 2, 0, 1, 0, 2, 0, 1, 0 },
		{ 0, 2, 0, 1, 0, 2, 0, 1, 0, 2 },
		{ 1, 0, 2, 0, 1, 0, 2, 0, 1, 0 },
		{ 0, 2, 0, 1, 0, 2, 0, 1, 0, 2 },
		{ 1, 0, 2, 0, 1, 0, 2, 0, 1, 0 },
		{ 0, 2, 0, 1, 0, 2, 0, 1, 0, 2 },
	};
	struct {
		float x, y;
	}dir;
	struct {
		float x, y;
	}pos;
	dir.x = 0.0;
	dir.y = -1.0;
	pos.x = ball.x;
	pos.y = ball.y;
	char gameOver[50];
	int score = 0;
	int maxscore = 0;
	for (int i = 0; i < 10; ++i)
	for (int j = 0; j < 10; ++j)
		maxscore += !!bricks[i][j];
	char str[50];
	SDL_Color fg = { 255, 0, 0 };
	SDL_Rect rect = { 120, 120, 0, 0 };
	TTF_Font *font = TTF_OpenFont("ARIAL.TTF", 20);//Case sensitive
	while (1)
	{
		switch (state){
		case 1:
			if (SDL_PollEvent(&event) == 0)
			{
				SDL_SetRenderDrawColor(ren, 0, 0, 0, 100);
				SDL_RenderClear(ren);
				SDL_SetRenderDrawColor(ren, 255, 0, 0, 100);
				for (int i = 0; i < BRICK_ROWS; ++i)
				{
					for (int j = 0; j < BRICK_COLS; ++j)
					{
						if (onPlay)
						{
							if (ball.y>i * 20 && ball.y<i * 20 + 20 && ball.x>j * 50 && ball.x < j * 50 + 50 && bricks[i][j] != 0)
							{
								switch (bricks[i][j])
								{
								case 2:dir.y = -dir.y; break;
								}
								bricks[i][j] = 0;
								score++;
								if (score == maxscore)state = 3;

							}

						}
						if (bricks[i][j] != 0)
						{
							SDL_Rect brick = { j * 50, i * 20, 50, 20 };
							switch (bricks[i][j])
							{
							case 1:SDL_BlitScaled(brickImage, NULL, screen, &brick); break;
							case 2:SDL_BlitScaled(brickImage2, NULL, screen, &brick); break;
							}

						}
					}
				}
				if (onPlay)
				{


					ball.x = (pos.x += dir.x*speed);
					ball.y = (pos.y += dir.y*speed);
					if (ball.x < LEFT_BOUNDARY)
						dir.x = -dir.x;
					if (ball.x + ball.w > RIGHT_BOUNDARY)
						dir.x = -dir.x;
					if (ball.y < TOP_BOUNDARY)
						dir.y = -dir.y;
					if ((ball.y + ball.h) >= board.y && (ball.y + ball.h) < (board.y + board.h) && (ball.x + ball.w) >= board.x && ball.x < (board.x + board.w))
					{
						if (stop_action == 0)
						{
							//printf("%d %d %d %d", ball.x, ball.y, board.x, board.y);
							dir.x = ((float)ball.x + ball.w / 2.0 - (board.x + board.w / 2.0)) / (board.w / 2.0);
							dir.y = -sqrt(1.1 - (dir.x*dir.x));
							stop_action = 1;
						}
					}
					else
					{
						stop_action = 0;
					}
					SDL_Delay(1);
				}
				SDL_BlitScaled(boardImage, NULL, screen, &board);
				SDL_BlitScaled(ballImage, NULL, screen, &ball);
				SDL_UpdateWindowSurface(window);
				if (ball.y > 480)state = 2;

			}
			else
			{
				if (event.type == SDL_MOUSEMOTION)
				{
					board.x = event.motion.x - board.w / 2;
					if (board.x < 0)board.x = 0;
					if (board.x + board.w>RIGHT_BOUNDARY)board.x = RIGHT_BOUNDARY - board.w;
					if (!onPlay)
					{

						ball.x = pos.x = event.motion.x - ball.w / 2;
						if (ball.x < board.w / 2 - ball.w / 2)ball.x = board.w / 2 - ball.w / 2;
						if (ball.x > RIGHT_BOUNDARY - board.w / 2 - ball.w / 2)ball.x = RIGHT_BOUNDARY - board.w / 2 - ball.w / 2;
					}
				}
				else if (event.type == SDL_MOUSEBUTTONUP)
				{
					onPlay = 1;
				}
				else if (event.type == SDL_KEYUP)
				{
					if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
						return 0;
				}
			}
			break;
		case 2:
			sprintf_s(gameOver, "Sorry, Game is Over. Your score:%d", score);
			SDL_SetRenderDrawColor(ren, 0, 0, 0, 100);
			SDL_RenderClear(ren);
			SDL_SetRenderDrawColor(ren, 0, 255, 0, 100);
			for (int i = 0; gameOver[i] != 0; ++i)
			{
				str[i] = gameOver[i];
				str[i + 1] = '\0';
				SDL_Surface *textArea = TTF_RenderText_Solid(font, str, fg);
				SDL_Delay(100);
				SDL_BlitSurface(textArea, NULL, screen, &rect);
				SDL_UpdateWindowSurface(window);
			}
			while (1){
				if (SDL_PollEvent(&event) == 0)
				{
					//Do nothing
				}
				else
				{
					if (event.type == SDL_KEYUP || event.type == SDL_MOUSEBUTTONUP)
						return 0;
				}

			}
			break;
		case 3:
			sprintf_s(gameOver, "Congrats! You Won By Scoring %d", score);
			SDL_SetRenderDrawColor(ren, 0, 0, 0, 100);
			SDL_RenderClear(ren);
			SDL_SetRenderDrawColor(ren, 0, 255, 0, 100);
			for (int i = 0; gameOver[i] != 0; ++i)
			{
				str[i] = gameOver[i];
				str[i + 1] = '\0';
				SDL_Surface *textArea = TTF_RenderText_Solid(font, str, fg);
				SDL_Delay(100);
				SDL_BlitSurface(textArea, NULL, screen, &rect);
				SDL_UpdateWindowSurface(window);
			}
			while (1){
				if (SDL_PollEvent(&event) == 0)
				{
					//Do nothing
				}
				else
				{
					if (event.type == SDL_KEYUP || event.type == SDL_MOUSEBUTTONUP)
						return 0;
				}

			}break;
		default:break;

		}
	}
}