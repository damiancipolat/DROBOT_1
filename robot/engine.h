//Engine representation.
struct engineType{
  int enPin,
  int in1,
  int in2
};

//Data type.
typedef struct robot_engine engineType;

//Speeds.
int forwardSpeed = 250;
int turnSpeed = 170;

//Methods.
robot_engine createEngine(int pwmPin,int in1, int in2);
void forward(robot_engine paramEngine);
void reverse(robot_engine paramEngine);
void pause(robot_engine paramEngine);
