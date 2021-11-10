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
#include <vector>
using namespace std;

// Global Variables:
fstream tripData;
string roleChoice;
string *roleChoicePtr = &roleChoice;

// Global Variables For Customer Screen:
double costPerKm = 2.60;
double *costPerKmPtr = &costPerKm;
double costPerHourWaiting = 50.00;
double *costPerHourWaitingPtr = &costPerHourWaiting;
double baseFare = 3.50;
double *baseFarePtr = &baseFare;
double airportCBDFixedFare = 63.00;
double *airportCBDFixedFarePtr = &airportCBDFixedFare;
double estimateDistance;
double *estimateDistancePtr = &estimateDistance;
int customerScreenMenuOption;
int *customerScreenMenuOptionPtr = &customerScreenMenuOption;
string estimateStart;
string *estimateStartPtr = &estimateStart;
string estimateDestination;
string *estimateDestinationPtr = &estimateDestination;
string pauseCharacter;
string *pauseCharacterPtr = &pauseCharacter;

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
bool pLeap;
bool *pLeapPtr = &pLeap;

// Global Variables For Driver Screen:
fstream driverActivityData;
string driverActivityLine;
string *driverActivityLinePtr = &driverActivityLine;
int driverActivityLinesCounter = 0;
int *driverActivityLinesCounterPtr = &driverActivityLinesCounter;
int tripToClaim;
int *tripToClaimPtr = &tripToClaim;
bool dateValidation1;
bool *dateValidation1Ptr = &dateValidation1;
bool dateValidation2;
bool *dateValidation2Ptr = &dateValidation2;
bool dateValidation3;
bool *dateValidation3Ptr = &dateValidation3;

// Global Variables For Admin LogIn:
fstream adminData;
string adminEmailAddress = "admin@nztaxitrip.com";
string *adminEmailAddressPtr = &adminEmailAddress;
string adminPassword = "toot-for-taxi";
string *adminPasswordPtr = &adminPassword;
string adminLine;
string *adminLinePtr = &adminLine;
string adminEmailNotFound;
string *adminEmailNotFoundPtr = &adminEmailNotFound;
int adminEmailLine;
int *adminEmailLinePtr = &adminEmailLine;
int adminLinesCounter = 1;
int *adminLinesCounterPtr = &adminLinesCounter;
int adminLogInAttempts = 0;

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

// Driver Activity Struct / Claimed Trips:
struct ClaimedTrips
{
    string emailAddress;
    int day = 0;
    int month = 0;
    int year = 0;
    double cost = 0;
    bool validDate1 = false;
    bool validDate2 = false;
    bool validDate3 = false;
    int emailLine;
};

// PLACEHOLDER TRIP BOOKING STRUCT:
struct Trips
{
    int tripNumber = 0;
    string customerName;
    string customerContactNumber;
    string startingPlace;
    string destination;
    int tripDate[3] = { 0,0,0 };
    string time;
    bool available = true;
    Trips *nextPosition;

    /* This will help us only print the trips booked
     * for the present or future.
     */
    bool past = false;
};

// Functions:
void introFunction();
string roleChoiceFunction();
void customerLogIn();
void customerRegistration();
void customerScreen();
void priceEstimation();
void tripBooking();
void driverLogIn();
void driverRegistration();
void driverScreen();
void claimTrip();
void adminLogIn();
void adminScreen();

int main()
{
    /* Create the adminData.txt file if it isn't already there, and make sure we overwrite the contents
     * Rather than adding duplicates of the admin information each time:
     * Admin Email: admin@nztaxitrip.com
     * Admin Password: toot-for-taxi
     */
    adminData.open("adminData.txt", ios::out);

    // Write to the file:
    adminData << *adminEmailAddressPtr << endl;
    adminData << *adminPasswordPtr << endl;
    adminData << "-----End of item-----" << endl;

    // Close the file:
    adminData.close();

    // Start the program with the intro:
    introFunction();
}

