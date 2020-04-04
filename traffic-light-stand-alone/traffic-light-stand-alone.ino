
const int GREEN_IO_PIN = 13;
const int AMBER_IO_PIN = 12;
const int RED_IO_PIN = 11;


const int TOTAL_SEQUENCE_STEPS = 4;
const int SEQUENCE_STEP_RED = 0;
const int SEQUENCE_STEP_AMBER = 1;
const int SEQUENCE_STEP_GREEN = 2;
const int SEQUENCE_STEP_WAIT_TIME = 3;

struct SequenceStep {
        int Red;
        int Amber;
        int Green;
        int WaitTime;
        bool AdjustWaitTime;
};

// Each sequence step consists of <red light state>, <amber light state>, <green light state>, <state wait time in ms>
/*const int trafficLightSequence[TOTAL_SEQUENCE_STEPS][4] = 
                                  { { HIGH,   LOW,  LOW, 5000 },
                                  {   HIGH,   HIGH, LOW, 2000 },
                                  {   LOW,    LOW,  HIGH,5000 },
                                  {   LOW,    HIGH, LOW, 2000 } };*/

const SequenceStep trafficLightSequence[TOTAL_SEQUENCE_STEPS] = { { HIGH,  LOW,  LOW,  5000, true },
                                                                  { HIGH,  HIGH, LOW,  2000, false },
                                                                  { LOW,   LOW,  HIGH, 5000, true },
                                                                  { LOW,   HIGH, LOW,  2000, false } };                              

void setup()
{
  pinMode(RED_IO_PIN, OUTPUT);
  pinMode(AMBER_IO_PIN, OUTPUT);
  pinMode(GREEN_IO_PIN, OUTPUT);
}

void loop()
{
  static int currentStep = 0;
  
  if ( currentStep >= TOTAL_SEQUENCE_STEPS )
  {
    currentStep = 0;
  }
  
  digitalWrite(RED_IO_PIN, trafficLightSequence[currentStep].Red);
  digitalWrite(AMBER_IO_PIN, trafficLightSequence[currentStep].Amber);
  digitalWrite(GREEN_IO_PIN, trafficLightSequence[currentStep].Green);  

  float delayTime = trafficLightSequence[currentStep].WaitTime;

  if ( trafficLightSequence[currentStep].AdjustWaitTime )
  {
    // use value of analog input to adjust wait from minimum 1000ms to max 2x configured wait time + 1000ms
    float analogIn = analogRead(0);
    delayTime = ( (analogIn / 1023) * delayTime * 2) + 1000;
  }
  
  delay(delayTime);

  currentStep++;
} 
