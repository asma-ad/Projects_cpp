#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;
// Project 01: Bank_1

const string clientFile = "Clients.txt";

enum enOptions
{
    showClient = 1,
    addClient = 2,
    deleteClient = 3,
    updateClient = 4,
    findTheClient = 5,
    exitButtun = 6
};

struct stClientData
{
    string pinCode;
    string accountNumber;
    string name;
    string numberPhone;
    double balance;
    bool markForDelete = false;
};

void start();

void printMenuScreen()
{
    system("cls");
    cout << "================================================\n";
    cout << "\t\tMenu screen\n";
    cout << "================================================\n";
    cout << "\t[1] Show clients list.\n";
    cout << "\t[2] Add new client.\n";
    cout << "\t[3] Delete client.\n";
    cout << "\t[4] Update client info.\n";
    cout << "\t[5] Find client.\n";
    cout << "\t[6] Exit.\n";
    cout << "================================================\n";
}

short readMenuOpetion()
{
    short answer = 0;
    do
    {
        printMenuScreen();
        cout << "Choose what do you want to do [1-6]?  ";
        cin >> answer;
    } while (answer < 1 || answer > 6);
    return answer;
}

void goBackToMenu()
{
    cout << "Press any key to go back to the menu ...";
    system("pause");
    start();
}

void printClientRecord(stClientData client)
{
    cout << "|  " << left << setw(15) << client.accountNumber;
    cout << "|  " << left << setw(10) << client.pinCode;
    cout << "|  " << left << setw(40) << client.name;
    cout << "|  " << left << setw(12) << client.numberPhone;
    cout << "|  " << left << setw(12) << client.balance;
}

std::vector<std::string> split(std::string text, std::string delim)
{
    std::vector<std::string> vWords;
    std::string word;
    short pos = 0;

    while ((pos = text.find(delim)) != std::string::npos)
    {
        word = text.substr(0, pos);
        if (word != "")
            vWords.push_back(word);
        text.erase(0, pos + delim.length());
    }
    if (text != "")
        vWords.push_back(text);

    return vWords;
}

stClientData convertLineDataToRecord(string record, string seperator = "#//#")
{
    stClientData stClient;
    vector<string> vClient = split(record, seperator);

    stClient.accountNumber = vClient[0];
    stClient.pinCode = vClient[1];
    stClient.name = vClient[2];
    stClient.numberPhone = vClient[3];
    stClient.balance = stod(vClient[4]);

    return stClient;
}

vector<stClientData> loadClientDataFromFile(string fileName)
{
    vector<stClientData> vClient;
    fstream MyFile;
    MyFile.open(fileName, ios::in); // read mode
    if (MyFile.is_open())
    {
        string line;
        stClientData client;
        while (getline(MyFile, line))
        {
            // convert line to record (struct)
            client = convertLineDataToRecord(line);
            // add record (struct) to vector
            vClient.push_back(client);
        }
        MyFile.close();
    }
    return vClient;
}

void printAllClientsData()
{
    vector<stClientData> vClient = loadClientDataFromFile(clientFile);
    // header
    cout << "\n\t\t\t\t\tClient List (" << vClient.size() << ") client(s).";
    cout << "\n---------------------------------------------------------------------------------------------------------------\n";

    cout << "|  " << left << setw(15) << "Account number";
    cout << "|  " << left << setw(10) << "PIN code";
    cout << "|  " << left << setw(40) << "Client name";
    cout << "|  " << left << setw(12) << "Phone";
    cout << "|  " << left << setw(12) << "Balance";
    cout << "\n---------------------------------------------------------------------------------------------------------------\n";

    // body
    for (stClientData client : vClient)
    {
        printClientRecord(client);
        cout << "\n";
    }
    cout << "\n---------------------------------------------------------------------------------------------------------------\n";
}

void addDataLineToFile(string FileName, string stDataLine)
{
    // declare
    fstream MyFile;
    // open a file for writting or appending
    MyFile.open(FileName, ios::out | ios::app);
    // check if the file is open
    if (MyFile.is_open())
    {
        // add data line to the file
        MyFile << stDataLine << endl;
        // close the file
        MyFile.close();
    }
    else
    {
        cerr << "Error: Unable to open the file " << FileName << " for writing or appending.\n";
    }
}

