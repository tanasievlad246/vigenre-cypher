#include <iostream>

using namespace std;

string message;
string mappedKey;
int tableArr[26][26];

void messageAndKey()
{
    string msg;
    cout << "Enter your message: ";
    getline(cin, msg);
    cin.ignore();
    cout << "\n";

    for (int i = 0; i < msg.length(); i++)
    {
        msg[i] = toupper(msg[i]);
    }

    string key;
    cout << "Enter the key: ";
    getline(cin, key);
    cin.ignore();

    for (int i = 0; i < key.length(); i++)
    {
        key[i] = toupper(key[i]);
    }

    // mapping key to msg
    string keyMap = "";
    for (int i = 0,j = 0; i < msg.length();i++)
    {
        if(msg[i] ==32)
        {
            keyMap += 32;
        } 
        else 
        {
            if(j<key.length())
            {
                keyMap += key[j];
                j++;
            } 
            else 
            {
                j = 0;
                keyMap += key[j];
                j++;
            }
        }
    }

    message = msg;
    mappedKey = keyMap; 
}

void createVigenereTable()
{
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            int temp;
            if((i+65)+j > 90)
            {
                temp = ((i+65)+j) - 26;

                //adding ASCII of alphabet letter in table index position
                tableArr[i][j] = temp;
            } 
            else 
            {
                temp = (i+65)+j;

                //adding ASCII of alphabet letter in table index position
                tableArr[i][j] = temp;
            }
        } // for j loop
    } // for i loop
}

void cipherEncryption(string message, string mappedKey)
{
    createVigenereTable();
    string encryptedText = "";
    for(int i = 0; i < message.length(); i++)
    {
        if(message[i] == 32 && mappedKey[i] == 32)
        {
            encryptedText += " ";
        } 
        else 
        {
            int x = (int)message[i]-65;
            int y = (int)mappedKey[i]-65;
            encryptedText += (char)tableArr[x][y];
        }
    }

    cout << "Encrypted Text: " << encryptedText << endl;
}

int itrCount(int key, int msg)
{
    int counter = 0;
    string result = "";

    //starting from ASCII of letter of Key and ending at letter of message
    // to get full 26 letters of alphabet
    for(int i = 0; i < 26; i++)
    {
        if(key+i > 90)
        {
            result += (char)(key+(i-26));
        } 
        else 
        {
            result += (char)(key+i);
        }
    } //for

    for(int i = 0; i < result.length(); i++)
    {
        if(result[i] == msg)
        {
            break;
        } 
        else 
        {
            counter++;
        }
    }
    return counter;
}

void cipherDecryption(string message, string mappedKey)
{
    string decryptedText = "";
    for(int i = 0; i < message.length(); i++)
    {
        if(message[i] == 32 && mappedKey[i] == 32)
        {
            decryptedText += " ";
        } 
        else 
        {
            int temp = itrCount((int)mappedKey[i], (int)message[i]);
            decryptedText += (char)(65+temp);
        }
    }

    cout << "Decrypted Text: " << decryptedText << endl;
}

int main()
{
    cout << "Message can only be alphabetic!" << endl; 

    int choice;

    cout << "1. Encryption\n2. Decryption\nChose (1, 2)" << endl;
    cin >> choice;
    cin.ignore();

    if (choice == 1)
    {
        cout << "Encryption" << endl;
        messageAndKey();
        cipherEncryption(message, mappedKey);
    }
    else if (choice == 2)
    {
        cout << "Decryption" << endl;
        messageAndKey();
        cipherDecryption(message, mappedKey);
    }
    else 
    {
        cout << "Wrong choice, please pick 1 or 2" << endl;
    }
    return 0;
}