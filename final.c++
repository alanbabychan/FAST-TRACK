#include <iostream>
#include <cstring>
#include<fstream>

using namespace std;

enum state
{
    main_menu,
    login_system
};

//Defining a structure
struct Node
{
    char name[20];
    char gen[6];
    int age;
    Node *link;
};
Node *start = nullptr;

//Some Global Variable used in the program
int dis;
char where[100], to[100], type[100], time[100], date[100];
static int p = 0;
enum state currentwindow = main_menu;
char current_client[100];

//Defining Structure for new users
struct userprofile
{
    char user_fname[100];
    char user_password[100];
    char user_email[100];
    userprofile *next;
};

//predefine function
userprofile *Adding_new_client(userprofile *);
void login_client(userprofile *);
void heading();
void WriteToFile(userprofile *);
userprofile *InitializeListing(userprofile *);
void logout_client();


//User Management
//Function for read from file
userprofile *InitializeListing(userprofile *hello)
{
    userprofile *text = nullptr, *petrol, temporary;
    ifstream fileopen("users.txt");

    if (!fileopen)
        return nullptr;

    if (fileopen.peek() == EOF)
        return nullptr;

    fileopen.clear();  // Clear the end-of-file flag
    fileopen.seekg(0, ios::beg);  // Move file pointer to the beginning

    while (fileopen >> temporary.user_fname >> temporary.user_password)
    {
        petrol = new userprofile;
        strcpy(petrol->user_fname, temporary.user_fname);
        strcpy(petrol->user_password, temporary.user_password);
        petrol->next = nullptr;

        if (hello == nullptr)
            hello = text = petrol;
        else
        {
            hello->next = petrol;
            hello = petrol;
        }
    }

    fileopen.close();
    return text;
}

//function to add new user in linked list
userprofile *Adding_new_client(userprofile *hello)
{
    userprofile *trans;
    trans = hello;
    userprofile *newwonderers = new userprofile;
    fflush(stdin);
    cout << "Enter Username \n";
    cin >> newwonderers->user_fname;

    while (hello != nullptr)
    {
        if (!strcmp(hello->user_fname, newwonderers->user_fname))
        {
            cout << "That username already exists\n";
            return trans;
        }
        hello = hello->next;
    }

    cout << "Enter the Email ID\n";
    cin >> newwonderers->user_email;

    while (hello != nullptr)
    {
        if (!strcmp(hello->user_email, newwonderers->user_email))
        {
            cout << "That username already exists\n";
            return trans;
        }
        hello = hello->next;
    }

    hello = trans;
    fflush(stdin);
    cout << "Enter password\n";
    cin.ignore();
    cin>>newwonderers->user_password;
    newwonderers->next = nullptr;

    if (hello == nullptr)
    {
        hello = trans = newwonderers;
    }
    else
    {
        while (hello->next != nullptr)
        {
            hello = hello->next;
        }
        hello->next = newwonderers;
    }

    WriteToFile(trans);
    cout << "User added successfully....\n";
    return trans;
}

// Function to login client
void login_client(userprofile *hello)
{
    char client_username[100];
    char client_password[100];
    fflush(stdin);
    cout << "\n\n";
    cout << "\t\tEnter Username:\n\t\t";
    cin >> client_username;
    fflush(stdin);
    cout << "\n\t\tEnter Password:\n\t\t";
    cin.ignore();
    cin>>client_password;

    while (hello != nullptr)
    {
        if ((!strcmp(hello->user_fname, client_username)) && (!strcmp(hello->user_password, client_password)))
        {
            currentwindow = login_system;
            strcpy(current_client, client_username);

            cout << "\n\t\tLogin successful!\n";
            system("PAUSE");
            return;
        }
        else if ((!strcmp(hello->user_fname, client_username)) && (strcmp(hello->user_password, client_password)))
        {
            cout << "Password mismatch\n";
            return;
        }
        hello = hello->next;
    }

    cout << "Sorry, no such user record was found\n";
}

//function to write the user details in the file
void WriteToFile(userprofile *hello)
{
    ofstream fileopen("users.txt");

    while (hello != nullptr)
    {
        fileopen << hello->user_fname << " " << hello->user_password << endl;
        hello = hello->next;
    }

    fileopen.close();
}

