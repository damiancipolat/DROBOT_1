//Engine representation.
struct ledType{
  int pin;
};

//Data type.
typedef struct ledType led;

//Methods.
led createLigth(int pin);
void turnOn(led tmpLed);
void turnOff(led tmpLed);
