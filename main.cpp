//**the include files**
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<bits/stdc++.h>
#include <sys/stat.h>
#include "Collision.hpp"
#include "Collision.cpp"
//#include "scorer.cpp"
//**the sizes declarations ****
#define window_width 1200
#define window_length 900
#define bg_width 700
#define bg_length 2500
#define character_width 200
#define character_length 300
#define brick_width 200
#define brick_length 50
#define cloud_width 0
#define cloud_length 0
//*** the default values declarations****
#define notSelectedColor sf::Color::Blue
#define SIZE 10
#define top_ground 550
#define max_brick 200
#define game_speed (1+(0.1*speed))
#define ground brick[brick_count].y+65
using namespace sf;
//***********structures***********
struct coordinate{int x,y;};
//***********functions*************
inline bool file_exists (const std::string& name) {
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}
class Scorer
{
    int high[10],n;
    std::string name[10],date[10];
    Font font;
    Text high_s,name_s,date_s;
    void get_data()
    {
        std::freopen("save/score.dat","r",stdin);
        for(n=0;std::scanf("%d",high[n])==1;n++)
        {
            std::cin>>name[n]>>date[n];
        }
        std::fclose(stdin);
    }
    std::string &enter_name()
    {
        sf::RenderWindow window(sf::VideoMode(700, 500), "SFML works!",sf::Style::None);
        RectangleShape rect( Vector2f (500,70));
        rect.setPosition(100,200);
        rect.setFillColor(Color::Red);
        rect.setOutlineThickness(2);
        Font font;
        font.loadFromFile("FORTE.ttf");
        sf::Text text,speech1,speech2;
        speech1.setCharacterSize(40);
        speech1.setFont(font);
        speech2.setCharacterSize(40);
        speech2.setFont(font);
        text.setCharacterSize(60);
        text.setFont(font);
        sf::String str;
        text.setPosition(110,200);
        speech1.setPosition(40,40);
        speech2.setPosition(200,300);

        speech2.setString("Maximum 10 letters");
        speech1.setString("You have achieved the honor to enter\nyour name in the HALL OF FAME");
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::TextEntered)
                {
                    // Handle ASCII characters only
                    if (event.text.unicode < 128)
                    {
                        str += static_cast<char>(event.text.unicode);
                        text.setString(str);
                    }
                }
                if((event.type==Event::KeyPressed&&Keyboard::isKeyPressed(Keyboard::Enter))||str.getSize()==10)
                {
                    std::string st;
                    for(String ::Iterator i=str.begin();i!=str.end();i++)
                        st=st+ (*i);
                    return st;

                }

            }

            window.clear(Color::Blue);
            window.draw(rect);
            window.draw(speech1);
            window.draw(speech2);
            window.draw(text);
            window.display();
        }
    }


public:
    scorer()
    {
        font.loadFromFile("font/FORTE.ttf");
        high_s.setFont(font);
        name_s.setFont(font);
        date_s.setFont(font);
        high_s.setPosition(300,300);
        name_s.setPosition(500,300);
        date_s.setPosition(700,300);
        high_s.setCharacterSize(2);
        name_s.setCharacterSize(2);
        date_s.setCharacterSize(2);
        get_data();
    }
    void print_data(RenderWindow &window)
    {
        Texture texture;
        texture.loadFromFile("pics/help.png");
        Sprite menubg(texture);
        Event e;
        bool skip=false;
        for(int i=0;i<n;i++)
        {
            while(window.pollEvent(e))
            {
                if(e.type == e.KeyPressed)
                {
                    skip=true;
                }
            }
            char str[10];
            sprintf(str,"%d",high[i]);
            high_s.setString(str);
            name_s.setString(name[i]);
            date_s.setString(date[i]);
            high_s.move(60,0);
            name_s.move(60,0);
            date_s.move(60,0);
            if(skip==false)
            {
                high_s.move(0,-400);
                name_s.move(0,-400);
                date_s.move(0,-400);
                for(int j=0;j<20;j++)
                {
                    high_s.move(0,20);
                    name_s.move(0,20);
                    date_s.move(0,20);
                    window.draw(high_s);
                    window.draw(name_s);
                    window.draw(date_s);
                    window.draw(menubg);
                    window.display();
                }
            }
            window.draw(high_s);
            window.draw(name_s);
            window.draw(date_s);
            window.draw(menubg);
            window.display();
        }
        high_s.setPosition(300,300);
        name_s.setPosition(500,300);
        date_s.setPosition(700,300);
    }
    void input_score(int score)
    {
        std::freopen("save/data.dat","w",stdout);
        for(int i=0;i<n||i<10;i++)
        {
            if(score>high[i])
            {
                auto t = std::time(nullptr);
                auto tm = *std::localtime(&t);
                std::printf("%d %s %s\n",score,enter_name().c_str(),std::put_time(&tm, "%d-%m-%Y"));
                continue;
            }
            std::printf("%d %s %s\n",high[i],name[i],date[i]);
        }
        get_data();
    }
    int &get_high()
    {
        return high[0];
    }
};

