#include "text.h"

void Text::create(int size, string path)
{
    this->font = TTF_OpenFont(path.c_str(), size);
    if (!this->font)
    {
        cout << "TTF file could not be found!\nPath: " << path << "\nError: " <<  TTF_GetError() << endl;
        exit(1);
    }        
}

void Text::display(SDL_Renderer* renderer, SDL_Color color, string text)
{
    SDL_Surface* surface = TTF_RenderText_Solid(this->font, text.c_str(), color);
    if (!surface)
    {
        cout << "Unable to render text surface!\nError: " << TTF_GetError() << endl;
        exit(1);
    }

    this->texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(!this->texture)
    {
        cout << "Unable to create texture from rendered text!\nError: " << SDL_GetError() << endl;
        exit(1);
    }

    this->w = surface->w;
    this->h = surface->h;

    SDL_FreeSurface(surface);
}

void Text::render(SDL_Renderer* renderer, double x, double y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    this->rect.x = x;
    this->rect.y = y;
    this->rect.w = this->w;
    this->rect.h = this->h;
    SDL_RenderCopyEx(renderer, this->texture, clip, &this->rect, angle, center, flip);
}

void Text::destroy()
{
    SDL_DestroyTexture(this->texture);
}