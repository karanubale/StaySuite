#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

void intro()
{
    cout << "\n\n\t            ";
    cout << "     C++ Project On StaySuit(Hotel Operations System)";
}

void head()
{
    cout << "\n\t\t\t\t   xyz Hotels and Group \t\t\t       ";
}

void time()
{
    int i = 0;
    long long j;
    cout << "	\n\n\n	Connecting to Server\n 	Syncing Data";
    while (i < 10)
    {
        for (j = 0; j < 100000000; j++)
        {
        }
        cout << ".";
        ++i;
    }
}

class hotel
{
private:
    int room_no;
    char name[40];
    char address[60];
    char phone[15];
    int days;
    float Amount;

public:
    void main_menu();
    void add();
    void display();
    void rooms();
    void edit();
    int check(int);
    void modify(int);
    void delete_rec(int);

    bool isValidPhoneNumber(const char *phone);
    bool isValidDays(int days);
};

void hotel::main_menu()
{
    int choice = 0;
    while (choice != 5)
    {
        system("cls");
        head();
        cout << "\n\n\n\t\t\t\t";
        cout << "\n\t\t\t\t* MAIN MENU *";
        cout << "\n\n\t\t\t1. Book A Room";
        cout << "\n\t\t\t2. Customer Record";
        cout << "\n\t\t\t3. Rooms Allotted";
        cout << "\n\t\t\t4. Edit Record";
        cout << "\n\t\t\t5. Exit";
        cout << "\n\n\t\t\tEnter Your Choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            add();
            break;
        case 2:
            display();
            break;
        case 3:
            rooms();
            break;
        case 4:
            edit();
            break;
        case 5:
            break;
        default:
        {
            cout << "\n\n\t\t\tWrong choice.....!!!";
            cout << "\n\t\t\tPress a key to continue....!!";
            cin.ignore().get();
        }
        }
    }
}
bool hotel::isValidPhoneNumber(const char *phone)
{
    int length = strlen(phone);
    if (length < 9)
    {
        return false;
    }
    for (int i = 0; i < length; ++i)
    {
        if (!isdigit(phone[i]))
        {
            return false;
        }
    }
    return true;
}

bool hotel::isValidDays(int days)
{
    return days > 0;
}

void hotel::add()
{
    system("cls");
    head();
    int r, flag;
    ofstream fout("Record.txt", ios::app | ios::binary);
    cout << "\n Enter Customer Details";
    cout << "\n ----------------------";
    cout << "\n\n Room no: ";
    cin >> r;
    flag = check(r);
    if (flag)
    {
        cout << "\n Sorry Sir..!!! Room is already booked";
    }
    else
    {
        room_no = r;
        cout << " Name: ";
        cin.ignore();
        cin.getline(name, 40);
        cout << " Address: ";
        cin.getline(address, 60);

        try
        {
            cout << " Phone No: ";
            cin.getline(phone, 15);
            if (!isValidPhoneNumber(phone))
            {
                throw runtime_error("Invalid phone number. Must be at least 9 digits and contain only numbers.");
            }

            cout << " No of Days to Checkout: ";
            cin >> days;
            if (!isValidDays(days))
            {
                throw runtime_error("Invalid number of days. Must be a positive integer.");
            }

            Amount = days * 800;
            fout.write(reinterpret_cast<char *>(this), sizeof(hotel));
            cout << "\n Room is booked...!!!";
        }
        catch (const runtime_error &e)
        {
            cout << "\n Error: " << e.what();
        }
    }

    cout << "\n Press a key to continue.....!!";
    cin.ignore().get();
    fout.close();
}

void hotel::display()
{
    system("cls");
    head();
    ifstream fin("Record.txt", ios::in | ios::binary);
    int r, flag = 0;
    cout << "\n Enter room no: ";
    cin >> r;
    while (fin.read(reinterpret_cast<char *>(this), sizeof(hotel)))
    {
        if (room_no == r)
        {
            system("cls");
            head();
            cout << "\n Customer Details";
            cout << "\n ----------------";
            cout << "\n\n Room no: " << room_no;
            cout << "\n Name: " << name;
            cout << "\n Address: " << address;
            cout << "\n Phone no: " << phone;
            cout << "\n Days: " << days;
            cout << "\n Total Amount: " << Amount;
            flag = 1;
            break;
        }
    }
    if (flag == 0)
        cout << "\n Sorry Sir, Room number not found or vacant....!!";
    cout << "\n\n Press a key to continue....!!";
    cin.ignore().get();
    fin.close();
}

void hotel::rooms()
{
    system("cls");
    head();
    ifstream fin("Record.txt", ios::in | ios::binary);
    cout << "\n\t\t\t    List Of Rooms Allotted";
    cout << "\n\t\t\t    ----------------------";
    while (fin.read(reinterpret_cast<char *>(this), sizeof(hotel)))
    {
        cout << "\n Room no: " << room_no << "\n Name: " << name;
        cout << "\n Address: " << address << "\n Phone: " << phone;
        cout << "\n Days: " << days << "\n Total: " << Amount;
        cout << "\n**";
    }
    cout << "\n\n\n\t\t\tPress a key to continue.....!!";
    cin.ignore().get();
    fin.close();
}