string convertRecordToLine(stClientData client, string seperator = "#//#")
{
    string str = "";

    str += client.accountNumber + seperator;
    str += client.pinCode + seperator;
    str += client.name + seperator;
    str += client.numberPhone + seperator;
    str += to_string(client.balance);

    return str;
}

bool isClientExistsByAccountNumber(string account_n, string fileName)
{
    vector<stClientData> vClients;
    fstream MyFile;
    MyFile.open(fileName, ios::in);
    if (MyFile.is_open())
    {
        string line;
        stClientData client;
        while (getline(MyFile, line))
        {
            client = convertLineDataToRecord(line);
            if (client.accountNumber == account_n)
            {
                MyFile.close();
                return true;
            }
            vClients.push_back(client);
        }
        MyFile.close();
    }
    return false;
}

stClientData readData()
{
    stClientData client;

    cout << "Enter your account number: ";
    getline(cin >> ws, client.accountNumber);
    // check if account number exists
    while (isClientExistsByAccountNumber(client.accountNumber, clientFile))
    {
        cout << "\nClient " << client.accountNumber << " already exists, enter another one! ";
        cout << "\nEnter your account number: ";
        getline(cin >> ws, client.accountNumber);
    }

    cout << "Enter your PIN code: ";
    getline(cin, client.pinCode);

    cout << "Enter your name: ";
    getline(cin, client.name);

    cout << "Enter your phone number: ";
    getline(cin, client.numberPhone);

    cout << "Enter your account balance: ";
    cin >> client.balance;

    return client;
}

void addNewClient()
{
    stClientData client = readData();
    addDataLineToFile(clientFile, convertRecordToLine(client));
}

void addClients()
{
    char addMore = 'Y';
    do
    {
        cout << "Adding new client:\n\n";
        addNewClient();
        cout << "\nClient added successufully!\nDo you want to add more clients? [Y/N]: ";
        cin >> addMore;

    } while (toupper(addMore) == 'Y');
}

void showAddClientsScreen()
{
    cout << "==================================================\n";
    cout << "\t\tAdd new client screen\n";
    cout << "==================================================\n";
    addClients();
}

string readAccountNumber()
{
    string account_N = "";
    cout << "Enter account number: ";
    cin >> account_N;
    return account_N;
}

bool isClientFound(vector<stClientData> vClient, stClientData &client, string account_N)
{
    for (stClientData c : vClient)
    {
        if (c.accountNumber == account_N)
        {
            client = c;
            return true;
        }
    }

    return false;
}

bool isClientFound(stClientData &client, string account_N)
{
    vector<stClientData> vClient = loadClientDataFromFile(clientFile);
    for (stClientData c : vClient)
    {
        if (c.accountNumber == account_N)
        {
            client = c;
            return true;
        }
    }

    return false;
}

bool markAccountForDeletion(vector<stClientData> &vClients, string account_N)
{
    for (stClientData &c : vClients)
    {
        if (c.accountNumber == account_N)
        {
            c.markForDelete = true;
            return true;
        }
    }
    return false;
}

vector<stClientData> saveClientsToFile(string fileName, vector<stClientData> vClients)
{
    fstream MyFile;
    // open file to overwrite
    MyFile.open(fileName, ios::out);
    string dataLine;
    if (MyFile.is_open())
    {
        for (stClientData c : vClients)
        {
            // add only clients that are not marked for deletion
            if (c.markForDelete == false)
            {
                dataLine = convertRecordToLine(c);
                MyFile << dataLine << endl;
            }
        }
        MyFile.close();
    }
    return vClients;
}

void printClientCard(stClientData client)
{
    cout << "\nAccount number :  " << client.accountNumber;
    cout << "\nPIN code       :  " << client.pinCode;
    cout << "\nClient name    :  " << client.name;
    cout << "\nNumber phone   :  " << client.numberPhone;
    cout << "\nBalaance       :  " << client.balance;
    cout << "\n\n";
}