//function for heading 
void heading()
{
    cout << "\t\t\t\t***Tourism Package ""Management System***\n";
    cout << "\t\t\t    ***ID PROOF""Is Necessary For Travel Purpose***\n\n";
}

//function for log out client
void logout_client()
{
    if (currentwindow == main_menu || strcmp(current_client, "\0") == 0)
    {
        cout << "You must be logged in to logout\n";
        return;
    }

    strcpy(current_client, "\0");
    currentwindow = main_menu;
    cout << "You have been successfully logged out\n";
}

//Booking System
//class for train
class Train
{
  //declaration of variable used in train class
  char trainNo[5], driver[10], arrival[5], depart[5], from[10], to[10], seat[8][4][10];

public:
  //declaration of function used in train class
  void install();
  void allotment();
  void empty();
  void show();
  void avail();
  void position(int i);
  void saveToFile();
  void loadFromFile();
};

Train train[10];

//function to print the lines
void vline(char ch)
{
  for (int i = 80; i > 0; i--)
    cout << ch;
}

//function used to install a new train in the system
void Train::install()
{
  char newTrainNo[5];
  cout << "Enter train no: ";
  cin >> newTrainNo;

  // Check if the train number already exists
  for (int i = 0; i < p; i++)
  {
    if (strcmp(train[i].trainNo, newTrainNo) == 0)
    {
      cout << "Train with the same number already exists. Please enter a different train number.\n";
      return; // Exit the function if the train number already exists
    }
  }

  // If the train number is unique, proceed with installation
  strcpy(train[p].trainNo, newTrainNo);

  cout << "\nEnter Driver's name: ";
  cin >> train[p].driver;

  cout << "\nArrival time: ";
  cin >> train[p].arrival;

  cout << "\nDeparture: ";
  cin >> train[p].depart;

  cout << "\nFrom: \t\t\t";
  cin >> train[p].from;

  cout << "\nTo: \t\t\t";
  cin >> train[p].to;

  train[p].empty();
  p++;
  saveToFile();
}

//function used for reservation of seat in particular train 
void Train::allotment()
{
  int seat;
  char number[5];
  top:
  cout << "Train no: ";
  cin >> number;

  int n;
  for (n = 0; n <= p; n++)
  {
    if (strcmp(train[n].trainNo, number) == 0)
      break;
  }
  while (n <= p)
  {
    cout << "\nSeat Number: ";
    cin >> seat;
    if (seat > 32)
    {
      cout << "\nThere are only 32 seats available in this train.";
    }
    else
    {
      if (strcmp(train[n].seat[seat / 4][(seat % 4) - 1], "Empty") == 0)
      {
        cout << "Enter passenger's name: ";
        cin >> train[n].seat[seat / 4][(seat % 4) - 1];
        cout<<"Your ticket is reserved and sent to your registered Email ID"<<'\n';
        system("PAUSE");
        break;
      }
      else
        cout << "The seat no. is already reserved.\n";
    }
    
  }

  if (n > p)
  {
    cout << "Enter correct train no.\n";
    goto top;
  }
  cout<<"Your tickect has been reserved successfully\n";
  saveToFile(); // Save changes to file
  system("CLS");
}

//function print the seat which are empty
void Train::empty()
{
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      strcpy(train[p].seat[i][j], "Empty");
    }
  }
}

//function used to show the seats which are reversed for a particular train no
void Train::show()
{
  int n;
  char number[5];
  cout << "Enter train no: ";
  cin >> number;
  for (n = 0; n <= p; n++)
  {
    if (strcmp(train[n].trainNo, number) == 0)
      break;
  }
  while (n <= p)
  {
    vline('*');
    cout << '\n';
    cout << "Train no: \t" << train[n].trainNo << "\nDriver: \t" << train[n].driver << "\t\tArrival time: \t" << train[n].arrival << "\tDeparture time:" << train[n].depart << "\nFrom: \t\t" << train[n].from << "\t\tTo: \t\t" << train[n].to << "\n";
    vline('*');
    train[0].position(n);
    int a = 1;
    for (int i = 0; i < 8; i++)
    {
      for (int j = 0; j < 4; j++)
      {
        a++;
        if (strcmp(train[n].seat[i][j], "Empty") != 0)
          cout << "\nThe seat no " << (a - 1) << " is reserved";
      }
    }
    break;
  }
  if (n > p)
    cout << "Enter correct train no: ";
}

