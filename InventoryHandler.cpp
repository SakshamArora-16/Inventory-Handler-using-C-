//---OFFICE MANAGEMENT---//

#include <fstream.h>
#include <iostream.h>
#include <conio.h>
#include <ctype.h>
#include <process.h>
#include <iomanip.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*FUNCTION TO FLASH THE INTRODUCTORY SCREEN.*/

void welcome_screen()
{
    clrscr();
    gotoxy(15, 10);
    cputs("********************* WELCOME  *********************** ");
    gotoxy(20, 14);
    cputs("      OFFICE MANAGEMENT SOFTWARE   ");
    gotoxy(22, 18);
    cputs("     PRESS ANY KEY TO CONTINUE    ");
    getch();
    return;
}
// DECLARATION OF CLASS OFFICE.//

class office
{
    int record;
    long pn1;
    long pn2;
    int age;
    char address1[50];
    char address2[50];
    char occupation[20];
    char name[20];
    char emailadd[25];

public:
    void modification();
    void addition();
    void deletion();
    void menu();
    void search();
    void view1();
    void addin();
    void display();
    void view();
    char check(char *);
    int test();
} obj;

// FUNCTION TO ADD NEW RECORDS.//

void office::addition()
{
    ofstream fout;
    fout.open("cust.dat", ios::out | ios::app);
    addin();
    fout.write((char *)&obj, sizeof(obj));
    fout.close();
}

/*FUNCTION TO FIND THE NUMBER OF RECORDS IN THE FILE.*/

int office::test()
{
    ifstream fin;
    fin.open("cust.dat");
    fin.seekg(0, ios::end);
    int n;
    n = fin.tellg() / sizeof(obj);
    cout << " \n NUMBER OF RECORDS = " << n;
    return n;
}

// FUNCTION TO SEARCH A RECORD.//

void office::search()
{
    ifstream fin;
    fin.open("cust.dat");
    if (fin.fail())
    {
        cout << " \n FILE NOT FOUND ";
        getch();
        return;
    }
    clrscr();

    gotoxy(30, 1);
    cout << " SEARCHING ";
    cout << " \n ENTER PHONE NUMBER TO BE SEARCHED : ";
    long pn;
    cin >> pn;
    int n;
    n = test();

    for (int i = 0; i < n; i++)
    {
        fin.read((char *)&obj, sizeof(obj));
        if ((pn == pn1) || (pn == pn2))
        {
            view1();
            return;
        }
    }

    cout << endl
         << endl
         << "\tFile not found.";
    getch();
}

// FUNCTION TO ENTER DETAILS.//

void office::addin()
{
    clrscr();
    char ch;
    gotoxy(30, 1);
    cout << " ADD NEW RECORD. ";
    gotoxy(30, 2);
    cout << "-----------------";
    gotoxy(1, 4);
    cout << " \n ENTER HOUSE PHONE NUMBER : ";
    cin >> pn1;
    cout << " \n ENTER OFFICE PHONE NUMBER : ";
    cin >> pn2;
    cin.get(ch);
    cout << " \n ENTER NAME : ";
    cin.getline(name, 20, '\n');
    cout << " \n ENTER THE OCCUPATION : ";
    cin.getline(occupation, 20, '\n');
    cout << " \n ENTER HOUSE ADDRESS : ";
    cin.getline(address1, 50, '\n');
    cout << " \n ENTER OFFICE ADDRESS : ";
    cin.getline(address2, 50, '\n');
    cout << " \n ENTER EMAIL ADDRESS : ";
    cin.getline(emailadd, 25, '\n');
}

// FUNCTION TO DISPLAY ALL THE RECORDS.//

void office::view1()
{
    cout << "\n";
    cout << "HOUSE PHONE NUMBER : " << obj.pn1 << "\n";
    cout << "OFFICE PHONE NUMBER : " << obj.pn2 << "\n";
    cout << " NAME : " << obj.name << "\n";
    cout << " HOUSE ADDRESS : " << obj.address1 << "\n";
    cout << " OCCUPATION : " << obj.occupation << "\n";
    cout << " OFFICE ADDRESS : " << obj.address2 << "\n";
    cout << " EMAIL ADDRESS : " << obj.emailadd << "\n";
    getch();
}

/*FUNCTION TO MODIFY ANY DATA IN THE RECORD IF NECESSARY.*/

