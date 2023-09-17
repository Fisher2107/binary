//How to compile: g++ -c main.cpp
//How to link: g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
#include <SFML/Graphics.hpp>

int main()
{
    //Create a rectangle class, color, posisition,speed,size
    class Rectangle {
        private:
            sf::RectangleShape rectangle;
            double speed_ang = 0;
            double speed_x=0;
            double speed_y=0;
        public:
            Rectangle(){
                rectangle.setFillColor(sf::Color(255,255,255));
                rectangle.setSize(sf::Vector2f(200,20));
            }
            void set_pos(int x, int y){
                rectangle.setPosition(x,y);
            }
            void set_col(int x, int y, int z){
                rectangle.setFillColor(sf::Color(x,y,z));
            }
            void set_speed(double x,double y){
                speed_x=x;
                speed_y=y;
            }
            void set_size(int x, int y){
                rectangle.setSize(sf::Vector2f(x,y));
            }
            void set_speed_ang(double x){
                speed_ang=x;
            }
            sf::RectangleShape draw(){
                rectangle.move(speed_x,speed_y);
                rectangle.rotate(speed_ang);
                return rectangle;
            }


    };

    sf::RenderWindow window(sf::VideoMode(800, 600), "Binary");
    window.setFramerateLimit(60);

    Rectangle rect1;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(rect1.draw());
        window.display();
        
    }

    return 0;
}