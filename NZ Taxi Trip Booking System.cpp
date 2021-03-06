/* Authors: Jade Brown & Johnathan Worrall
 * Assignment: CS103 Group Project
 * Project Name: NZ Taxi Trip Booking System
 */

#define _CRT_SECURE_NO_WARNINGS
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
fstream tripData;
fstream newCustomerData;
fstream tripNumberGenerator;
fstream tripCancellations;
string roleChoice;
string* roleChoicePtr = &roleChoice;
int lastWeekDay;
int lastWeekMonth;
int lastWeekYear;
int* lastWeekDayPtr = &lastWeekDay;
int* lastWeekMonthPtr = &lastWeekMonth;
int* lastWeekYearPtr = &lastWeekYear;

// Global Variables For Customer Registration / LogIn:
fstream customerData;
int noOfNewCustomersToday = 0;
int* noOfNewCustomersTodayPtr = &noOfNewCustomersToday;
int noOfNewCustomersThisWeek = 0;
int* noOfNewCustomersThisWeekPtr = &noOfNewCustomersThisWeek;
int customerLogInAttempts = 0;
int customerEmailLine;
int* customerEmailLinePtr = &customerEmailLine;
int customerLinesCounter = 0;
int customerScreenLineCounter = 1;
string customerEmailLogIn;
string* customerEmailLogInPtr = &customerEmailLogIn;
string customerPassword;
string* customerPasswordPtr = &customerPassword;
string customerLine;
string customerEmailNotFound;
string* customerEmailNotFoundPtr = &customerEmailNotFound;
string newCustomerEmail;
string* newCustomerEmailPtr = &newCustomerEmail;
bool customerJustRegistered = false;
bool* customerJustRegisteredPtr = &customerJustRegistered;

// Global Variables For Customer Screen:
double costPerKm = 2.60;
double* costPerKmPtr = &costPerKm;
double costPerHourWaiting = 50.00;
double* costPerHourWaitingPtr = &costPerHourWaiting;
double baseFare = 3.50;
double* baseFarePtr = &baseFare;
double airportCBDFixedFare = 63.00;
double* airportCBDFixedFarePtr = &airportCBDFixedFare;
double estimateDistance;
double* estimateDistancePtr = &estimateDistance;
int customerScreenMenuOption;
int* customerScreenMenuOptionPtr = &customerScreenMenuOption;
string estimateStart;
string* estimateStartPtr = &estimateStart;
string estimateDestination;
string* estimateDestinationPtr = &estimateDestination;
string pauseCharacter;
string* pauseCharacterPtr = &pauseCharacter;

// Global Variables For Trip Booking:
int noOfCancellationsDaily = 0;
int* noOfCancellationsDailyPtr = &noOfCancellationsDaily;
int noOfCancellationsWeekly = 0;
int* noOfCancellationsWeeklyPtr = &noOfCancellationsWeekly;
int tripBookingChoice;
int* tripBookingChoicePtr = &tripBookingChoice;
int tripToCancel;
int* tripToCancelPtr = &tripToCancel;

// Global Variables For Driver Registration / LogIn:
fstream driverData;
string licenceStatus;
string* licenceStatusPtr = &licenceStatus;
string driverEmailLogIn;
string* driverEmailLogInPtr = &driverEmailLogIn;
string driverPassword;
string* driverPasswordPtr = &driverPassword;
string driverLine;
string* driverLinePtr = &driverLine;
string driverEmailNotFound;
string* driverEmailNotFoundPtr = &driverEmailNotFound;
int drivingExperience;
int* drivingExperiencePtr = &drivingExperience;
int vehicleAge;
int* vehicleAgePtr = &vehicleAge;
int driverAge;
int* driverAgePtr = &driverAge;
int driverLinesCounter = 1;
int* driverLinesCounterPtr = &driverLinesCounter;
int driverEmailLine;
int* driverEmailLinePtr = &driverEmailLine;
int pLongevity;
int* pLongevityPtr = &pLongevity;
int pYearToCheck;
int* pYearToCheckPtr = &pYearToCheck;
int driverLogInAttempts = 0;
bool pLeap;
bool* pLeapPtr = &pLeap;

// Global Variables For Driver Screen:
fstream driverActivityData;
string driverActivityLine;
string* driverActivityLinePtr = &driverActivityLine;
int driverActivityLinesCounter = 0;
int* driverActivityLinesCounterPtr = &driverActivityLinesCounter;
int tripToClaim;
int* tripToClaimPtr = &tripToClaim;
bool dateValidation1;
bool* dateValidation1Ptr = &dateValidation1;
bool dateValidation2;
bool* dateValidation2Ptr = &dateValidation2;
bool dateValidation3;
bool* dateValidation3Ptr = &dateValidation3;
vector<int>displayedTripNumbers;

// Global Variables For Admin LogIn:
fstream adminData;
string adminEmailAddress;
string* adminEmailAddressPtr = &adminEmailAddress;
string adminPassword;
string* adminPasswordPtr = &adminPassword;
string adminLine;
string* adminLinePtr = &adminLine;
string adminEmailNotFound;
string* adminEmailNotFoundPtr = &adminEmailNotFound;
int adminLinesCounter = 1;
int* adminLinesCounterPtr = &adminLinesCounter;
int adminLogInAttempts = 0;

// Structures:
struct Customer
{
    // General Information:
    string fullName;
    string contactNumber;
    string postalAddress;

    // Payment Information:
    string cardNumber;
    char cardExpiry[10] = " ";
    string cardVerificationCode;

    // Login Information:
    string emailAddress;
    string password1;
    string password2;
    string passwordConfirmed;
};

struct CustomerCount
{
    int day = 0;
    int month = 0;
    int year = 0;
    bool tooOld = false;
};

struct CancellationCount
{
    int day = 0;
    int month = 0;
    int year = 0;
    bool tooOld = false;
};

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
    int endorsementExpiry[3] = { 0,0,0 };
};

// Driver Activity Struct / Claimed Trips:
struct ClaimedTrips
{
    int tripNumber = 0;
    string emailAddress;
    int day = 0;
    int month = 0;
    int year = 0;
    string time;
    double cost = 0.00;
    bool validDate1 = false;
    bool validDate2 = false;
    bool validDate3 = false;
    int emailLine = 0;
};

// Trip Booking Structure:
struct Trips
{
    int tripNumber = 0;
    string customerName;
    string customerContactNumber;
    string startingPlace;
    string destination;
    int tripDate[3] = { 0,0,0 };
    string time;
    int noOfPeople = 0;
    string extraSupport;
    string luggage;
    string visaCardNumber;
    string cardExpiry;
    string cardCVC;
    bool paymentStatus = false;
    double cost = 0;
    bool available = true;
    Trips *nextPosition = NULL;

    /* This will help us only print the trips booked
     * for the present or future.
     */
    bool past = false;
};

// Functions:
void cleanUpData();
void introFunction();
string roleChoiceFunction();
void customerLogIn();
void customerRegistration();
void customerScreen();
void priceEstimation();
void tripBooking();
void tripCancellation();
void billScreen(Trips trip, int distance);
void driverLogIn();
void driverRegistration();
void driverScreen(string myEmail);
void claimTrip(string myEmail);
void bookedTripsDisplay();
void adminLogIn();
void adminScreen();

int main()
{
    /* Create the adminData.txt file if it isn't already there, and make sure we overwrite the contents
     * rather than adding duplicates of the admin information each time:
     * Admin Email: admin@nztaxitrip.com
     * Admin Password: toot-for-taxi
     */
    adminData.open("adminData.txt", ios::out);

    // Write to the file:
    adminData << "admin@nztaxitrip.com" << endl;
    adminData << "toot-for-taxi" << endl;
    adminData << "-----End of item-----" << endl;

    // Close the file:
    adminData.close();

    /* Clean up the trips, driver activity, customer count and cancellation count files,
     * deleting anything older than a week.
     */
    cleanUpData();

    // Start the program with the intro:
    introFunction();
}

