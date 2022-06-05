#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <string>
using namespace sf;
using namespace std;
Texture texture1;
//texture1.loadFromFile("orange.jpg");
class Item : public Drawable {
private:
    RectangleShape shape;
    virtual void draw(RenderTarget& target, RenderStates states) const {
        target.draw(shape, states);
    }
public:
    Item(int x, int y) {
        shape.setSize(Vector2f(100, 100));
        shape.setPosition(x, y);
        //Texture texture;
        //texture.loadFromFile("orange.jpg");
        shape.setTexture(&texture1);
        //shape.setTextureRect(IntRect(10, 10, 270, 150));
        //shape.setPosition(x,y);
    }
    void movv(float x, float y) {
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
    if (basket.getGlobalBounds().intersects(item.getShape().getGlobalBounds()))
    {
        score++;
        return true;
    }
    return false;
}


int main()
{
    RenderWindow window(VideoMode(600, 600), "SFML works!");
    //RectangleShape basket(Vector2f(100,100));
    texture1.loadFromFile("orange.png");
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
    srand(time(0));
    vector<Item> items;
    Clock clock;
    Time deltatime;
    int k = 0;
    while (window.isOpen())
    {
        deltatime = clock.getElapsedTime();
        clock.restart();
        //Time time_2;
        sf::Event event;
        while (window.pollEvent(event))
        {
            pos = basket.getPosition();
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::A && pos.x > 0)
                    basket.move(-4000 * deltatime.asSeconds(), 0);
                if (event.key.code == Keyboard::D && pos.x < 500)
                    basket.move(4000 * deltatime.asSeconds(), 0);
            }



        }
        k += deltatime.asMilliseconds();
        for (auto item = items.begin(); item != items.end(); item++) {
            item->movv(0, 250 * deltatime.asSeconds());
        }
        items.erase(remove_if(items.begin(), items.end(), outOfScreen), items.end());
        items.erase(remove_if(items.begin(), items.end(), collide), items.end());
        if (k > 400) {
            items.push_back(Item((rand() % 5) * 100, 0));
            k = 0;
        }
        Vector2f pos;
        r = to_string(score);
        text.setString(r);
        window.clear();
        window.draw(basket);
        for (Item item : items)
            window.draw(item);
        window.draw(text);
        window.display();
    }

    return 0;

}