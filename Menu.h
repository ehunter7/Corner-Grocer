// ##################################################
// File: Menu.h
// Author: Eric Hunter
// Date: February 15, 2022
// Description: Header file for Menu class.
//				Declares the function calls
// ##################################################

#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>

/*
	Brief:
		struct hold the title of the menu item and its index.
*/

struct Item {
	std::string m_title;
	void(*m_Callback)(const std::string& pName);
	void(*m_ExitCallback)(bool& exitCondtion);
	void(*m_CallbackNoString)();
	std::string m_pName;
	int m_Index;
	bool m_exitCondition = NULL;
};

/*
	Brief:
		Menu class used to set up the displayed menu.
		Also gets the users menu selection.

	Future improvements:
		I would like to have the objects store functions
		for each of the menu items so that when a user
		makes a selection, the object would run the function.

	Notes:
		The design of the class is intended to be a singleton design.
*/
class Menu {
public:

	//Deletes copy constructor to not allow class instantiation outside of class. 
	Menu(const Menu&) = delete;

	//Gets a single instance of the class
	static Menu& Get();

	//Static function map to internal functions.

	static void Push(const std::string& title);

	static void Push(const std::string& title, void(*callback)());


	//Maps to IPush
	static void Push(const std::string& title, void(*callback)(const std::string& pName), const std::string& pName);

	//Maps to IDisplayMenu
	static void DisplayMenu();

	//Maps to IGetUserInput
	static int GetUserInput();

	static void HandleUserInput(const int& input);

private:

	//class member
	std::vector<Item> m_Items;

	//Cunstructor in private to not allow class instantiation outside of this class.
	Menu() {};

	//Internal function calls used to clean up fucntion calls in main.

	void IPush(const std::string& title);

	void IPush(const std::string& title, void(*callback)());



	// ################################################################
	// @par Name
	// IPush
	// @purpose
	// Adds struct object Item to the classes vector of menu items
	// @param [in]:
	// Type string which is a reference to to the title
	// @return
	// void
	// @par References
	// none
	// @par Notes
	// The 'I' in the function name is to indicate that it is an internal function
	// ################################################################
	void IPush(const std::string& title, void(*callback)(const std::string& pName), const std::string& pName);


	// ################################################################
	// @par Name
	// IDisplayMenu
	// @purpose
	// Displays the added menu items to the console
	// @param [in]:
	// none
	// @return
	// void
	// @par References
	// none
	// @par Notes
	// The 'I' in the function name is to indicate that it is an internal function
	// ################################################################
	void IDisplayMenu() const;

	// ################################################################
	// @par Name
	// IGetUserSelection
	// @purpose
	// Displays the added menu items to the console
	// @param [in]:
	// none
	// @return
	// type int as the susers menu selection
	// @par References
	// none
	// @par Notes
	// The 'I' in the function name is to indicate that it is an internal function
	// ################################################################
	int IGetUserSelection();

	void IHandleUserInput(const int& input);
};

