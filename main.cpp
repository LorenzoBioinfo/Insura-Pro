// InsuraPro Solutions Project

/*
Project Requirements:

OOP in C++: Implement OOP principles to create a robust and flexible structure.
Data Structure: Design a data structure to store customer information and their interactions.
User Interface: Develop an interactive and intuitive command-line interface.

Functionality:
- Add Customer: Insert new customers into the CRM.
- View Customers: Display all stored customers.
- Edit Customer: Modify the details of an existing customer.
- Delete Customer: Remove customers from the CRM.
- Search Customer: Search for customers by first or last name.
- Manage Interactions: Add, view, and search interactions for each customer
  (interactions include sales appointments and signed contracts).
- Save and Load Data: Save customer and interaction data to a file (text or CSV)
  and load them at startup.
- User Interface: The interface will be command-line based, with a main menu
  providing clear options for all necessary operations, ensuring a smooth
  and user-friendly experience.
*/

//#include <bits/stdc++.h> gave me an error on my Mac,
// so I used these individual includes instead.
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <limits>
#include <queue>
#include <stack>
#include <deque>
#include <bitset>
#include <cassert>
#include <fstream>
#include <sstream>


#include "InsuraPro.h"
using namespace std;


void remove_newline(char* buffer) {
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
}





// Function for check if file exists at beginning of program
bool check_and_file(InsuraPro ip,  string& filename) {
    FILE *file = fopen(filename.c_str(), "r");
    bool loading=false;
    if (file != NULL) {
        cout << "The file" << filename << " exists. Do you want to load it? (Yes/No): ";
        string inputchoice;
        cin >> inputchoice;
        if (inputchoice == "Yes" || inputchoice == "yes") {
            cout << "File will be loaded in InsuraPro.\n";
            //ip.loadData(filename);
            loading = true;
        } else {
            cout << "File won't be loaded.\n";

        }
    } else {
        cout << "The file " << filename << " does not exist.\n";
    }
    return loading;

}





// Main function
// First, create the InsuraPro CRM
// Checks if there are pre-existing data about clients and interactions
// Then it starts the program
int main() {
    cout << "\n--- Welcome to CRM InsuraPro Solutions ---\n"<<endl;
    InsuraPro ip;

    string filepath1="./clients.csv";
    bool loadfile=check_and_file(ip,filepath1);
    if (loadfile) {

        ip.loadData(filepath1);
    }
    string filepath2="./interactions.csv";
    bool loadfileInteractions=check_and_file(ip,filepath2);
    if (loadfileInteractions) {

        ip.loadDataInteractions(filepath2);
    }

    ip.show_options();

    return 0;
}









