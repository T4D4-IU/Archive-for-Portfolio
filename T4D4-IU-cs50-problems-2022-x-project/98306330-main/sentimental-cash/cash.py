from cs50 import get_float

# decline
change = 0
coins = 0

while change <= 0:
    change = get_float("Change owed:")
    cents = round(change * 100)
    #  input

while cents > 0:
    if cents >= 25:
        cents = cents - 25
        coins = coins + 1
        # ここで1回先頭へ
    elif cents >= 10:
        cents = cents - 10
        coins = coins + 1
        # ここで1回先頭へ
    elif cents >= 5:
        cents = cents - 5
        coins = coins + 1
        # ここで1回先頭へ
    elif cents >= 1:
        cents = cents - 1
        coins = coins + 1
        # ここで1回先頭へ

print(coins)