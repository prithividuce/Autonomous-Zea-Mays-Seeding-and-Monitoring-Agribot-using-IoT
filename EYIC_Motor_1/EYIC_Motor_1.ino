/*
  *
  * Project Name:   Autonomous Zea Mays Seeding and Monitoring Agribot using IoT
  * Author List:    Sudharsanan J, Prithivi Rajan K. 
  *     
  * Filename:     EYIC_Motor_1.ino
  * Functions:    setup(), loop()
  * Global Variables: temp, upperThreshold, lowerThreshold.
  *     
  *
  */

 unsigned int temp = 0;
 const unsigned int upperThreshold = 600;
 const unsigned int lowerThreshold = 50;

/*
  *
  * Function Name:  setup
  * Input:    None
  * Output:   None
  * Logic:    Runs only once in Arduino
  * Example Call:   setup();
  *
  */

 void setup()
 {
   pinMode(8, OUTPUT);
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

 void loop(){
   temp=analogRead(A0);
   
    if(temp<lowerThreshold)
    {
     digitalWrite(8, HIGH);
    }
   
   else if(temp>upperThreshold)
   {
     digitalWrite(8, LOW);
   }
 }
