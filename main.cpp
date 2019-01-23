//**the include files**
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<bits/stdc++.h>
#include <sys/stat.h>
#include "Collision.hpp"
#include "Collision.cpp"
//**the sizes declarations ****
#define window_width 1200
#define window_length 900
#define bg_width 700
#define bg_length 2500
#define character_width 200
#define character_length 300
#define brick_width 200
#define brick_length 50
//*** the default values declarations****
#define notSelectedColor sf::Color::Blue
#define SIZE 10
#define top_ground 540
#define max_brick 200
#define game_speed (1+(0.1*speed))
#define brick_speed (1+(0.17*speed))
#define ground brick[brick_count].y+55
using namespace sf;
//***********structures***********
struct coordinate{int x,y;};
//***********functions*************
inline bool file_exists (const std::string& name) {
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}

class CLOUD
{
    int z;
    coordinate pos[10];
    int velocity[10];
    Texture cloud_texture;
public:
    Sprite scloud[10];
    void load()
    {
        std::srand(time(NULL));
        int v=rand()%3;
        z=-(rand()%2);
        cloud_texture.loadFromFile("pics/cloud1.png");
        for(int cx,cy,c,i=0;i<10;i++)
        {
            c=rand();
            cy=(c%700)-400;
            cx=(c%800)-100;
            scloud[i].setTexture(cloud_texture);
            velocity[i]=(z*v)+1;
            pos[i].x=cx;
            pos[i].y=cy;
            scloud[i].setPosition(cx,cy);
        }
    }
    void cloud_move()
    {
        int v=rand()%3;
        for(int c,cx,cy,i=0;i<10;i++)
        {
            pos[i].x+=velocity[i];
            scloud[i].move(velocity[i],0);

            if((pos[i].x<-200||pos[i].x>900))
            {
                c=rand();
                cy=(c%400)-500;
                cx=(c%800)-100;
                velocity[i]=(z*v)+1;
                pos[i].x=cx;
                pos[i].y=cy;
                scloud[i].setPosition(cx,cy);
            }
        }
    }
    void cloud_scroll()
    {
        int v=rand()%3;
        for(int c,cx,cy,i=0;i<10;i++)
        {
            pos[i].y+=3;
            scloud[i].move(0,3);

            if(pos[i].y>1000||pos[i].y<-400)
            {
                c=rand();
                cy=(c%400)-500;
                cx=(c%800)-100;
                velocity[i]=(z*v)+1;
                pos[i].x=cx;
                pos[i].y=cy;
                scloud[i].setPosition(cx,cy);
            }
        }
    }
    void cloud_create()
    {
        int v=rand()%3;
        for(int c,cx,cy,i=0;i<10;i++)
        {
            if((pos[i].x<-200||pos[i].x>900)||pos[i].y>1000)
            {
                c=rand();
                cy=(c%700)-400;
                cx=(c%800)-100;
                velocity[i]=(z*v)+1;
                pos[i].x=cx;
                pos[i].y=cy;
                scloud[i].setPosition(cx,cy);
            }
        }
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
    CLOUD cloud;
    int brick_count,x , y ,speed,score,fuel,level,mapnum,highscore,level_score,jack,life;
    int jump;
    char text[10];
    Font values;
    Text score_text,highscore_text,level_text;
    float character_velocity ,brick_velocity,gravitation,jump_accelaration;
    coordinate brick[max_brick];
    IntRect bgsource;
    Texture bgimage_texture,character_texture1,character_texture2,character_texture3,brick_texture;
    Sprite scharacter,sbrick,bg,sbrick_top;
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
            brick[brick_count].x=(900*(brick_count%2))-brick_width;
        }
        else   // level 3 brick creation
        {
            srand(time(NULL));
            brick[brick_count].x=(910*(rand()%2))-brick_width-jack/12;
        }
        if(brick[brick_count].x*brick_velocity>0)       // fixing brick_velocity direction
        {
            brick_velocity*=-1;
        }
        brick[brick_count].y=brick[brick_count-1].y - brick_length;   // new brick height
        sbrick_top.setPosition(brick[brick_count].x,brick[brick_count].y);
    }
    int map_changer(RenderWindow &gamewindow,char* arg)
    {
        Text map_change;
        map_change.setFont(values);
        map_change.setCharacterSize(50);
        map_change.setString("NEW MAP UNLOCKED");
        map_change.setPosition(-500,400);
        for(int i=-65;i<65;i++)
        {
            scharacter.move(0,-5);
            map_change.move(10,0);
            gamewindow.draw(bg);
            for(int i=brick_count-1;i>=0;i--)
            {
                sbrick.setPosition(brick[i].x,brick[i].y);
                gamewindow.draw(sbrick);
                if(brick[i].y>900) break;
            }
            gamewindow.draw(map_change);
            gamewindow.draw(sbrick_top);
                gamewindow.draw(scharacter);
                gamewindow.draw(sidewindow.print());
                gamewindow.draw(life_ani.print());
                gamewindow.draw(score_text);
                gamewindow.draw(highscore_text);
                gamewindow.draw(level_text);
                gamewindow.display();
                gamewindow.clear(sf::Color::Cyan);
            }
            speed-=1;
            bgimage_texture.loadFromFile(arg);
            bg.setTexture(bgimage_texture);
            y=100;
            scharacter.setPosition(x,y);
            brick_count=0;
            brick_create(level);
            for(int i=0;i<max_brick;i++)        /* brick initialization */
            {
                brick[i].x=-200;
                brick[i].y=sf::VideoMode().getDesktopMode().height+200;
            }
            brick[0].y=800-40;
            bgsource.top=1600;
            bg.setTextureRect(bgsource);
            character_velocity = 0,brick_velocity=(game_speed)*2.5,gravitation=game_speed*0.25,jump_accelaration=-12;
            sbrick_top.setPosition(brick[0].x,brick[0].y);
            cloud.load();
    }
    void scroll();
