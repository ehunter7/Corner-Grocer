# ##################################################
# File: MyPythonFile.py
# Author: Eric Hunter
# Date: February 18, 2022
# ##################################################
import re
import string

#Declaration of a dictionary to hold data from file
#set globally to be used in all functions
COLLECTION = {}


def write_to_file():

    #Opens the file to write to
    file = open("frequency.dat", 'w')

    #Iterates through data in dictionary and writes it to file
    for key in COLLECTION:
        file.write(key + " " + str(COLLECTION[key]) + "\n")

    #Closes file once done
    file.close()


def file_data():

    #Opens the file to read from
    file = open("InputFile.txt")
    
    #Reads each item in list individually
    for line in file:

        #removes the new line character
        stripped_line = line.rstrip()

        #If item is found in collection increment count
        if COLLECTION.get(stripped_line):
            COLLECTION[stripped_line] += 1
        else:
            #otherwise add item to dictionary and add value
            COLLECTION[stripped_line] = 1   

    #Closes file to avoid curruption
    file.close()

    #Writes data to file
    write_to_file()


def amount_of_each_item():
    
    #populates COLLECTION dictionary with data from file
    file_data()

    #Iterates through dictionary and prints the name of the item and the amount of times it showed up in list
    for key in COLLECTION:
        print( key, COLLECTION[key] )

    #new line for readability
    print("\n")


def frequency_of_item(userInput):

    #populates COLLECTION dictionary with data from file
    file_data()

    #gets amount of specific item in list
    if COLLECTION.get(userInput):
        return COLLECTION.get(userInput)
    else:
        #if item is not found  return -1
        return -1

    


