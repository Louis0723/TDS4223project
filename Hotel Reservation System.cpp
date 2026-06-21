 //YAP ZI YI

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdio>
#include <limits>
#include <algorithm>
using namespace std;

void searchCustomer();
void jumpSearchRoom();
void interpolationSearchPrice();
void searchBookingID();
void summaryReport();
void bookingStatistic();
void viewProfile();
void updateProfile();
void deleteAccount();
void viewAllReservations();
void cancelReservation();

void jumpSearchRoomType();
void jumpSearchAvailableRoom();
void interpolationSearchPayment();
void monthlyReport();
void roomStatistic();
void revenueStatistic();
void sortRoomRecords();

void makePayment();
void viewPaymentHistory();
void searchPaymentRecord();
void deletePaymentRecord();

void adminMenu();
bool adminLogin();
string currentCustomerID = "";
struct Node;
struct RoomNode;

RoomNode* roomHead = NULL;
Node* reservationHead = NULL;

//ZIYI
class Report
{
public:
    virtual void generateReport()
    {
        cout << "\nGenerating Report...";
    }

    virtual ~Report() {}
};

class Account
{
protected:
    string id;
    string password;

public:
    Account() {}

    Account(string i, string p)
    {
        id = i;
        password = p;
    }

    virtual ~Account() {}
};

class User : public Account
{
public:
    User() {}

    User(string i, string p) : Account(i, p) {}

    virtual ~User() {}
};

class Customer : public User
{
public:
    string customerID;
    string name;
    string phone;
    string password;

    Customer() {}

    Customer(string id, string name, string phone, string password)
    {
        customerID = id;
        this->name = name;
        this->phone = phone;
        this->password = password;
    }

    ~Customer()
    {
        // Destructor removed
    }

    void update(string newName);
    void update(string newName, string newPhone);
    void update(string newName, string newPhone, string newPassword);
    void update(string newPhone, int dummy);

    friend void displayCustomer(Customer c);
    friend void updateCustomerRecord(Customer &c);
    friend void showCustomerPassword(Customer c);
    friend void showCustomerContact(Customer c);
};

void Customer::update(string newName)
{
    name = newName;
}

void Customer::update(string newName, string newPhone)
{
    name = newName;
    phone = newPhone;
}

void Customer::update(string newName,
                      string newPhone,
                      string newPassword)
{
    name = newName;
    phone = newPhone;
    password = newPassword;
}

void Customer::update(string newPhone, int dummy)
{
    phone = newPhone;
}

class Admin : public User, public Report
{
public:
    string adminName;

    Admin() {}

    Admin(string id, string password, string name)
        : User(id, password)
    {
        adminName = name;
    }

    void generateReport() override
    {
        cout << "\nAdmin Report Generated";
    }

    ~Admin()
    {
        cout << "Admin object destroyed\n";
    }

    void showAdmin()
    {
        cout << "\nAdmin Name: " << adminName;
    }
};

class Staff : public User
{
public:
    string staffName;
    string role;

    Staff() {}

    Staff(string id, string password, string name, string r)
        : User(id, password)
    {
        staffName = name;
        role = r;
    }

    void showStaff()
    {
        cout << "\nStaff Name: " << staffName;
        cout << "\nRole: " << role;
    }
};

void displayCustomer(Customer c)
{
    cout << "\nCustomer ID : "
         << c.customerID;

    cout << "\nName : "
         << c.name;

    cout << "\nPhone : "
         << c.phone;
}

void updateCustomerRecord(Customer &c)
{
    cout << "\nEnter New Name : ";
    getline(cin, c.name);

    cout << "\nEnter New Phone : ";
    getline(cin, c.phone);
}

void showCustomerPassword(Customer c)
{
    cout << "\nCustomer ID : "
         << c.customerID;

    cout << "\nPassword : "
         << c.password;
}

void showCustomerContact(Customer c)
{
    cout << "\nCustomer Name : "
         << c.name;

    cout << "\nPhone Number : "
         << c.phone;
}

void viewAllReservations()
{
    system("cls");

    ifstream file("reservation.txt");

    string bookingID;
    string customerID;
    string roomNumber;
    string days;
    string totalPrice;

    bool found = false;
    int no = 1;

    cout << "\n\n\t\t\t\t========================================";
    cout << "\n\t\t\t\t        ALL RESERVATIONS";
    cout << "\n\t\t\t\t========================================";

    while(getline(file, bookingID, '|'))
    {
        getline(file, customerID, '|');
        getline(file, roomNumber, '|');
        getline(file, days, '|');
        getline(file, totalPrice);

        found = true;

        cout << "\n\n\t\t\t\tReservation #" << no++;

        cout << "\n\t\t\t\tBooking ID   : "
             << bookingID;

        cout << "\n\t\t\t\tCustomer ID  : "
             << customerID;

        cout << "\n\t\t\t\tRoom Number  : "
             << roomNumber;

        cout << "\n\t\t\t\tDays Stayed  : "
             << days;

        cout << "\n\t\t\t\tTotal Price  : RM"
             << totalPrice;

        cout << "\n\t\t\t\t----------------------------------------";
    }

    if(!found)
    {
        cout << "\n\n\t\t\t\tNo Reservation Found!";
    }

    file.close();
    system("pause");
}

struct Reservation
{
    string bookingID;
    string customerID;
    int roomNumber;
    int days;
    double totalPrice;
};

struct Node
{
    Reservation data;
    Node* next;
};

