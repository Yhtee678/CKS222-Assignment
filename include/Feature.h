#ifndef Feature_H
#define Feature_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include "Constants.h"
#include "Review.h"
#include "Person.h"
#include "Traveler.h"
#include "Hotel.h"
#include "TravelerValidation.h"
#include "RatingValidation.h"
#include <vector>

using namespace std;

void printMenu();

void propertyDeepDive(Hotel hotels[], int hotelCount) {
    cout << "\n========== PROPERTY DEEP-DIVE ==========" << endl;
    cout << "Enter hotel name: ";
    cin.ignore();
    string searchName;
    getline(cin, searchName);

    for (int i = 0; i < hotelCount; i++) {
        if (hotels[i].getHotelName() == searchName) {
            hotels[i].printHotelProfile();
            hotelAnalyticsReport(hotels[i]);
            return;
        }
    }

    cout << "Hotel '" << searchName << "' not found in database." << endl;
}

void travelerProfileManagement(Traveler travelers[], int travelerCount) {
    cout << "\n========== TRAVELER PROFILE ==========" << endl;
    cout << "Enter traveler ID: ";
    string searchID;
    cin >> searchID;

    for (int i = 0; i < travelerCount; i++) {
        if (travelers[i].getPersonID() == searchID) {
            travelers[i].printProfile();
            travelers[i].displayTravelerReviews();
            return;
        }
    }

    cout << "Traveler with ID " << searchID << " not found." << endl;
}

void topPickMatcher(Hotel hotels[], int hotelCount) {
    cout << "\n========== TOP-PICK MATCHER ==========" << endl;
    cout << "Hotel Rankings (by average rating):" << endl;

    Hotel temp;
    for (int i = 0; i < hotelCount - 1; i++) {
        for (int j = 0; j < hotelCount - i - 1; j++) {
            if (hotels[j] < hotels[j + 1]) {
                temp = hotels[j];
                hotels[j] = hotels[j + 1];
                hotels[j + 1] = temp;
            }
        }
    }

    cout << "\nTop 10 Ranked Hotels:" << endl;
    for (int i = 0; i < hotelCount && i < 10; i++) {
        cout << "[" << (i + 1) << "] "
             << hotels[i].getHotelName() << " (Avg Rating: "
             << fixed << setprecision(2) << hotels[i].getAverageRating() << ")" << endl;
    }
}

void topReviewers(Traveler travelers[], int travelerCount) {
    cout << "\n========== TOP REVIEWERS (by Loyalty Points) ==========" << endl;

    Traveler temp;
    for (int i = 0; i < travelerCount - 1; i++) {
        for (int j = 0; j < travelerCount - i - 1; j++) {
            if (travelers[j] < travelers[j + 1]) {
                temp = travelers[j];
                travelers[j] = travelers[j + 1];
                travelers[j + 1] = temp;
            }
        }
    }

    cout << "\nTop Reviewers:" << endl;
    for (int i = 0; i < travelerCount && i < 10; i++) {
        cout << "[" << (i + 1) << "] " << travelers[i].getPersonName()
             << " | Loyalty Points: " << travelers[i].getLoyaltyPoints()
             << " | Level: " << travelers[i].getMembershipLevel()
             << " | Reviews: " << travelers[i].getReviewCount() << endl;
    }
}

void addNewReview(Traveler travelers[], int travelerCount, Hotel hotels[], int& hotelCount) {
    string uid, hName, comment;
    int rating = 0;

    cout << "\n========== SUBMIT NEW REVIEW ==========" << endl;
    cout << "Enter your User ID: ";
    if (!getline(cin, uid)) return;

    int tIndex = -1;

    for (int i = 0; i < travelerCount; ++i) {
        if (travelers[i].getPersonID() == uid) {
            tIndex = i;
            break;
        }
    }

    if (tIndex == -1) {
        cout << "Error: User ID not found!" << endl;
        return;
    }

    cout << "Enter Hotel Name: ";
    if (!getline(cin, hName)) return;

    if (hName.find_first_not_of(" \t\r\n")
        == string::npos) {
        cout << "Error: Hotel name cannot be empty."
             << endl;
        return;
    }

    if (!readRating(cin, cout, rating)) {
        return;
    }

    cout << "Comment: ";
    if (!getline(cin, comment)) return;

    // Find existing hotel.
    int hIndex = -1;

    for (int i = 0; i < hotelCount; ++i) {
        if (hotels[i].getHotelName() == hName) {
            hIndex = i;
            break;
        }
    }

    // Check all capacities before making changes.
    if (travelers[tIndex].getReviewCount()
        >= MAX_REVIEWS) {
        cout << "Error: Traveler review storage is full."
             << endl;
        return;
    }

    if (hIndex == -1 && hotelCount >= MAX_HOTELS) {
        cout << "Error: Hotel storage is full."
             << endl;
        return;
    }

    if (hIndex != -1 &&
        hotels[hIndex].getReviewCount()
        >= MAX_REVIEWS) {
        cout << "Error: Hotel review storage is full."
             << endl;
        return;
    }

    Review newRev(uid, hName, rating, comment);

    // Store review in hotel collection.
    if (hIndex == -1) {
        hotels[hotelCount] = Hotel(hName);

        if (!hotels[hotelCount].addReview(newRev)) {
            cout << "Error: Unable to save hotel review."
                 << endl;
            return;
        }

        ++hotelCount;
    } else {
        if (!hotels[hIndex].addReview(newRev)) {
            cout << "Error: Unable to save hotel review."
                 << endl;
            return;
        }
    }

    // Store review in traveler collection.
    if (!travelers[tIndex].addReview(newRev)) {
        cout << "Error: Unable to save traveler review."
             << endl;
        return;
    }

    // Reward points only after successful submission.
    int currentPoints =
        travelers[tIndex].getLoyaltyPoints();

    travelers[tIndex].setLoyaltyPoints(
        currentPoints + 100
    );

    travelers[tIndex].updateMembershipLevel();

    cout << "\nSuccess! Review submitted."
         << " +100 Points earned!" << endl;

    cout << "New Status: "
         << travelers[tIndex].getMembershipLevel()
         << endl;
}

string generateID(int count)
{
    if (count + 1 < 10)
        return "U00" + to_string(count + 1);

    else if (count + 1 < 100)
        return "U0" + to_string(count + 1);

    else
        return "U" + to_string(count + 1);
}

void addNewTraveler(Traveler travelers[], int& travelerCount)
{
    if (travelerCount >= MAX_TRAVELERS) {
        cout << "Error: System is full." << endl;
        return;
    }

    string name, email, state;

    cout << "\n========== ADD NEW TRAVELER =========="
         << endl;


    cout << "Enter Full Name: ";
    if (!getline(cin, name)) return;

    if (!validTravelerName(name)) {
        cout << "Error: Name cannot be empty." << endl;
        return;
    }

    cout << "Enter Email Address: ";
    if (!getline(cin, email)) return;

    if (!validTravelerEmail(email)) {
        cout << "Error: Invalid email address." << endl;
        return;
    }

    cout << "Enter State: ";
    if (!getline(cin, state)) return;

    if (!validTravelerState(state)) {
        cout << "Error: State cannot be empty." << endl;
        return;
    }

    vector<string> existingIDs;

    for (int i = 0; i < travelerCount; ++i) {
        existingIDs.push_back(
            travelers[i].getPersonID()
        );
    }

    string id = nextTravelerID(existingIDs);

    if (id.empty()) {
        cout << "Error: No available User ID."
             << endl;
        return;
    }

    travelers[travelerCount] =
        Traveler(id, name, email, state, "Bronze", 0);

    ++travelerCount;

    cout << "\nTraveler registered successfully!"
         << endl;
    cout << "Generated User ID: "
         << id << endl;
}


void printMenu() {
    cout << "\n========== HOTEL REVIEW SYSTEM ==========" << endl;
    cout << "1. Property Deep-Dive" << endl;
    cout << "2. Traveler Profile" << endl;
    cout << "3. Top-Pick Matcher" << endl;
    cout << "4. Top Reviewers" << endl;
    cout << "5. Add New Review" << endl;
    cout << "6. Add New Traveler" << endl;
    cout << "7. Save & Exit" << endl;
    cout << "========================================" << endl;
    cout << "Please enter your choice: ";
}

#endif
