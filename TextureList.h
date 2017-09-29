#include "texture.h"

texture blastimg;
texture character;
texture gameovr;
texture start;
texture highscor;
texture ship;
texture Mouse;
texture bullet;
texture opponent;
texture h1;
texture h2;
texture h3;
texture h4;
texture h5;
texture spacebar;
texture menuborder;
texture motion;
texture Earth;
texture Mars;


void textureInit()
{
    start.Create("background.bmp"); //adding image on start screen
	blastimg.Create("blastimg1.bmp");
	character.Create("main_backgroung.bmp");// cover pic
    gameovr.Create("Game_over.bmp");// game over pic
    start.Create("background.bmp"); //adding image on start screen

    ship.Create("ship.bmp");
    Earth.Create("Earth.bmp");
    Mouse.Create("Mouse.bmp");
    bullet.Create("bullet.bmp");
    opponent.Create("opp_bullet.bmp");
    Mars.Create("unnamed.bmp");

    h1.Create("1.bmp");
    h2.Create("2.bmp");
    h3.Create("3.bmp");
    h4.Create("4.bmp");
    h5.Create("5.bmp");

    motion.Create("keyboard.bmp");
    spacebar.Create("spacebar.bmp");
    menuborder.Create("menuborder.bmp");
}
