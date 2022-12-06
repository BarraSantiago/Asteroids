#include "DrawAdapted.h"

namespace barra
{
    Rectangle TextureToSourceRec(Texture2D texture)
    {
        int frameWidth = texture.width;
        int frameHeight = texture.height;
        return {0.0f, 0.0f, static_cast<float>(frameWidth), static_cast<float>(frameHeight)};
    }
}