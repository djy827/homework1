#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
#define MAX 100
long int speed = 0;
int position_x, position_y;
int high, width;
int bullet_x, bullet_y;
int enemy_x, enemy_y;
int map[MAX][MAX];
/*0表示空白，1表示战机*的区域，2表示敌人战机的位置。
3表示上下围墙，4表示左右围墙,5表示子弹的位置*/
int score;
void starup()
{
    high =40;
    width =40;
    position_x = high / 2;
    position_y = width / 2;
    bullet_x = 0;
    bullet_y = position_y;
    enemy_x = 2;
    enemy_y = position_y - 1;
    score = 0;

}
void startMap()
{
    int i, j;
    for (i = 1; i <= high - 1; i++)
    {
        map[i][1] = 4;
        for (j = 2; j <= width - 1; j++)
            map[i][j] = 0;
        map[i][width] = 4;
    }
    i = high;
    for (j = 1; j <= width; j++)
        map[i][j] = 3;

    map[bullet_x][bullet_y] = 5;
    map[position_x - 1][position_y] = 1;
    i = position_x;
    for (j = position_y - 2; j <= position_y + 2; j++)
        map[i][j] = 1;
    map[position_x + 1][position_y - 1] = 1;
    map[position_x + 1][position_y + 1] = 1;
    map[enemy_x][enemy_y] = 2;
    map[enemy_x - 1][enemy_y - 1] = 2;
    map[enemy_x - 1][enemy_y + 1] = 2;
}
void HideCursor()
{
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
void gotoxy(int x, int y) 
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
}
void updateWithoutInput() 
{
    if (bullet_x > 0)
        bullet_x--;
    if ((bullet_x == enemy_x) && (bullet_y == enemy_y))
    {
        score++;
        enemy_x = 0;
        enemy_y = rand() % width;
        bullet_x = 0;
    }
	 if ((bullet_x == enemy_x) && (bullet_y == enemy_y-1))
    {
        score++;
        enemy_x = 0;
        enemy_y = rand() % width;
        bullet_x = 0;
    } if ((bullet_x == enemy_x) && (bullet_y == enemy_y+1))
    {
        score++;
        enemy_x = 0;
        enemy_y = rand() % width;
        bullet_x = 0;
    } if ((bullet_x == enemy_x) && (bullet_y == enemy_y-2))
    {
        score++;
        enemy_x = 0;
        enemy_y = rand() % width;
        bullet_x = 0;
    } if ((bullet_x == enemy_x) && (bullet_y == enemy_y+2))
    {
        score++;
        enemy_x = 0;
        enemy_y = rand() % width;
        bullet_x = 0;
    }
    if (enemy_x > high)
    {
        enemy_x = 0;
        enemy_y = rand() % width;
    }
    if (speed == 1)
        for (int i = 1; i <= 10000; i++)
        {
            for (int j = 1; j <= 2000; j++)
            {
                speed = 1;
            }
        }
    speed = 0;
    if (speed == 0)
    {
        enemy_x++;
        speed = 1;
    }
}
void updateWithInput()
{
    char input;
    if (kbhit())
    {
        input = getch();
        if (input == 'a')
            position_y--;
        if (input == 's')
            position_x++;
        if (input == 'd')
            position_y++;
        if (input == 'w')
            position_x--;
        if (input == ' ')
        {
            bullet_x = position_x - 1;
            bullet_y = position_y;
        }
    }
}
void show()
{
    gotoxy(0, 0);
    int i, j;
    for (i = 1; i <= high; i++)
    {
        for (j = 1; j <= width; j++)
        {
            if (map[i][j] == 0)
                printf(" ");
            if (map[i][j] == 1)
                printf("*");
            if (map[i][j] == 2)
                printf("#");
            if (map[i][j] == 3)
                printf("~");
            if (map[i][j] == 4)
                printf("|");
            if (map[i][j] == 5)
                printf("|");
        }
        printf("\n");
    }
    printf("\n你的得分:%d\n\n", score);
    printf("操作说明: ASDW分别操作 左下右上四个的移动\n");
    printf("**空格是发出子弹**\n");
}
int main()
{
    starup();
    while (1)
    {
        HideCursor();
        startMap();
        show();
        updateWithoutInput();
        updateWithInput();
    }
    return 0;
}
