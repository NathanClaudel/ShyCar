#define IN1 D1
#define IN2 D2
#define ENA D0
#define ENB D5
#define IN3 D3
#define IN4 D4

#define MULTIPLICATOR 5

//Angle of movement relative to the body
static int currentDirection;

void initMovement()
{
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);  
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
}

// Speed goes between -100 and 100
void setRightSpeed(signed char speed)
{
  int speedc = speed * MULTIPLICATOR;
  //Serial.println(speedc);
  if (speedc > 0)
  {
    analogWrite(ENA, speedc);// motor speed 
    digitalWrite(IN1,LOW);// rotate forward
    digitalWrite(IN2,HIGH); 
  } 
  else 
  {
    analogWrite(ENA, -speedc);// motor speed 
    digitalWrite(IN1,HIGH);// rotate backwards
    digitalWrite(IN2,LOW); 
  }
}

void setLeftSpeed(signed char speed)
{
  int speedc = speed * MULTIPLICATOR;
  if (speedc > 0) 
  {
    analogWrite(ENB, speedc);// motor speed
    digitalWrite(IN3,HIGH);// rotate forward
    digitalWrite(IN4,LOW);
  } 
  else 
  {
    analogWrite(ENB, -speedc);// motor speed
    digitalWrite(IN3,LOW);// rotate forward
    digitalWrite(IN4,HIGH);
  }
}

void setMovement(signed char speed, signed char direction)
{
  //turn left
  if(direction < 0)
  {
    setRightSpeed(speed);
    setLeftSpeed((speed * (100 + direction))/100);
  }
  else
  {
    setLeftSpeed(speed);
    setRightSpeed((speed * (100 - direction))/100);
  }

  currentDirection = direction;
}

void turnAround(signed char speed, signed char direction)
{
  setRightSpeed(direction < 0 ? speed : - speed);
  setLeftSpeed(direction < 0 ? - speed : speed);
}

int movementDirection()
{
  return currentDirection;
}
