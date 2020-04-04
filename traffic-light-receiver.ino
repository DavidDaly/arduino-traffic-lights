const int GREEN_IO_PIN = 13;
const int AMBER_IO_PIN = 12;
const int RED_IO_PIN = 11;

const int STX = 0x02;
const int ETX = 0x03;
const int MAX_MSG_LENGTH = 20;
 
void setup() {
  Serial.begin(9600); 
  pinMode(RED_IO_PIN, OUTPUT);
  pinMode(AMBER_IO_PIN, OUTPUT);
  pinMode(GREEN_IO_PIN, OUTPUT);
}
 
void loop() {

  static char  currentMessage[MAX_MSG_LENGTH] ;
  static int   currentMessagePos = 0;
  static bool  stxReceived = false;
  static int   data = 0;
  
  if (Serial.available() > 0)
  {
    data = Serial.read();
    
    if (data == STX)
    {
      stxReceived = true;
      currentMessagePos = 0;
    }
    else if ( (data == ETX) && stxReceived)
    {
      currentMessage[currentMessagePos] = 0;
      ProcessMessage(currentMessage);
      currentMessagePos = 0;
      stxReceived = false;
    }
    else
    {
      currentMessage[currentMessagePos] = data;
      currentMessagePos++;
    }

    if ( currentMessagePos >= MAX_MSG_LENGTH )
    {
      currentMessagePos = 0;
      stxReceived = false;
    }
    
  }
}

void ProcessMessage(char* message)
{

  /* Message format is RxAxGx where x is 0 to switch the light off
   * and 1 to switch it on. R stand for Red. A stands for Amber.  
   * G stands for Green.
   * 
   * Examples:
   *   R0A0G1 -> Green on, other lights off
   *   R1A1G0 -> Red and Amber on, Green of
   */

  // Red light
  if ( message[1] == '1' )
  {
    digitalWrite(RED_IO_PIN, HIGH);  
  }
  else if ( message[1] == '0' )
  {
    digitalWrite(RED_IO_PIN, LOW); 
  }

  // Amber light
  if ( message[3] == '1' )
  {
    digitalWrite(AMBER_IO_PIN, HIGH);  
  }
  else if ( message[3] == '0' )
  {
    digitalWrite(AMBER_IO_PIN, LOW); 
  }

  // Green light
  if ( message[5] == '1' )
  {
    digitalWrite(GREEN_IO_PIN, HIGH);  
  }
  else if ( message[5] == '0' )
  {
    digitalWrite(GREEN_IO_PIN, LOW); 
  }

}
