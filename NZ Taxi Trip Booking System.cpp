/* Authors: Jade Brown & Johnathan Worrall
 * Assignment: CS103 Group Project
 * Project Name: NZ Taxi Trip Booking System
 */

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
#include <fstream>
#include <chrono>
#include <thread>
using namespace std;

// Global Variables:
string roleChoice;
string *roleChoicePtr = &roleChoice;

// Global Variables For Driver Registration / LogIn:
fstream driverData;
string licenceStatus;
string *licenceStatusPtr = &licenceStatus;
string driverEmailLogIn;
string *driverEmailLogInPtr = &driverEmailLogIn;
string driverPassword;
string *driverPasswordPtr = &driverPassword;
string driverLine;
string *driverLinePtr = &driverLine;
string driverEmailNotFound;
string *driverEmailNotFoundPtr = &driverEmailNotFound;
int drivingExperience;
int *drivingExperiencePtr = &drivingExperience;
int vehicleAge;
int *vehicleAgePtr = &vehicleAge;
int driverAge;
int *driverAgePtr = &driverAge;
int driverLinesCounter = 1;
int *driverLinesCounterPtr = &driverLinesCounter;
int driverEmailLine;
int *driverEmailLinePtr = &driverEmailLine;
int pLongevity;
int *pLongevityPtr = &pLongevity;
int pYearToCheck;
int *pYearToCheckPtr = &pYearToCheck;
int driverLogInAttempts = 0;
int *driverLogInAttemptsPtr = &driverLogInAttempts;
bool pLeap;
bool *pLeapPtr = &pLeap;

// Structures:
struct Driver
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
    string endorsementNumber = "P";
    int endorsementExpiry[3] = {0,0,0};
};

// Functions:
void introFunction();
string roleChoiceFunction();
void customerLogIn();
void customerRegistration();
void driverLogIn();
void driverRegistration();
void driverScreen();
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
    // Header Section:
    cout << "___________________________________________________" << endl << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "___________________________________________________" << endl << endl;

    cout << "Driver LogIn" << endl << endl;

    // Fix the missed inputs issue:
    cin.ignore();

    // Obtain the login details:
    cout << "Please enter your email address: ";
    getline(cin, *driverEmailLogInPtr);
    cout << "Please enter your password: ";
    getline(cin, *driverPasswordPtr);

    // Open and search driverData.txt for these details:
    driverData.open("driverData.txt", ios::in);
    // Search for the email address:
    while (getline(driverData, driverLine))
    {
        if (driverLine == *driverEmailLogInPtr)
        {
            // If you find the email address, record how far down the data file it is:
            *driverEmailLinePtr = driverLinesCounter;
        }
        // The confirmed password is located 1 line down from the email address:
        else if (*driverEmailLinePtr != 0 && driverLinesCounter == (*driverEmailLinePtr + 1))
        {
            // Check if the password entered is incorrect:
            while (*driverPasswordPtr != driverLine)
            {
                driverLogInAttemptsPtr++;
                // Check if the user has used up all their attempts:
                if (*driverLogInAttemptsPtr >= 3)
                {
                    // Reset login attempts and make the user wait 10 seconds:
                    *driverLogInAttemptsPtr = 0;
                    cout << "\nSorry. Incorrect password! Please try again after 10 seconds." << endl;

                    // Create a timer for 1 minute:
                    using namespace std::chrono_literals;
                    std::cout << "Waiting...\n" << std::flush;
                    auto start = std::chrono::high_resolution_clock::now();
                    std::this_thread::sleep_for(10000ms);
                    auto end = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double, std::milli> elapsed = end - start;

                    // After the timer is done, let them try again:
                    cout << "\n\nPlease enter your password: ";
                    getline(cin, *driverPasswordPtr);
                }
                /* If the password entered is incorrect, tell the user this,
                 * as well as how many attempts they have left to make:
                 */
                cout << "\nSorry. Incorrect password! Please try again." << endl;
                cout << "Please enter your password: ";
                getline(cin, *driverPasswordPtr);
            }
            /* Once the password is correct...
             * Reset the lines being read to zero and close the file:
             */
            driverLinesCounter = 0;
            driverData.close();

            // Tell the user they have successfully logged in, and take them to the Driver Screen:
            cout << "\nLog in successful!" << endl;
            driverScreen();
        }
        // Count the lines being read:
        driverLinesCounter++;
    }
    // If, after searching through the whole file, the email address entered is not found:
    if (*driverEmailLinePtr == NULL)
    {
        driverData.close();
        cout << "\nSorry. That email address was not found. Do you want to register (type: register)" << endl;
        cout << "or return to the home screen (type: home)? ";
        cin >> *driverEmailNotFoundPtr;

        // Make sure the input is valid:
        while (*driverEmailNotFoundPtr != "register" && *driverEmailNotFoundPtr != "home" && *driverEmailNotFoundPtr != "Register" && *driverEmailNotFoundPtr != "Home")
        {
            cout << "\nSorry. Invalid input. Please type register or home: ";
            cin >> *driverEmailNotFoundPtr;
        }

        // Act on valid input:
        if (*driverEmailNotFoundPtr == "register" || *driverEmailNotFoundPtr == "Register")
        {
            driverRegistration();
        }
        else if (*driverEmailNotFoundPtr == "home" || *driverEmailNotFoundPtr == "Home")
        {
            introFunction();
        }
    }
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
    Driver newDriver;

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
                    cout << "Your Endorsement Number: " << newDriver.endorsementNumber << endl;

                    // Ask if the user if they want a 1 year P endorsement or a 5 year one:
                    cout << "\nDo you want this endorsement to last 1 year or 5 years?" << endl;
                    cout << "Longevity of P Endorsement: ";
                    cin >> *pLongevityPtr;

                    // Make sure P Logevity is 1 or 5:
                    while (*pLongevityPtr != 1 && *pLongevityPtr != 5)
                    {
                        cout << "\nSorry. You have entered an invalid option. Please enter 1 or 5." << endl;
                        cout << "Longevity of P Endorsement: ";
                        cin >> *pLongevityPtr;
                    }

                    /* Generate an endorsement expiry date...
                     * First by checking the current date:
                     */
                    time_t now = time(0);
                    struct  tm* dt = localtime(&now);

                    /* Check if the current month is february, 
                     * and if so, check if next year or the year in 5 years will be a leap year :
                     */
                    // Check if we're looking at next year, or the year in 5 years' time:
                    if (*pLongevityPtr == 1)
                    {
                        *pYearToCheckPtr = (dt->tm_year + 1900) + 1;
                    }
                    else if (*pLongevityPtr == 5)
                    {
                        *pYearToCheckPtr = (dt->tm_year + 1900) + 5;
                    }
                    // Check if the year is divisible by 4:
                    if (*pYearToCheckPtr % 4 == 0)
                    {
                        // Check if the year is divisible by 100:
                        if (*pYearToCheckPtr % 100 == 0)
                        {
                            // Check if the year is divisible by 400:
                            if (*pYearToCheckPtr % 400 == 0)
                            {
                                *pLeapPtr = true;
                            }
                            else
                            {
                                *pLeapPtr = false;
                            }
                        }
                        else
                        {
                            *pLeapPtr = true;
                        }
                    }
                    else
                    {
                        *pLeapPtr = false;
                    }

                    /* Determine what the expiry day should be.
                     * If it is currently the 29th of February, and the expiry year is not a leap year,
                     * make the expiry day the first day of the following month. 
                     */
                    if (*pLeapPtr == false && (dt->tm_mon + 1) == 2 && dt->tm_mday == 29)
                    {
                        newDriver.endorsementExpiry[0] = 1; // 1st
                        newDriver.endorsementExpiry[1] = 3; // March
                    }
                    // Otherwise leave the day and month of expiry the same as the current day and month:
                    else
                    {
                        newDriver.endorsementExpiry[0] = dt->tm_mday;
                        newDriver.endorsementExpiry[1] = dt->tm_mon + 1;
                    }
                    newDriver.endorsementExpiry[2] = *pYearToCheckPtr;

                    // Display the expiry date:
                    cout << "\nYour Endorsement Expiry Date (dd/mm/yyyy) is: " << newDriver.endorsementExpiry[0] << "/" << newDriver.endorsementExpiry[1] << "/" << newDriver.endorsementExpiry[2] << endl << endl;

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
                    driverData << newDriver.endorsementExpiry[0] << endl;
                    driverData << newDriver.endorsementExpiry[1] << endl;
                    driverData << newDriver.endorsementExpiry[2] << endl;
                    driverData << "-----End of item-----" << endl;

                    // Close the file:
                    driverData.close();

                    // Take the user to the driver screen after registering:
                    driverScreen();
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

// Driver Logged In Screen Function:
void driverScreen()
{
    cout << "\n[Insert Driver Screen Here]" << endl;
}

// Admin LogIn Function:
void adminLogIn()
{
    cout << "\n[Insert Admin LogIn Here]" << endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu