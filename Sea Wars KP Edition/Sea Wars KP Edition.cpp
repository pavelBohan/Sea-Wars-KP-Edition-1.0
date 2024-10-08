#include <iostream>
#include<cmath>
#include <windows.h>
using namespace std;

int const n = 10;//Размер поля
int cpu_matrix[n][n] = { 0 };// поле ии
int player1_matrix[n][n] = { 0 }; //поле первого игрока
int player2_matrix[n][n] = { 0 }; //поле второго игрока

int player1_dead_ship_count = 0;//количество убитых первым игроком кораблей
int player2_dead_ship_count = 0;//количество убитых вторым игроком кораблей
int cpu_dead_ship_count = 0;//количество убитых компьютером кораблей

//всё, что отвечает за вывод поля на экран
void vision(int mass[n][n]); //показ поля.
void x_ray(int mass[n][n]);//показ поля в режиме отладки 

//всё, что отвечает за расстановку
int ships_alignment_ii(int matrix[][n], int ship_rate, int ship_count);//генерация раастановки кораблей ии
int ship_rotate(int matrix[n][n]);//поворот поставленных кораблей ии
int random_alignment(int matrix[n][n]);//расстановка кораблей

//всё, что отвечает за сражение
int battle(int dead_ship_count, int matrix[n][n]);//игрок наносит удар по вражескому полю
int popadanie(int dead_ship_count, int x, int y, int matrix[n][n]);//проверка на попадание по кораблю
int ship_kill(int dead_ship_count, int x, int y, int matrix[n][n]);//проверка на убийство корабля

int main() {
    setlocale(LC_ALL, "RU");
    cout << "М"; Sleep(200); cout << "О"; Sleep(200); cout << "Р"; Sleep(200); cout << "С"; Sleep(200); cout << "К"; Sleep(200);
    cout << "О"; Sleep(200); cout << "Й"; Sleep(200); cout << "    "; Sleep(200); cout << "Б"; Sleep(200); cout << "О"; Sleep(200);
    cout << "Й"; Sleep(1000); cout << "\n" << "\n" << "\n KP Edition\n"; Sleep(1000); cout << "\n" << "\n" << "\n" << "\n";

    int gamemode, first_try, choice; cout << "\nВыберите режим игры:\nНажмите 1 для игры с другом\nНажмите 2 для игры с компьютером\nНажмите любое другое число для выхода из игры\n";
    cin >> gamemode;
    switch (gamemode)
    {
    case(1):
        cout << "\nРежим еще в разработке, вы будете перенаправлены в режим против компьютера\n";
    case(2)://сражение с компьютером
        srand(time(NULL));
        random_alignment(cpu_matrix);//раастановка кораблей ии  
        cout << "\nВведите 1, если хотите расставить корабли самостоятельно\nВведите другое любое число, если хотите случайную расстановку кораблей\n";
        cin >> choice;
        switch (choice)
        {
        case(1):
            cout << "\nФункция еще в разработке, корабли будут расставлены случайно\n";
        default:
            random_alignment(player1_matrix);//случайная расстановка кораблей игрока
            cout << "\nВаши корабли успешно расставлены!\n";
            break;
        }
        first_try = rand() % 2;//случайный выбор человека, который ходит первым
        switch (first_try)
        {
        case(0):
                do
                {
                    cout << "\nНаша очередь наносить удар!!!\n";
                    battle(player1_dead_ship_count, cpu_matrix);//бьем по полю компьютера
                   // cout << "\nКомпьюетр наносит ответный удар!!!\n";
                   // battle(*cpu_dead_ship_count, player1_matrix);//компьютер бьёт по полю игрока
                } while (player1_dead_ship_count < 10 || cpu_dead_ship_count < 10);
                if (player1_dead_ship_count == 10)
                {
                    cout << "\nВы победили!!!\n";
                }
                else
                {
                    cout << "\nКомпьютер победил!!!\n";
                }
            break;
        case(1):
                do
                {
                   // cout << "\nКомпьютер проводит атаку!\n";
                   // battle(*cpu_dead_ship_count, player1_matrix);//компьютер бьёт по полю игрока
                    cout << "\nТеперь мы наносим удар!!!\n";
                    battle(player1_dead_ship_count ,cpu_matrix);//бьем по полю компьютера
                } while (player1_dead_ship_count < 10 || cpu_dead_ship_count < 10);
                if (player1_dead_ship_count == 10)
                {
                    cout << "\nВы победили!!!\n";
                }
                else
                {
                    cout << "\nКомпьютер победили!!!\n";
                }
            break;
        default:
            cout << "Ты никак не должен был пописать сюда, но если так случилось, то это ошибка, обратись к создателям этого кода:\n@MoonExe\n@RinneJaaba\n@ProgressMachine\n";
            break;
        }
    default:
        cout << "\n Морское пока! \n";
        break;
    }
}

