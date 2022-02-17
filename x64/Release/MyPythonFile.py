import re
import string


def printsomething():
    print("Hello from python!")

def PrintMe(v):
    print("You sent me: " + v)
    return 100;

def SquareValue(v):
    return v * v


collection = {}

def AmountOfEachItem():
    
    file = open("InputFile.txt")
    
    for line in file:
        found = 0
        for item in collection:
            if line == item["name"]:
                item["amount"] += 1
                found = 1
                break

        if found != 1:
            collection.append(line, 1)
    
    for item in collection:
        for key,value in dictionary.items():
            print(key, ':', value)