//function used to print the seat details in matriex form
void Train::position(int l)
{
  int s = 0;
  p = 0;
  for (int i = 0; i < 8; i++)
  {
    cout << "\n";
    for (int j = 0; j < 4; j++)
    {
      s++;
      if (strcmp(train[l].seat[i][j], "Empty") == 0)
      {
        cout.width(5);
        cout.fill(' ');
        cout << s << ".";
        cout.width(10);
        cout.fill(' ');
        cout << train[l].seat[i][j];
        p++;
      }
      else
      {
        cout.width(5);
        cout.fill(' ');
        cout << s << ".";
        cout.width(10);
        cout.fill(' ');
        cout << "Reserved";
      }
    }
  }
  cout << "\n\nThere are " << p << " seats empty in Train No: " << train[l].trainNo;
}

//function will print the train installed in the file(avaiable train)
void Train::avail()
{
  for (int n = 0; n < p; n++)
  {
    vline('_');
    cout<<"\n";
    cout << '\n';
    cout << "Train no: \t" << train[n].trainNo << "\nDriver: \t" << train[n].driver << '\n'<< "Arrival time: \t" << train[n].arrival << "\nDeparture Time:\t" << train[n].depart << "\nFrom: \t\t" << train[n].from << "    " << "\nTo: \t\t" << train[n].to;
    cout <<'\n';
    vline('_');
    cout<<'\n';
  }
}

//function used to read the data from train_data.txt file
void Train::saveToFile()
{
  ofstream outFile("train_data.txt", ios::out);

  if (!outFile)
  {
    cout << "Error opening file for writing!" << endl;
    return;
  }

  for (int i = 0; i < p; i++)
  {
    outFile << train[i].trainNo << ' ' << train[i].driver << ' ' << train[i].arrival << ' ' << train[i].depart << ' '
            << train[i].from << ' ' << train[i].to << endl;

    for (int j = 0; j < 8; j++)
    {
      for (int k = 0; k < 4; k++)
      {
        outFile << train[i].seat[j][k] << ' ';
      }
    }
    outFile << endl;
  }

  outFile.close();
}

//function used to write the data in train_data.txt file
void Train::loadFromFile()
{
  ifstream inFile("train_data.txt", ios::in);

  if (!inFile)
  {
    cerr << "Error opening file for reading!" << endl;
    return;
  }

  p = 0;

  while (inFile >> train[p].trainNo >> train[p].driver >> train[p].arrival >> train[p].depart >> train[p].from >> train[p].to)
  {
    for (int j = 0; j < 8; j++)
    {
      for (int k = 0; k < 4; k++)
      {
        inFile >> train[p].seat[j][k];
      }
    }
    p++;
  }

  inFile.close();
}

//function used for train reservation
int trainfunction()
{
    train[0].loadFromFile(); // Load existing data from file

  int w;

  while (1)
  {
    system("CLS");
    cout << "\n\t\t\t\t=========================";
            cout << "\n\t\t\t\t TRAIN BOOKING";
            cout << "\n\t\t\t\t=========================";
            cout<<'\n';
    cout << "\t\t\t1.Install\n\t\t\t"
         << "2.Reservation\n\t\t\t"
         << "3.Show\n\t\t\t"
         << "4.Trains Available. \n\t\t\t"
         << "5.Exit";

    cout << "\n\t\t\tEnter your choice:-> ";
    cin >> w;

    switch (w)
    {
    case 1:
      train[p].install();
      system("PAUSE");
      system("CLS");
      break;

    case 2:
      train[p].allotment();
      system("CLS");
      break;

    case 3:
      train[0].show();
      system("PAUSE");
      system("CLS");
      break;

    case 4:
      train[0].avail();
      system("PAUSE");
      system("CLS");
      break;

    case 5:
      return 0; 
    }
  }
}

