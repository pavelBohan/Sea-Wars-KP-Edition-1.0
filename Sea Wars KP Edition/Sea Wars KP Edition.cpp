#include <iostream>
using namespace std;
int const n = 10;
void vision(int mass[][n]);
int ships_alignment(int matrix[][n], int ship_rate, int ship_count);
int ship_rotate(int matrix[][n]);

 int main() {
    srand(time(NULL));
    int cpu_matrix[n][n] = { 0 };
    ship_rotate(cpu_matrix);
    vision(cpu_matrix);
     system("pause");
     return 0;
 }

 void vision(int mass[][n]) {
     for (int i = 0; i < n; ++i) {
         for (int j = 0; j < n; ++j)
             if (mass[i][j] == 0)
                 cout << ".";
             else {
                 cout << mass[i][j];
             }
         cout << endl;
     }
 }

int ships_alignment(int matrix[][n], int ship_rate, int ship_count) {
    bool s_i_p = 1;//возможна ли установка(setting_is_possible)
     int x, y;//координаты
     int turn = 0;//поворот
     int temp_x;
     int temp_y;
     int num_ship = 0;
     while (num_ship < ship_count) {
         do {
             x = rand() % n;
             y = rand() % n;
             //начальное положение
             temp_x = x;
             temp_y = y;

             turn = rand() % 4;

             s_i_p = 1;
             for (int i = 0; i < ship_rate; ++i) {
                 if (x < 0 || y < 0 || x >= n || y >= n) {
                     s_i_p = 0;
                     break;
                 }
                 if (matrix[x][y] == 1 ||
                     matrix[x][y + 1] == 1 ||
                     matrix[x][y - 1] == 1 ||
                     matrix[x + 1][y] == 1 ||
                     matrix[x + 1][y + 1] == 1 ||
                     matrix[x + 1][y - 1] == 1 ||
                     matrix[x - 1][y] == 1 ||
                     matrix[x - 1][y + 1] == 1 ||
                     matrix[x - 1][y - 1] == 1)
                 {
                     s_i_p = 0;
                     break;
                 }
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
         } while (s_i_p != 1);

         if (s_i_p == 1) {
             x = temp_x;
             y = temp_y;
             for (int i = 0; i < ship_rate; ++i) {
                 matrix[x][y] = 1;
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
         num_ship++;
     }
     return matrix[n][n];
 }

 int ship_rotate(int matrix[][n]) {
     int ship_rate = 4;//кол-во палуб
     int ship_count = 1;//кол-во кораблей
     ships_alignment(matrix, ship_rate, ship_count);
     --ship_rate;
     ++ship_count;
     ships_alignment(matrix, ship_rate, ship_count);
     --ship_rate;
     ++ship_count;
     ships_alignment(matrix, ship_rate, ship_count);
     --ship_rate;
     ++ship_count;
     ships_alignment(matrix, ship_rate, ship_count);
     return matrix[n][n];
}