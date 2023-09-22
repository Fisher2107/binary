//How to compile: g++ -c main.cpp
//How to link: g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>

int main()
{
    class Rectangle {
        private:
            sf::RectangleShape rectangle;
            double speed_ang = 0;
            double speed_x=0;
            double speed_y=0;
            
        public:
            Rectangle(){
                set_col(255,255,255);
                set_size(100,20);
                set_pos(0,0);
            }
            void set_pos(int x, int y){
                rectangle.setPosition(x,y);
                sf::Vector2f center(rectangle.getSize()/2.f);
                rectangle.setOrigin(center);
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

    class Duet {
        private:
            sf::CircleShape red;
            sf::CircleShape blue;
            int speed_ang = 0;
            int center[2] = {0,0};
            double width = 0;
            bool left_blue = 1;
            float coords[1000][2];
            int coords_index = 0;

        void fillcoords(){
            float increment=2*M_PI / 1000;
            float theta = 0;
            for(int i=0;i<1000;i++){
                coords[i][0]= center[0] + ((width/2) * cos(theta));
                coords[i][1]= center[1] + (width/2) * sin(theta);
                theta+=increment;
                //std::cout<<coords[i][0]<<"  "<<coords[i][1]<<std::endl;
            }
        }
            
        public:
            Duet(){
                red.setRadius(10);
                blue.setRadius(10);
                red.setFillColor(sf::Color::Red);
                blue.setFillColor(sf::Color::Blue);
                set_pos(300,300,90);
            }

            void set_speed_ang(double x){
                speed_ang=x;
            }

            void set_pos(int x,int y,int wid){
                width = wid;
                center[0]=x;
                center[1]=y;
                fillcoords();
            }

            void swap(){
                left_blue = !left_blue;
            }
            
            void draw(){
                if (coords_index>=1000){
                    coords_index-=1000;
                }else if(coords_index<0){
                    coords_index+=1000;
                }
                red.setPosition(
                    coords[coords_index%1000][0],
                    coords[coords_index%1000][1]
                    );
                blue.setPosition(
                    coords[(coords_index+500)%1000][0],
                    coords[(coords_index+500)%1000][1]
                    );
                coords_index+=speed_ang;
                std::cout<<coords_index<<std::endl;
            }

            sf::CircleShape draw_red() {
                return red;
            }
            sf::CircleShape draw_blue(){
                return blue;
            }



    };

    sf::RenderWindow window(sf::VideoMode(800, 600), "Binary");
    window.setFramerateLimit(60);

    Rectangle rect1;
    rect1.set_speed(0,1);
    rect1.set_speed_ang(4);
    rect1.set_pos(300,-50);

    Duet duet;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        //if left duet.set_speed_ang =1, elif -1, else 0
        window.clear();
        window.draw(rect1.draw());
        //Controls for duet
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            duet.set_speed_ang(11);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            duet.set_speed_ang(-11);
        } else{
            duet.set_speed_ang(0);
        }



        duet.draw();
        window.draw(duet.draw_red());
        window.draw(duet.draw_blue());
        window.display();
        
    }

    return 0;
}