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
        x = X; y = Y; //координата появления спрайта
        w = W/2; h = H/2;
        name = Name;
        moveTimer = 0;
        dx = 0; dy = 0;
        speed = 0;
        CurrentFrame = 0;
        health = 100;
        life = true; //инициализировали логическую переменную жизни, герой жив
        texture.loadFromImage(image); //заносим наше изображение в текстуру
        sprite.setTexture(texture); //заливаем спрайт текстуро

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
        playerScore = 0;
        state = stay;
        if (name == "Player1"){
            //Задаем спрайту один прямоугольник для
            //вывода одного игрока. IntRect – для приведения типов
            sprite.setTextureRect(IntRect(0, 0, w, h));
        }
    }
    void control(){
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
                   state = left;
                   speed = 0.1;
               }
       if (Keyboard::isKeyPressed(Keyboard::Right)) {
           state = right;
           speed = 0.1;
       }
       if (Keyboard::isKeyPressed(Keyboard::Up)) {
           state = up;
           speed = 0.1;
       }
       if (Keyboard::isKeyPressed(Keyboard::Down)) {
           state = down;
           speed = 0.1;
       }
    }
//Метод проверки столкновений с элементами карты
    void checkCollisionWithMap(float Dx, float Dy) {
        for (int i = y / 32; i < (y + h) / 32; i++)//проходимся по элементам карты
                    for (int j = x / 32; j<(x + w) / 32; j++)
                    {
                        if (TileMap[i][j] == '0')//если элемент тайлик земли
                        {
                            if (Dy > 0) { y = i * 32 - h; dy = 0; }//по Y
                            if (Dy < 0) { y = i * 32 + 32; dy = 0; }//столкновение с верхними краями
                            if (Dx > 0) { x = j * 32 - w; dx = 0; }//с правым краем карты
                            if (Dx < 0) { x = j * 32 + 32; dx = 0; }// с левым краем карты
                        }
                        if (TileMap[i][j] == 's') {
                            playerScore++; //если взяли камень
                            TileMap[i][j] = ' ';
                        }
                        if (TileMap[i][j] == 'f') {
                            health -= 40;//если взяли ядовитый цветок
                            TileMap[i][j] = ' ';//убрали цветок
                        }
                        if (TileMap[i][j] == 'h') {
                            health += 20;//если взяли сердечко
                            TileMap[i][j] = ' ';//убрали сердечко
                        }
                    }
    }

    void update(float time) //метод "оживления/обновления" объекта класса.
    {
        if (life) {//проверяем, жив ли герой
                    control();//функция управления персонажем
                    switch (state)//делаются различные действия в зависимости от состояния
                    {
                        case right:{//состояние идти вправо
                            dx = speed;
                            CurrentFrame += 0.005*time;
                            if (CurrentFrame > 10) CurrentFrame -= 10;
                                sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96));
                                sprite.setScale({1,1});
                            break;

                        }
                        case left:{//состояние идти влево
                            dx = -speed;
                            CurrentFrame += 0.005*time;

                            if (CurrentFrame > 10) CurrentFrame -= 10;
                                sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96));

                            break;
                        }
                        case up:{//идти вверх
                            dy = -speed;
                            CurrentFrame += 0.005*time;
                            if (CurrentFrame > 10) CurrentFrame -= 10;
                            sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96));
                            break;
                        }
                        case down:{//идти вниз
                            dy = speed;
                            CurrentFrame += 0.005*time;
                            if (CurrentFrame > 10) CurrentFrame -= 10;
                            sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96));
                            break;
                        }
                        case stay:{//стоим
                            dy = speed;
                            dx = speed;
                            break;
                        }
                    }
                    x += dx*time; //движение по “X”
                    checkCollisionWithMap(dx, 0);//обрабатываем столкновение по Х
                    y += dy*time; //движение по “Y”
                    checkCollisionWithMap(0, dy);//обрабатываем столкновение по Y
                    speed = 0; //обнуляем скорость, чтобы персонаж остановился.
                    //state = stay; //состояние - стоим
                    sprite.setPosition(x, y); //спрайт в позиции (x, y).
                    if (health <= 0){ life = false; }//если жизней меньше 0, либо равно 0, то умираем
                }
    }
};




class Enemy :public Entity{
public:
    int direction;//направление движения врага

