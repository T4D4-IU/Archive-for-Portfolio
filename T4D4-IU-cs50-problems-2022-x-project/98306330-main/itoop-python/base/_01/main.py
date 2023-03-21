def main():
    play(1, 2)


def play(left_hand: int, right_hand: int):
    result = judge(left_hand, right_hand)
    show_result(result)


def judge(left_hand: int, right_hand: int) -> int:
    # 勝敗を判定して結果（1:勝ち, 2:引き分け, 3:負け）を返却しよう
    if left_hand == 0:#gu-
        if right_hand == 0:#gu-
            return 2
        elif right_hand == 1:#thoki
            return 1
        else:#pa-
            return 3
    elif left_hand == 1:#thoki
        if right_hand == 0:#gu-
            return 3
        elif right_hand == 1:#thoki
            return 2
        else:#pa-
            return 1
    else:#pa-
        if right_hand == 0:#gu-
            return 1
        elif right_hand == 1:#thoki
            return 3
        else:#pa-
            return 2


def show_result(result: int):
    # 結果をもとに勝敗を print を使って表示しよう
    if result == 1:
        print("win")
    elif result == 2:
        print("draw")
    else:
        print("lose")
    return


if __name__ == '__main__':
    main()
