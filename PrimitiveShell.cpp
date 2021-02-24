
// include that sweet, sweet POSIX library
#include <unistd.h>

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <cstring>

// namespace delcarations 
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::strtok;

// global variable for main while loop running
bool RUNFLAG = 1;

// custom datatype for storing commands 
struct command 
{
   // name of the command we parse 
   char commandName;   
   // vector of arguments
   vector<string> arguments;

   void printContents()
   {
      cout << "Name: " << commandName << endl;

      for(int i = 0; i < arguments.size(); i++)
      {
         cout << "Argument " << i <<  " " << arguments[i] << endl;
      }
   }
};

// function prototypes 
void printPrompt(void);
void parseInput(command *);
void commandLookup(command *);


// main driver loop
int main(void)
{

   command userCommand;
   command * p_userCommand = &userCommand; // pointer to our struct 

   // main loop of the terminal 
   while(RUNFLAG)
   {      
      printPrompt();
      
      parseInput(p_userCommand);

      //userCommand.printContents();
       
      commandLookup(p_userCommand);
      
   }

   return 0;
}

// printPrompt: prints prompt in form of ~[ID]/CWD$
// Input: None
// Output: None 
void printPrompt(void)
{
   char * buffer;
   buffer = new char[256];
   
   // get the current working directory and store in character array
   getcwd(buffer, 256);

   // print our terminal greeting, c style 
   printf("vrg6@primitiveShell%s$ ", buffer);

   return;
}

// parseInput: User inputs data, and then that data is parsed by this function
// the first value is the command, and subsequent values are arguments put onto the vector
// Input: Pointer to a command struct 
// Output: populated command struct 
void parseInput(command * commandPointer)
{
   // clear our struct before inputting new data 
   commandPointer->commandName = ' '; // clear out name 
   commandPointer->arguments.clear(); // clears out arguments 

    
   char userInput[256];
   cin.getline(userInput, 256);

   // split string into token sequence, populate command struct appropriately
   
   char * token; // token from strok
   char delimiter[]  = " "; // delimter for strok 
   
   token = strtok(userInput, delimiter);

   // commandPointer->commandName = (token[0]);
   // check to make sure user input's first part is a character.. if not, replace command with "Z" for error
   if(string(token).length() > 1)
   {
      commandPointer->commandName = 'Z';
   }
   else 
   {
      commandPointer->commandName = token[0];
   }

   while(token != NULL)
   {
      
      token = strtok(NULL, " ");      
      
      // make sure there is something in token to push_back
      if(token)
      {
         commandPointer->arguments.push_back(string(token));
      }

   }

   return;
}

// commandLookup uses a large switch-case construct to find the supported commands
// unsupported commands default to an error
// unsupported arguments are caught in a try-catch block and output error
// Input: pointer to command struct
// Output: 
void commandLookup(command * userCommand)
{
   switch (userCommand->commandName)
   {

   // error case 
   case 'Z':
      cout << "Unsupported command entered, enter \"H\" for help..." << endl;
      break;
   
   case 'H':
      cout << "Help" << endl;
      break;
   
   case 'C':
      cout << "Copy" << endl;
      break;

   case 'D':
      cout << "Delete File" << endl;
      break;

   case 'E':
      cout << "Echo" << endl;
      break;

   case 'L':
      cout << "List" << endl;
      break;

   case 'M':
      cout << "Make" << endl;
      break;

   case 'P':
      cout << "Print" << endl;
      break;

   case 'Q':
      cout << "Quit" << endl;
      break;

   case 'S':
      cout << "Surf" << endl;
      break;
   
   case 'W':
      cout << "Wipe" << endl;
      break;

   default:
      cout << "Unsupported command entered, enter \"H\" for help..." << endl;
      break;
   }
}

/*
sources 
===========
https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.3.0/com.ibm.zos.v2r3.bpxbd00/rtgtc.htm

https://www.geeksforgeeks.org/split-a-sentence-into-words-in-cpp/
https://www.programiz.com/cpp-programming/library-function/cstring/strtok
https://stackoverflow.com/questions/3889992/how-does-strtok-split-the-string-into-tokens-in-c
*/