class animation
{
    Texture texture;
    Sprite name;
    IntRect box;
    int t,width,minsize;
public:

    void load(char *a,int b)
    {
        texture.loadFromFile(a);
        width=texture.getSize().x;
        minsize=width/b;
        box.left=0;box.top=0;box.width=minsize;box.height=texture.getSize().y;
        name.setTexture(texture);
        name.setTextureRect(box);
    }
    void pos(int a,int b)
    {
        name.setPosition(a,b);
    }
    void set_pic(int a)
    {
        box.left=minsize*a;
        name.setTextureRect(box);
    }
    void set_pic(int a,int b,int delay)
    {

    }
    Sprite &print()
    {
        return name;
    }
};
class Game
{
    Scorer scorer;
    int brick_count,x , y ,speed,score,fuel,level,mapnum,highscore,level_score,jack,life;
    char text[10];
    Font values;
    Text score_text,highscore_text,level_text;
    float character_velocity ,brick_velocity,gravitation,jump_accelaration;
    coordinate cloud[20],brick[max_brick];
    IntRect bgsource;
    Texture bgimage_texture,cloud_texture, character_texture1,character_texture2,character_texture3,brick_texture;
    Sprite sCloud, scharacter,sbrick,bg;
    Event event;
    animation sidewindow,life_ani;

    Music background_game_sound;
    SoundBuffer jump_soundbuffer;
    Sound jump_sound;
    SoundBuffer level_up_soundbuffer;
    Sound level_up_sound;
    SoundBuffer dead_soundbuffer;
    Sound dead_sound;
    SoundBuffer back_soundbuffer;
    Sound back_sound;

    void brick_create(int i)
    {
        if(i<2)        // level 1 brick creation
        {
            brick[brick_count].x=(window_length*(brick_count%2))-brick_width;
        }
        else   // level 3 brick creation
        {
            srand(time(NULL));
            brick[brick_count].x=(window_length*(rand()%2))-brick_width;
        }
        if(brick[brick_count].x*brick_velocity>0)       // fixing brick_velocity direction
        {
            brick_velocity*=-1;
        }
        brick[brick_count].y=brick[brick_count-1].y - brick_length;   // new brick height
    }
    void scroll();
public:
    Game();
    bool DEAD;
    bool game(sf::RenderWindow &gamewindow,int volume=3);
    int gethigh()
    {
        int high;
        std::freopen("save/score.dat","r",stdin);
        std::scanf("%d",&high);
        std::fclose(stdin);
        return high;
    }
    void print_high(int high)
    {
        std::freopen("save/score.dat","w",stdout);
        std::printf("%d\n",high);
        std::fclose(stdout);
    }
};

class MENU
{
    Game game;
    sf::Texture menubgtexture,sound_arrow_texture;
    sf::Sprite menubg,sound_arrow;
    sf::Font gamename,menuitems,style1;
    sf::Text gamename_text,menu_text[6],options_text[5];
    sf::Event event;
    animation sound;

    Music background_music;
    SoundBuffer updown_soundbuffer;
    Sound updown_sound;
    SoundBuffer select_soundbuffer;
    Sound select_sound;
    SoundBuffer exit_soundbuffer;
    Sound exit_sound;
    SoundBuffer invalid_soundbuffer;
    Sound invalid_sound;
    SoundBuffer sound_change_soundbuffer;
    Sound sound_change;


