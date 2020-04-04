
const int GREEN_IO_PIN = 13;
const int AMBER_IO_PIN = 12;
const int RED_IO_PIN = 11;

const int TOTAL_SEQUENCE_STEPS = 8;
const int SEQUENCE_STEP_RED = 0;
const int SEQUENCE_STEP_AMBER = 1;
const int SEQUENCE_STEP_GREEN = 2;
const int SEQUENCE_STEP_WAIT_TIME = 3;

const int STX = 0x02;
const int ETX = 0x03;

struct SequenceStep {
        int Red;
        int Amber;
        int Green;
        int WaitTime;
        bool AdjustWaitTime;
        String TransmitMessage;
};


const SequenceStep trafficLightSequence[TOTAL_SEQUENCE_STEPS] = { { HIGH,  LOW,  LOW,  5000, true,  "R0A0G1" },
                                                                  { HIGH,  LOW,  LOW,  1500, false, "R0A1G0" },
                                                                  { HIGH,  LOW,  LOW,  500,  false, "R1A0G0" },
                                                                  { HIGH,  HIGH, LOW,  1500, false, "R1A0G0" },
                                                                  { LOW,   LOW,  HIGH, 5000, true,  "R1A0G0" },
                                                                  { LOW,   HIGH, LOW,  1500, false, "R1A0G0" },
                                                                  { HIGH,  LOW,  LOW,  500,  false, "R1A0G0" }, 
                                                                  { HIGH,  LOW,  LOW,  1500, false, "R1A1G0" } };                              

void setup()
{
  pinMode(RED_IO_PIN, OUTPUT);
  pinMode(AMBER_IO_PIN, OUTPUT);
  pinMode(GREEN_IO_PIN, OUTPUT);

  Serial.begin(9600); 
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

  Serial.write(STX);
  Serial.write(trafficLightSequence[currentStep].TransmitMessage.c_str());
  Serial.write(ETX);

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
