/* Authors: Jade Brown & Johnathan Worrall
 * Assignment: CS103 Group Project
 * Project Name: NZ Taxi Trip Booking System
 */

#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
using namespace std;

// Global Variables:
string roleChoice;
string *roleChoicePtr = &roleChoice;
fstream driverData;

// Global Variables For Driver Registration / LogIn:
string licenceStatus;
string *licenceStatusPtr = &licenceStatus;
int drivingExperience;
int *drivingExperiencePtr = &drivingExperience;
int vehicleAge;
int *vehicleAgePtr = &vehicleAge;
int driverAge;
int *driverAgePtr = &driverAge;

// Structures:
struct driver
{
    // General Information:
    string fullName;
    string gender;
    string dateOfBirth;
    string nationality;
    string contactNumber;
    string postalAddress;

    // Driving / Vehicle Details:
    string licenceNumber;
    string licenceExpiry;
    int drivingExperience = 0;
    string vehicleRegistrationNumber;
    string vehicleModel;
    string wofExpiryDate;

    // Payment Information:
    string bankName;
    string bankAccountNumber;

    // Account LogIn Information
    string emailAddress;
    string password1;
    string password2;
    string passwordConfirmed;

    // Endorsement Information:
    int endorsementNumber = 0;
    string endorsementExpiry;
};

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
    // Eligibility Test Section:
    cout << "___________________________________________________" << endl << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "___________________________________________________" << endl << endl;

    cout << "Eligibility Test" << endl << endl;

    // Temporary Structure:
    driver newDriver;

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
                // Check the user's age:
                cout << "\nHow old are you?" << endl;
                cout << "Age: ";
                cin >> *driverAgePtr;
                if (*driverAgePtr > 21)
                {
                    // Passed!
                    cout << "\nCongratulations! You have passed the eligibility test!" << endl;
                    cout << "You may now continue to register." << endl;

                    // Registration Section:
                    cout << "___________________________________________________" << endl << endl;
                    cout << "---------------------------------------------------" << endl;
                    cout << "___________________________________________________" << endl << endl;

                    cout << "Registration" << endl << endl;

                    // Fix the spaces causing missed inputs issue:
                    cin.ignore();

                    // Gather Input:
                    cout << "|| General Information ||" << endl << endl;
                    cout << "Full Name: ";
                    getline(cin, newDriver.fullName);
                    cout << "Gender: ";
                    getline(cin, newDriver.gender);
                    cout << "Date of Birth (dd/mm/yyyy): ";
                    getline(cin, newDriver.dateOfBirth);
                    cout << "Nationality: ";
                    getline(cin, newDriver.nationality);
                    cout << "Contact Number: ";
                    getline(cin, newDriver.contactNumber);
                    cout << "Postal Address: ";
                    getline(cin, newDriver.postalAddress);

                    cout << "\n|| Driving & Vehicle Details ||" << endl << endl;
                    cout << "Licence Number: ";
                    getline(cin, newDriver.licenceNumber);
                    cout << "Licence Expiry Date (dd/mm/yyyy): ";
                    getline(cin, newDriver.licenceExpiry);
                    newDriver.drivingExperience = *drivingExperiencePtr;
                    cout << "Years of Driving Experience: " << newDriver.drivingExperience << endl;
                    cout << "Vehicle Registration Number: ";
                    getline(cin, newDriver.vehicleRegistrationNumber);
                    cout << "Vehicle Model: ";
                    getline(cin, newDriver.vehicleModel);
                    cout << "WOF Expiry Date: ";
                    getline(cin, newDriver.wofExpiryDate);

                    cout << "\n|| Payment Information ||" << endl << endl;
                    cout << "Bank Name: ";
                    getline(cin, newDriver.bankName);
                    cout << "Bank Account Number: ";
                    getline(cin, newDriver.bankAccountNumber);

                    cout << "\n|| Account LogIn Information ||" << endl << endl;
                    cout << "Email Address: ";
                    getline(cin, newDriver.emailAddress);
                    cout << "Create a Password: ";
                    getline(cin, newDriver.password1);
                    cout << "Re-enter Your Password: ";
                    getline(cin, newDriver.password2);

                    // Make sure both passwords are the same before confirming:
                    if (newDriver.password1 == newDriver.password2)
                    {
                        newDriver.passwordConfirmed = newDriver.password1;
                    }
                    else
                    {
                        while (newDriver.password1 != newDriver.password2)
                        {
                            cout << "\nError. The passwords you have entered do not match." << endl;
                            cout << "Please try again." << endl << endl;

                            cout << "Create a Password: ";
                            getline(cin, newDriver.password1);
                            cout << "Re-enter Your Password: ";
                            getline(cin, newDriver.password2);
                        }
                        // Once they do match, confirm:
                        newDriver.passwordConfirmed = newDriver.password1;
                    }

                    // Endorsement Section:
                    cout << endl << endl;
                    cout << "___________________________________________________" << endl << endl;
                    cout << "---------------------------------------------------" << endl;
                    cout << "___________________________________________________" << endl << endl;

                    cout << "Endorsement" << endl << endl;

                    // Assign an endorsement number:
                    newDriver.endorsementNumber = 12789;
                    cout << "Your Endorsement Number: " << newDriver.endorsementNumber << endl;

                    // Generate an endorsement expiry date:
                    newDriver.endorsementExpiry = "31/10/2023";
                    cout << "Your Endorsement Expiry Date: " << newDriver.endorsementExpiry << endl << endl;

                    // Enter details into the driverData.txt file:
                    driverData.open("driverData.txt", ios::out | ios::app);
                    driverData << newDriver.fullName << endl;
                    driverData << newDriver.gender << endl;
                    driverData << newDriver.dateOfBirth << endl;
                    driverData << newDriver.nationality << endl;
                    driverData << newDriver.contactNumber << endl;
                    driverData << newDriver.postalAddress << endl;
                    driverData << newDriver.licenceNumber << endl;
                    driverData << newDriver.licenceExpiry << endl;
                    driverData << newDriver.drivingExperience << endl;
                    driverData << newDriver.vehicleRegistrationNumber << endl;
                    driverData << newDriver.vehicleModel << endl;
                    driverData << newDriver.wofExpiryDate << endl;
                    driverData << newDriver.bankName << endl;
                    driverData << newDriver.bankAccountNumber << endl;
                    driverData << newDriver.emailAddress << endl;
                    driverData << newDriver.passwordConfirmed << endl;
                    driverData << newDriver.endorsementNumber << endl;
                    driverData << newDriver.endorsementExpiry << endl;
                    driverData << "-----End of item-----" << endl;

                    // Close the file:
                    driverData.close();
                }
                else
                {
                    cout << "\nSorry! You are not eligible to drive for us at this time." << endl;
                    cout << "but you are welcome to register once you are over 21 years old!" << endl << endl;
                    // Back to intro screen:
                    introFunction();
                }
            }
            else
            {
                cout << "\nSorry! You are not eligible to drive for us at this time," << endl;
                cout << "but you are welcome to register with a vehicle that is ten or less years old!" << endl << endl;
                // Back to intro screen:
                introFunction();
            }
        }
        else
        {
            cout << "\nSorry! You are not eligible to drive for us at this time," << endl;
            cout << "but you are welcome to register once you have been driving for at least 2 years!" << endl << endl;
            // Back to intro screen:
            introFunction();
        }
    }
    else
    {
        cout << "\nSorry! You are not eligible to drive for us at this time," << endl;
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