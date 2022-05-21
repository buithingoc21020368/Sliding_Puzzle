#include "graphics.h"
#include <iostream>
#include <SDL_ttf.h>
#include <SDL_image.h>

//Setup graphics
bool Graphics::setup() {

    //Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cerr << "Error: init" << SDL_GetError() << std::endl;
        return false;
    }
    
    //Create window
    window = SDL_CreateWindow("Sliding Puzzle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        std::cerr << "Error: Create window" << SDL_GetError() << std::endl;
        return false;
    }
    
    //Create drawing pen
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        std::cerr << "Error: Create renderer" << SDL_GetError() << std::endl;
        return false;
    }
    
    //Initialize the truetype font API 
    if (TTF_Init() < 0) {
        std::cerr << "SDL_ttf could not initialise" << TTF_GetError() << std::endl;
        return false;
    }


    cat = IMG_LoadTexture(renderer, "media/graphics/cat2.png");
    if (cat == NULL) {
        std::cerr << "Error: Load cat texture";
        return false;
    }
    return true;
}

//Release memory
void Graphics::destroy() {
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;
    tilenumber = NULL;
    clicks = NULL;
    wintext = NULL;
    menutext = NULL;
    menuinstr = NULL;
    cat = NULL;
}

//Setup grid size
void Graphics::setGridSize(const int& n) {
    grid = n;
    rawSize = (WINDOW_WIDTH - 2*WINDOW_PADDING) / grid;
    TILE_PADDING = rawSize / 10;
    TILE_SIZE    = rawSize - TILE_PADDING;
}

//Draw board
void Graphics::drawBoard(const std::vector<Tile>& t, const bool& drawnumber) {
    for (int i = 0; i < t.size(); ++i) {
        SDL_Rect temp = t[i].position();
        
        if      (t[i].tileType() == Tile::type::invisible)
            SDL_SetRenderDrawColor(renderer, 163, 118, 172, 1); //empty board colour
        
        else if (t[i].tileType() == Tile::type::rollover || t[i].tileType() == Tile::type::buttonpressed)
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1); //highlight board colour
        
        else if (t[i].tileType() == Tile::type::shadow)
            SDL_SetRenderDrawColor(renderer, 100, 65, 107, 1); //shadow colour
        
        else
            SDL_SetRenderDrawColor(renderer, 237, 229, 239, 1); //default board colour
        
        SDL_RenderFillRect(renderer, &temp);
        
        if (drawnumber){
            if (t[i].tileType() != Tile::type::invisible) {
                std::cout << "Check tile" << '\n';
                std::string num = std::to_string(i+1); //position numbers count from 1
                tilenumber = renderText(num, "media/font/arial.ttf", fontcolour, 25);
                SDL_QueryTexture(tilenumber, NULL, NULL, &temp.w, &temp.h);
                renderTexture(tilenumber, temp.x+(TILE_SIZE/2 - temp.w/2), temp.y+(TILE_SIZE/2 - temp.h/2), NULL);
            }
        }
    }
}

void Graphics::renderCat(const std::vector<Tile>& tiles, const std::vector<SDL_Rect>& positions) {
    // for all but the last (invisible) tile
    for (int i = tiles.size()-2; i >= 0; --i) {
        for (int j = tiles.size()-2; j >= 0; --j) {
            // 'attach' tile position n to position of cat photo
            SDL_Rect temp = positions[j];
            renderTexture(cat, tiles[j].position().x, tiles[j].position().y, &temp);
        }
    }
}

void Graphics::updateClicks(const int& n) {
    std::string count = std::to_string(n);
    std::string message = "Clicks: " + count;
    clicks = renderText(message, "media/font/arial.ttf", fontcolour, 15);
    int W; int H;
    SDL_QueryTexture(clicks, NULL, NULL, &W, &H);
    
    SDL_Rect clickBanner       { WINDOW_WIDTH/2-W, WINDOW_HEIGHT/6-3*H, 2*W, 2*H };
    SDL_Rect clickBannerShadow { WINDOW_WIDTH/2-W + 3, WINDOW_HEIGHT/6-3*H + 3, 2*W, 2*H};
    SDL_SetRenderDrawColor     (renderer, 100, 65, 107, 1);
    SDL_RenderFillRect         (renderer, &clickBannerShadow);
    SDL_SetRenderDrawColor     (renderer, 237, 229, 239, 1);
    SDL_RenderFillRect         (renderer, &clickBanner);
    renderTexture(clicks, (0.77*(clickBanner.x+clickBanner.w) - W/2), (0.8*(clickBanner.y+clickBanner.h) - H/2), NULL);
}

void Graphics::winMessage(const bool& win, const int& clicks, const std::string& message) {
    if (win == true && clicks > 0){
        wintext = renderText(message, "media/font/arial.ttf", fontcolour, 15);
        int W; int H;
        SDL_QueryTexture(wintext, NULL, NULL, &W, &H);
        
        SDL_Rect winBannerShadow { WINDOW_PADDING + 3, WINDOW_PADDING+TILE_SIZE+TILE_PADDING + 3,
                                   3*TILE_SIZE + 2*TILE_PADDING, TILE_SIZE};
        SDL_Rect winBanner       { WINDOW_PADDING, WINDOW_PADDING+TILE_SIZE+TILE_PADDING,
                                   3*TILE_SIZE + 2*TILE_PADDING, TILE_SIZE};
        SDL_SetRenderDrawColor   (renderer, 100, 65, 107, 1);
        SDL_RenderFillRect       (renderer, &winBannerShadow);
        SDL_SetRenderDrawColor   (renderer, 237, 229, 239, 1);
        SDL_RenderFillRect       (renderer, &winBanner);
        renderTexture(wintext, (0.5*WINDOW_WIDTH - 0.5*W), (0.5*WINDOW_HEIGHT - H), NULL);
    }
}

void Graphics::menuInstruction(const std::string& message) {
    SDL_Color darkpink { 100, 65, 107, 1 };
    menuinstr = renderText(message, "media/font/arial.ttf", darkpink, 12);
    int W; int H;
    SDL_QueryTexture(menuinstr, NULL, NULL, &W, &H);
    renderTexture(menuinstr, (0.5*WINDOW_WIDTH - 0.5*W), (WINDOW_HEIGHT - 0.5*WINDOW_PADDING), NULL);
}

void Graphics::menuText(std::vector<Tile> tiles, const bool& catmode) {
    int number = 3;
    int W; int H;
    
    for (int i = 0; i < 6; ++i){
        std::string numStr = std::to_string(number);
        std::string message = numStr + " x " + numStr;
        
        menutext = renderText(message, "media/font/arial.ttf", fontcolour, 25);
        SDL_QueryTexture(menutext, NULL, NULL, &W, &H);
        renderTexture(menutext, (tiles[i].position().x + 0.5*tiles[i].position().w - 0.5*W),
                                (tiles[i].position().y + 0.5*tiles[i].position().h - 0.5*H), NULL);
        number += 1;
    }
    if (catmode){
        SDL_Color tilecolour { 237, 229, 239, 1};
        menutext = renderText("Cat Mode", "media/font/arial.ttf", tilecolour, 20);
        SDL_QueryTexture(menutext, NULL, NULL, &W, &H);
        renderTexture(menutext, (tiles[6].position().x + 0.5*tiles[6].position().w - 0.5*W + 2),
                                (tiles[6].position().y + 0.5*tiles[6].position().h - 0.5*H + 2), NULL);
    }
    
    menutext = renderText("START", "media/font/arial.ttf", fontcolour, 25);
    SDL_QueryTexture(menutext, NULL, NULL, &W, &H);
    renderTexture(menutext, (tiles[7].position().x + 0.5*tiles[7].position().w - 0.5*W),
                            (tiles[7].position().y + 0.5*tiles[7].position().h - 0.5*H), NULL);
    
    menutext = renderText("Select your grid size:", "media/font/arial.ttf", fontcolour, 20);
    SDL_QueryTexture(menutext, NULL, NULL, &W, &H);
    renderTexture(menutext, 0.5*WINDOW_WIDTH - 0.5*W, WINDOW_PADDING-1.5*H, NULL);
}

void Graphics::renderTexture(SDL_Texture *tex, int x, int y, SDL_Rect *clip = NULL) {
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    if (clip != NULL){
        dst.w = clip->w;
        dst.h = clip->h;
    }
    else {
        SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    }
    SDL_RenderCopy(renderer, tex, clip, &dst);
}

SDL_Texture* Graphics::renderText(const std::string &message, const std::string &filepath, SDL_Color colour, int fontsize) {
    //Open the font
    TTF_Font *font = TTF_OpenFont(filepath.c_str(), fontsize);
    if (font == NULL){
        std::cerr << "TTF_OpenFont" << TTF_GetError;
        return NULL;
    }
    //render to a surface as that's what TTF_RenderText returns
    SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), colour);
    if (surf == NULL){
        TTF_CloseFont(font);
        std::cout << "TTF_RenderText" << TTF_GetError;
        return NULL;
    }
    //load that surface into texture
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
    if (texture == NULL){
        std::cout << "CreateTexture" << SDL_GetError();
    }
    //Clean up surface and font
    SDL_FreeSurface(surf);
    TTF_CloseFont(font);
    return texture;
}