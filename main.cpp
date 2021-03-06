
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include "MusicManager.hpp"

int main(int, char const**)
{
    
    srand((unsigned int) time(NULL));
    //Initialize the program
    MusicManager play;
    play.runProgram();
    return EXIT_SUCCESS;
}