void office::modification()
{
    clrscr();
    gotoxy(30, 1);
    cout << "  MODIFICATION  ";
    long pn;
    int n, i;
    ifstream fin;
    ofstream fout;
    fin.open("cust.dat");
    if (fin.fail())
    {
        cout << "\n FILE NOT FOUND !";
        fout.close();
        exit(0);
    }
    fout.open("new");
    n = test();
    if (n == 0)
    {
        cout << "\n FILE IS EMPTY ! ";
        getch();
        return;
    }

    while (!fin.eof())
    {
        fin.read((char *)&obj, sizeof(obj));
        fout.write((char *)&obj, sizeof(obj));
    }

    fin.close();
    fout.close();
    fout.open("tele.dat", ios::trunc);
    fin.open("new");
    if (fin.fail())
    {
        cout << "\n FILE NOT FOUND !";
        exit(0);
    }
    char ch;
    cout << "\n ENTER PHONE NUMBER :";
    cin >> pn;
    ch = cin.get();
    for (i = 0; i < n; i++)
    {
        fin.read((char *)&obj, sizeof(obj));
        char d;
        if (pn == pn1)
        {
            view1();
            d = check("HOUSE PHONE NUMBER ");
            if ((d == 'y') || (d == 'Y'))
            {
                cout << "\n ENTER NEW PHONE NUMBER :";
                cin >> pn1;
                ch = cin.get();
            }
            if (check("OFFICE PHONE NUMBER ") == 'Y')
            {
                cout << "\n ENTER NEW PHONE NUMBER :";
                cin >> pn2;
                ch = cin.get();
            }
            if (check("NAME") == 'y')
            {
                cout << "\n ENTER NEW NAME : ";
                cin.getline(name, 20, '\n');
            }
            if (check("HOME ADDRESS") == 'y')
            {
                cout << "\n ENTER NEW ADDRESS :";
                cin.getline(address1, 50, '\n');
            }
            if (check("OFFICE ADDRESS") == 'y')
            {
                cout << "\n ENTER NEW ADDRESS :";
                cin.getline(address2, 50, '\n');
            }
            if (check("EMAIL ADDRESS:") == 'y')
            {
                cout << "\n ENTER NEW MAIL ADDRESS :";
                cin.getline(emailadd, 25, '\n');
            }
        }
        fout.write((char *)&obj, sizeof(obj));
    }
    fout.close();
    fin.close();
}

/*FUNCTION TO ASK IF THE CONCERNED DATA NEED TO BE MODIFIED AND RETURN THE CHOICE TO FUNCTION FOR MODIFICATION OF DATA*/

char office::check(char *s)
{
    cout << "\n MODIFY \t " << s << "\t"
         << "Y/N";
    char ch;
    ch = getch();

    if ((ch == 'y') || (ch == 'Y'))
        return 'y';
    else
        return 'n';
}

// FUNCTION TO DELETE DATA.//

void office::deletion()
{
    clrscr();
    gotoxy(30, 1);
    cout << "[DELETION]";
    long pn;
    int n, i;
    ifstream fin;
    ofstream fout;
    fin.open("cust.dat");
    if (fin.fail())
    {
        cout << "\n FILE NOT FOUND ! ";
        getch();
        return;
    }
    fout.open("new");
    n = test();
    if (n == 0)
    {
        cout << "\n FILE IS EMPTY ! ";
        getch();
        return;
    }
    for (i = 0; i < n; i++)
    {
        fin.read((char *)&obj, sizeof(obj));
        fout.write((char *)&obj, sizeof(obj));
    }
    fin.close();
    fout.close();
    fout.open("cust.dat", ios::trunc);
    fin.open("new");
    if (fin.fail())
    {
        cout << "\n FILE NOT FOUND ! ";
        getch();
        return;
    }
    cout << "\n ENTER PHONE NUMBER :";
    cin >> pn;
    for (i = 0; i < n; i++)
    {
        fin.read((char *)&obj, sizeof(obj));
        if (pn != pn1)
            fout.write((char *)&obj, sizeof(obj));
    }
    fout.close();
    fin.close();
}

// FUNCTION TO DISPLAY DATA.//

void office::view()
{
    ifstream fin;
    int n, j;
    fin.open("cust.dat");
    if (fin.fail())
    {
        cout << "\n FILE NOT FOUND ! ";
        getch();
        return;
    }
    clrscr();
    int i = 0;
    n = test();
    for (j = 0; j < n; j++)
    {
        cout << "\n RECORD " << i + 1 << "\n";
        fin.read((char *)&obj, sizeof(obj));
        cout << "\n PHONE NUMBER :" << obj.pn1 << "\n";
        cout << "\n PHONE NUMBER2 :" << obj.pn2 << "\n";
        cout << "\n NAME :" << obj.name << "\n";
        cout << "\n HOUSE ADDRESS :" << obj.address1 << "\n";
        cout << "\n OCCUPATION :" << obj.occupation << "\n";
        cout << "\n OFFICE ADDRESS :" << obj.address2 << "\n";
        cout << "\n EMAIL ADDRESS : " << obj.emailadd << "\n";
        i++;
    }
    fin.close();
    getch();
}

// FUNCTION TO FLASH MAIN MENU.//

void office::menu()
{
    char ch;
    clrscr();
    gotoxy(27, 6);
    cout << "YOU ARE AT MAIN MENU.";
    gotoxy(27, 7);
    cout << "---------------------";
    gotoxy(30, 8);
    cout << " A:ADDITION ";
    gotoxy(30, 9);
    cout << " D:DELETION \n  \r ";
    gotoxy(30, 10);
    cout << " M:MODIFICATION \n \r ";
    gotoxy(30, 11);
    cout << " V:VIEW \n \r ";
    gotoxy(30, 12);
    cout << " S:SEARCH \n \r ";
    gotoxy(30, 13);
    cout << " E:EXIT \n \r ";
    ch = getch();

    switch (ch)
    {
    case 'a':
    case 'A':
        addition();
        break;
    case 'd':
    case 'D':
        deletion();
        break;
    case 'm':
    case 'M':
        modification();
        break;
    case 'v':
    case 'V':
        view();
        break;
    case 's':
    case 'S':
        search();
        break;
    case 'e':
    case 'E':
        exit(0);
        break;
    }
    return;
}

// MAIN FUNCTION.//

int main()
{
    welcome_screen();
    while (1)
    {
        obj.menu();
    }
    getch();
    return 0;
}
