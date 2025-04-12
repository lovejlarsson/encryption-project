import nltk
import csv
import os
import random

# Ladda ner wordlist om det är första gången
#nltk.download('words')
from nltk.corpus import words


word_length = 10
output_path = "X:/Programmering/ordlistor/10000ord_10längd"
antal_ord   = 10000

# Filtrera ord med önskad längd
filtered_words = [w for w in words.words() if len(w) == word_length]

# Kontrollera att det finns tillräckligt många ord
if len(filtered_words) == 0:
    print(f"Inga ord hittades med längd {word_length}.")
    exit()
elif antal_ord > len(filtered_words):
    print(f"⚠️ Det finns bara {len(filtered_words)} ord med längd {word_length}. Tar alla.")
    antal_ord = len(filtered_words)

# Random
random_words = random.sample(filtered_words, antal_ord)

with open(output_path, "w", newline='', encoding="utf-8") as csvfile:
    writer = csv.writer(csvfile)
    for word in random_words:
        writer.writerow([word])

print(f"✅ {antal_ord} ord med {word_length} bokstäver sparades till:\n{output_path}")