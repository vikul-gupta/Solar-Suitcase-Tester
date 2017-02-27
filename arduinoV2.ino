/* Tester code for We Care Solar suitcases that tests for connectivity and reverse polarity.
 * /home/pi/Desktop
 */

#include <stdio.h>
using namespace std;

//const char* PATH = "~/Desktop/test.csv";
const byte NUMTESTS = 32;
const byte OFFCONN = 6;
//String bad_connections[NUMTESTS];
//String reverse_polarities[NUMTESTS];
byte badCount = 0;
byte reverseCount = 0;
// GPIO pins used
const byte DC1p = 22;        // DC Receptacle #1 positive
const byte DC1n = 23;       // DC Receptacle #1 negative
const byte DC2p = 24;      // DC Receptacle #2 positive
const byte DC2n = 25;       // DC Receptacle #2 negative
const byte DC3p = 26;       // DC Receptacle #3 positive
const byte DC3n = 27;        // DC Receptacle #3 negative
const byte DC4p = 28;       // DC Receptacle #4 positive
const byte DC4n = 29;        // DC Receptacle #4 negative
const byte Ep = 30;          // Expansion port positive
const byte En = 31;         // Expansion port negative
const byte Bp = 32;          // Battery positive
const byte Bn = 33;          // Battery negative
const byte Sp = 34;        // Solar Homerun Cable positive
const byte Sn = 35;         // Solar Homerun Cable negative
const byte CSp = 38;        // Charge Controller Solar positive
const byte CSn = 39;        // Charge Controller Solar negative
const byte CBp = 40;        // Charge Controller Battery positive
const byte CBn = 41;        // Charge Controller Battery negative
const byte CLp = 42;        // Charge Controller Load positive
const byte CLn = 43;        // Charge Controller Load negative

// Function prototypes
void checkConnections(String bad_connections[]);
void checkSwitchOff(String bad_connections[]);
void checkReversePolarity(String bad_connections[], String reverse_polarities[]);
byte contains(String error, String bad_connections[]);
void takeOut(String error, String bad_connections[]);
bool connected(byte pin_out, byte pin_in);
String arrToStr(String bad_connections[], String reverse_polarities[]);

void setup() {
  // put your setup code here, to run once
    Serial.begin(38400);

    String bad_connections[NUMTESTS];
    String reverse_polarities[NUMTESTS];
    
    checkConnections(bad_connections);
    Serial.println("Hello");

    //Serial.println("Turn switches off.");
    //delay(5000);
    //checkSwitchOff(bad_connections);

    //checkReversePolarity(bad_connections, reverse_polarities);
    //Serial.prbyte(connected(CSp, CBp));
    // Save file on the USB
    //FILE *f;
    //f = fopen(PATH, "a");

    // Create connections char*
    //String output = arrToStr(bad_connections, reverse_polarities);
    String output = "bla";
    //char* revPol;
    //revP.toCharArray(revPol, revP.length());
    
    /*
    fputs(badConn, f);
    fputs(revPol, f);
    fclose(f);*/
    //Serial.prbyteln(bad_connections[0]);
    Serial.println(output);
}

void loop() {
  // put your main code here, to run repeatedly:

}


/* Function: checkConnections()
 * This function checks all of the connections to see if they are connected or not,
 * primarily through a subfunction called connected(pin_out, pin_in). If the two
 * pobytes do not follow the expected connectivity, its error code will be added to
 * the list bad_connections. This assumes the load switch is on.
 */
void checkConnections(String bad_connections[]) {
    String testNames[NUMTESTS] = {"2A", "2B", "2C", "2D", "2E.1", "2E.2", "2E.3", "2E.4", "2F",
                         "3A", "3B", "3C", "3D.1", "3D.2", "3D.3", "3D.4", "3E.1", "3E.2"
                         "3E.3", "3E.4", "3F", "4A", "4B", "4C", "4D", "4E", "4F",
                         "4G.1", "4G.2", "4G.3", "4G.4", "4H"};
    byte pins[NUMTESTS][3] = { {Bn, CBn, 0}, {CSn, CBn, 0}, {CSn, CLn, 0}, {Sn, CLn, 0}, {CLn, DC1n, 0},
                    {CLn, DC2n, 0}, {CLn, DC3n, 0}, {CLn, DC4n, 0}, {Bp, CBp, 0}, //Start of 3
                    {CBp, CSp, 1}, {CBp, CLp, 1}, {Sp, CSp, 0}, {CBp, DC1p, 1}, {CBp, DC2p, 1},
                    {CBp, DC3p, 1}, {CBp, DC4p, 1}, {CLp, DC1p, 0}, {CLp, DC2p, 0}, 
                    {CLp, DC3p, 0}, {CLp, DC4p, 0}, {CLp, Ep, 0}, //Start of 4
                    {Bp, Bn, 1}, {CSp, CSn, 1}, {Sp, Sn, 1}, {CSp, CBn, 1}, {CBp, CBn, 1}, {CLp, CLn, 1},
                    {CLp, DC1n, 1}, {CLp, DC2n, 1}, {CLp, DC3n, 1}, {CLp, DC4n, 1}, {Ep, En, 1} };
                    
    for (byte i = 0; i < NUMTESTS; i++) {
      //Serial.prbyteln(i);
      //String test = testNames[i];
      byte deets[3];
      memcpy(deets[3], pins[i], 3*sizeof(byte));
      if (connected(deets[0], deets[1]) != deets[2]) {
        bad_connections[badCount] = testNames[i];
        badCount++;
      }
    }
}

