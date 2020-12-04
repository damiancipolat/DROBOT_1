#include <SoftwareSerial.h>

//Bluetooth board.
struct boardBTH{
  int rx;
  int tx;
  SoftwareSerial serial=SoftwareSerial(0,1);
};

//Data type.
typedef struct boardBTH bth;

bth createBoard(int rx,int tx);
String getData(bth board);
