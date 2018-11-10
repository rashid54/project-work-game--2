#include <SFML/Graphics.hpp>
#include<bits/stdc++.h>
#define notSelected sf::Color::Blue
#define SIZE 10
using namespace sf;

void play_menu();
void options_menu();
void highscore_menu();
void help_menu();
struct {int x,y;} cloud[20];

void scroll(int &y, int &h, float &character_velocity);

void game(){
    srand(time(NULL));

    RenderWindow window(VideoMode(1200, 900), "JUMPING RABBIT");
    window.setFramerateLimit(60);

    Texture bgimage, cloud_texture, character_texture;
    bgimage.loadFromFile("pics/background.jpeg");
    cloud_texture.loadFromFile("pics/cloud1.png");
    character_texture.loadFromFile("pics/rabbit2.png");

    Sprite sCloud(cloud_texture), scharacter(character_texture);
    IntRect bgsource(0,1120,1300,745);
    Sprite bg(bgimage,bgsource);
    bg.setScale(0.6f,1.22f);

    for(int i = 0; i < SIZE; i++){
        cloud[i].x = std::rand() % 800;
        cloud[i].y = std::rand() % 500;
    }

    int x = 180, y = 100, h = 200;
    float character_velocity = 0;

    while(window.isOpen()){
        Event e;
        while(window.pollEvent(e)){
            if(e.type == Event::Closed)
                window.close();
            if(e.type==Event::MouseButtonPressed)
            {
                std::cout<< "x pos:"<<e.mouseButton.x<<"y pos:"<<e.mouseButton.y<<std::endl<<std::endl;
            }
            if(Keyboard::isKeyPressed(Keyboard::Space)&&character_velocity==0)character_velocity=-12;

        } // END EVENT LOOP

        // character_velocity is vertical acceleration
        if(y>520&& character_velocity>=0) character_velocity=0;
        else character_velocity += 0.5;
        y += character_velocity;

        //check_bounce(x, y, character_velocity);

        if(y < h)
            {
                scroll(y, h, character_velocity);
                bgsource.top+=character_velocity;
                bg.setTextureRect(bgsource);
            }

        scharacter.setPosition(x, y);

        window.draw(bg);
        window.draw(scharacter);

        // Draws the cloudforms on the screen
        for(int i = 0; i < SIZE; i++){
            sCloud.setPosition(cloud[i].x, cloud[i].y);
            window.draw(sCloud);
        }
        window.draw(scharacter);
        window.display();
    }

//    return 0;
}

void gen_cloud(){
    for(int i = 0; i < SIZE; i++){
        cloud[i].x = std::rand() % 800;
        cloud[i].y = std::rand() % 500;
    }
}

// Bounce is initiated when acceleration is downward and doodle is
// touching a cloudform.
void check_bounce(int &x, int &y, float &character_velocity){
    for(int i = 0; i < SIZE; i++)
        if((x + 50 > cloud[i].x) && (x + 20 < cloud[i].x + 68)
        && (y + 70 > cloud[i].y) && (y + 70 < cloud[i].y + 14) && (character_velocity > 0))
            character_velocity = -10;
}

void scroll(int &y, int &h, float &character_velocity){
    for(int i = 0; i < SIZE; i++){
        y = h; // doodle's y position set to 200

        cloud[i].y = cloud[i].y - character_velocity; // all cloudform y values rerender with character_velocity

        // When a cloudform goes below the view of the screen, it is redrawn at the
        // top of the screen with a random x coordinate.
        if(cloud[i].y > 900){
            cloud[i].y =0;
            cloud[i].x = std::rand() %800;
        }
    }
}


int main()
{
    int cursor=0;
    sf::RenderWindow window(sf::VideoMode(1200,900), "JUMPING RABBIT");
    sf::Texture menubgtexture;
    if(!menubgtexture.loadFromFile("pics/menubg.jpg")) std::cout<<"Error loading menubg"<<std::endl;
    sf::Sprite menubg(menubgtexture);
    menubg.setScale(1.3f,1.3f);

    sf::Font gamename,menuitems,style1;
    if(!gamename.loadFromFile("fonts/FORTE.ttf")) std::cout<<"Error loading gamename"<<std::endl;
    if(!menuitems.loadFromFile("fonts/MAGNETOB.ttf")) std::cout<<"Error loading menuitems"<<std::endl;
    if(!style1.loadFromFile("fonts/SitkaI.ttf")) std::cout<<"Error loading style1"<<std::endl;

    sf::Text gamename_text,menu_text[5];

    gamename_text.setFont(gamename);
    gamename_text.setString("JUMPING RABBIT");
    gamename_text.setCharacterSize(75);
    gamename_text.setScale(1.0f,1.0f);
    gamename_text.setOutlineThickness(1.0f);
    gamename_text.setFillColor(sf::Color::Green);
    gamename_text.setLetterSpacing(1.0f);
    gamename_text.setPosition(200,2);

    for(int i=0;i<5;i++)
    {
        menu_text[i].setFont(menuitems);
        menu_text[i].setCharacterSize(60);
        menu_text[i].setScale(1.0f,1.0f);
        menu_text[i].setPosition(60,330+(i*60));
        menu_text[i].setFillColor(notSelected);
    }
    menu_text[0].setString("Play");
    menu_text[1].setString("Options");
    menu_text[2].setString("Highscore");
    menu_text[3].setString("Help");
    menu_text[4].setString("Exit");
    menu_text[cursor].setFillColor(sf::Color::Cyan);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed||Keyboard::isKeyPressed(Keyboard::Escape))
                window.close();
            if (Keyboard::isKeyPressed(Keyboard::Down))
            {
                menu_text[cursor].setFillColor(Color::Blue);
                cursor=(cursor+1)%5;
                menu_text[cursor].setFillColor(Color::Cyan);
            }
            if (Keyboard::isKeyPressed(Keyboard::Up))
            {
                menu_text[cursor].setFillColor(Color::Blue);
                cursor=(cursor+4)%5;
                menu_text[cursor].setFillColor(Color::Cyan);
            }
            if(Keyboard::isKeyPressed(Keyboard::Enter))
            {
                if(cursor==0) {
                    window.close();
                    game();
                    sf::RenderWindow window(sf::VideoMode(1200,900), "JUMPING RABBIT");
                }
                else if(cursor==1) options_menu();
                else if(cursor==2) highscore_menu();
                else if(cursor==3) help_menu();
                else if(cursor==4) window.close();
            }

        }



        window.clear();
        window.draw(menubg);
        window.draw(gamename_text);
        for(int i=0;i<5;i++) window.draw(menu_text[i]);
        window.display();
    }

    return 0;
}


void play_menu(){
}
void options_menu(){}
void highscore_menu(){}
void help_menu(){}
