//  Brett Arnold
//  Project 1 Starter Code - DNA Profiling
//  Program takes commands and file names from user 
//  and displays different databases with DNA strand
//  counting/ processing and dna strand search features
//
#include "ourvector.h"
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>

using namespace std;

ourvector<string> strDb, strDna, strProcess;
int prcsCheck, count = 0;
ifstream infile;

int menuCall(); // function prototype

//open file and fills database vector
void loadDb(string file)
{
    string data1;
    infile.open(file); // open file and check
    cout << "Loading database..." << endl;
    
    if (!infile.is_open())
    {
        cout << "Error: unable to open " << file << endl;
    }
    
    while (!infile.eof()) // read file data
    {
        infile >> data1;
        if (infile.fail())
        {
            break;
        }

        strDb.push_back(data1); // save data to vector
    }
   /*if(infile.is_open() == true) // personal check // not needed
    {
        cout << "Loading database..." << endl; // check 
    }*/

    infile.close();
    menuCall();
}
// parse vector string and display or save to vector
void parseString(int start, int end, ourvector<string> file) // parses proper piece of file and swaps commas in files
{
    char ch[end + 1];
    string strchar;

   for(int i = start; i < end; i++)
   {
    strchar = file.at(i);
   //s = str[i]; // same accessor
    strcpy(ch, strchar.c_str()); // copy string to char array
 
    for (unsigned int j = 0; j < strchar.length(); j++) // go through string
    {
        
        if(ch[j] == ',') // flip characters
        {
            ch[j] = ' ';
        }
        if(start >= 1) // checks for vector database parse
        {
            cout << ch[j]; // displays database
        }

        // inject into process string only if processing
        if(start == 0) // checks parse for Dna keys
        {
            std::string s;
            char c = ch[j];
            s.push_back(c);
            strProcess.push_back(s);
        }
    }
    //new line for database display
    if(start >= 1)
    {
     cout << endl;
    }
   }
}

// display messages for empty vectors
void checkVectors() 
{
     if(strDna.size() != 0)
   {
    cout << endl << "DNA loaded:" << endl;
    for(int i = 0; i < strDna.size(); i++)
    {
        cout << strDna.at(i) << endl;
    }
   }
   if(strDna.size() == 0)
   {
    cout << endl << "No DNA loaded." << endl;
   }
   
   if(prcsCheck != 0) // this line is actually just a check// not needed
   {
    cout << endl << "DNA processed.";
   }
   if(prcsCheck == 0)
   {
    cout << "No DNA has been processed." << endl;
   }
}

// check and display the database
void displayDataBase()
{
    if(strDb.size() == 0) //check database vector
    {
        cout << "No database loaded." << endl;
    }
    else
    {
        cout << "Database loaded:" << endl;
    }

    parseString(1, strDb.size(), strDb);

    checkVectors();

    menuCall();
}
//open dna file and save to vector
void loadDna(string file)
{
    string data2;
    cout << "Loading DNA..." << endl;
    infile.open(file);
    
    if (!infile.is_open()) // open file and error check
    {
       // cout << endl << "Error: unable to open " << ' file '<< endl;
       cout << endl;
        std::cout << "Error: unable to open " << "\'" << file << "\'" << endl;
        menuCall();
    }
    
    while (!infile.eof()) // read dna file to dna vector
    {
        infile >> data2;
        if (infile.fail())
        {
            break;
        }

        strDna.push_back(data2);
    }

    /// personal use check // not needed
   /* if(infile.is_open() == true)
    {
        cout << "Loading DNA..." << endl; 
    }*/

    infile.close();
    menuCall();
}

//checks vector for database
void processCheck() 
{
    if(strDb.size() == 0)
    {
        cout << "No database loaded." << endl;
    }

    if(strDna.size() == 0)
    {
        cout << endl << "DNA not loaded." << endl;
    }
}
// parse dna search key and find quantity of each in string
void processDNA(string file)
{
    string search1, search2, search3;
    infile.open(file);

    cout << "Processing DNA..." << endl;
    processCheck();

    if(strDna.size() != 0)
    {
        parseString(0, 1, strDb);
    }

    if(strProcess.size() != 0) // dna process check
    {
        prcsCheck++;
       /* for(int i = 0; i < strProcess.size(); i++)
        {
            cout << strProcess.at(i); 
        }*/
        getline(infile, search1, ','); //failed attempt at storing variables
        getline(infile, search2, ',');
        cout << search1 << search2;
    }

    strProcess.clear();  //stops reload of vector
    menuCall();
}

//start menu/ user interaction
int menuCall() // takes commands from user and runs functions
{
    string command, file;

    cout << endl << "Enter command or # to exit: "; 
    cin >> command; 

    if(command != "#")
    {
        if(command == "l") // first command search // load_db
        {
            cin >> file;
            loadDb(file);
        }
        
        if(command == "d") // display command /// display
        {
            displayDataBase();
            //break;
        }

        if(command == "ld") // load_dna
        {
            cin >> file;
            loadDna(file);
        }
        if(command == "p") //process
        {
            processDNA(file);
        }
        if(command == "search")
        {
            cout << endl << "NOT IMPLEMENTED!" << endl;
        }
        else
        return 1;
    }
    return 1;
}

int main() 
{
    cout << "Welcome to the DNA Profiling Application." << endl;

    menuCall(); // call menu to run program

    return 0;
}