bool deleteClients(vector<stClientData> &vClients, string account_N)
{
    stClientData client;
    char answer = 'n';

    if (isClientFound(vClients, client, account_N))
    {
        printClientCard(client);
        cout << "\n\nAre you sure you want to delete this client [Y/N]?  ";
        cin >> answer;

        if (answer == 'y' || answer == 'Y')
        {
            // mark account for deletion
            markAccountForDeletion(vClients, account_N);
            // save clients to file
            saveClientsToFile(clientFile, vClients);
            // refrsh clients
            vClients = loadClientDataFromFile(clientFile);

            cout << "\n\nClient account deleted successfully!";
            return true;
        }
    }
    cout << "Account " << account_N << " Not found!\n";
    return false;
}

void showDeleteClientsScreen()
{
    cout << "==================================================\n";
    cout << "\t\tDelete client screen\n";
    cout << "==================================================\n";

    vector<stClientData> vClients = loadClientDataFromFile(clientFile);
    string account_N = readAccountNumber();

    deleteClients(vClients, account_N);
}

stClientData changeClientData(string account_N)
{
    stClientData client;
    client.accountNumber = account_N;

    cout << "Enter your PIN code: ";
    getline(cin >> ws, client.pinCode);

    cout << "Enter your name: ";
    getline(cin, client.name);

    cout << "Enter your phone number: ";
    getline(cin, client.numberPhone);

    cout << "Enter your account balance: ";
    cin >> client.balance;

    return client;
}

bool updateClientAccount(vector<stClientData> &vClients, string account_N)
{
    stClientData client;
    char answer = 'n';

    if (isClientFound(vClients, client, account_N))
    {
        printClientCard(client);
        cout << "\n\nAre you sure you want to update this client [Y/N]?  ";
        cin >> answer;

        if (answer == 'y' || answer == 'Y')
        {
            // update account
            for (stClientData &c : vClients)
            {
                if (c.accountNumber == account_N)
                {
                    c = changeClientData(account_N);
                    break;
                }
            }
            // save clients to file
            saveClientsToFile(clientFile, vClients);

            cout << "\n\nClient account updated successfully!";
            return true;
        }
    }
    cout << "Account " << account_N << " Not found!\n";
    return false;
}

void showUpdateClientsScreen()
{
    cout << "==================================================\n";
    cout << "\t\tUpdate client screen\n";
    cout << "==================================================\n";

    vector<stClientData> vClients = loadClientDataFromFile(clientFile);
    string account_N = readAccountNumber();

    updateClientAccount(vClients, account_N);
}

void findClient()
{
    string account_N = readAccountNumber();
    stClientData client;

    if (isClientFound(client, account_N))
        printClientCard(client);
    else
        cout << "Not found!\nThere's no account with " << account_N << "!\n";
}

void showFindClientsScreen()
{
    cout << "==================================================\n";
    cout << "\t\tFindclient screen\n";
    cout << "==================================================\n";
    findClient();
}

void showEndScreen()
{
    cout << "==================================================\n";
    cout << "\t\tThank you!\n";
    cout << "==================================================\n";
}
void ActiveMenuOption(enOptions menuOption)
{
    switch (menuOption)
    {
    case enOptions::showClient:
        system("cls");
        printAllClientsData();
        goBackToMenu();
        break;
    case enOptions::addClient:
        system("cls");
        showAddClientsScreen();
        goBackToMenu();
        break;
    case enOptions::deleteClient:
        system("cls");
        showDeleteClientsScreen();
        goBackToMenu();
        break;
    case enOptions::updateClient:
        system("cls");
        showUpdateClientsScreen();
        goBackToMenu();
        break;
    case enOptions::findTheClient:
        system("cls");
        showFindClientsScreen();
        goBackToMenu();
        break;
    case enOptions::exitButtun:
        system("cls");
        showEndScreen();
        break;
    default:
        break;
    }
}

void start()
{
    ActiveMenuOption(enOptions(readMenuOpetion()));
}

int main()
{
    start();
    return 0;
}