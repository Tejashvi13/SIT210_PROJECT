const int sensor_pin = A4;	/* Soil moisture sensor O/P pin */
int led1 = D6;
int led2 = D5;
int led3 = D4;
int led4 = D3;
int led5 = D2;


bool shouldNotify = true;


void setup() 
{
  Serial.begin(9600);	/* Define baud rate for serial communication */
  
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  
  Particle.function("led",ledToggle);
  
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
}

void loop() 
{
  float moisture_percentage;
  int sensor_analog;
  sensor_analog = analogRead(sensor_pin);
  moisture_percentage = (100 - ( (sensor_analog/4095.00) * 100 ) );
  Serial.print("Moisture Percentage = ");
  
  String moisture = String (moisture_percentage); 
  

  
  if (moisture_percentage < 65 )
    {
        Particle.publish("LowMoisture", moisture, PRIVATE);
        Particle.publish("LowMoisture", "Moisture", PRIVATE);
    }

  
  
  
  Serial.print(moisture_percentage);
  Serial.print("%\n\n");
  
  
  Particle.publish("moisture_percentage", moisture , PRIVATE);
  
  delay(30000);
}

int ledToggle(String command) {
    /* Particle.functions always take a string as an argument and return an integer.
    Since we can pass a string, it means that we can give the program commands on how the function should be used.
    In this case, telling the function "on" will turn the LED on and telling it "off" will turn the LED off.
    Then, the function returns a value to us to let us know what happened.
    In this case, it will return 1 for the LEDs turning on, 0 for the LEDs turning off,
    and -1 if we received a totally bogus command that didn't do anything to the LEDs.
    */

    if (command=="All on") 
    {
        digitalWrite(led1,HIGH);
        digitalWrite(led2,HIGH);
        digitalWrite(led3,HIGH);
        digitalWrite(led4, HIGH);
        digitalWrite(led5, HIGH);
    }
    else if (command=="All off") 
    {
        digitalWrite(led1,LOW);
        digitalWrite(led2,LOW);
        digitalWrite(led3,LOW);
        digitalWrite(led4, LOW);
        digitalWrite(led5, LOW);
    }
    else 
    {
        return -1;
    }
}




