#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int steps = get_int("How many steps:");//段数を入力
    while (steps < 1 || steps > 8) //条件を満たさない場合に再度入力させる
    {
        steps = get_int("How many steps?:");
    }
    for (int i = 0; i < steps; i++)
    {
        for (int j = i + 1; j < steps; j++)
        {
            printf(" ");//空白を出力
        }
        for (int k = 8 - i; k < 9; k++)
        {
            printf("#");//#を出力
        }
        printf("\n");
    }
}