    int cursor,screen_x,screen_y,sound_level;
public:
    MENU();
    int main_menu(RenderWindow &window);
    int option_menu(RenderWindow &window);
    void highscore_menu(RenderWindow &window);
    void help_menu(RenderWindow &window);
    int gethigh()
    {
        int high;
        std::freopen("save/score.dat","r",stdin);
        std::scanf("%d",&high);
        std::fclose(stdin);
        return high;
    }
    int get_sound()
    {
        int value;
        std::freopen("save/data.dat","r",stdin);
        std::scanf("%d",&value);
        std::fclose(stdin);
        return value;
    }
    void print_sound(int value)
    {
        std::freopen("save/data.dat","w",stdout);
        std::printf("%d\n",value);
        std::fclose(stdout);
    }
    void set_default()
    {
        std::freopen("save/data.dat","w",stdout);
        std::printf("%d\n",3);
        std::fclose(stdout);
        std::freopen("save/score.dat","w",stdout);
        std::printf("%d\n",0);
        std::fclose(stdout);
        sound_level=3;
        sound.set_pic(3);
        background_music.setVolume(sound_level*15);
        updown_sound.setVolume(sound_level*15);
        select_sound.setVolume(sound_level*5);
        exit_sound.setVolume(sound_level*15);
        invalid_sound.setVolume(sound_level*15);
        sound_change.setVolume(sound_level*15);
    }

};

int main()
{
    // **********Initialization Start*************
    int screen_x=sf::VideoMode::getDesktopMode().width;
    int screen_y=sf::VideoMode::getDesktopMode().height;
    sf::RenderWindow window(sf::VideoMode(window_width,window_length), "JUMPING RABBIT",sf::Style::None);
    window.setFramerateLimit(60);
    if(window_width>screen_x)
    {
        window.setSize(sf::Vector2u (screen_x,screen_y));
        window.setPosition(sf::Vector2i (0,0));
    }

    // ******loading resources****************
    MENU menu;
    if(!(file_exists("save/score.dat")&&file_exists("save/data.dat")))
    {
        std::cout<<"setting default"<<std::endl;
        menu.set_default();
    }
    menu.main_menu(window);

    return 0;
}

