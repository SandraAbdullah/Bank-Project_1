#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

const string ClientsFileName = "Clients.txt";

struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance = 0;
    bool MarkForDelete = false;
};

string ReadClientAccountNumber()
{
    string AccountNumber = "";
    cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;

    return AccountNumber;
}

sClient ReadClientData()
{
    sClient Client;
    cout << "Please enter AccountNumber? ";
    getline(cin >> ws, Client.AccountNumber);

    cout << "Please enter PinCode? ";
    getline(cin, Client.PinCode);

    cout << "Please enter Name? ";
    getline(cin, Client.Name);

    cout << "Please enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Please enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;
}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{
    string ClientDataLine = "";

    ClientDataLine = Client.AccountNumber + Seperator;
    ClientDataLine += Client.PinCode + Seperator;
    ClientDataLine += Client.Name + Seperator;
    ClientDataLine += Client.Phone + Seperator;
    ClientDataLine += to_string(Client.AccountBalance);

    return ClientDataLine;
}

void AddDataLineToFile(string FileName, sClient Client)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {
        string ClientDataLine = ConvertRecordToLine(Client);
        MyFile << ClientDataLine << endl;

        MyFile.close();
    }
}

vector<string> SplitString(string S1, string Delim)
{
    vector<string>vString;

    short pos = 0;
    string sWard;

    while ((pos = S1.find(Delim)) != S1.npos)
    {
        sWard = S1.substr(0, pos);

        if (sWard != "")
        {
            vString.push_back(sWard);

        }S1.erase(0, pos + Delim.length());
    }

    if (S1 != "")
    {
        vString.push_back(S1);
    }

    return vString;
}

sClient ConvertLineToRecord(string Line, string Seperator = "#//#")
{
    sClient Client;

    vector<string>vClientData = SplitString(Line, Seperator);

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);

    return Client;
}

vector <sClient> LoadClientsDataFromFile(string FileName)
{
    vector <sClient> vClients;

    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLineToRecord(Line);
            vClients.push_back(Client);
        }
        MyFile.close();
    }
    return vClients;
}

void AddNewClientAndSaveDataToFile(string FileName, vector<sClient>vClients)
{
    sClient Client = ReadClientData();

    AddDataLineToFile(FileName, Client);

    vClients = LoadClientsDataFromFile(ClientsFileName);
}

void AddingNewClient(vector<sClient>vClients)
{
    cout << "------------------------------------\n";
    cout << "\tAdd New Client Screen\n";
    cout << "------------------------------------\n";

    char AddMore = 'Y';

    do
    {
        cout << "Adding new Client:\n\n";
        AddNewClientAndSaveDataToFile(ClientsFileName, vClients);
        cout << "\nClient Added Successfully, do you want to add more Client?\n";
        cin >> AddMore;
    } while (toupper(AddMore) == 'Y');
}

void PrintClientCard(sClient Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code     : " << Client.PinCode;
    cout << "\nName         : " << Client.Name;
    cout << "\nPhone        : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
}

void PrintClientRecord(sClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void ShowAllClients(vector <sClient> vClients)
{
    cout << "\n\t\t\t\t\tClients List (" << vClients.size() << ") Client(s).\n";
    cout << "-------------------------------------------------------------------------------------------------------\n" << endl;
    cout << "| " << setw(15) << left << "Account Number";
    cout << "| " << setw(10) << left << "Pin Code";
    cout << "| " << setw(40) << left << "Client Name";
    cout << "| " << setw(12) << left << "Phone";
    cout << "| " << setw(12) << left << "Balance";

    cout << "\n-------------------------------------------------------------------------------------------------------\n" << endl;

    for (sClient Client : vClients)
    {
        PrintClientRecord(Client);
        cout << endl;
    }
    cout << "\n-------------------------------------------------------------------------------------------------------\n" << endl;
}

bool FindClintByAccountNumber(string AccountNumber, vector<sClient>vClients, sClient& Client)
{
    for (sClient C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}

void PrintClientAfterFoundAcoountNumber(vector<sClient>vClients, sClient& Client)
{
    string AccountNumber = ReadClientAccountNumber();
    if (FindClintByAccountNumber(AccountNumber, vClients, Client))
        PrintClientCard(Client);
    else
        cout << "\n\nClient with Account Number (" << AccountNumber << ") is Not Found!" << endl;


}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<sClient>& vClients)
{
    for (sClient& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }
    }
    return false;
}