void insertReservationList(Reservation r)
{
    Node* newNode = new Node;

    newNode->data = r;
    newNode->next = NULL;

    if(reservationHead == NULL)
    {
        reservationHead = newNode;
    }
    else
    {
        Node* temp = reservationHead;

        while(temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = newNode;
    }
}

void displayReservationList()
{
    system("cls");

    Node* temp = reservationHead;

    cout << "\n===== LINKED LIST RESERVATIONS =====\n";

    if(reservationHead == NULL)
    {
        cout << "\nNo reservations in linked list.";
        system("pause");
        return;
    }

    while(temp != NULL)
    {
        cout << "\nBooking ID : "
             << temp->data.bookingID;

        cout << "\nCustomer ID : "
             << temp->data.customerID;

        cout << "\nRoom Number : "
             << temp->data.roomNumber;

        cout << "\nDays : "
             << temp->data.days;

        cout << "\nTotal Price : RM"
             << temp->data.totalPrice;

        cout << "\n----------------------";

        temp = temp->next;
    }

    system("pause");
}

void viewProfile()
{
    system("cls");

    string id = currentCustomerID;

    ifstream file("customer.txt");

    string customerID,name,phone,password;

    bool found = false;

    while(getline(file,customerID,'|'))
    {
        getline(file,name,'|');
        getline(file,phone,'|');
        getline(file,password);

        if(customerID == id)
        {
            found = true;

            cout << "\nCustomer ID : "
                 << customerID;

            cout << "\nName : "
                 << name;

            cout << "\nPhone : "
                 << phone;

            break;
        }
    }

    if(!found)
    {
        cout << "\nCustomer Not Found";
    }

    file.close();

    system("pause");
}

void updateProfile()
{
    system("cls");

    string id = currentCustomerID;

    ifstream file("customer.txt");
    ofstream temp("temp.txt");

    string customerID,name,phone,password;

    bool found = false;

    while(getline(file,customerID,'|'))
    {
        getline(file,name,'|');
        getline(file,phone,'|');
        getline(file,password);

        if(customerID == id)
        {
            found = true;

            cin.ignore();

            cout << "\nNew Name : ";
            getline(cin,name);

            cout << "\nNew Phone : ";
            getline(cin,phone);

            cout << "\nNew Password : ";
            getline(cin,password);
        }

        temp << customerID << "|"
             << name << "|"
             << phone << "|"
             << password << endl;
    }

    file.close();
    temp.close();

    remove("customer.txt");
    rename("temp.txt","customer.txt");

    if(found)
        cout << "\nProfile Updated!";
    else
        cout << "\nCustomer Not Found";

    system("pause");
}

void deleteAccount()
{
    system("cls");

    string id = currentCustomerID;

    ifstream file("customer.txt");
    ofstream temp("temp.txt");

    string customerID,name,phone,password;

    bool found = false;

    while(getline(file,customerID,'|'))
    {
        getline(file,name,'|');
        getline(file,phone,'|');
        getline(file,password);

        if(customerID == id)
        {
            found = true;
            continue;
        }

        temp << customerID << "|"
             << name << "|"
             << phone << "|"
             << password << endl;
    }

    file.close();
    temp.close();

    remove("customer.txt");
    rename("temp.txt","customer.txt");

    if(found)
        cout << "\nAccount Deleted!";
    else
        cout << "\nCustomer Not Found";

    system("pause");
}

//ZIYI


//LOUIS
struct Room
{
    int roomNumber;
    string roomType;
    double price;
};

Room roomList[5] =
{
    {101, "Single", 100},
    {102, "Single", 100},
    {201, "Double", 180},
    {202, "Double", 180},
    {301, "Suite", 350}
};
//ONG ZHENG HAO)
// ROOM MANAGEMENT MODULE 

struct RoomRecord
{
    int roomNumber;
    string roomType;
    double price;
};

struct RoomNode
{
    RoomRecord data;
    RoomNode* next;
};

struct Payment
{
    string paymentID;
    string bookingID;
    double amount;
    string method;
};

struct CustomerRecord
{
    string customerID;
    string name;
    string phone;
    string password;
};

// ADD ROOM
void addRoomRecord()
{
    system("cls");

    RoomRecord r;

    cout << "\n\n\t\t\t\t============ ADD NEW ROOM ============\n";

    cout << "\n\n\t\t\t\tEnter Room Number: ";
    cin >> r.roomNumber;

    cin.ignore();

    cout << "\n\n\t\t\t\tEnter Room Type: ";
    getline(cin, r.roomType);

    cout << "\n\n\t\t\t\tEnter Price: RM";
    cin >> r.price;

    ofstream file("room.txt", ios::app);

    file << r.roomNumber << "|"
         << r.roomType << "|"
         << r.price << endl;

    file.close();

    cout << "\n\n\t\t\t\tRoom Added Successfully!\n";
    system("pause");
}


// DISPLAY ROOMS FROM FILE
void displayRoomRecords()
{
    system("cls");

    ifstream file("room.txt");

    string roomNumber, roomType, price;

    cout << "\n\n\t\t\t\t============= ROOM LIST (DATABASE) =============\n";

    while(getline(file, roomNumber, '|'))
    {
        getline(file, roomType, '|');
        getline(file, price);

        cout << "\n\n\t\t\t\tRoom No   : " << roomNumber;
        cout << "\n\n\t\t\t\tType      : " << roomType;
        cout << "\n\n\t\t\t\tPrice     : RM" << price;
        cout << "\n\n\t\t\t\t--------------------------------\n";
    }

    file.close();

    system("pause");
}


// UPDATE ROOM
void updateRoomRecord()
{
    system("cls");
	cout << "\n\n\t\t\t\t============= Update Room =============\n";
    string id;
    cout << "\n\n\t\t\t\tEnter Room Number to Update: ";
    cin >> id;

    ifstream file("room.txt");
    ofstream temp("temp.txt");

    string roomNumber, roomType, price;

    bool found = false;

    while(getline(file, roomNumber, '|'))
    {
        getline(file, roomType, '|');
        getline(file, price);

        if(roomNumber == id)
        {
            found = true;

            cin.ignore();
			
            cout << "\n\n\t\t\t\tEnter New Room Type: ";
            getline(cin, roomType);

            cout << "\n\n\t\t\t\tEnter New Price: RM";
            cin >> price;
        }

        temp << roomNumber << "|"
             << roomType << "|"
             << price << endl;
    }

    file.close();
    temp.close();

    remove("room.txt");
    rename("temp.txt", "room.txt");

    if(found)
        cout << "\n\n\t\t\t\tRoom Updated Successfully!\n";
    else
        cout << "\n\n\t\t\t\tRoom Not Found!\n";

    system("pause");
}


// DELETE ROOM
void deleteRoomRecord()
{
    system("cls");
	cout << "\n\n\t\t\t\t============= Delete Room =============\n";
    string id;
    cout << "\n\n\t\t\t\tEnter Room Number to Delete: ";
    cin >> id;

    ifstream file("room.txt");
    ofstream temp("temp.txt");

    string roomNumber, roomType, price;

    bool found = false;

    while(getline(file, roomNumber, '|'))
    {
        getline(file, roomType, '|');
        getline(file, price);

        if(roomNumber == id)
        {
            found = true;
            continue;
        }

        temp << roomNumber << "|"
             << roomType << "|"
             << price << endl;
    }

    file.close();
    temp.close();

    remove("room.txt");
    rename("temp.txt", "room.txt");

    if(found)
        cout << "\n\n\t\t\t\tRoom Deleted Successfully!\n";
    else
        cout << "\n\n\t\t\t\tRoom Not Found!\n";

    system("pause");
}


// SEARCH ROOM (SIMPLE LINEAR SEARCH)
void searchRoomRecord()
{
    system("cls");
	cout << "\n\n\t\t\t\t============= Search Room =============\n";
    string id;
    cout << "\n\n\t\t\t\tEnter Room Number to Search: ";
    cin >> id;

    ifstream file("room.txt");

    string roomNumber, roomType, price;
    bool found = false;

    while(getline(file, roomNumber, '|'))
    {
        getline(file, roomType, '|');
        getline(file, price);

        if(roomNumber == id)
        {
            found = true;

            cout << "\n\n\t\t\t\tRoom Found!";
            cout << "\n\n\t\t\t\tRoom No : " << roomNumber;
            cout << "\n\n\t\t\t\tType    : " << roomType;
            cout << "\n\n\t\t\t\tPrice   : RM" << price;
            break;
        }
    }

    file.close();

    if(!found)
        cout << "\n\n\t\t\t\tRoom Not Found!\n";

    system("pause");
}
// SORT ROOM RECORDS USING BUBBLE SORT
void sortRoomRecords()
{
    system("cls");

    RoomRecord room[100];
    int count = 0;

    ifstream file("room.txt");

    string roomNumber, roomType, price;

    while(getline(file, roomNumber, '|'))
    {
        getline(file, roomType, '|');
        getline(file, price);

        room[count].roomNumber = stoi(roomNumber);
        room[count].roomType = roomType;
        room[count].price = stod(price);

        count++;
    }

    file.close();

    // Bubble Sort by Room Number
    for(int i = 0; i < count - 1; i++)
    {
        for(int j = 0; j < count - i - 1; j++)
        {
            if(room[j].roomNumber > room[j + 1].roomNumber)
            {
                RoomRecord temp = room[j];
                room[j] = room[j + 1];
                room[j + 1] = temp;
            }
        }
    }

    cout << "\n\n\t\t\t\t============= SORTED ROOM RECORDS =============\n";

    for(int i = 0; i < count; i++)
    {
        cout << "\n\n\t\t\t\tRoom Number : " << room[i].roomNumber;
        cout << "\n\n\t\t\t\tRoom Type   : " << room[i].roomType;
        cout << "\n\n\t\t\t\tPrice       : RM" << room[i].price;
        cout << "\n\n\t\t\t\t--------------------------------\n";
    }

    system("pause");
}

//LOUIS

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
    system("cls");

    Customer c;

    cout << "\n\n\t\t\t\t===== CUSTOMER REGISTRATION =====\n";

    cout << "\n\n\t\t\t\tEnter Customer ID: ";
    cin >> c.customerID;

    if(customerExists(c.customerID))
    {
        cout << "\n\n\t\t\t\tCustomer ID already exists!\n";
        system("pause");
        return;
    }

    cin.ignore();

    cout << "\n\n\t\t\t\tEnter Name: ";
    getline(cin, c.name);

    cout << "\n\n\t\t\t\tEnter Phone Number: ";
    getline(cin, c.phone);

    cout << "\n\n\t\t\t\tEnter Password: ";
    getline(cin, c.password);

    ofstream file("customer.txt", ios::app);

    if(!file)
    {
        cout << "\n\n\t\t\t\tError Opening customer.txt";
        system("pause");
        return;
    }

    file << c.customerID << "|"
         << c.name << "|"
         << c.phone << "|"
         << c.password << endl;

    file.close();

    cout << "\n\n\t\t\t\tRegistration Successful!\n";

    system("pause");
}

