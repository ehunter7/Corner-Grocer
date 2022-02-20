
#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>

#include "Menu.h"
using namespace std;

//Function declarations
void DisplayHistogram();
void GetFrequencyOfItem();

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(const string& pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("MyPythonFile");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"MyPythonFile");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"MyPythonFile");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

int main()
{
	//Adds menu options to the Menu object
	Menu::Push("Number of times each item appears", CallProcedure, "amount_of_each_item");
	Menu::Push("Number of times an individual item appears", GetFrequencyOfItem);
	Menu::Push("Generate Histogram", DisplayHistogram);
	Menu::Push("Exit");

	//infinite loop runsuntil user enters 4 to exit program
	while (true) {

		Menu::DisplayMenu();

		//Gets the users menu selection as stores it as input
		int input = Menu::GetUserInput();

		//Border used for readability and seperation
		cout << setw(46) << setfill('~') << "\n";

		//New Line for rewadability
		cout << endl;

		//If user has selected exit then exit
		if (input == 4) break;

		//Takes the users menu input and handles it. 
		Menu::HandleUserInput(input);
	}

	return 0;
}

void GetFrequencyOfItem() {

	//Variable userInput that users entered value 
	string userInput;

	//Shuttle holds the value returned from python code, set to -1 until item is found
	int shuttle = -1;

	//While the item the user is searching for is not found. 
	while (shuttle == -1) {

		//Prompt user to enter value
		cout << "Enter item to search for: ";
		cin >> userInput;

		//Capitalizes the first letter of the entered to match stored data
		userInput[0] = toupper(userInput[0]);

		//Shuttle is set to the number of times item is found in list
		shuttle = callIntFunc("frequency_of_item", userInput);

		//If returned value is -1 item wasnt found
		if (shuttle == -1) {
			cout << "The Item you have searched for is not on the list. ";
			cout << "Please try again." << endl;
		}
	}

	//Prompt to let user know how many times item appears on list
	cout << userInput << " appear on the list " << shuttle << " times." << endl;

	//New line for readability
	cout << endl;
}

void DisplayHistogram() {

	//Calls python function to pull data from file and store as a dictionary
	CallProcedure("file_data");

	//Temperary variables to hold data read from 
	string name;
	int amount;

	string fileName = "frequency.dat";
	
	//Open an input file stream
	ifstream itemList;

	//Opens file passed to the function
	itemList.open(fileName);

	//If statement checks if file has been opened
	if (!itemList.is_open()) {

		cout << fileName << " could not be opened for reading" << endl;

		//Throw statement exits function
		throw exception("Program exiting");
	}
	//If file was opened, proceed with reading from file
	else {

		//While not at end of file
		while (!itemList.fail()) {

			//Get the city name from file
			itemList >> name;

			//Get the city temp from file
			itemList >> amount;

			//Histogram output
			cout << flush << name << setw(15 - name.length()) << setfill(' ')  << " ";
			cout << setw(amount + 1) << setfill('*') << "\n";

		}
	}

	//New Line for readability
	cout << endl;

	//Closes file after reading
	itemList.close();
}