Game::Game()
{
    //loading audio and audio buffers

    background_game_sound.openFromFile("audio/background_game_sound.ogg");
    jump_soundbuffer.loadFromFile("audio/jump_sound.ogg");
    level_up_soundbuffer.loadFromFile("audio/level_up.ogg");
    dead_soundbuffer.loadFromFile("audio/dead_sound.ogg");
    back_soundbuffer.loadFromFile("audio/back_sound.ogg");

    jump_sound.setBuffer(jump_soundbuffer);
    level_up_sound.setBuffer(level_up_soundbuffer);
    dead_sound.setBuffer(dead_soundbuffer);
    back_sound.setBuffer(back_soundbuffer);

    background_game_sound.setLoop(true);
    //loading texture and sprites

    bgimage_texture.loadFromFile("pics/background1.png");
    cloud_texture.loadFromFile("pics/cloud1.png");
    sidewindow.load("pics/side window.png",4);
    Collision::CreateTextureAndBitmask(character_texture1,"pics/rabbit1.png");
    Collision::CreateTextureAndBitmask(character_texture2,"pics/rabbit1_jumping.png");
    Collision::CreateTextureAndBitmask(character_texture3,"pics/rabbit1_inair.png");
    Collision::CreateTextureAndBitmask(brick_texture,"pics/brick1.png");
    sCloud.setTexture(cloud_texture);
    scharacter.setTexture(character_texture1);
    sbrick.setTexture(brick_texture);
    bgsource.top=bg_length-900,bgsource.left=0,bgsource.width=700,bgsource.height=bg_length;
    bg.setTexture(bgimage_texture);
    bg.setTextureRect(bgsource);
    sidewindow.pos(700,0);
    life_ani.load("pics/life_shape.png",5);
    life_ani.pos(774,277);
    //loading text
    values.loadFromFile("fonts/RAVIE.ttf");
    score_text.setFont(values);
    sprintf(text,"%d",score);  //not need
    score_text.setString(text);//not need
    score_text.setCharacterSize(45);
    score_text.setOutlineThickness(1);
    score_text.setFillColor(sf::Color::Green);
    score_text.setPosition(1015,480);

    highscore_text.setFont(values);
    sprintf(text,"%d",highscore);   //not need
    highscore_text.setString(text); //not need
    highscore_text.setCharacterSize(45);
    highscore_text.setOutlineThickness(1);
    highscore_text.setFillColor(sf::Color::Green);
    highscore_text.setPosition(1015,330);

    level_text.setFont(values);
    sprintf(text,"%d",level);   //not need
    level_text.setString(text); //not need
    level_text.setCharacterSize(45);
    level_text.setOutlineThickness(1);
    level_text.setFillColor(sf::Color::Green);
    level_text.setPosition(805,455);
    highscore=scorer.get_high();
}
 bool Game::game(sf::RenderWindow &gamewindow,int volume)
{
    //***new game initialization start****
    brick_count=0,x = 250, y = 100,speed=0,fuel=100,level=0,mapnum=0,highscore=scorer.get_high(),level_score=0,jack=0,life=3,score=0;
    sprintf(text,"%d",level);
    level_text.setString(text);
    sprintf(text,"%d",highscore);
    highscore_text.setString(text);
    sprintf(text,"%d",score);
    score_text.setString(text);
    bgsource.top=bg_length-900;
    bg.setTextureRect(bgsource);
    life_ani.set_pic(2);

    character_velocity = 0,brick_velocity=game_speed*2.5,gravitation=game_speed*0.25,jump_accelaration=-12;
    DEAD=false;

    for(int i=0;i<max_brick;i++)        /* brick initialization */
    {
        brick[i].x=-200;
        brick[i].y=sf::VideoMode().getDesktopMode().height+200;
    }
    brick[0].y=800-40;

    for(int i = 0; i < SIZE; i++)       /*cloud initialization*/
    {
        cloud[i].x = std::rand() % 800;
        cloud[i].y = std::rand() % 500;
    }
    //***new game initialization end****

    background_game_sound.setVolume(volume*15);
    jump_sound.setVolume(volume*15);
    level_up_sound.setVolume(volume*15);
    dead_sound.setVolume(volume*15);
    back_sound.setVolume(volume*15);

    background_game_sound.play();

    //*****gameloop start*******
    while(life){
        //******poll event*****
        while(gamewindow.pollEvent(event)){
            if((Keyboard::isKeyPressed(Keyboard::Escape)))
                {
                    print_high(highscore);
                    back_sound.play();
                    background_game_sound.pause();
                    return DEAD;
                }
            if(event.type==Event::MouseButtonPressed)       /* Unit testing: finding coordinates */
            {
                std::cout<< "x pos:"<<event.mouseButton.x<<"y pos:"<<event.mouseButton.y<<std::endl<<std::endl;
            }
            if(Keyboard::isKeyPressed(Keyboard::Space)&&character_velocity==0&&y+character_length>=ground)  // for detecting jump
                {
                    jump_sound.play();
                    character_velocity=jump_accelaration;
                }

        }
        /*if(Keyboard::isKeyPressed(Keyboard::LShift)&&fuel>3)
        {
            character_velocity=-6;
            fuel-=1;
        }
        std::cout<<fuel<<std::endl;
        */
        //******poll event END*****

        sbrick.setPosition(brick[brick_count].x,brick[brick_count].y);
        scharacter.setPosition(x,y);
        //*****handling situation during collision*****
        if(Collision::PixelPerfectTest(scharacter,sbrick))
        {
            if((((brick[brick_count].y) + 15 )> (y + character_length))&&( 350 > brick[brick_count].x)&&( 350 < (brick[brick_count].x + brick_width)))
            {       //*****new brick is added******
                if(character_velocity>=0)       //***only when coming down****
                {
                    brick_count++;
                    brick_create(level);
                    level_score+=(100-std::abs(250-brick[brick_count-1].x))/10;
                    score+=(100-std::abs(250-brick[brick_count-1].x))/10;
                    sprintf(text,"%d",score);
                    score_text.setString(text);     //updating score sprite
                    if(score>highscore){
                        highscore=score;
                        print_high(highscore);
                        sprintf(text,"%d",highscore);
                        highscore_text.setString(text);
                    }
                    //speedcount+=score;
                    if(brick_count%10==0) {
                            level_up_sound.play();
                            level++;
                            mapnum=(level/5);
                            sprintf(text,"%d",level);
                            level_text.setString(text);
                            jack=-80;
                            sidewindow.set_pic(2);
                    }
                    if(level_score>35){
                            speed++;
                            level_score=0;
                            character_velocity = 0,brick_velocity=game_speed*2.5,gravitation=game_speed*0.25,jump_accelaration=-12;
                    }
                    fuel+=5;
                    std::cout<<"score:"<<score<<" level:"<<level<<" speed:"<<speed<<" mapnum:"<<mapnum<<std::endl;
                }
            }
            else{
                //DEAD=true; //******When Dead*****
                //return DEAD;
                dead_sound.play();
                life--;
                life_ani.set_pic(5-life);
                x = 250, y = ground-700;
                character_velocity=0;
                jack=-80;
                sidewindow.set_pic(3);
                if(life==0)
                {
                    background_game_sound.stop();
                }
            }
        }

        // character gravitation
        if((y+character_length)>ground&& character_velocity>=0)//***when above ground and downward accelaration*****
            character_velocity=0;                               // ****the character is stationary******
        else character_velocity += gravitation;             //***continuous gravitational accelaration *****

        y += character_velocity;

        //******brick movement*****
        if(brick[brick_count].x<-200||brick[brick_count].x>700)
            brick_create(level);
        brick[brick_count].x+=(int)brick_velocity;

        //*********check if scrolling is needed**********

        if(ground < top_ground)
        {
            scroll();
        }
        //std::cout<<ground<<std::endl<<y<<std::endl;

        //*****start of drawing*****
        scharacter.setPosition(x, y);

        gamewindow.draw(bg);

        // Draws the cloudforms on the screen
        /*for(int i = 0; i < SIZE; i++){
            sCloud.setPosition(cloud[i].x, cloud[i].y);
            gamewindow.draw(sCloud);
        }
        */      // temporary disabled

        //draws all the bricks
        for(int i=brick_count;i>=0;i--)
        {
            sbrick.setPosition(brick[i].x,brick[i].y);
            gamewindow.draw(sbrick);
            if(brick[i].y>900) break;
        }
        if(character_velocity==0) scharacter.setTexture(character_texture1);
        else if( character_velocity<0) scharacter.setTexture(character_texture2);
        else if(character_velocity>0) scharacter.setTexture(character_texture3);
        gamewindow.draw(scharacter);
        jack++;
        if(jack==120){ jack=0;sidewindow.set_pic(0);}
        else if(jack==60) sidewindow.set_pic((1));
        gamewindow.draw(sidewindow.print());
        gamewindow.draw(life_ani.print());
        gamewindow.draw(score_text);
        gamewindow.draw(highscore_text);
        gamewindow.draw(level_text);
        gamewindow.display();
        gamewindow.clear(sf::Color::Cyan);
        //std::cout<<brick[0].x<<std::endl;
    }
    return 0;
}
MENU::MENU()
    {
        cursor=0;sound_level=get_sound();

        screen_x=sf::VideoMode::getDesktopMode().width;
        screen_y=sf::VideoMode::getDesktopMode().height;
        //window.setMouseCursorVisible(false);

        background_music.openFromFile("audio/background_music.ogg");
        updown_soundbuffer.loadFromFile("audio/updown_sound.ogg");
        select_soundbuffer.loadFromFile("audio/select_sound.ogg");
        exit_soundbuffer.loadFromFile("audio/exit_sound.ogg");
        invalid_soundbuffer.loadFromFile("audio/invalid_sound.ogg");
        sound_change_soundbuffer.loadFromFile("audio/sound_change.ogg");

        updown_sound.setBuffer(updown_soundbuffer);
        select_sound.setBuffer(select_soundbuffer);
        exit_sound.setBuffer(exit_soundbuffer);
        invalid_sound.setBuffer(invalid_soundbuffer);
        sound_change.setBuffer(sound_change_soundbuffer);

        background_music.setLoop(true);
        background_music.setVolume(sound_level*15);
        updown_sound.setVolume(sound_level*15);
        select_sound.setVolume(sound_level*5);
        exit_sound.setVolume(sound_level*15);
        invalid_sound.setVolume(sound_level*15);
        sound_change.setVolume(sound_level*15);


        sound.load("pics/sound.png",6);
        sound_arrow_texture.loadFromFile("pics/sound_arrow.png");
        sound_arrow.setTexture(sound_arrow_texture);

        if(!menubgtexture.loadFromFile("pics/menubg1.png")) std::cout<<"Error loading menubg"<<std::endl;
        menubg.setTexture(menubgtexture);
        if(!gamename.loadFromFile("fonts/FORTE.ttf")) std::cout<<"Error loading gamename"<<std::endl;
        if(!menuitems.loadFromFile("fonts/MAGNETOB.ttf")) std::cout<<"Error loading menuitems"<<std::endl;
        if(!style1.loadFromFile("fonts/SitkaI.ttf")) std::cout<<"Error loading style1"<<std::endl; //error loading####

        gamename_text.setFont(gamename);
        gamename_text.setString("JUMPING RABBIT");
        gamename_text.setCharacterSize(75);
        gamename_text.setOutlineThickness(1);
        gamename_text.setFillColor(sf::Color::Green);
        gamename_text.setPosition(200,2);
        for(int i=0;i<5;i++)
        {
            menu_text[i].setFont(menuitems);
            menu_text[i].setCharacterSize(60);
            menu_text[i].setPosition(60,330+(i*60));
            menu_text[i].setFillColor(notSelectedColor);
            menu_text[i].setOutlineColor(notSelectedColor);

            options_text[i].setFont(menuitems);
            options_text[i].setCharacterSize(60);
            options_text[i].setPosition(60,330+(i*60));
            options_text[i].setFillColor(notSelectedColor);
            options_text[i].setOutlineColor(notSelectedColor);
        }
        menu_text[0].setString("Play");
        menu_text[1].setString("Options");
        menu_text[2].setString("Highscore");
        menu_text[3].setString("Help");
        menu_text[4].setString("Exit");
        menu_text[5].setString("Continue");
        options_text[0].setString("Sound");
        options_text[1].setString("Reset");
        options_text[2].setString("Back");

        menu_text[cursor].setFillColor(sf::Color::Cyan);
        menu_text[cursor].setOutlineThickness(1);
}
int MENU::main_menu(RenderWindow &window)
{
    background_music.play();

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed||Keyboard::isKeyPressed(Keyboard::BackSpace))
                {
                    exit_sound.play();
                    window.close();
                }
            else if(event.type==Event::KeyPressed)
            {
                if(Keyboard::isKeyPressed(Keyboard::Tab)&&!(1200>screen_x))
                {
                    if(window.getSize()!=Vector2u (screen_x,screen_y))
                    {
                        window.setSize(sf::Vector2u (screen_x,screen_y));
                        window.setPosition(sf::Vector2i (0,0));
                    }
                    else{
                        window.setSize(sf::Vector2u (1200,900));
                        window.setPosition(sf::Vector2i ((screen_x/2)-600,(screen_y/2)-450));
                    }
                }
                else if (Keyboard::isKeyPressed(Keyboard::Down))
                {
                    updown_sound.play();
                    menu_text[cursor].setFillColor(Color::Blue);
                    menu_text[cursor].setOutlineThickness(0);
                    cursor=(cursor+1)%5;
                    menu_text[cursor].setFillColor(Color::Cyan);
                    menu_text[cursor].setOutlineThickness(1);
                }
                else if (Keyboard::isKeyPressed(Keyboard::Up))
                {
                    updown_sound.play();
                    menu_text[cursor].setFillColor(Color::Blue);
                    menu_text[cursor].setOutlineThickness(0);
                    cursor=(cursor+4)%5;
                    menu_text[cursor].setFillColor(Color::Cyan);
                    menu_text[cursor].setOutlineThickness(1);
                }
                else if(Keyboard::isKeyPressed(Keyboard::Enter))
                {
                    select_sound.play();
                    for(float i=0;menu_text[cursor].getPosition().x<900;i+=15)
                    {
                        menu_text[cursor].move(i,0);
                        window.clear();
                        window.draw(menubg);
                        window.draw(gamename_text);
                        for(int i=0;i<5;i++) window.draw(menu_text[i]);
                        if(game.DEAD==false) window.draw(menu_text[5]);
                        window.display();
                    }
                    menu_text[cursor].setPosition(60,330+cursor*60);
                    if(cursor==0){
                            background_music.stop();
                            game.game(window,sound_level);
                            background_music.play();
                    }
                    else if(cursor==1) option_menu(window);
                    else if(cursor==2) highscore_menu(window);
                    else if(cursor==3) help_menu(window);
                    else if(cursor==4) {
                            exit_sound.play();
                            window.close();
                    }
                }
                else
                {
                    invalid_sound.play();
                }
            }
        }

        // *****Render window*********
        window.clear();
        window.draw(menubg);
        window.draw(gamename_text);
        for(int i=0;i<5;i++) window.draw(menu_text[i]);
        if(game.DEAD==false) window.draw(menu_text[5]);
        window.display();
                    }
        return 0;
}
int MENU::option_menu(RenderWindow &window)
{
    int cur=0;
    options_text[0].setFillColor(Color::Cyan);
    options_text[0].setOutlineThickness(1);
    options_text[0].setPosition(window_width,330);
    sound.set_pic(sound_level);
    sound.pos(60,348);
    sound_arrow.setPosition(15,348);

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed||Keyboard::isKeyPressed(Keyboard::BackSpace))
                {
                    exit_sound.play();
                    window.close();
                }
            else if(event.type==Event::KeyPressed)
            {
                if(Keyboard::isKeyPressed(Keyboard::Tab)&&!(1200>screen_x))
                {
                    if(window.getSize()!=Vector2u (screen_x,screen_y))
                    {
                        window.setSize(sf::Vector2u (screen_x,screen_y));
                        window.setPosition(sf::Vector2i (0,0));
                    }
                    else{
                        window.setSize(sf::Vector2u (1200,900));
                        window.setPosition(sf::Vector2i ((screen_x/2)-600,(screen_y/2)-450));
                    }
                }
                else if (Keyboard::isKeyPressed(Keyboard::Down))
                {
                    updown_sound.play();
                    options_text[cur].setFillColor(Color::Blue);
                    options_text[cur].setOutlineThickness(0);
                    cur=(cur+1)%3;
                    options_text[cur].setFillColor(Color::Cyan);
                    options_text[cur].setOutlineThickness(1);
                    if(cur==0){
                            sound_arrow.setPosition(15,348);
                            sound.pos(60,348);
                            options_text[0].setPosition(window_width,330);
                    }
                    else {
                            sound_arrow.setPosition(window_width,348);
                            sound.pos(window_width,348);
                            options_text[0].setPosition(60,330);
                    }
                }
                else if (Keyboard::isKeyPressed(Keyboard::Up))
                {
                    updown_sound.play();
                    options_text[cur].setFillColor(Color::Blue);
                    options_text[cur].setOutlineThickness(0);
                    cur=(cur+2)%3;
                    options_text[cur].setFillColor(Color::Cyan);
                    options_text[cur].setOutlineThickness(1);
                    if(cur==0){
                            sound_arrow.setPosition(15,348);
                            sound.pos(60,348);
                            options_text[0].setPosition(window_width,330);
                    }
                    else {
                            sound_arrow.setPosition(window_width,348);
                            sound.pos(window_width,348);
                            options_text[0].setPosition(60,330);
                    }
                }
                else if(Keyboard::isKeyPressed(Keyboard::Enter))
                {
                    if(cur==0)      continue;
                    select_sound.play();
                    for(float i=0;options_text[cur].getPosition().x<900;i+=15)
                    {
                        options_text[cur].move(i,0);
                        window.clear();
                        window.draw(menubg);
                        window.draw(gamename_text);
                        for(int i=0;i<3;i++) window.draw(options_text[i]);
                        window.display();
                    }
                    options_text[cur].setPosition(60,330+cur*60);
                    options_text[cur].setFillColor(Color::Cyan);
                    options_text[cur].setOutlineThickness(1);

                    if(cur==1) set_default();
                    else if(cur==2){
                            options_text[cur].setFillColor(Color::Blue);
                            options_text[cur].setOutlineThickness(0);
                            return 0;
                    }
                }
                else if(Keyboard::isKeyPressed(Keyboard::Left)&&cur==0)
                {
                    sound_level=(sound_level+5)%6;
                    sound.set_pic(sound_level);
                    background_music.setVolume(sound_level*15);
                    updown_sound.setVolume(sound_level*15);
                    select_sound.setVolume(sound_level*5);
                    exit_sound.setVolume(sound_level*15);
                    invalid_sound.setVolume(sound_level*15);
                    sound_change.setVolume(sound_level*15);
                    sound_change.play();
                    print_sound(sound_level);
                }
                else if(Keyboard::isKeyPressed(Keyboard::Right)&&cur==0)
                {
                    sound_level=(sound_level+1)%6;
                    sound.set_pic(sound_level);
                    background_music.setVolume(sound_level*15);
                    updown_sound.setVolume(sound_level*15);
                    select_sound.setVolume(sound_level*5);
                    exit_sound.setVolume(sound_level*15);
                    invalid_sound.setVolume(sound_level*15);
                    sound_change.setVolume(sound_level*15);
                    sound_change.play();
                    print_sound(sound_level);
                }
            }
        }

        // *****Render window*********
        window.clear();
        window.draw(menubg);
        window.draw(gamename_text);
        for(int i=0;i<3;i++) window.draw(options_text[i]);
        window.draw(sound_arrow);
        window.draw(sound.print());
        window.display();
                    }
        return 0;
}
void gen_cloud(){
    for(int i = 0; i < SIZE; i++){
        //cloud[i].x = std::rand() % 800;
        //cloud[i].y = std::rand() % 500;
    }
}

