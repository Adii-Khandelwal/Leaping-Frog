#include <iostream>
#include <deque>
#include <vector>
#include <conio.h>
#include <time.h>
using namespace std;

class Player
{
public:
    int x, y;
    Player(int width) { x = width / 2; y = 0; }
};

class Lane
{
private:
    deque<bool> cars;
    bool right;
public:
    Lane(int width)
    {
        for (int i = 0; i < width; i++)
            cars.push_front(true);
        right = rand() % 2;
    }
    void Move()
    {
        if (right)
        {
            if (rand() % 10 == 1)
                cars.push_front(true);
            else
                cars.push_front(false);
            cars.pop_back();
        }
        else
        {
            if (rand() % 10 == 1)
                cars.push_back(true);
            else
                cars.push_back(false);
            cars.pop_front();
        }
    }
    bool CheckPos(int pos) { return cars[pos]; }
    void ChangeDirection() { right = !right; }
};

class Game
{
private:
    bool quit;
    int numberOfLanes;
    int width;
    int score=0;
    Player* player;
    vector<Lane*> map;
public:
    Game(int w = 20, int h = 10)
    {
        numberOfLanes = h;
        width = w;
        quit = false;
        for (int i = 0; i < numberOfLanes; i++)
            map.push_back(new Lane(width));
        player = new Player(width);
    }
    ~Game()
    {
        delete player;
        for (int i = 0; i < map.size(); i++)
        {
            Lane* current = map.back();
            map.pop_back();
            delete current;
        }
    }
    void Draw()
    {
        system("cls");
        for (int i = 0; i < numberOfLanes; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (i == 0 && (j == 0 || j == width - 1))
                    cout << "S";
                else if (i == numberOfLanes - 1 && (j == 0 || j == width - 1))
                    cout << "F";
                else if (map[i]->CheckPos(j) && i != 0 && i != numberOfLanes - 1)
                    cout << "#";
                else if (player->x == j && player->y == i)
                    cout << "V";
                else
                    cout << " ";
            }
            cout << endl;
        }
        cout << "Score: " << score << endl;
    }
    void Input()
    {
        if (_kbhit())
        {
            char current = _getch();
            if (current == 'a')
                player->x--;
            if (current == 'd')
                player->x++;
            if (current == 'w')
                player->y--;
            if (current == 's')
                player->y++;
            if (current == 'q')
                quit = true;
        }
    }
    void Logic()
    {
        for (int i = 1; i < numberOfLanes - 1; i++)
        {
            if (rand() % 10 == 1)
                map[i]->Move();
            if (map[i]->CheckPos(player->x) && player->y == i)
                quit = true;
        }
        if (player->y == numberOfLanes - 1)
        {
            score++;
            player->y = 0;
            cout << "\x07";
            map[rand() % numberOfLanes]->ChangeDirection();
        }
    }
    void Run()
    {
        while (!quit)
        {
            Input();
            Draw();
            Logic();
        }
    }
};

int main()
{
    srand(time(NULL));
    Game game(30, 5);
    game.Run();
    cout << "Game over!" << endl;
    getchar();
    return 0;
}