bool loginUser()
{
	system("cls");
	
	
    string id, password;

    cout << "\n\n\t\t\t\t===== LOGIN =====\n";

    cout << "\n\n\t\t\t\tCustomer ID: ";
    cin >> id;

    cout << "\n\n\t\t\t\tPassword: ";
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
            currentCustomerID = customerID;

            cout << "\nLogin Successful!\n";
            file.close();
            return true;
        }
    }

    file.close();

    cout << "\n\n\t\t\t\tInvalid Customer ID or Password!\n";
    system("pause");
    return false;
    
      
}

void displayRooms()
{
    system("cls");

    cout << "\n\t========================================================";
    cout << "\n\tRoom No\tRoom Type\tPrice\t\tStatus";
    cout << "\n\t========================================================";

    for(int i = 0; i < 5; i++)
    {
        bool booked = false;

        ifstream file("reservation.txt");

        string bookingID, customerID, roomNo, days, totalPrice;

        while(getline(file, bookingID, '|'))
        {
            getline(file, customerID, '|');
            getline(file, roomNo, '|');
            getline(file, days, '|');
            getline(file, totalPrice);

            if(stoi(roomNo) == roomList[i].roomNumber)
            {
                booked = true;
                break;
            }
        }

        file.close();

        cout << "\n\t"
             << roomList[i].roomNumber
             << "\t"
             << roomList[i].roomType
             << "\t\tRM"
             << roomList[i].price
             << "\t\t";

        if(booked)
            cout << "Booked";
        else
            cout << "Available";
    }

    cout << "\n\t========================================================";

    system("pause");
}