void hotel::edit()
{
    system("cls");
    head();
    int choice, r;
    cout << "\n EDIT MENU";
    cout << "\n ---------";
    cout << "\n\n 1. Modify Customer Record";
    cout << "\n 2. Delete Customer Record";
    cout << "\n Enter your choice: ";
    cin >> choice;

    if (choice <= 0 || choice > 2)
    {
        cout << "\n Invalid choice. Please select option 1 or 2.";
        cout << "\n Press a key to return to the main menu.";
        cin.ignore().get();
        return;
    }

    system("cls");
    head();
    cout << "\n Enter room no: ";
    cin >> r;

    switch (choice)
    {
    case 1:
        modify(r);
        break;
    case 2:
        delete_rec(r);
        break;
    }

    cout << "\n Press a key to continue....!!!";
    cin.ignore().get();
}

int hotel::check(int r)
{
    int flag = 0;
    ifstream fin("Record.txt", ios::in | ios::binary);
    while (fin.read(reinterpret_cast<char *>(this), sizeof(hotel)))
    {
        if (room_no == r)
        {
            flag = 1;
            break;
        }
    }
    fin.close();
    return flag;
}

void hotel::modify(int r)
{
    system("cls");
    head();
    long pos;
    int flag = 0;
    fstream file("Record.txt", ios::in | ios::out | ios::binary);
    while (!file.eof())
    {
        pos = file.tellg();
        file.read(reinterpret_cast<char *>(this), sizeof(hotel));
        if (room_no == r)
        {
            try
            {
                cout << "\n Enter New Details";
                cout << "\n -----------------";
                cout << "\n Name: ";
                cin.ignore();
                cin.getline(name, 40);
                cout << " Address: ";
                cin.getline(address, 60);

                cout << " Phone no: ";
                cin.getline(phone, 15);
                if (!isValidPhoneNumber(phone))
                {
                    throw runtime_error("Invalid phone number. Must be at least 9 digits and contain only numbers.");
                }

                cout << " Days: ";
                cin >> days;
                if (!isValidDays(days))
                {
                    throw runtime_error("Invalid number of days. Must be a positive integer.");
                }

                Amount = days * 800;
                file.seekg(pos);
                file.write(reinterpret_cast<char *>(this), sizeof(hotel));
                cout << "\n Record is modified....!!";
                flag = 1;
                break;
            }
            catch (const runtime_error &e)
            {
                cout << "\n Error: " << e.what();
            }
        }
    }

    if (flag == 0)
        cout << "\n Sorry Sir, Room number not found or vacant...!!";
    file.close();
}

void hotel::delete_rec(int r)
{
    system("cls");
    head();
    int flag = 0;
    char ch;
    ifstream fin("Record.txt", ios::in | ios::binary);
    ofstream fout("temp.dat", ios::out | ios::binary);
    while (fin.read(reinterpret_cast<char *>(this), sizeof(hotel)))
    {
        if (room_no == r)
        {
            cout << "\n Name: " << name;
            cout << "\n Address: " << address;
            cout << "\n Phone No: " << phone;
            cout << "\n Days: " << days;
            cout << "\n Total Amount: " << Amount;
            cout << "\n\n Do you want to delete this record (y/n): ";
            cin >> ch;
            if (ch == 'n')
                fout.write(reinterpret_cast<char *>(this), sizeof(hotel));
            flag = 1;
        }
        else
        {
            fout.write(reinterpret_cast<char *>(this), sizeof(hotel));
        }
    }

    fin.close();
    fout.close();
    if (flag == 0)
        cout << "\n Sorry, room no. not found or vacant...!!";
    else
    {
        remove("Record.txt");
        rename("temp.dat", "Record.txt");
    }
}

int main()
{
    hotel h;
    system("cls");
    cout << "\n\n\n";
    intro();
    time();
    cout << "\n\n\n\t\t\tPress a key to continue..!!";

    cin.ignore().get();
    system("cls");
    head();
    char id[5], pass[7];
    cout << "\n\n\t\t\t\tusername => ";
    cin >> id;
    cout << "\n\t\t\t\tpassword => ";
    cin >> pass;
    cout << "\n\n\t";
    time();
    cout << "\t";
    if (strcmp(id, "user") == 0 && strcmp(pass, "user") == 0)
        cout << "\n\n\t\t\t  !!!Login Successful!!!";
    else
    {
        cout << "\n\n\t\t\t!!!Invalid Credentials!!!";
        cin.ignore().get();
        exit(-1);
    }
    system("cls");
    h.main_menu();
    cin.ignore().get();

    return 0;
}