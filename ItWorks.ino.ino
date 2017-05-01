/* Tester code for We Care Solar suitcases that tests for connectivity and reverse polarity.
   /home/pi/Desktop
*/

#include <stdio.h>
#include <SD.h>
#include <LiquidCrystal.h>
using namespace std;

//const char* PATH = "~/Desktop/test.csv";
const byte NUMTESTS = 32;
const byte OFFCONN = 6;
File myfile;
byte suitcaseNum = 0000;

byte badCount = 0;
byte reverseCount = 0;
// GPIO pins used
const byte DC1p = 23;        // DC Receptacle #1 positive
const byte DC1n = 25;       // DC Receptacle #1 negative
const byte DC2p = 27;      // DC Receptacle #2 positive
const byte DC2n = 29;       // DC Receptacle #2 negative
const byte DC3p = 31;       // DC Receptacle #3 positive
const byte DC3n = 33;        // DC Receptacle #3 negative
const byte DC4p = 35;       // DC Receptacle #4 positive
const byte DC4n = 37;        // DC Receptacle #4 negative
const byte Ep = 39;          // Expansion port positive
const byte En = 41;         // Expansion port negative
const byte Bp = 43;          // Battery positive
const byte Bn = 45;          // Battery negative
const byte Sp = 47;        // Solar Homerun Cable positive
const byte Sn = 49;         // Solar Homerun Cable negative
const byte CSp = 22;        // Charge Controller Solar positive
const byte CSn = 24;        // Charge Controller Solar negative
const byte CBp = 26;        // Charge Controller Battery positive
const byte CBn = 28;        // Charge Controller Battery negative
const byte CLp = 30;        // Charge Controller Load positive
const byte CLn = 32;        // Charge Controller Load negative
const byte SDLoc = 53;      // SD card for file writing

#define btnRIGHT 0
#define btnUP 1
#define btnDOWN 2
#define btnLEFT 3
#define btnSELECT 4
#define btnNONE 5

//set up lCD pins
LiquidCrystal lcd(8, 9, 10, 4, 5, 6, 7);

// Function prototypes
void checkConnections(String bad_connections[]);
void checkSwitchOff(String bad_connections[]);
void checkReversePolarity(String bad_connections[], String reverse_polarities[]);
byte contains(String error, String bad_connections[]);
void takeOut(String error, String bad_connections[]);
bool connected(byte pin_out, byte pin_in);
void displayResults(String bad_connections[], String reverse_polarities[]);
void writeResults(String bad_connections[], String reverse_polarities[]);
void showResults(String bad_connections[], String reverse_polarities[]);
byte read_LCD_buttons();
byte inputNum();

void test(int out, int in) {
  for (int i = 23; i < 49; i++) {
    digitalWrite(i, LOW);
  }
  for (int i = 0; i < 10; i++) {
    bool result = connected(out, in);
    Serial.println(result);
  }
}

void setup() {
  Serial.begin(9600);
  /*
      // TESTING
      // TEST 1: set pin to high or low - THIS WORKS, HIGH is 4.96V
      pinMode(48, OUTPUT);
      digitalWrite(48, LOW);

      // TEST 2A: set pin to high or low w/ 1 ohm resistor - THIS WORKS, HIGH is 4.96V
      // TEST 2B: 680 ohm resistor - THIS WORKS, HIGH is 4.64V
      pinMode(Bp, OUTPUT);
      digitalWrite(Bp, HIGH);

      // DOCUMENTATION states: HIGH (output) - 5; HIGH (input) - >3, LOW (output) - 0, LOW (input) - <1.5
      //test(CSp, CBp);

      test(Ep, En);*/


  // initializing bad_connections and reverse_polarities arrays
  String bad_connections[NUMTESTS];
  String reverse_polarities[NUMTESTS];
  /*
      // set up lcd and get suitcase number
      lcd.begin(16,2);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Hello World");
      delay(1000);
      //byte suitcaseNum = inputNum();

      // checks connections with switches on
      lcd.clear();
      lcd.print("Turn Switches On");
      delay(5000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Running Test...");
      delay(100);
      checkConnections(bad_connections);

      // checks connections with switches off
      lcd.clear();
      lcd.print("Turn Switches");
      lcd.setCursor(0,1);
      lcd.print("Off");
      delay(5000);
      lcd.clear();
      lcd.print("Running Test...");
      checkSwitchOff(bad_connections);

      // checks reverse polarity
      checkReversePolarity(bad_connections, reverse_polarities);

      // display results in two locations
      showResults(bad_connections, reverse_polarities); // lcd
      displayResults(bad_connections, reverse_polarities); // serial

      // File writing
      lcd.clear();
      lcd.print("Writing to file");
      SD.begin(4);
      myfile = SD.open("combo.txt", FILE_WRITE);
      writeResults(bad_connections, reverse_polarities);
      myfile.close();
  */
  // Just serial things
  checkConnections(bad_connections);
  Serial.println("Turn Switch Off");
  delay(5000);
  checkSwitchOff(bad_connections);
  checkReversePolarity(bad_connections, reverse_polarities);
  displayResults(bad_connections, reverse_polarities); // serial
  /*
      //Serial.println(connected(Bp, Bn));
      Serial.println("DC1p: ");
      test(CBp, DC1p);
      Serial.println("DC2p: ");
      test(CBp, DC2p);
      Serial.println("DC3p: ");
      test(CBp, DC3p);
      Serial.println("DC4p: ");
      test(CBp, DC4p);
      for (int i = 23; i < 49; i++){
        digitalWrite(i, LOW);
      }*/
}


