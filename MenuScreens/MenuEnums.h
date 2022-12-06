#pragma once

namespace barra
{
    enum class MenuOptions
    {
        menu,
        play,
        options,
        rules,
        credits,
        exit
    };

    struct MenuUI
    {
        int fontSize;
        float xPosition;
        float yPosition;
        float xRepos;
        float yRepos;
    };

    MenuUI InitMenuUI();
}