void checkSwitchOff(String bad_connections[]) {
  String testNames[OFFCONN] = {"2F", "3C", "3E.1", "3E.2", "3E.3", "3E.4"};
  byte pins[OFFCONN][3] = { {Bp, CBp, 1}, {Sp, CSp, 1}, {CLp, DC1p, 1}, {CLp, DC2p, 1},
                           {CLp, DC3p, 1}, {CLp, DC4p, 1} };

  for (byte i = 0; i < OFFCONN; i++) {
    //Serial.prbyteln(i);
    //String test = testNames[i];
    byte deets[3];
    memcpy(deets[3], pins[i], 3*sizeof(byte));
    if (connected(deets[0], deets[1]) != deets[2]) {
      bad_connections[badCount] = testNames[i];
      badCount++; 
    }
  }
}

/* Function: checkReversePolarity(&bad_connections)
 * @param: bad_connections - list of all bad connections, will be byteened
 * if any of the bad connections are actually reverse polarity connections
 * @return: a list of reverse polarity connections by their error code
 */
void checkReversePolarity(String bad_connections[], String reverse_polarities[]) {
    String all_errors[10] = {"2A", "2B", "2C", "2D", "2E.1", "2E.2", "2E.3", "2E.4", "2F", "3F"};
    byte tests[10][2] = { {Bp, CBn}, {CSp, CBn}, {CSp, CLn}, {Sp, CSn}, {DC1p, CLn}, {DC2p, CLn},
                       {DC3p, CLn}, {DC4p, CLn}, {Bn, CBp}, {En, CLp} };

    for (byte i = 0; i < 10; i++) {
      //String error = all_errors[i];
      if (contains(all_errors[i], bad_connections) != NUMTESTS) {
        byte test[2];
        memcpy(test, tests[i], 2 * sizeof(byte));
        if (connected(test[0], test[1]) != 1) {
          reverse_polarities[reverseCount] = all_errors[i];
          reverseCount++;
          takeOut(all_errors[i], bad_connections);
        }
      }
    }
}

// Contains method for array
byte contains(String error, String bad_connections[]) {
  char* err;
  error.toCharArray(err, error.length());
  for (byte i = 0; i < badCount; i++) {
    char* badC;
    String bad = bad_connections[badCount];
    bad.toCharArray(badC, bad.length());
    if (!strcmp(badC, err)) {
      return i;
    }
  }
  return NUMTESTS;
}

// removes element from array
void takeOut(String error, String bad_connections[]) {
  byte index = contains(error, bad_connections);
  for (byte i = index; i < badCount - 1; i++) {
    bad_connections[i] = bad_connections[i + 1];
  }
}

/* Function: connected(pin_out,pin_in)
 * This function checks to see if the two pins are connected by setting
 * one pin high and checking to see if the other pin also registers as high.
 * @param: pin_out - one of the pins, will be set high
 * @param: pin_in - one of the pins, will check to see if it receives high
 * @return: Will return true if the two pins are connected and false
 *          if the two pins are not connected
 */
bool connected(byte pin_out, byte pin_in) {
    pinMode(pin_out, OUTPUT);
    digitalWrite(pin_out, HIGH);
    return digitalRead(pin_in);
}

String arrToStr(String bad_connections[], String reverse_polarities[]) {
    String connections;

    //Bad Connections
    connections += "Bad Connections: { ";
    for (byte i = 0; i < badCount; i++) {
      connections += (bad_connections[i] + ',');
    }
    connections[connections.length() - 1] = '}';
    connections += "\n";

    //Reverse Polarity
    connections += "Reverse Connections: { ";
    for (byte j = 0; j < reverseCount; j++) {
      connections += (reverse_polarities[j] + ',');
    }
    connections[connections.length() - 1] = '}';
    connections += "\n";
    
    return connections;
}