void cleanUpData()
{
    /* First, we'll need to calculate what the date was last week,
     * so we'll obtain today's date...
     */
    time_t now = time(0);
    struct  tm* dt = localtime(&now);

    // Then set up some local variables:
    string tripLines;
    int currentDay = dt->tm_mday;
    int currentMonth = dt->tm_mon + 1;
    int currentYear = dt->tm_year + 1900;
    int counts = 0;
    int multiplication = 0;
    bool isLeap;
    bool tooOld;
    vector<Trips>cleaningVector;
    vector<ClaimedTrips>cleaningVector2;
    vector<CustomerCount>cleaningVector3;
    vector<CancellationCount>cleaningVector4;
    vector<int>cleaningEndMarkers;

    // Start the dates off as the same:
    *lastWeekDayPtr = currentDay;
    *lastWeekMonthPtr = currentMonth;
    *lastWeekYearPtr = currentYear;

    // Count 7 days back, unless we reach 1:
    while (*lastWeekDayPtr > 1 && counts < 7)
    {
        counts++;
        lastWeekDay--;
    }

    // If we haven't counted 7 days, count the rest back from the last day of last month:
    if (counts < 7)
    {
        // Find out what month last month was, and assign lastWeekDay accordingly:
        if (currentMonth == 1)
        {
            *lastWeekMonthPtr = 12;
            *lastWeekYearPtr = currentYear - 1;
        }
        else
        {
            *lastWeekMonthPtr = currentMonth - 1;
        }

        switch (*lastWeekMonthPtr)
        {
        case 1:
            *lastWeekDayPtr = 31;
            break;
        case 2:
            // Is it currently a leap year?
            // Check if the year is divisible by 4:
            if (currentYear % 4 == 0)
            {
                // Check if the year is divisible by 100:
                if (currentYear % 100 == 0)
                {
                    // Check if the year is divisible by 400:
                    if (currentYear % 400 == 0)
                    {
                        isLeap = true;
                    }
                    else
                    {
                        isLeap = false;
                    }
                }
                else
                {
                    isLeap = true;
                }
            }
            else
            {
                isLeap = false;
            }
            // The day we start counting from will depend on if it's a leap year:
            if (isLeap == true)
            {
                *lastWeekDayPtr = 29;
            }
            else if (isLeap == false)
            {
                *lastWeekDayPtr = 28;
            }
            break;
        case 3:
            *lastWeekDayPtr = 31;
            break;
        case 4:
            *lastWeekDayPtr = 30;
            break;
        case 5:
            *lastWeekDayPtr = 31;
            break;
        case 6:
            *lastWeekDayPtr = 30;
            break;
        case 7:
            *lastWeekDayPtr = 31;
            break;
        case 8:
            *lastWeekDayPtr = 31;
            break;
        case 9:
            *lastWeekDayPtr = 30;
            break;
        case 10:
            *lastWeekDayPtr = 31;
            break;
        case 11:
            *lastWeekDayPtr = 30;
            break;
        case 12:
            *lastWeekDayPtr = 31;
            break;
        }

        // Count the rest of the days:
        while (counts < 7)
        {
            counts++;
            lastWeekDay--;
        }
    }

    // Reset counter so we can use it again:
    counts = 0;

    // Reset Multiplication:
    multiplication = 0;

    /* Now we have the date for last week!
     * We now need to search through the trips file,
     * and find any trips that are older than one week.
     */
    tripData.open("tripData.txt", ios::in);

    // Create a temporary instance of the Trips structure:
    Trips* cleaningTrips = new Trips;

    while (getline(tripData, tripLines))
    {
        // For every first line:
        if (counts == (multiplication * 19))
        {
            cleaningTrips->tripNumber = stoi(tripLines);
        }
        // For every second line:
        else if (counts == (multiplication * 19) + 1)
        {
            cleaningTrips->customerName = tripLines;
        }
        // For every third line:
        else if (counts == (multiplication * 19) + 2)
        {
            cleaningTrips->customerContactNumber = tripLines;
        }
        // For every fourth line:
        else if (counts == (multiplication * 19) + 3)
        {
            cleaningTrips->startingPlace = tripLines;
        }
        // For every fifth line:
        else if (counts == (multiplication * 19) + 4)
        {
            cleaningTrips->destination = tripLines;
        }
        // For every sixth line:
        else if (counts == (multiplication * 19) + 5)
        {
            cleaningTrips->tripDate[0] = stoi(tripLines);
        }
        // For every seventh line:
        else if (counts == (multiplication * 19) + 6)
        {
            cleaningTrips->tripDate[1] = stoi(tripLines);
        }
        // For every eighth line:
        else if (counts == (multiplication * 19) + 7)
        {
            cleaningTrips->tripDate[2] = stoi(tripLines);
        }
        // For every ninth line:
        else if (counts == (multiplication * 19) + 8)
        {
            cleaningTrips->time = tripLines;
        }
        // For every tenth line:
        else if (counts == (multiplication * 19) + 9)
        {
            cleaningTrips->noOfPeople = stoi(tripLines);
        }
        // For every eleventh line:
        else if (counts == (multiplication * 19) + 10)
        {
            cleaningTrips->extraSupport = tripLines;
        }
        // For every twelth line:
        else if (counts == (multiplication * 19) + 11)
        {
            cleaningTrips->luggage = tripLines;
        }
        // For every thirteenth line:
        else if (counts == (multiplication * 19) + 12)
        {
            cleaningTrips->visaCardNumber = tripLines;
        }
        // For every fourteenth line:
        else if (counts == (multiplication * 19) + 13)
        {
            cleaningTrips->cardExpiry = tripLines;
        }
        // For every fifteenth line:
        else if (counts == (multiplication * 19) + 14)
        {
            cleaningTrips->cardCVC = tripLines;
        }
        // For every sixteenth line:
        else if (counts == (multiplication * 19) + 15)
        {
            // Payment Status:
            if (tripLines == "true")
            {
                cleaningTrips->paymentStatus = true;
            }
            else if (tripLines == "false")
            {
                cleaningTrips->paymentStatus = false;
            }
        }
        // For every seventeenth line:
        else if (counts == (multiplication * 19) + 16)
        {
            cleaningTrips->cost = stod(tripLines);
        }
        // For every eighteenth line:
        else if (counts == (multiplication * 19) + 17)
        {
            if (tripLines == "true")
            {
                cleaningTrips->available = true;
            }
            else if (tripLines == "false")
            {
                cleaningTrips->available = false;
            }
        }
        // For every nineteenth line:
        else if (counts == (multiplication * 19) + 18)
        {
            // Add the instance to the vector:
            cleaningVector.push_back(*cleaningTrips);

            // Create a new instance:
            Trips* cleaningTrips = new Trips;

            multiplication++;
        }
        // Count the lines being read:
        counts++;
    }
    // Close the file:
    tripData.close();

    // Add the last instance to the vector:
    cleaningVector.push_back(*cleaningTrips);

    // And then delete it, as it will be empty:
    cleaningVector.pop_back();

    // Now that we've stored everything in a struct, we can re-write the tripData file:
    tripData.open("tripData.txt", ios::out);

    for (int i = 0; i < cleaningVector.size(); i++)
    {
        /* For each instance in the vector, find out if the date is more than a week ago
         * and only print the contents if the date is more recent.
         */
        if (cleaningVector[i].tripDate[2] < *lastWeekYearPtr)
        {
            tooOld = true;
        }
        else
        {
            // If the year isn't too far back, check the month:
            if (cleaningVector[i].tripDate[2] == *lastWeekYearPtr && cleaningVector[i].tripDate[1] < *lastWeekMonthPtr)
            {
                tooOld = true;
            }
            else
            {
                // If the month isn't too far back, check the day:
                if (cleaningVector[i].tripDate[2] == *lastWeekYearPtr && cleaningVector[i].tripDate[1] == *lastWeekMonthPtr && cleaningVector[i].tripDate[0] < *lastWeekDayPtr)
                {
                    tooOld = true;
                }
                else
                {
                    tooOld = false;
                }
            }
        }
        // Only print if tooOld is false:
        if (tooOld == false)
        {
            tripData << cleaningVector[i].tripNumber << endl;
            tripData << cleaningVector[i].customerName << endl;
            tripData << cleaningVector[i].customerContactNumber << endl;
            tripData << cleaningVector[i].startingPlace << endl;
            tripData << cleaningVector[i].destination << endl;
            tripData << cleaningVector[i].tripDate[0] << endl;
            tripData << cleaningVector[i].tripDate[1] << endl;
            tripData << cleaningVector[i].tripDate[2] << endl;
            tripData << cleaningVector[i].time << endl;
            tripData << cleaningVector[i].noOfPeople << endl;
            tripData << cleaningVector[i].extraSupport << endl;
            tripData << cleaningVector[i].luggage << endl;
            tripData << cleaningVector[i].visaCardNumber << endl;
            tripData << cleaningVector[i].cardExpiry << endl;
            tripData << cleaningVector[i].cardCVC << endl;
            if (cleaningVector[i].paymentStatus == true)
            {
                tripData << "true" << endl;
            }
            else if (cleaningVector[i].paymentStatus == false)
            {
                tripData << "false" << endl;
            }
            tripData << cleaningVector[i].cost << endl;
            if (cleaningVector[i].available == true)
            {
                tripData << "true" << endl;
            }
            else if (cleaningVector[i].available == false)
            {
                tripData << "false" << endl;
            }
            tripData << "-----End of item-----" << endl;
        }
    }
    // Close the file:
    tripData.close();

    /* We now have to do the same thing for the
     * driverActivityData file. We'll clear the cleaningVector
     * first, and reset counts to 0.
     *
     * We'll also try and delete any leftover cleaningTrips.
     */
    cleaningVector.clear();
    delete cleaningTrips;
    counts = 0;

    // First, let's look for end markers in the driverActivityData file:
    driverActivityData.open("driverActivityData.txt", ios::in);

    while (getline(driverActivityData, tripLines))
    {
        // Count the lines being read:
        counts++;

        if (tripLines == "-----End of item-----")
        {
            // Add the location of the end marker to the appropriate vector:
            cleaningEndMarkers.push_back(counts);
        }
    }
    // Close the file:
    driverActivityData.close();
    counts = 0;

    // Open it again so we can fill the struct:
    driverActivityData.open("driverActivityData.txt", ios::in);

    // Create a temporary instance of the ClaimedTrips structure:
    ClaimedTrips* cleaningTrips2 = new ClaimedTrips;

    while (getline(driverActivityData, tripLines))
    {
        // Count the lines being read:
        counts++;

        for (int i = 0; i < cleaningEndMarkers.size(); i++)
        {
            // For every first line:
            if (counts == (cleaningEndMarkers[i] - 7))
            {
                cleaningTrips2->tripNumber = stoi(tripLines);
            }
            // For every second line:
            if (counts == (cleaningEndMarkers[i] - 6))
            {
                cleaningTrips2->emailAddress = tripLines;
            }
            // For every third line:
            else if (counts == (cleaningEndMarkers[i] - 5))
            {
                cleaningTrips2->day = stoi(tripLines);
            }
            // For every fourth line:
            else if (counts == (cleaningEndMarkers[i] - 4))
            {
                cleaningTrips2->month = stoi(tripLines);
            }
            // For every fifth line:
            else if (counts == (cleaningEndMarkers[i] - 3))
            {
                cleaningTrips2->year = stoi(tripLines);
            }
            // For every sixth line:
            else if (counts == (cleaningEndMarkers[i] - 2))
            {
                cleaningTrips2->time = tripLines;
            }
            // For every seventh line:
            else if (counts == (cleaningEndMarkers[i] - 1))
            {
                cleaningTrips2->cost = stod(tripLines);
            }
            // For every eighth line:
            else if (counts == (cleaningEndMarkers[i]))
            {
                // Add the instance to the vector:
                cleaningVector2.push_back(*cleaningTrips2);

                // Create a new instance:
                ClaimedTrips* cleaningTrips2 = new ClaimedTrips;
            }
        }
    }
    // Close the file:
    driverActivityData.close();

    counts = 0;
    cleaningEndMarkers.clear();

    // Add the last instance to the vector:
    cleaningVector2.push_back(*cleaningTrips2);

    // And then delete it, as it will be empty:
    cleaningVector2.pop_back();

    // Now that we've stored everything in a struct, we can re-write the driverActivityData file:
    driverActivityData.open("driverActivityData.txt", ios::out);

    for (int i = 0; i < cleaningVector2.size(); i++)
    {
        /* For each instance in the vector, find out if the date is more than a week ago
         * and only print the contents if the date is more recent.
         */
        if (cleaningVector2[i].year < *lastWeekYearPtr)
        {
            tooOld = true;
        }
        else
        {
            // If the year isn't too far back, check the month:
            if (cleaningVector2[i].year == *lastWeekYearPtr && cleaningVector2[i].month < *lastWeekMonthPtr)
            {
                tooOld = true;
            }
            else
            {
                // If the month isn't too far back, check the day:
                if (cleaningVector2[i].year == *lastWeekYearPtr && cleaningVector2[i].month == *lastWeekMonthPtr && cleaningVector2[i].day < *lastWeekDayPtr)
                {
                    tooOld = true;
                }
                else
                {
                    tooOld = false;
                }
            }
        }
        // Only print if tooOld is false:
        if (tooOld == false)
        {
            driverActivityData << cleaningVector2[i].tripNumber << endl;
            driverActivityData << cleaningVector2[i].emailAddress << endl;
            driverActivityData << cleaningVector2[i].day << endl;
            driverActivityData << cleaningVector2[i].month << endl;
            driverActivityData << cleaningVector2[i].year << endl;
            driverActivityData << cleaningVector2[i].time << endl;
            driverActivityData << cleaningVector2[i].cost << endl;
            driverActivityData << "-----End of item-----" << endl;
        }
    }
    // Close the file:
    driverActivityData.close();

    // Clear the cleaning vector:
    cleaningVector2.clear();

    // Delete leftover cleaningTrips2 instances:
    delete cleaningTrips2;

    /* Since we are counting the number of new customers registering each
     * day and week, we will need to clean out any items in the 
     * newCustomerData file that are older than one week.
     * As always, we start by storing the end markers in this file in a vector.
     */
    newCustomerData.open("newCustomerData.txt", ios::in);

    while (getline(newCustomerData, customerLine))
    {
        // Count the lines being read:
        counts++;

        // Look for end markers and store them:
        if (customerLine == "-----End of item-----")
        {
            cleaningEndMarkers.push_back(counts);
        }
    }
    // Close the file:
    newCustomerData.close();

    // Reset the counter:
    counts = 0;

    // Create a new instance of the CustomerCount struct:
    CustomerCount *newCount = new CustomerCount;

    // Open the newCustomerData file:
    newCustomerData.open("newCustomerData.txt", ios::in);

    // Fill the instance:
    while (getline(newCustomerData, customerLine))
    {
        // Count the lines being read:
        counts++;

        for (int i = 0; i < cleaningEndMarkers.size(); i++)
        {
            // For every first line:
            if (counts == (cleaningEndMarkers[i] - 3))
            {
                newCount->day = stoi(customerLine);
            }
            // For every second line:
            else if (counts == (cleaningEndMarkers[i] - 2))
            {
                newCount->month = stoi(customerLine);
            }
            // For every third line:
            else if (counts == (cleaningEndMarkers[i] - 1))
            {
                newCount->year = stoi(customerLine);
            }
            // For every fourth line:
            else if (counts == cleaningEndMarkers[i])
            {
                // Add the instance to the vector:
                cleaningVector3.push_back(*newCount);

                // Create a new instance:
                CustomerCount* newCount = new CustomerCount;
            }
        }
    }
    // Close the file:
    newCustomerData.close();

    // Reset counter:
    counts = 0;

    // Clear the end marker vector:
    cleaningEndMarkers.clear();

    // Add the last instance to the vector:
    cleaningVector3.push_back(*newCount);

    // And then delete it, as it will be empty:
    cleaningVector3.pop_back();

    // Now that we've stored everything in a struct, we can re-write the newCustomerData file:
    newCustomerData.open("newCustomerData.txt", ios::out);

    for (int i = 0; i < cleaningVector3.size(); i++)
    {
        /* For each instance in the vector, find out if the date is more than a week ago
         * and only print the contents if the date is more recent.
         */
        if (cleaningVector3[i].year < *lastWeekYearPtr)
        {
            cleaningVector3[i].tooOld = true;
        }
        else
        {
            // If the year isn't too far back, check the month:
            if (cleaningVector3[i].year == *lastWeekYearPtr && cleaningVector3[i].month < *lastWeekMonthPtr)
            {
                cleaningVector3[i].tooOld = true;
            }
            else
            {
                // If the month isn't too far back, check the day:
                if (cleaningVector3[i].year == *lastWeekYearPtr && cleaningVector3[i].month == *lastWeekMonthPtr && cleaningVector3[i].day < *lastWeekDayPtr)
                {
                    cleaningVector3[i].tooOld = true;
                }
                else
                {
                    cleaningVector3[i].tooOld = false;
                }
            }
        }
    }
    // Printing loop:
    for (int i = 0; i < cleaningVector3.size(); i++)
    {
        // Only print if tooOld is false:
        if (cleaningVector3[i].tooOld == false)
        {
            newCustomerData << cleaningVector3[i].day << endl;
            newCustomerData << cleaningVector3[i].month << endl;
            newCustomerData << cleaningVector3[i].year << endl;
            newCustomerData << "-----End of item-----" << endl;
        }
    }

    // Close the file:
    newCustomerData.close();

    // Clear the cleaning vector:
    cleaningVector3.clear();

    // Delete leftover newCount instances:
    delete newCount;

    /* We are also counting the number of cancellations each week,
     * so we will need to remove any cancellations older than a week
     * as well.
     */
    tripCancellations.open("tripCancellations.txt", ios::in);

    while (getline(tripCancellations, tripLines))
    {
        // Count the lines being read:
        counts++;

        // Look for end markers and store them:
        if (tripLines == "-----End of item-----")
        {
            cleaningEndMarkers.push_back(counts);
        }
    }
    // Close the file:
    tripCancellations.close();

    // Reset the counter:
    counts = 0;

    // Create a new instance of the CancellationCount struct:
    CancellationCount *newCancellation = new CancellationCount;

    // Open the tripCancellations file:
    tripCancellations.open("tripCancellations.txt", ios::in);

    // Fill the instance:
    while (getline(tripCancellations, tripLines))
    {
        // Count the lines being read:
        counts++;

        for (int i = 0; i < cleaningEndMarkers.size(); i++)
        {
            // For every first line:
            if (counts == (cleaningEndMarkers[i] - 3))
            {
                newCancellation->day = stoi(tripLines);
            }
            // For every second line:
            else if (counts == (cleaningEndMarkers[i] - 2))
            {
                newCancellation->month = stoi(tripLines);
            }
            // For every third line:
            else if (counts == (cleaningEndMarkers[i] - 1))
            {
                newCancellation->year = stoi(tripLines);
            }
            // For every fourth line:
            else if (counts == cleaningEndMarkers[i])
            {
                // Add the instance to the vector:
                cleaningVector4.push_back(*newCancellation);

                // Create a new instance:
                CancellationCount* newCancellation = new CancellationCount;
            }
        }
    }
    // Close the file:
    tripCancellations.close();

    // Reset counter:
    counts = 0;

    // Clear the end marker vector:
    cleaningEndMarkers.clear();

    // Add the last instance to the vector:
    cleaningVector4.push_back(*newCancellation);

    // And then delete it, as it will be empty:
    cleaningVector4.pop_back();

    // Now that we've stored everything in a struct, we can re-write the tripCancellations file:
    tripCancellations.open("tripCancellations.txt", ios::out);

    for (int i = 0; i < cleaningVector4.size(); i++)
    {
        /* For each instance in the vector, find out if the date is more than a week ago
         * and only print the contents if the date is more recent.
         */
        if (cleaningVector4[i].year < *lastWeekYearPtr)
        {
            cleaningVector4[i].tooOld = true;
        }
        else
        {
            // If the year isn't too far back, check the month:
            if (cleaningVector4[i].year == *lastWeekYearPtr && cleaningVector4[i].month < *lastWeekMonthPtr)
            {
                cleaningVector4[i].tooOld = true;
            }
            else
            {
                // If the month isn't too far back, check the day:
                if (cleaningVector4[i].year == *lastWeekYearPtr && cleaningVector4[i].month == *lastWeekMonthPtr && cleaningVector4[i].day < *lastWeekDayPtr)
                {
                    cleaningVector4[i].tooOld = true;
                }
                else
                {
                    cleaningVector4[i].tooOld = false;
                }
            }
        }
    }
    // Printing loop:
    for (int i = 0; i < cleaningVector4.size(); i++)
    {
        // Only print if tooOld is false:
        if (cleaningVector4[i].tooOld == false)
        {
            tripCancellations << cleaningVector4[i].day << endl;
            tripCancellations << cleaningVector4[i].month << endl;
            tripCancellations << cleaningVector4[i].year << endl;
            tripCancellations << "-----End of item-----" << endl;
        }
    }

    // Close the file:
    tripCancellations.close();

    // Clear the cleaning vector:
    cleaningVector4.clear();

    // Delete leftover newCancellation instances:
    delete newCancellation;
}

