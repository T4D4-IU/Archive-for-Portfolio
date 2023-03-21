from cs50 import get_string
import string

text = get_string("Text:")

letters = 0
# letters=文字数
words = 1
# words=単語数
sentences = 0
# sentences=文章数

for letter in text:
    if letter == "!" or letter == "?" or letter == ".":
        sentences += 1
    elif letter in string.punctuation:
        continue
    elif letter in string.whitespace:
        words += 1
    else:
        letters += 1
# ここまででText内に含まれる文字数、単語数、文章数を算出する
W = words / 100
L = letters / W
S = sentences / W
index = round((0.0588 * L) - (0.296 * S) - 15.8)
# 100文字あたりの文字数、単語数、文章数を算出しindexを求める

if index > 16:
    print("Grade 16+")
elif index < 1:
    print("Before Grade 1")
else:
    print(f"Grade {index}")