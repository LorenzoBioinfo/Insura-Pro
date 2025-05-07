
#ifndef Interaction_h
#define Interaction_h


using namespace std;

// Creates a Class for Interactions
class Interaction {
public:
    // Interaction is defined by name and last name of clients, type (Contract or Appointment,
    // Description and date
    string name;
    string lastname;
    string type;
    string description;
    string date;

    // Constructor of Interactions
    Interaction(string _name, string _lastname,string _type, string _description, string _date) {
        name=_name;
        lastname=_lastname;
        type=_type;
        description=_description;
        date=_date;
    }
    // Method to print interaction to screen
    void get_interaction() {
        cout << name << " | "
        << lastname << " | "
        << type << " | "
        << description << " | "
        << date << endl;
    }
    // Method to print interaction to file
    string print_to_file()  {
        return name + "," + lastname + "," + type + "," + description + "," + date;
    }
};
#endif