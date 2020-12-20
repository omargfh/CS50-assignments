string = input("Text: ")
words = string.split()
letters, wordc, sentences = 0, 0, 0
for word in words:
    wordc += 1
    if word.endswith(".") or word.endswith("?") or word.endswith("!"):
        sentences += 1
for letter in string:
    if letter.isalpha():
        letters += 1
L = letters / wordc * 100
S = sentences / wordc * 100
index = 0.0588 * L - 0.296 * S - 15.8
print("Grade", round(index) if index < 16 and index >= 1 else "Before Grade 1" if index < 1 else "16+")