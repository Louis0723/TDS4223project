//YAP ZI YI

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdio>
#include <limits>
using namespace std;

void jumpSearchRoom();
void interpolationSearchPrice();
void searchBookingID();
void summaryReport();
void bookingStatistic();
void viewProfile();
void updateProfile();
void deleteAccount();

void jumpSearchRoomType();
void jumpSearchAvailableRoom();
void interpolationSearchPayment();
void monthlyReport();
void roomStatistic();
void revenueStatistic();

void adminMenu();
bool adminLogin();
string currentCustomerID = "";

//ZIYI
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
        cout << "Customer object destroyed\n";
    }

    void update(string newName);
    void update(string newName, string newPhone);

    friend void displayCustomer(Customer c);
    friend void updateCustomerRecord(Customer &c);
};

void Customer::update(string newName)
{
    name = newName;
    cout << "\nName updated only!";
}

void Customer::update(string newName, string newPhone)
{
    name = newName;
    phone = newPhone;
    cout << "\nName and Phone updated!";
}

class Admin : public User
{
public:
    string adminName;

    Admin() {}

    Admin(string id, string password, string name)
        : User(id, password)
    {
        adminName = name;
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

struct Reservation
{
    string bookingID;
    string customerID;
    int roomNumber;
    int days;
    double totalPrice;
};

void viewProfile()
{
    system("cls");

    string id;

    cout << "\nEnter Customer ID : ";
    cin >> id;

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

    string id;

    cout << "\nEnter Customer ID : ";
    cin >> id;

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

    string id;

    cout << "\nEnter Customer ID : ";
    cin >> id;

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
	
    Customer *c = new Customer();

    cout << "\n\n\t\t\t\t===== CUSTOMER REGISTRATION =====\n";

    cout << "\n\n\t\t\t\tEnter Customer ID: ";
    cin >> c->customerID;

    if (customerExists(c->customerID))
    {
        cout << "\n\n\t\t\t\tCustomer ID already exists!\n";

        delete c;

        system("pause");
        return;
    }
     cin.ignore();

    cout << "\n\n\t\t\t\tEnter Name: ";
    getline(cin, c->name);

    cout << "\n\n\t\t\t\tEnter Phone Number: ";
    getline(cin, c->phone);

    cout << "\n\n\t\t\t\tEnter Password: ";
    getline(cin, c->password);

    ofstream file("customer.txt", ios::app);

    file << c->customerID << "|"
         << c->name << "|"
         << c->phone << "|"
         << c->password << endl;

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

cout << "\n\t101\tSingle\t\tRM100\t\tAvailable";
cout << "\n\t102\tSingle\t\tRM100\t\tAvailable";
cout << "\n\t201\tDouble\t\tRM180\t\tAvailable";
cout << "\n\t202\tDouble\t\tRM180\t\tAvailable";
cout << "\n\t301\tSuite\t\tRM350\t\tAvailable";

cout << "\n\t========================================================";
cout << "\n\tTotal Rooms Available : 5";
    
    system("pause");
    
}

void bookRoom()
{
    Reservation *r = new Reservation;

    system("cls");

    cout << "\n\n\t\t\t\t===== BOOK ROOM =====\n";

    // Generate Booking ID
    ifstream readFile("reservation.txt");

    string line;
    int count = 0;

    while(getline(readFile, line))
    {
        count++;
    }

    readFile.close();

    count++;

    if(count < 10)
        r->bookingID = "B00" + to_string(count);
    else if(count < 100)
        r->bookingID = "B0" + to_string(count);
    else
        r->bookingID = "B" + to_string(count);

    cout << "\n\n\t\t\t\tGenerated Booking ID : "
         << r->bookingID;

    r->customerID = currentCustomerID;

    cout << "\n\n\t\t\t\tRoom Number: ";
    cin >> r->roomNumber;

    cout << "\n\n\t\t\t\tNumber of Days: ";
    cin >> r->days;

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
        return;
    }

    if(r->days <= 0)
    {
        cout << "\n\n\t\t\t\tInvalid Number of Days!";
        system("pause");
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

    cout << "\n\n\t\t\t\t===== RESERVATION RECORD =====\n";
    int no = 1;
    while (getline(file, bookingID, '|'))
    {
        getline(file, customerID, '|');
        getline(file, roomNumber, '|');
        getline(file, days, '|');
        getline(file, totalPrice);

        cout << "\n\n\t\t\t\t================================";
        cout << "\n\t\t\t\tReservation #" << no++;
        cout << "\n\t\t\t\t================================";

        cout << "\n\t\t\t\tBooking ID   : " << bookingID;
        cout << "\n\t\t\t\tCustomer ID  : " << customerID;
        cout << "\n\t\t\t\tRoom Number  : " << roomNumber;
        cout << "\n\t\t\t\tDays Stayed  : " << days;
        cout << "\n\t\t\t\tTotal Price  : RM" << totalPrice;

        cout << "\n\t\t\t\t================================";
    }

    file.close();
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

cout << "\n\n\t\tCHECK-IN SERVICES";
cout << "\n\t\t-----------------------------------------------------";
cout << "\n\t\t4.  Check In";
cout << "\n\t\t5.  Check Out";

cout << "\n\n\t\tSEARCH SERVICES";
cout << "\n\t\t-----------------------------------------------------";
cout << "\n\t\t6.  Search Room Number";
cout << "\n\t\t7.  Search Room Type";
cout << "\n\t\t8.  Search Available Room";
cout << "\n\t\t9.  Search Room Price";
cout << "\n\t\t10. Search Booking ID";

cout << "\n\n\t\tPROFILE MANAGEMENT";
cout << "\n\t\t-----------------------------------------------------";
cout << "\n\t\t11. Logout";
cout << "\n\t\t12. View Profile";
cout << "\n\t\t13. Update Profile";
cout << "\n\t\t14. Delete Account";

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
                checkIn();
                break;

            case 5:
                checkOut();
                break;

            case 6:
                jumpSearchRoom();
                break;

           case 7:
                jumpSearchRoomType();
                break;

          case 8:
               jumpSearchAvailableRoom();
               break;

         case 9:
               interpolationSearchPrice();
               break;

         case 10:
               searchBookingID();
               break;

        case 11:
               break;

        case 12:
            viewProfile();
            break;

        case 13:
            updateProfile();
            break;

        case 14:
            deleteAccount();
            break;

            default:
                cout << "\n\n\t\t\t\tInvalid Choice!";
                system("pause");
        }

    } while(choice != 11);
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
        cout << "\n\t\t\t\tPlease check the Booking ID and try again.";
        cout << "\n\t\t\t\tExample: B001, B002, B003";
    }

    cout << "\n\n\t\t\t\t";
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

    cout << "\n\n\t\t\t\tAVAILABLE ROOMS\n";

    for(int i=0;i<5;i++)
    {
        cout << "\n\t\t\t\tRoom Number : "
             << roomList[i].roomNumber;

        cout << "\n\t\t\t\tRoom Type : "
             << roomList[i].roomType;

        cout << "\n\t\t\t\tPrice : RM"
             << roomList[i].price << endl;
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
                viewReservation();
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

            default:
                cout << "\nInvalid Choice!";
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

//ZIYI



//YAP ZI YI

//ONG ZHENG HAO

//ONG ZHENG HAO




//CHIA SHI LOUIS