void introFunction()
{
    /* Header Section:
     * Taxi modified from a car ASCII image "MACHO 2020" by The Animator on animasci.com
     * License will be included with these programming files.
     */
    cout << endl << endl;
    cout << "\t\t\t                  ---" << endl;
    cout << "\t\t\t                  | |" << endl;
    cout << "\t\t\t                 ....." << endl;
    cout << "\t\t\t           , ,''  |    ```...___," << endl;
    cout << "\t\t\t    .--  ''  P(___|_______/    (|" << endl;
    cout << "\t\t\t  ( //            |             |" << endl;
    cout << "\t\t\t  ` ._: ' ' :_____|______: ' ' :/" << endl;
    cout << "\t\t\t      '  o  '            '  o  '" << endl;
    cout << "\t\t\t        - -                - - " << endl << endl;
    cout << "\t\t\t______________________________________________" << endl << endl;
    cout << "\t\t\t__________Welcome to NZ Taxi Trip~!___________" << endl;
    cout << "\t\t\t______________________________________________" << endl << endl << endl;

    // Terms & Conditions Section:
    cout << "\t\t\t________________T's & C's Apply_______________" << endl << endl << endl;

    // Customer T's & C's:
    cout << "\t\t\t_________Customer Terms & Conditions__________" << endl << endl;
    cout << "\t\t1. Wear a face mask during your ride (can be temporarily removed" << endl;
    cout << "\t\t   for the purpose of drinking water from a bottle) unless you have" << endl;
    cout << "\t\t   a medical exemption (in which case you will need to provide proof" << endl;
    cout << "\t\t   of this)." << endl;
    cout << "\t\t2. Do not ride with us if you are awaiting the results of a Covid" << endl;
    cout << "\t\t   test, suspect you may have Covid, or are currently showing cold or" << endl;
    cout << "\t\t   flu-like symptoms." << endl;
    cout << "\t\t3. There is to be no consumption of hot food in the cab, nor any drinks" << endl;
    cout << "\t\t   that may spill." << endl << endl << endl;

    // Driver T's & C's:
    cout << "\t\t\t__________Driver Terms & Conditions___________" << endl << endl;
    cout << "\t\t1. In order to drive for us, you will need to have had both Covid-19" << endl;
    cout << "\t\t   vaccinations." << endl;
    cout << "\t\t2. Always wear a face mask when driving with a passenger (unless you" << endl;
    cout << "\t\t   have a medical exemption)." << endl;
    cout << "\t\t3. You must be at least 22 years of age to drive for us." << endl;
    cout << "\t\t4. Always conduct yourself in a polite and professional manner with" << endl;
    cout << "\t\t   customers." << endl;
    cout << "\t\t5. All drivers who choose to participate in NZ Taxi Trip do so at their" << endl;
    cout << "\t\t   discretion, as an independent contractor." << endl << endl << endl << endl;

    // Use a function to determine the user's role:
    roleChoiceFunction();

    if (*roleChoicePtr == "C")
    {
        // Check if they already have an account or if they need to register:
        cout << "\n\t\tDo you have an account? Yes or No: ";
        string customerAccountAnswer;
        string* customerAccountAnswerPtr = &customerAccountAnswer;
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
                cout << "\t\tSorry. You have entered an invalid option. Please try again." << endl;
                cout << "\n\t\tDo you have an account? Yes or No: ";
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
        cout << "\n\t\tDo you have an account? Yes or No: ";
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
                cout << "\t\tSorry. You have entered an invalid option. Please try again." << endl;
                cout << "\n\t\tDo you have an account? Yes or No: ";
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
    cout << "\t\tAre you a customer (C), a driver (D) or an admin (A)? ";
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
    // Header Section:
    cout << "\t\t___________________________________________________" << endl << endl;
    cout << "\t\t---------------------------------------------------" << endl;
    cout << "\t\t___________________________________________________" << endl << endl;

    cout << "\n\t\t\tCustomer LogIn" << endl << endl << endl;

    // Fix the missed inputs issue:
    cin.ignore();

    // Obtain the login details:
    cout << "\t\tPlease enter your email address: ";
    getline(cin, *customerEmailLogInPtr);
    cout << "\t\tPlease enter your password: ";
    getline(cin, *customerPasswordPtr);

    // Set login attempts to 0:
    customerLogInAttempts = 0;

    // Open and search customerData.txt for these details:
    customerData.open("customerData.txt", ios::in);

    // Set customerEmailLine to NULL first:
    *customerEmailLinePtr = NULL;

    // Search for the email address:
    while (getline(customerData, customerLine))
    {
        if (customerLine == *customerEmailLogInPtr)
        {
            // If you find the email address, record how far down the data file it is:
            *customerEmailLinePtr = customerLinesCounter;
        }
        // The confirmed password is located 1 line down from the email address:
        else if (*customerEmailLinePtr != NULL && customerLinesCounter == (*customerEmailLinePtr + 1))
        {
            // Check if the password entered is incorrect:
            while (*customerPasswordPtr != customerLine)
            {
                customerLogInAttempts++;
                // Check if the user has used up all their attempts:
                if (customerLogInAttempts >= 3)
                {
                    // Reset login attempts and make the user wait 10 seconds:
                    customerLogInAttempts = 0;
                    cout << "\n\t\tSorry. Incorrect password! Please try again after 10 seconds." << endl;

                    // Create a timer for 1 minute:
                    using namespace std::chrono_literals;
                    std::cout << "\n\t\tWaiting...\n" << std::flush;
                    auto start = std::chrono::high_resolution_clock::now();
                    std::this_thread::sleep_for(10000ms);
                    auto end = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double, std::milli> elapsed = end - start;

                    // After the timer is done, let them try again:
                    cout << "\n\t\tPlease enter your password: ";
                    getline(cin, *customerPasswordPtr);
                    customerLogInAttempts++;
                }
                /* If the password entered is incorrect, tell the user this,
                 * as well as how many attempts they have left to make:
                 */
                if (*customerPasswordPtr != customerLine)
                {
                    cout << "\n\t\tSorry. Incorrect password! Please try again." << endl;
                    cout << "\t\tPlease enter your password: ";
                    getline(cin, *customerPasswordPtr);
                }
            }
            /* Once the password is correct...
             * Reset the lines being read to zero and close the file:
             */
            customerLinesCounter = 0;
            customerData.close();

            // Tell the user they have successfully logged in, and take them to the Customer Screen:
            cout << "\n\n\t\tLog in successful!" << endl;
            customerScreen();
        }
        // Count the lines being read:
        customerLinesCounter++;
    }

    // Close the file!
    customerData.close();

    // If, after searching through the whole file, the email address entered is not found:
    if (*customerEmailLinePtr == NULL)
    {
        cout << "\n\t\tSorry. That email address was not found. Do you want to register (type: register)" << endl;
        cout << "\t\tor return to the home screen (type: home)? ";
        cin >> *customerEmailNotFoundPtr;

        // Make sure the input is valid:
        while (*customerEmailNotFoundPtr != "register" && *customerEmailNotFoundPtr != "home" && *customerEmailNotFoundPtr != "Register" && *customerEmailNotFoundPtr != "Home")
        {
            cout << "\n\t\tSorry. Invalid input. Please type register or home: ";
            cin >> *customerEmailNotFoundPtr;
        }

        // Act on valid input:
        if (*customerEmailNotFoundPtr == "register" || *customerEmailNotFoundPtr == "Register")
        {
            customerRegistration();
        }
        else if (*customerEmailNotFoundPtr == "home" || *customerEmailNotFoundPtr == "Home")
        {
            introFunction();
        }
    }
}

// Customer Registration Function:
void customerRegistration()
{
    // Header Section:
    cout << "\n\n\t\t___________________________________________________" << endl << endl;
    cout << "\t\t---------------------------------------------------" << endl;
    cout << "\t\t___________________________________________________" << endl << endl;

    cout << "\n\t\t\tCustomer Registration" << endl << endl << endl;

    // Temporary Structure:
    Customer newCustomer;

    // Fix the spaces causing missed inputs issue:
    cin.ignore();

    // Gather input, starting with general information:
    cout << "\t\t\t|| General Information ||" << endl << endl;
    cout << "\t\tFull Name: ";
    getline(cin, newCustomer.fullName);
    cout << "\t\tContact Number: ";
    getline(cin, newCustomer.contactNumber);
    cout << "\t\tPostal Address: ";
    getline(cin, newCustomer.postalAddress);

    // Payment Information:
    cout << "\n\n\n\t\t\t|| Payment Information ||" << endl << endl;
    cout << "\t\tVisa Card Number: ";
    getline(cin, newCustomer.cardNumber);
    cout << "\t\tCard Expiry (dd/mm/yyyy): ";
    cin >> newCustomer.cardExpiry;
    cin.ignore();
    cout << "\t\tCard CVC: ";
    getline(cin, newCustomer.cardVerificationCode);

    // Login Information:
    cout << "\n\n\n\t\t\t|| Account LogIn Information ||" << endl << endl;
    cout << "\t\tEmail Address: ";
    getline(cin, newCustomer.emailAddress);
    cout << "\t\tCreate a Password: ";
    getline(cin, newCustomer.password1);
    cout << "\t\tRe-enter Your Password: ";
    getline(cin, newCustomer.password2);

    // Check if the passwords match:
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
    customerData.open("customerData.txt", ios::out | ios::app);
    customerData << newCustomer.fullName << endl;
    customerData << newCustomer.contactNumber << endl;
    customerData << newCustomer.postalAddress << endl;
    customerData << newCustomer.cardNumber << endl;
    customerData << newCustomer.cardExpiry << endl;
    customerData << newCustomer.cardVerificationCode << endl;
    customerData << newCustomer.emailAddress << endl;
    customerData << newCustomer.passwordConfirmed << endl;
    customerData << "-----End of item-----" << endl;

    // Close the file:
    customerData.close();

    /* For each new customer, mark the date of registration in the
     * newCustomerData.txt file.
     */
    newCustomerData.open("newCustomerData.txt", ios::out | ios::app);

    time_t now = time(0);
    struct  tm* dt = localtime(&now);

    // Add the day, month and year, and then an end marker:
    newCustomerData << dt->tm_mday << endl;
    newCustomerData << dt->tm_mon + 1 << endl;
    newCustomerData << dt->tm_year + 1900 << endl;
    newCustomerData << "-----End of item-----" << endl;

    // Close the file:
    newCustomerData.close();

    // Tell the system that the user just registered:
    *customerJustRegisteredPtr = true;

    // Grab the email address of this new customer:
    *newCustomerEmailPtr = newCustomer.emailAddress;

    // We also need to find out what line this is on:
    customerData.open("customerData.txt", ios::in);

    while (getline(customerData, customerLine))
    {
        if (customerLine == *newCustomerEmailPtr)
        {
            *customerEmailLinePtr = customerScreenLineCounter;
        }
        customerScreenLineCounter++;
    }
    // Close the file:
    customerData.close();

    // Reset the counter:
    customerScreenLineCounter = 1;

    // Send the user to the customer screen:
    customerScreen();
}

// Customer Screen:
void customerScreen()
{
    /* Header Section:
     * Taxi modified from a car ASCII image "MACHO 2020" by The Animator on animasci.com
     * License will be included with these programming files.
     */
    cout << endl << endl;
    cout << "\t\t                  ---" << endl;
    cout << "\t\t                  | |" << endl;
    cout << "\t\t                 ....." << endl;
    cout << "\t\t           , ,''  |    ```...___," << endl;
    cout << "\t\t    .--  ''  P(___|_______/    (|" << endl;
    cout << "\t\t  ( //            |             |" << endl;
    cout << "\t\t  ` ._: ' ' :_____|______: ' ' :/" << endl;
    cout << "\t\t      '  o  '            '  o  '" << endl;
    cout << "\t\t        - -                - - " << endl;
    cout << "\t\t______________________________________________" << endl;
    cout << "\t\t______________________________________________" << endl << endl;

    cout << "\n\t\t\tWelcome, Customer!" << endl << endl;

    // Create some local variables:
    string customerScreenLine;
    int customerScreenLineCounter = 1;

    /* If the customer just registered, we need to access their email
     * address using the global variable.
     */
    if (*customerJustRegisteredPtr == true)
    {
        *customerEmailLogInPtr = *newCustomerEmailPtr;
    }

    // Reset the counter:
    customerScreenLineCounter = 1;

    // Standard Costs Section:
    cout << "\n\t\t\t|| Standard Costs ||" << endl << endl;

    cout << "\t\tBase fare                        : " << *baseFarePtr << endl;
    cout << "\t\tCost per kilometer               : " << *costPerKmPtr << endl;
    cout << "\t\tCost per hour of waiting time" << endl;
    cout << "\t\t(if applicable)                  : " << *costPerHourWaitingPtr << endl;
    cout << "\t\tFixed fare between the airport" << endl;
    cout << "\t\tand the CBD                      : " << *airportCBDFixedFarePtr << endl << endl;

    // Options Section:
    cout << "\n\t\t\t|| Options ||" << endl << endl;

    cout << "\t\t1. Get a price estimation" << endl;
    cout << "\t\t2. Book a trip" << endl;
    cout << "\t\t3. Cancel a trip" << endl;
    cout << "\t\t4. Log out" << endl << endl;

    cout << "\n\t\tWhat would you like to do?" << endl;
    cout << "\t\tPlease type 1, 2, 3 or 4: ";
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
        tripCancellation();
    }
    else if (*customerScreenMenuOptionPtr == 4)
    {
        // Then reset the 'just registered' boolean to false:
        *customerJustRegisteredPtr = false;

        // Go back to the intro screen to log out:
        introFunction();
    }
    else
    {
        // Manage invalid inputs:
        while (*customerScreenMenuOptionPtr != 1 && *customerScreenMenuOptionPtr != 2 && *customerScreenMenuOptionPtr != 3 && *customerScreenMenuOptionPtr != 4)
        {
            cout << "\t\tSorry. Invalid input. Please type 1, 2, 3 or 4: ";
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
            tripCancellation();
        }
        else if (*customerScreenMenuOptionPtr == 4)
        {
            // Then reset the 'just registered' boolean to false:
            *customerJustRegisteredPtr = false;

            // Go back to the intro screen to log out:
            introFunction();
        }
    }
}

// Price Estimation Function:
void priceEstimation()
{
    // Header Section:
    cout << "\n\t\t___________________________________________________" << endl << endl;
    cout << "\t\t---------------------------------------------------" << endl;
    cout << "\t\t___________________________________________________" << endl << endl;

    cout << "\n\t\t\tPrice Estimation" << endl << endl << endl;

    cout << "\t\tPlease Note: This estimation does not apply to trips to and from" << endl;
    cout << "\t\tthe airport and the CBD. The set fare for these is displayed above." << endl << endl;

    // Prevent missed inputs:
    cin.ignore();

    // Gather input:
    cout << "\n\t\tWhat is your starting location? ";
    getline(cin, *estimateStartPtr);

    cout << "\n\t\tWhat is your destination? ";
    getline(cin, *estimateDestinationPtr);

    cout << "\n\t\tHow far are you travelling in kilometers?" << endl;
    cout << "\t\t(please do not include 'km'): ";
    cin >> *estimateDistancePtr;

    // Calculate and display the estimated price:
    cout << "\n\n\t\tYou should expect to pay $" << *baseFarePtr + (*estimateDistancePtr * *costPerKmPtr) << " for your trip." << endl << endl;

    // Display the 'road' again:
    cout << "\n\t\t___________________________________________________" << endl << endl;
    cout << "\t\t---------------------------------------------------" << endl;
    cout << "\t\t___________________________________________________" << endl << endl;

    // Make the system wait for input:
    cout << "\n\t\tPlease enter any character to continue... ";
    cin >> *pauseCharacterPtr;

    // Back to the customer screen:
    customerScreen();
}

// Trip Booking Function:
void tripBooking()
{
    // Header Section:
    cout << "\n\t\t___________________________________________________" << endl << endl;
    cout << "\t\t---------------------------------------------------" << endl;
    cout << "\t\t___________________________________________________" << endl << endl;

    cout << "\n\t\t\tTrip Booking" << endl << endl << endl;

    // Create a temporary instance:
    Trips newTrip;

    // Local Variables:
    int counts = 0;
    int emailLine = 0;
    int generatedTripNumber = 0;
    int confirmOrCancel;
    double distanceTravelled;
    bool inThePast = false;
    string line;
    string oneLine;
    string bookAnother;

    // Allow us to use time:
    time_t now = time(0);
    struct  tm* dt = localtime(&now);

    /* If the customer just registered, we need to access their email
     * address using the global variable.
     */
    if (*customerJustRegisteredPtr == true)
    {
        *customerEmailLogInPtr = *newCustomerEmailPtr;
    }

    // Open the customerData file and read its contents:
    customerData.open("customerData.txt", ios::in);

    while (getline(customerData, line))
    {
        // Count the lines being read:
        counts++;

        // Look for the currently logged in customer's email address:
        if (line == *customerEmailLogInPtr)
        {
            // Record its position:
            emailLine = counts;
        }
    }
    // Close the file:
    customerData.close();

    // Reset the counter:
    counts = 0;

    // Open the file again, and gather what's needed for trip booking:
    customerData.open("customerData.txt", ios::in);

    while (getline(customerData, line))
    {
        // Count the lines again:
        counts++;

        // Grab the full name:
        if (counts == (emailLine - 6))
        {
            newTrip.customerName = line;
        }
        // Grab the contact number:
        if (counts == (emailLine - 5))
        {
            newTrip.customerContactNumber = line;
        }
        // Grab the Visa card number:
        if (counts == (emailLine - 3))
        {
            newTrip.visaCardNumber = line;
        }
        // Grab the card expiry date:
        if (counts == (emailLine - 2))
        {
            newTrip.cardExpiry = line;
        }
        // Grab the card CVC:
        if (counts == (emailLine - 1))
        {
            newTrip.cardCVC = line;
        }
    }
    // Close the file, before asking the user to fill in the rest:
    customerData.close();

    // Reset the counter:
    counts = 0;

    // Fix the missed inputs issue:
    cin.ignore();

    // Gather input about this trip:
    cout << "\t\t\tHello " << newTrip.customerName << "~!" << endl << endl;

    cout << "\n\t\tPlease enter your starting location: ";
    getline(cin, newTrip.startingPlace);
    cout << "\n\t\tPlease enter your desired destination: ";
    getline(cin, newTrip.destination);
    cout << "\n\t\tPlease enter the distance you will be travelling in kilometers" << endl;
    cout << "\t\t(please do not include 'km'): ";
    cin >> distanceTravelled;
    cout << "\n\t\tPlease enter the date of this trip in the following format... (no inputs starting with 0)" << endl;
    cout << "\t\tDay   (dd)    : ";
    cin >> newTrip.tripDate[0];
    cout << "\t\tMonth (mm)    : ";
    cin >> newTrip.tripDate[1];
    cout << "\t\tYear  (yyyy)  : ";
    cin >> newTrip.tripDate[2];

    // Check if the user is attempting to book a trip in the past, starting with the year:
    if (newTrip.tripDate[2] < dt->tm_year + 1900)
    {
        inThePast = true;
    }
    // Check the month:
    else if (newTrip.tripDate[2] == dt->tm_year + 1900 && newTrip.tripDate[1] < dt->tm_mon + 1)
    {
        inThePast = true;
    }
    // Check the day:
    else if (newTrip.tripDate[2] == dt->tm_year + 1900 && newTrip.tripDate[1] == dt->tm_mon + 1 && newTrip.tripDate[0] < dt->tm_mday)
    {
        inThePast = true;
    }
    else
    {
        inThePast = false;
    }
    // Make the user re-enter the date if it is in the past:
    while (inThePast == true)
    {
        cout << "\n\t\tSorry! You have tried to enter a date in the past. Please try again." << endl;

        cout << "\n\t\tPlease enter the date of this trip in the following format... (no inputs starting with 0)" << endl;
        cout << "\t\tDay   (dd)    : ";
        cin >> newTrip.tripDate[0];
        cout << "\t\tMonth (mm)    : ";
        cin >> newTrip.tripDate[1];
        cout << "\t\tYear  (yyyy)  : ";
        cin >> newTrip.tripDate[2];

        // Check if the user is attempting to book a trip in the past, starting with the year:
        if (newTrip.tripDate[2] < dt->tm_year + 1900)
        {
            inThePast = true;
        }
        // Check the month:
        else if (newTrip.tripDate[2] == dt->tm_year + 1900 && newTrip.tripDate[1] < dt->tm_mon + 1)
        {
            inThePast = true;
        }
        // Check the day:
        else if (newTrip.tripDate[2] == dt->tm_year + 1900 && newTrip.tripDate[1] == dt->tm_mon + 1 && newTrip.tripDate[0] < dt->tm_mday)
        {
            inThePast = true;
        }
        else
        {
            inThePast = false;
        }
    }
    cout << "\n\t\tPlease enter the time you want to be picked up: ";
    cin.ignore();
    getline(cin, newTrip.time);
    cout << "\n\t\tPlease enter the number of people travelling: ";
    cin >> newTrip.noOfPeople;
    cout << "\n\t\tDo you need any extra support?" << endl;
    cout << "\t\tPlease specify: ";
    cin.ignore();
    getline(cin, newTrip.extraSupport);
    cout << "\n\t\tDo you have any luggage?" << endl;
    cout << "\t\tPlease specify if it is normal, " << endl;
    cout << "\t\tlarge and / or heavy: ";
    getline(cin, newTrip.luggage);

    // Set the current payment status:
    newTrip.paymentStatus = false;

    // Confirm the trip's cost:
    newTrip.cost = *baseFarePtr + (*costPerKmPtr * distanceTravelled);

    // Generate the bill:
    billScreen(newTrip, distanceTravelled);

    // Ask the user if they want to confirm payment or cancel:
    cout << "\n\t\tWould you like to confirm payment (type: 1) or cancel (type: 2)? ";
    cin >> confirmOrCancel;

    // Handle the input:
    if (confirmOrCancel == 1)
    {
        /* Generate a new trip number.
         * If there isn't a tripNumberGenerator file yet,
         * make one, and make the first trip number 0
         * (it will soon be changed to 1).
         */
        tripNumberGenerator.open("tripNumberGenerator.txt", ios::out | ios::_Noreplace);

        tripNumberGenerator << 0;

        tripNumberGenerator.close();

        // Read the file, and update its number by adding 1:
        tripNumberGenerator.open("tripNumberGenerator.txt", ios::in);

        while (getline(tripNumberGenerator, oneLine))
        {
            generatedTripNumber = stoi(oneLine);
        }
        generatedTripNumber++;

        // Close the file:
        tripNumberGenerator.close();

        // Open the file again in order to rewrite it with its new number:
        tripNumberGenerator.open("tripNumberGenerator.txt", ios::out);

        tripNumberGenerator << generatedTripNumber;

        // Close the file:
        tripNumberGenerator.close();

        // Update the current struct instance:
        newTrip.tripNumber = generatedTripNumber;

        // Thank the user for confirming payment:
        cout << "\n\t\tThank you for confirming payment, enjoy your trip~!!!" << endl << endl;

        // Update the payment status:
        newTrip.paymentStatus = true;

        // Show the bill again and that it is paid:
        billScreen(newTrip, distanceTravelled);

        // Write to the tripData file:
        tripData.open("tripData.txt", ios::out | ios::app);

        tripData << newTrip.tripNumber << endl;
        tripData << newTrip.customerName << endl;
        tripData << newTrip.customerContactNumber << endl;
        tripData << newTrip.startingPlace << endl;
        tripData << newTrip.destination << endl;
        tripData << newTrip.tripDate[0] << endl;
        tripData << newTrip.tripDate[1] << endl;
        tripData << newTrip.tripDate[2] << endl;
        tripData << newTrip.time << endl;
        tripData << newTrip.noOfPeople << endl;
        tripData << newTrip.extraSupport << endl;
        tripData << newTrip.luggage << endl;
        tripData << newTrip.visaCardNumber << endl;
        tripData << newTrip.cardExpiry << endl;
        tripData << newTrip.cardCVC << endl;
        if (newTrip.paymentStatus == true)
        {
            tripData << "true" << endl;
        }
        else if (newTrip.paymentStatus == false)
        {
            tripData << "false" << endl;
        }
        tripData << newTrip.cost << endl;
        if (newTrip.available == true)
        {
            tripData << "true" << endl;
        }
        else if (newTrip.available == false)
        {
            tripData << "false" << endl;
        }
        tripData << "-----End of item-----" << endl;

        // Close the file:
        tripData.close();
    }
    else if (confirmOrCancel == 2)
    {
        cout << "\n\t\tTrip Cancelled." << endl << endl;

        // Send the user back to the customer screen:
        customerScreen();
    }
    else
    {
        // Deal with invalid inputs:
        while (confirmOrCancel != 1 && confirmOrCancel != 2)
        {
            cout << "\n\t\tSorry! Invalid input. Please type 1 or 2: ";
            cin >> confirmOrCancel;
        }
        // Once the input is valid, act on it:
        if (confirmOrCancel == 1)
        {
            /* Generate a new trip number.
             * If there isn't a tripNumberGenerator file yet,
             * make one, and make the first trip number 0
             * (it will soon be changed to 1).
             */
            tripNumberGenerator.open("tripNumberGenerator.txt", ios::out | ios::_Noreplace);

            tripNumberGenerator << 0;

            tripNumberGenerator.close();

            // Read the file, and update its number by adding 1:
            tripNumberGenerator.open("tripNumberGenerator.txt", ios::in);

            while (getline(tripNumberGenerator, oneLine))
            {
                generatedTripNumber = stoi(oneLine);
            }
            generatedTripNumber++;

            // Close the file:
            tripNumberGenerator.close();

            // Open the file again in order to rewrite it with its new number:
            tripNumberGenerator.open("tripNumberGenerator.txt", ios::out);

            tripNumberGenerator << generatedTripNumber;

            // Close the file:
            tripNumberGenerator.close();

            // Update the current struct instance:
            newTrip.tripNumber = generatedTripNumber;

            // Thank the user for confirming payment:
            cout << "\n\t\tThank you for confirming payment, enjoy your trip~!!!" << endl << endl;

            // Update the payment status:
            newTrip.paymentStatus = true;

            // Show the bill again and that it is paid:
            billScreen(newTrip, distanceTravelled);

            // Write to the tripData file:
            tripData.open("tripData.txt", ios::out | ios::app);

            tripData << newTrip.tripNumber << endl;
            tripData << newTrip.customerName << endl;
            tripData << newTrip.customerContactNumber << endl;
            tripData << newTrip.startingPlace << endl;
            tripData << newTrip.destination << endl;
            tripData << newTrip.tripDate[0] << endl;
            tripData << newTrip.tripDate[1] << endl;
            tripData << newTrip.tripDate[2] << endl;
            tripData << newTrip.time << endl;
            tripData << newTrip.noOfPeople << endl;
            tripData << newTrip.extraSupport << endl;
            tripData << newTrip.luggage << endl;
            tripData << newTrip.visaCardNumber << endl;
            tripData << newTrip.cardExpiry << endl;
            tripData << newTrip.cardCVC << endl;
            if (newTrip.paymentStatus == true)
            {
                tripData << "true" << endl;
            }
            else if (newTrip.paymentStatus == false)
            {
                tripData << "false" << endl;
            }
            tripData << newTrip.cost << endl;
            if (newTrip.available == true)
            {
                tripData << "true" << endl;
            }
            else if (newTrip.available == false)
            {
                tripData << "false" << endl;
            }
            tripData << "-----End of item-----" << endl;

            // Close the file:
            tripData.close();
        }
        else if (confirmOrCancel == 2)
        {
            cout << "\n\t\tTrip Cancelled." << endl << endl;

            // Send the user back to the customer screen:
            customerScreen();
        }
    }
    // Preventing missed inputs:
    cin.ignore();

    // Ask the user if they want to book another trip:
    cout << "\n\t\tDo you want to book another trip? y / n: ";
    getline(cin, bookAnother);

    // Act on the input:
    if (bookAnother == "y")
    {
        tripBooking();
    }
    else if (bookAnother == "n")
    {
        // Back to the customer screen:
        customerScreen();
    }
    else
    {
        // Handle invalid inputs:
        while (bookAnother != "y" && bookAnother != "n")
        {
            cout << "\n\t\tSorry! Invalid input. Please type y or n: ";
            getline(cin, bookAnother);
        }
        // Once valid...
        if (bookAnother == "y")
        {
            tripBooking();
        }
        else if (bookAnother == "n")
        {
            // Back to the customer screen:
            customerScreen();
        }
    }
}

void billScreen(Trips trip, int distance)
{
    // Heading Image:
    cout << "\n\n\t\t___________________________________________________" << endl << endl;
    cout << "\t\t---------------------------------------------------" << endl;
    cout << "\t\t___________________________________________________" << endl << endl;

    cout << "\n\t\t\tBill For " << trip.customerName << endl << endl << endl;

    // Trip Details:
    cout << "\t\t\t|| Trip Details ||" << endl << endl;
    cout << "\t\tTrip Date       : " << trip.tripDate[0] << "/" << trip.tripDate[1] << "/" << trip.tripDate[2] << endl;
    cout << "\t\tTrip Time       : " << trip.time << endl;
    cout << "\t\tStarting Place  : " << trip.startingPlace << endl;
    cout << "\t\tDestination     : " << trip.destination << endl << endl << endl << endl;

    // Bill Breakdown:
    cout << "\t\t\t|| Bill Breakdown ||" << endl << endl;
    cout << "\t\tBase Fare       : $" << *baseFarePtr << endl;
    cout << "\t\tCost Per Km     : $" << *costPerKmPtr << endl;
    cout << "\t\tTravel Distance :  " << distance << endl;
    cout << "\t\tTotal Cost      : $" << trip.cost << endl << endl;
    cout << "\t\tPayment Status  : ";

    // Check the payment status and display it:
    if (trip.paymentStatus == true)
    {
        cout << "Paid" << endl << endl;
    }
    else if (trip.paymentStatus == false)
    {
        cout << "Pending Payment" << endl << endl;
    }

    // ASCII Road:
    cout << "\t\t___________________________________________________" << endl << endl;
    cout << "\t\t---------------------------------------------------" << endl;
    cout << "\t\t___________________________________________________" << endl << endl;
}