public:
    Game();
    bool DEAD;
    int game(sf::RenderWindow &gamewindow,int volume=3,int high=0);
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
    sf::Font gamename,menuitems;
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


    int high,cursor,screen_x,screen_y,sound_level;
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
    if(window_width>(screen_x))
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


    sidewindow.load("pics/side window.png",4);
    Collision::CreateTextureAndBitmask(character_texture1,"pics/rabbit1.png");
    Collision::CreateTextureAndBitmask(character_texture2,"pics/rabbit1_jumping.png");
    Collision::CreateTextureAndBitmask(character_texture3,"pics/rabbit1_inair.png");
    Collision::CreateTextureAndBitmask(brick_texture,"pics/brick1.png");
    scharacter.setTexture(character_texture1);
    sbrick.setTexture(brick_texture);
    sbrick_top.setTexture(brick_texture);
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
    highscore=gethigh();
}
 int Game::game(sf::RenderWindow &gamewindow,int volume,int high)
{
    //***new game initialization start****
    if(DEAD==true)
    {
        cloud.load();
        bgimage_texture.loadFromFile("pics/background1.png");
        bgsource.top=bg_length-900,bgsource.left=0,bgsource.width=700,bgsource.height=bg_length;
        bg.setTexture(bgimage_texture);
        bg.setTextureRect(bgsource);

        brick_count=0,x = 250, y = 100,speed=4,fuel=100,level=1,mapnum=0,highscore=high,level_score=0,jack=0,life=3,score=0;
        sprintf(text,"%d",level);
        level_text.setString(text);
        sprintf(text,"%d",highscore);
        highscore_text.setString(text);
        sprintf(text,"%d",score);
        score_text.setString(text);
        bgsource.top=bg_length-900;
        bg.setTextureRect(bgsource);
        life_ani.set_pic(2);

        character_velocity = 0,brick_velocity=brick_speed*2.5,gravitation=game_speed*0.25,jump_accelaration=-12;
        DEAD=false;

        for(int i=0;i<max_brick;i++)        /* brick initialization */
        {
            brick[i].x=-200;
            brick[i].y=sf::VideoMode().getDesktopMode().height+200;
        }
        brick[0].y=800-40;
        sbrick_top.setPosition(brick[0].x,brick[0].y);
        background_game_sound.stop();
        jump=0;
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
            if(event.type==Event::MouseButtonPressed)       /* Unit testing: finding coordinates */
            {
                std::cout<< "x pos:"<<event.mouseButton.x<<"y pos:"<<event.mouseButton.y<<std::endl<<std::endl;
            }
            if(event.type==event.KeyPressed)
            {
                if((Keyboard::isKeyPressed(Keyboard::Escape)))
                {
                        print_high(highscore);
                        back_sound.play();
                        background_game_sound.pause();
                        return highscore;
                    }

                else if(Keyboard::isKeyPressed(Keyboard::Space)&&((character_velocity==0&&y+character_length>=ground)||jump==1))  // for detecting jump
                    {
                        jump--;
                        jump_sound.play();
                        character_velocity=jump_accelaration;
                    }
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
        if(Collision::PixelPerfectTest(scharacter,sbrick_top))
        {
            if(level>1) jump=2;
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
                            sprintf(text,"%d",level);
                            level_text.setString(text);
                            jack=-80;
                            sidewindow.set_pic(2);
                            if(level==5)
                            {
                                score+=(life*50);
                                life++;
                                life_ani.set_pic(5-life);
                                map_changer(gamewindow,"pics/background2.png");
                            }
                            else if(level==10)
                            {
                                score+=(life*50);
                                life++;
                                life_ani.set_pic(5-life);
                                map_changer(gamewindow,"pics/background3.png");
                            }
                            else if(level==15)
                            {
                                score+=(life*50);
                                Text winner;
                                winner.setFont(values);
                                winner.setPosition(-400,400);
                                winner.setCharacterSize(60);
                                winner.setString("   Congratulations!!!\nEntering Free Mode");
                                for(int i=0;i<400;i++)
                                {
                                    winner.move(3,0);
                                    gamewindow.draw(bg);

                                    for(int i=0;i<10;i++)
                                    {
                                        gamewindow.draw(cloud.scloud[i]);
                                    }

                                    //draws all the bricks
                                    for(int i=brick_count-1;i>=0;i--)
                                    {
                                        sbrick.setPosition(brick[i].x,brick[i].y);
                                        gamewindow.draw(sbrick);
                                        if(brick[i].y>900) break;
                                    }
                                    gamewindow.draw(sbrick_top);
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
                                    gamewindow.draw(winner);
                                    gamewindow.display();
                                    gamewindow.clear(sf::Color::Cyan);

                                }
                            }
                    }
                    if(level_score>35){
                            speed++;
                            level_score=0;
                            character_velocity = 0,brick_velocity=brick_speed*2.5,gravitation=game_speed*0.25,jump_accelaration=-12;
                    }
                    std::cout<<"score:"<<score<<" level:"<<level<<" speed:"<<speed<<" mapnum:"<<mapnum<<std::endl;
                }
            }
            else{
                //when dead
                dead_sound.play();
                life--;
                life_ani.set_pic(5-life);
                x = 250, y = ground-700;
                character_velocity=0;
                jack=-80;
                sidewindow.set_pic(3);
                if(life==0)
                {
                    DEAD=true;
                    background_game_sound.stop();
                    Text map_change;
                    map_change.setFont(values);
                    map_change.setCharacterSize(50);
                    map_change.setString("YOU'RE DEAD!!");
                    map_change.setPosition(-500,400);
                    for(int i=-65;i<65;i++)
                    {
                        if(i==-30||i==30) dead_sound.play();
                        scharacter.move(-2,-5);
                        map_change.move(10,0);
                        gamewindow.draw(bg);
                        for(int i=brick_count-1;i>=0;i--)
                        {
                            sbrick.setPosition(brick[i].x,brick[i].y);
                            gamewindow.draw(sbrick);
                            if(brick[i].y>900) break;
                        }
                        gamewindow.draw(map_change);
                        gamewindow.draw(sbrick_top);
                            gamewindow.draw(scharacter);
                            gamewindow.draw(sidewindow.print());
                            gamewindow.draw(life_ani.print());
                            gamewindow.draw(score_text);
                            gamewindow.draw(highscore_text);
                            gamewindow.draw(level_text);
                            gamewindow.display();
                            gamewindow.clear(sf::Color::Cyan);
                        }
                    return highscore;
                }
            }

        }

        // character gravitation
        if((y+character_length)>ground&& character_velocity>=0)//***when above ground and downward accelaration*****
            {
                character_velocity=0;                               // ****the character is stationary******
                if(level>1) jump=2;
            }
        else if(character_velocity>12) character_velocity=12;
        else character_velocity += gravitation;             //***continuous gravitational accelaration *****

        scharacter.move(0,character_velocity);
        y += character_velocity;

        //******brick movement*****
        if(brick[brick_count].x<-200||brick[brick_count].x>700)
            brick_create(level);
        sbrick_top.move((int)brick_velocity,0);
        brick[brick_count].x+=(int)brick_velocity;

        //*********check if scrolling is needed**********

        if(ground < top_ground)
        {
            scroll();
            cloud.cloud_scroll();
        }
        cloud.cloud_move();
        //std::cout<<ground<<std::endl<<y<<std::endl;

        //*****start of drawing*****

        gamewindow.draw(bg);

        for(int i=0;i<10;i++)
        {
            gamewindow.draw(cloud.scloud[i]);
        }

        //draws all the bricks
        for(int i=brick_count-1;i>=0;i--)
        {
            sbrick.setPosition(brick[i].x,brick[i].y);
            gamewindow.draw(sbrick);
            if(brick[i].y>900) break;
        }
        gamewindow.draw(sbrick_top);
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
        cursor=0;sound_level=get_sound();high=gethigh();

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
        menu_text[5].setFont(menuitems);
        menu_text[5].setCharacterSize(60);
        menu_text[5].setPosition(60,270);
        menu_text[5].setFillColor(notSelectedColor);
        menu_text[5].setOutlineColor(notSelectedColor);

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
    int menu_num=5;
    game.DEAD=true;
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
                if(Keyboard::isKeyPressed(Keyboard::Tab)&&!(window_width>screen_x-100))
                {
                    if(window.getSize()!=Vector2u (screen_x,screen_y))
                    {
                        window.setSize(sf::Vector2u (screen_x,screen_y));
                        window.setPosition(sf::Vector2i (0,0));
                    }
                    else{
                        window.setSize(sf::Vector2u (window_width,window_length));
                        window.setPosition(sf::Vector2i ((screen_x/2)-600,(screen_y/2)-450));
                    }
                }
                else if (Keyboard::isKeyPressed(Keyboard::Down))
                {
                    updown_sound.play();
                    menu_text[cursor].setFillColor(Color::Blue);
                    menu_text[cursor].setOutlineThickness(0);
                    cursor=(cursor+1)%menu_num;
                    menu_text[cursor].setFillColor(Color::Cyan);
                    menu_text[cursor].setOutlineThickness(1);
                }
                else if (Keyboard::isKeyPressed(Keyboard::Up))
                {
                    updown_sound.play();
                    menu_text[cursor].setFillColor(Color::Blue);
                    menu_text[cursor].setOutlineThickness(0);
                    cursor=(cursor+(menu_num-1))%menu_num;
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
                            game.DEAD=true;
                            background_music.stop();
                            high=game.game(window,sound_level,high);
                            if(game.DEAD==false) menu_num=6;
                            else menu_num=5;
                            background_music.play();
                    }
                    else if(cursor==1) option_menu(window);
                    else if(cursor==2) highscore_menu(window);
                    else if(cursor==3) help_menu(window);
                    else if(cursor==4) {
                            exit_sound.play();
                            window.close();
                    }
                    else if(cursor==5) {
                        background_music.stop();
                        high=game.game(window,sound_level,high);
                        if(game.DEAD==false) menu_num=6;
                        else menu_num=5;
                        background_music.play();
                        menu_text[5].setPosition(60,270);
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


void Game::scroll()
{

    y+=3;
    bgsource.top-=3;
    bg.setTextureRect(bgsource);
    for(int i=0;i<=brick_count;i++)
    {
        brick[i].y+=3;
    }
    sbrick_top.move(0,3);
    //std::cout<<brick[brick_count].y<<std::endl;

}

void MENU::highscore_menu(RenderWindow &window)
{
    int i=0;
    menubgtexture.loadFromFile("pics/help.png");
    menubg.setTexture(menubgtexture);


    Text help_text;
    help_text.setFont(menuitems);
    help_text.setPosition(-200,400);
    help_text.setCharacterSize(40);
    char str[100];
    std::sprintf(str,"The current highscore is :%d",high);
    help_text.setString(str);
    while(true){
        while(window.pollEvent(event))
        {
            if(event.type==event.KeyPressed)
            {
                if(Keyboard::isKeyPressed(Keyboard::Escape))
                {
                    menubgtexture.loadFromFile("pics/menubg1.png");
                    menubg.setTexture(menubgtexture);
                    return ;
                }
                if(Keyboard::isKeyPressed(Keyboard::Enter))
                {
                    if(help_text.getPosition().x<200)
                    {
                        help_text.setPosition(200,400);
                    }
                    else{
                        if(i==0) help_text.setString("           Good Luck \non getting the next highscore");
                        else if(i==1){
                            menubgtexture.loadFromFile("pics/menubg1.png");
                            menubg.setTexture(menubgtexture);
                            return ;
                        }
                        i++;
                        help_text.setPosition(-200,400);
                    }
                }
            }
        }

        if(help_text.getPosition().x<200)
        {
            help_text.move(10,0);
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
    menubgtexture.loadFromFile("pics/help.png");
    menubg.setTexture(menubgtexture);

    Text help_text;
    Font font;
    font.loadFromFile("fonts/FORTE.ttf");
    help_text.setFont(font);
    help_text.setPosition(-200,400);
    help_text.setCharacterSize(40);
    help_text.setString("Press UP and DOWN keys to navigate the menu\nUse ENTER to select the menu items to your choice");
    Event e;
    while(true){
        while(window.pollEvent(e))
        {
            if(e.type==e.KeyPressed)
            {
                if(Keyboard::isKeyPressed(Keyboard::Escape))
                {
                    menubgtexture.loadFromFile("pics/menubg1.png");
                    menubg.setTexture(menubgtexture);
                    return ;
                }
                if(Keyboard::isKeyPressed(Keyboard::Enter))
                {
                    if(help_text.getPosition().x<200)
                    {
                        help_text.setPosition(200,400);
                    }
                    else{
                        if(i==0) help_text.setString("          Press SPACE to jump in game\n Try to land on the center-top of the brick\n                to score higher score");
                        else if(i==1) help_text.setString("Be careful not to get knocked by the bricks");
                        else if(i==2) help_text.setString(" You can perform only one airjump \n  while in the air from level 2");
                        else if(i==3) help_text.setString("                 Happy Gaming");
                        else if(i==4) {
                            menubgtexture.loadFromFile("pics/menubg1.png");
                            menubg.setTexture(menubgtexture);
                            return;
                        }
                        i++;
                        help_text.setPosition(-200,400);
                    }
                }
            }
        }
        if(help_text.getPosition().x<200)
        {
            help_text.move(10,0);
        }
        window.clear();
        window.draw(menubg);
        window.draw(help_text);
        window.display();
    }

}
