#include <stdio.h>
#include "background.h"
int main(void){
    start_background_system();
    background_system_msg("echo Roguelike room loaded!");
    return 0;
}