sClient ChangeClientRecord(string AccountNumber)
{
    sClient Client;

    Client.AccountNumber = AccountNumber;

    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;
}

vector<sClient> SaveVectorToFile(string FileName, vector<sClient> vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);

    string DataLine;

    if (MyFile.is_open())
    {
        for (sClient C : vClients)
        {
            if (C.MarkForDelete == false)
            {
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }

    return vClients;

}

bool DeleteClientByAccountNumber(vector<sClient>& vClients)
{
    string AccountNumber = ReadClientAccountNumber();

    sClient Client;
    char Answer = 'n';

    if (FindClintByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);

        cout << "\n\nAre you sure you want to delete this client? y/n ?\n";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);

            SaveVectorToFile(ClientsFileName, vClients);

            vClients = LoadClientsDataFromFile(ClientsFileName);

            cout << "\n\nClient Deleted successfully." << endl;

            return true;
        }
    }

    else
    {
        cout << "\n\nClient with Account Number (" << AccountNumber << ") is Not Found!" << endl;
        return false;
    }
}

bool UpdateClientByAccountNumber(vector<sClient>& vClients)
{
    cout << "------------------------------------\n";
    cout << "\tUpdate Client Info Screen\n";
    cout << "------------------------------------\n";

    string AccountNumber = ReadClientAccountNumber();

    sClient Client;
    char Answer = 'n';

    if (FindClintByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);

        cout << "\n\nAre you sure you want to update this client? y/n? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            for (sClient& C : vClients)
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
        }

        SaveVectorToFile(ClientsFileName, vClients);

        cout << "\n\nClient Updated Successfully.";

        return true;
    }

    else
    {
        cout << "\n\nClient with Account Number (" << AccountNumber << ") is Not Found!" << endl;
        return false;
    }
}

short MainMenueScreen()
{
    cout << "================================================\n";
    cout << "\t\tMain Menue Screen\n";
    cout << "================================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Exit.\n";
    cout << "================================================\n";


    short Number;
    do
    {
        cout << "Choose what do you want to do?  [1 to 6]?\n";
        cin >> Number;
    } while (Number < 1 || Number>6);
    return Number;
}

void DoOrders(vector <sClient> vClients, sClient& Client)
{
    short Number = MainMenueScreen();

    switch (Number)
    {
      case 1:
        system("cls");
        ShowAllClients(vClients);
        cout << "\n\nPress any key to go back to main menue\n";
        system("pause > 0");
        system("cls");
        DoOrders(vClients, Client);
        break;
 
      case 2:
          system("cls");
          AddingNewClient(vClients);
          cout << "\n\nPress any key to go back to main menue\n";
          system("pause > 0");
          system("cls");
          DoOrders(vClients, Client);
          break;

      case 3:
          system("cls");

          cout << "------------------------------------\n";
          cout << "\tDelete Client Screen\n";
          cout << "------------------------------------\n";

          DeleteClientByAccountNumber(vClients);
          cout << "\n\nPress any key to go back to main menue\n";
          system("pause > 0");
          system("cls");
          DoOrders(vClients, Client);
          break;

      case 4:
          system("cls");
          UpdateClientByAccountNumber(vClients);
          cout << "\n\nPress any key to go back to main menue\n";
          system("pause > 0");
          system("cls");
          DoOrders(vClients, Client);
          break;

      case 5:
          system("cls");

          cout << "------------------------------------\n";
          cout << "\tFind Client Screen\n";
          cout << "------------------------------------\n";

          PrintClientAfterFoundAcoountNumber(vClients, Client);
          cout << "\n\nPress any key to go back to main menue\n";
          system("pause > 0");
          system("cls");
          DoOrders(vClients, Client);
          break;

      default:
          system("cls");
          cout << "---------------------------------------\n";
          cout << "\t\tProgram Ends :-)\n";
          cout << "---------------------------------------\n";
          system("pause > 0");
    }
}

int main()
{ 
    sClient Client;
    
    vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);

    DoOrders(vClients, Client);

    return 0;
}
