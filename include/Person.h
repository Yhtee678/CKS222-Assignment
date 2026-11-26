#ifndef Person_H
#define Person_H

#include<iostream>
#include<string>
#include "Constants.h"
using namespace std;

// =====================================================
// CLASS: Person
// =====================================================

class Person
{
  protected:
    string id;
    string name;
    string email;
    string state;

  public:
  	Person(): id(""), name(""), email(""), state(""){}
    Person(string pId, string pN, string pE, string pS): id(pId), name(pN), email(pE), state(pS){}


    string getPersonID() const {return id;}
    string getPersonName() {return name;}
    string getState() const { return state; }
    string getPersonEmail() const { return email; }

    void printProfile() const
    {
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Email: " << email << endl;
        cout << "State: " << state << endl;
    }

};
#endif
