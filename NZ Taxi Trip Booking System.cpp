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
    // Road Header Image:
    cout << "___________________________________________________" << endl << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "___________________________________________________" << endl << endl;

    cout << "Eligibility Test" << endl << endl;

    // Local Variables:
    string licenceStatus;
    string *licenceStatusPtr = &licenceStatus;
    int drivingExperience;
    int *drivingExperiencePtr = &drivingExperience;
    int vehicleAge;
    int *vehicleAgePtr = &vehicleAge;

    // First check if the user is eligible to become a driver:
    // Check the licence status:
    cout << "What is the status of your licence? Please type: Learners, Restricted, or Full." << endl;
    cout << "Licence: ";
    cin >> *licenceStatusPtr;
    if (*licenceStatusPtr == "Full")
    {
        // Check the user's number of years of driving experience:
        cout << "\nHow many years of driving experience do you have?" << endl;
        cout << "Years of experience: ";
        cin >> *drivingExperiencePtr;
        if (*drivingExperiencePtr >= 2)
        {
            // Check how old the taxi's model is:
            cout << "\nHow old is your vehicle (in years)?" << endl;
            cout << "Vehicle's age: ";
            cin >> *vehicleAgePtr;
            if (*vehicleAgePtr <= 10)
            {
                //
            }
            else
            {
                cout << "Sorry! You are not eligible to drive for us at this time," << endl;
                cout << "but you are welcome to register with a vehicle that is ten or less years old!" << endl << endl;
            }
        }
        else
        {
            cout << "Sorry! You are not eligible to drive for us at this time," << endl;
            cout << "but you are welcome to register once you have been driving for at least 2 years!" << endl << endl;
        }
    }
    else
    {
        cout << "Sorry! You are not eligible to drive for us at this time," << endl;
        cout << "but you are welcome to register once you have your full licence!" << endl << endl;
        // Back to intro screen:
        introFunction();
    }
}

// Admin LogIn Function:
void adminLogIn()
{
    cout << "\n[Insert Admin LogIn Here]" << endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu