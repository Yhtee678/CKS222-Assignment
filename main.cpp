
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <limits>

#include "Constants.h"
#include "Review.h"
#include "Person.h"
#include "Traveler.h"
#include "Hotel.h"
#include "Feature.h"
#include "MenuInput.h"
using namespace std;
bool dataLoadSafe = true;

// =====================================================
// OPEN "users.txt" FILE EXACTLY AT ONCE
// =====================================================

void loadTravelers(Traveler travelers[], int& travelerCount)
{
    ifstream inFile("users.txt");

    if (!inFile) {
        cout << "Error opening users.txt file!" << endl;
        dataLoadSafe = false;
        return;
    }

    string id, name, state, email, level;
    int points;

    while (getline(inFile, id, '\t')) {

        if (!getline(inFile, name, '\t') ||
            !getline(inFile, state, '\t') ||
            !getline(inFile, email, '\t') ||
            !getline(inFile, level, '\t') ||
            !(inFile >> points)) {
            cout << "Warning: Invalid traveler record."
                 << endl;
            dataLoadSafe = false;
            break;
        }

        inFile.ignore(
            numeric_limits<streamsize>::max(), '\n'
        );

        if (travelerCount >= MAX_TRAVELERS) {
            cout << "Warning: Traveler capacity reached."
                 << endl;
            dataLoadSafe = false;
            break;
        }

        travelers[travelerCount] =
            Traveler(id, name, email, state, level, points);

        ++travelerCount;
    }

    cout << "Loaded " << travelerCount
         << " travelers." << endl;
}

// =====================================================
// OPEN "reviews.txt" FILE EXACTLY AT ONCE
// =====================================================

void loadReviews(
    Traveler travelers[],
    int travelerCount,
    Hotel hotels[],
    int& hotelCount
) {
    ifstream inFile("reviews.txt");

    if (!inFile) {
        cout << "Error opening reviews.txt file!" << endl;
        dataLoadSafe = false;
        return;
    }

    string id, hotelName, comment;
    int rating;

    while (getline(inFile, id, '\t')) {

        if (!(inFile >> rating)) {
            cout << "Warning: Invalid review rating."
                 << endl;
            dataLoadSafe = false;
            break;
        }

        inFile.ignore();

        if (!getline(inFile, comment, '\t') ||
            !getline(inFile, hotelName)) {
            cout << "Warning: Invalid review record."
                 << endl;
            dataLoadSafe = false;
            break;
        }

        int tIndex = -1;
        int hIndex = -1;

        for (int i = 0; i < travelerCount; ++i) {
            if (travelers[i].getPersonID() == id) {
                tIndex = i;
                break;
            }
        }

        for (int i = 0; i < hotelCount; ++i) {
            if (hotels[i].getHotelName() == hotelName) {
                hIndex = i;
                break;
            }
        }

        if (tIndex == -1) {
            cout << "Warning: Unknown traveler ID."
                 << endl;
            dataLoadSafe = false;
            continue;
        }

        if (travelers[tIndex].getReviewCount()
            >= MAX_REVIEWS) {
            cout << "Warning: Traveler review capacity reached."
                 << endl;
            dataLoadSafe = false;
            continue;
        }

        if (hIndex == -1 && hotelCount >= MAX_HOTELS) {
            cout << "Warning: Hotel capacity reached."
                 << endl;
            dataLoadSafe = false;
            continue;
        }

        if (hIndex != -1 &&
            hotels[hIndex].getReviewCount() >= MAX_REVIEWS) {
            cout << "Warning: Hotel review capacity reached."
                 << endl;
            dataLoadSafe = false;
            continue;
        }

        Review rev(
            id,
            hotelName,
            static_cast<double>(rating),
            comment
        );

        if (hIndex == -1) {
            hotels[hotelCount] = Hotel(hotelName);
            hIndex = hotelCount;
            ++hotelCount;
        }

        if (!hotels[hIndex].addReview(rev)) {
            cout << "Warning: Hotel review not loaded."
                 << endl;
            dataLoadSafe = false;
            continue;
        }

        if (!travelers[tIndex].addReview(rev)) {
            cout << "Warning: Traveler review not loaded."
                 << endl;
            dataLoadSafe = false;
            continue;
        }
    }

    cout << "Loaded reviews and created "
         << hotelCount << " hotels." << endl;
}

// =====================================================
// MAIN FUNCTION
// =====================================================

int main() {
  cout << "========== HOTEL REVIEW SYSTEM ==========" << endl;
  cout << "Loading data..." << endl << endl;

  //Entity-centric Lifestyle
  static Traveler travelers[MAX_TRAVELERS];
  int travelerCount = 0;

  static Hotel hotels[MAX_HOTELS];
  int hotelCount = 0;

loadTravelers(travelers, travelerCount);

  if (dataLoadSafe) {
      loadReviews(travelers, travelerCount, hotels, hotelCount);
  }

  if (!dataLoadSafe) {
      cerr << "Error: Data loading was incomplete." << endl;
      cerr << "Original data files will not be overwritten." << endl;
      return 1;
  }

int choice = 0;
while (choice != 7)
{
    printMenu();

    if (!readMenuChoice(cin, cout, choice)) {
        cout << "\nInput ended. Exiting system..." << endl;
        break;
    }

    switch (choice)
    {
      case 1:
        propertyDeepDive(hotels, hotelCount);
        break;
      case 2:
        travelerProfileManagement(travelers, travelerCount);
        break;
      case 3:
        topPickMatcher(hotels, hotelCount);
        break;
      case 4:
        topReviewers(travelers, travelerCount);
        break;
      case 5:
        addNewReview(travelers, travelerCount, hotels, hotelCount);
        break;
      case 6:
        addNewTraveler(travelers, travelerCount);
        break;
      case 7:
        cout << "\nExiting system..." << endl;
        break;
      default:
        cout << "Invalid choice!" << endl;
    }
  }

// =====================================================
// SAVE "users.txt" FILE EXACTLY AT ONCE
// =====================================================
if (!dataLoadSafe) {
    cout << "Warning: Data loading was incomplete."
         << endl;
    cout << "Original data files will not be overwritten."
         << endl;
    return 1;
}

 ofstream saveUser("users.txt");

for (int i = 0; i < travelerCount; i++)
{
    saveUser << travelers[i].getPersonID() << '\t'
             << travelers[i].getPersonName() << '\t'
             << travelers[i].getState() << '\t'
             << travelers[i].getPersonEmail() << '\t'
             << travelers[i].getMembershipLevel() << '\t'
             << travelers[i].getLoyaltyPoints() << endl;
}

saveUser.close();

// =====================================================
// SAVE "reviews.txt" FILE EXACTLY AT ONCE
// =====================================================

  ofstream saveReview("reviews.txt");

for (int i = 0; i < travelerCount; i++)
{
    Review* reviews = travelers[i].getAllReviews();

    int rCount = travelers[i].getReviewCount();

    for (int j = 0; j < rCount; j++)
    {
        saveReview << reviews[j].getUserID() << '\t'
                   << reviews[j].getRating() << '\t'
                   << reviews[j].getReviewText() << '\t'
                   << reviews[j].getHotelName() << endl;
    }
}

saveReview.close();
  cout << "Saving data..." << endl;

  cout << "Program terminated. Thanks for using our NotTravel system!" << endl;

  return 0;

}
