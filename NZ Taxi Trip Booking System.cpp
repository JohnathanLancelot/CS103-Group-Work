/* Authors: Jade Brown & Johnathan Worrall
 * Assignment: CS103 Group Project
 * Project Name: NZ Taxi Trip Booking System
 */

#include <iostream>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <string>
#include <fstream>
#include <chrono>
#include <thread>
#include <vector>
using namespace std;

// Global Variables:
string roleChoice;
string *roleChoicePtr = &roleChoice;

int noOfNewCustomersToday = 0;
int* noOfNewCustomersTodayPtr = &noOfNewCustomersToday;
int noOfNewCustomersThisWeek = 0;
int* noOfNewCustomersThisWeekPtr = &noOfNewCustomersThisWeek;
int customerAgePtr;
string customerEmailLogIn;
string* driverEmailLogInPtr = &customerEmailLogIn;
string customerPassword;
string* customerPasswordPtr = &customerPassword;
string customerLine;
string* customerLinePtr = &customerLine;
string customerEmailNotFound;
string* customerEmailNotFoundPtr = &customerEmailNotFound;
string newCustomerEmail;
string* newCustomerEmailPtr = &newCustomerEmail;
fstream Data;

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
    cout << endl << endl;
    cout << "                  ---" << endl;
    cout << "                  | |" << endl;
    cout << "                 ....." << endl; 
    cout << "           , ,''  |    ```...___," << endl;
    cout << "    .--  ''  P(___|_______/    (|" << endl;
    cout << "  ( //            |             |" << endl;
    cout << "  ` ._: ' ' :_____|______: ' ' :/" << endl;
    cout << "      '  o  '            '  o  '" << endl;
    cout << "        - -                - - " << endl;
    cout << " _____________________________________________" << endl;
    cout << " ___________Welcome to NZ Taxi~!______________" << endl;
    cout << " _____________________________________________" << endl << endl;
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
            while (*driverAccountAnswerPtr != "Yes" && *    driverAccountAnswerPtr != "No")
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
struct Customer {
    // General Information:
    string fullName;
    string gender;
    string dateOfBirth;
    string nationality;
    string contactNumber;
    string postalAddress;

    // Payment Information:
    string bankName;
    string bankAccountNumber;

    // Account LogIn Information
    string emailAddress;
    string password1;
    string password2;
    string passwordConfirmed;

    // Endorsement Information:
    string endorsementNumber = "P";
    int endorsementExpiry[3] = { 0,0,0 };
};
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
    Customer newCustomer;
    // Eligibility Test Section:
    cout << "\n\n\t\t___________________________________________________" << endl << endl;
    cout << "\t\t---------------------------------------------------" << endl;
    cout << "\t\t___________________________________________________" << endl << endl;

    cout << "\n\t\t\tEligibility Test" << endl << endl << endl;

    // Temporary Structure:
   
    // Check the user's age:
    cout << "\n\t\tHow old are you?" << endl;
    cout << "\t\tAge: ";
    cin >> customerAgePtr;
    if (customerAgePtr > 21)
    {
        // Passed!
        cout << "\n\n\t\tCongratulations! You have passed the eligibility test!" << endl;
        cout << "\t\tYou may now continue to register." << endl;

        // Registration Section:
        cout << "\n\n\n\t\t___________________________________________________" << endl << endl;
        cout << "\t\t---------------------------------------------------" << endl;
        cout << "\t\t___________________________________________________" << endl << endl;

        cout << "\n\t\t\tRegistration" << endl << endl << endl;

        // Fix the spaces causing missed inputs issue:
        cin.ignore();

        // Gather Input:
        cout << "\t\t\t|| General Information ||" << endl << endl;
        cout << "\t\tFull Name: ";
    getline:(cin, newCustomer.fullName);
        cout << "\t\tGender: ";
    getline:(cin, newCustomer.gender);

        cout << "\t\tDate of Birth (dd/mm/yyyy): ";
    getline:(cin, newCustomer.dateOfBirth);
        cout << "\t\tNationality: ";
    getline:(cin, newCustomer.nationality);
        cout << "\t\tContact Number: ";
    getline:(cin, newCustomer.contactNumber);
        cout << "\t\tPostal Address: ";
    getline:(cin, newCustomer.postalAddress);

        cout << "\n\n\n\t\t\t|| Payment Information ||" << endl << endl;
        cout << "\t\tBank Name: ";
    getline:(cin, newCustomer.bankName);
        cout << "\t\tBank Account Number: ";
    getline:(cin, newCustomer.bankAccountNumber);

        cout << "\n\n\n\t\t\t|| Account LogIn Information ||" << endl << endl;
        cout << "\t\tEmail Address: ";
    getline:(cin, newCustomer.emailAddress);
        cout << "\t\tCreate a Password: ";
    getline:(cin, newCustomer.password1);
        cout << "\t\tRe-enter Your Password: ";
    getline:(cin, newCustomer.password2);

        if (newCustomer.password1 == newCustomer.password2)
        {
            newCustomer.passwordConfirmed = newCustomer.password1;
        }
        else
        {
            while (newCustomer.password1 != newCustomer.password2)
            {
                cout << "\n\t\tError. The passwords you have entered do not match." << endl;
                cout << "\t\tPlease try again." << endl << endl << endl;

                cout << "\t\tCreate a Password: ";
                getline(cin, newCustomer.password1);
                cout << "\t\tRe-enter Your Password: ";
                getline(cin, newCustomer.password2);
            }
            // Once they do match, confirm:
            newCustomer.passwordConfirmed = newCustomer.password1;
        }
        // Enter details into the customerData.txt file:
        /*
        customerData.open("customerData.txt", ios::out | ios::app);
        customerData << newCustomer.fullName << endl;
        customerData << newCustomer.gender << endl;
        customerData << newCustomer.dateOfBirth << endl;
        customerData << newCustomer.nationality << endl;
        customerData << newCustomer.contactNumber << endl;
        customerData << newCustomer.postalAddress << endl;
        customerData << newCustomer.licenceNumber << endl;
        customerData << newCustomer.licenceExpiry << endl;
        customerData << newCustomer.drivingExperience << endl;
        customerData << newCustomer.vehicleRegistrationNumber << endl;
        customerData << newCustomer.vehicleModel << endl;
        customerData << newCustomer.wofExpiryDate << endl;
        customerData << newCustomer.bankName << endl;
        customerData << newCustomer.bankAccountNumber << endl;
        customerData << newCustomer.emailAddress << endl;
        customerData << newCustomer.passwordConfirmed << endl;
        customerData << newCustomer.endorsementNumber << endl;
        customerData << newCustomer.endorsementExpiry[0] << endl;
        customerData << newCustomer.endorsementExpiry[1] << endl;
        customerData << newCustomer.endorsementExpiry[2] << endl;
        customerData << "-----End of item-----" << endl;*/

        // Driver LogIn Function:
        void driverLogIn();
        {
            cout << "\n[Insert Driver LogIn Here]" << endl;
        }

        // Driver Registration Function:
        void driverRegistration();
        {
            cout << "\n[Insert Driver Registration Here]" << endl;
        }

        // Admin LogIn Function:
        void adminLogIn();
        {
            cout << "\n[Insert Admin LogIn Here]" << endl;
        }

        // Run program: Ctrl + F5 or Debug > Start Without Debugging menu
        // Debug program: F5 or Debug > Start Debugging menu



    }
}