    Enemy(Image &image, float X, float Y, int W, int H, std::string Name) :Entity(image, X, Y, W, H, Name){
        if (name == "EasyEnemy"){
                //Задаем спрайту один прямоугольник для
                //вывода одного игрока. IntRect – для приведения типов
                sprite.setTextureRect(IntRect(0, 0, w, h));
                direction = rand() % (3); //Направление движения врага задаём случайным образом
                //через генератор случайных чисел
                speed = 0.1;//даем скорость.этот объект всегда двигается
                dx = speed;
                sprite.setScale({1,1});
                }
    }
    void checkCollisionWithMap(float Dx, float Dy)//ф-ция проверки столкновений с картой
    {
        for (int i = y / 32; i < (y + h) / 32; i++)//проходимся по элементам карты
                   for (int j = x / 32; j<(x + w) / 32; j++)
                   {
                       if (TileMap[i][j] == '0')//если элемент - тайлик земли
                       {
                           if (Dy > 0) {
                               y = i * 32 - h; dy = -0.1;
                               direction = rand() % (3); //Направление движения врага
                           }//по Y
                           if (Dy < 0) {
                               y = i * 32 + 32; dy = 0.1;
                               direction = rand() % (3);//Направление движения врага
                           }//столкновение с верхними краями
                           if (Dx > 0) {
                               x = j * 32 - w; dx = -0.1;
                               direction = rand() % (3);//Направление движения врага
                           }//с правым краем карты
                           if (Dx < 0) {
                               x = j * 32 + 32; dx = 0.1;
                               direction = rand() % (3); //Направление движения врага
                           }// с левым краем карты
                       }
                   }
    }
    void update(float time)
    {
        if (name == "EasyEnemy"){//для персонажа с таким именем логика будет такой
                    if (life) {//проверяем, жив ли герой
                    switch (direction)//делаются различные действия в зависимости от состояния
                    {
                        case 0:{//состояние идти вправо
                            dx = speed;
                            CurrentFrame += 0.005*time;
                            if (CurrentFrame > 3) CurrentFrame -= 3;
                            sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 0, 32, 32));
                            break;
                        }
                        case 1:{//состояние идти влево
                            dx = -speed;
                            CurrentFrame += 0.005*time;
                            if (CurrentFrame > 3) CurrentFrame -= 3;
                            sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 32, 32, 32));
                            break;
                        }
                        case 2:{//идти вверх
                            dy = -speed;
                            CurrentFrame += 0.005*time;
                            if (CurrentFrame > 3) CurrentFrame -= 3;
                            sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 64, 32, 32));
                            break;
                        }
                        case 3:{//идти вниз
                            dy = speed;
                            CurrentFrame += 0.005*time;
                            if (CurrentFrame > 3) CurrentFrame -= 3;
                            sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 96, 32, 32));
                            break;
                        }
                    }
                    x += dx*time; //движение по “X”
                    checkCollisionWithMap(dx, 0);//обрабатываем столкновение по Х
                    y += dy*time; //движение по “Y”
                    checkCollisionWithMap(0, dy);//обрабатываем столкновение по Y
                    sprite.setPosition(x, y); //спрайт в позиции (x, y).
                    if (health <= 0){ life = false; }//если жизней меньше 0, либо равно 0, то умираем
                    }
                }
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
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(sf::VideoMode(800, 640, desktop.bitsPerPixel), "Lesson 14");

    Font font;//шрифт
    font.loadFromFile("CyrilicOld.ttf");//передаем нашему шрифту файл шрифта
    Text text("", font, 20);//создаем объект текст
    text.setColor(Color::Green);

    //покрасили текст в красный
    text.setStyle(Text::Bold);//жирный текст.

    Image map_image;//объект изображения для карты
    map_image.loadFromFile("images/map.png");//загружаем файл для карты
    Texture map;//текстура карты

    map.loadFromImage(map_image);//заряжаем текстуру картинкой
    Sprite s_map;//создаём спрайт для карты
    s_map.setTexture(map);//заливаем текстуру спрайтом


    Image heroImage;
    heroImage.loadFromFile("images/heromain.png"); // загружаем изображение игрока

    Player p(heroImage, 100, 100, 96, 96, "Player1");

    std::list<Entity*> enemies; //список врагов
    std::list<Entity*> Bullets; //список пуль
    std::list<Entity*>::iterator it; //итератор чтобы проходить по элементам списка
    std::list<Entity*>::iterator it2; //итератор чтобы проходить по элементам списка

    const int ENEMY_COUNT = 3; //максимальное количество врагов в игре
    int enemiesCount = 0;

    for (int i = 0; i < ENEMY_COUNT; i++)
    {
        enemies.push_back(RandomGenerationEnemy(easyEnemyImage));
    }


    while (window.isOpen())
        {

        for (it = Bullets.begin(); it != Bullets.end(); it++)
        {
            (*it)->update(time); //запускаем метод update()
        }

        for (it = Bullets.begin(); it != Bullets.end(); )//говорим что проходимся от начала до конца
        {// если этот объект мертв, то удаляем его
            if ((*it)-> life == false) { it = Bullets.erase(it); }
            else it++;//и идем курсором (итератором) к след объекту.
        }

        if(p.life == true){//если игрок жив
            for (it = enemies.begin(); it != enemies.end(); it++){//бежим по списку врагов
                if ((p.getRect().intersects((*it)->getRect())) && ((*it)->name == "EasyEnemy"))
                {
                    p.health = 0;
                    std::cout << "you are lose";
                }
            }
        }


        for (int i = 0; i < HEIGHT_MAP; i++)
            for (int j = 0; j < WIDTH_MAP; j++)
            {
                if (TileMap[i][j] == ' ') s_map.setTextureRect(IntRect(0, 0, 32, 32));
                window.draw(s_map);
                if (TileMap[i][j] == 's') s_map.setTextureRect(IntRect(32, 0, 32, 32));
                if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(64, 0, 32, 32));
                if ((TileMap[i][j] == 'f')) s_map.setTextureRect(IntRect(96, 0, 32, 32));//цветок

                if ((TileMap[i][j] == 'h')) s_map.setTextureRect(IntRect(96, 0, 32, 32));

                //сердце
                s_map.setPosition(j * 32, i * 32);
                window.draw(s_map);
            }
         }

    return 0;
}