//class for bus
class Bus
{
  // declaration of the variable used in the class
  char busn[5], driver[10], arrival[5], depart[5], from[10], to[10], seat[8][4][10];

public:
  // this are declaration of function used in the bus class
  void install();
  void allotment();
  void empty();
  void show();
  void avail();
  void position(int i);
  void saveToFile();
  void loadFromFile();
};

Bus bus[10];

void line(char ch)
{
  for (int i = 80; i > 0; i--)
    cout << ch;
}

//function used to install a new bus in the system
void Bus::install()
{
  char newBusNo[5];
  cout << "Enter bus no: ";
  cin >> newBusNo;

  // Check if the bus number already exists
  for (int i = 0; i < p; i++)
  {
    if (strcmp(bus[i].busn, newBusNo) == 0)
    {
      cout << "Bus with the same number already exists. Please enter a different bus number.\n";
      return; // Exit the function if the bus number already exists
    }
  }

  // If the bus number is unique, proceed with installation
  strcpy(bus[p].busn, newBusNo);

  cout << "\nEnter Driver's name: ";
  cin >> bus[p].driver;

  cout << "\nArrival time: ";
  cin>>bus[p].arrival;

  cout << "\nDeparture: ";
  cin >> bus[p].depart;

  cout << "\nFrom: \t\t\t";
  cin >> bus[p].from;

  cout << "\nTo: \t\t\t";
  cin >> bus[p].to;

  bus[p].empty();
  p++;
  saveToFile();
}

//function used for the reservation of seat in a particular bus
void Bus::allotment()
{
  int seat;
  char number[5];
  top:
  cout << "Bus no: ";
  cin >> number;

  int n;
  for (n = 0; n <= p; n++)
  {
    if (strcmp(bus[n].busn, number) == 0)
    break;
  }
  while (n <= p)
  {
    cout << "\nSeat Number: ";
    cin >> seat;
    if (seat > 32)
    {
        cout << "\nThere are only 32 seats available in this bus.";
    }
    else
    {
        if (strcmp(bus[n].seat[seat / 4][(seat % 4) - 1], "Empty") == 0)
        {
            cout << "Enter passanger's name: ";
            cin >> bus[n].seat[seat / 4][(seat % 4) - 1];
             cout<<"Your ticket is reserved and sent to your registered Email ID"<<'\n';
            system("PAUSE");
            break;
        }
        else
        cout << "The seat no. is already reserved.\n";
    }
  }

  if (n > p)
  {
    cout << "Enter correct bus no.\n";
    goto top;
  }
   saveToFile(); // Save changes to file
}


//Function used to print the seat which are empty
void Bus::empty()
{
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      strcpy(bus[p].seat[i][j], "Empty");
    }
  }
}

//function used to show the seats which are reversed for a particular bus no
void Bus::show()
{
  int n;
  char number[5];
  cout << "Enter bus no: ";
  cin >> number;
  for (n = 0; n <= p; n++)
  {
    if (strcmp(bus[n].busn, number) == 0)
      break;
  }
  while (n <= p)
  {
    vline('*');
    cout << '\n';
    cout << "Train no: \t" << bus[n].busn << "\nDriver: \t" << bus[n].driver << "\t\tArrival time: \t" << bus[n].arrival << "\tDeparture time:" << bus[n].depart << "\nFrom: \t\t" << bus[n].from << "\t\tTo: \t\t" << bus[n].to << "\n";
    vline('*');
    bus[0].position(n);
    int a = 1;
    for (int i = 0; i < 8; i++)
    {
      for (int j = 0; j < 4; j++)
      {
        a++;
        if (strcmp(bus[n].seat[i][j], "Empty") != 0)
          cout << "\nThe seat no " << (a - 1) << " is reserved"<<'\n';
      }
    }
    break;
  }
  if (n > p)
    cout << "Enter correct bus no: ";
}