void tripCancellation()
{
    // Header Section:
    cout << "\n\n\t\t___________________________________________________" << endl << endl;
    cout << "\t\t---------------------------------------------------" << endl;
    cout << "\t\t___________________________________________________" << endl << endl;

    cout << "\n\t\t\tTrip Cancellation" << endl << endl << endl;

    // Local Variables:
    int counter = 0;
    int emailLineForCancellation = 0;
    int* emailLineForCancellationPtr = &emailLineForCancellation;
    int tripFoundIndex = 0;
    int multiplyNineteen = 0;
    int multiplyEight = 0;
    bool tripFound = false;
    bool dateValid;
    string line;
    string fullName;
    string tripNotFoundOption;
    string tripInPastOption;
    string cancelAnother;
    string noneToCancel;
    vector<int>fullNameLines;
    vector<Trips>preCancellationVector;
    vector<Trips>wholeFileVector;
    vector<ClaimedTrips>wholeFileVector2;

    // Allow us to use time:
    time_t now = time(0);
    struct  tm* dt = localtime(&now);

    // Start by showing the user their trips:
    cout << "\t\t\t|| Your Booked Trips ||" << endl << endl;

    /* First we need to find out the user's full name.
     * Open the customerData file and look for the currently logged in user's email address.
     */
    customerData.open("customerData.txt", ios::in);

    while (getline(customerData, line))
    {
        // Count the lines being read:
        counter++;

        // Look for the email address:
        if (line == *customerEmailLogInPtr)
        {
            // Record its position:
            *emailLineForCancellationPtr = counter;
        }
    }
    // Close the file:
    customerData.close();

    // Reset the counter:
    counter = 0;

    // Re-open the file:
    customerData.open("customerData.txt", ios::in);

    while (getline(customerData, line))
    {
        // Count the lines being read:
        counter++;

        // Look for the customer's name, 6 lines up from the email:
        if (counter == (*emailLineForCancellationPtr - 6))
        {
            fullName = line;
        }
    }
    // Close the file:
    customerData.close();

    // Reset the counter:
    counter = 0;

    // Now open the tripData file and look for the name:
    tripData.open("tripData.txt", ios::in);

    while (getline(tripData, line))
    {
        // Count lines:
        counter++;

        // Look for the name and record its position/s in a vector:
        if (line == fullName)
        {
            fullNameLines.push_back(counter);
        }
    }
    // Close the file:
    tripData.close();

    // Reset line counter:
    counter = 0;

    // If the full name was not found, tell the user this and send them back:
    if (fullNameLines.size() == 0)
    {
        cout << "\n\t\tIt looks like you have no trips to cancel!" << endl << endl;

        cout << "\t\tEnter any key to continue... ";
        getline(cin, noneToCancel);

        // Send the user back to their Customer Screen:
        customerScreen();
    }

    // Create a temporary instance of the Trips structure:
    Trips *newTrip = new Trips;

    // Re-open the tripData file and read its lines:
    tripData.open("tripData.txt", ios::in);

    while (getline(tripData, line))
    {
        // Count lines:
        counter++;

        // Go through the vector to obtain each section:
        for (int i = 0; i < fullNameLines.size(); i++)
        {
            // For each first line:
            if (counter == fullNameLines[i] - 1)
            {
                newTrip->tripNumber = stoi(line);
            }
            // For each second line:
            else if (counter == fullNameLines[i])
            {
                newTrip->customerName = line;
            }
            // For each third line:
            else if (counter == fullNameLines[i] + 1)
            {
                newTrip->customerContactNumber = line;
            }
            // For each fourth line:
            else if (counter == fullNameLines[i] + 2)
            {
                newTrip->startingPlace = line;
            }
            // For each fifth line:
            else if (counter == fullNameLines[i] + 3)
            {
                newTrip->destination = line;
            }
            // For each sixth line:
            else if (counter == fullNameLines[i] + 4)
            {
                newTrip->tripDate[0] = stoi(line);
            }
            // For each seventh line:
            else if (counter == fullNameLines[i] + 5)
            {
                newTrip->tripDate[1] = stoi(line);
            }
            // For each eighth line:
            else if (counter == fullNameLines[i] + 6)
            {
                newTrip->tripDate[2] = stoi(line);
            }
            // For each ninth line:
            else if (counter == fullNameLines[i] + 7)
            {
                newTrip->time = line;
            }
            // For each tenth line:
            else if (counter == fullNameLines[i] + 8)
            {
                newTrip->noOfPeople = stoi(line);
            }
            // For each eleventh line:
            else if (counter == fullNameLines[i] + 9)
            {
                newTrip->extraSupport = line;
            }
            // For each twelth line:
            else if (counter == fullNameLines[i] + 10)
            {
                newTrip->luggage = line;
            }
            // For every thirteenth line:
            else if (counter == fullNameLines[i] + 11)
            {
                newTrip->visaCardNumber = line;
            }
            // For every fourteenth line:
            else if (counter == fullNameLines[i] + 12)
            {
                newTrip->cardExpiry = line;
            }
            // For every fifteenth line:
            else if (counter == fullNameLines[i] + 13)
            {
                newTrip->cardCVC = line;
            }
            // For every sixteenth line:
            else if (counter == fullNameLines[i] + 14)
            {
                if (line == "true")
                {
                    newTrip->paymentStatus = true;
                }
                else if (line == "false")
                {
                    newTrip->paymentStatus = false;
                }
            }
            // For every seventeenth line:
            else if (counter == fullNameLines[i] + 15)
            {
                newTrip->cost = stod(line);
            }
            // For every eighteenth line:
            else if (counter == fullNameLines[i] + 16)
            {
                if (line == "true")
                {
                    newTrip->available = true;
                }
                else if (line == "false")
                {
                    newTrip->available = false;
                }
            }
            // For every nineteenth line:
            else if (counter == fullNameLines[i] + 17)
            {
                // Add the instance to a vector:
                preCancellationVector.push_back(*newTrip);

                // Create a new instance:
                Trips *newTrip = new Trips;
            }
        }
    }
    // Close the file:
    tripData.close();

    // Add the last instance to the vector:
    preCancellationVector.push_back(*newTrip);

    // Then delete the last instance, as it will be empty:
    preCancellationVector.pop_back();

    // Reset the counter:
    counter = 0;

    // Now print some of the details of the user's trips:
    for (int i = 0; i < preCancellationVector.size(); i++)
    {
        cout << "\t\tTrip Number     : " << preCancellationVector[i].tripNumber << endl;
        cout << "\t\tStarting Place  : " << preCancellationVector[i].startingPlace << endl;
        cout << "\t\tDestination     : " << preCancellationVector[i].destination << endl;
        cout << "\t\tTrip Date       : " << preCancellationVector[i].tripDate[0] << "/" << preCancellationVector[i].tripDate[1] << "/" << preCancellationVector[i].tripDate[2] << endl;
        cout << "\t\tTrip Time       : " << preCancellationVector[i].time << endl;
        cout << "\t\tPayment Status  : ";
        if (preCancellationVector[i].paymentStatus == true)
        {
            cout << "Paid" << endl;
        }
        else if (preCancellationVector[i].paymentStatus == false)
        {
            cout << "Not Yet Paid" << endl;
        }
        cout << "\t\tCost            : " << preCancellationVector[i].cost << endl;

        // Leave a blank line before the next trip:
        cout << endl;
    }

    // Ask the user which trip they want to cancel:
    cout << "\t\tWhich trip would you like to cancel? Trip no. ";
    cin >> *tripToCancelPtr;

    // Check if this trip is one of the user's booked trips:
    for (int i = 0; i < preCancellationVector.size(); i++)
    {
        if (preCancellationVector[i].tripNumber == *tripToCancelPtr)
        {
            tripFound = true;

            // Record the index position:
            tripFoundIndex = i;
        }
    }

    // If the trip isn't found, tell the user this:
    if (tripFound == false)
    {
        cout << "\n\t\tSorry! That trip wasn't found. Do you want to try again? y / n : ";
        getline(cin, tripNotFoundOption);

        // Act on input:
        if (tripNotFoundOption == "y")
        {
            // Clean up the data first:
            fullNameLines.clear();
            preCancellationVector.clear();
            delete newTrip;

            tripCancellation();
        }
        else if (tripNotFoundOption == "n")
        {
            // Clean up the data first:
            fullNameLines.clear();
            preCancellationVector.clear();
            delete newTrip;

            // Back to the customer screen:
            customerScreen();
        }
        // Deal with invalid inputs:
        while (tripNotFoundOption != "y" && tripNotFoundOption != "n")
        {
            cout << "\n\t\tSorry! Invalid input. Please type y or n: ";
            getline(cin, tripNotFoundOption);
        }
        // Act on input, once valid:
        if (tripNotFoundOption == "y")
        {
            // Clean up the data first:
            fullNameLines.clear();
            preCancellationVector.clear();
            delete newTrip;

            tripCancellation();
        }
        else if (tripNotFoundOption == "n")
        {
            // Clean up the data first:
            fullNameLines.clear();
            preCancellationVector.clear();
            delete newTrip;

            // Back to the customer screen:
            customerScreen();
        }
    }
    /* If tripFound isn't false, we still need to check if it is in the past, 
     * since we don't want users to be able to cancel past trips.
     * First check the year.
     */
    if (preCancellationVector[tripFoundIndex].tripDate[2] < (dt->tm_year + 1900))
    {
        dateValid = false;
    }
    // Check the month:
    else if (preCancellationVector[tripFoundIndex].tripDate[2] == (dt->tm_year + 1900) && 
             preCancellationVector[tripFoundIndex].tripDate[1] < (dt->tm_mon + 1))
    {
        dateValid = false;
    }
    // Check the day:
    else if (preCancellationVector[tripFoundIndex].tripDate[2] == (dt->tm_year + 1900) &&
             preCancellationVector[tripFoundIndex].tripDate[1] == (dt->tm_mon + 1) &&
             preCancellationVector[tripFoundIndex].tripDate[0] < (dt->tm_mday))
    {
        dateValid = false;
    }
    else
    {
        dateValid = true;
    }
    // If the date is valid, past is false:
    if (dateValid == true)
    {
        preCancellationVector[tripFoundIndex].past = false;
    }
    else
    {
        preCancellationVector[tripFoundIndex].past = true;
    }

    // If the trip is in the past, tell the user this:
    if (preCancellationVector[tripFoundIndex].past == true)
    {
        cout << "\n\t\tSorry! You cannot cancel past trips. Do you want to cancel a different trip? y / n : ";
        getline(cin, tripInPastOption);

        // Act on input:
        if (tripInPastOption == "y")
        {
            // Clean up the data first:
            fullNameLines.clear();
            preCancellationVector.clear();

            tripCancellation();
        }
        else if (tripInPastOption == "n")
        {
            // Clean up the data first:
            fullNameLines.clear();
            preCancellationVector.clear();

            // Back to the customer screen:
            customerScreen();
        }
        else
        {
            // Deal with invalid inputs:
            while (tripInPastOption != "y" && tripInPastOption != "n")
            {
                cout << "\n\t\tSorry! Invalid input. Please type y or n: ";
                getline(cin, tripInPastOption);
            }
            // Once valid, act on it:
            if (tripInPastOption == "y")
            {
                // Clean up the data first:
                fullNameLines.clear();
                preCancellationVector.clear();

                tripCancellation();
            }
            else if (tripInPastOption == "n")
            {
                // Clean up the data first:
                fullNameLines.clear();
                preCancellationVector.clear();

                // Back to the customer screen:
                customerScreen();
            }
        }
    }

    // Reset line counter:
    counter = 0;

    // Create a temporary instance of the Trips structure:
    Trips* tripStored = new Trips;

    // If the trip isn't in the past, cancel it:
    tripData.open("tripData.txt", ios::in);

    /* First, we need to read every single line in the tripData file,
     * and assign it to a vector.
     */
    while (getline(tripData, line))
    {
        // Count the lines being read:
        counter++;

        // For every first line:
        if (counter == (multiplyNineteen * 19) + 1)
        {
            tripStored->tripNumber = stoi(line);
        }
        // For every second line:
        else if (counter == (multiplyNineteen * 19) + 2)
        {
            tripStored->customerName = line;
        }
        // For every third line:
        else if (counter == (multiplyNineteen * 19) + 3)
        {
            tripStored->customerContactNumber = line;
        }
        // For every fourth line:
        else if (counter == (multiplyNineteen * 19) + 4)
        {
            tripStored->startingPlace = line;
        }
        // For every fifth line:
        else if (counter == (multiplyNineteen * 19) + 5)
        {
            tripStored->destination = line;
        }
        // For every sixth line:
        else if (counter == (multiplyNineteen * 19) + 6)
        {
            tripStored->tripDate[0] = stoi(line);
        }
        // For every seventh line:
        else if (counter == (multiplyNineteen * 19) + 7)
        {
            tripStored->tripDate[1] = stoi(line);
        }
        // For every eighth line:
        else if (counter == (multiplyNineteen * 19) + 8)
        {
            tripStored->tripDate[2] = stoi(line);
        }
        // For every ninth line:
        else if (counter == (multiplyNineteen * 19) + 9)
        {
            tripStored->time = line;
        }
        // For every tenth line:
        else if (counter == (multiplyNineteen * 19) + 10)
        {
            tripStored->noOfPeople = stoi(line);
        }
        // For every eleventh line:
        else if (counter == (multiplyNineteen * 19) + 11)
        {
            tripStored->extraSupport = line;
        }
        // For every twelth line:
        else if (counter == (multiplyNineteen * 19) + 12)
        {
            tripStored->luggage = line;
        }
        // For every thirteenth line:
        else if (counter == (multiplyNineteen * 19) + 13)
        {
            tripStored->visaCardNumber = line;
        }
        // For every fourteenth line:
        else if (counter == (multiplyNineteen * 19) + 14)
        {
            tripStored->cardExpiry = line;
        }
        // For every fifteenth line:
        else if (counter == (multiplyNineteen * 19) + 15)
        {
            tripStored->cardCVC = line;
        }
        // For every sixteenth line:
        else if (counter == (multiplyNineteen * 19) + 16)
        {
            if (line == "true")
            {
                tripStored->paymentStatus = true;
            }
            else if (line == "false")
            {
                tripStored->paymentStatus = false;
            }
        }
        // For every seventeenth line:
        else if (counter == (multiplyNineteen * 19) + 17)
        {
            tripStored->cost = stod(line);
        }
        // For every eighteenth line:
        else if (counter == (multiplyNineteen * 19) + 18)
        {
            if (line == "true")
            {
                tripStored->available = true;
            }
            else if (line == "false")
            {
                tripStored->available = false;
            }
        }
        // For every nineteenth line:
        else if (counter == (multiplyNineteen * 19) + 19)
        {
            // Add the instance to the vector:
            wholeFileVector.push_back(*tripStored);

            // Update the multiplication counter:
            multiplyNineteen++;

            // Create a new trip instance:
            Trips* tripStored = new Trips;
        }
    }
    // Close the file:
    tripData.close();

    // Add the last instance to the vector:
    wholeFileVector.push_back(*tripStored);

    // Then delete the last instance, as it will be empty:
    wholeFileVector.pop_back();

    // Reset the counter:
    counter = 0;

    // Reset multiplication:
    multiplyNineteen = 0;

    // Now re-write the file:
    tripData.open("tripData.txt", ios::out);

    for (int i = 0; i < wholeFileVector.size(); i++)
    {
        // Only add the items that aren't being cancelled:
        if (wholeFileVector[i].tripNumber == *tripToCancelPtr)
        {
            continue;
        }
        else
        {
            tripData << wholeFileVector[i].tripNumber << endl;
            tripData << wholeFileVector[i].customerName << endl;
            tripData << wholeFileVector[i].customerContactNumber << endl;
            tripData << wholeFileVector[i].startingPlace << endl;
            tripData << wholeFileVector[i].destination << endl;
            tripData << wholeFileVector[i].tripDate[0] << endl;
            tripData << wholeFileVector[i].tripDate[1] << endl;
            tripData << wholeFileVector[i].tripDate[2] << endl;
            tripData << wholeFileVector[i].time << endl;
            tripData << wholeFileVector[i].noOfPeople << endl;
            tripData << wholeFileVector[i].extraSupport << endl;
            tripData << wholeFileVector[i].luggage << endl;
            tripData << wholeFileVector[i].visaCardNumber << endl;
            tripData << wholeFileVector[i].cardExpiry << endl;
            tripData << wholeFileVector[i].cardCVC << endl;
            if (wholeFileVector[i].paymentStatus == true)
            {
                tripData << "true" << endl;
            }
            else if (wholeFileVector[i].paymentStatus == false)
            {
                tripData << "false" << endl;
            }
            tripData << wholeFileVector[i].cost << endl;
            if (wholeFileVector[i].available == true)
            {
                tripData << "true" << endl;
            }
            else if (wholeFileVector[i].available == false)
            {
                tripData << "false" << endl;
            }
            tripData << "-----End of item-----" << endl;
        }
    }
    // Close the file:
    tripData.close();

    // Also delete this trip in the driverActivityData file:
    driverActivityData.open("driverActivityData.txt", ios::in);

    // Create a new instance of the claimed trips structure:
    ClaimedTrips* deletedClaim = new ClaimedTrips;

    // First, store every line in a vector:
    while (getline(driverActivityData, line))
    {
        // Count the lines:
        counter++;

        // For every first line:
        if (counter == (multiplyEight * 8) + 1)
        {
            deletedClaim->tripNumber = stoi(line);
        }
        // For every second line:
        else if (counter == (multiplyEight * 8) + 2)
        {
            deletedClaim->emailAddress = line;
        }
        // For every third line:
        else if (counter == (multiplyEight * 8) + 3)
        {
            deletedClaim->day = stoi(line);
        }
        // For every fourth line:
        else if (counter == (multiplyEight * 8) + 4)
        {
            deletedClaim->month = stoi(line);
        }
        // For every fifth line:
        else if (counter == (multiplyEight * 8) + 5)
        {
            deletedClaim->year = stoi(line);
        }
        // For every sixth line:
        else if (counter == (multiplyEight * 8) + 6)
        {
            deletedClaim->time = line;
        }
        // For every seventh line:
        else if (counter == (multiplyEight * 8) + 7)
        {
            deletedClaim->cost = stod(line);
        }
        // For every eighth line:
        else if (counter == (multiplyEight * 8) + 8)
        {
            // Increase multiplyEight:
            multiplyEight++;

            // Add the instance to the vector:
            wholeFileVector2.push_back(*deletedClaim);

            // Create a new instance:
            ClaimedTrips* deletedClaim = new ClaimedTrips;
        }
    }
    // Close the file:
    driverActivityData.close();

    // Add the last instance to the vector:
    wholeFileVector2.push_back(*deletedClaim);

    // Then remove it:
    wholeFileVector2.pop_back();

    // Now re-print the driverActivityData file:
    driverActivityData.open("driverActivityData.txt", ios::out);

    for (int i = 0; i < wholeFileVector2.size(); i++)
    {
        // Skip printing if the trip number is the one to be deleted:
        if (wholeFileVector2[i].tripNumber == *tripToCancelPtr)
        {
            continue;
        }
        else
        {
            driverActivityData << wholeFileVector2[i].tripNumber << endl;
            driverActivityData << wholeFileVector2[i].emailAddress << endl;
            driverActivityData << wholeFileVector2[i].day << endl;
            driverActivityData << wholeFileVector2[i].month << endl;
            driverActivityData << wholeFileVector2[i].year << endl;
            driverActivityData << wholeFileVector2[i].time << endl;
            driverActivityData << wholeFileVector2[i].cost << endl;
            driverActivityData << "-----End of item-----" << endl;
        }
    }
    // Close the file:
    driverActivityData.close();

    // Reset the two counters:
    counter = 0;
    multiplyEight = 0;

    // Clear the vector and delete spare instances:
    wholeFileVector2.clear();
    delete deletedClaim;

    // Record this cancellation in the tripCancellations file:
    tripCancellations.open("tripCancellations.txt", ios::out | ios::app);

    // Today's date:
    tripCancellations << dt->tm_mday << endl;
    tripCancellations << dt->tm_mon + 1 << endl;
    tripCancellations << dt->tm_year + 1900 << endl;

    // And an end marker:
    tripCancellations << "-----End of item-----" << endl;

    // Close the file:
    tripCancellations.close();

    // Clear the vector:
    wholeFileVector.clear();

    // Delete spare instances:
    delete tripStored;

    // Fix missed inputs bug:
    cin.ignore();

    // Ask the user what they want to do now:
    cout << "\n\n\t\tTrip cancelled!" << endl;
    cout << "\t\tWould you like to cancel another trip ? y / n : ";
    getline(cin, cancelAnother);

    // Act on this input:
    if (cancelAnother == "y")
    {
        tripCancellation();
    }
    else if (cancelAnother == "n")
    {
        // Back to the customer screen:
        customerScreen();
    }
    else
    {
        // Deal with unexpected inputs:
        while (cancelAnother != "y" && cancelAnother != "n")
        {
            cout << "\n\n\t\tSorry! Invalid input. Please type y or n: ";
            getline(cin, cancelAnother);
        }
        // Once the input is valid, act on it:
        if (cancelAnother == "y")
        {
            tripCancellation();
        }
        else if (cancelAnother == "n")
        {
            // Back to the customer screen:
            customerScreen();
        }
    }
}

// Driver LogIn Function:
void driverLogIn()
{
    // Header Section:
    cout << "\t\t___________________________________________________" << endl << endl;
    cout << "\t\t---------------------------------------------------" << endl;
    cout << "\t\t___________________________________________________" << endl << endl;

    cout << "\n\t\t\tDriver LogIn" << endl << endl << endl;

    // Fix the missed inputs issue:
    cin.ignore();

    // Obtain the login details:
    cout << "\t\tPlease enter your email address: ";
    getline(cin, *driverEmailLogInPtr);
    cout << "\t\tPlease enter your password: ";
    getline(cin, *driverPasswordPtr);

    // Set login attempts to 0:
    driverLogInAttempts = 0;

    // Open and search driverData.txt for these details:
    driverData.open("driverData.txt", ios::in);

    // Set driverEmailLine to NULL:
    *driverEmailLinePtr = NULL;

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
                    cout << "\n\t\tSorry. Incorrect password! Please try again after 10 seconds." << endl;

                    // Create a timer for 1 minute:
                    using namespace std::chrono_literals;
                    std::cout << "\n\t\tWaiting...\n" << std::flush;
                    auto start = std::chrono::high_resolution_clock::now();
                    std::this_thread::sleep_for(10000ms);
                    auto end = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double, std::milli> elapsed = end - start;

                    // After the timer is done, let them try again:
                    cout << "\n\t\tPlease enter your password: ";
                    getline(cin, *driverPasswordPtr);
                    driverLogInAttempts++;
                }
                /* If the password entered is incorrect, tell the user this,
                 * as well as how many attempts they have left to make:
                 */
                if (*driverPasswordPtr != driverLine)
                {
                    cout << "\n\t\tSorry. Incorrect password! Please try again." << endl;
                    cout << "\t\tPlease enter your password: ";
                    getline(cin, *driverPasswordPtr);
                }
            }
            /* Once the password is correct...
             * Reset the lines being read to zero and close the file:
             */
            driverLinesCounter = 0;
            driverData.close();

            // Tell the user they have successfully logged in, and take them to the Driver Screen:
            cout << "\n\n\t\tLog in successful!" << endl;
            driverScreen(*driverEmailLogInPtr);
        }
        // Count the lines being read:
        driverLinesCounter++;
    }
    // Close the file:
    driverData.close();

    // If, after searching through the whole file, the email address entered is not found:
    if (*driverEmailLinePtr == NULL)
    {
        cout << "\n\t\tSorry. That email address was not found. Do you want to register (type: register)" << endl;
        cout << "\t\tor return to the home screen (type: home)? ";
        cin >> *driverEmailNotFoundPtr;

        // Make sure the input is valid:
        while (*driverEmailNotFoundPtr != "register" && *driverEmailNotFoundPtr != "home" && *driverEmailNotFoundPtr != "Register" && *driverEmailNotFoundPtr != "Home")
        {
            cout << "\n\t\tSorry. Invalid input. Please type register or home: ";
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
    cout << "\n\n\t\t___________________________________________________" << endl << endl;
    cout << "\t\t---------------------------------------------------" << endl;
    cout << "\t\t___________________________________________________" << endl << endl;

    cout << "\n\t\t\tEligibility Test" << endl << endl << endl;

    // Temporary Structure:
    Driver newDriver;

    // First check if the user is eligible to become a driver:
    // Check the licence status:
    cout << "\t\tWhat is the status of your licence? Please type: Learners, Restricted, or Full." << endl;
    cout << "\t\tLicence: ";
    cin >> *licenceStatusPtr;
    if (*licenceStatusPtr == "Full")
    {
        // Check the user's number of years of driving experience:
        cout << "\n\t\tHow many years of driving experience do you have?" << endl;
        cout << "\t\tYears of experience: ";
        cin >> *drivingExperiencePtr;
        if (*drivingExperiencePtr >= 2)
        {
            // Check how old the taxi's model is:
            cout << "\n\t\tHow old is your vehicle (in years)?" << endl;
            cout << "\t\tVehicle's age: ";
            cin >> *vehicleAgePtr;
            if (*vehicleAgePtr <= 10)
            {
                // Check the user's age:
                cout << "\n\t\tHow old are you?" << endl;
                cout << "\t\tAge: ";
                cin >> *driverAgePtr;
                if (*driverAgePtr > 21)
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
                    getline(cin, newDriver.fullName);
                    cout << "\t\tGender: ";
                    getline(cin, newDriver.gender);
                    cout << "\t\tDate of Birth (dd/mm/yyyy): ";
                    getline(cin, newDriver.dateOfBirth);
                    cout << "\t\tNationality: ";
                    getline(cin, newDriver.nationality);
                    cout << "\t\tContact Number: ";
                    getline(cin, newDriver.contactNumber);
                    cout << "\t\tPostal Address: ";
                    getline(cin, newDriver.postalAddress);

                    cout << "\n\n\n\t\t\t|| Driving & Vehicle Details ||" << endl << endl;
                    cout << "\t\tLicence Number: ";
                    getline(cin, newDriver.licenceNumber);
                    cout << "\t\tLicence Expiry Date (dd/mm/yyyy): ";
                    getline(cin, newDriver.licenceExpiry);
                    newDriver.drivingExperience = *drivingExperiencePtr;
                    cout << "\t\tYears of Driving Experience: " << newDriver.drivingExperience << endl;
                    cout << "\t\tVehicle Registration Number: ";
                    getline(cin, newDriver.vehicleRegistrationNumber);
                    cout << "\t\tVehicle Model: ";
                    getline(cin, newDriver.vehicleModel);
                    cout << "\t\tWOF Expiry Date: ";
                    getline(cin, newDriver.wofExpiryDate);

                    cout << "\n\n\n\t\t\t|| Payment Information ||" << endl << endl;
                    cout << "\t\tBank Name: ";
                    getline(cin, newDriver.bankName);
                    cout << "\t\tBank Account Number: ";
                    getline(cin, newDriver.bankAccountNumber);

                    cout << "\n\n\n\t\t\t|| Account LogIn Information ||" << endl << endl;
                    cout << "\t\tEmail Address: ";
                    getline(cin, newDriver.emailAddress);
                    cout << "\t\tCreate a Password: ";
                    getline(cin, newDriver.password1);
                    cout << "\t\tRe-enter Your Password: ";
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
                            cout << "\n\t\tError. The passwords you have entered do not match." << endl;
                            cout << "\t\tPlease try again." << endl << endl << endl;

                            cout << "\t\tCreate a Password: ";
                            getline(cin, newDriver.password1);
                            cout << "\t\tRe-enter Your Password: ";
                            getline(cin, newDriver.password2);
                        }
                        // Once they do match, confirm:
                        newDriver.passwordConfirmed = newDriver.password1;
                    }

                    // Endorsement Section:
                    cout << endl << endl << endl;
                    cout << "\t\t___________________________________________________" << endl << endl;
                    cout << "\t\t---------------------------------------------------" << endl;
                    cout << "\t\t___________________________________________________" << endl << endl;

                    cout << "\n\t\t\tEndorsement" << endl << endl << endl;

                    // Assign an endorsement number:
                    cout << "\t\tYour Endorsement Number: " << newDriver.endorsementNumber << endl;

                    // Ask if the user if they want a 1 year P endorsement or a 5 year one:
                    cout << "\n\t\tDo you want this endorsement to last 1 year or 5 years?" << endl;
                    cout << "\t\tLongevity of P Endorsement: ";
                    cin >> *pLongevityPtr;

                    // Make sure P Logevity is 1 or 5:
                    while (*pLongevityPtr != 1 && *pLongevityPtr != 5)
                    {
                        cout << "\n\t\tSorry. You have entered an invalid option. Please enter 1 or 5." << endl;
                        cout << "\t\tLongevity of P Endorsement: ";
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
                    cout << "\n\n\t\tYour Endorsement Expiry Date (dd/mm/yyyy) is: " << newDriver.endorsementExpiry[0] << "/" << newDriver.endorsementExpiry[1] << "/" << newDriver.endorsementExpiry[2] << endl << endl;

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
                    driverScreen(newDriver.emailAddress);
                }
                else
                {
                    cout << "\n\t\tSorry! You are not eligible to drive for us at this time." << endl;
                    cout << "\t\tbut you are welcome to register once you are over 21 years old!" << endl << endl;
                    // Back to intro screen:
                    introFunction();
                }
            }
            else
            {
                cout << "\n\t\tSorry! You are not eligible to drive for us at this time," << endl;
                cout << "\t\tbut you are welcome to register with a vehicle that is ten or less years old!" << endl << endl;
                // Back to intro screen:
                introFunction();
            }
        }
        else
        {
            cout << "\n\t\tSorry! You are not eligible to drive for us at this time," << endl;
            cout << "\t\tbut you are welcome to register once you have been driving for at least 2 years!" << endl << endl;
            // Back to intro screen:
            introFunction();
        }
    }
    else
    {
        cout << "\n\t\tSorry! You are not eligible to drive for us at this time," << endl;
        cout << "\t\tbut you are welcome to register once you have your full licence!" << endl << endl;
        // Back to intro screen:
        introFunction();
    }
}

