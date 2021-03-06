#include <Servo.h>

#define SERVO_PIN D8
#define SERVO_ORIGIN -90 //The position of the detector facing forward
#define SERVO_MAX 70
Servo servo;

/* Constantes pour les broches */
#define TRIGGER_PIN  D6 //TRIGGER
#define ECHO_PIN  D7   //ECHO
 
/* Constantes pour le timeout */
const unsigned long MEASURE_TIMEOUT = 25000UL; // 25ms = ~8m à 340m/s

/* Vitesse du son dans l'air en mm/us */
const float SOUND_SPEED = 340.0 / 1000;

const float Dist_MAX = 150.0; // At which distance (in mm) the car should stop. 
const float Dist_MIN = 1.0; //To avoid bugs



void initDetector()
{
  servo.attach(SERVO_PIN);
   
  /* Initialise les broches */
  pinMode(TRIGGER_PIN, OUTPUT);
  digitalWrite(TRIGGER_PIN, LOW); // La broche TRIGGER doit être à LOW au repos
  pinMode(ECHO_PIN, INPUT);
}

void turnDetector(int commandDirection)
{
  servo.write( - (commandDirection * SERVO_MAX) / 100 - SERVO_ORIGIN);
}

int getDistance()
{
  
  /* 1. Lance une mesure de distance en envoyant une impulsion HIGH de 10µs sur la broche TRIGGER */
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  
  /* 2. Mesure le temps entre l'envoi de l'impulsion ultrasonique et son écho (si il existe) */
  long measure = pulseIn(ECHO_PIN, HIGH, MEASURE_TIMEOUT);
   
  /* 3. Calcul la distance à partir du temps mesuré */
  float distance_mm = measure / 2.0 * SOUND_SPEED;
 
  return(distance_mm);
  
}