void bookRoom()
{
    Reservation *r = new Reservation;

    system("cls");

    cout << "\n\n\t\t\t\t===== BOOK ROOM =====\n";

    ifstream readFile("reservation.txt");

    string bookingID, customerID, roomNo, days, totalPrice;
    string lastBookingID = "";

    while(getline(readFile, bookingID, '|'))
    {
        getline(readFile, customerID, '|');
        getline(readFile, roomNo, '|');
        getline(readFile, days, '|');
        getline(readFile, totalPrice);

        lastBookingID = bookingID;
    }

    readFile.close();

    int nextNumber = 1;

    if(!lastBookingID.empty())
    {
        nextNumber = stoi(lastBookingID.substr(1)) + 1;
    }

    if(nextNumber < 10)
        r->bookingID = "B00" + to_string(nextNumber);
    else if(nextNumber < 100)
        r->bookingID = "B0" + to_string(nextNumber);
    else
        r->bookingID = "B" + to_string(nextNumber);

    cout << "\n\n\t\t\t\tGenerated Booking ID : "
         << r->bookingID;

    r->customerID = currentCustomerID;

    cout << "\n\n\t\t\t\tRoom Number: ";
    cin >> r->roomNumber;

    cout << "\n\n\t\t\t\tNumber of Days: ";
    cin >> r->days;

    // Check duplicate booking
ifstream check("reservation.txt");

string bID, cID, checkRoomNo, checkDays, total;

while(getline(check, bID, '|'))
{
    getline(check, cID, '|');
    getline(check, checkRoomNo, '|');
    getline(check, checkDays, '|');
    getline(check, total);

    if(stoi(checkRoomNo) == r->roomNumber)
    {
        cout << "\n\n\t\t\t\tRoom Already Booked!";
        check.close();

        delete r;
        system("pause");
        return;
    }
}

check.close();

    double roomPrice = 0;

    if(r->roomNumber == 101 || r->roomNumber == 102)
    {
        roomPrice = 100;
    }
    else if(r->roomNumber == 201 || r->roomNumber == 202)
    {
        roomPrice = 180;
    }
    else if(r->roomNumber == 301)
    {
        roomPrice = 350;
    }
    else
    {
        cout << "\n\n\t\t\t\tInvalid Room Number!";
        system("pause");
        delete r;
        return;
    }

    if(r->days <= 0)
    {
        cout << "\n\n\t\t\t\tInvalid Number of Days!";
        system("pause");
        delete r;
        return;
    }

    r->totalPrice = roomPrice * r->days;

cout << "\n\n\t\t\t\t================================";
cout << "\n\t\t\t\t       BOOKING SUMMARY";
cout << "\n\t\t\t\t================================";

cout << "\n\n\t\t\t\tBooking ID      : "
     << r->bookingID;

cout << "\n\t\t\t\tCustomer ID     : "
     << r->customerID;

cout << "\n\t\t\t\tRoom Number     : "
     << r->roomNumber;

cout << "\n\t\t\t\tDays Stayed     : "
     << r->days;

cout << "\n\t\t\t\tPrice Per Day   : RM"
     << roomPrice;

cout << "\n\t\t\t\tTotal Payment   : RM"
     << r->totalPrice;

cout << "\n\t\t\t\t================================";

    ofstream file("reservation.txt", ios::app);

    file << r->bookingID << "|"
         << r->customerID << "|"
         << r->roomNumber << "|"
         << r->days << "|"
         << r->totalPrice << endl;

    file.close();

    cout << "\n\n\t\t\t\tRoom Reserved Successfully!";

    insertReservationList(*r);

    cout << "\n\n\t\t\t\tYour Booking ID is : "
     << r->bookingID << "\n";

    delete r;
    system("pause");
}


void viewReservation()
{
    system("cls");

    ifstream file("reservation.txt");

    string bookingID;
    string customerID;
    string roomNumber;
    string days;
    string totalPrice;

    bool found = false;
    int no = 1;

    cout << "\n\n\t\t\t\t===== RESERVATION RECORD =====\n";

    while(getline(file, bookingID, '|'))
    {
        getline(file, customerID, '|');
        getline(file, roomNumber, '|');
        getline(file, days, '|');
        getline(file, totalPrice);

        if(customerID == currentCustomerID)
        {
            found = true;

            cout << "\n\n\t\t\t\t================================";
            cout << "\n\t\t\t\tReservation #" << no++;
            cout << "\n\t\t\t\t================================";

            cout << "\n\t\t\t\tBooking ID   : " << bookingID;
            cout << "\n\t\t\t\tCustomer ID  : " << customerID;
            cout << "\n\t\t\t\tRoom Number  : " << roomNumber;
            cout << "\n\t\t\t\tDays Stayed  : " << days;
            cout << "\n\t\t\t\tTotal Price  : RM" << totalPrice;
        }
    }

    if(!found)
    {
        cout << "\n\n\t\t\t\tNo Reservation Found!";
    }

    file.close();
    system("pause");
}

void cancelReservation()
{
    system("cls");

    string bookingID;

    cout << "\n\n\t\t\t\t===== CANCEL RESERVATION =====";
    cout << "\n\n\t\t\t\tEnter Booking ID : ";
    cin >> bookingID;

    ifstream file("reservation.txt");
    ofstream temp("temp.txt");

    string bID, cID, roomNo, days, totalPrice;

    bool found = false;

    while(getline(file, bID, '|'))
    {
        getline(file, cID, '|');
        getline(file, roomNo, '|');
        getline(file, days, '|');
        getline(file, totalPrice);

        if(bID == bookingID &&
        cID == currentCustomerID)
        {
            char confirm;

            cout << "\n\n\t\t\t\tBooking Found";
            cout << "\n\t\t\t\tRoom Number : " << roomNo;
            cout << "\n\t\t\t\tTotal Price : RM" << totalPrice;

            cout << "\n\n\t\t\t\tConfirm Cancel (Y/N) : ";
            cin >> confirm;

            if(confirm == 'Y' || confirm == 'y')
            {
                found = true;
                continue;
            }
        }

        temp << bID << "|"
             << cID << "|"
             << roomNo << "|"
             << days << "|"
             << totalPrice << endl;
    }

    file.close();
    temp.close();

    remove("reservation.txt");
    rename("temp.txt", "reservation.txt");

    if(found)
    {
        cout << "\n\n\t\t\t\tReservation Cancelled Successfully!";
    }
    else
    {
        cout << "\n\n\t\t\t\tBooking Not Found!";
    }

    system("pause");
}

void checkIn()
{
    system("cls");

    string bookingID;

    cout << "\nEnter Booking ID : ";
    cin >> bookingID;

    ofstream file("checkin.txt",ios::app);

    file << bookingID << endl;

    file.close();

    cout << "\nCheck-In Successful!";

    system("pause");
}

void checkOut()
{
    system("cls");

    string bookingID;

    cout << "\nEnter Booking ID : ";
    cin >> bookingID;

    ofstream file("checkout.txt",ios::app);

    file << bookingID << endl;

    file.close();

    cout << "\nCheck-Out Successful!";

    system("pause");
}

