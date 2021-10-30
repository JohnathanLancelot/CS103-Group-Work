/* Authors: Jade Brown & Johnathan Worrall
 * Assignment: CS103 Group Project
 * Project Name: NZ Taxi Trip Booking System
 */

#include <iostream>
#include <cmath>
#include <string>
using namespace std;

// Global Variables:
string roleChoice;
string *roleChoicePtr = &roleChoice;

// Functions:
void introFunction();
string roleChoiceFunction();
void customerLogIn();
void customerRegistration();
void driverLogIn();
void driverRegistration();
void adminLogIn();

int main()
{
    // Start the program with the intro:
    introFunction();
}

void introFunction()
{
    /* TO ADD (JADE):
     * - Some kind of text art with a taxi / road theme (Johnathan happy to help with this part)
     * - Business Title
     * - Terms and Conditions
     * - More professional confirmation of the user category (role choice function) and handling of unexpected inputs
     * - Customer LogIn
     * - Customer Registration
     * 
     * TO ADD (JOHNATHAN):
     * - Driver LogIn
     * - Driver Registration
     * - Admin LogIn
     */

    // Placeholder for the intro screen:
    cout << "[intro screen]" << endl << endl;

    // Use a function to determine the user's role:
    roleChoiceFunction();

    if (*roleChoicePtr == "C")
    {
        // Check if they already have an account or if they need to register:
        cout << "\nDo you have an account? Yes or No : ";
        string customerAccountAnswer;
        string *customerAccountAnswerPtr = &customerAccountAnswer;
        cin >> *customerAccountAnswerPtr;
        if (*customerAccountAnswerPtr == "Yes")
        {
            customerLogIn();
        }
        else if (*customerAccountAnswerPtr == "No")
        {
            customerRegistration();
        }
        else
        {
            while (*customerAccountAnswerPtr != "Yes" && *customerAccountAnswerPtr != "No")
            {
                cout << "Sorry. You have entered an invalid option. Please try again." << endl;
                cout << "\nDo you have an account? Yes or No : ";
                cin >> *customerAccountAnswerPtr;
            }
            if (*customerAccountAnswerPtr == "Yes")
            {
                customerLogIn();
            }
            else if (*customerAccountAnswerPtr == "No")
            {
                customerRegistration();
            }
        }
    }
    else if (*roleChoicePtr == "D")
    {
        // Check if they already have an account or if they need to register:
        cout << "\nDo you have an account? Yes or No : ";
        string driverAccountAnswer;
        string* driverAccountAnswerPtr = &driverAccountAnswer;
        cin >> *driverAccountAnswerPtr;
        if (*driverAccountAnswerPtr == "Yes")
        {
            driverLogIn();
        }
        else if (*driverAccountAnswerPtr == "No")
        {
            driverRegistration();
        }
        else
        {
            while (*driverAccountAnswerPtr != "Yes" && *driverAccountAnswerPtr != "No")
            {
                cout << "Sorry. You have entered an invalid option. Please try again." << endl;
                cout << "\nDo you have an account? Yes or No : ";
                cin >> *driverAccountAnswerPtr;
            }
            if (*driverAccountAnswerPtr == "Yes")
            {
                driverLogIn();
            }
            else if (*driverAccountAnswerPtr == "No")
            {
                driverRegistration();
            }
        }
    }
    else if (*roleChoicePtr == "A")
    {
        adminLogIn();
    }
}

// Role Choice Function:
string roleChoiceFunction()
{
    // Input:
    cout << "Are you a customer (C), a driver (D) or an admin (A)? ";
    cin >> *roleChoicePtr;

    // Action:
    if (*roleChoicePtr == "C" || *roleChoicePtr == "D" || *roleChoicePtr == "A")
    {
        return *roleChoicePtr;
    }
    else
    {
        // TO DO (JADE): Possibly change this to proper error handling as covered in week 13
        while (*roleChoicePtr != "C" && *roleChoicePtr != "D" && *roleChoicePtr != "A")
        {
            cout << "Sorry. You have entered an invalid option. Please try again." << endl;
            roleChoiceFunction();
        }
    }
}

// Customer LogIn Function:
void customerLogIn()
{
    cout << "\n[Insert Customer LogIn Here]" << endl;
}

// Customer Registration Function:
void customerRegistration()
{
    cout << "\n[Insert Customer Registration Here]" << endl;
}

// Driver LogIn Function:
void driverLogIn()
{
    cout << "\n[Insert Driver LogIn Here]" << endl;
}

// Driver Registration Function:
void driverRegistration()
{
    cout << "\n[Insert Driver Registration Here]" << endl;
}

// Admin LogIn Function:
void adminLogIn()
{
    cout << "\n[Insert Admin LogIn Here]" << endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu