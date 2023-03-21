from asyncio.windows_events import NULL
from ctypes.wintypes import tagRECT
from pkgutil import get_importer
from re import T
from tokenize import blank_re
from turtle import width
import pyautogui
import tkinter
from PIL import Image, ImageTk
from tkinter import filedialog

RESIZE_RETIO = 1.5 # 縮小倍率の規定

# ドラッグ開始した時のイベント - - - - - - - - - - - - - - - - - - - - - - - - - - 
def start_point_get(event):
    global start_x, start_y # グローバル変数に書き込みを行なうため宣言

    canvas1.delete("rect1")  # すでに"rect1"タグの図形があれば削除

    # canvas1上に四角形を描画
    canvas1.create_rectangle(event.x,
                             event.y,
                             event.x + 1,
                             event.y + 1,
                             outline="red",
                             tag="rect1")
    # グローバル変数に座標を格納
    start_x, start_y = event.x, event.y

# ドラッグ中のイベント - - - - - - - - - - - - - - - - - - - - - - - - - - 
def rect_drawing(event):

    # ドラッグ中のマウスポインタが領域外に出た時の処理
    if event.x < 0:
        end_x = 0
    else:
        end_x = min(img_resized.width, event.x)
    if event.y < 0:
        end_y = 0
    else:
        end_y = min(img_resized.height, event.y)

    # "rect1"タグの画像を再描画
    canvas1.coords("rect1", start_x, start_y, end_x, end_y)

# ドラッグを離したときのイベント - - - - - - - - - - - - - - - - - - - - - - - - - - 
def release_action(event):

    #グローバル変数の宣言
    global x_position, y_position, tate, yoko

    # "rect1"タグの画像の座標を元の縮尺に戻して取得
    start_x, start_y, end_x, end_y = [
        round(n * RESIZE_RETIO) for n in canvas1.coords("rect1")
    ]

    #グローバル変数に座標を収納
    x_position, y_position = start_x, start_y
    yoko= (end_x - start_x)
    tate = (end_y - start_y)

    # 取得した座標を表示
    pyautogui.alert("start_x : " + str(x_position) + "\n" + "start_y : " +
                   str(y_position) + "\n" + "end_x : " + str(end_x) + "\n" +
                   "end_y : " + str(end_y) + "\n" + "height : " + str(tate) 
                   + "\n" + "width : " +str(yoko))

def screenshot(event):

    x = x_position
    y = y_position
    haba = yoko
    takasa = tate
    sayuu_blank = int(sayuu.get())
    jyouge_blank = int(jyouge.get())

    #取得した範囲のスクショを取る
    before_img = pyautogui.screenshot(region = (x, y, haba, takasa))#x_position is not defined

    #スクショの編集
    after_img = add_blank(before_img, sayuu_blank, jyouge_blank)
    #保存先の決定
    save_path = filedialog.asksaveasfilename(
        title = "名前を付けて保存",
        filetypes = [("PNG", ".png"), ("JPEG", ".jpg"), ("Bitmap", ".bmp"), ("Tiff", ".tif") ], # ファイルフィルタ
        initialdir = "./", # 自分自身のディレクトリ
        defaultextension = "png"
        )
    #スクショの保存
    after_img.save(save_path)

    #アプリの自動終了
    quit()

def add_blank(before_img, sayuu_blank, jyouge_blank):

    #変数の設定
    new_width = yoko + sayuu_blank + sayuu_blank
    new_height = tate + jyouge_blank + jyouge_blank
    color = (255, 255, 255)
    #color色のnew_width x new_heightの画像を生成
    result = Image.new(before_img.mode, (new_width, new_height), color)
    result.paste(before_img, (sayuu_blank, jyouge_blank))
    return result

#メイン処理
if __name__ == "__main__":


    #最初に表示するスクリーンショットの取得
    img = pyautogui.screenshot()


    # スクリーンショットした画像は表示しきれないので画像リサイズ
    img_resized = img.resize(size=(int(img.width / RESIZE_RETIO),
                                   int(img.height / RESIZE_RETIO)),
                             resample=Image.Resampling.BILINEAR)

    root = tkinter.Tk()
    root.title("add blank to screenshot")
    root.attributes("-topmost", True) # tkinterウィンドウを常に最前面に表示
    # Canvasウィジェットの描画
    canvas1 = tkinter.Canvas(root,
                             bg="black",
                             width=img_resized.width,
                             height=img_resized.height)

    # tkinterで表示できるように画像変換
    img_tk = ImageTk.PhotoImage(img_resized)
   
    # Canvasウィジェットに取得した画像を描画
    canvas1.create_image(0, 0, image=img_tk, anchor=tkinter.NW)

    # Canvasウィジェットを配置し、各種イベントを設定
    canvas1.pack()
    canvas1.bind("<ButtonPress-1>", start_point_get)
    canvas1.bind("<Button1-Motion>", rect_drawing)
    canvas1.bind("<ButtonRelease-1>", release_action)

    #画像の下に行間が欲しいので空白生成
    blank1 = tkinter.Label(text="")
    blank1.pack()

    #上下のブランク幅を取得
    Static2 = tkinter.Label(text="上下のブランクの幅")
    Static2.pack()
    jyouge = tkinter.Entry()
    jyouge.insert(tkinter.END, "10")
    jyouge.pack()


    #左右のブランクを取得
    Static3 = tkinter.Label(text="左右のブランクの幅")
    Static3.pack()
    sayuu = tkinter.Entry()
    sayuu.insert(tkinter.END, "10")
    sayuu.pack()

    #スクショを取り修正し保存する
    make_screenshot = tkinter.Button(text="赤枠で囲まれた範囲のスクショを生成")
    make_screenshot.bind("<Button-1>", screenshot)
    make_screenshot.pack()

    root.mainloop()