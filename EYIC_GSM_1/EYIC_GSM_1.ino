/*
  *
  * Project Name:   Autonomous Zea Mays Seeding and Monitoring Agribot using IoT
  * Author List:    Sudharsanan J, Manikandan A. 
  *     
  * Filename:     EYIC_GSM_1.ino
  * Functions:    read_data(), upload(char up[50]), ShowSerialData(), setup(), loop()
  * Global Variables: lcd,DHT,SIM900,tm,hum,moist,ph,moist_str1,ph_str1,hum_str1,temp_str1,rs,en,d4,d5,d6,d7
  *     
  *
  */

#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <dht.h>
#include <stdlib.h>
dht DHT;
/* Create object named SIM900 of the class SoftwareSerial */
SoftwareSerial SIM900(7, 6);
float tem,hum,moist,ph;
char  moist_str1[15]="field1=",ph_str1="field2=",hum_str1[15]="field4=",temp_str1[15]="field3=";
const int rs = 5, en = 13, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

/*
  *
  * Function Name:  read_data()
  * Input:    None
  * Output:   None
  * Logic:    Reads Data from moisture, temperature, Humidity and pH sensor and converts into string and displays in lcd.
  * Example Call:   read_data();
  *
  */

void read_data()
{
  char moist_str[10],hum_str[10],temp_str[10],ph_str[10];
  strcpy(moist_str1,"field1=");
  strcpy(ph_str1,"field2=");
  strcpy(hum_str1,"field4=");
  strcpy(temp_str1,"field3=");
  moist = analogRead(A1);
  DHT.read11(A2);
  ph=analogRead(A0);;
  moist = map(moist,1024,200,0,100);
  tem=DHT.temperature;
  hum=DHT.humidity;
  itoa(int(moist),moist_str,10);
  itoa(int(hum),hum_str,10);
  itoa(int(tem),temp_str,10);
  itoa(ph,ph_str,10);
  strcat(moist_str1,moist_str);
  strcat(ph_str1,ph_str);
  strcat(hum_str1,hum_str);
  strcat(temp_str1,temp_str);
  lcd.setCursor(0,0);
  lcd.print("MOIST ");
  lcd.setCursor(6,0);
  lcd.print(int(moist));
  lcd.setCursor(9,0);
  lcd.print("HUM ");
  lcd.setCursor(13,0);
  lcd.print(int(hum));
  lcd.setCursor(0,1);
  lcd.print("TEMP ");
  lcd.setCursor(5,1);
  lcd.print(int(tem));
  lcd.setCursor(8,1);
  lcd.print("pH ");
  lcd.setCursor(11,1);
  lcd.print(ph);
  if(int(moist)<40)    //Transmits data through RF module
  {
    digitalWrite(2,LOW);
    digitalWrite(12,HIGH);
  }
  if(int(moist)>60)
  {
    digitalWrite(2,HIGH);
    digitalWrite(12,LOW);
  }
}

/*
  *
  * Function Name:  upload
  * Input:    char up[50]
  * Output:   None
  * Logic:    Uploads the URL refered as up into the cloud using GSM module
  * Example Call:   upload("Https:............eyic.com");
  *
  */

void upload(char up[50])
{
  char api_key[50]="api_key=RN0OKHSSMTZMYSPF&";
  strcat(api_key,up);
  Serial.println(api_key);
  Serial.println();
  Serial.println("AT+HTTPINIT\\r\\n");
  SIM900.println("AT+HTTPINIT");  /* Initialize HTTP service */
  delay(5000); 
  ShowSerialData();
  delay(5000);
  Serial.println("AT+HTTPPARA=\"CID\",1\\r\\n");
  SIM900.println("AT+HTTPPARA=\"CID\",1");  /* Set parameters for HTTP session */
  delay(5000);
  ShowSerialData();
  delay(5000);
  Serial.println("AT+HTTPPARA=\"URL\",\"api.thingspeak.com/update\"\\r\\n");
  SIM900.println("AT+HTTPPARA=\"URL\",\"api.thingspeak.com/update\"");  /* Set parameters for HTTP session */
  delay(5000);
  ShowSerialData();
  delay(5000);
  Serial.println("AT+HTTPDATA=36,20000\\r\\n");
  SIM900.println("AT+HTTPDATA=36,20000"); /* POST data of size 33 Bytes with maximum latency time of 10seconds for inputting the data*/ 
  delay(5000);
  ShowSerialData();
  delay(5000);
  Serial.println(api_key);  /* Data to be sent */
  SIM900.println(api_key);
  delay(5000);
  ShowSerialData();
  delay(5000);
  Serial.println("AT+HTTPACTION=1\\r\\n");
  SIM900.println("AT+HTTPACTION=1");  /* Start POST session */
  delay(5000);
  ShowSerialData();
  delay(5000);
  Serial.println("AT+HTTPTERM\\r\\n");  
  SIM900.println("AT+HTTPTERM");  /* Terminate HTTP service */
  delay(5000);
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
  SIM900.begin(9600);  /* Define baud rate for software serial communication */
  Serial.begin(9600); /* Define baud rate for serial communication */
  // with the arduino pin number it is connected to
  lcd.begin(16,2);
  pinMode(2,OUTPUT);
  pinMode(12,OUTPUT);
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
  read_data();
  Serial.println("HTTP post method :");
  Serial.println("AT\\r\\n");
  SIM900.println("AT"); /* Check Communication */
  delay(5000);
  ShowSerialData(); /* Print response on the serial monitor */
  delay(5000);
  /* Configure bearer profile 1 */
  Serial.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"\\r\\n");
  SIM900.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");  /* Connection type GPRS */
  delay(5000);
  ShowSerialData();
  delay(5000);
  Serial.println("AT+SAPBR=3,1,\"APN\",\"\"\\r\\n");
  SIM900.println("AT+SAPBR=3,1,\"APN\",\"\"");  /* APN of the provider */
  delay(5000);
  ShowSerialData();
  delay(5000);
  Serial.println("AT+SAPBR=1,1\\r\\n");
  SIM900.println("AT+SAPBR=1,1"); /* Open GPRS context */
  delay(5000);
  ShowSerialData();
  delay(5000);
  Serial.println("AT+SAPBR=2,1\\r\\n");
  SIM900.println("AT+SAPBR=2,1"); /* Query the GPRS context */
  delay(5000);
  ShowSerialData();
  delay(5000);
  upload(moist_str1);
  upload(ph_str1);
  upload(temp_str1);
  upload(hum_str1);
  delay(5000);
  Serial.println("AT+SAPBR=0,1\\r\\n");
  SIM900.println("AT+SAPBR=0,1"); /* Close GPRS context */
  delay(5000);
  ShowSerialData();
  delay(5000);
  delay(900000UL);
}

void ShowSerialData()
{
  while(SIM900.available()!=0)  /* If data is available on serial port */
  Serial.write(char (SIM900.read())); /* Print character received on to the serial monitor */
}
