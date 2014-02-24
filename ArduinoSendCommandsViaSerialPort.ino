/*
Awaiting text commands via serial port #1 - digital pins 0 (RX1), 1 (TX1)
Max command length - 64 chars
Command ends with "new-line" char
Diagnostics messages are sent back to serial port #1

This code is in the public domain.
Copyright © 2014, foreglance.com
*/
//--- constants ---
const int SerialPortBaudRate = 9600;
const int MaxCommandLength = 64;
const char LF = '\n';
const String EmptyString = "";

//--- fields ---
String command = EmptyString;
int commandLength = 0;
char inputChar;
boolean awaitingCommand = true;

//--- setup ---
void setup() {
  command.reserve(MaxCommandLength);
  initSerialPort1();
  awaitCommand();
}

//--- main loop ---
void loop() {
  processCommand();
  readSerialData();
}

//--- commands ---
void commandStart(){
  Serial1.println("Start");
}

void commandStop(){
  Serial1.println("Stop");
}

//--- methods ---

//invoke command methods
void processCommand(){
  if(awaitingCommand)
    return;
    
  if(command == "start")
    commandStart();
  else if(command == "stop")
    commandStop();
  else
    Serial1.println("Unknown command:" + command);

  awaitCommand();
}

//initialize the serial port #1
void initSerialPort1(){
  Serial1.begin(SerialPortBaudRate);
  while(!Serial1){}//wait while the serial port is ready
}

//request for a new command
void awaitCommand(){
  command = EmptyString;
  commandLength = 0;
  awaitingCommand = true;
}

//read data for the buffer of the serial port #1
void readSerialData() {
  //when command is not awaited 
  // and data do not exist in the buffer of the serial port
  if(!awaitingCommand || !Serial1.available()) 
    return; // do not read data
    
  // take a char from the buffer
  inputChar = (char)Serial1.read(); 

  //if taken char is "new-line" 
  // and no other data were taken earlier
  if(LF == inputChar && 0 == commandLength)
    return; // do not change the command text

  commandLength++; // length of the command text with taken char

  //if taken char is not "new-line"
  // and the command text with this char not longer tham Max 
  if(LF != inputChar && MaxCommandLength > commandLength)
    command += inputChar; //add this char to the command text
  else
    awaitingCommand = false; //define the command as received
}

