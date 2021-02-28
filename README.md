## Primitive Shell 
### An innovative design by Vincent Garbonick 

Make sure to use some kind of markdown viewer in order to see the README formatted in a visually appeling way. 

## Compilation 
1. Navigate to the directory where PrimitiveShell is stored in your terminal of choice. 
2. Execute "g++ PrimitiveShell.cpp". This will create an output binary to run. This binary will be called "a.out".
3. Execute the command "ulimit -u && ./a.out". The ulimit -u limits the number of threads that can be produced, the && tells the shell to also execute a.out.

## Shell Use 
Simply enter one of the commands from the "Commands" section and press [enter]

## Shell Commands
* C *source*, *destination*: this copies a source file to a destination file
* D *filename*: this deletes the file of specified name
* E *comment*: this prints off the passed comment to the terminal
* H: displays the help screen
* L: lists contents in directory
* M *filename*: creates a file of chosen name using vim
* P *filename*: prints the contents of the filename to the screen
* Q: quits the shell
* S: launches firefox
* W: wipes the screen

## Sources and Acknowledgements
https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.3.0/com.ibm.zos.v2r3.bpxbd00/rtgtc.htm

https://www.geeksforgeeks.org/split-a-sentence-into-words-in-cpp/
https://www.programiz.com/cpp-programming/library-function/cstring/strtok
https://stackoverflow.com/questions/3889992/how-does-strtok-split-the-string-into-tokens-in-c

https://stackoverflow.com/questions/28575643/using-execvp-in-c-to-copy-files-under-linux
https://www.google.com/search?q=execvp+manual&oq=execvp+manual&aqs=chrome..69i57j0i22i30l2.2768j0j7&sourceid=chrome&ie=UTF-8
https://stackoverflow.com/questions/347949/how-to-convert-a-stdstring-to-const-char-or-char

https://stackoverflow.com/questions/47068948/best-practice-to-use-execvp-in-c

https://codechacha.com/en/fork-waitpid-and-timeout/

