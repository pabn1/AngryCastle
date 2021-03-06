#include "Texture.h"

Texture::Texture(Window *window, std::string filename):
	clipRect(),
	flip(false)
{
	renderer = window->getRenderer();
	texture = loadImage(filename);

	// Set width and height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

Texture::~Texture()
{

}

SDL_Texture *Texture::loadImage(std::string filename)
{
//	printf("Loading %s\n", filename.c_str());
	SDL_Surface* surface = IMG_Load(filename.c_str());

	if (!surface) {
		printf("Tekstuurin lataaminen ei onnistunut\n");
		printf("IMG_LoadTexture: %s\n", IMG_GetError());
		return NULL;
	}

	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,
												  0xFF, 0, 0xFF));

	SDL_Texture *newTexture = SDL_CreateTextureFromSurface(renderer, surface);

	if (!newTexture) {
		printf("Unable to create texture from %s!\nSDL Error: %s\n", filename.c_str(), SDL_GetError());
		return NULL;
	}

	SDL_FreeSurface(surface);

	return newTexture;
}

// source = kuvasta leikatun alueen sijainti ja koko
void Texture::render(int x, int y)
{
	// NOTE(jouni): Jos source on tyhj� k�ytet��n kuvan alkup. kokoa
	if (clipRect.w <= 0 && clipRect.h <= 0)
	{
		int width, height;
		SDL_QueryTexture(texture, NULL, NULL, &width, &height);

		SDL_Rect clip = {0, 0, width, height};
		clipRect = clip;
	}

	SDL_Rect destination = {x, y, clipRect.w, clipRect.h};
	SDL_RendererFlip flag = SDL_FLIP_NONE;

	if (flip) {
		flag = SDL_FLIP_HORIZONTAL;
	}

	SDL_RenderCopyEx(renderer, texture, &clipRect, &destination, 0, NULL, flag);

	/*
	int SDL_RenderCopyEx(SDL_Renderer*          renderer,
                     SDL_Texture*           texture,
                     const SDL_Rect*        srcrect,
                     const SDL_Rect*        dstrect,
                     const double           angle,
                     const SDL_Point*       center,
                     const SDL_RendererFlip flip)
	*/
}

void Texture::free()
{
	SDL_DestroyTexture(texture);
}

void Texture::crop(SDL_Rect rect)
{
	clipRect.x = rect.x;
	clipRect.y = rect.y;
	clipRect.w = rect.w;
	clipRect.h = rect.h;
}

int Texture::getWidth()
{
	return width;
}

int Texture::getHeight()
{
	return height;
}