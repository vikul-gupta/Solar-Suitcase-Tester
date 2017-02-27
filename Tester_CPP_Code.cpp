/* Tester code for We Care Solar suitcases that tests for connectivity and reverse polarity.
 * /home/pi/Desktop
 */

#include <stdio.h>
#include <time.h>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
using namespace std;

/*
from time import strftime
import Adafruit_CharLCD as LCD
import RPi.GPIO as GPIO
import os
*/

const string PATH = "/mnt/test.csv";

// Faulty Connections
// 3A, 3B,

/* Function: checkConnections()
 * This function checks all of the connections to see if they are connected or not,
 * primarily through a subfunction called connected(pin_out, pin_in). If the two
 * points do not follow the expected connectivity, its error code will be added to
 * the list bad_connections. This assumes the load switch is on.
 */
vector<string> checkConnections() {
    //lcd.clear();
    // Step 2 of Testing
    //numTests = 33
    //testRun = 1
    //lcd.message(testRun + '/' + numTests)'''
    map<string, list<int>> connections;
    connections = {'2A': [Bn, CBn, 0], '2B': [CSn, CBn, 0], '2C': [CSn, CLn, 0)]
                '2D': [Sn, CLn, 0], '2E.1': [CLn, DC1n, 0], '2E.2': [CLn, DC2n, 0],
                '2E.3': [CLn, DC3n, 0], '2E.4': [CLn, DC4n, 0], '2F': [Bp, CBp, 0],
                '''
                Step 3
                '''
                '3A': [CBp, CSp, 1], '3B': [CBp, CLp, 1], '3C': [Sp, CSp, 0],
                '3D.1': [CBp, DC1p, 1], '3D.2': [CBp, DC2p, 1], '3D.3': [CBp, DC3p, 1],
                '3D.4': [CBp, DC4p, 1], '3E.1': [CLp, DC1p, 0], '3E.2': [CLp, DC2p, 0],
                '3E.3': [CLp, DC3p, 0], '3E.4': [CLp, DC4p, 0], '3F': [CLp, Ep, 0],
                '''
                Step 4
                '''
                '4A': [Bp, Bn, 1], '4B': [CSp, CSn, 1], '4C': [Sp, Sn, 1],
                '4D': [CSp, CBn, 1], '4E': [CBp, CBn, 1], '4F': [CLp, CLn, 1],
                '4G.1': [CLp, DC1n, 1], '4G.2': [CLp, DC2n, 1], '4G.3': [CLp, DC3n, 1],
                '4G.4': [CLp, DC4n, 1], '4H': [Ep, En, 1]};

        for_each (string test : connections.items()) {
            list<int> deets = connections[test];
            if (connected(deets[0], deets[1]) == deets[2]) {
                bad_connections.append(test);
            }
        }

        return bad_connections;
}

/* Function: checkReversePolarity(&bad_connections)
 * @param: bad_connections - list of all bad connections, will be shortened
 * if any of the bad connections are actually reverse polarity connections
 * @return: a list of reverse polarity connections by their error code
 */
list<string> checkReversePolarity(&bad_connections) {
    Map<string, list<int>> all_errors = {'2A': [Bp, CBn], '2B': [CSp, CBn], '2C': [CSp, CLn], '2D': [Sp, CSn],
                  '2E.1': [DC1p, CLn], '2E.2': [DC2p, CLn], '2E.3': [DC3p, CLn], '2E.4': [DC4p, CLn],
                  '2F': [Bn, CBp], '3F': [En, CLp]};

    list<string> reverse_connections;

    for_each (string error : all_errors) {
        if (bad_connections.count(error) == 1) {
            test = all_errors[error];
            if (test != None && connected(test[0], test[1]) == 1) {
                reverse_connections.append(error);
                bad_connections.remove(error);
            }
        }
    }

    return reverse_connections;
}

/* Function: connected(pin_out,pin_in)
 * This function checks to see if the two pins are connected by setting
 * one pin high and checking to see if the other pin also registers as high.
 * @param: pin_out - one of the pins, will be set high
 * @param: pin_in - one of the pins, will check to see if it receives high
 * @return: Will return true if the two pins are connected and false
 *          if the two pins are not connected
 */
bool connected(pin_out, pin_in) {
    //cleanup
    //setmode
    pinMode(pin_out, OUTPUT);
    //setup
    digitalWrite(pin_out, HIGH);
    return digitalRead(pin_in);
}

/* Function: inputNum()
 * This function allows the user to input the number of the suitcase using
 * the LCD display buttons and display. For a max of 4 digits, the user can
 * press UP to increase the number, DOWN to decrease the number, LEFT to move
 * the changing digit up by 10 and RIGHT to move the changing digit down by 10.
 * To finish, the user presses SELECT.
 * @return: The number of the suitcase.
 
int inputNum() {
    num = 0;
    unit = 1;

    lcd.message('#: ' + str(num).zfill(4) + "\n" + displayUnit(unit));
    while (true) {
        if (lcd.is_pressed(LCD.UP)) {
            num = num + 1*unit;
            if (num > 9999) {              // makes sure only 4 digits
                num = num - 1*unit;
            }
            lcd.clear();
            lcd.message('#: ' + str(num).zfill(4) + "\n" + displayUnit(unit));
            time.sleep(0.3);           // pause for 300ms
        } else if (lcd.is_pressed(LCD.DOWN) && num/unit > 0) {
            num = num - 1*unit;
            if (num < unit && unit > 1) {
                unit = unit/10;
            }
            lcd.clear();
            lcd.message('#: ' + str(num).zfill(4) + "\n" + displayUnit(unit));
            time.sleep(0.3);
        } else if (lcd.is_pressed(LCD.LEFT) && unit < 1000) {
            unit = 10*unit;
            lcd.clear();
            lcd.message('#: ' + str(num).zfill(4) + "\n" + displayUnit(unit));
            time.sleep(0.3);
        } else if (lcd.is_pressed(LCD.RIGHT) && unit > 1) {
            unit = unit/10;
            lcd.clear();
            lcd.message('#: ' + str(num).zfill(4) + "\n" + displayUnit(unit));
            time.sleep(0.3);
        } else if (lcd.is_pressed(LCD.SELECT)) {
            return num;
        }
    }
}

string displayUnit(int unit) {
    if (unit == 1) {
        return "      ^";
    } else if (unit == 10) {
        return "     ^";
    } else if (unit == 100) {
        return "    ^";
    } else {
        return "   ^";
    }
}

/* Function: displayConnections(bad_connections)
 * This function displays the list of bad_connections on the LCD display.
 * The user presses RIGHT to see the next bad connection, LEFT to see the
 * previous bad connection, and DOWN to return to the next part of the test.
 * @param: bad_connections: the list of bad connections to display
 
void displayConnections(curr_list) {
    int i = 0;
    while (i < len(curr_list)) {
        if (lcd.is_pressed(LCD.RIGHT)) {
            lcd.clear();
            lcd.message(str(curr_list[i]));
            i++;
            time.sleep(.5);
        } else if (lcd.is_pressed(LCD.LEFT) && i > 0) {
            lcd.clear();
            i--;
            lcd.message(str(curr_list[i]));
            time.sleep(.5);
        } else if (lcd.is_pressed(LCD.DOWN)) {
            time.sleep(0.5);
        }
    }
}

/* Function: finishTest()
 * This function allows the user to start a new test by pressing UP and
 * shut down by pressing DOWN.
 * @return: 1 if the user wants to start a new test
         0 if the user wants to shut down
 
int finishTest() {
    lcd.clear();
    lcd.message('UP - new test' + "\n"  + 'DOWN - shut down');
    while (true) {
        if (lcd.is_pressed(LCD.UP)) {
            return 1;
        } else if (lcd.is_pressed(LCD.DOWN)) {
            return 0;
        }
    }
}

void turnOnSwitches() {
    lcd.clear();
    lcd.message('turn ON' + "\n"  + 'switches-SELECT');
    time.sleep(1);
    while (true) {
        if (lcd.is_pressed(LCD.SELECT)) {
            lcd.clear();
            break;
        }
    }
}
*/
string arrToStr(list<string> connectionsArr) {
    string connections = "";
        for_each (string connection : connectionsArr) {
            badConnections += (connection + ',');
        }
        badConnections.pop_back();
        return badConnections;
}


