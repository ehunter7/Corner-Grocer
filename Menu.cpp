// ##################################################
// File: Menu.cpp
// Author: Eric Hunter
// Date: February 15, 2022
// Description: Contains functions for Menu class
// ##################################################

#include "Menu.h"

Menu& Menu::Get()
{
	//Static declaration
	static Menu instance;

	return instance;
}

void Menu::Push(const std::string& title)
{
	return Get().IPush(title);
}

void Menu::Push(const std::string& item, void(*callback)())
{
	return Get().IPush(item, callback);
}


void Menu::Push(const std::string& item, void(*callback)(const std::string& pName), const std::string& pName)
{
	return Get().IPush(item, callback, pName);
}


void Menu::DisplayMenu()
{
	return Get().IDisplayMenu();
}

int Menu::GetUserInput()
{
	return Get().IGetUserSelection();
}

void Menu::HandleUserInput(const int& input){
	return Get().IHandleUserInput(input);
}

void Menu::IPush(const std::string& title)
{
	//Declares new struct object
	Item* tmpItem = new Item();

	//Sets the title of the menu item
	tmpItem->m_title = title;

	//Sets the index of the menu item
	tmpItem->m_Index = this->m_Items.size() + 1;

	//Adds the new object to the vector of menu items
	this->m_Items.push_back(*tmpItem);

	//Deletes the allocated memory of the the struct object
	delete tmpItem;
}

void Menu::IPush(const std::string& title, void(*callback)())
{
	//Declares new struct object
	Item* tmpItem = new Item();

	//Sets the title of the menu item
	tmpItem->m_title = title;

	//Sets the callback function
	tmpItem->m_CallbackNoString = callback;

	//Sets the index of the menu item
	tmpItem->m_Index = this->m_Items.size() + 1;

	//Adds the new object to the vector of menu items
	this->m_Items.push_back(*tmpItem);

	//Deletes the allocated memory of the the struct object
	delete tmpItem;
}


void Menu::IPush(const std::string& title, void(*callback)(const std::string& pName), const std::string& pName)
{
	//Declares new struct object
	Item* tmpItem = new Item();

	//Sets the title of the menu item
	tmpItem->m_title = title;

	//Sets the callback function
	tmpItem->m_Callback = callback;

	//Sets the index of the menu item
	tmpItem->m_Index = this->m_Items.size() + 1;

	tmpItem->m_pName = pName;

	//Adds the new object to the vector of menu items
	this->m_Items.push_back(*tmpItem);

	//Deletes the allocated memory of the the struct object
	delete tmpItem;
}


void Menu::IDisplayMenu() const
{
	//Creates a top border of the menu
	std::cout << std::setfill('~') << std::setw(46) << "\n";

	unsigned short i;

	//Iterates through the class vector memebr of struct objects and displays them to the console
	for (i = 0; i < this->m_Items.size(); i++) {

		std::cout << this->m_Items.at(i).m_Index << ": " << this->m_Items.at(i).m_title << std::endl;
	}

	//Promts the user what to enter as a selection
	std::cout << "Enter your selection as a number ";
	
	//informs the user how to enter options of menu items. 
	for (int i = 1; i <= this->m_Items.size(); i++) {
		if (i != this->m_Items.size()) {
			std::cout << i << ", ";
		}
		else {
			std::cout << "or " << i << "." << std::endl;
		}
	}

	//Bottom border
	std::cout << std::setfill('~') << std::setw(46) << "\n";
}

int Menu::IGetUserSelection()
{
	//Variable used to store user input and to validate the input
	int userInput;
	bool validMenuOption = false;

	//While input has not been validated
	while (!validMenuOption) {

		//Try catch to 
		try {

			//Gets user input
			std::cin >> userInput;

			//Checks if input is a valid menu item
			if (userInput < 1 || userInput > this->m_Items.size()) {

				//If input is not a valid option, throw error
				throw std::exception("Invalid entry.");
			}

			//If input is valid, move on
			validMenuOption = true;
		}
		catch (const std::exception& error) {

			// Clear the failed attempt
			std::cin.clear();

			//tmp string used to help clear failed input attempt
			std::string tmp;

			//flush stream
			getline(std::cin, tmp);

			std::cout << error.what() << " Please try again" << std::endl;
		}
	}

	return userInput;
}

void Menu::IHandleUserInput(const int& input) {

	//sets input to 0 basded index
	int index = input - 1;

	//If menu item does not have string function added
	if(m_Items.at(index).m_pName != "") {

		//call functin and pass string as param
		 m_Items.at(index).m_Callback(m_Items.at(index).m_pName);
	}
	else {
		//Otherwise call function that does not take string param 
		m_Items.at(index).m_CallbackNoString();
	}

	
}

