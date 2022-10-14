#include "Animation.h"

Animation::Animation(Texture* tex, Vector2 imageCount, Uint32 switchTime) :
    imageCount(imageCount),
    switchTime(switchTime),
    currentImage(0, 0)
{
    totalTime = 0;

    // REQUIRES: tex->getSize is divisible by imageCount
    uvRect.w = tex->getSize().x / imageCount.x;
    uvRect.h = tex->getSize().y / imageCount.y;
}

void Animation::update(int row, int colBegin, int colEnd, Uint32 deltaTime, bool faceRight)
{
    currentImage.y = row;
    totalTime += deltaTime;

    if (switchTime != 0.0f)
    {
        if (totalTime >= switchTime)
        {
            totalTime -= switchTime;
            currentImage.x++;
            if (currentImage.x < colBegin)
            {
                currentImage.x = colBegin;
            }
            else if (currentImage.x >= imageCount.x || currentImage.x > colEnd)
            {
                currentImage.x = colBegin;
            }
        }
    }
    else
    {
        currentImage.x = colBegin;
    }

    uvRect.y = currentImage.y * uvRect.h;

    /*
    if (faceRight)
    {
        uvRect.x = currentImage.x * uvRect.w;
        uvRect.w = abs(uvRect.w);
    }
    else
    {
        uvRect.x = (currentImage.x + 1) * abs(uvRect.w);
        uvRect.w = -abs(uvRect.w);
    }
    */
    uvRect.x = currentImage.x * uvRect.w;
    uvRect.w = abs(uvRect.w);

    ///Provide information
    this->row = row;
    this->col = currentImage.x;
    this->colBegin = colBegin;
    this->colEnd = colEnd;
}

void Animation::setTexture(Texture* tex)
{
    uvRect.w = tex->getSize().x / static_cast<float>(imageCount.x);
    uvRect.h = tex->getSize().y / static_cast<float>(imageCount.y);
}

void Animation::setSwitchTime(Uint32 switchTime)
{
    this->switchTime = switchTime;
}

SDL_Rect* Animation::getClip()
{
    return &uvRect;
}