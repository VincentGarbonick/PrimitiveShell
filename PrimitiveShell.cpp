#ifndef DEBUG
   //#define DEBUG
#endif

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
#include <algorithm> 
#include <wait.h>

#define DIVIDER "------------------------------------------\n"

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
void executeCommand(string, vector<string>, int, bool);
void helpScreen();

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

   // vector for firefox arguments, since it is a "unique" command
   vector<string> listVector;
   listVector.push_back("-l");

   switch (userCommand->commandName)
   {

   // error case 
   case 'Z':
      cout << "Unsupported command entered, enter \"H\" for help..." << endl;
      break;
   
   case 'H':

      helpScreen();

      break;
   
   case 'C':
      
      executeCommand("cp", userCommand->arguments, 2, 0);

      break;

   case 'D':

      executeCommand("rm", userCommand->arguments, 1, 0);

      break;

   case 'E':

      executeCommand("echo", userCommand->arguments, 1, 0);

      break;

   case 'L':

      executeCommand("ls", listVector, 1, 0);
      
      break;

   case 'M':

      // In this house, we use vim. Not nano.
      executeCommand("vim", userCommand->arguments, 1, 0);

      break;

   case 'P':

      executeCommand("cat", userCommand->arguments, 1, 0);

      break;

   case 'Q':
      
      RUNFLAG = 0;

      break;

   case 'S':

      executeCommand("firefox", userCommand->arguments, 0, 1);

      break;
   
   case 'W':

      executeCommand("clear", userCommand->arguments, 0, 0);

      break;

   default:
      cout << "Unsupported command entered, enter \"H\" for help..." << endl;
      break;
   }
}

// executes needed command with execvp()
// Input: Character pointer for command, vector for arguments, number of arguments expected, isBackground 1 = yes, 0 = no
// Output: Character pointer for arguments
void executeCommand(string command, vector<string> argumentVector, int expectedArguments, bool isBackground)
{
 


   /* 
   =========================================
   THIS BLOCK OF CODE CONSTRUCTS THE ARGUMENTS TO BE PASSED TO EXECVP
   =========================================
   */



   // c string arrays for passing arguments
   const char * cStringCommand = command.c_str();

   int errorCode = 0;

   // construct a character array pointer for arguments if we have arguments
   if(argumentVector.size() == expectedArguments)
   {
      // we need our argv to look like as follows 
      // argv[0] = commandName 
      // argv[1 - n-1] = arguments 
      // argv[n] = NULL 
      const char * argv[argumentVector.size() + 2];

      // copy vector to cstring array, if expected arguments are greater than 0
      if(expectedArguments > 0)
      {
         for(int i = 1; i < argumentVector.size() + 1; i++)
         {
            argv[i] = argumentVector[i - 1].c_str();

         }
      }

      // make sure our argv[0] has name of command
      argv[0] = command.c_str();
      argv[argumentVector.size() + 1] = NULL; // need to add this at very end 

      // fork out a child process to execute the execvp call
      pid_t pid = fork();

      if(pid < 0)
      {
         cout << "Fork failed catastrophically" << endl;
      }


      // child process
      if(pid == 0)
      {

         #if defined(DEBUG)
            if(isBackground == 0)
            {
               cout << "Child ID:" << getpid() << " Parent ID: " << getppid() << endl;
            }
         #endif

         // execute command in the fork
         errorCode = execvp(cStringCommand, const_cast<char * const *>(argv));

         if(errorCode = -1)
         {
            cout << "Invalid arguments" << endl; 
         }
         
         // in case execVP does not exit 
         kill(pid, SIGTERM); // *demonic voice* kill the child 

      }
      // otherwise this is the parent process 
      else 
      {

         int exitState;

         // wait on the child process to die so we can get back to work
         pid_t returnedPid;
         // only wait if the child is not a background process, if it's background, don't bother waiting
         if(isBackground == 0)
         {
            returnedPid = waitpid(pid, &exitState, 0);
            #if defined(DEBUG)
               cout << "returned exit state of " << returnedPid << " was " << exitState << endl;
               cout << "WIFEXITED: " << WIFEXITED(exitState) << " WEXITSTATUS: " << WEXITSTATUS(exitState) << endl;
            #endif
         }
      }
      
   }
   else 
   {
      cout << "Invalid number of arguments..." 
           << command << " requires " << expectedArguments << " arguments..." << endl; 
   }

   return;
}

// helpScreen() prints out a help screen for the user
// Inputs: None 
// Outputs: Help screen on console 
void helpScreen()
{
   cout << "\n" << "=================================================\n"
   << "This is a primitive shell application\n"
   << DIVIDER
   << "C source, destination: this copies a source file to a destination file\n"
   << DIVIDER
   << "D filename: this deletes the file of specified name\n"
   << DIVIDER
   << "E comment: this prints off the passed comment to the termina\n"
   << DIVIDER
   << "H: displays the help screen\n"
   << DIVIDER
   << "L: lists contents in directory\n"
   << DIVIDER
   << "M filename: creates a file of chosen name using vim\n"
   << DIVIDER
   << "P filename: prints the contents of the filename ot the screen\n"
   << DIVIDER
   << "Q: quits the shell\n"
   << DIVIDER
   << "S: launches firefox\n"
   << DIVIDER
   << "W: wipes the screen\n\n"
   << "Each command requires the specified number of arguments. More or less arguments\n"
   << "will cause the command to fail\n"
   << "=================================================" << endl;

   return;
}

/*
sources 
===========
https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.3.0/com.ibm.zos.v2r3.bpxbd00/rtgtc.htm

https://www.geeksforgeeks.org/split-a-sentence-into-words-in-cpp/
https://www.programiz.com/cpp-programming/library-function/cstring/strtok
https://stackoverflow.com/questions/3889992/how-does-strtok-split-the-string-into-tokens-in-c

https://stackoverflow.com/questions/28575643/using-execvp-in-c-to-copy-files-under-linux
https://www.google.com/search?q=execvp+manual&oq=execvp+manual&aqs=chrome..69i57j0i22i30l2.2768j0j7&sourceid=chrome&ie=UTF-8
https://stackoverflow.com/questions/347949/how-to-convert-a-stdstring-to-const-char-or-char

https://stackoverflow.com/questions/47068948/best-practice-to-use-execvp-in-c

https://codechacha.com/en/fork-waitpid-and-timeout/

ps -aux | grep kworker | wc -l
*/