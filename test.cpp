#include <iostream>
#include <conio.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <string>

using namespace std;

// START OF CLASS

class hotel
{

    int room_no;
    char name[30];
    char address[50];
    char phone[10];
    char food[20];
    char drink[20];
    char transportation[10];
    char destination[50];

public:
    void main_menu();     // to dispay the main menu
    void add();           // to book a room
    void display();       // to display the customer Booking
    void rooms();         // to display alloted rooms
    void edit();          // to edit the customer Booking
    int check(int);       // to check room status
    void modify(int);     // to modify the Booking
    void delete_rec(int); // to delete the Booking
    void bill(int);       // for the bill of a Booking
    void service();
};
// END OF CLASS

// FOR DISPLAYING MAIN MENU

void hotel::main_menu()
{

    int choice;
    while (choice != 6)
    {

        system("cls");
        cout << "\n\t\t\t\t***************************";
        cout << "\n\t\t\t\t* SIMPLE HOTEL MANAGEMENT *";
        cout << "\n\t\t\t\t***************************";
        cout << "\n\n\n\t\t\tMAIN MENU";
        cout << "\n\t\t\t1.Book A Room";
        cout << "\n\t\t\t2.Customer Bookings";
        cout << "\n\t\t\t3.Rooms Allotted";
        cout << "\n\t\t\t4.Edit Booking";
        cout << "\n\t\t\t5.Customer service";
        cout << "\n\t\t\t6.Exit";
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
            service();
            break;

        case 6:
            break;
        default:
        {

            cout << "\n\n\t\t\tWrong choice.....!!!";
            cout << "\n\t\t\tPress any key to continue....!!";
            getch();
        }
        }
    }
}

// END OF MENU FUNCTION

// FUNCTION FOR BOOKING OF ROOM

void hotel::add()
{

    system("cls");
    int r, flag;
    ofstream fout("Booking.dat", ios::app);

    cout << "\n Enter Customer Detalis";
    cout << "\n ----------------------";
    cout << "\n\n Room no: ";
    cout << "\n Total no. of Rooms - 50";
    cout << "\n Ordinary Rooms from 1 - 30";
    cout << "\n Luxuary Rooms from 31 - 45";
    cout << "\n Royal Rooms from 46 - 50";
    cout << "\n Enter The Room no. you want to stay in :- ";
    cin >> r;

    flag = check(r);

    if (flag)
        cout << "\n Sorry..!!!Room is already booked";

    else
    {

        room_no = r;
        cout << " Name: ";
        cin >> name;
        cout << " Address: ";
        cin >> address;
        cout << " Phone No: ";
        cin >> phone;

        fout.write((char *)this, sizeof(hotel));
        cout << "\n Room is booked...!!!";
    }

    cout << "\n Press any key to continue.....!!";

    getch();
    fout.close();
}

// END OF BOOKING FUNCTION

// FUNCTION FOR DISPLAYING A PURTICULAR CUSTOMER`S Booking

void hotel::display()
{

    system("cls");

    ifstream fin("Booking.dat", ios::in);
    int r, flag;

    cout << "\n Enter room no. for a particular customer`s details :- ";
    cin >> r;

    while (!fin.eof())
    {

        fin.read((char *)this, sizeof(hotel));
        if (room_no == r)
        {

            system("cls");
            cout << "\n Cusromer Details";
            cout << "\n ----------------";
            cout << "\n\n Room no: " << room_no;
            cout << "\n Name: " << name;
            cout << "\n Address: " << address;
            cout << "\n Phone no: " << phone;
            flag = 1;
            break;
        }
    }

    if (flag == 0)
        cout << "\n Sorry Room no. not found or vacant....!!";
    cout << "\n\n Press any key to continue....!!";

    getch();
    fin.close();
}

// END OF DISPLAY FUNCTION

// FUNCTION TO DISPLAY ALL ROOMS OCCUPIED

void hotel::rooms()
{

    system("cls");

    ifstream fin("Booking.dat", ios::in);
    cout << "\t\t\t\t\t\t\t\t  List Of Rooms and Service Allotted";
    cout << "\n\t\t\t\t\t\t\t\t\t----------------------";
    cout << "\n\t\t\t\tROOM BOOKING\t\t\t\t\t\t\t\t\tSERVICE BOOKING";
    cout << "\n\n Room No.\tName\t\tAddress\t\t\tPhone No \t\tFood Booking\t\tDrink Booking\t\tTransportation Booking.\n";

    while (!fin.eof())
    {

        fin.read((char *)this, sizeof(hotel));
        cout << "\n\n " << room_no << "\t\t" << name;
        cout << "\t\t" << address << "\t\t\t" << phone; 
        cout << "\t\t\t" << food << "\t\t" << drink << "\t\t\t\t\t" << transportation <<" to "<<destination;
    }

    cout << "\n\n\n\t\t\t\t\t\t\t\tPress any key to continue.....!!";
    getch();
    fin.close();
}

// FUNCTION FOR EDITING BOOKINGS AND FOR BILL

void hotel::edit()
{

    system("cls");

    int choice, r;
    cout << "\n EDIT MENU";
    cout << "\n ---------";
    cout << "\n\n 1.Modify Customer Booking";
    cout << "\n 2.Delete Customer Booking";
    cout << "\n 3. Bill Of Customer";
    cout << "\n Enter your choice: ";

    cin >> choice;
    system("cls");

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

    case 3:
        bill(r);
        break;

    default:
        cout << "\n Wrong Choice.....!!";
    }
    cout << "\n Press any key to continue....!!!";

    getch();
}

