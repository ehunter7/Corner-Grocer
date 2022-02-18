import re
import string

collection = {}

def write_to_file():

    file = open("frequency.dat", 'w')

    for key in collection:
        file.write(key + " " + str(collection[key]) + "\n")

    file.close()



def file_data():

    file = open("InputFile.txt")
    
    for line in file:
        stripped_line = line.rstrip()
        if collection.get(stripped_line):
            collection[stripped_line] += 1
        else:
            collection[stripped_line] = 1   

    file.close()

    write_to_file()


def amount_of_each_item():
    
    file_data()

    for key in collection:
        print( key, collection[key] )


def frequency_of_item(userInput):

    file_data()
 
    return collection.get(userInput)