void makePayment()
{
    system("cls");

    Payment p;

    cout << "\n\n\t\t\t\t===== PAYMENT =====";

    cout << "\n\n\t\t\t\tEnter Payment ID : ";
    cin >> p.paymentID;

    cout << "\n\n\t\t\t\tEnter Booking ID : ";
    cin >> p.bookingID;

    cout << "\n\n\t\t\t\tEnter Amount : RM";
    cin >> p.amount;

cin.ignore(numeric_limits<streamsize>::max(), '\n'); // FIX HERE

    cout << "\n\n\t\t\t\tPayment Method : ";
    getline(cin, p.method);

    ofstream file("payment.txt", ios::app);

    file << p.paymentID << "|"
         << p.bookingID << "|"
         << p.amount << "|"
         << p.method << endl;

    file.close();

    cout << "\n\n\t\t\t\tPayment Successful!";

    system("pause");
}
//ZIYI

//ADMIN LOGIN LOUIS
bool adminLogin()
{
    system("cls");

    string username, password;
        cout << "\n\n\t\t\t\t================================";
        cout << "\n\t\t\t\t\tAdmin Login";
        cout << "\n\t\t\t\t================================";
    cout << "\n\n\t\t\t\tUsername : ";
    cin >> username;

    cout << "\n\n\t\t\t\tPassword : ";
    cin >> password;

    ifstream file("admin.txt");

    if(!file)
    {
        cout << "\n\n\t\t\t\tCannot open admin.txt";
        system("pause");
        return false;
    }

    string user, pass;

    while(getline(file, user, '|'))
    {
        getline(file, pass);


        if(user == username && pass == password)
        {
            cout << "\n\n\t\t\t\tLogin Successful!";
            system("pause");
            return true;
        }
    }

    cout << "\n\n\t\t\t\tInvalid Username or Password!";
    system("pause");

    return false;
}


//ADMIN LOGIN LOUIS

//ZIYI
void customerMenu()
{
    int choice;

    do
    {
system("cls");

cout << "\n\n";
cout << "\t\t=====================================================\n";
cout << "\t\t              HOTEL RESERVATION SYSTEM\n";
cout << "\t\t                  CUSTOMER MENU\n";
cout << "\t\t=====================================================\n";

cout << "\n\t\tBOOKING SERVICES";
cout << "\n\t\t-----------------------------------------------------";
cout << "\n\t\t1.  Display Rooms";
cout << "\n\t\t2.  Book Room";
cout << "\n\t\t3.  View Reservation";

cout << "\n\n\t\tPayment Services";
cout << "\n\t\t-----------------------------------------------------";
cout << "\n\t\t4.  Make Payment";
cout << "\n\t\t5.  View Payment History";

cout << "\n\n\t\tCHECK-IN SERVICES";
cout << "\n\t\t-----------------------------------------------------";
cout << "\n\t\t6.  Check In";
cout << "\n\t\t7.  Check Out";

cout << "\n\n\t\tSEARCH SERVICES";
cout << "\n\t\t-----------------------------------------------------";
cout << "\n\t\t8.  Search Room Number";
cout << "\n\t\t9.  Search Room Type";
cout << "\n\t\t10.  Search Available Room";
cout << "\n\t\t11.  Search Room Price";
cout << "\n\t\t12. Search Booking ID";

cout << "\n\n\t\tPROFILE MANAGEMENT";
cout << "\n\t\t-----------------------------------------------------";
cout << "\n\t\t13. Logout";
cout << "\n\t\t14. View Profile";
cout << "\n\t\t15. Update Profile";
cout << "\n\t\t16. Delete Account";
cout << "\n\t\t17. Display Reservation Linked List";
cout << "\n\t\t18. Cancel Reservation";

cout << "\n\n\t\t=====================================================";
cout << "\n\t\tEnter Choice : ";

cin >> choice;

if(cin.fail())
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\nInvalid Input!";
    system("pause");
    continue;
}

        switch(choice)
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
			    makePayment();
			    break;
			
			case 5:
			    viewPaymentHistory();
			    break;
			    
            case 6:
                checkIn();
                break;

            case 7:
                checkOut();
                break;

            case 8:
                jumpSearchRoom();
                break;

           case 9:
                jumpSearchRoomType();
                break;

          case 10:
               jumpSearchAvailableRoom();
               break;

         case 11:
               interpolationSearchPrice();
               break;

         case 12:
               searchBookingID();
               break;

        case 13:
               break;

        case 14:
            viewProfile();
            break;

        case 15:
            updateProfile();
            break;

        case 16:
            deleteAccount();
            break;

        case 17:
            displayReservationList();
            break;

        case 18:
            cancelReservation();
            break;

        default:
            cout << "\n\n\t\t\t\tInvalid Choice!";
            system("pause");
        }

    } while(choice != 13);
}
//ZIYI


//LOUIS



void jumpSearchRoom()
{
    system("cls");

    int key;

    cout << "\n\n\t\t\t\t===================================";
    cout << "\n\t\t\t\t      JUMP SEARCH ROOM";
    cout << "\n\t\t\t\t===================================";

    cout << "\n\n\t\t\t\tEnter Room Number : ";
    cin >> key;

    int n = 5;
    int step = sqrt(n);
    int prev = 0;

    while (roomList[min(step, n) - 1].roomNumber < key)
    {
        prev = step;
        step += sqrt(n);

        if (prev >= n)
        {
            cout << "\n\n\t\t\t\tRoom Not Found!";
            return;
        }
    }

    while (roomList[prev].roomNumber < key)
    {
        prev++;

        if (prev == min(step, n))
        {
            cout << "\n\n\t\t\t\tRoom Not Found!";
            return;
        }
    }

    if (roomList[prev].roomNumber == key)
    {
        cout << "\n\n\t\t\t\tRoom Found!";
        cout << "\n\t\t\t\tRoom Number : " << roomList[prev].roomNumber;
        cout << "\n\t\t\t\tRoom Type   : " << roomList[prev].roomType;
        cout << "\n\t\t\t\tPrice       : RM" << roomList[prev].price;
    }
    else
    {
        cout << "\n\n\t\t\t\tRoom Not Found!";
    }

    cout << "\n\n\t\t\t\t";
    system("pause");
}
//LOUIS


//LOUIS

