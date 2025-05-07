
#ifndef InsuraPro_h
#define InsuraPro_h

#include "Client.h"
using namespace std;
// Creates a Class for the InsuraPro CRM
class InsuraPro {
    vector<Client> clients;
    public:
        // Create a progressive index id for clients in Clients crc
        int current_id=1;

        // This method displays the options the user can choose from and receives input from the keyboard.
        // The while loop ensures it is called repeatedly until the program ends
        void show_options() {
            int input = -1;

        while (true) {
            cout << "\n--- How can I help you? ---\n";
            cout << "1. Add New Client\n";
            cout << "2. Show All Clients\n";
            cout << "3. Update Client's Info\n";
            cout << "4. Delete a Client\n";
            cout << "5. Find a Client\n";
            cout << "6. Manage Interactions\n";
            cout << "7. Load Data\n";
            cout << "8. Save Data\n";
            cout << "0. Exit\n";
            cout << "Choice: ";

            cin >> input;

            // this assures user's choice is a number
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number.\n";
                continue;
            }

            cout << "You chose: " << input << endl;

            // switch case for all user's options
            switch (input) {
                case 0:
                    cout << "Goodbye!\n";
                    return;
                case 1:
                    cout << "Adding new client...\n";
                    addClient();
                    break;
                case 2:
                    cout << "Showing all clients...\n";
                    printAllClients();
                    break;
                case 3:
                    cout << "Updating client info...\n";
                    updateClientInfo();
                    break;
                case 4:
                    cout << "Deleting a client...\n";
                    deleteClient();
                    break;
                case 5:
                    cout << "Finding a client...\n";
                    searchClient();
                    break;
                case 6:
                    cout << "Managing interactions...\n";
                    manageInteractions();
                    break;
                case 7: {
                    cout << "Loading data...\n";
                    string filepathclient="./clients.csv";
                    loadDataFromFile(filepathclient);
                    string filepathinteractions="./interactions.csv";
                    loadDataInteractionsFromFile(filepathinteractions);
                    break;
                }
                case 8:
                    cout << "Saving data into files...\n";
                    saveData();
                    break;
                default:
                    cout << "Please choose a valid option (0-8).\n";
                    break;
            }
        }
    }

    // Method that allows user to add a new client
    void addClient() {
        string name, lastname, birthdate, phone, email;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Check if a user with same name and last name exists
        while (true) {
            cout << "Enter the client's first name: ";
            getline(cin, name);

            cout << "Enter the client's last name: ";
            getline(cin, lastname);

            bool duplicate = false;
            for (Client& c : clients) {
                if (c.name == name && c.lastName == lastname) {
                    std::cout << "Error: a client with this name and surname already exists. Please try again.\n";
                    duplicate = true;
                    break;
                }
            }

            if (!duplicate) break;
        }

        //Add Birth date and checks if it's in a valid date format
        while (true) {
            cout << "Enter the client's birth date (DD/MM/YYYY): ";
            getline(cin, birthdate);

            if (birthdate.length() != 10 || birthdate[2] != '/' || birthdate[5] != '/') {
                cout << "Error: Birth date format should be dd/mm/yyyy.\n";
                continue;
            }

            string dayinput = birthdate.substr(0, 2);
            string monthinput = birthdate.substr(3, 2);
            string yearinput = birthdate.substr(6, 4);

            if (!isdigit(dayinput[0]) || !isdigit(dayinput[1])) {
                cout << "Error: day must be numeric.\n";
                continue;
            }
            int dayint = stoi(dayinput);
            if (dayint < 1 || dayint > 31) {
                cout << "Error: day must be between 1 and 31.\n";
                continue;
            }

            if (!isdigit(monthinput[0]) || !isdigit(monthinput[1])) {
                cout << "Error: month must be numeric.\n";
                continue;
            }
            int monthint = stoi(monthinput);
            if (monthint < 1 || monthint > 12) {
                cout << "Error: month must be between 1 and 12.\n";
                continue;
            }

            if (!isdigit(yearinput[0]) || !isdigit(yearinput[1]) ||
                !isdigit(yearinput[2]) || !isdigit(yearinput[3])) {
                cout << "Error: year must be numeric.\n";
                continue;
            }
            int yearint = stoi(yearinput);
            if (yearint < 1900 || yearint > 2100) {
                cout << "Error: year must be between 1900 and 2100.\n";
                continue;
            }

            break;
        }

        // Checks for Phone number in numeric format
        while (true) {
            cout << "Enter the client's phone number: ";
            getline(cin, phone);

            bool valid = !phone.empty() && all_of(phone.begin(), phone.end(), ::isdigit);
            if (valid) break;
            cout << "Invalid phone number. Please enter digits only.\n";
        }

        // Checks Email contains @ and a domain
        while (true) {
            cout << "Enter the client's email: ";
            getline(cin, email);
            size_t at_pos = email.find('@');

            if (email.find(' ') != string::npos) {
                cout << "Error: The email can not contain spaces.\n";
            } else if (at_pos == string::npos) {
                cout << "Error: The email must contain a '@' symbol.\n";
            } else if (at_pos == email.length() - 1) {
                cout << "Error: The email must contain a domain after '@'.\n";
            } else {
                break;
            }
        }

        // Add client to clients vector
        Client inputClient(current_id++, name, lastname, birthdate, email, phone);
        clients.push_back(inputClient);
        cout << "\nClient created:\n";
        inputClient.get_client();
    }



    // Allows to update's client info
    void updateClientInfo() {

            // Asks name and last name of client user wants to update
            string searchName, searchLastName;
            cout << "Please, enter the name of client you want to update: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clean buffer
            getline(cin, searchName);
            cout << "Please, enter the last name of client you want to update: ";
            getline(cin, searchLastName);

            // Search in client list the client that matches with name e lastname
            bool found = false;
            for (Client& client : clients) {
                // If found, asks the new infos
                if (client.matches(searchName,  searchLastName)){
                    found = true;
                    cout << "Client found:\n";
                    client.get_client();
                    string newName, newLastName, newBirth, newEmail, newPhone;

                    cout << "\nPlease, insert the updated info:\n";
                    cout << "Name: ";
                    getline(cin, newName);
                    cout << "Last Name: ";
                    getline(cin, newLastName);
                    cout << "Date of birth (DD/MM/YYYY): ";
                    getline(cin, newBirth);
                    cout << "Email: ";
                    getline(cin, newEmail);
                    cout << "Phone number: ";
                    getline(cin, newPhone);

                    // Update the info
                    client.name = newName;
                    client.lastName = newLastName;
                    client.birthDate = newBirth;
                    client.email = newEmail;
                    client.phone = newPhone;

                    cout << "Updated info with success!\n";
                    client.get_client();
                    break;
                }
            }
            if (!found) {
                // if not found, it prints a message and clean buffer
                cout << "Client not found.\n";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }


        }

    // Method to print all clients in InsuraPro CRM list
    void printAllClients()  {
            for (Client& client : clients) {
                client.get_client();
            }
        }

    // Method to delete client info from InsuraPro CRM list
    void deleteClient() {
            string nameInput, lastNameInput;
            cout << "Please, enter the name of client you want to delete: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, nameInput);
            cout << "Please, enter the last name of client you want to delete: ";
            getline(cin, lastNameInput);

            for (auto it = clients.begin(); it != clients.end(); ++it) {
                if (it->name == nameInput && it->lastName == lastNameInput) {
                    cout << "Client found:\n";
                    it->get_client();

                    string confirmation;
                    cout << "Are you sure? (Yes/No): ";
                    getline(cin, confirmation);

                    if (confirmation == "Yes" || confirmation == "yes") {
                        clients.erase(it);
                        cout << "Client deleted with success.\n";
                    } else {
                        cout << "No client removed.\n";
                    }
                    return;
                }
            }

            cout << "Client not found.\n";
        }

    // Search a client by name/lastname or both
    void searchClient() {
            int choice;
            string nameInput, lastNameInput;

            cout << "How do you want to search?:\n";
            cout << "1. By Name\n";
            cout << "2. By Last Name\n";
            cout << "3. By Name and Last Name\n";
            cout << "Choice: ";
            cin >> choice;

            // Pulizia buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (choice == 1) {
                cout << "Name: ";
                getline(cin, nameInput);
            } else if (choice == 2) {
                cout << "Last name: ";
                getline(cin, lastNameInput);
            } else if (choice == 3) {
                cout << "Name: ";
                getline(cin, nameInput);
                cout << "Last name: ";
                getline(cin, lastNameInput);
            } else {
                cout << "Plese, enter a valid option.\n";
                return;
            }

            bool found = false;

            for (Client& client : clients) {
                bool match = false;

                if (choice == 1 && client.name == nameInput) {
                    match = true;
                } else if (choice == 2 && client.lastName == lastNameInput) {
                    match = true;
                } else if (choice == 3 && client.name == nameInput && client.lastName == lastNameInput) {
                    match = true;
                }

                if (match) {
                    client.get_client();
                    found = true;
                }
            }

            if (!found) {
                cout << "No client found with such name and/or last name.\n";
            }
        }


    // Load Data from file at the beginning of program
    void loadData(string& filename) {
            ifstream file(filename);
            if (!file) {
                cout << "Error, please check your file " << filename << "\n";
                return;
            }

            string line;
            current_id = clients.size() + 1;

            while (getline(file, line)) {

                stringstream ss(line);
                string name, lastname, birth, email, phone;
                if (getline(ss, name, ',') &&
                    getline(ss, lastname, ',') &&
                    getline(ss, birth, ',') &&
                    getline(ss, email, ',') &&
                    getline(ss, phone)) {

                    // Add client to list
                    Client loadedClient(current_id++, name, lastname, birth, email, phone);
                    clients.push_back(loadedClient);

                    cout << "Added Client: " << name << " " << lastname << endl;  // Messaggio di debug
                    } else {
                        cout << "Error in current line: " << line << "\n";  // Debug in caso di errore nel formato
                    }
            }

            file.close();
            cout << "Data loaded with success!\n";
        }

    // Load Data from file if user decides to upload data
    void loadDataFromFile(string& filename) {
            FILE *file = fopen(filename.c_str(), "r");
            if (file != NULL) {
                fclose(file);

                cout << "The file " << filename << " exists. Do you want to load it? (Yes/No): ";
                string inputchoice;
                cin >> inputchoice;

                if (inputchoice == "Yes" || inputchoice == "yes") {
                    loadData(filename);
                } else {
                    cout << "The fill won't be loaded .\n";
                }
            } else {
                cout << "The file" << filename << "does not exist.\n";
            }
        }

    // Load Interactions data at beginning
    void loadDataInteractions(string& filename) {
            ifstream file(filename);
            if (!file.is_open()) {
                cout << "Error, please check your file: " << filename << endl;
                return;
            }

            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string name, lastname, type, description, date;


                if (getline(ss, name, ',') &&
                    getline(ss, lastname, ',') &&
                    getline(ss, type, ',') &&
                    getline(ss, description, ',') &&
                    getline(ss, date)) {


                    date.erase(remove(date.begin(), date.end(), '\r'), date.end());
                    date.erase(remove(date.begin(), date.end(), '\n'), date.end());

                    Interaction loadedInteraction(name, lastname, type, description, date);

                    bool found = false;
                    for (Client& client : clients) {
                        if (client.matches(name, lastname)) {
                            client.addInteraction(loadedInteraction);
                            found = true;
                            break;
                        }
                    }

                    if (!found) {
                        cout << "Client not found with name : " << name << " and last name: " << lastname << endl;
                    }
                    } else {
                        cout << "Error in line: " << line << endl;
                    }
            }

            file.close();
            cout << "Interactions data uploaded with success!\n";
        }

    // Load Interactions data if user decides to upload data
    void loadDataInteractionsFromFile( string& filename) {
            FILE *file = fopen(filename.c_str(), "r");
            if (file != NULL) {
                fclose(file);

                cout << "The file " << filename << " exists. Do you want to load it? (Yes/No): ";
                string inputchoice;
                cin >> inputchoice;

                if (inputchoice == "Yes" || inputchoice == "yes") {
                    loadDataInteractions(filename);
                } else {
                    cout << "The file won't be loaded.\n";
                }
            } else {
                cout << "The file " << filename << "does not exist.\n";
            }
        }

    // Save data in two files
    void saveData() {

            ofstream clientFile("./clients.csv");
            if (clientFile.is_open()) {
                for (Client& client : clients) {
                    clientFile << client.print_to_file() << endl;
                }
                clientFile.close();
                cout << "Client data saved successfully in 'clients.csv'." << endl;
            } else {
                cout << "Unable to open 'clients.csv' for writing." << endl;
            }

            ofstream interactionFile("./interactions.csv");
            if (interactionFile.is_open()) {
                for (Client& client : clients) {
                    for (Interaction& interaction : client.interactions) {
                        interactionFile << interaction.print_to_file() << endl;
                    }
                }
                interactionFile.close();
                cout << "Interaction data saved successfully in 'interactions.csv'." << endl;
            } else {
                cout << "Unable to open 'interactions.csv' for writing." << endl;
            }
        }

    // Method for Interaction management
    void manageInteractions() {
        string nameInput, lastNameInput;
        cout << "Please, enter the name of the client: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        getline(cin, nameInput);
        cout << "Please, enter the last name of the client: ";
        getline(cin, lastNameInput);


    bool found = false;

    for (Client& client : clients) {
        if (client.matches(nameInput,lastNameInput)) {
            found = true;
            cout << "Client found:\n";
            client.get_client();

            int choice = -1;
            //cin.ignore(numeric_limits<streamsize>::max(), '\n');

            while (choice != 0) {
                cout << "\n--- Manage Interactions for Client " << client.name << " " << client.lastName << " ---\n";
                cout << "1. Show all client's interactions\n";
                cout << "2. Add a new interaction\n";
                cout << "3. Find an interaction by type and/or date\n";
                cout << "0. Return to the main menu\n";
                cout << "Choice: ";
                cin >> choice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // pulizia buffer

                switch (choice) {
                    case 1: {
                        cout << "\nInterations:\n";
                        if (client.interactions.empty()) {
                            cout << "No interactions found!.\n";
                        } else {
                            for (Interaction& interaction : client.interactions) {
                                interaction.get_interaction();
                            }
                        }
                        break;
                    }

                    case 2: {
                        string type, description, date;
                        while (true) {
                            cout << "Interaction Type (Appointment/Contract): ";
                            getline(cin, type);

                            if (type == "Appointment" || type == "Contract") {
                                break;
                            } else {
                                cout << "Invalid type. Please enter 'Appointment' or 'Contract'.\n";
                            }
                        }

                        cout << "Description ";
                        getline(cin, description);
                        cout << "Date (DD/MM/YYYY): ";
                        getline(cin, date);

                        Interaction newInteraction(client.name, client.lastName, type, description, date);
                        client.addInteraction(newInteraction);
                        cout << "Interaction added with success.\n";
                        break;
                    }

                    case 3: {
                        int searchChoice;
                        cout << "\nhHow do you want to search?\n";
                        cout << "1. By Type (Appointment/Contract)\n";
                        cout << "2. By date\n";
                        cout << "3. By Type and date\n";
                        cout << "Choice: ";
                        cin >> searchChoice;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        string searchType, searchDate;

                        switch (searchChoice) {
                            case 1:
                                cout << "Please, enter the type of the interaction: ";
                                getline(cin, searchType);
                                break;
                            case 2:
                                cout << "Please, enter the date (DD/MM/YYYY): ";
                                getline(cin, searchDate);
                                break;
                            case 3:
                                cout << "Please, enter the type of the interaction:";
                                getline(cin, searchType);
                                cout << "Please, enter the date (DD/MM/YYYY): ";
                                getline(cin, searchDate);
                                break;
                            default:
                                cout << "No valid option.\n";
                                break;
                        }

                        bool foundInteraction = false;
                        for (Interaction& interaction : client.interactions) {
                            bool typeMatches = (searchChoice == 1 || searchChoice == 3) ? (interaction.type == searchType) : true;
                            bool dateMatches = (searchChoice == 2 || searchChoice == 3) ? (interaction.date == searchDate) : true;

                            if (typeMatches && dateMatches) {
                               interaction.get_interaction();
                                foundInteraction = true;
                                choice = 0;
                                break;


                            }
                        }

                        if (!foundInteraction) {
                            cout << "No interaction found with such criteria.\n";
                        }
                        break;
                    }

                    case 0:
                        cout << "Exit from Interactions' menu.\n";
                        break;

                    default:
                        cout << "No valid option.\n";
                }
            }

            break;
        }
    }

    if (!found) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Client not found!.\n";
    }
}




};











#endif