void vision(int matrix[n][n]) {
    cout << "    1  2  3  4  5  6  7  8  9  10 \n";
    int stroka = 0;
    for (int x = 0; x < n; ++x) {
        stroka++;
        if (stroka == 10)
        {
            cout << stroka << " ";
        }
        else
        {
            cout << " " << stroka << " ";
        }
        for (int y = 0; y < n; y++)
            if (matrix[x][y] <= 3)
                cout << " - ";//" " << matrix[x][y] << " ";
            else
            {
                if (matrix[x][y] % 3 == 0)
                {
                    cout << " 0 ";
                }
                else
                {
                    cout << " + ";
                }
            }
        cout << endl;
    }
 }

void x_ray(int matrix[][n]) {
    int choice,stroka; cout << "\n1 - матрица\n2 - читы\n"; cin >> choice;
    switch (choice)
    {
    case(1):
        cout << "    1  2  3  4  5  6  7  8  9  10 \n";
        stroka = 0;
        for (int x = 0; x < n; ++x) {
            stroka++;
            if (stroka == 10)
            {
                cout << stroka << " ";
            }
            else
            {
                cout << " " << stroka << " ";
            }

            for (int y = 0; y < n; ++y)
                if (matrix[x][y] == 3)
                    cout << " " << matrix[x][y] << " ";//" # "; //" " << matrix[x][y] << " ";
                else if (matrix[x][y] == 2)
                {
                    cout << " " << matrix[x][y] << " ";//" - ";
                }
                else
                {
                    if (matrix[x][y] % 3 == 0)
                    {
                        cout << " " << matrix[x][y] << " ";//" 0 ";
                    }
                    else
                    {
                        cout << " " << matrix[x][y] << " ";//" + ";
                    }
                }
            cout << endl;
        }
        break;
    case(2):
        cout << "    1  2  3  4  5  6  7  8  9  10 \n";
        stroka = 0;
        for (int x = 0; x < n; ++x) {
            stroka++;
            if (stroka == 10)
            {
                cout << stroka << " ";
            }
            else
            {
                cout << " " << stroka << " ";
            }
            for (int y = 0; y < n; ++y)
                if (matrix[x][y] == 3)
                    cout << " # ";
                else if (matrix[x][y] == 2)
                {
                    cout << " - ";
                }
                else
                {
                    if (matrix[x][y] % 3 == 0)
                    {
                        cout << " 0 ";
                    }
                    else
                    {
                        cout << " + ";
                    }
                }
            cout << endl;
        }
        cout << "\nКоличество убитых кораблей первым игроком " << player1_dead_ship_count << "\nКоличество убитых кораблей вторым игроком " << player2_dead_ship_count << "\nКоличество убитых кораблей второго игрока " << cpu_dead_ship_count << "\n";
        break;
    default:
        break;
    }
}

int ships_alignment_ii(int matrix[n][n], int ship_rate, int ship_count) {
    bool s_i_p = 1;//возможна ли установка(setting_is_possible)
    int x, y;//координаты
    int turn = 0;//поворот
    int temp_x;
    int temp_y;
    int num_ship = 0;
    while (num_ship < ship_count) {
        do {
            x = rand() % n;//[x][] - строчка, вертикаль
            y = rand() % n;//точка[][y] - столбик, горизонталь
            //создание точки в двумерном массиве [x][y]
            temp_x = x;
            temp_y = y;

            turn = rand() % 4;//выбор случайного положения

            s_i_p = 1;
            for (int i = 0; i < ship_rate; ++i) {
                //если корабль выходит за границами поля, то нельзя установить
                if (x < 0 || y < 0 || x >= n || y >= n) {
                    s_i_p = 0;
                    break;
                }
                //если в радиусе 1 клетки есть корабль, то нелья установить
                if (matrix[x][y] == 3 || matrix[x][y + 1] == 3 || matrix[x][y - 1] == 3 || matrix[x + 1][y] == 3 ||
                    matrix[x + 1][y + 1] == 3 || matrix[x + 1][y - 1] == 3 || matrix[x - 1][y] == 3 || matrix[x - 1][y + 1] == 3 ||
                    matrix[x - 1][y - 1] == 3){
                    s_i_p = 0;
                    break;
                }
                switch (turn) {//0 - от точки вверх, 1 - от точки вправо, 2 - от точки вниз, 3 - от точки влево.
                 case 0:
                    x++;
                    break;
                 case 1:
                     y++;
                     break;
                 case 2:
                     x--;
                     break;
                 case 3:
                     y--;
                     break;
                 }
             }
         } 
        while (s_i_p != 1);

         if (s_i_p == 1) {
             x = temp_x;
             y = temp_y;
             for (int i = 0; i < ship_rate; ++i) {
                 matrix[x][y] = 3;
                 //построение корабля от точки.
                 switch (turn) {
                 case 0:
                     x++;
                     break;
                 case 1:
                     y++;
                     break;
                 case 2:
                     x--;
                     break;
                 case 3:
                     y--;
                     break;

                 }
             }
         }
         num_ship++; //количество поставленных кораблей +1
     }
     return matrix[n][n];//сохранить двумерный массив
 }