void loop() {
  // DO NOT put any code in here
}

byte read_LCD_buttons() {              // read the buttons
  byte adc_key_in = analogRead(0);       // read the value from the sensor

  // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
  // we add approx 50 to those values and check to see if we are close
  // We make this the 1st option for speed reasons since it will be the most likely result

  if (adc_key_in > 1000) return btnNONE;

  // For V1.1 us this threshold
  if (adc_key_in < 50)   return btnRIGHT;
  if (adc_key_in < 250)  return btnUP;
  if (adc_key_in < 450)  return btnDOWN;
  if (adc_key_in < 650)  return btnLEFT;
  if (adc_key_in < 850)  return btnSELECT;
  return btnNONE;
}

byte inputNum() {
  lcd.setCursor(0, 0);
  lcd.print("Press right to enter suitcase number");
  byte lcd_key = -1;
  byte num = 0000;
  byte unit = 1;
  //wait for user to press right to begin entering suitcase number
  while (lcd_key != btnRIGHT) {
    lcd_key = read_LCD_buttons();  // read the buttons
    if (lcd_key == btnRIGHT) {
      lcd.print(num);
      break;
    }
  }

  lcd.setCursor(1, 4);
  lcd.print("Select to Finish");
  byte cursor = 3;
  lcd.setCursor(0, cursor);
  lcd.blink();
  lcd_key = -1;
  while (lcd_key != btnSELECT) {
    lcd_key = read_LCD_buttons();
    if (lcd_key == btnUP) { // increment number
      num = num + 1 * unit;
      if (num > 9999) {
        num = num - 1 * unit; //makes sure only 4 digits
      }
    } else if (lcd_key == btnDOWN && (num / unit > 0)) { // decrement number CHECK THIS FOR WHEN num > unit
      num = num - 1 * unit;
      if (num < unit && unit > 1) {
        unit = unit / 10;
      }
    } else if (lcd_key == btnLEFT && (unit < 1000)) { // move cursor left digit number
      unit = 10 * unit;
      if (cursor > 0) {
        cursor--;
      }
    } else if (lcd_key == btnRIGHT && (unit > 1)) { // move cursor right digit number
      unit = 10 / unit;
      if (cursor < 3) {
        cursor++;
      }
    }
    lcd.clear();
    lcd.setCursor(0, cursor);
    lcd.blink();
    lcd.print(num);
    delay(300);
  }
  return num;
}

void showResults(String bad_connections[], String reverse_polarities[]) {
  lcd.clear();
  lcd.print("RIGHT-see bad");
  lcd.setCursor(0, 1);
  lcd.print("DOWN to continue");

  byte lcd_key = -1;
  while (lcd_key != btnRIGHT && lcd_key != btnDOWN) {
    lcd_key = read_LCD_buttons();
  }
  if (lcd_key == btnRIGHT) {
    lcd.clear();
    lcd.print(String(badCount) + " results");
    delay(1000);
    displayConnections(bad_connections, badCount);
  }

  lcd.clear();
  lcd.print("RIGHT-see reverse");
  lcd.setCursor(0, 1);
  lcd.print("DOWN to continue");
  lcd_key = -1;
  while (lcd_key != btnRIGHT && lcd_key != btnDOWN) {
    lcd_key = read_LCD_buttons();
  }
  if (lcd_key == btnRIGHT) {
    displayConnections(reverse_polarities, reverseCount);
  }
}

