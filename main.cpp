#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <sstream>


const int width = 1024;
const int height = 512;
const int pixels = 32;
std::vector<std::vector<sf::Vector2i>> map;
std::vector<sf::Vector2i> tempmap;
sf::Texture tileTexture;
sf::Sprite tiles;


/***
class Player
{
public:
    sf::RectangleShape rect;
    float bottom, left,right, top;
    Player(sf::Vector2f position, sf::Vector2f size, sf::Color color)
    {
        rect.setPosition(position);
        rect.setSize(size);
        rect.setFillColor(color);
    }
};

void update()
{
    bottom = rect.getPosition().y + rect.getSize().y;
    top = rect.getPosition().y;
    right = rect.getPosition().x + rect.getSize().x;
    left = rect.getPosition().x;
}

bool collision(Player p)
{
    if(right < p.left || left > p.right || top > p.bottom || bottom < p.top)
    {
        return false;
    }
    return true;
}
*/

// INICIO DE CODIGO PARA CARGAR MAPA
void LoadMap(const char*filename)
{
    std::ifstream openFile(filename);
    tempmap.clear();
    map.clear();
    if(openFile.is_open())
    {
        std::string tileLocation;
        openFile >> tileLocation;
        tileTexture.loadFromFile(tileLocation);
        tiles.setTexture(tileTexture);
        while(!openFile.eof())
        {
            std::string str;
            std::string value;
            std::getline(openFile, str);
            std::stringstream stream(str);
            while(std::getline(stream, value, ' '))
            {
                std::string xx = value.substr(0, value.find(','));
                std::string yy = value.substr(value.find(',')+1);
                int x, y, i, j;
                for(i = 0; i < xx.length(); i++)
                {
                    if(!isdigit(xx[i]))
                        break;
                }
                for(j = 0; j < yy.length(); j++)
                {
                    if(!isdigit(yy[j]))
                        break;
                }
                x = (i == xx.length()) ? atoi(xx.c_str()) : -1;
                y = (i == yy.length()) ? atoi(yy.c_str()) : -1;
                tempmap.push_back(sf::Vector2i(x,y));
            }
            map.push_back(tempmap);
            tempmap.clear();
        }
    }
}
// FIN DE CODIGO PARA CARGAR MAPA



int main()
{
// INICIO DE CODIGO PARA CARGAR MUSICA
    sf::SoundBuffer soundBuffer;
    sf::Sound sound;
    if(!soundBuffer.loadFromFile("assets/music.ogg"))
        std::cout << "Missing Sound music.ogg" << std::endl;
    sound.setBuffer(soundBuffer);
    sound.setVolume(40);
    sound.setLoop(true);
// FIN DE CODIGO PARA CARGAR MUSICA



// INICIO DE CODIGO PARA CARGAR VENTANA Y EVENTOS
    LoadMap("assets/map.txt");
    sf::RenderWindow window;
    sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width/2)-755, (sf::VideoMode::getDesktopMode().height/2)-390);
    window.create(sf::VideoMode(width, height, pixels), "JUEGO POO II", sf::Style::Titlebar | sf::Style::Close);
    window.setKeyRepeatEnabled(true);
    while(window.isOpen())
    {
        sf::Event Event;
        while(window.pollEvent(Event))
        {
            switch(Event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if(Event.key.code == sf::Keyboard::L)
                        LoadMap("assets/map.txt");
                        break;
                    if(Event.key.code == sf::Keyboard::Escape)
                        window.close();
                        break;
                    if(Event.key.code == sf::Keyboard::M)
                        sound.play();
                        break;
                    if(Event.key.code == sf::Keyboard::N)
                        sound.stop();
                        break;
            }
        }
        window.clear(sf::Color(0, 240, 255));
        for(int i = 0; i <  map.size(); i++)
        {
            for(int j = 0; j < map[i].size(); j++)
            {
                if(map[i][j].x != -1 && map[i][j].y != -1)
                {
                    tiles.setPosition(j * 32, i * 32);
                    tiles.setTextureRect(sf::IntRect(map[i][j].x * 32, map[i][j].y * 32, 32, 32));
                    window.draw(tiles);
                }
            }
        }
        window.display();
    }
// FIN DE CODIGO PARA CARGAR VENTANA

    return 0;
}
