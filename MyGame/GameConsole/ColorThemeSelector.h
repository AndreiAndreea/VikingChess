#pragma once
#include "ColorTheme.h"

class ColorThemeSelector {
private:
    static ColorThemeSelector* instance;

    ColorThemeSelector() {} 

public:
    static ColorThemeSelector* getInstance() {
        if (!instance)
            instance = new ColorThemeSelector();
        return instance;
    }

    ColorTheme chooseTheme();
};
