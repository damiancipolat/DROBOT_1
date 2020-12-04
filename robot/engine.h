//Engine representation.
struct engineType{
  int enPin;
  int in1;
  int in2;
};

//Data type.
typedef struct engineType engine;

//Methods.
engine createEngine(int pwmPin,int in1, int in2);
void forward(engine paramEngine);
void reverse(engine paramEngine);
void pause(engine paramEngine);
