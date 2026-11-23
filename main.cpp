
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include "Constants.h"
#include "Review.h"
#include "Person.h"
#include "Traveler.h"
#include "Hotel.h"
#include "Feature.h"
using namespace std;

// =====================================================
// OPEN "users.txt" FILE EXACTLY AT ONCE
// =====================================================

void loadTravelers(Traveler travelers[], int& travelerCount)
{
  ifstream inFile("users.txt");
  if (!inFile)
  {
    cout << "Error opening users.txt file!" << endl;
    return;
  }

  string id, name, state, email, level;
  int points;

  while(getline(inFile, id, '\t'))
  {
    getline(inFile, name, '\t');
    getline(inFile, state, '\t');
    getline(inFile, email, '\t');
    getline(inFile, level, '\t');
    inFile >> points;
    inFile.ignore();

    Traveler t(id, name, email, state, level, points);
    travelers[travelerCount] = t;
    travelerCount++;
  }

  inFile.close();
  cout << "Loaded " << travelerCount << " travelers." << endl;
}

// =====================================================
// OPEN "reviews.txt" FILE EXACTLY AT ONCE
// =====================================================

void loadReviews(Traveler travelers[], int travelerCount, Hotel hotels[], int &hotelCount)
{
  ifstream inFile2("reviews.txt");
  if (!inFile2)
  {
    cout << "Error opening reviews.txt file!" << endl;
    return;
  }

string id, hotelName, comment;
int rating;

while(getline(inFile2, id, '\t'))
{
  inFile2 >> rating;
  inFile2.ignore();

  getline(inFile2, comment, '\t');
  getline(inFile2, hotelName);

  Review rev(id, hotelName, static_cast<double>(rating), comment);

        for (int i = 0; i < travelerCount; i++) {
            if (travelers[i].getPersonID() == id) {
                travelers[i].addReview(rev);
                break;
            }
        }

        int index = -1;

         for (int i = 0; i < hotelCount; i++)
     {
         if (hotels[i].getHotelName() == hotelName)
    {
        index = i;
        break;
    }
}

         if (index == -1)
     {
    hotels[hotelCount] = Hotel(hotelName);
    hotels[hotelCount].addReview(rev);
    hotelCount++;
     }
         else
{
    hotels[index].addReview(rev);
}
    }


    inFile2.close();
    cout << "Loaded reviews and created " << hotelCount << " hotels." << endl;
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
  loadReviews(travelers, travelerCount, hotels, hotelCount);

  int choice = 0;
  while (choice != 7)
  {
    printMenu();
    if (!(cin >> choice)) {
        cout << "Please enter a valid number (1-7)." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
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
