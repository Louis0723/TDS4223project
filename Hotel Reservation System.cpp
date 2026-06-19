#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Customer
{
public:
    string customerID;
    string name;
    string phone;
    string password;

    Customer() {}
    ~Customer() {}
};

struct Reservation
{
    string bookingID;
    string customerID;
    int roomNumber;
    int days;
    double totalPrice;
};

bool customerExists(string id)
{
    ifstream file("customer.txt");

    string customerID, name, phone, password;

    while (getline(file, customerID, '|'))
    {
        getline(file, name, '|');
        getline(file, phone, '|');
        getline(file, password);

        if (customerID == id)
        {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

void registerUser()
{
    Customer c;

    cout << "\n===== CUSTOMER REGISTRATION =====\n";

    cout << "Enter Customer ID: ";
    cin >> c.customerID;

    if (customerExists(c.customerID))
    {
        cout << "Customer ID already exists!\n";
        return;
    }

    cin.ignore();

    cout << "Enter Name: ";
    getline(cin, c.name);

    cout << "Enter Phone Number: ";
    getline(cin, c.phone);

    cout << "Enter Password: ";
    getline(cin, c.password);

    ofstream file("customer.txt", ios::app);

    file << c.customerID << "|"
         << c.name << "|"
         << c.phone << "|"
         << c.password << endl;

    file.close();

    cout << "\nRegistration Successful!\n";
}

bool loginUser()
{
    string id, password;

    cout << "\n===== LOGIN =====\n";

    cout << "Customer ID: ";
    cin >> id;

    cout << "Password: ";
    cin >> password;

    ifstream file("customer.txt");

    string customerID, name, phone, pass;

    while (getline(file, customerID, '|'))
    {
        getline(file, name, '|');
        getline(file, phone, '|');
        getline(file, pass);

        if (customerID == id && pass == password)
        {
            cout << "\nLogin Successful!\n";
            file.close();
            return true;
        }
    }

    file.close();

    cout << "\nInvalid Customer ID or Password!\n";
    return false;
}

void displayRooms()
{
    cout << "\n===== AVAILABLE ROOMS =====\n";

    cout << "Room No\tType\tPrice\n";
    cout << "101\tSingle\tRM100\n";
    cout << "102\tSingle\tRM100\n";
    cout << "201\tDouble\tRM180\n";
    cout << "202\tDouble\tRM180\n";
    cout << "301\tSuite\tRM350\n";
}

void bookRoom()
{
    Reservation r;

    cout << "\n===== BOOK ROOM =====\n";

    cout << "Booking ID: ";
    cin >> r.bookingID;

    cout << "Customer ID: ";
    cin >> r.customerID;

    cout << "Room Number: ";
    cin >> r.roomNumber;

    cout << "Number of Days: ";
    cin >> r.days;

    cout << "Total Price: ";
    cin >> r.totalPrice;

    ofstream file("reservation.txt", ios::app);

    file << r.bookingID << "|"
         << r.customerID << "|"
         << r.roomNumber << "|"
         << r.days << "|"
         << r.totalPrice << endl;

    file.close();

    cout << "\nRoom Reserved Successfully!\n";
}

void viewReservation()
{
    ifstream file("reservation.txt");

    string bookingID;
    string customerID;
    string roomNumber;
    string days;
    string totalPrice;

    cout << "\n===== RESERVATION RECORD =====\n";

    while (getline(file, bookingID, '|'))
    {
        getline(file, customerID, '|');
        getline(file, roomNumber, '|');
        getline(file, days, '|');
        getline(file, totalPrice);

        cout << "\nBooking ID : " << bookingID;
        cout << "\nCustomer ID: " << customerID;
        cout << "\nRoom Number: " << roomNumber;
        cout << "\nDays       : " << days;
        cout << "\nTotal Price: RM" << totalPrice;
        cout << "\n-----------------------------\n";
    }

    file.close();
}

void checkIn()
{
    string bookingID;

    cout << "\n===== CHECK IN =====\n";

    cout << "Enter Booking ID: ";
    cin >> bookingID;

    cout << "\nCheck-In Successful!\n";
}

void checkOut()
{
    string bookingID;

    cout << "\n===== CHECK OUT =====\n";

    cout << "Enter Booking ID: ";
    cin >> bookingID;

    cout << "\nCheck-Out Successful!\n";
}

void customerMenu()
{
    int choice;

    do
    {
        cout << "\n==============================";
        cout << "\n CUSTOMER MENU";
        cout << "\n==============================";
        cout << "\n1. Display Rooms";
        cout << "\n2. Book Room";
        cout << "\n3. View Reservation";
        cout << "\n4. Check In";
        cout << "\n5. Check Out";
        cout << "\n6. Logout";

        cout << "\n\nEnter Choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                displayRooms();
                break;

            case 2:
                bookRoom();
                break;

            case 3:
                viewReservation();
                break;

            case 4:
                checkIn();
                break;

            case 5:
                checkOut();
                break;

            case 6:
                cout << "\nLogged Out Successfully!\n";
                break;

            default:
                cout << "\nInvalid Choice!\n";
        }

    } while (choice != 6);
}

int main()
{
    int choice;

    do
    {
        cout << "\n================================";
        cout << "\n HOTEL RESERVATION SYSTEM";
        cout << "\n================================";
        cout << "\n1. Register";
        cout << "\n2. Login";
        cout << "\n3. Exit";

        cout << "\n\nEnter Choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                registerUser();
                break;

            case 2:
                if (loginUser())
                {
                    customerMenu();
                }
                break;

            case 3:
                cout << "\nThank You!\n";
                break;

            default:
                cout << "\nInvalid Choice!\n";
        }

    } while (choice != 3);

    return 0;
}