int hotel::check(int r)
{

    int flag = 0;

    ifstream fin("Booking.dat", ios::in);

    while (!fin.eof())
    {

        fin.read((char *)this, sizeof(hotel));
        if (room_no == r)
        {

            flag = 1;
            break;
        }
    }

    fin.close();
    return (flag);
}

// FUNCTION TO MODIFY CUSTOMERS Booking

void hotel::modify(int r)
{

    long pos, flag = 0;

    fstream file("Booking.dat", ios::in | ios::out | ios::binary);

    while (!file.eof())
    {

        pos = file.tellg();
        file.read((char *)this, sizeof(hotel));

        if (room_no == r)
        {

            cout << "\n Enter New Details";
            cout << "\n -----------------";
            cout << "\n Name: ";
            cin >> name;
            cout << " Address: ";
            cin >> address;
            cout << " Phone no: ";
            cin >> phone;
            file.seekg(pos);
            file.write((char *)this, sizeof(hotel));
            cout << "\n Booking is modified....!!";
            flag = 1;
            break;
        }
    }

    if (flag == 0)
        cout << "\n Sorry Room no. not found or vacant...!!";
    file.close();
}

// END OF MODIFY FUNCTION

// FUNCTION FOR DELETING Booking

void hotel::delete_rec(int r)
{

    int flag = 0;
    char ch;
    ifstream fin("Booking.dat", ios::in);
    ofstream fout("temp.dat", ios::out);

    while (!fin.eof())
    {

        fin.read((char *)this, sizeof(hotel));
        if (room_no == r)

        {

            cout << "\n Name: " << name;
            cout << "\n Address: " << address;
            cout << "\n Pone No: " << phone;
            cout << "\n\n Do you want to delete this Booking(y/n): ";
            cin >> ch;

            if (ch == 'n')
                fout.write((char *)this, sizeof(hotel));
            flag = 1;
        }

        else
            fout.write((char *)this, sizeof(hotel));
    }

    fin.close();
    fout.close();

    if (flag == 0)
        cout << "\n Sorry room no. not found or vacant...!!";

    else
    {

        remove("Booking.dat");
        rename("temp.dat", "Booking.dat");
    }
}

// END OF DELETE FUNCTION

// FUNCTION FOR CUSTOMER`S BILL

void hotel::bill(int r)
{

    hotel h1;
    ifstream f1;
    f1.open("Booking.dat", ios::in | ios::binary);

    if (!f1)
        cout << "cannot open";

    else
    {

        f1.read((char *)&h1, sizeof(hotel));
        while (f1)

        {

            f1.read((char *)&h1, sizeof(hotel));
        }

        if (h1.room_no == r)
        {

            if (h1.room_no >= 1 && h1.room_no <= 30)
                cout << "Your bill = 2000";

            else if (h1.room_no >= 35 && h1.room_no <= 45)
                cout << "Your bill = 5000";

            else
                cout << "Your bill = 7000";
        }

        else
        {
            cout << "Room no. not found";
        }
    }

    f1.close();
    getch();
}

void hotel::service()
{
    system("cls");
    int r, flag, choice;
    ofstream fout("Booking.dat");
    cout << "Enter your room: ";
    cin >> r;

    flag = check(r);

    if (!flag)
    {
        cout << "Sorry room no. not found or vacant...!!";
    }
    else
    {
        ofstream fout("Customer service booking.dat", ios::app);
        cout << "\n\n\n\t\t\tSERVICE MENU";
        cout << "\n\t\t\t1.Order Food";
        cout << "\n\t\t\t2.Order Drink";
        cout << "\n\t\t\t3.Book a transportation";
        cout << "\n\n\t\t\tEnter Your Choice: ";
        cin >> choice;
        if (choice == 1)
        {
                cout << "What do you want to eat: ";
                cin >> food;
                fout.write((char *)this, sizeof(hotel));
                cout << "Succesfully!!!";
            
            cout << "\nPress any key to continue...";

            getch();
            fout.close();
        }
        if (choice == 2)
        {
            
                cout << "What do you want to drink: ";
                cin >> drink;
                fout.write((char *)this, sizeof(hotel));
                cout << "Succesfully!!!";
            
            cout << "\nPress any key to continue...";
            getch();
            fout.close();
        }
    }
    if (choice == 3)
    {
        
            cout << "What kind of transporation do you want to book (car/bikes): ";
            cin >> transportation;
            cout << "Please enter your destination address: ";
            cin >> destination;
            fout.write((char *)this, sizeof(hotel));
            cout << "\nSuccesfully!!!";
        
        cout << "\nPress any key to continue...";
        getch();
        fout.close();
    }
}
// END OF BILLING FUNCTION

// START OF MAIN PROGARM

int main()
{

    hotel h;

    system("cls");

    cout << "\n\t\t\t\t\t****************************";
    cout << "\n\t\t\t\t\t* HOTEL MANAGEMENT PROJECT *";
    cout << "\n\t\t\t\t\t****************************";
    cout << "\n\n\n\n\n\n\n\t\t\t\t\tPress any key to continue....!!";

    getch();

    h.main_menu();
    return 0;
}
