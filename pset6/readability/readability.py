import cs50
from sys import argv
# 1-Letters, 2-words, 3- sentences

MIN_LEVEL = 0
MAX_LEVEL = 16


def main():
    # get user input
    text = input("Text:")
    # count words
    text_words = Readability(text)
    text_words = text_words.count_words(text)
    #print(f"text_words {text_words}")
    # count letters
    text_char = Readability(text)
    text_char = text_char.count_letters(text)
    #print(f"text_char {text_char}")
    # count sentences
    text_sentence = Readability(text)
    text_sentence = text_sentence.count_sentence(text)
    #print(f"text_sentence {text_sentence}")
    # Coleman-Liau index
    text_level = Readability(text)
    text_level = text_level.implement_Coleman_index(text_char, text_words, text_sentence)
    #print(f"text_level {text_level}")
    # Find level
    get_readability_level(text_level)
    
    
def get_readability_level(text_level):
    if text_level >= MAX_LEVEL:
        print("Grade 16+")
    elif text_level < MAX_LEVEL and text_level > MIN_LEVEL:
        print(f"Grade {text_level}")
    else:
        print("Before Grade 1")
        
        
class Readability():
    
    def __init__(self, text):
        self.text = text
    # count num of words
    
    def count_words(self, text):
        counter = 0
        for words in text:
            if words.isspace():
                counter += 1
        return counter + 1
        
    # count num of characters in a sentence
    
    def count_letters(self, text):
        counter = 0
        for char in text:
            if char.isalpha():
                counter += 1
        return counter
    
    def count_sentence(self, text):
        counter = 0
        forbidden_list = ['.', '!', '?']
        for char in text:
            if char in forbidden_list:
                counter += 1
        return counter
        
    def implement_Coleman_index(self, letters, words, sentences):
        # find the average number of letters text
        L = ((letters / words) * 100)
        # find the average number of sentences text
        S = ((sentences / words) * 100)
        index = 0.0588 * L - 0.296 * S - 15.8
        return round(index)
        
        
if __name__ == "__main__":
    main()