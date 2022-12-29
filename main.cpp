#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "map.h" //подключили код с картой
#include <list>
#include <math.h>
using namespace sf;

////////////////////////////КЛАСС СУЩНОСТЬ////////////////////////
class Entity {
public:
    enum { left, right, up, down, stay} state;// тип перечисления - состояние объекта
    float dx, dy, x, y, speed, moveTimer;//добавили переменную таймер для будущих целей
    int w, h, health; //переменная “health”, хранящая жизни игрока
    bool life; //переменная “life” жизнь, логическая
    Texture texture;//сфмл текстура
    Sprite sprite;//сфмл спрайт
    float CurrentFrame;//хранит текущий кадр
    std::string name;//враги могут быть разные, врагов можно различать по именам
//каждому можно дать свое действие в update() в зависимости от имени


    Entity(Image &image, float X, float Y, int W, int H, std::string Name){


    }


    FloatRect getRect(){//метод получения прямоугольника. его коорд, размеры (шир,высот).
        FloatRect FR(x, y, w, h); // переменная FR типа FloatRect
        return FR;
        //return FloatRect(x, y, w, h);
        //Тип данных (класс) "sf::FloatRect" позволяет хранить четыре координаты прямоугольника
        //в нашей игре это координаты текущего расположения тайла на карте
        //далее это позволит спросить, есть ли ещё какой-либо тайл на этом месте
        //эта ф-ция нужна для проверки пересечений
    }

    virtual void update(float time) = 0;
};
////////////////////////////КЛАСС ИГРОКА////////////////////////
class Player :public Entity {
public:
    int playerScore;//эта переменная может быть только у игрока
    Player(Image &image, float X, float Y, int W, int H, std::string Name) :Entity(image, X,Y, W, H, Name){

    }
    void control(){

    }
//Метод проверки столкновений с элементами карты
    void checkCollisionWithMap(float Dx, float Dy) {

    }
    void update(float time) //метод "оживления/обновления" объекта класса.
    {

    }
};




class Enemy :public Entity{
public:
    int direction;//направление движения врага

    Enemy(Image &image, float X, float Y, int W, int H, std::string Name) :Entity(image, X, Y, W, H, Name){

    }
    void checkCollisionWithMap(float Dx, float Dy)//ф-ция проверки столкновений с картой
    {

    }
    void update(float time)
    {

    }
};//класс Enemy закрыт




class Bullet :public Entity{//класс пули
public:
    Entity* point;
    int direction;//направление пули
    Bullet(Image &image, float X, float Y, int W, int H, std::string Name, Entity *dir):Entity(image, X, Y, W, H, Name){

    }
    void update(float time)
        {


    }
};



Enemy* RandomGenerationEnemy(Image easyEnemyImage){

}

int main()
{

    return 0;
}