void displayConnections(String curr_list[], int count) {
  lcd.clear();
  lcd.print("BAD_CONNECTIONS");
  delay(1000);
  lcd.clear();
  byte i = 0;
  byte lcd_key = -1;
  while (i < count) {
    delay(500);
    while (lcd_key != btnRIGHT && lcd_key != btnLEFT) {
      lcd_key = read_LCD_buttons();
    }
    if (lcd_key == btnRIGHT) {
      lcd.clear();
      lcd.print(curr_list[i]);
      i++;
      delay(100);
    } /*else if  (lcd_key == btnLEFT && i > 0){
            lcd.clear();
            i--;
            lcd.print(curr_list[i]);
            delay(100);
        } else if  (lcd_key == btnDOWN){
            delay(100);
            return;
        }*/
    lcd_key = -1;
  }
}

/* Function: checkConnections()
   This function checks all of the connections to see if they are connected or not,
   primarily through a subfunction called connected(pin_out, pin_in). If the two
   pobytes do not follow the expected connectivity, its error code will be added to
   the list bad_connections. This assumes the load switch is on.
*/
void checkConnections(String bad_connections[]) {
  String testNames[NUMTESTS] = {"2A", "2B", "2C", "2D", "2E.1", "2E.2", "2E.3", "2E.4", "2F",
                                "3A", "3B", "3C", "3D.1", "3D.2", "3D.3", "3D.4", "3E.1", "3E.2",
                                "3E.3", "3E.4", "3F", "4A", "4B", "4C", "4D", "4E", "4F",
                                "4G.1", "4G.2", "4G.3", "4G.4", "4H"
                               };

  // BEEP is 0
  // NO BEEP is 1
  byte pins[NUMTESTS][3] = { {Bn, CBn, 0}, {CSn, CBn, 0}, {CSn, CLn, 0}, {Sn, CLn, 0}, {CLn, DC1n, 0},
    {CLn, DC2n, 0}, {CLn, DC3n, 0}, {CLn, DC4n, 0}, {Bp, CBp, 0},
    //Start of 3
    {CSp, CBp, 1}, {CBp, CLp, 1}, {Sp, CSp, 0}, {CBp, DC1p, 1}, {CBp, DC2p, 1},
    {CBp, DC3p, 1}, {CBp, DC4p, 1}, {CLp, DC1p, 0}, {CLp, DC2p, 0},
    {CLp, DC3p, 0}, {CLp, DC4p, 0}, {CLp, Ep, 0},
    //Start of 4
    {Bn, Bp, 1}, {CSp, CSn, 1}, {Sp, Sn, 1}, {CSp, CBn, 1}, {CBn, CBp, 1}, {CLn, CLp, 1},
    {DC1n, CLp, 1}, {DC2n, CLp, 1}, {DC3n, CLp, 1}, {DC4n, CLp, 1}, {En, Ep, 1}
  };

  for (byte i = 0; i < NUMTESTS; i++) {
    if (connected(pins[i][0], pins[i][1]) == pins[i][2]) { // If they are equal, bad connection
      bad_connections[badCount] = testNames[i];
      Serial.println(testNames[i] + " FAILED TEST");
      badCount++;
    }
  }
}

void checkSwitchOff(String bad_connections[]) {
  String testNames[OFFCONN] = {"2F", "3C", "3E.1", "3E.2", "3E.3", "3E.4"};
  byte pins[OFFCONN][3] = { {CBp, Bp, 1}, {Sp, CSp, 1}, {CLp, DC1p, 1}, {CLp, DC2p, 1},
    {CLp, DC3p, 1}, {CLp, DC4p, 1}
  };

  for (byte i = 0; i < OFFCONN; i++) {
    if (connected(pins[i][0], pins[i][1]) == pins[i][2]) { // If equal, bad connection
      bad_connections[badCount] = testNames[i];
      Serial.println(testNames[i] + " FAILED OFF TEST");
      badCount++;
    }
  }
}