int ship_rotate(int matrix[n][n]) {
     int ship_rate = 4;//кол-во палуб
     int ship_count = 1;//кол-во кораблей
     ships_alignment_ii(matrix, ship_rate, ship_count);//создание и размещение четырехпалубного корабля
     --ship_rate;
     ++ship_count;
     ships_alignment_ii(matrix, ship_rate, ship_count);//содание и размещение двух трёхпалубных кораблей
     --ship_rate;
     ++ship_count;
     ships_alignment_ii(matrix, ship_rate, ship_count);//создание и размещение трех двухпалубных кораблей
     --ship_rate;
     ++ship_count;
     ships_alignment_ii(matrix, ship_rate, ship_count);//создание и размещение четырех однопалубных кораблей
     return matrix[n][n];
}

int random_alignment(int matrix[n][n]) {
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix[i][j] = 2;
        }
    }
    ship_rotate(matrix);
    return matrix[n][n];
}

int battle(int dead_ship_count, int matrix[n][n])
{   
    int x, y;
    do
    {
        cout << "\n";
        x_ray(matrix);
        cout << "Введите координаты клетки, которую будем атаковать!\nВведите цифру по вертикали:\n";
        cin >> x; 
        if (x > 10 && x < 1)
        {
            do
            {
                cout << "\nКапитан, это пространство вне нашей боевой зоны!!!\nВведите подходящие координаты от 1 до 10\n" << "\n";
            } while (x > 10 && x < 1);
        }
        cout << "Введите цифру по горизонтали:\n"; cin >> y;
        if (y > 10 && y < 1)
        {
            do
            {
                cout << "\nКапитан, это пространство вне нашей боевой зоны!!!\nВведите подходящие координаты от 1 до 10\n" << "\n";
            } while (y > 10 && y < 1);
        }
        matrix[x - 1][y - 1] = pow(matrix[x - 1][y - 1], 2);
        popadanie(dead_ship_count,x - 1, y - 1, matrix);
    } while (matrix[x][y] % 2 != 0);
    return matrix[n][n];
}

int popadanie(int dead_ship_count, int x, int y, int matrix[n][n])
{
    if (matrix[x][y] % 3 == 0)
    {
        srand(time(NULL));
        int a = 4;//количество возможных диалогов
        int slovo = rand() % a;
        switch (slovo)
        {
        case(0):
            cout << "\n Есть пробитие!! \n" << "\n";
            break;
        case(1):
            cout << "\n Попадание! \n" << "\n";
            break;
        case(2):
            cout << "\n Прямо в цель! \n" << "\n";
            break;
        case(3):
            cout << "\n В яблОЧКО! \n" << "\n";
            break;
        default:
            break;
        }
        ship_kill(dead_ship_count, x, y, matrix);
        battle(dead_ship_count, matrix);
    }
    else
    {
        srand(time(NULL));
        int a = 4;//количество возможных диалогов
        int slovo = rand() % a;
        switch (slovo)
        {
        case(0):
            cout << "\n Там ничего нет!! \n";
            break;
        case(1):
            cout << "\n Мимо! \n";
            break;
        case(2):
            cout << "\n Опять двадцать пять! \n";
            break;
        case(3):
            cout << "\n Корабля здесь нет! \n";
            break;
        default:
            break;
        }
        return matrix[n][n];
    }
    
}

int ship_kill(int dead_ship_count, int x, int y, int matrix[n][n])
{
    if (matrix[x][y + 1] != 3 && matrix[x][y - 1] != 3 && matrix[x + 1][y] != 3 && matrix[x - 1][y] && matrix[x][y] % 3 == 0)
    {
        matrix[x][y] = pow(matrix[x][y], 2);
        matrix[x][y + 1] = pow(matrix[x][y + 1], 2);
        matrix[x][y - 1] = pow(matrix[x][y - 1], 2);
        matrix[x + 1][y] = pow(matrix[x + 1][y], 2);
        matrix[x + 1][y + 1] = pow(matrix[x + 1][y + 1], 2);
        matrix[x + 1][y - 1] = pow(matrix[x + 1][y - 1], 2);
        matrix[x - 1][y] = pow(matrix[x - 1][y], 2);
        matrix[x - 1][y + 1] = pow(matrix[x - 1][y + 1], 2);
        matrix[x - 1][y - 1] = pow(matrix[x - 1][y - 1], 2);
        dead_ship_count++;
        cout << "\nПошёл ко дну!!!\n" << "\n";
    }
    return matrix[n][n];
}