#ifndef Client_h
#define Client_h

#include "Interaction.h"
using namespace std;
// Creates a Class for Client
class Client{
    // Interaction is defined by name and last name of clients, date of birth,
    // email and phone number
    // Client's interactions are stored in a vector
public:
    int id;
    string name;
    string lastName;
    string birthDate;
    string email;
    string phone;
    vector<Interaction> interactions;

    // Constructor of Client
    Client(int _id, string _name,string _lastName,string _birthDate,
        string _email, string _phone){
        id=_id;
        name=_name;
        lastName=_lastName;
        birthDate=_birthDate;
        email=_email;
        phone=_phone;

    }
    // Method to print client's info to screen
    void get_client() {
        cout << id <<  " | " << name << " | "
        << lastName << " | "
        << email << " | "
        << phone << " | "
        << birthDate << endl;
    }

    // Methods that add interaction to client's interaction list
    void addInteraction(Interaction& i) {
        interactions.push_back(i);
    }

    //Method that compares the current object's `name` and `lastName` members with the provided arguments.
    bool matches(std::string &name, std::string &lastname) {
        return this->name == name && this->lastName == lastname;
    }
    // Method to print interaction to file
    string print_to_file()  {
        return  name + "," + lastName + "," + birthDate + "," + email + "," + phone;}
};

#endif