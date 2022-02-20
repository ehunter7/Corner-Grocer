// ##################################################
// File: Menu.h
// Author: Eric Hunter
// Date: February 18, 2022
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
		struct hold menu list item properties.
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
		Functions are now stored but i would like to have it handle exiting the program

	Notes:
		The design of the class is intended to be a singleton design.
*/
class Menu {
public:

	//Deletes copy constructor to not allow class instantiation outside of class. 
	Menu(const Menu&) = delete;

	//Gets a single instance of the class
	static Menu& Get();

	//Static function map to internal functions. Internal functions are prefixed with an 'I'
	//Maps to functions that are prefixed with an 'I'

	static void Push(const std::string& title);

	static void Push(const std::string& title, void(*callback)());

	static void Push(const std::string& title, void(*callback)(const std::string& pName), const std::string& pName);

	static void DisplayMenu();

	static int GetUserInput();

	static void HandleUserInput(const int& input);

private:

	//class member
	std::vector<Item> m_Items;

	//Cunstructor in private to not allow class instantiation outside of this class.
	Menu() {};

	//Internal function calls used to clean up fucntion calls in main.

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
	void IPush(const std::string& title);


	// ################################################################
	// @par Name
	// IPush
	// @purpose
	// Adds struct object Item to the classes vector of menu items
	// @param [in]:
	// Type string which is a reference to to the title
	// @param [in]:
	// void callback function to call when menu option is selected
	// @return
	// void
	// @par References
	// none
	// @par Notes
	// The 'I' in the function name is to indicate that it is an internal function
	// ################################################################
	void IPush(const std::string& title, void(*callback)());


	// ################################################################
	// @par Name
	// IPush
	// @purpose
	// Adds struct object Item to the classes vector of menu items
	// @param [in]:
	// Type string which is a reference to to the title
	// @param [in]:
	// void callback function to call when menu option is selected
	// @param [in]:
	// String to be passed to callback if menu option is selected
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


	// ################################################################
	// @par Name
	// IHandleUserInput
	// @purpose
	// Takes the users input and calls the function associated with that menu item
	// @param [in]:
	// const int type of the userinput passed as reference
	// @return
	// type int as the susers menu selection
	// @par References
	// none
	// @par Notes
	// The 'I' in the function name is to indicate that it is an internal function
	// ################################################################
	void IHandleUserInput(const int& input);
};