void interpolationSearchPrice()
{
    system("cls");

    double key;

    double prices[5] = {100,100,180,180,350};

    cout << "\n\n\t\t\t\t===================================";
    cout << "\n\t\t\t\t  INTERPOLATION SEARCH PRICE";
    cout << "\n\t\t\t\t===================================";

    cout << "\n\n\t\t\t\tEnter Room Price : RM";
    cin >> key;

    int low = 0;
    int high = 4;
    bool found = false;

    while (low <= high &&
           key >= prices[low] &&
           key <= prices[high])
    {
        if (low == high)
        {
            if (prices[low] == key)
            {
                found = true;

                cout << "\n\n\t\t\t\tPrice Found!";
                cout << "\n\t\t\t\tRoom Price : RM" << prices[low];
            }
            break;
        }

        if(prices[high] == prices[low])
        {
            if(prices[low] == key)
                found = true;
            break;
        }

        int pos = low +
                  (((double)(high - low) /
                   (prices[high] - prices[low])) *
                   (key - prices[low]));

        if (prices[pos] == key)
        {
            found = true;

            cout << "\n\n\t\t\t\tPrice Found!";
            cout << "\n\t\t\t\tRoom Price : RM" << prices[pos];

            break;
        }

        if (prices[pos] < key)
            low = pos + 1;
        else
            high = pos - 1;
    }

    if(!found)
    {
        cout << "\n\n\t\t\t\tPrice Not Found!";
        cout << "\n\t\t\t\tAvailable Prices:";
        cout << "\n\t\t\t\tRM100";
        cout << "\n\t\t\t\tRM180";
        cout << "\n\t\t\t\tRM350";
    }

    cout << "\n\n\t\t\t\t";
    system("pause");
}


//LOUIS
void searchBookingID()
{
    system("cls");

    string bookingID;
    bool found = false;

    cout << "\n\n\t\t\t\t===================================";
    cout << "\n\t\t\t\t     SEARCH BOOKING ID";
    cout << "\n\t\t\t\t===================================";

    cout << "\n\n\t\t\t\tEnter Booking ID : ";
    cin >> bookingID;

    ifstream file("reservation.txt");

    string bID, cID, roomNo, days, totalPrice;

    while(getline(file, bID, '|'))
    {
        getline(file, cID, '|');
        getline(file, roomNo, '|');
        getline(file, days, '|');
        getline(file, totalPrice);

        if(bID == bookingID)
        {
            found = true;

            cout << "\n\n\t\t\t\tBooking Found!";
            cout << "\n\n\t\t\t\tBooking ID  : " << bID;
            cout << "\n\t\t\t\tCustomer ID : " << cID;
            cout << "\n\t\t\t\tRoom Number : " << roomNo;
            cout << "\n\t\t\t\tDays        : " << days;
            cout << "\n\t\t\t\tTotal Price : RM" << totalPrice;

            break;
        }
    }
    file.close();

if(!found)
{
    cout << "\n\n\t\t\t\tBooking ID Not Found!";
}

system("pause");
}


void searchCustomer()
{
    system("cls");

    CustomerRecord customer[100];
    int count = 0;

    ifstream file("customer.txt");

    while(getline(file, customer[count].customerID, '|'))
    {
        getline(file, customer[count].name, '|');
        getline(file, customer[count].phone, '|');
        getline(file, customer[count].password);
        count++;
    }

    file.close();

    // Bubble Sort Customer ID
    for(int i = 0; i < count - 1; i++)
    {
        for(int j = 0; j < count - i - 1; j++)
        {
            if(customer[j].customerID > customer[j + 1].customerID)
            {
                CustomerRecord temp = customer[j];
                customer[j] = customer[j + 1];
                customer[j + 1] = temp;
            }
        }
    }

    string key;

    cout << "\n\n\t\t\t\t===================================";
    cout << "\n\t\t\t\t      JUMP SEARCH CUSTOMER";
    cout << "\n\t\t\t\t===================================";

    cout << "\n\n\t\t\t\tEnter Customer ID : ";
    cin >> key;

    int n = count;
    int step = sqrt(n);
    int prev = 0;

    while(customer[min(step, n) - 1].customerID < key)
    {
        prev = step;
        step += sqrt(n);

        if(prev >= n)
        {
            cout << "\n\n\t\t\t\tCustomer Not Found!";
            system("pause");
            return;
        }
    }

    while(customer[prev].customerID < key)
    {
        prev++;

        if(prev == min(step, n))
        {
            cout << "\n\n\t\t\t\tCustomer Not Found!";
            system("pause");
            return;
        }
    }

    if(customer[prev].customerID == key)
    {
        cout << "\n\n\t\t\t\t===================================";
        cout << "\n\t\t\t\t      CUSTOMER FOUND";
        cout << "\n\t\t\t\t===================================";

        cout << "\n\n\t\t\t\tCustomer ID : "
             << customer[prev].customerID;

        cout << "\n\t\t\t\tName        : "
             << customer[prev].name;

        cout << "\n\t\t\t\tPhone       : "
             << customer[prev].phone;

        cout << "\n\t\t\t\tPassword    : "
             << customer[prev].password;

        cout << "\n\n\t\t\t\t===================================";
    }
    else
    {
        cout << "\n\n\t\t\t\tCustomer Not Found!";
    }

    system("pause");
}


//LOUIS

//LOUIS
void summaryReport()
{
    system("cls");

    ifstream file("reservation.txt");

    string bookingID;
    string customerID;
    string roomNumber;
    string days;
    string totalPrice;

    int totalBooking = 0;
    double totalIncome = 0;

    while(getline(file, bookingID, '|'))
    {
        getline(file, customerID, '|');
        getline(file, roomNumber, '|');
        getline(file, days, '|');
        getline(file, totalPrice);

        totalBooking++;
        totalIncome += stod(totalPrice);
    }

    file.close();

    cout << "\n\n\t\t\t\t===================================";
    cout << "\n\t\t\t\t       SUMMARY REPORT";
    cout << "\n\t\t\t\t===================================";

    cout << "\n\n\t\t\t\tTotal Booking : "
         << totalBooking;

    cout << "\n\t\t\t\tTotal Revenue : RM"
         << totalIncome;
     
     double averageRevenue = 0;

if(totalBooking > 0)
{
    averageRevenue = totalIncome / totalBooking;
}

cout << "\n\t\t\t\tAverage Revenue : RM"
     << averageRevenue;
     
    cout << "\n\n\t\t\t\t===================================";

    cout << "\n\n\t\t\t\t";
    system("pause");
}
//LOUIS

