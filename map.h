#ifndef MAP
#define MAP
#include <SFML/Graphics.hpp>
const int HEIGHT_MAP = 20;//размер карты высота
const int WIDTH_MAP = 25;//размер карты ширина
std::string TileMap[HEIGHT_MAP] = {
"0000000000000000000000000",
"0                       0",
"0                       0",
"0                       0",
"0                       0",
"0                       0",
"0                       0",
"0                       0",
"0                       0",
"0                       0",
"0                       0",
"0                       0",
"0                 s     0",
"0                    h  0",
"0                       0",
"0          f     s      0",
"0                       0",
"0       h         f     0",
"0                       0",
"0000000000000000000000000",
};
void randomMapGenerate(){//рандомно расставляем камни

};
#endif // MAP