//function used to print the seat details in matriex form
void Bus::position(int l)
{
  int s = 0;
  p = 0;
  for (int i = 0; i < 8; i++)
  {
    cout << "\n";
    for (int j = 0; j < 4; j++)
    {
      s++;
      if (strcmp(bus[l].seat[i][j], "Empty") == 0)
      {
        cout.width(5);
        cout.fill(' ');
        cout << s << ".";
        cout.width(10);
        cout.fill(' ');
        cout << bus[l].seat[i][j];
        p++;
      }
      else
      {
        cout.width(5);
        cout.fill(' ');
        cout << s << ".";
        cout.width(10);
        cout.fill(' ');
        cout << "Reserved";
      }
    }
  }
  cout << "\n\nThere are " << p << " seats empty in Bus No: " << bus[l].busn;
}

//function will print the bus installed in the file(avaiable buses)
void Bus::avail()
{
  for (int n = 0; n < p; n++)
  {
    vline('*');
    cout<<'\n';
    cout << "Bus no: \t" << bus[n].busn << "\nDriver: \t" << bus[n].driver<< '\n'<<"Arrival time: \t" << bus[n].arrival << "\tDeparture Time:\t"<< bus[n].depart << "\nFrom: \t\t" << bus[n].from <<"    "<< "\t\tTo: \t\t"<< bus[n].to << "\n";
    vline('*');
    cout<<'\n';
    vline('_');
  }
}

//function used to read the data from bus_data.txt file
void Bus::saveToFile()
{
  ofstream outFile("bus_data.txt", ios::out);

  if (!outFile)
  {
    cerr << "Error opening file for writing!" << endl;
    return;
  }

  for (int i = 0; i < p; i++)
  {
    outFile << bus[i].busn << ' ' << bus[i].driver << ' ' << bus[i].arrival << ' ' << bus[i].depart << ' '
            << bus[i].from << ' ' << bus[i].to << endl;

    for (int j = 0; j < 8; j++)
    {
      for (int k = 0; k < 4; k++)
      {
        outFile << bus[i].seat[j][k] << ' ';
      }
    }
    outFile << endl;
  }

  outFile.close();
}


//function used to write the data in bus_data.txt file
void Bus::loadFromFile()
{
  ifstream inFile("bus_data.txt", ios::in);

  if (!inFile)
  {
    cerr << "Error opening file for reading!" << endl;
    return;
  }

  p = 0;

  while (inFile >> bus[p].busn >> bus[p].driver >> bus[p].arrival >> bus[p].depart >> bus[p].from >> bus[p].to)
  {
    for (int j = 0; j < 8; j++)
    {
      for (int k = 0; k < 4; k++)
      {
        inFile >> bus[p].seat[j][k];
      }
    }
    p++;
  }

  inFile.close();
}

//Function for bus reservation
int busfunction()
{
     bus[0].loadFromFile(); // Load existing data from file

  int w;

  while (1)
  {
    system("CLS");
    cout << "\n\t\t\t\t=========================";
            cout << "\n\t\t\t\t BUS BOOKING";
            cout << "\n\t\t\t\t=========================";
            cout<<'\n';
    cout << "\t\t\t1.Install\n\t\t\t"
         << "2.Reservation\n\t\t\t"
         << "3.Show\n\t\t\t"
         << "4.Buses Available. \n\t\t\t"
         << "5.Exit";

    cout << "\n\t\t\tEnter your choice:-> ";
    cin >> w;

    switch (w)
    {
    case 1:
      bus[p].install();
      system("PAUSE");
      system("CLS");
      break;

    case 2:
      bus[p].allotment();
      system("PAUSE");
      system("CLS");
      break;

    case 3:
      bus[0].show();
      system("PAUSE");
      system("CLS");
      
      break;

    case 4:
      bus[0].avail();
      system("PAUSE");
      system("CLS");
      break;

    case 5:
      return 0;
    }
  }
}

// Function for getting passenger details for cab booking
void details3()
{
    int k;
    // Clearing Screen
    system("CLS");

    // Calling heading() function
    heading();
    cout << "\t\t\t\tEnter Number Of Passengers: ";
    cin >> k;
    cout << "\t\t\t\tEnter Date (DD/MM/YYYY): ";
    fflush(stdin);
    cin.ignore();
    cin.getline(date, 100);
    cout << "\t\t\t\tEnter the Time of pickup (hour:min AM/PM): ";
    fflush(stdin);
    cin.ignore();
    cin.getline(time, 100);
    system("CLS");
}