//LOUIS
void bookingStatistic()
{
    system("cls");

    ifstream file("reservation.txt");

    string bookingID;
    string customerID;
    string roomNumber;
    string days;
    string totalPrice;

    int singleRoom = 0;
    int doubleRoom = 0;
    int suiteRoom = 0;

    while(getline(file, bookingID, '|'))
    {
        getline(file, customerID, '|');
        getline(file, roomNumber, '|');
        getline(file, days, '|');
        getline(file, totalPrice);

        int room = stoi(roomNumber);

        if(room == 101 || room == 102)
            singleRoom++;

        else if(room == 201 || room == 202)
            doubleRoom++;

        else if(room == 301)
            suiteRoom++;
    }

    file.close();

    cout << "\n\n\t\t\t\t===================================";
    cout << "\n\t\t\t\t      BOOKING STATISTICS";
    cout << "\n\t\t\t\t===================================";

    cout << "\n\n\t\t\t\tSingle Room Booking : "
         << singleRoom;

    cout << "\n\t\t\t\tDouble Room Booking : "
         << doubleRoom;

    cout << "\n\t\t\t\tSuite Room Booking  : "
         << suiteRoom;

    cout << "\n\n\t\t\t\t===================================";

    cout << "\n\n\t\t\t\t";
    system("pause");
}

void jumpSearchRoomType()
{
    system("cls");

    string type;

    cout << "\n\n\t\t\t\tEnter Room Type : ";
    cin >> type;

    bool found = false;

    for(int i=0;i<5;i++)
    {
        if(roomList[i].roomType == type)
        {
            found = true;

            cout << "\n\n\t\t\t\tRoom Number : "
                 << roomList[i].roomNumber;

            cout << "\n\t\t\t\tPrice : RM"
                 << roomList[i].price;
        }
    }

    if(!found)
    {
        cout << "\n\n\t\t\t\tRoom Type Not Found";
    }

    system("pause");
}

void jumpSearchAvailableRoom()
{
    system("cls");

    bool found = false;

    cout << "\n\n\t\t\t\tAVAILABLE ROOMS\n";

    for(int i = 0; i < 5; i++)
    {
        bool booked = false;

        ifstream file("reservation.txt");

        string bookingID, customerID, roomNo, days, totalPrice;

        while(getline(file, bookingID, '|'))
        {
            getline(file, customerID, '|');
            getline(file, roomNo, '|');
            getline(file, days, '|');
            getline(file, totalPrice);

            if(stoi(roomNo) == roomList[i].roomNumber)
            {
                booked = true;
                break;
            }
        }

        file.close();

        if(!booked)
        {
            found = true;

            cout << "\n\t\t\t\tRoom Number : "
                 << roomList[i].roomNumber;

            cout << "\n\t\t\t\tRoom Type   : "
                 << roomList[i].roomType;

            cout << "\n\t\t\t\tPrice       : RM"
                 << roomList[i].price;

            cout << "\n\t\t\t\t-----------------------";
        }
    }

    if(!found)
    {
        cout << "\n\n\t\t\t\tNo Available Rooms!";
    }

    system("pause");
}

void interpolationSearchPayment()
{
    system("cls");

    double payment;

    cout << "\n\n\t\t\t\tEnter Payment : RM";
    cin >> payment;

    ifstream file("reservation.txt");

    string bookingID;
    string customerID;
    string roomNumber;
    string days;
    string totalPrice;

    bool found = false;

    while(getline(file, bookingID, '|'))
    {
        getline(file, customerID, '|');
        getline(file, roomNumber, '|');
        getline(file, days, '|');
        getline(file, totalPrice);

        if(stod(totalPrice) == payment)
        {
            found = true;

            cout << "\n\n\t\t\t\tBooking ID : "
                 << bookingID;
        }
    }

    if(!found)
    {
        cout << "\n\n\t\t\t\tPayment Not Found";
    }

    file.close();

    system("pause");
}
void monthlyReport()
{
    system("cls");

    ifstream file("reservation.txt");

    string bookingID, customerID, roomNumber, days, totalPrice;

    int totalBookings = 0;
    int singleRoom = 0;
    int doubleRoom = 0;
    int suiteRoom = 0;

    double totalRevenue = 0;

    while(getline(file, bookingID, '|'))
    {
        getline(file, customerID, '|');
        getline(file, roomNumber, '|');
        getline(file, days, '|');
        getline(file, totalPrice);

        totalBookings++;
        totalRevenue += stod(totalPrice);

        int room = stoi(roomNumber);

        if(room == 101 || room == 102)
            singleRoom++;
        else if(room == 201 || room == 202)
            doubleRoom++;
        else if(room == 301)
            suiteRoom++;
    }

    file.close();

    double averageRevenue = 0;

    if(totalBookings > 0)
    {
        averageRevenue = totalRevenue / totalBookings;
    }

cout << "\n\n\t\t\t\t========================================";
cout << "\n\t\t\t\t            MONTHLY REPORT";
cout << "\n\t\t\t\t========================================";

cout << "\n\n\t\t\t\tTotal Bookings      : "
     << totalBookings;

cout << "\n\t\t\t\tTotal Revenue       : RM"
     << totalRevenue;

cout << "\n\t\t\t\tAverage Revenue     : RM"
     << averageRevenue;

cout << "\n\n\t\t\t\tROOM DISTRIBUTION";
cout << "\n\t\t\t\t----------------------------------------";

cout << "\n\t\t\t\tSingle Room Booking : "
     << singleRoom;

cout << "\n\t\t\t\tDouble Room Booking : "
     << doubleRoom;

cout << "\n\t\t\t\tSuite Room Booking  : "
     << suiteRoom;

cout << "\n\n\t\t\t\t========================================";

    system("pause");
}

void roomStatistic()
{
    system("cls");

cout << "\n\n\t\t\t\t================================";
cout << "\n\t\t\t\t      ROOM STATISTICS";
cout << "\n\t\t\t\t================================";

cout << "\n\n\t\t\t\tSingle Rooms : 2";
cout << "\n\t\t\t\tDouble Rooms : 2";
cout << "\n\t\t\t\tSuite Rooms  : 1";

cout << "\n\n\t\t\t\tTotal Rooms  : 5";

cout << "\n\t\t\t\t================================";

    system("pause");
}

void revenueStatistic()
{
    system("cls");

    ifstream file("reservation.txt");

    string bookingID;
    string customerID;
    string roomNumber;
    string days;
    string totalPrice;

    double revenue = 0;

    while(getline(file, bookingID, '|'))
    {
        getline(file, customerID, '|');
        getline(file, roomNumber, '|');
        getline(file, days, '|');
        getline(file, totalPrice);

        revenue += stod(totalPrice);
    }

    file.close();
        cout << "\n\n\t\t\t\t================================";
        cout << "\n\t\t\t\t Revenue Statistic";
        cout << "\n\t\t\t\t================================";
    cout << "\n\n\t\t\t\tTOTAL REVENUE : RM"
         << revenue;

    system("pause");
}




