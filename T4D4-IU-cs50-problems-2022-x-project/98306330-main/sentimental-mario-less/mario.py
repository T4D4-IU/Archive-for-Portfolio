from cs50 import get_int
while True:
    # pythonにはdo-while文が無いのでTrueでループさせ続けて最後に条件式で満たすモノをBreakで外に出してあげる事で擬似的にdo-while文を作る
    steps = get_int("Height:")
    if 1 < steps < 8:
        # 1より大きく8より小さい
        break
    elif steps == 1:
        # 1と同じ
        break
    elif steps == 8:
        # 8と同じ
        break
        # 3つの条件で1以上8以下の数字かどうかを判別
    print(f"please input figure between 1 and 8")
j = 1
for i in range(steps):
    print(" "*(steps-j), end='')
    print("#"*j)
    j += 1