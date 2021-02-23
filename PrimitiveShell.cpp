
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
   string commandName;   
   // vector of arguments
   vector<string> arguments;

   void printContents()
   {
      cout << commandName;

      for(int i = 0; i < arguments.size(); i++)
      {
         cout << arguments[i] << endl;
      }
   }
};

// function prototypes 
void printPrompt(void);
void parseInput(command *);



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

      // userCommand.printContents();
       

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
   commandPointer->commandName = " "; // clear out name 
   commandPointer->arguments.clear(); // clears out arguments 

    
   char userInput[256];
   cin.getline(userInput, 256);

   // split string into token sequence, populate command struct appropriately
   
   char * token; // token from strok
   char delimiter[]  = " "; // delimter for strok 
   
   token = strtok(userInput, delimiter);
   cout << token;
   //commandPointer->commandName = std::format("{}", token);

   while(token != NULL)
   {
      
      token = strtok(NULL, " ");      
      //commandPointer->arguments.push_back( std::format("{}", token)  );

   }

   return;
}

/*
sources 
===========
https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.3.0/com.ibm.zos.v2r3.bpxbd00/rtgtc.htm

https://www.geeksforgeeks.org/split-a-sentence-into-words-in-cpp/
https://www.programiz.com/cpp-programming/library-function/cstring/strtok
https://stackoverflow.com/questions/3889992/how-does-strtok-split-the-string-into-tokens-in-c
*/