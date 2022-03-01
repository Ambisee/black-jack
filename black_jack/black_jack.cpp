// black_jack.cpp :
// This file contains the main function
//

# include <iostream>
# include "screens.h"
# include "Option.h"

int main()
{
    bool run = true;
    Option* gameOptions = new Option();

    while (run) {
        int num = main_menu_screen();
        switch (num) {
            case 1:
                game_screen(gameOptions);
                break;
            case 2:
                option_screen(gameOptions);
                break;
            case 3:
                run = false;
            default:
                break;
        }
    }
    
    delete gameOptions;
    gameOptions = nullptr;

    return 0;
}