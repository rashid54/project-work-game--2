#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<bits/stdc++.h>
using namespace sf;
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