// Driver Logged In Screen Function:
void driverScreen(string myEmail)
{
    /* Header Section:
     * Taxi modified from a car ASCII image "MACHO 2020" by The Animator on animasci.com
     * License will be included with these programming files.
     */
    cout << endl << endl;
    cout << "\t\t                  ---" << endl;
    cout << "\t\t                  | |" << endl;
    cout << "\t\t                 ....." << endl;
    cout << "\t\t           , ,''  |    ```...___," << endl;
    cout << "\t\t    .--  ''  P(___|_______/    (|" << endl;
    cout << "\t\t  ( //            |             |" << endl;
    cout << "\t\t  ` ._: ' ' :_____|______: ' ' :/" << endl;
    cout << "\t\t      '  o  '            '  o  '" << endl;
    cout << "\t\t        - -                - - " << endl;
    cout << "\t\t______________________________________________" << endl;
    cout << "\t\t______________________________________________" << endl << endl;

    cout << "\n\t\t\tWelcome, Driver!" << endl << endl;

    // Payment Details Section:
    cout << "\n\t\t\t|| Payment Details ||" << endl << endl;

    // Create some local variables:
    string driverScreenLine;
    Driver loggedInDriver;
    int driverScreenLineCounter = 1;
    int emailLine = 0;
    int lineCount = 0;

    // Record the email address of the current user:
    loggedInDriver.emailAddress = myEmail;

    // Open the driverData.txt file to retrieve the email line:
    driverData.open("driverData.txt", ios::in);

    while (getline(driverData, driverScreenLine))
    {
        // Count the lines:
        lineCount++;

        // Look for the email address and record its position:
        if (driverScreenLine == loggedInDriver.emailAddress)
        {
            emailLine = lineCount;
        }
    }
    // Close the file:
    driverData.close();

    // Reset the counter:
    lineCount = 0;

    // Open the driverData.txt file to display the payment details:
    driverData.open("driverData.txt", ios::in);

    /* Look for the bank name and the bank account number,
     * 2 lines up and 1 line up from the email address respectively:
     */
    while (getline(driverData, driverScreenLine))
    {
        // Record the bank name:
        if (driverScreenLineCounter == (emailLine - 2))
        {
            loggedInDriver.bankName = driverScreenLine;
        }
        else if (driverScreenLineCounter == (emailLine - 1))
        {
            loggedInDriver.bankAccountNumber = driverScreenLine;
        }
        driverScreenLineCounter++;
    }

    // Close the file and print out the payment details:
    driverData.close();
    cout << "\t\tBank Name: " << loggedInDriver.bankName << endl;
    cout << "\t\tBank Account Number: " << loggedInDriver.bankAccountNumber << endl;

    bookedTripsDisplay();

    // Report Section:
    cout << "\n\n\t\t\t|| Daily Report ||" << endl << endl;

    time_t now = time(0);
    struct  tm* dt = localtime(&now);

    // To print out today's date...
    cout << "\t\t\tToday's Date: " << dt->tm_mday << "/" << dt->tm_mon + 1 << "/" << dt->tm_year + 1900 << endl << endl;

    // Create some local variables:
    int numberOfTripsToday = 0;
    int reportLinesCounter = 0;
    double sumOfCosts = 0;
    string activityLine;
    vector<ClaimedTrips>activityEmailLine;

    // Look for the current user's email address in the file containing claimed trips:
    driverActivityData.open("driverActivityData.txt", ios::in);
    while (getline(driverActivityData, activityLine))
    {
        // Count the lines being read:
        reportLinesCounter++;

        if (activityLine == loggedInDriver.emailAddress)
        {
            // Create a new instance for the struct array:
            ClaimedTrips* newTrip = new ClaimedTrips;

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
            else if (reportLinesCounter == i->emailLine + 5)
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
    cout << "\t\tYour Trips Today   : " << numberOfTripsToday << endl;

    // Print the total cost of trips today:
    cout << "\t\tTotal Earnings     : " << sumOfCosts << endl;

    /* My research has shown that taxi drivers in NZ earn an average of $42,423 a year,
     * making their tax rate ((10.5% of 14,000) + (17.5% of (42,423 - 14,000)) / 42,423) * 100 = 15.2%.
     * (((0.105 * 14000) + (0.175 * (42423 - 14000))) / 42423) * 100 = 15.2.
     */
    cout << "\t\tTax Amount         : " << sumOfCosts * 0.152 << endl << endl << endl;

    // Give the user some options to move forward:
    cout << "\t\tWould you like to claim a trip (type: 1), or log out (type: 2)? ";
    int claimOrLogOut;
    cin >> claimOrLogOut;

    // Acting on the user's input:
    if (claimOrLogOut == 1)
    {
        // Claim a trip:
        claimTrip(loggedInDriver.emailAddress);
    }
    else if (claimOrLogOut == 2)
    {
        cout << endl;

        // Delete the struct instances in the vector so as to avoid a memory leak:
        activityEmailLine.clear();

        // Send the user back to the starting screen:
        introFunction();
    }
    else
    {
        while (claimOrLogOut != 1 && claimOrLogOut != 2)
        {
            cout << "\n\t\tSorry! You have entered an invalid option. Please try again." << endl;
            cout << "\t\tWhat would you like to do? ";
            cin >> claimOrLogOut;
        }
        // Once the input is valid, act on it:
        if (claimOrLogOut == 1)
        {
            // Claim a trip:
            claimTrip(loggedInDriver.emailAddress);
        }
        else if (claimOrLogOut == 2)
        {
            cout << endl;

            // Delete the struct instances in the vector so as to avoid a memory leak:
            activityEmailLine.clear();

            // Send the user back to the starting screen:
            introFunction();
        }
    }
}

// Claim Trip Function:
void claimTrip(string myEmail)
{
    // Local Variables:
    string yesOrNo;
    string availability;
    string tripLine;
    int lineCount = 0;
    int counting = 0;
    int multiplyNineteen = 0;
    int toClaimLocation = 0;
    bool tripFound = false;
    vector<string>addClaim;
    vector<string>trips;

    cout << "\n\n\t\tWhich trip would you like to claim?" << endl;
    cout << "\t\tTrip Number: ";
    cin >> *tripToClaimPtr;

    // First check if this trip exists and isn't in the past:
    for (int i = 0; i < displayedTripNumbers.size(); i++)
    {
        // Look for the trip number in the displayed trips vector:
        if (*tripToClaimPtr == displayedTripNumbers[i])
        {
            tripFound = true;
        }
    }

    if (tripFound == true)
    {
        // Then the trip exists, and we now have to read it to see if it's available:
        tripData.open("tripData.txt", ios::in);

        /* We're looking for the availability, date, time, trip number and the cost----to be used in 
         * adding this trip to the claimed trips file (driverActivityData) if it isn't already there.
         */
        while (getline(tripData, tripLine))
        {
            counting++;

            // First, let's find the position of the trip number we want:
            if (counting == (multiplyNineteen * 19) + 1)
            {
                if (stoi(tripLine) == *tripToClaimPtr)
                {
                    // Record the position:
                    toClaimLocation = counting;
                }
            }
            else if (counting == (multiplyNineteen * 19) + 19)
            {
                // Increase the multiplication counter to get to the next item:
                multiplyNineteen++;
            }
        }
        // Close the file and reset the counters:
        tripData.close();
        counting = 0;
        multiplyNineteen = 0;

        // Re-open the file and grab the things we need:
        tripData.open("tripData.txt", ios::in);

        while (getline(tripData, tripLine))
        {
            // Count the lines:
            counting++;

            // Find the availability:
            if (counting == (toClaimLocation + 17))
            {
                availability = tripLine;
            }
            // Store the trip number:
            else if (counting == (toClaimLocation))
            {
                addClaim.push_back(tripLine);
            }
            // Store the email address:
            else if (counting == (toClaimLocation + 1))
            {
                addClaim.push_back(myEmail);
            }
            // Store the date in the addClaim vector, starting with the day:
            else if (counting == (toClaimLocation + 5))
            {
                addClaim.push_back(tripLine);
            }
            // Month:
            else if (counting == (toClaimLocation + 6))
            {
                addClaim.push_back(tripLine);
            }
            // Year:
            else if (counting == (toClaimLocation + 7))
            {
                addClaim.push_back(tripLine);
            }
            // Store the time:
            else if (counting == (toClaimLocation + 8))
            {
                addClaim.push_back(tripLine);
            }
            // Store the cost:
            else if (counting == (toClaimLocation + 16))
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

            // Add everything from the addClaim vector:
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
                if (counting == (toClaimLocation + 17))
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

            // Re-print the booked trips:
            bookedTripsDisplay();

            // Clear the vector:
            trips.clear();

            // Ask the user if they would like to claim another trip:
            cout << "\n\n\t\tWould you like to claim another trip (type y or n)? ";
            cin >> yesOrNo;

            if (yesOrNo == "y")
            {
                claimTrip(myEmail);
            }
            else if (yesOrNo == "n")
            {
                // Back to the driver screen:
                driverScreen(myEmail);
            }
            else
            {
                // Invalid input:
                while (yesOrNo != "y" && yesOrNo != "n")
                {
                    cout << "\n\t\tSorry! Invalid input. Please type y or n: ";
                    cin >> yesOrNo;
                }
                // When valid, check the input again:
                if (yesOrNo == "y")
                {
                    claimTrip(myEmail);
                }
                else if (yesOrNo == "n")
                {
                    driverScreen(myEmail);
                }
            }
        }
        else if (availability == "false")
        {
            // Clear the vector as we won't need it:
            addClaim.clear();

            cout << "\n\t\tSorry, that trip isn't available." << endl;
            cout << "\t\tWould you like to claim a different trip (type y or n)? ";
            cin >> yesOrNo;

            if (yesOrNo == "y")
            {
                claimTrip(myEmail);
            }
            else if (yesOrNo == "n")
            {
                // Back to the driver screen:
                driverScreen(myEmail);
            }
            else
            {
                // Invalid input:
                while (yesOrNo != "y" && yesOrNo != "n")
                {
                    cout << "\n\t\tSorry! Invalid input. Please type y or n: ";
                    cin >> yesOrNo;
                }
                // When valid, check the input again:
                if (yesOrNo == "y")
                {
                    claimTrip(myEmail);
                }
                else if (yesOrNo == "n")
                {
                    driverScreen(myEmail);
                }
            }
        }
    }
    else
    {
        cout << "\n\t\tSorry, that trip doesn't exist!" << endl;
        cout << "\t\tWould you like to claim a different trip (type y or n)? ";
        cin >> yesOrNo;

        if (yesOrNo == "y")
        {
            claimTrip(myEmail);
        }
        else if (yesOrNo == "n")
        {
            // Back to the driver screen:
            driverScreen(myEmail);
        }
        else
        {
            // Invalid input:
            while (yesOrNo != "y" && yesOrNo != "n")
            {
                cout << "\n\t\tSorry! Invalid input. Please type y or n: ";
                cin >> yesOrNo;
            }
            // When valid, check the input again:
            if (yesOrNo == "y")
            {
                claimTrip(myEmail);
            }
            else if (yesOrNo == "n")
            {
                driverScreen(myEmail);
            }
        }
    }
}

// Booked Trips Display Section:
void bookedTripsDisplay()
{
    // Trips Booked Section:
    cout << "\n\n\n\t\t\t|| Trips Booked By Customers ||" << endl << endl;

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
    Trips* headTrip = new Trips;
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
            headTrip->noOfPeople = stoi(driverScreenTripLine);
            break;
        case 11:
            headTrip->extraSupport = driverScreenTripLine;
            break;
        case 12:
            headTrip->luggage = driverScreenTripLine;
            break;
        case 13:
            headTrip->visaCardNumber = driverScreenTripLine;
            break;
        case 14:
            headTrip->cardExpiry = driverScreenTripLine;
            break;
        case 15:
            headTrip->cardCVC = driverScreenTripLine;
            break;
        case 16:
            if (driverScreenTripLine == "true")
            {
                headTrip->paymentStatus = true;
            }
            else if (driverScreenTripLine == "false")
            {
                headTrip->paymentStatus = false;
            }
            break;
        case 17:
            headTrip->cost = stod(driverScreenTripLine);
            break;
        case 18:
            if (driverScreenTripLine == "true")
            {
                headTrip->available = true;
            }
            else if (driverScreenTripLine == "false")
            {
                headTrip->available = false;
            }
            break;
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
    Trips* previousTrip = headTrip;

    /* Each item in the data file takes up 19 lines(including the end marker)
     * so, if we add 19 to the line counter each time we reach a new node,
     * we'll be able to obtain the information we need:
     */
    int addNineteen = 0;

    // Start from the second node:
    for (int i = 1; i < driverScreenEndMarkerCounter; i++)
    {
        Trips* newTrip = new Trips;

        // Set the line counter to zero:
        driverScreenTripLineCounter = 0;

        // Add nineteen:
        addNineteen += 19;

        // Re-open the tripData.txt file and look for the next set of trip details:
        tripData.open("tripData.txt", ios::in);

        while (getline(tripData, driverScreenTripLine))
        {
            // Count the number of lines being read:
            driverScreenTripLineCounter++;

            if (driverScreenTripLineCounter == 1 + addNineteen)
            {
                newTrip->tripNumber = stoi(driverScreenTripLine);
            }
            else if (driverScreenTripLineCounter == 2 + addNineteen)
            {
                newTrip->customerName = driverScreenTripLine;
            }
            else if (driverScreenTripLineCounter == 3 + addNineteen)
            {
                newTrip->customerContactNumber = driverScreenTripLine;
            }
            else if (driverScreenTripLineCounter == 4 + addNineteen)
            {
                newTrip->startingPlace = driverScreenTripLine;
            }
            else if (driverScreenTripLineCounter == 5 + addNineteen)
            {
                newTrip->destination = driverScreenTripLine;
            }
            else if (driverScreenTripLineCounter == 6 + addNineteen)
            {
                newTrip->tripDate[0] = stoi(driverScreenTripLine);
            }
            else if (driverScreenTripLineCounter == 7 + addNineteen)
            {
                newTrip->tripDate[1] = stoi(driverScreenTripLine);
            }
            else if (driverScreenTripLineCounter == 8 + addNineteen)
            {
                newTrip->tripDate[2] = stoi(driverScreenTripLine);
            }
            else if (driverScreenTripLineCounter == 9 + addNineteen)
            {
                newTrip->time = driverScreenTripLine;
            }
            else if (driverScreenTripLineCounter == 10 + addNineteen)
            {
                newTrip->noOfPeople = stoi(driverScreenTripLine);
            }
            else if (driverScreenTripLineCounter == 11 + addNineteen)
            {
                newTrip->extraSupport = driverScreenTripLine;
            }
            else if (driverScreenTripLineCounter == 12 + addNineteen)
            {
                newTrip->luggage = driverScreenTripLine;
            }
            else if (driverScreenTripLineCounter == 13 + addNineteen)
            {
                newTrip->visaCardNumber = driverScreenTripLine;
            }
            else if (driverScreenTripLineCounter == 14 + addNineteen)
            {
                newTrip->cardExpiry = driverScreenTripLine;
            }
            else if (driverScreenTripLineCounter == 15 + addNineteen)
            {
                newTrip->cardCVC = driverScreenTripLine;
            }
            else if (driverScreenTripLineCounter == 16 + addNineteen)
            {
                if (driverScreenTripLine == "true")
                {
                    newTrip->paymentStatus = true;
                }
                else if (driverScreenTripLine == "false")
                {
                    newTrip->paymentStatus = false;
                }
            }
            else if (driverScreenTripLineCounter == 17 + addNineteen)
            {
                newTrip->cost = stod(driverScreenTripLine);
            }
            else if (driverScreenTripLineCounter == 18 + addNineteen)
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
    Trips* temporaryTrip = headTrip;

    while (temporaryTrip != NULL)
    {
        if (temporaryTrip->past == false)
        {
            cout << "\t\tTrip Number     : " << temporaryTrip->tripNumber << endl;
            cout << "\t\tCustomer Name   : " << temporaryTrip->customerName << endl;
            cout << "\t\tContact Number  : " << temporaryTrip->customerContactNumber << endl;
            cout << "\t\tStarting Place  : " << temporaryTrip->startingPlace << endl;
            cout << "\t\tDestination     : " << temporaryTrip->destination << endl;
            cout << "\t\tTrip Date       : " << temporaryTrip->tripDate[0] << "/" << temporaryTrip->tripDate[1] << "/" << temporaryTrip->tripDate[2] << endl;
            cout << "\t\tTrip Time       : " << temporaryTrip->time << endl;
            cout << "\t\tNo. of People   : " << temporaryTrip->noOfPeople << endl;
            cout << "\t\tExtra Support   : " << temporaryTrip->extraSupport << endl;
            cout << "\t\tLuggage Needs   : " << temporaryTrip->luggage << endl;
            cout << "\t\tPrice           : " << temporaryTrip->cost << endl;
            cout << "\t\tPayment Status  : ";
            if (temporaryTrip->paymentStatus == true)
            {
                cout << "Paid" << endl;
            }
            else if (temporaryTrip->paymentStatus == false)
            {
                cout << "Not Yet Paid" << endl;
            }
            cout << "\t\tAvailability    : ";
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

            // If the trip is not in the past, list its trip number in the appropriate vector:
            displayedTripNumbers.push_back(temporaryTrip->tripNumber);
        }

        // Retrieve the next node:
        temporaryTrip = temporaryTrip->nextPosition;
    }

    // Delete the linked list to avoid a memory leak:
    while (headTrip != NULL)
    {
        Trips* tempNode = headTrip;
        headTrip = tempNode->nextPosition;
        delete(tempNode);
    }
}

// Admin LogIn Function:
void adminLogIn()
{
    cout << endl << endl;

    // Header Section:
    cout << "\t\t___________________________________________________" << endl << endl;
    cout << "\t\t---------------------------------------------------" << endl;
    cout << "\t\t___________________________________________________" << endl << endl << endl;

    cout << "\t\t\tAdmin LogIn" << endl << endl << endl;

    // Fix the missed inputs issue:
    cin.ignore();

    // Set admin login attempts to 0:
    adminLogInAttempts = 0;

    // Obtain the login details:
    cout << "\t\tPlease enter your email address: ";
    getline(cin, *adminEmailAddressPtr);
    cout << "\t\tPlease enter your password: ";
    getline(cin, *adminPasswordPtr);

    // Open and search adminData.txt for these details:
    adminData.open("adminData.txt", ios::in);
    // Search for the email address:
    while (getline(adminData, adminLine))
    {
        // The confirmed password is located 1 line down from the email address at line 2:
        if (*adminEmailAddressPtr == "admin@nztaxitrip.com" && adminLinesCounter == 2)
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
                    cout << "\n\t\tSorry. Incorrect password! Please try again after 10 seconds." << endl;

                    // Create a timer for 1 minute:
                    using namespace std::chrono_literals;
                    std::cout << "\n\t\tWaiting...\n" << std::flush;
                    auto start = std::chrono::high_resolution_clock::now();
                    std::this_thread::sleep_for(10000ms);
                    auto end = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double, std::milli> elapsed = end - start;

                    // After the timer is done, let them try again:
                    cout << "\n\t\tPlease enter your password: ";
                    getline(cin, *adminPasswordPtr);
                    adminLogInAttempts++;
                }
                if (*adminPasswordPtr != adminLine)
                {
                    /* If the password entered is incorrect, tell the user this,
                     * as well as how many attempts they have left to make:
                     */
                    cout << "\n\t\tSorry. Incorrect password! Please try again." << endl;
                    cout << "\t\tPlease enter your password: ";
                    getline(cin, *adminPasswordPtr);
                }
            }
            /* Once the password is correct...
             * Reset the lines being read to 1 and close the file:
             */
            adminLinesCounter = 1;
            adminData.close();

            // Tell the user they have successfully logged in, and take them to the Admin Screen:
            cout << "\n\n\t\tLog in successful!" << endl;
            adminLogInAttempts = 0;
            adminScreen();
        }
        // Count the lines being read:
        adminLinesCounter++;
    }
    // Close the file!
    adminData.close();

    // If the email address is incorrect:
    if (*adminEmailAddressPtr != "admin@nztaxitrip.com")
    {
        cout << "\n\t\tSorry. That email address was not found." << endl;
        cout << "\t\tDo you want to return to the home screen(type: home)? ";
        cin >> *adminEmailNotFoundPtr;

        // Make sure the input is valid:
        while (*adminEmailNotFoundPtr != "home" && *adminEmailNotFoundPtr != "Home")
        {
            cout << "\n\t\tSorry. Invalid input. Please type 'home' to return home: ";
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
    cout << endl << endl << endl;
    cout << "\t\t                  ---" << endl;
    cout << "\t\t                  | |" << endl;
    cout << "\t\t                 ....." << endl;
    cout << "\t\t           , ,''  |    ```...___," << endl;
    cout << "\t\t    .--  ''  P(___|_______/    (|" << endl;
    cout << "\t\t  ( //            |             |" << endl;
    cout << "\t\t  ` ._: ' ' :_____|______: ' ' :/" << endl;
    cout << "\t\t      '  o  '            '  o  '" << endl;
    cout << "\t\t        - -                - - " << endl;
    cout << "\t\t______________________________________________" << endl;
    cout << "\t\t______________________________________________" << endl << endl;

    cout << "\n\t\t\tWelcome, Admin!" << endl << endl;

    // Daily Driver Report:
    cout << "\n\t\t\t|| Daily Driver Report ||" << endl << endl;

    // Print today's date:
    time_t now = time(0);
    struct  tm* dt = localtime(&now);

    cout << "\t\tToday's Date: " << dt->tm_mday << "/" << dt->tm_mon + 1 << "/" << dt->tm_year + 1900 << endl << endl;

    // Check how many claimed trips happened today by looking in the claimed trips file:
    driverActivityData.open("driverActivityData.txt", ios::in);

    string activityLine;
    int lineCounter = 0;
    int numberOfTrips = 0;
    int dayToCheck;
    int monthToCheck;
    int yearToCheck;
    int adminChoice;
    int weeklyNewCustomers = 0;
    int dailyNewCustomers = 0;
    int customerRegistrationDay = 0;
    int customerRegistrationMonth = 0;
    int customerRegistrationYear = 0;
    int weeklyCancellations = 0;
    int dailyCancellations = 0;
    int cancellationDay = 0;
    int cancellationMonth = 0;
    int cancellationYear = 0;
    double totalCustomerPayments = 0;
    double cost = 0;
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

            if (lineCounter == (endMarkers[a]) - 5)
            {
                // Day:
                if (stoi(activityLine) == dt->tm_mday)
                {
                    dayValid = true;
                }
                else
                {
                    dayValid = false;
                }
            }
            else if (lineCounter == (endMarkers[a]) - 4)
            {
                // Month:
                if (stoi(activityLine) == dt->tm_mon + 1)
                {
                    monthValid = true;
                }
                else
                {
                    monthValid = false;
                }
            }
            else if (lineCounter == (endMarkers[a]) - 3)
            {
                // Year:
                if (stoi(activityLine) == dt->tm_year + 1900)
                {
                    yearValid = true;
                }
                else
                {
                    yearValid = false;
                }
            }
            // Also, record the cost of the trip:
            else if (lineCounter == (endMarkers[a]) - 1)
            {
                cost = stod(activityLine);
            }
        }
        // Close the file:
        driverActivityData.close();

        // Reset the line counter:
        lineCounter = 0;

        // If the day, month and year matches today's date, add to numberOfTrips and total cost:
        if (dayValid == true && monthValid == true && yearValid == true)
        {
            numberOfTrips++;
            totalCustomerPayments += cost;
        }
    }

    // Print the number of trips:
    cout << "\t\tNumber of Trips Today                  : " << numberOfTrips << endl;

    // Total paid in fares:
    cout << "\t\tTotal Driver Earnings (Gross)          : " << totalCustomerPayments << endl;

    // Total tax deductions (based on the average taxi driver's yearly earnings of $42,423):
    cout << "\t\tTotal Tax Deductions                   : " << totalCustomerPayments * 0.152 << endl;

    // Net income earned by all drivers today:
    cout << "\t\tCombined Net Earnings for Drivers      : " << totalCustomerPayments - (totalCustomerPayments * 0.152) << endl << endl << endl;

    // Weekly Driver Report:
    cout << "\n\t\t\t|| Weekly Driver Report ||" << endl << endl;

    cout << "\t\tDate: From " << *lastWeekDayPtr << "/" << *lastWeekMonthPtr << "/" << *lastWeekYearPtr << " to " << dt->tm_mday << "/" << dt->tm_mon + 1 << "/" << dt->tm_year + 1900 << endl << endl;

    /* Check how many claimed trips happened in the past week by looking in the claimed
     * trips file.
     * Because we deleted any trips older than a week using the cleaningUpData() function,
     * we just need to check for trips that aren't in the future.
     */

     // Reset the line counter, cost sum, and trip sum:
    cost = 0;
    lineCounter = 0;
    numberOfTrips = 0;
    totalCustomerPayments = 0;

    // We can use the end markers again to read each date and cost line:
    for (int i = 0; i < endMarkers.size(); i++)
    {
        // Open the file:
        driverActivityData.open("driverActivityData.txt", ios::in);

        while (getline(driverActivityData, activityLine))
        {
            // Count the lines being read:
            lineCounter++;

            // Check the day:
            if (lineCounter == (endMarkers[i] - 5))
            {
                dayToCheck = stoi(activityLine);
            }
            // Check the month:
            else if (lineCounter == (endMarkers[i] - 4))
            {
                monthToCheck = stoi(activityLine);
            }
            // Check the year:
            else if (lineCounter == (endMarkers[i] - 3))
            {
                yearToCheck = stoi(activityLine);
            }
            // Check the cost:
            else if (lineCounter == (endMarkers[i] - 1))
            {
                cost = stod(activityLine);
            }
        }
        // Close the file and reset the counter:
        driverActivityData.close();
        lineCounter = 0;

        // Find out if the date is in the future, starting with the year:
        if (yearToCheck > dt->tm_year + 1900)
        {
            yearValid = false;
        }
        // Then check the month:
        else if (yearToCheck == dt->tm_year + 1900 && monthToCheck > dt->tm_mon + 1)
        {
            monthValid = false;
        }
        else if (yearToCheck == dt->tm_year + 1900 && monthToCheck == dt->tm_mon + 1 && dayToCheck > dt->tm_mday)
        {
            dayValid = false;
        }
        else
        {
            yearValid = true;
            monthValid = true;
            dayValid = true;

            /* If the date isn't in the future,
             * add to the number of trips and the total payments.
             */
            numberOfTrips++;
            totalCustomerPayments += cost;
        }
    }
    // Print the number of trips:
    cout << "\t\tNumber of Trips This Week              : " << numberOfTrips << endl;

    // Total paid in fares:
    cout << "\t\tTotal Driver Earnings (Gross)          : " << totalCustomerPayments << endl;

    // Total tax deductions (based on the average taxi driver's yearly earnings of $42,423):
    cout << "\t\tTotal Tax Deductions                   : " << totalCustomerPayments * 0.152 << endl;

    // Net income earned by all drivers today:
    cout << "\t\tCombined Net Earnings for Drivers      : " << totalCustomerPayments - (totalCustomerPayments * 0.152) << endl << endl << endl;

    // Customer Report:
    cout << "\n\t\t\t|| Customer Report ||" << endl << endl;

    /* Search through the newCustomerData file and count the number of items with today's date, 
     * as well as the total number of items:
     */
    newCustomerData.open("newCustomerData.txt", ios::in);

    // Clear the end markers vector so we can use it again:
    endMarkers.clear();

    // Reset the counter:
    lineCounter = 0;

    while (getline(newCustomerData, customerLine))
    {
        // Count the lines being read:
        lineCounter++;

        // Look for end markers:
        if (customerLine == "-----End of item-----")
        {
            // Add to the weekly new customers sum:
            weeklyNewCustomers++;

            // Add the location to the endMarkers vector:
            endMarkers.push_back(lineCounter);
        }
    }
    // Close the file:
    newCustomerData.close();

    // Reset the counter as well as the date validations:
    lineCounter = 0;
    dayValid = false;
    monthValid = false;
    yearValid = false;

    // Open the file again and read each line:
    newCustomerData.open("newCustomerData.txt", ios::in);

    while (getline(newCustomerData, customerLine))
    {
        // Count the lines being read:
        lineCounter++;

        // Go through the vector of end markers to read each item's info:
        for (int i = 0; i < endMarkers.size(); i++)
        {
            // For every first line:
            if (lineCounter == (endMarkers[i] - 3))
            {
                customerRegistrationDay = stoi(customerLine);
            }
            // For every second line:
            else if (lineCounter == (endMarkers[i] - 2))
            {
                customerRegistrationMonth = stoi(customerLine);
            }
            // For every third line:
            else if (lineCounter == (endMarkers[i] - 1))
            {
                customerRegistrationYear = stoi(customerLine);
            }
            // For every fourth line:
            else if (lineCounter == endMarkers[i])
            {
                // Find out if the date is today, starting with the day:
                if (customerRegistrationDay == dt->tm_mday)
                {
                    dayValid = true;
                }
                else
                {
                    dayValid = false;
                }
                // Then check the month:
                if (customerRegistrationMonth == dt->tm_mon + 1)
                {
                    monthValid = true;
                }
                else
                {
                    monthValid = false;
                }
                // Then check the year:
                if (customerRegistrationYear == dt->tm_year + 1900)
                {
                    yearValid = true;
                }
                else
                {
                    yearValid = false;
                }
                // If all 3 are valid, add to the number of daily customers:
                if (dayValid == true && monthValid == true && yearValid == true)
                {
                    dailyNewCustomers++;
                }
            }
        }
    }
    // Close the file, reset the counter and clear the vector:
    newCustomerData.close();
    lineCounter = 0;
    endMarkers.clear();

    // Confirm the number of new customers today:
    *noOfNewCustomersTodayPtr = dailyNewCustomers;

    // Confirm the number of new customers this week:
    *noOfNewCustomersThisWeekPtr = weeklyNewCustomers;

    /* Search through the tripCancellations file and count the 
     * number of items with today's date,
     * as well as the total number of items:
     */
    tripCancellations.open("tripCancellations.txt", ios::in);

    // Clear the end markers vector so we can use it again:
    endMarkers.clear();

    // Reset the counter:
    lineCounter = 0;

    while (getline(tripCancellations, customerLine))
    {
        // Count the lines being read:
        lineCounter++;

        // Look for end markers:
        if (customerLine == "-----End of item-----")
        {
            // Add to the weekly cancellations sum:
            weeklyCancellations++;

            // Add the location to the endMarkers vector:
            endMarkers.push_back(lineCounter);
        }
    }
    // Close the file:
    tripCancellations.close();

    // Reset the counter as well as the date validations:
    lineCounter = 0;
    dayValid = false;
    monthValid = false;
    yearValid = false;

    // Open the file again and read each line:
    tripCancellations.open("tripCancellations.txt", ios::in);

    while (getline(tripCancellations, customerLine))
    {
        // Count the lines being read:
        lineCounter++;

        // Go through the vector of end markers to read each item's info:
        for (int i = 0; i < endMarkers.size(); i++)
        {
            // For every first line:
            if (lineCounter == (endMarkers[i] - 3))
            {
                cancellationDay = stoi(customerLine);
            }
            // For every second line:
            else if (lineCounter == (endMarkers[i] - 2))
            {
                cancellationMonth = stoi(customerLine);
            }
            // For every third line:
            else if (lineCounter == (endMarkers[i] - 1))
            {
                cancellationYear = stoi(customerLine);
            }
            // For every fourth line:
            else if (lineCounter == endMarkers[i])
            {
                // Find out if the date is today, starting with the day:
                if (cancellationDay == dt->tm_mday)
                {
                    dayValid = true;
                }
                else
                {
                    dayValid = false;
                }
                // Then check the month:
                if (cancellationMonth == dt->tm_mon + 1)
                {
                    monthValid = true;
                }
                else
                {
                    monthValid = false;
                }
                // Then check the year:
                if (cancellationYear == dt->tm_year + 1900)
                {
                    yearValid = true;
                }
                else
                {
                    yearValid = false;
                }
                // If all 3 are valid, add to the number of daily cancellations:
                if (dayValid == true && monthValid == true && yearValid == true)
                {
                    dailyCancellations++;
                }
            }
        }
    }
    // Close the file, reset the counter and clear the vector:
    tripCancellations.close();
    lineCounter = 0;
    endMarkers.clear();

    // Confirm the number of cancellations today:
    *noOfCancellationsDailyPtr = dailyCancellations;

    // Confirm the number of cancellations this week:
    *noOfCancellationsWeeklyPtr = weeklyCancellations;

    // Print the number of new customers today and this week:
    cout << "\t\tNumber of New Customers Today          : " << *noOfNewCustomersTodayPtr << endl;
    cout << "\t\tNumber of New Customers This Week      : " << *noOfNewCustomersThisWeekPtr << endl;

    // Print the number of trip cancellations today and this week:
    cout << "\t\tNumber of Trip Cancellations Today     : " << *noOfCancellationsDailyPtr << endl;
    cout << "\t\tNumber of Trip Cancellations This Week : " << *noOfCancellationsWeeklyPtr << endl << endl << endl;

    // Give the admin the option to log out:
    cout << "\t\tWould you like to log out (type: 1)? ";
    cin >> adminChoice;

    // Act on input:
    if (adminChoice == 1)
    {
        // Go back to the intro screen:
        introFunction();
    }
    else
    {
        while (adminChoice != 1)
        {
            cout << "\n\t\tSorry. You have entered an invalid option." << endl;
            cout << "\t\tPlease type 1 if you want to log out: ";
            cin >> adminChoice;
        }
        // Once the user enters 1, take them to the intro screen:
        introFunction();
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu