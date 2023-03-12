#include <string>

using std::string;

class RubyImage {
    public:
        bool loaded = false;
        SDL_Rect rect;
        SDL_Rect clip_rect;

        SDL_Surface* surface;

        double scale;

        string path;
        
        RubyImage(int cx, int cy, int cscale, string cpath) {
            rect.x = cx;
            rect.y = cy;
            scale = cscale;
            path = cpath;
        }

        //Declare functions
        void registerImage();
        bool loadImage();
        void blit(SDL_Surface* parentSurface);
        ~RubyImage();
        double getX();
        double getY();
        void setX(double x);
        void setY(double y);
        void setScale(double s);
};

std::vector<RubyImage*> IMAGE_REGISTRY;

void RubyImage::registerImage() {
    IMAGE_REGISTRY.push_back(this);
}

bool RubyImage::loadImage() {
    printf("Loading image %s!\n", path.c_str());
    surface = SDL_LoadBMP(path.c_str());
    if(surface == NULL) {
        return false;
    }
    rect.w = surface->w * scale;
    rect.h = surface->h * scale;
    clip_rect = rect;
    loaded = true;
    return true;
}

void RubyImage::blit(SDL_Surface* parentSurface) {
    if(!loaded) {
        loadImage();
        return;
    }
    SDL_BlitSurface(surface, &clip_rect, parentSurface, &rect);
}


RubyImage::~RubyImage() {
    printf("surface freed.\n");
    SDL_FreeSurface(surface);
}

double RubyImage::getX() {
    return rect.x;
}

double RubyImage::getY() {
    return rect.y;
}

void RubyImage::setX(double x) {
    rect.x = x;
}

void RubyImage::setY(double y) {
    rect.y = y;
}

void RubyImage::setScale(double s) {
    scale = s;
    rect.w = surface->w * scale;
    rect.h = surface->h * scale;
    clip_rect = rect;
}

class RubySpriteSheet {
public:
    RubyImage* src;
    int row;
    int col;
    int rowWidth;
    int colHeight;
    
    RubySpriteSheet(RubyImage* src, int rowWidth, int colHeight);
    void blit();
    void RecalculateClipBox();
    void setX(double x) { src->setX(x); }
    void setY(double y) { src->setY(y); }
    void setRow(int row);
    void setCol(int col);
    double getX() { return src->getX(); }
    double getY() { return src->getY(); }
};

RubySpriteSheet::RubySpriteSheet(RubyImage* src, int rowWidth, int colHeight) {
    this->src = src;
    this->rowWidth = rowWidth;
    this->colHeight = colHeight;
    RecalculateClipBox();
}

void RubySpriteSheet::blit() {
    src->blit(screenSurface);
}

void RubySpriteSheet::RecalculateClipBox() {
    src->clip_rect.w = rowWidth;
    src->clip_rect.h = colHeight;
    src->clip_rect.x = rowWidth * row;
    src->clip_rect.y = colHeight * col;
}

void RubySpriteSheet::setCol(int col) {
    this->col = col;
    RecalculateClipBox();
}

void RubySpriteSheet::setRow(int row) {
    this->row = row;
    RecalculateClipBox();
}