#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <string>
#include <Thor/Animations.hpp>
using namespace sf;
using namespace thor;
using namespace std;
Texture texture1;
Animator<RectangleShape, string> bigger;
//texture1.loadFromFile("orange.jpg");
class Item : public Drawable, public Transformable {
private:
    RectangleShape shape;
    //FrameAnimation biger;
    virtual void draw(RenderTarget& target, RenderStates states) const {
        target.draw(shape, states);
    }
public:
    Item(int x, int y) {
        shape.setSize(Vector2f(100, 70));
        shape.setPosition(x, y);
        //Texture texture;
        //texture.loadFromFile("orange.jpg");
        shape.setTexture(&texture1);
        //shape.setTextureRect(IntRect(0, 0, 100, 70));
        //shape.setTextureRect(IntRect(2400, 0, 800, 800));
        //shape.setPosition(x,y);
    }
    void movv(float x, float y) {
        shape.move(x, y);
    }
    RectangleShape getShape() {
        return shape;
    }
    void anime() {
        //bigger.update(clock_1.restart());
        bigger.animate(shape);
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
    texture1.loadFromFile("anim.png");
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
    Clock clock_1;
    FrameAnimation biger;
    biger.addFrame(1.f, IntRect(0, 0, 800, 900));
    biger.addFrame(1.f, IntRect(800, 0, 800, 900));
    biger.addFrame(1.f, IntRect(1600, 0, 800, 900));
    biger.addFrame(1.f, IntRect(2400, 0, 800, 900));
    biger.addFrame(1.f, IntRect(3200, 0, 800, 900));
    biger.addFrame(1.f, IntRect(4000, 0, 800, 900));
    biger.addFrame(1.f, IntRect(4800, 0, 800, 900));
    //Animator<RectangleShape, string> bigger;
    bigger.addAnimation("biger", biger, seconds(2.0f));
    //Sprite hello;
    //bigger.playAnimation("down");
    int con = 0;
    while (window.isOpen())
    {
        deltatime = clock.getElapsedTime();
        clock.restart();
        //Time time_2;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

        }
        pos = basket.getPosition();
        if (Keyboard::isKeyPressed(Keyboard::A) && pos.x > 0)
            basket.move(-400 * deltatime.asSeconds(), 0);
        if (Keyboard::isKeyPressed(Keyboard::D) && pos.x < 500)
            basket.move(400 * deltatime.asSeconds(), 0);
        k += deltatime.asMilliseconds();
        for (auto item = items.begin(); item != items.end(); item++) {
            bigger.update(clock_1.restart());
            item->anime();
            item->movv(0, 250 * deltatime.asSeconds());
        }
        items.erase(remove_if(items.begin(), items.end(), outOfScreen), items.end());
        items.erase(remove_if(items.begin(), items.end(), collide), items.end());
        if (k > 400) {
            items.push_back(Item((rand() % 5) * 100, 0));
            k = -((rand() % 5 + 1) * 100);
        }
        //bigger.playAnimation("down");
        //bigger.update(clock_1.restart());
        //bigger.animate(item);
        if (!bigger.isPlayingAnimation()) {
            bigger.playAnimation("biger");
        }
        Vector2f pos;
        r = to_string(score);
        text.setString(r);
        window.clear();
        window.draw(basket);
        window.draw(text);
        for (Item item : items) {
            //bigger.update(clock_1.restart());
            //item.anime();
            window.draw(item);
        }
        //window.draw(text);
        window.display();
    }

    return 0;

}