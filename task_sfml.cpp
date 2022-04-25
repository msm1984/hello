#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <string>
using namespace sf;
using namespace std;
void my_Rotate(RectangleShape &s, int k){
    //Vector2f ori = s.getPosition();
    //s.move(100,0);
    //if(ori.y == 0 && ori.x != 600){
        //s.move(100,0);
        //s.setOrigin(100,0);
    //}
    s.rotate(-k);
        //clock.restart();
    /*if(ori.x == 600 && ori.y != 100){
        s.setPosition()
    }*/

}
void orig(RectangleShape &s){
    Vector2f pos = s.getOrigin();
    Vector2f pis = s.getPosition();
    //s.setPosition(0,0);
    if(pis.x != 500 && pis.x != 600 && pis.y == 0){
    s.move(100,0);
    if(pos.x == 100 && pos.y == 0)
        s.setOrigin(100,100);
    if(pos.x == 100 && pos.y == 100)
        s.setOrigin(0,100);
    if(pos.x == 0 && pos.y == 100)
        s.setOrigin(0,0);
    if(pos.x == 0 && pos.y == 0)
        s.setOrigin(100,0);
    }
    if(pis.x == 500 && pis.y == 0){
        s.move(100,100);
        s.setOrigin(0,100);
    }
    if(pis.x == 600 && pis.y != 500){
    s.move(0,100);
    if(pos.x == 100 && pos.y == 0)
        s.setOrigin(100,100);
    if(pos.x == 100 && pos.y == 100)
        s.setOrigin(0,100);
    if(pos.x == 0 && pos.y == 100)
        s.setOrigin(0,0);
    if(pos.x == 0 && pos.y == 0)
        s.setOrigin(100,0);
    }
    if(pis.y == 500 && pis.x == 600){
        s.move(-100,100);
        s.setOrigin(100,0);
    }
    if(pis.x != 100 && pis.y == 600){
    s.move(-100,0);
    if(pos.x == 100 && pos.y == 0)
        s.setOrigin(100,100);
    if(pos.x == 100 && pos.y == 100)
        s.setOrigin(0,100);
    if(pos.x == 0 && pos.y == 100)
        s.setOrigin(0,0);
    if(pos.x == 0 && pos.y == 0)
        s.setOrigin(100,0);
    }
    if(pis.x == 100 && pis.y == 600){
        s.move(-100,-100);
        s.setOrigin(0,100);
    }
    if(pis.x == 0 && pis.y != 100){
    s.move(0,-100);
    if(pos.x == 100 && pos.y == 0)
        s.setOrigin(100,100);
    if(pos.x == 100 && pos.y == 100)
        s.setOrigin(0,100);
    if(pos.x == 0 && pos.y == 100)
        s.setOrigin(0,0);
    if(pos.x == 0 && pos.y == 0)
        s.setOrigin(100,0);
    }
    if(pis.x == 0 && pis.y == 100){
        s.move(100,-100);
        s.setOrigin(100,0);
    }

}

int main()
{
    RenderWindow window(VideoMode(600, 600), "SFML works!");
    RectangleShape shape(Vector2f(100,100));
    Texture texture;
    texture.loadFromFile("wood.jpg");
    shape.setTexture(&texture); // texture is a sf::Texture
    shape.setTextureRect(sf::IntRect(10, 10, 100, 100));
    Font font;
    font.loadFromFile("arial.ttf");
    Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(Color::Red);
    shape.move(100,0);
    shape.setOrigin(100,0);
    //sf::Vector2f origin = shape.getOrigin();
    //shape.setRotation(-90);
    //shape.rotate(5.f);
    Clock clock;
    Time elapse;
    int k = 30;
    string r;
    //text.setString(r);
    text.setPosition(300,300);
    //int i = 0;
    srand(time(0));
    int a = rand()%255;
    int b = rand()%255;
    int c = rand()%255;
    //a = rand()%200;
    //shape.rotate(-10);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if((Keyboard::isKeyPressed(Keyboard::A)) && k < 50){
            k += 10;
        }
        if((Keyboard::isKeyPressed(Keyboard::D)) && k > 0){
            k -= 10;
        }
        r = to_string(k);
        text.setString(r);

        //window.clear(Color(200,0,0));
        //window.draw(shape);
        //window.display();
        int j = 0;
        //a = rand()%200;
        //b = rand()%200;
        //int i = 0;
        while(j<45){
        elapse = clock.getElapsedTime();
        if(elapse.asMilliseconds() > k){
        window.clear(Color(c,b,a));
        my_Rotate(shape,2);
        window.draw(shape);
        window.draw(text);
        window.display();
        //clock.restart();
        j++;
        if(a != 255 && b != 255 && c != 255 && a != 0){
            a++;
        }
        if(b != 255 && a == 255 && c != 255){
            b++;
        }
        if(b == 255 && a == 255 && c != 255){
            c++;
        }
        if(b == 255 && a != 0 && c == 255){
            a--;
        }
        if(b != 0 && a == 0 && c == 255){
            b--;
        }
        if(b == 0 && a == 0 && c != 0){
            c--;
        }
        if(a == 0 && b == 0 & c == 0){
            a++;
        }
        clock.restart();
        }
        }
        orig(shape);
    }

    return 0;
}
