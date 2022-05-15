#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <string>
#include <iostream>
using namespace sf;
using namespace std;
class Item {
private:
    RectangleShape shape;
    Texture texture;
public:
    Item(int x, int y) {
        shape.setSize(Vector2f(100, 100));
        //texture.loadFromFile("orange.jpg");
        //shape.setTexture(&texture);
        shape.setPosition(x, y);
        //Texture texture;
        if (!texture.loadFromFile("orange.png")) {
            cout << "hello" << endl;
        }
        shape.setTexture(&texture);
        //shape.setTextureRect(IntRect(10, 10, 270, 150));
        //shape.setPosition(x,y);
    }
    void movv(int x, int y) {
        shape.move(x, y);
    }
    RectangleShape getShape() {
        return shape;
    }

};
bool outOfScreen(Item& item) {
    return item.getShape().getPosition().y == 650;
}
int score = 0;
RectangleShape basket(Vector2f(100, 100));
/*basket.setPosition(250,500);
Texture texture;
texture.loadFromFile("hello.jpg");
basket.setTexture(&texture);
basket.setTextureRect(IntRect(10, 10, 270, 150));*/
bool collide(Item& item) {
    if (item.getShape().getPosition().x == basket.getPosition().x &&
        item.getShape().getPosition().y == basket.getPosition().y) {
        score++;
        return true;
    }
    return false;
}


int main()
{
    RenderWindow window(VideoMode(600, 600), "SFML works!");
    //RectangleShape basket(Vector2f(100,100));
    basket.setPosition(250, 500);
    Texture texture;
    texture.loadFromFile("basket.png");
    basket.setTexture(&texture);
    //basket.setTextureRect(IntRect(10, 10, 270, 150));
    Vector2f pos;
    Font font;
    font.loadFromFile("arial.ttf");
    Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(Color::Red);
    string r;
    //Clock clock;
    Clock clock;
    srand(time(0));
    Time time_1;
    Time time_2;
    vector<Item> items;
    while (window.isOpen())
    {

        //Clock clock;
        //Time time_1;
        //Time time_2;
        sf::Event event;
        while (window.pollEvent(event))
        {
            pos = basket.getPosition();
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyReleased) {
                if (event.key.code == Keyboard::A && pos.x > 0)
                    basket.move(-50, 0);
                if (event.key.code == Keyboard::D && pos.x < 500)
                    basket.move(50, 0);
            }



        }
        time_2 = clock.getElapsedTime();
        if (time_2.asMilliseconds() > 1000) {
            clock.restart();
            for (auto item = items.begin(); item != items.end(); item++) {
                item->movv(0, 100);
            }
            items.erase(remove_if(items.begin(), items.end(), outOfScreen), items.end());
            items.erase(remove_if(items.begin(), items.end(), collide), items.end());
            items.push_back(Item((rand() % 5) * 100, 0));
        }
        Vector2f pos;
        r = to_string(score);
        text.setString(r);
        window.clear();
        window.draw(basket);
        for (Item item : items) {
            window.draw(item.getShape());
        }
        window.draw(text);
        window.display();
    }

    return 0;

}