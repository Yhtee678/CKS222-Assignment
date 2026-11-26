#ifndef Hotel_H
#define Hotel_H

#include<iostream>
#include<string>
#include<iomanip>
#include "Review.h"
#include "Constants.h"
using namespace std;

// =====================================================
// CLASS: Hotel
// =====================================================

class Hotel
{
  private:
    string hotelName;
    Review hotelReview[MAX_REVIEWS];
    int reviewCount;
    double totalRating;

  public:
    Hotel() : hotelName(""), reviewCount(0), totalRating(0.0){}

    // Constructor for creating new hotels when loading reviews
    Hotel(string hName) :
    hotelName(hName), reviewCount(0), totalRating(0.0){}

    // Getter functions
    string getHotelName() const {return hotelName;}
    int getReviewCount() const {return reviewCount;}

    double getAverageRating() const
    {
      if (reviewCount == 0) return 0.0;
      else return totalRating / reviewCount;
    }

    // Add review to hotel's collection
    bool addReview(const Review& review) {
        if (reviewCount >= MAX_REVIEWS) return false;

        hotelReview[reviewCount++] = review;
        totalRating += review.getRating();
        return true;
    }

    // Display hotel information and all reviews
    void printHotelProfile() const {
        cout << "\n========== HOTEL: " << hotelName << " ==========" << endl;
        cout << "Total Reviews: " << reviewCount << endl;
        cout << "Average Rating: " << fixed << setprecision(2) << getAverageRating() << "/5.0" << endl;
        cout << "======================================\n" << endl;

        if (reviewCount == 0) {
            cout << "No reviews available for this hotel." << endl;
            return;
        }

        cout << "REVIEWS:" << endl;
        for (int i = 0; i < reviewCount; i++) {
            cout << "[" << (i+1) << "] ";
            hotelReview[i].print();
        }
    }

    // Operator overloading - comparing hotels by ratings
    bool operator>(const Hotel& right) const
    {
      return this->getAverageRating() > right.getAverageRating();
    }

    bool operator<(const Hotel& right) const
    {
      return this->getAverageRating() < right.getAverageRating();
    }

    // =====================================================
    // Friend Function
    // =====================================================
    friend void hotelAnalyticsReport(const Hotel& hotel);

};

void hotelAnalyticsReport(const Hotel& hotel) {
    cout << "\n--- Analytics Report for " << hotel.hotelName << " ---" << endl;
    cout << "Total Reviews: " << hotel.reviewCount << endl;
    if (hotel.reviewCount > 0) {
        cout << "Cumulative Rating: " << fixed << setprecision(1) << hotel.totalRating << endl;
        cout << "Average Rating: " << fixed << setprecision(2) << hotel.totalRating / hotel.reviewCount << "/5.0" << endl;
    } else {
        cout << "No rating data available." << endl;
    }
    cout << "-------------------------------------------" << endl;
}




#endif