void viewPaymentHistory()
{
    system("cls");

    ifstream file("payment.txt");

    string paymentID;
    string bookingID;
    string amount;
    string method;

    cout << "\n\n\t\t\t\t===== PAYMENT HISTORY =====";

    while(getline(file, paymentID, '|'))
    {
        getline(file, bookingID, '|');
        getline(file, amount, '|');
        getline(file, method);

        cout << "\n\n\t\t\t\tPayment ID : "
             << paymentID;

        cout << "\n\t\t\t\tBooking ID : "
             << bookingID;

        cout << "\n\t\t\t\tAmount : RM"
             << amount;

        cout << "\n\t\t\t\tMethod : "
             << method;

        cout << "\n\t\t\t\t------------------------";
    }

    file.close();

    system("pause");
}


void searchPaymentRecord()
{
    system("cls");

    string id;

    cout << "\n\n\t\t\t\t===== SEARCH PAYMENT =====";

    cout << "\n\n\t\t\t\tEnter Payment ID : ";
    cin >> id;

    ifstream file("payment.txt");

    string paymentID;
    string bookingID;
    string amount;
    string method;

    bool found = false;

    while(getline(file, paymentID, '|'))
    {
        getline(file, bookingID, '|');
        getline(file, amount, '|');
        getline(file, method);

        if(paymentID == id)
        {
            found = true;

            cout << "\n\n\t\t\t\tPayment Found!";

            cout << "\n\t\t\t\tPayment ID : "
                 << paymentID;

            cout << "\n\t\t\t\tBooking ID : "
                 << bookingID;

            cout << "\n\t\t\t\tAmount : RM"
                 << amount;

            cout << "\n\t\t\t\tMethod : "
                 << method;

            break;
        }
    }

    file.close();

    if(!found)
    {
        cout << "\n\n\t\t\t\tPayment Not Found!";
    }

    system("pause");
}



//LOUIS


//LOUIS

void adminMenu()
{
    int choice;

    do
    {
system("cls");

cout << "\n";
cout << "\t\t=====================================================\n";
cout << "\t\t          HOTEL RESERVATION SYSTEM\n";
cout << "\t\t                 ADMIN PANEL\n";
cout << "\t\t=====================================================\n";

cout << "\n\t\t [1]  View Reservations";
cout << "\n\t\t [2]  Search Booking ID";
cout << "\n\t\t [3]  Search Room Number";
cout << "\n\t\t [4]  Search Room Type";
cout << "\n\t\t [5]  Search Room Price";
cout << "\n\t\t [6]  Search Total Payment";

cout << "\n\n\t\t ---------------- REPORTS ----------------";

cout << "\n\t\t [7]  Summary Report";
cout << "\n\t\t [8]  Monthly Report";
cout << "\n\t\t [9]  Booking Statistics";
cout << "\n\t\t [10] Room Statistics";
cout << "\n\t\t [11] Revenue Statistics";

cout << "\n\n\t\t -----------------------------------------";

cout << "\n\t\t [12] Logout";
cout << "\n\t\t [13] Add Room";
cout << "\n\t\t [14] Display Room Records";
cout << "\n\t\t [15] Update Room";
cout << "\n\t\t [16] Delete Room";
cout << "\n\t\t [17] Search Room";
cout << "\n\t\t [18] Sort Room Records";
cout << "\n\t\t [19] View Payment History";
cout << "\n\t\t [20] Search Payment";
cout << "\n\t\t [21] Search Customer";


cout << "\n\n\t\t=====================================================";
cout << "\n\t\t Enter Choice : ";
        cin >> choice;

        if(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "\nInvalid Input!";
            system("pause");
            continue;
        }

        switch(choice)
        {
            case 1:
                viewAllReservations();
                break;

            case 2:
                searchBookingID();
                break;

            case 3:
                jumpSearchRoom();
                break;

            case 4:
                jumpSearchRoomType();
                break;

            case 5:
                interpolationSearchPrice();
                break;

            case 6:
                interpolationSearchPayment();
                break;

            case 7:
                summaryReport();
                break;

            case 8:
                monthlyReport();
                break;

            case 9:
                bookingStatistic();
                break;

            case 10:
                roomStatistic();
                break;

            case 11:
                revenueStatistic();
                break;

            case 12:
                break;
            case 13:
    			addRoomRecord();
    			break;

			case 14:
    			displayRoomRecords();
    			break;

			case 15:
			    updateRoomRecord();
			    break;
			
			case 16:
			    deleteRoomRecord();
			    break;
			
			case 17:
			    searchRoomRecord();
			    break;
			case 18:
			    sortRoomRecords();
			    break;
			
			case 19:
			    viewPaymentHistory();
			    break;
			
			case 20:
			    searchPaymentRecord();
			    break;
			    
			case 21:
                searchCustomer();
                break;

			    
                cout << "\nInvalid Choice!";
                system("pause");
                
                default:
            cout << "\n\n\t\t\t\tInvalid Choice!";
            system("pause");
        
        }
        
    } while(choice != 12);
}

//LOUIS 

//ZIYI
int main()
{
    int choice;

    do
    {
      system("cls");

       cout << "\n\n";
cout << "\t\t==================================================\n";
cout << "\t\t          HOTEL RESERVATION SYSTEM\n";
cout << "\t\t==================================================\n";

cout << "\n\t\tWelcome To Hotel Reservation System";
cout << "\n\t\tManage Reservations Efficiently";

       cout << "\n\t\t1. Customer Register";
       cout << "\n\t\t2. Customer Login";
       cout << "\n\t\t3. Admin Login";
       cout << "\n\t\t4. Exit";

       cout << "\n\n\t\t-----------------------------------------";
       cout << "\n\t\tEnter Choice : ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                registerUser();
                break;

            case 2:
                if(loginUser())
                {
                    customerMenu();
                }
                break;

            case 3:
                if(adminLogin())
                {
                    adminMenu();
                }
                break;

            case 4:
                cout << "\n\n\t\t\t\tThank You!";
                break;

            default:
                cout << "\n\n\t\t\t\tInvalid Choice!";
                system("pause");
        }

    } while(choice != 4);

    return 0;
}
