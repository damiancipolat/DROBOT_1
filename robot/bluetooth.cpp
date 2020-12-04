#include <SoftwareSerial.h>
#include "bluetooth.h"

bth createBoard(int rx,int tx){

  //Define vaiables.
  bth newBoard;
  newBoard.rx=rx;
  newBoard.tx=tx;
  
  //Start serial.
  newBoard.serial=SoftwareSerial(rx,tx);  
  newBoard.serial.begin(38400);

  return newBoard; 
}

//Read value from a board.
String getData(bth board){

  if (board.serial.available())
    return board.serial.readString();
  else
    return "";

}