/* Function: checkReversePolarity(&bad_connections)
   @param: bad_connections - list of all bad connections, will be byteened
   if any of the bad connections are actually reverse polarity connections
   @return: a list of reverse polarity connections by their error code
*/
void checkReversePolarity(String bad_connections[], String reverse_polarities[]) {
  String all_errors[10] = {"2A", "2B", "2C", "2D", "2E.1", "2E.2", "2E.3", "2E.4", "2F", "3F"};
  byte tests[10][2] = { {Bp, CBn}, {CSp, CBn}, {CSp, CLn}, {Sp, CSn}, {DC1p, CLn}, {DC2p, CLn},
    {DC3p, CLn}, {DC4p, CLn}, {Bn, CBp}, {En, CLp}
  };

  for (byte i = 0; i < 10; i++) {
    //String error = all_errors[i];
    if (contains(all_errors[i], bad_connections) != NUMTESTS) {
      if (connected(tests[i][0], tests[i][1]) == 1) { // If there is a connection, there is RP
        reverse_polarities[reverseCount] = all_errors[i];
        reverseCount++;
        Serial.println("Trying to remove: " + all_errors[i]);
        takeOut(all_errors[i], bad_connections);
      }
    }
  }
}

// Contains method for array
byte contains(String error, String bad_connections[]) {
  char err[error.length() + 1];
  error.toCharArray(err, error.length() + 1);
  for (byte i = 0; i < badCount; i++) {
    String bad = bad_connections[i];
    char badC[bad.length() + 1];
    bad.toCharArray(badC, bad.length() + 1);
    if (strcmp(badC, err) == 0) {
      Serial.println("FOUND: " + bad + " Searching For: " + error + " On: " + i);
      return i;
    }
  }
  return NUMTESTS;
}

// removes element from array
void takeOut(String error, String bad_connections[]) {
  byte index = contains(error, bad_connections);
  Serial.println(bad_connections[index] + " REMOVING " + error);
  for (byte i = index; i < badCount - 1; i++) {
    bad_connections[i] = bad_connections[i + 1];
  }
  bad_connections[badCount - 1] = "";
  badCount--;
}

/* Function: connected(pin_out,pin_in)
   This function checks to see if the two pins are connected by setting
   one pin high and checking to see if the other pin also registers as high.
   @param: pin_out - one of the pins, will be set high
   @param: pin_in - one of the pins, will check to see if it receives high
   @return: Will return true if the two pins are connected and false
            if the two pins are not connected
*/
bool connected(byte pin_out, byte pin_in) {
  // set all pins to input and then write to low - disable internal pulldown
  for (int i = 23; i <= 49; i++) {
    pinMode(i, INPUT);
    digitalWrite(i, LOW);
  }
  
  pinMode(pin_in, INPUT);
  //digitalWrite(pin_in, LOW);
  pinMode(pin_out, OUTPUT);

  // set output pin to high and read input pin
  digitalWrite(pin_out, HIGH);
  delay(500);
  return digitalRead(pin_in);
}

void displayResults(String bad_connections[], String reverse_polarities[]) {
  Serial.println("--------------------------------RESULTS--------------------------------");
  Serial.print("Bad Connections: { ");
  for (int i = 0; i < badCount; i++) {
    Serial.print(bad_connections[i] + " ");
  }
  Serial.println("}");
  Serial.print("Reverse Connections: { ");
  for (int i = 0; i < reverseCount; i++) {
    Serial.print(reverse_polarities[i] + " ");
  }
  Serial.println("}");
}

/* websites: https://www.allaboutcircuits.com/projects/reading-and-writing-files-from-an-sd-card-with-an-arduino/
    https://www.arduino.cc/en/Reference/SD
    https://www.arduino.cc/en/tutorial/files
    https://www.amazon.com/Ethernet-Shield-Network-Expansion-Arduino/dp/B00AXVX5D0/ref=sr_1_2?ie=UTF8&qid=1489737925&sr=8-2&keywords=arduino+ethernet+shield
    https://www.amazon.com/SanDisk-MicroSD-TransFlash-Adapter-camcorder/dp/B000VOU91U/ref=sr_1_2?ie=UTF8&qid=1489737866&sr=8-2&keywords=sd+micro+card+2gb
*/
void writeResults(String bad_connections[], String reverse_polarities[]) {
  myfile.println("--------------------------------RESULTS--------------------------------");
  myfile.print("Bad Connections: { ");
  for (int i = 0; i < badCount; i++) {
    myfile.print(bad_connections[i] + " ");
  }
  myfile.println("}");
  myfile.print("Reverse Connections: { ");
  for (int i = 0; i < reverseCount; i++) {
    myfile.print(reverse_polarities[i] + " ");
  }
  myfile.println("}");
}