// CODE STARTS EXECUTING HERE
void main() {
    // GPIO settings
    //GPIO.setmode(GPIO.BCM);
    //GPIO.setwarnings(False);

    // GPIO pins used
    int DC1p = 4;        // DC Receptacle #1 positive
    int DC1n = 17;       // DC Receptacle #1 negative
    int DC2p = 27;      // DC Receptacle #2 positive
    int DC2n = 22;       // DC Receptacle #2 negative
    int DC3p = 10;       // DC Receptacle #3 positive
    int DC3n = 9;        // DC Receptacle #3 negative
    int DC4p = 11;       // DC Receptacle #4 positive
    int DC4n = 5;        // DC Receptacle #4 negative
    int Ep = 6;          // Expansion port positive
    int En = 13;         // Expansion port negative
    int CLp = 19;        // Charge Controller Load positive
    int CLn = 26;        // Charge Controller Load negative
    int CBp = 21;        // Charge Controller Battery positive
    int CBn = 20;        // Charge Controller Battery negative
    int CSp = 16;        // Charge Controller Solar positive
    int CSn = 12;        // Charge Controller Solar negative
    int Bp = 7;          // Battery positive
    int Bn = 8;          // Battery negative
    int Sp = 25;        // Solar Homerun Cable positive
    int Sn = 24;         // Solar Homerun Cable negative

    /*
    // Initialize the LCD using the pins
    lcd = LCD.Adafruit_CharLCDPlate();
    lcd.clear();
    */
    /*
    // Make list of button value, text, and backlight color.
    list<list<list<>> buttons;
    buttons = [ [[LCD.], ['Select'], [(1,1,1)]],
                [[LCD.LEFT],   ['Left']  , [(1,0,0)]],
                [[LCD.UP],     ['Up']    , [(0,0,1)]],
                [[LCD.DOWN],   ['Down']  , [(0,1,0)]],
                [LCD.RIGHT],  ['Right'] , (1,0,1)) ];
    */
    //string writeFormat = "%Y.%m.%d.%H.%M";

    // Save file on the USB
    ofstream f;
    f.open(PATH, "a");

    int testing = 1;

    //while (testing == 1) {
        int suitcaseNum = inputNum();
        //f << (strftime(writeFormat) +
        //        '     Suitcase Number: ' + str(suitcaseNum) + "\n");
        //turnOnSwitches();
        list<string> bad_connections = checkConnections();
        list<string> reverse_polarities = checkReversePolarity(bad_connections);
        //lcd.message('switches off' + "\n"  + 'SELECT - continue');
        //Turn LED on
        //checkSwitchOffConnections();

        

        f << ('Bad Connections: ' + arrToStr(bad_connections)+ "\n");
        f << ('Reverse Polarities: ' + arrToStr(reverse_polarities)+ "\n");

        /*
        lcd.clear();
        lcd.message('RIGHT-see bad' + "\n"  + 'DOWN - continue');
        displayConnections(bad_connections);
        lcd.clear();
        lcd.message('RIGHT-see reverse' + "\n"  + 'DOWN - continue');
        displayConnections(reverse_polarities);
        testing = finishTest();
        time.sleep(0.5);
        */
    //}

    f.close();
    //lcd.clear();
    //GPIO.cleanup();
    //os.system('shutdown now -h')
}
