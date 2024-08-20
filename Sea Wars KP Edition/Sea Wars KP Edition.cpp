#include <iostream>
#include <windows.h>
using namespace std;

int const n = 10;//Размер поля

void vision(int mass[][n]); //показ поля
int ships_alignment_ii(int matrix[][n], int ship_rate, int ship_count);//генерация раастановки кораблей ии
int ship_rotate(int matrix[][n]);//поворот поставленных кораблей ии
void ii_alignment();//раастановка кораблей ии

int main() {
    setlocale(LC_ALL, "RU");
    cout << "М"; Sleep(200); cout << "О"; Sleep(200); cout << "Р"; Sleep(200); cout << "С"; Sleep(200); cout << "К"; Sleep(200);
    cout << "О"; Sleep(200); cout << "Й"; Sleep(200); cout << "    "; Sleep(200); cout << "Б"; Sleep(200); cout << "О"; Sleep(200);
    cout << "Й"; Sleep(1000); cout << "\n" << "\n" << "\n KP Edition\n"; Sleep(1000); cout << "\n" << "\n" << "\n" << "\n";

    ii_alignment();//раастановка кораблей ии
}

void vision(int mass[][n]) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            if (mass[i][j] == 0)
                cout << " - ";
            else {
                cout << " 0 "/*mass[i][j] */;
            }
        cout << endl;
    }
 }

int ships_alignment_ii(int matrix[][n], int ship_rate, int ship_count) {
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
                if (matrix[x][y] == 1 || matrix[x][y + 1] == 1 || matrix[x][y - 1] == 1 || matrix[x + 1][y] == 1 ||
                    matrix[x + 1][y + 1] == 1 || matrix[x + 1][y - 1] == 1 || matrix[x - 1][y] == 1 || matrix[x - 1][y + 1] == 1 ||
                    matrix[x - 1][y - 1] == 1){
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
                 matrix[x][y] = 1;
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
     return matrix[n][n];//сохранить расстановку ии
 }

int ship_rotate(int matrix[][n]) {
     int ship_rate = 4;//кол-во палуб
     int ship_count = 1;//кол-во кораблей
     ships_alignment_ii(matrix, ship_rate, ship_count);
     --ship_rate;
     ++ship_count;
     ships_alignment_ii(matrix, ship_rate, ship_count);
     --ship_rate;
     ++ship_count;
     ships_alignment_ii(matrix, ship_rate, ship_count);
     --ship_rate;
     ++ship_count;
     ships_alignment_ii(matrix, ship_rate, ship_count);
     return matrix[n][n];
}

void ii_alignment() {
    srand(time(NULL));
    int cpu_matrix[n][n] = { 0 };
    ship_rotate(cpu_matrix);
    vision(cpu_matrix);
    system("pause");//фунция для теста
}