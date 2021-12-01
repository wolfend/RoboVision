//pins used*******************************************************
const short PIN_PWM1 = 7;
const short PIN_PWM2 = 8;
const short PIN_Direction1 = 9;
const short PIN_Direction2 = 10;
const short PIN_Sonar = 1;
const short PIN_LEDred = 11;
const short PIN_LEDgreen = 12;
const short PIN_LEDblue = 6;
const short PIN_IRrcvr = 5;
const short PIN_SYSMODE = 3;

PIDLoop headingLoopSlow(10,0,2);
PIDLoop headingLoopMove(100, 0, 20);
PIDLoop headingLoopFast(400,0, 100);
HUSKYLENS huskylens;
void printResult(HUSKYLENSResult result);
int ID1 = 1;
SemaphoreHandle_t xSerialSemaphore;  //semaphore to manage serial port


enum driveStates {
  Paused,
  Forward,
  ForwardTracking,
  Reverse,
  SearchRight,
  SearchLeft
};
enum turnStates {
  Left,
  Straight,
  Right
};
enum visionModes {
  objectTracking,
  lineFollowing
};
//++++++++++++++++++++++++++++++++ Defines
#define MIN_SONARdistance 2
#define SLOW_SPEED       50
#define MOVE_SPEED       80
#define FAST_SPEED       130
#define SEARCH_SPEED     40
#define TURN_SPEED_DELTA  2
#define TURN_TIME         80
#define SAFE_DIST         60
#define WARNDIST1         40
#define WARNDIST2         20
#define DECODE_SONY

// ************************All global variables belong to one structure - global:
struct global
{
enum driveStates driveState;
enum turnStates turnState;
enum visionModes visionModeNew;
enum visionModes visionModeCurrent;
bool inTrack;
int sonarDistance = 0;
int IRKeypress = -1;
int32_t error;
int leftSpeed = 0;                                
int rightSpeed = 0;
int currentSpeed;
bool LEDred;
bool LEDgreen;
bool LEDblue;
};

struct global g;
