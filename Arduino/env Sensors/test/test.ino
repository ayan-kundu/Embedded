#include <SoftwareSerial.h>
//#include <ModbusMaster.h>

// Define the pins for RS485 communication
#define RX 2
#define TX 3
// enable pins 
#define RE 7
#define DE 8
 
// Request frame for the soil sensor
const byte soilSensorRequest[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x02, 0xC4, 0x0B};
byte soilSensorResponse[9];
SoftwareSerial modbus(RX, TX); // Software serial for RS485 communication
 
void setup()
{
  Serial.begin(9600); // Initialize serial communication for debugging
  modbus.begin(4800); // Initialize software serial communication at 4800 baud rate
  pinMode(RE, OUTPUT); // Set RE pin as output
  pinMode(DE, OUTPUT); // Set DE pin as output

}
 
 
void loop()
{
  /*Start the transmission mode for RS485 */
  digitalWrite(DE, HIGH);
  digitalWrite(RE, HIGH);delay(10);
 
  // Send the request frame to the soil sensor
  modbus.write(soilSensorRequest, sizeof(soilSensorRequest));
 
  /*End the transmission mode and set to receive mode for RS485*/
  digitalWrite(DE, LOW);
  digitalWrite(RE, LOW);
  delay(10);

  // Wait for the response from the sensor or timeout after 1 second
  unsigned long startTime = millis();
  while (modbus.available() < 9 && millis() - startTime < 1000)
  {
    delay(1); // help continue the loop 
  }
  Serial.println("Waited 1 sec for response");
  if (modbus.available() >= 9) // If valid response received
  {
    //byte response[5]
    //modbus.readBytes(response,5)  ///////////////////////////////////
    // Read the response from the sensor
    byte index = 0;
    while (modbus.available() && index < 9)
    {
      soilSensorResponse[index] = modbus.read();
      Serial.print(soilSensorResponse[index], HEX); // Print the received byte in HEX format
      Serial.print(" ");
      index++;
    }
    Serial.println("Soil sensor Response Read");
 
    /* Parse and calculate the Moisture value */
    int Moisture_Int = int(soilSensorResponse[3] << 8 | soilSensorResponse[4]);
    float Moisture_Percent = Moisture_Int / 10.0;
 
    Serial.print("Moisture: ");
    Serial.print(Moisture_Percent);
    Serial.println(" %RH");
 
 

    /* Parse and calculate the Temperature value */
    int Temperature_Int = int(soilSensorResponse[5] << 8 | soilSensorResponse[6]);
    float Temperature_Celsius = Temperature_Int / 10.0;
 
    // Check if temperature is negative and convert accordingly
    if (Temperature_Int > 0x7FFF)
    {
      Temperature_Celsius = 0x10000 - Temperature_Int;
      Temperature_Celsius = -Temperature_Celsius / 10.0;
    }
 
    Serial.print("Temperature: ");
    Serial.print(Temperature_Celsius);
    Serial.println(" °C");
  }

  delay(1000); // Wait for a second before the next loop iteration
}