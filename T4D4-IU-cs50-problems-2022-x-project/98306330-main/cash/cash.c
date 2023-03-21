#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // お客さまに何¢払えばいいのか聞く
    int cents = get_cents();

    // お客様にお渡しする25¢の枚数を計算する
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // お客様にお渡しする10¢の枚数を計算する
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // お客様に渡すべき5¢の枚数を計算する
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    //お客様にお渡しする1¢の枚数を計算する
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // お客さまにお渡しするコインの総数を印刷する
    printf("%i\n", coins);
}

int get_cents(void)
{
    // 入力
    int cents;
    do
    {
        cents = get_int("Change owed:");
    }
    while (0 > cents);
    return cents;
}

int calculate_quarters(int cents)
{
    // 25¢が幾つ必要か
    int quarters;
    quarters = cents / 25;
    return quarters;

}

int calculate_dimes(int cents)
{
    // 10¢が幾つ必要か
    int dimes;
    dimes = cents / 10;
    return dimes;
}

int calculate_nickels(int cents)
{
    // 5¢が幾つ必要か
    int nickels;
    nickels = cents / 5;
    return nickels;
}

int calculate_pennies(int cents)
{
    // 1¢が幾つ必要か
    int pennies;
    pennies = cents / 1;
    return pennies;
}