void Game::scroll()
{

    y+=3;
    bgsource.top-=3;
    bg.setTextureRect(bgsource);
    for(int i=0;i<=brick_count;i++)
    {
        brick[i].y+=3;
    }
    //std::cout<<brick[brick_count].y<<std::endl;

}

void MENU::highscore_menu(RenderWindow &window)
{
    int i=0;
    menubgtexture.loadFromFile("pics/help.png");
    menubg.setTexture(menubgtexture);


    Text help_text;
    help_text.setFont(menuitems);
    help_text.setPosition(200,400);
    char str[100];

    int high=0;
    std::sprintf(str,"The current highscore is :%d",high);
    help_text.setString(str);
    while(true){
        while(window.pollEvent(event))
        {
            if(event.type==event.KeyPressed)
            {
                if(Keyboard::isKeyPressed(Keyboard::Escape)||i==1)
                {
                    menubgtexture.loadFromFile("pics/menubg1.png");
                    menubg.setTexture(menubgtexture);
                    return ;
                }
                if(Keyboard::isKeyPressed(Keyboard::Enter))
                {
                    if(i==0) help_text.setString("Good Luck on getting the next highscore");
                    i++;
                }
            }
        }
        window.clear();
        window.draw(menubg);
        window.draw(help_text);
        window.display();
    }
}
void MENU::help_menu(RenderWindow &window)
{
    int i=0;
    Texture help_texture;
    help_texture.loadFromFile("pics/help.png");
    Sprite help_sprite;
    help_sprite.setTexture(help_texture);
    help_sprite.setPosition(0,0);


    Text help_text;
    Font font;
    font.loadFromFile("fonts/FORTE.ttf");
    help_text.setFont(font);
    help_text.setPosition(200,400);
    help_text.setString("Press UP and DOWN keys to navigate the menu\nUse ENTER to select the menu items to your choice");
    Event e;
    while(true){
        while(window.pollEvent(e))
        {
            if(e.type==e.KeyPressed)
            {
                if(Keyboard::isKeyPressed(Keyboard::Escape))
                {
                    return ;
                }
                if(Keyboard::isKeyPressed(Keyboard::Enter))
                {
                    if(i==0) help_text.setString("Press SPACE to jump in game\n Try to land on the center-top the brick to score higher score");
                    else if(i==1) help_text.setString("Be careful not to get knocked by the bricks");
                    else if(i==2) help_text.setString("Happy Gaming");
                    else if(i==3) return;
                    i++;
                }
            }
        }
        window.clear();
        window.draw(help_sprite);
        window.draw(help_text);
        window.display();
    }

}