//Function to print the receipt after cab reservation
void receipt3()
{
    Node *ptr = start;
    int b, n;

    if (dis < 50)
    {
        b = 50 * 12;
    }
    else
    {
        b = 50 * 5 + (dis - 50) * 15;
    }

    cout << "\t\t\t\tTotal Amount: " << b << endl;
    cout << "\t\t\t\tEnter 1 to book the cab or enter any other to exit" << endl;
    cin >> n;
    cout << endl;
    if (n == 1)
    {
        heading();
        cout << "\n\t\t\t\t**Take Screenshot For Further Use**\n";
        cout << "\t\t\t\tSelected Type: " << type << endl;
        cout << "\t\t\t\tFrom: " << where << endl;
        cout << "\t\t\t\tTo: " << to << endl;
        cout << "\t\t\t\tDate: " << date << endl;
        cout << "\t\t\t\tTime of Pickup: " << time << endl;
        cout << "\t\t\t\tTotal Distance: " << dis << endl;

        if (dis < 50)
        {
            b = 50 * 12;
        }
        else
        {
            b = 50 * 5 + (dis - 50) * 15;
        }

        cout << "\t\t\t\tYour Cab Confirmation has been sent to your registered E-mail ID\n";
        cout << "\t\t\t\tTotal Amount: " << b << endl;
        cout << "\t\t\t\t**Thank You For Registration**";
    }
    else
    {
        exit(0);
    }
    system("PAUSE");
}

//Function for cab reservation
int cabfunction()
{
    char c[100];
    char c1[100];

    // Clearing Screen
    system("CLS");

   
    cout << "\n\t\t\t\t=========================";
            cout << "\n\t\t\t\t Cab BOOKING";
            cout << "\n\t\t\t\t=========================";
            cout<<'\n';
    cout << "For First 50KM cost is 12 per KM and after that 5 extra per KM\n";
    strcpy(type, "Cab Booking");
    cout << "Enter the Pickup Address: ";
    cin >> c;
    cout << "Enter the place Drop Address: ";
    cin >> c1;
    cout << "Enter the distance between both the place: ";
    cin >> dis;
    strcpy(where, c);
    strcpy(to, c1);

    // Calling details() function
    details3();

    // Calling receipt() function
    receipt3();
}

//Driver code
int main()
{
    heading();
    userprofile *p = nullptr;
    int a;
    p = InitializeListing(p);
    while (1)
    {
        if (currentwindow == main_menu)
        {
            cout << "\n\t\t\tAdd User - 1\n\t\t\tLogin User - 2\n\t\t\tExit - 3\n";
            cout << "Enter Your Choice\n";
            cin >> a;
            switch (a)
            {
            case 1:
                p = Adding_new_client(p);
                system("PAUSE");
                system("CLS");
                break;

            case 2:
                login_client(p);
                break;

            case 3:
                exit(0);
                break;

            default:
                cout << "Invalid Input\n";
            }
        }
        else if (currentwindow == login_system)
        {
            system("CLS");
            cout << "\n\t\t\t\t=========================";
            cout << "\n\t\t\t\tTOURISM MANAGEMENT SYSTEM";
            cout << "\n\t\t\t\t=========================";
            cout << "\n";
            int a;
            cout << "\t\t\t\t1. Train Booking ""\n";
            cout << "\n";
            cout << "\t\t\t\t2. Bus Booking\n";
            cout << "\n";
            cout << "\t\t\t\t3. Cab Booking\n";
            cout << "\n";
            cout << "\t\t\t\t4. Logic Out\n";
            cout << "\n";
            cout << "\t\t\t\tEnter Choice: ";
            cin >> a;

            switch (a)
            {
            case 1:
                trainfunction();
                break;

            case 2:
                busfunction();
                break;

            case 3:
                cabfunction();
                break;

            case 4:
                logout_client();
                system("PAUSE");
                system("CLS");
                break;

            default:
                cout << "Enter Right Choice...";
                break;
            }
        }
    }
    return 0;
}