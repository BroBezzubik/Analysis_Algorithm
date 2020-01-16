"""
    Выделить все слова с уменьшительно-ласкательныи суффиксами
"""

import re
import typing

#(?:ек|ик|ец|ок|иц|ушк|ышк|очк|урк|чик|к|)

def findWords(text):
    regexp = r"\b[а-яА-ЯёЁ]+(?:ек|ик|ец|ок|иц|ушк|ышк|очк|урк|чик|к)[а-яА-ЯёЁ]*\b"
    m = re.findall(regexp, text)
    print(m)

def get_state(letter, state):
    """
    :param letter: - symbol in string
    :param state: - previos state
    :return: - current state
    """

    # States of automat
    # е и о ц к ы ш у р ч Е \n
    states = [
        [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
        [7, 7, 3, 1, 8, 4, 1, 5, 1, 2, 1],
        [1, 6, 1, 1, 1, 1, 1, 1, 1, 1, 1],
        [1, 1, 1, 1, 8, 1, 1, 1, 1, 6, 1],
        [1, 1, 1, 1, 1, 1, 6, 1, 1, 1, 1],
        [1, 1, 1, 1, 1, 1, 6, 1, 6, 1, 1],
        [1, 1, 1, 1, 8, 1, 1, 1, 1, 1, 1],
        [1, 1, 1, 8, 8, 1, 1, 1, 1, 1, 1],
        [8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8],
    ]

    choice = 0
    suffix_letters = "еиоцкышурче"
    flag = suffix_letters.find(letter)

    if flag:
        choice = flag
    else: choice = 0


    return states[state][choice]



def stateMachine(text : str):
    word_array = text.split(' ')
    buf = []
    for word in word_array:
        pos = 0
        state = 0

        while pos < len(word):
            letter = word[pos].lower()
            state = get_state(letter, state)
            pos += 1

        if state == 8:
            buf.append(word)

    print(buf)
    return buf





def main():
    text = """Котик мурлыкал от того, что его гладили по брюшку. Рыбка. Дочка, Доча, Девочка, Женщина"""
    findWords(text)
    stateMachine(text)


if __name__ == '__main__':
    main()