char commandSpeed;
signed char commandDirection;

bool avoiding = false;

void setup() 
{
  // Initialise Serial connection
  Serial.begin(115200);
  
  initMovement();
  initDetector();
  initConnection();

  delay(1000);

  initLeds();

  lightGreen();
}

void loop() 
{
  // Receiving the packet
  signed char *code = receivePacket();
  commandSpeed = code[0];
  commandDirection = code[1];

  // Detector moving towards the direction of movement
  turnDetector(commandDirection);

  delay(10);

  // Obstacle detection
  int distance = getDistance();
  handleDistance(distance);

  // Updating movement
  setMovement(commandSpeed, commandDirection);
}

void handleDistance(int distance)
{
  if(distance < 300 && distance > 1)
  {
    lightRed();
    sendAvoiding(true);
    
    if(commandDirection > 0)
    {
      commandDirection = -100;
    }
    else
    {
      commandDirection = 100;
    }
    
    if(distance < 150)
    {
      turnAround(commandSpeed, commandDirection);
      delay(500);
    }
  }
  else
  {
    lightGreen();
    sendAvoiding(false);
  }
}
