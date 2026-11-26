#ifndef Traveler_H
#define Traveler_H

#include<iostream>
#include "Person.h"
#include "Review.h"
#include "Constants.h"
using namespace std;

// =====================================================
// CLASS: Traveler
// =====================================================

class Traveler: public Person
{
  private:
    string membershipLevel;
    int loyaltyPoints;
    Review TravelerReview[MAX_REVIEWS];
    int reviewCount;

  public:
    Traveler() : Person()
    {
      membershipLevel = "";
      loyaltyPoints = 0;
      reviewCount = 0;
    }
    // Default constrcutor
    Traveler(string pId, string pN, string pE, string pS, string ml, int lp) :
    Person(pId, pN, pE, pS), membershipLevel(ml), loyaltyPoints(lp), reviewCount(0){}


    // Getter functions
    string getMembershipLevel() const {return membershipLevel;}
    int getLoyaltyPoints() const {return loyaltyPoints;}
    int getReviewCount() const {return reviewCount; }
    Review* getAllReviews()
{
    return TravelerReview;
}

    bool addReview(const Review& review)
    {
      if (reviewCount >= MAX_REVIEWS) return false;

      TravelerReview[reviewCount++] = review;

      return true;
    }

    void setLoyaltyPoints(int p) { loyaltyPoints = p; }

    void updateMembershipLevel() {
      if (loyaltyPoints >= 10000) membershipLevel = "Platinum";
      else if (loyaltyPoints >= 5000) membershipLevel = "Gold";
      else if (loyaltyPoints >= 1000) membershipLevel = "Silver";
      else membershipLevel = "Bronze";
    }

    void printProfile() const // Changed name to match base class
    {
        cout << "========== TRAVELER PROFILE ==========" << endl;
        Person::printProfile();
        cout << "Membership Level: " << membershipLevel << endl;
        cout << "Loyalty Points: " << loyaltyPoints << endl;
        cout << "Reviews Written: " << reviewCount << endl;
        cout << "=====================================" << endl;
    }

    void displayTravelerReviews() const {
        if (reviewCount == 0) {
            cout << "This traveler has not written any reviews." << endl;
            return;
        }
        else {
          cout << "\nAuthor: " << name << " - Reviews (" << reviewCount << "):" << endl;
          for (int i = 0; i < reviewCount; i++) {
              cout << "[" << (i+1) << "] ";
              TravelerReview[i].print();
          }
        }
    }

    // Compare travelers by loyalty points
    bool operator>(const Traveler& right) const {
        return this->loyaltyPoints > right.loyaltyPoints;
    }

    // Added operator< for sorting
    bool operator<(const Traveler& right) const {
        return this->loyaltyPoints < right.loyaltyPoints;
    }
};

#endif
