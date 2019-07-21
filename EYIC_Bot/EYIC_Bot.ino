

/*
  *
  * Project Name:   Autonomous Zea Mays Seeding and Monitoring Agribot using IoT
  * Author List:    Sudharsanan J, Prithivi Rajan K, Harish N, Manikandan A. 
  *     
  * Filename:     EYIC_Bot.ino
  * Functions:    Sharp_sensor_estimation(unsigned char), SharpRead(), sensorprint(), forward(), left(), right(), back(), stop1(), setup(), loop()
  * Global Variables: lcd,ser, f, b, r, l, flag,seedcount
  *     
  *
  */

#include <LiquidCrystal.h>
#include <Servo.h>
LiquidCrystal lcd(6,9,5,4,3,2); 
Servo ser;
int f,b,r,l,flg=0,seedcount=0;

//f refers the front sharp sensor value
//b refers the back sharp sensor value
//r refers the right sharp sensor value
//l refers the left sharp sensor value

/*
  *
  * Function Name:  Sharp_sensor_estimation
  * Input:    adc_reading
  * Output:     the exact distance in mm
  * Logic:    converts the adc_reading into distance and returns the didtance in mm
  * Example Call:   Sharp_sensor_estimation(300);
  *
  */
unsigned int Sharp_sensor_estimation(unsigned char adc_reading)
{
  float dist;  //temporary variable to find distance
  unsigned int distanceInt;  //actual distance is been stored
  dist = (int)(10.00*(2799.6*(1.00/(pow(adc_reading,1.1546)))));
  distanceInt = (int)dist;
  if(distanceInt>800)
  {
    distanceInt=800;
  }
  return distanceInt;
}


/*
  *
  * Function Name:  SharpRead()
  * Input:    None
  * Output:   None
  * Logic:    Reads the sensor values from sharp sensor
  * Example Call:   SharpRead();
  *
  */

void SharpRead()
{
  lcd.clear();
  b=analogRead(A0);
  l=analogRead(A1);
  f=analogRead(A2);
  r=analogRead(A3);
  b = map(b,0,1023,0,255);
  l = map(l,0,1023,0,255);
  f = map(f,0,1023,0,255);
  r = map(r,0,1023,0,255);
  b = Sharp_sensor_estimation(b);
  l = Sharp_sensor_estimation(l);
  f = Sharp_sensor_estimation(f);
  r = Sharp_sensor_estimation(r);
}


/*
  *
  * Function Name: sensorprint()
  * Input:    None
  * Output:   None
  * Logic:    Print the sharp sensor readings in lcd
  * Example Call:   sensorprint();
  *
  */

void sensorprint()
{
  lcd.setCursor(0,0);
  lcd.print(f);
  lcd.setCursor(12,0);
  lcd.print(b);
  lcd.setCursor(0,1);
  lcd.print(l);
  lcd.setCursor(12,1);
  lcd.print(r);
}


/*
  *
  * Function Name:  forward
  * Input:    None
  * Output:   None
  * Logic:    Moves the Agribot in forward direction
  * Example Call:   forward();
  *
  */

void forward()
{
 digitalWrite(41,HIGH);
 digitalWrite(45,LOW);
 digitalWrite(43,LOW);
 digitalWrite(39,HIGH);
}

/*
  *
  * Function Name:  left
  * Input:    None
  * Output:   None
  * Logic:    Moves the Agribot in left direction
  * Example Call:   left();
  *
  */

void left()
{
 digitalWrite(41,LOW);
 digitalWrite(45,HIGH);
 digitalWrite(43,LOW);
 digitalWrite(39,HIGH);
}

/*
  *
  * Function Name:  right
  * Input:    None
  * Output:   None
  * Logic:    Moves the Agribot in right direction
  * Example Call:   right();
  *
  */

void right()
{
 digitalWrite(41,HIGH);
 digitalWrite(45,LOW);
 digitalWrite(43,HIGH);
 digitalWrite(39,LOW);
}

/*
  *
  * Function Name:  back
  * Input:    None
  * Output:   None
  * Logic:    Moves the Agribot in back direction
  * Example Call:   back();
  *
  */

void back()
{
 digitalWrite(41,LOW);
 digitalWrite(45,HIGH);
 digitalWrite(43,HIGH);
 digitalWrite(39,LOW);
}

/*
  *
  * Function Name:  stop1
  * Input:    None
  * Output:   None
  * Logic:    stops the Agribot
  * Example Call:   stop1();
  *
  */

void stop1()
{
 digitalWrite(41,LOW);
 digitalWrite(45,LOW);
 digitalWrite(43,LOW);
 digitalWrite(39,LOW);
}

/*
  *
  * Function Name:  setup
  * Input:    None
  * Output:   None
  * Logic:    Runs only once in Arduino
  * Example Call:   setup();
  *
  */

void setup() {
  // put your setup code here, to run once:
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  pinMode(39,OUTPUT);
  pinMode(41,OUTPUT);
  pinMode(43,OUTPUT);
  pinMode(45,OUTPUT);
  ser.attach(12);
  lcd.begin(16,2);
  Serial.begin(9600);
  forward();
}

/*
  *
  * Function Name:  loop
  * Input:    None
  * Output:   None
  * Logic:    Runs repeatedly
  * Example Call:   loop();
  *
  */

void loop() {
  // put your main code here, to run repeatedly:
 SharpRead();
 sensorprint();
 if(f<180 && f>110)     //Detects the front sensor
 {
   delay(500);
   if(flg%2==0)
   {
     flg++;
     if(flg==3)
     {
        stop1();
        exit(1);
     }
     right();
     lcd.setCursor(4,0);
     lcd.print("right");
     delay(3000);
     while(1)
     { 
        SharpRead();
        if(l<180 && l>90)   //Turns while left sensor detect the boundry
        {
           break;
        }
        else
        {
         right();
        }
      }
      forward();
      delay(3500);
      right();
      lcd.setCursor(4,0);
      lcd.print("right");
      delay(3000);
      while(1)
      { 
         SharpRead();
         if(b<180 && b>110)
         {
            //exit(1);
            break;
         }
         else
         {
           right();
         }
      }
      forward();
      delay(1000);
    }
    
    
    else
    {
      flg++;
      if(flg==3)
      {
        stop1();
        exit(1);
      }
      left();
      lcd.setCursor(4,0);
      lcd.print("left");
      delay(3000);
      while(1)
      { 
         SharpRead();
         if(r<180 && r>120)     //Turns while right sensor detects the boundry
         {
            //exit(1);
            break;
         }
         else
         {
           left();
         }
      }
      forward();
      delay(3500);
      left();
      lcd.setCursor(4,0);
      lcd.print("left");
      delay(3000);
      while(1)
      { 
         SharpRead();
         if(b<180 && b>110)
         {
            //exit(1);
            break;
         }
         else
         {
           left();
         }
      }
      forward();
      delay(1000);
    }
 }
 else          // Sows the seed
 {
  stop1();
  ser.write(0);
  delay(200);
  ser.write(130);
  delay(200);
  ser.write(0);
  delay(1000);
  forward();
  delay(2000);
  seedcount++;
 }
 lcd.setCursor(4,0);
 lcd.print(seedcount);
 lcd.setCursor(4,1);
 lcd.print(flg);
 delay(300);
}
