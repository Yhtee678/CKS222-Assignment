#ifndef Review_H
#define Review_H

#include <iostream>
#include <string>
#include<iomanip>

using namespace std;

// =====================================================
// CLASS: Review
// =====================================================

class Review {
private:
    string userID;
    string hotelName;
    double rating;
    string reviewText;

public:
    Review() : userID(""), hotelName(""), rating(0.0), reviewText("") {}

    Review(string uid, string hotel, double r, string text)
        : userID(uid), hotelName(hotel), rating(r), reviewText(text) {}

    string getUserID() const { return userID; }
    string getHotelName() const { return hotelName; }
    double getRating() const { return rating; }
    string getReviewText() const { return reviewText; }

    void print() const {
        cout << " User: " << userID
             << " | Rating: " << fixed << setprecision(1) << rating << "/5.0" << endl;
        cout << "  Text: " << reviewText << endl;
    }

};

#endif