void introFunction()
{
    // Placeholder for the intro screen:
    cout << "[intro screen]" << endl << endl;

    // Use a function to determine the user's role:
    roleChoiceFunction();

    if (*roleChoicePtr == "C")
    {
        // Check if they already have an account or if they need to register:
        cout << "\nDo you have an account? Yes or No: ";
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
                cout << "\nDo you have an account? Yes or No: ";
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
        cout << "\nDo you have an account? Yes or No: ";
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
                cout << "\nDo you have an account? Yes or No: ";
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

    // TEMPORARY:
    cout << endl << endl;
    customerScreen();
}

// Customer Registration Function:
void customerRegistration()
{
    cout << "\n[Insert Customer Registration Here]" << endl;
}

// Customer Screen:
void customerScreen()
{
    /* Header Section:
     * Taxi modified from a car ASCII image "MACHO 2020" by The Animator on animasci.com
     * License will be included with these programming files.
     */
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
    cout << "______________________________________________" << endl;
    cout << "______________________________________________" << endl << endl;

    cout << "\nWelcome, Customer!" << endl << endl;

    // Standard Costs Section:
    cout << "\n|| Standard Costs ||" << endl << endl;

    cout << "Base fare                        : " << *baseFarePtr << endl << endl;
    cout << "Cost per kilometer               : " << *costPerKmPtr << endl << endl;
    cout << "Cost per hour of waiting time" << endl;
    cout << "(if applicable)                  : " << *costPerHourWaitingPtr << endl << endl;
    cout << "Fixed fare between the airport" << endl;
    cout << "and the CBD                      : " << *airportCBDFixedFarePtr << endl << endl;

    // Options Section:
    cout << "\n|| Options ||" << endl << endl;

    cout << "1. Get a price estimation" << endl << endl;
    cout << "2. Book or cancel a trip" << endl << endl;
    cout << "3. Log out" << endl << endl;

    cout << "What would you like to do?" << endl;
    cout << "Please type 1, 2 or 3: ";
    cin >> *customerScreenMenuOptionPtr;

    cout << endl;

    // Act on the user's choice:
    if (*customerScreenMenuOptionPtr == 1)
    {
        // Start the price estimation function:
        priceEstimation();
    }
    else if (*customerScreenMenuOptionPtr == 2)
    {
        tripBooking();
    }
    else if (*customerScreenMenuOptionPtr == 3)
    {
        // Go back to the intro screen to log out:
        introFunction();
    }
    else
    {
        // Manage invalid inputs:
        while (*customerScreenMenuOptionPtr != 1 && *customerScreenMenuOptionPtr != 2 && *customerScreenMenuOptionPtr != 3)
        {
            cout << "Sorry. Invalid input. Please type 1, 2 or 3: ";
            cin >> *customerScreenMenuOptionPtr;
            cout << endl;
        }
        // Once the input is valid, act on it:
        if (*customerScreenMenuOptionPtr == 1)
        {
            // Start the price estimation function:
            priceEstimation();
        }
        else if (*customerScreenMenuOptionPtr == 2)
        {
            tripBooking();
        }
        else if (*customerScreenMenuOptionPtr == 3)
        {
            // Go back to the intro screen to log out:
            introFunction();
        }
    }
}

// Price Estimation Function:
void priceEstimation()
{
    // Header Section:
    cout << "___________________________________________________" << endl << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "___________________________________________________" << endl << endl;

    cout << "Price Estimation" << endl << endl;

    cout << "Please Note: This estimation does not apply to trips to and from" << endl;
    cout << "the airport and the CBD. The set fare for these is displayed above." << endl << endl;

    // Prevent missed inputs:
    cin.ignore();

    // Gather input:
    cout << "\nWhat is your starting location? ";
    getline(cin, *estimateStartPtr);

    cout << "\nWhat is your destination? ";
    getline(cin, *estimateDestinationPtr);

    cout << "\nHow far are you travelling?" << endl;
    cout << "(please do not include 'km'): ";
    cin >> *estimateDistancePtr;

    // Calculate and display the estimated price:
    cout << "\n\nYou should expect to pay $" << *baseFarePtr + (*estimateDistancePtr * *costPerKmPtr) << " for your trip." << endl << endl;

    // Display the 'road' again:
    cout << "___________________________________________________" << endl << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "___________________________________________________" << endl << endl;

    // Make the system wait for input:
    cout << "Please enter any character to continue... ";
    cin >> *pauseCharacterPtr;

    // Back to the customer screen:
    customerScreen();
}

// Trip Booking Function:
void tripBooking()
{
    cout << "\n[Insert Trip Booking Screen Here]" << endl;
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
        else if (*driverEmailLinePtr != NULL && driverLinesCounter == (*driverEmailLinePtr + 1))
        {
            // Check if the password entered is incorrect:
            while (*driverPasswordPtr != driverLine)
            {
                driverLogInAttempts++;
                // Check if the user has used up all their attempts:
                if (driverLogInAttempts >= 3)
                {
                    // Reset login attempts and make the user wait 10 seconds:
                    driverLogInAttempts = 0;
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
                    driverLogInAttempts++;
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
    /* Header Section:
     * Taxi modified from a car ASCII image "MACHO 2020" by The Animator on animasci.com
     * License will be included with these programming files.
     */
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
    cout << "______________________________________________" << endl;
    cout << "______________________________________________" << endl << endl;

    cout << "\nWelcome, Driver!" << endl << endl;

    // Payment Details Section:
    cout << "\n|| Payment Details ||" << endl << endl;

    // Open the driverData.txt file to display the payment details:
    driverData.open("driverData.txt", ios::in);

    // Create some local variables to read this file with:
    string driverScreenLine;
    Driver loggedInDriver;
    int driverScreenLineCounter = 1;

    /* Look for the bank name and the bank account number, 
     * 2 lines up and 1 line up from the email address respectively:
     */
    while (getline(driverData, driverScreenLine))
    {
        // Record the bank name:
        if (driverScreenLineCounter == (*driverEmailLinePtr - 2))
        {
            loggedInDriver.bankName = driverScreenLine;
        }
        else if (driverScreenLineCounter == (*driverEmailLinePtr - 1))
        {
            loggedInDriver.bankAccountNumber = driverScreenLine;
        }
        driverScreenLineCounter++;
    }

    // Close the file and print out the payment details:
    driverData.close();
    cout << "Bank Name: " << loggedInDriver.bankName << endl;
    cout << "Bank Account Number: " << loggedInDriver.bankAccountNumber << endl << endl;

    // Trips Booked Section:
    cout << "\n|| Trips Booked By Customers ||" << endl << endl;

    // Open the tripData.txt file to view the trips booked:
    tripData.open("tripData.txt", ios::in);

    // Create some local variables to read this file with:
    string driverScreenTripLine;
    string dayOfMonth;
    string monthOfYear;
    string year;
    int convertedDayOfMonth;
    int convertedMonthOfYear;
    int convertedYear;
    int driverScreenTripLineCounter = 0;
    int driverScreenEndMarkerCounter = 0;

    /* We're going to be comparing the trips' dates with the current date
     * to see if any are in the past, as we don't want to print these.
     */
    time_t now = time(0);
    struct  tm* dt = localtime(&now);

    /* Now create a linked list of all the trips in the file,
     * starting with the 'headNode':
     */
    Trips *headTrip = new Trips;
    while (getline(tripData, driverScreenTripLine))
    {
        // Count the number of lines being read:
        driverScreenTripLineCounter++;

        switch (driverScreenTripLineCounter)
        {
        case 1:
            headTrip->tripNumber = stoi(driverScreenTripLine);
            break;
        case 2:
            headTrip->customerName = driverScreenTripLine;
            break;
        case 3:
            headTrip->customerContactNumber = driverScreenTripLine;
            break;
        case 4:
            headTrip->startingPlace = driverScreenTripLine;
            break;
        case 5:
            headTrip->destination = driverScreenTripLine;
            break;
        case 6:
            headTrip->tripDate[0] = stoi(driverScreenTripLine);
            break;
        case 7:
            headTrip->tripDate[1] = stoi(driverScreenTripLine);
            break;
        case 8:
            headTrip->tripDate[2] = stoi(driverScreenTripLine);
            break;
        case 9:
            headTrip->time = driverScreenTripLine;
            break;
        case 10:
            if (driverScreenTripLine == "true")
            {
                headTrip->available = true;
            }
            else if (driverScreenTripLine == "false")
            {
                headTrip->available = false;
            }
        }

        // Count the number of end markers:
        if (driverScreenTripLine == "-----End of item-----")
        {
            driverScreenEndMarkerCounter++;
        }
    }
    // Close the file:
    tripData.close();

    // Check if the date is in the past, starting with the year:
    if (headTrip->tripDate[2] < (dt->tm_year + 1900))
    {
        headTrip->past = true;
    }
    else
    {
        // Check the month:
        if (headTrip->tripDate[2] == (dt->tm_year + 1900) && headTrip->tripDate[1] < (dt->tm_mon + 1))
        {
            headTrip->past = true;
        }
        else
        {
            // Check the day:
            if (headTrip->tripDate[2] == (dt->tm_year + 1900) && headTrip->tripDate[1] == (dt->tm_mon + 1) && headTrip->tripDate[0] < dt->tm_mday)
            {
                headTrip->past = true;
            }
            else
            {
                headTrip->past = false;
            }
        }
    }

    // Set the head node's next position to NULL:
    headTrip->nextPosition = NULL;

    // Create the previous node as the headNode:
    Trips *previousTrip = headTrip;

    /* Each item in the data file takes up 11 lines(including the end marker)
     * so, if we add 11 to the line counter each time we reach a new node, 
     * we'll be able to obtain the onformation we need:
     */
    int addEleven = 0;

    // Start from the second node:
    for (int i = 1; i < driverScreenEndMarkerCounter; i++)
    {
        Trips *newTrip = new Trips;

        // Set the line counter to zero:
        driverScreenTripLineCounter = 0;

        // Add eleven:
        addEleven += 11;

        // Re-open the tripData.txt file and look for the next set of trip details:
        tripData.open("tripData.txt", ios::in);

        while (getline(tripData, driverScreenTripLine))
        {
            // Count the number of lines being read:
            driverScreenTripLineCounter++;

            if (driverScreenTripLineCounter == 1 + addEleven)
            {
                newTrip->tripNumber = stoi(driverScreenTripLine);
            }
            else if (driverScreenTripLineCounter == 2 + addEleven)
            {
                newTrip->customerName = driverScreenTripLine;
            }
            else if (driverScreenTripLineCounter == 3 + addEleven)
            {
                newTrip->customerContactNumber = driverScreenTripLine;
            }
            else if (driverScreenTripLineCounter == 4 + addEleven)
            {
                newTrip->startingPlace = driverScreenTripLine;
            }
            else if (driverScreenTripLineCounter == 5 + addEleven)
            {
                newTrip->destination = driverScreenTripLine;
            }
            else if (driverScreenTripLineCounter == 6 + addEleven)
            {
                newTrip->tripDate[0] = stoi(driverScreenTripLine);
            }
            else if (driverScreenTripLineCounter == 7 + addEleven)
            {
                newTrip->tripDate[1] = stoi(driverScreenTripLine);
            }
            else if (driverScreenTripLineCounter == 8 + addEleven)
            {
                newTrip->tripDate[2] = stoi(driverScreenTripLine);
            }
            else if (driverScreenTripLineCounter == 9 + addEleven)
            {
                newTrip->time = driverScreenTripLine;
            }
            else if (driverScreenTripLineCounter == 10 + addEleven)
            {
                if (driverScreenTripLine == "true")
                {
                    newTrip->available = true;
                }
                else if (driverScreenTripLine == "false")
                {
                    newTrip->available = false;
                }
            }
        }
        // Close the file:
        tripData.close();

        // Check if the date is in the past, starting with the year:
        if (newTrip->tripDate[2] < (dt->tm_year + 1900))
        {
            newTrip->past = true;
        }
        else
        {
            // Check the month:
            if (newTrip->tripDate[2] == (dt->tm_year + 1900) && newTrip->tripDate[1] < (dt->tm_mon + 1))
            {
                newTrip->past = true;
            }
            else
            {
                // Check the day:
                if (newTrip->tripDate[2] == (dt->tm_year + 1900) && newTrip->tripDate[1] == (dt->tm_mon + 1) && newTrip->tripDate[0] < dt->tm_mday)
                {
                    newTrip->past = true;
                }
                else
                {
                    newTrip->past = false;
                }
            }
        }

        // Set the node's next position to NULL:
        newTrip->nextPosition = NULL;

        // Set the connection between the last node and the current node:
        previousTrip->nextPosition = newTrip;

        // Replace the values of the previous node with those of the current node:
        previousTrip = newTrip;
    }

    // Print out all of the trips booked, unless they are in the past:
    Trips *temporaryTrip = headTrip;

    while (temporaryTrip != NULL)
    {
        if (temporaryTrip->past == false)
        {
            cout << "Trip Number: " << temporaryTrip->tripNumber << endl;
            cout << "Customer Name: " << temporaryTrip->customerName << endl;
            cout << "Contact Number: " << temporaryTrip->customerContactNumber << endl;
            cout << "Starting Place: " << temporaryTrip->startingPlace << endl;
            cout << "Destination: " << temporaryTrip->destination << endl;
            cout << "Trip Date: " << temporaryTrip->tripDate[0] << "/" << temporaryTrip->tripDate[1] << "/" << temporaryTrip->tripDate[2] << endl;
            cout << "Trip Time: " << temporaryTrip->time << endl;
            cout << "Availability: ";
            if (temporaryTrip->available == true)
            {
                cout << "Available" << endl;
            }
            else if (temporaryTrip->available == false)
            {
                cout << "Unavailable" << endl;
            }

            // Create a space before the next trip:
            cout << endl;
        }

        // Retrieve the next node:
        temporaryTrip = temporaryTrip->nextPosition;
    }

    // Delete the linked list to avoid a memory leak:
    while (headTrip != NULL)
    {
        Trips *tempNode = headTrip;
        headTrip = tempNode->nextPosition;
        delete(tempNode);
    }

    // Report Section:
    cout << "\n\n|| Daily Report ||" << endl << endl;

    // To print out today's date...
    cout << "Today's Date: " << dt->tm_mday << "/" << dt->tm_mon + 1 << "/" << dt->tm_year + 1900 << endl << endl;

    // Create some local variables:
    int numberOfTripsToday = 0;
    int reportLinesCounter = 0;
    double sumOfCosts = 0;
    string activityLine;
    vector<ClaimedTrips>activityEmailLine;

    // Look for the current user's email address in the file containing claimed trips:
    driverActivityData.open("driverActivityData.txt",ios::in);
    while (getline(driverActivityData, activityLine))
    {
        // Count the lines being read:
        reportLinesCounter++;

        if (activityLine == *driverEmailLogInPtr)
        {
            // Create a new instance for the struct array:
            ClaimedTrips *newTrip = new ClaimedTrips;

            // Record the lines at which we found the email address in the vector:
            newTrip->emailLine = reportLinesCounter;
            activityEmailLine.push_back(*newTrip);
        }
    }

    // Close the file:
    driverActivityData.close();
    reportLinesCounter = 0;

    // For each email instance in the array, check if the date is today:
    for (auto i = activityEmailLine.begin(); i != activityEmailLine.end(); i++)
    {
        // Open the file:
        driverActivityData.open("driverActivityData.txt", ios::in);

        while (getline(driverActivityData, activityLine))
        {
            // Count the lines being read:
            reportLinesCounter++;

            // First check the date of each trip:
            if (reportLinesCounter == i->emailLine + 1)
            {
                // Check if the day number is correct:
                if (stoi(activityLine) == dt->tm_mday)
                {
                    i->validDate1 = true;
                }
                else
                {
                    i->validDate1 = false;
                }
            }
            else if (reportLinesCounter == i->emailLine + 2)
            {
                // Check if the month is correct:
                if (stoi(activityLine) == dt->tm_mon + 1)
                {
                    i->validDate2 = true;
                }
                else
                {
                    i->validDate2 = false;
                }
            }
            else if (reportLinesCounter == i->emailLine + 3)
            {
                // Check if the year is correct:
                if (stoi(activityLine) == dt->tm_year + 1900)
                {
                    i->validDate3 = true;
                }
                else
                {
                    i->validDate3 = false;
                }
            }
            // Now check the cost of each trip (4 lines down from the email address):
            else if (reportLinesCounter == i->emailLine + 4)
            {
                i->cost = stod(activityLine);
            }
        }
        // Close the file:
        driverActivityData.close();
        reportLinesCounter = 0;

        // Now, if all the date validations are true, add to the sum of costs:
        if (i->validDate1 == true && i->validDate2 == true && i->validDate3 == true)
        {
            sumOfCosts += i->cost;

            // And add to the trips counter:
            numberOfTripsToday++;
        }
    }

    // Print the number of trips today:
    cout << "Your Trips Today: " << numberOfTripsToday << endl << endl;

    // Print the total cost of trips today:
    cout << "Total Earnings: " << sumOfCosts << endl << endl;

    /* My research has shown that taxi drivers in NZ earn an average of $42,423 a year,
     * making their tax rate ((10.5% of 14,000) + (17.5% of (42,423 - 14,000)) / 42,423) * 100 = 15.2%.
     * (((0.105 * 14000) + (0.175 * (42423 - 14000))) / 42423) * 100 = 15.2.
     */
    cout << "Tax Amount: " << sumOfCosts * 0.152 << endl << endl;

    // Give the user some options to move forward:
    cout << "Would you like to claim a trip (type: claim), or log out (type: log out)? ";
    string driverScreenEndOption;
    getline(cin, driverScreenEndOption);

    // Acting on the user's input:
    if (driverScreenEndOption == "claim")
    {
        // Claim a trip:
        claimTrip();
    }
    else if (driverScreenEndOption == "log out")
    {
        cout << endl;

        // Delete the struct instances in the vector so as to avoid a memory leak:
        activityEmailLine.clear();

        // Send the user back to the starting screen:
        introFunction();
    }
    else
    {
        // Fixing a missed inputs bug:
        cin.ignore();

        while (driverScreenEndOption != "claim" && driverScreenEndOption != "log out")
        {
            cout << "\nSorry! You have entered an invalid option. Please try again." << endl;
            cout << "What would you like to do? ";
            getline(cin, driverScreenEndOption);
        }
        // Once the input is valid, act on it:
        if (driverScreenEndOption == "claim")
        {
            // Claim a trip:
            claimTrip();
        }
        else if (driverScreenEndOption == "log out")
        {
            cout << endl;

            // Send the user back to the starting screen:
            introFunction();
        }
    }
}

// Claim Trip Function:
void claimTrip()
{
    // Local Variables:
    string yesOrNo;
    string availability;
    string tripLine;
    int lineCount = 0;
    int counting = 0;
    int multiply = 0;
    vector<string>addClaim;
    vector<string>trips;

    cout << "\nWhich trip would you like to claim?" << endl;
    cout << "Trip Number: ";
    cin >> *tripToClaimPtr;

    // First check if this trip exists:
    tripData.open("tripData.txt", ios::in);

    while (getline(tripData, tripLine))
    {
        lineCount++;
    }
    tripData.close();

    /* Since there are 11 lines in each collection of data on trips,
     * and since these trips' trip numbers are assigned in order,
     * we can use math to figure out if this trip exists or not.
     */
    if (lineCount >= (*tripToClaimPtr * 11))
    {
        // Then the trip exists, and we now have to read it to see if it's available:
        tripData.open("tripData.txt", ios::in);

        /* (*tripToClaimPtr * 11) gets us to the end of the section / trip we are looking
         * for, so (*tripToClaimPtr * 11) - 1 will give us the position of the availability,
         * which is one line up from the end marker.
         * 
         * We're also looking for the date and the cost----to be used in adding this trip to the
         * claimed trips file (driverActivityData) if it isn't already there.
         */
        while (getline(tripData, tripLine))
        {
            counting++;

            if (counting == ((*tripToClaimPtr * 11) - 1))
            {
                availability = tripLine;
            }
            // Store the date and cost in the addClaim vector:
            else if (counting == ((*tripToClaimPtr * 11) - 5))
            {
                addClaim.push_back(tripLine);
            }
            else if (counting == ((*tripToClaimPtr * 11) - 4))
            {
                addClaim.push_back(tripLine);
            }
            else if (counting == ((*tripToClaimPtr * 11) - 3))
            {
                addClaim.push_back(tripLine);
            }
            else if (counting == ((*tripToClaimPtr * 11) - 2))
            {
                addClaim.push_back(tripLine);
            }
        }
        // Close the file and reset counting:
        tripData.close();
        counting = 0;

        /* If the trip is available, re - write the file with the availability now
         * as false, and store the claimed trip in the driverActivityData file.
         */
        if (availability == "true")
        {
            // Store the claimed trip in the driverActivityData file:
            driverActivityData.open("driverActivityData.txt", ios::out | ios::app);

            // Add the currently logged in driver's email address:
            driverActivityData << *driverEmailLogInPtr << endl;

            // Add the date and cost from the addClaim vector:
            for (int i = 0; i < addClaim.size(); i++)
            {
                driverActivityData << addClaim[i] << endl;
            }

            // Add the end marker:
            driverActivityData << "-----End of item-----" << endl;

            // Close the file and clear the vector:
            driverActivityData.close();
            addClaim.clear();

            // Open, read and store every line from the tripData file:
            tripData.open("tripData.txt", ios::in);
            
            while (getline(tripData, tripLine))
            {
                // Store each line in the trips vector:
                trips.push_back(tripLine);
            }

            // Close the file:
            tripData.close();

            // Re-write the tripData file:
            tripData.open("tripData.txt", ios::out);

            // Reset the counter:
            counting = 0;

            for (int i = 0; i < trips.size(); i++)
            {
                // Count lines read:
                counting++;

                /* Put each line back into the file, except for the
                 * line containing the availability of the trip we just claimed.
                 * This has to be changed to false to show it has been taken.
                 */
                if (counting == ((*tripToClaimPtr * 11) - 1))
                {
                    tripData << "false" << endl;
                    trips[i] = "false";
                }
                else
                {
                    tripData << trips[i] << endl;
                }
            }
            // Close the file and reset counting to 0:
            tripData.close();
            counting = 0;

            // Re-print the trips:
            cout << "\n\n\n|| Trips Booked By Customers ||" << endl << endl;

            // Using math to tell where to print different items (11 lines per trip):
            for (int i = 0; i < trips.size(); i++)
            {
                // For every first line:
                if (i == (multiply * 11))
                {
                    cout << "Trip Number: " << trips[i] << endl;
                }
                // For every second line:
                else if (i == (multiply * 11) + 1)
                {
                    cout << "Customer Name: " << trips[i] << endl;
                }
                // For every third line:
                else if (i == (multiply * 11) + 2)
                {
                    cout << "Contact Number: " << trips[i] << endl;
                }
                // For every fourth line:
                else if (i == (multiply * 11) + 3)
                {
                    cout << "Starting Place: " << trips[i] << endl;
                }
                // For every fifth line:
                else if (i == (multiply * 11) + 4)
                {
                    cout << "Destination: " << trips[i] << endl;
                }
                // For every sixth line:
                else if (i == (multiply * 11) + 5)
                {
                    cout << "Trip Date: " << trips[i] << "/";
                }
                // For every seventh line:
                else if (i == (multiply * 11) + 6)
                {
                    cout << trips[i] << "/";
                }
                // For every eighth line:
                else if (i == (multiply * 11) + 7)
                {
                    cout << trips[i] << endl;
                }
                // For every ninth line:
                else if (i == (multiply * 11) + 8)
                {
                    cout << "Trip Time: " << trips[i] << endl;
                }
                // For every tenth line:
                else if (i == (multiply * 11) + 9)
                {
                    cout << "Availability: ";
                    if (trips[i] == "true")
                    {
                        cout << "Available" << endl;
                    }
                    else if (trips[i] == "false")
                    {
                        cout << "Unavailable" << endl;
                    }
                }
                // For every eleventh line:
                else if (i == (multiply * 11) + 10)
                {
                    // Leave a space before the next trip:
                    cout << endl;
                    multiply++;
                }
            }
            // Clear the vector, reset multiply:
            trips.clear();
            multiply = 0;

            // Ask the user if they would like to claim another trip:
            cout << "\n\nWould you like to claim another trip (type y or n)? ";
            cin >> yesOrNo;

            if (yesOrNo == "y")
            {
                claimTrip();
            }
            else if (yesOrNo == "n")
            {
                // Back to the driver screen:
                driverScreen();
            }
            else
            {
                // Invalid input:
                while (yesOrNo != "y" && yesOrNo != "n")
                {
                    cout << "\nSorry! Invalid input. Please type y or n: ";
                    cin >> yesOrNo;
                }
                // When valid, check the input again:
                if (yesOrNo == "y")
                {
                    claimTrip();
                }
                else if (yesOrNo == "n")
                {
                    driverScreen();
                }
            }
        }
        else if (availability == "false")
        {
            // Clear the vector as we won't need it:
            addClaim.clear();

            cout << "\nSorry, that trip isn't available." << endl;
            cout << "Would you like to claim a different trip (type y or n)? ";
            cin >> yesOrNo;

            if (yesOrNo == "y")
            {
                claimTrip();
            }
            else if (yesOrNo == "n")
            {
                // Back to the driver screen:
                driverScreen();
            }
            else
            {
                // Invalid input:
                while (yesOrNo != "y" && yesOrNo != "n")
                {
                    cout << "\nSorry! Invalid input. Please type y or n: ";
                    cin >> yesOrNo;
                }
                // When valid, check the input again:
                if (yesOrNo == "y")
                {
                    claimTrip();
                }
                else if (yesOrNo == "n")
                {
                    driverScreen();
                }
            }
        }
    }
    else
    {
        cout << "\nSorry, that trip doesn't exist!" << endl;
        cout << "Would you like to claim a different trip (type y or n)? ";
        cin >> yesOrNo;

        if (yesOrNo == "y")
        {
            claimTrip();
        }
        else if (yesOrNo == "n")
        {
            // Back to the driver screen:
            driverScreen();
        }
        else
        {
            // Invalid input:
            while (yesOrNo != "y" && yesOrNo != "n")
            {
                cout << "\nSorry! Invalid input. Please type y or n: ";
                cin >> yesOrNo;
            }
            // When valid, check the input again:
            if (yesOrNo == "y")
            {
                claimTrip();
            }
            else if (yesOrNo == "n")
            {
                driverScreen();
            }
        }
    }
}

// Admin LogIn Function:
void adminLogIn()
{
    // Header Section:
    cout << "___________________________________________________" << endl << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "___________________________________________________" << endl << endl;

    cout << "Admin LogIn" << endl << endl;

    // Fix the missed inputs issue:
    cin.ignore();

    // Obtain the login details:
    cout << "Please enter your email address: ";
    getline(cin, *adminEmailAddressPtr);
    cout << "Please enter your password: ";
    getline(cin, *adminPasswordPtr);

    // Open and search adminData.txt for these details:
    adminData.open("adminData.txt", ios::in);
    // Search for the email address:
    while (getline(adminData, adminLine))
    {
        if (adminLine == *adminEmailAddressPtr)
        {
            // If you find the email address, record how far down the data file it is:
            *adminEmailLinePtr = adminLinesCounter;
        }
        // The confirmed password is located 1 line down from the email address:
        else if (*adminEmailLinePtr != NULL && adminLinesCounter == (*adminEmailLinePtr + 1))
        {
            // Check if the password entered is incorrect:
            while (*adminPasswordPtr != adminLine)
            {
                adminLogInAttempts++;
                // Check if the user has used up all their attempts:
                if (adminLogInAttempts >= 3)
                {
                    // Reset login attempts and make the user wait 10 seconds:
                    adminLogInAttempts = 0;
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
                    getline(cin, *adminPasswordPtr);
                    adminLogInAttempts++;
                }
                /* If the password entered is incorrect, tell the user this,
                 * as well as how many attempts they have left to make:
                 */
                cout << "\nSorry. Incorrect password! Please try again." << endl;
                cout << "Please enter your password: ";
                getline(cin, *adminPasswordPtr);
            }
            /* Once the password is correct...
             * Reset the lines being read to zero and close the file:
             */
            adminLinesCounter = 0;
            adminData.close();

            // Tell the user they have successfully logged in, and take them to the Admin Screen:
            cout << "\nLog in successful!" << endl;
            adminLogInAttempts = 0;
            adminScreen();
        }
        // Count the lines being read:
        adminLinesCounter++;
    }
    // If, after searching through the whole file, the email address entered is not found:
    if (*adminEmailLinePtr == NULL)
    {
        adminData.close();
        cout << "\nSorry. That email address was not found." << endl;
        cout << "Do you want to return to the home screen(type: home)? ";
        cin >> *adminEmailNotFoundPtr;

        // Make sure the input is valid:
        while (*adminEmailNotFoundPtr != "home" && *adminEmailNotFoundPtr != "Home")
        {
            cout << "\nSorry. Invalid input. Please type 'home' to return home: ";
            cin >> *adminEmailNotFoundPtr;
        }

        // Act on valid input:
        introFunction();
    }
}

// Admin Logged In Screen Function:
void adminScreen()
{
    /* Header Section:
     * Taxi modified from a car ASCII image "MACHO 2020" by The Animator on animasci.com
     * License will be included with these programming files.
     */
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
    cout << "______________________________________________" << endl;
    cout << "______________________________________________" << endl << endl;

    cout << "\nWelcome, Admin!" << endl << endl;

    // Daily Driver Report:
    cout << "\n|| Daily Driver Report ||" << endl << endl;

    // Print today's date:
    time_t now = time(0);
    struct  tm* dt = localtime(&now);

    cout << "Today's Date: " << dt->tm_mday << "/" << dt->tm_mon + 1 << "/" << dt->tm_year + 1900 << endl << endl;

    // Check how many claimed trips happened today by looking in the claimed trips file:
    driverActivityData.open("driverActivityData.txt", ios::in);

    string activityLine;
    int lineCounter = 0;
    int numberOfTrips = 0;
    double totalCustomerPayments = 0;
    bool dayValid = false;
    bool monthValid = false;
    bool yearValid = false;
    vector<int>endMarkers;
    vector<double>costs;

    while (getline(driverActivityData, activityLine))
    {
        // Count the lines:
        lineCounter++;

        // Record the locations of the end markers in a vector:
        if (activityLine == "-----End of item-----")
        {
            endMarkers.push_back(lineCounter);
        }
    }
    driverActivityData.close();
    lineCounter = 0;

    // For each section, check the date:
    for (auto a = 0; a < endMarkers.size(); a++)
    {
        driverActivityData.open("driverActivityData.txt", ios::in);

        while (getline(driverActivityData, activityLine))
        {
            // Count the lines:
            lineCounter++;

            if (lineCounter == (endMarkers[a]) + 4)
            {
                if (stoi(activityLine) == dt->tm_mday)
                {
                    dayValid = true;
                }
                else
                {
                    dayValid = false;
                }
            }
            else if (lineCounter == (endMarkers[a]) + 3)
            {
                if (stoi(activityLine) == dt->tm_mon + 1)
                {
                    monthValid = true;
                }
                else
                {
                    monthValid = false;
                }
            }
            else if (lineCounter == (endMarkers[a]) + 2)
            {
                if (stoi(activityLine) == dt->tm_year + 1900)
                {
                    yearValid = true;
                }
                else
                {
                    yearValid = false;
                }
            }
            // Also, record the cost of the trip and add it to the total:
            else if (lineCounter == (endMarkers[a]) + 1)
            {
                totalCustomerPayments += stod(activityLine);
            }
        }
        // Close the file:
        driverActivityData.close();

        // Reset the line counter:
        lineCounter = 0;

        // If the day, month and year matches today's date, add to numberOfTrips:
        if (dayValid == true && monthValid == true && yearValid == true)
        {
            numberOfTrips++;
        }
    }

    // Print the number of trips:
    cout << "Number of Trips Today              : " << numberOfTrips << endl << endl;

    // Total paid in fares:
    cout << "Total Driver Earnings (Gross)      : " << totalCustomerPayments << endl << endl;

    // Total tax deductions (based on the average taxi driver's yearly earnings of $42,423):
    cout << "Total Tax Deductions               : " << totalCustomerPayments * 0.152 << endl << endl;

    // Net income earned by all drivers today:
    cout << "Combined Net Earnings for Drivers  : " << totalCustomerPayments - (totalCustomerPayments * 0.152) << endl << endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu