#/home/pi/Desktop
# Tester code for We Care Solar suitcases that tests for connectivity and reverse polarity.

import time
from time import strftime
import Adafruit_CharLCD as LCD
import RPi.GPIO as GPIO
import os

# Faulty Connections
# 3A, 3B, 

'''
Function: checkConnections()
This function checks all of the connections to see if they are connected or not, 
primarily through a subfunction called connected(pin_out, pin_in). If the two 
points do not follow the expected connectivity, its error code will be added to 
the list bad_connections. This assumes the load switch is on.
'''

def checkConnections():
    lcd.clear()

    '''
    Step 2 of Testing
    '''
    '''numTests = 33
    testRun = 1
    lcd.message(testRun + '/' + numTests)'''
    # Check 2A
    if connected(Bn, CBn) == 0:
        if connected(Bp, CBn):
            reverse_polarities.append('2A')
        else:
            bad_connections.append('2A')

    # Check 2B
    if connected(CBn, CSn) == 0:
        if connected(CSp, CBn):
            reverse_polarities.append('2B')
        else:
            bad_connections.append('2B')

    # Check 2C
    if connected(CLn,CSn)== 0:
        if connected(CSp, CLn):
            reverse_polarities.append('2C')
        else:
            bad_connections.append('2C')

    # Check 2D
    if connected(Sn,CSn) == 0:
        if connected(Sp, CSn):
            reverse_polarities.append('2D')
        else:
            bad_connections.append('2D')

    # Check 2E.1
    if connected(CLn,DC1n)== 0:
        if connected(CLn, DC1p):
            reverse_polarities.append('2E.1')
        else:
            bad_connections.append('2E.1')

    # Check 2E.2
    if connected(CLn,DC2n)== 0:
        if connected(CLn, DC2p):
            reverse_polarities.append('2E.2')
        else:
            bad_connections.append('2E.2')

    # Check 2E.3
    if connected(CLn,DC3n) == 0:
        if connected(CLn, DC3p):
            reverse_polarities.append('2E.3')
        else:
            bad_connections.append('2E.3')

    # Check 2E.4
    if connected(CLn,DC4n) == 0:
        bad_connections.append('2E.4')

    # Check 2F
    if connected(Bp,CBp)== 0:
        if connected(Bn, CBp):
            reverse_polarities.append('2F')
        else:
            bad_connections.append('2F')


    '''
    Step 3 of Testing
    '''
    
    # Check 3A
    if connected(CBp,CSp) == 1:
        bad_connections.append('3A')

    # Check 3B
    if connected(CBp,CLp) == 1:
        bad_connections.append('3B')

    # Check 3C
    if connected(Sp,CSp) == 0:
        bad_connections.append('3C')

    # Check 3D.1
    if connected(CBp,DC1p) == 1:
        bad_connections.append('3D.1')

    # Check 3D.2
    if connected(CBp,DC2p) == 1:
        bad_connections.append('3D.2')

    # Check 3D.3
    if connected(CBp,DC3p) == 1:
        bad_connections.append('3D.3')

    # Check 3D.4
    if connected(CBp,DC4p) == 1:
        bad_connections.append('3D.4')

    # Check 3E.1
    connected(DC1p,CLp)

    # Check 3E.1
    if connected(DC1p,CLp) == 0:
        bad_connections.append('3E.1')

    # Check 3E.2
    if connected(CLp,DC2p) == 0:
        bad_connections.append('3E.2')

    # Check 3E.3
    if connected(CLp,DC3p) == 0:
        bad_connections.append('3E.3')

    # Check 3E.4
    if connected(CLp,DC4p) == 0:
        bad_connections.append('3E.4')

    # Check 3F
    if connected(CLp,Ep) == 0:
        if connected(CLp, En):
            reverse_polarities.append('3F')
        else:
            bad_connections.append('3F')
    
    '''
    Step 4
    '''
    
    # Check 4A
    if connected(Bp,Bn) == 1:
        bad_connections.append('4A')

    # Check 4B
    if connected(CSp,CSn) == 1:
        bad_connections.append('4B')

    # Check 4C
    if connected(Sp, Sn) == 1:
        bad_connections.append('4C')

    # Check 4D
    if connected(CSp, CBn) == 1:
        bad_connections.append('4D')

    # Check 4E
    if connected(CBp,CBn) == 1:
        bad_connections.append('4E')

    # Check 4F
    if connected(CLp,CLn) == 1:
        bad_connections.append('4F')

    # Check 4G.1
    if connected(CLp,DC1n) == 1:
        bad_connections.append('4G.1')

    # Check 4G.2
    if connected(CLp,DC2n) == 1:
        bad_connections.append('4G.2')

    # Check 4G.3
    if connected(CLp,DC3n) == 1:
        bad_connections.append('4G.3')

    # Check 4G.4
    if connected(CLp,DC4n) == 1:
        bad_connections.append('4G.4')

    # Check 4H
    if connected(En,Ep) == 1:
        bad_connections.append('4H')


def checkSwitchOffConnections():
    while True:
        if lcd.is_pressed(LCD.SELECT):
            lcd.clear()
            
            # Check 2F - off
            if connected(Bp,CBp)== 1:
                if connected(Bn, CBp):
                    reverse_polarities.append('2F - off')
                else:
                    bad_connections.append('2F - on')

            # Check 3C - off
            if connected(Sp,CSp) == 1:
                bad_connections.append('3C - off')

            # Check 3E.1 - off
            if connected(CLp,DC1p) == 1:
                bad_connections.append('3E.1 - off')

            # Check 3E.2 - off
            if connected(CLp,DC2p) == 1:
                bad_connections.append('3E.2 - off')

            # Check 3E.3 - off
            if connected(CLp,DC3p) == 1:
                bad_connections.append('3E.3 - off')

            # Check 3E.4 - off
            if connected(CLp,DC4p) == 1:
                bad_connections.append('3E.4 - off')

            break

'''
    Function: checkReversePolarity(&bad_connections)
    @param: bad_connections - list of all bad connections, will be shortened
    if any of the bad connections are actually reverse
    polarity connections
    @return: a list of reverse polarity connections by their error code
    '''
def checkReversePolarity(&bad_connections):
    all_errors = {'2A': [Bp, CBn], '2B': [CSp, CBn], '2C': [CSp, CLn], '2D': [Sp, CSn],
        '2E.1': [DC1p, CLn], '2E.2': [DC2p, CLn], '2E.3': [DC3p, CLn], '2E.4': [DC4p, CLn],
            '2F': [Bn, CBp], '3F': [En, CLp]}
    
    reverse_connections = [];
    
    for i in all_errors:
        error = all_errors[i];
        if bad_connections.count(error) == 1:
            test = all_errors.get(error);
            if test != None and connected(test[0], test[1]) == 1:
                reverse_connections.append(error);
                bad_connections.remove(error);

return reverse_connections;


'''
Function: connected(pin_out,pin_in)
This function checks to see if the two pins are connected by setting
one pin high and checking to see if the other pin also registers as high.
@param: pin_out - one of the pins, will be set high
@param: pin_in - one of the pins, will check to see if it receives
                    high
@return: Will return true if the two pins are connected and false
            if the two pins are not connected
'''
def connected(pin_out, pin_in):
    GPIO.cleanup()
    time.sleep(0.3)
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(pin_out,GPIO.OUT)
    GPIO.setup(pin_in,GPIO.IN,GPIO.PUD_DOWN)
    GPIO.output(pin_out,1)
    time.sleep(0.35)
    return GPIO.input(pin_in)


'''
Function: inputNum()
This function allows the user to input the number of the suitcase using
the LCD display buttons and display. For a max of 4 digits, the user can
press UP to increase the number, DOWN to decrease the number, LEFT to move
the changing digit up by 10 and RIGHT to move the changing digit down by 10.
To finish, the user presses SELECT.
@return: The number of the suitcase.
'''

def inputNum():
    num = 0
    unit = 1
    
    lcd.message('#: ' + str(num).zfill(4) + "\n" + displayUnit(unit))
    while True:
        if lcd.is_pressed(LCD.UP):
            num = num + 1*unit
            if num > 9999:               # makes sure only 4 digits
                num = num - 1*unit
            lcd.clear()
            lcd.message('#: ' + str(num).zfill(4) + "\n" + displayUnit(unit))
            time.sleep(0.3)           # pause for 300ms
        elif lcd.is_pressed(LCD.DOWN) and num/unit > 0:
            num = num - 1*unit
            if num < unit and unit > 1:
                unit = unit/10
            lcd.clear()
            lcd.message('#: ' + str(num).zfill(4) + "\n" + displayUnit(unit))
            time.sleep(0.3)
        elif lcd.is_pressed(LCD.LEFT) and unit < 1000:
            unit = 10*unit
            lcd.clear()
            lcd.message('#: ' + str(num).zfill(4) + "\n" + displayUnit(unit))
            time.sleep(0.3)
        elif lcd.is_pressed(LCD.RIGHT) and unit > 1:
            unit = unit/10
            lcd.clear()
            lcd.message('#: ' + str(num).zfill(4) + "\n" + displayUnit(unit))
            time.sleep(0.3)
        elif lcd.is_pressed(LCD.SELECT):
            return num

def displayUnit(unit):
    if unit == 1:
        return '      ^'
    elif unit == 10:
        return '     ^'
    elif unit == 100:
        return '    ^'
    else:
        return '   ^'

'''
Function: displayConnections(bad_connections)
This function displays the list of bad_connections on the LCD display. 
The user presses RIGHT to see the next bad connection, LEFT to see the
previous bad connection, and DOWN to return to the next part of the test.
@param: bad_connections: the list of bad connections to display
'''

def displayConnections(curr_list):
    i = 0;
    while i < len(curr_list):
        if lcd.is_pressed(LCD.RIGHT):
            lcd.clear()
            lcd.message(str(curr_list[i]))
            i = i + 1
            time.sleep(.5)
        elif lcd.is_pressed(LCD.LEFT) and i > 0:
            lcd.clear()
            i = i - 1
            lcd.message(str(curr_list[i]))
            time.sleep(.5)
        elif lcd.is_pressed(LCD.DOWN):
            time.sleep(0.5)
            return
            
'''
Function: finishTest()
This function allows the user to start a new test by pressing UP and 
shut down by pressing DOWN.
@return: 1 if the user wants to start a new test
         0 if the user wants to shut down
'''
def finishTest():
    lcd.clear()
    lcd.message('UP - new test' + "\n"  + 'DOWN - shut down')
    while True:
        if lcd.is_pressed(LCD.UP):
            return 1
        elif lcd.is_pressed(LCD.DOWN):
            return 0
    
def turnOnSwitches():
    lcd.clear()
    lcd.message('turn ON' + "\n"  + 'switches-SELECT')
    time.sleep(1)
    while True:
        if lcd.is_pressed(LCD.SELECT):
            lcd.clear()
            break


''' CODE STARTS EXECUTING HERE'''

               
# GPIO settings
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

# GPIO pins used
DC1p = 4        # DC Receptacle #1 positive
DC1n = 17       # DC Receptacle #1 negative
DC2p = 27       # DC Receptacle #2 positive
DC2n = 22       # DC Receptacle #2 negative
DC3p = 10       # DC Receptacle #3 positive
DC3n = 9        # DC Receptacle #3 negative
DC4p = 11       # DC Receptacle #4 positive
DC4n = 5        # DC Receptacle #4 negative
Ep = 6          # Expansion port positive
En = 13         # Expansion port negative
CLp = 19        # Charge Controller Load positive
CLn = 26        # Charge Controller Load negative
CBp = 21        # Charge Controller Battery positive
CBn = 20        # Charge Controller Battery negative
CSp = 16        # Charge Controller Solar positive
CSn = 12        # Charge Controller Solar negative
Bp = 7          # Battery positive
Bn = 8          # Battery negative
Sp = 25         # Solar Homerun Cable positive
Sn = 24         # Solar Homerun Cable negative


# Initialize the LCD using the pins
lcd = LCD.Adafruit_CharLCDPlate()
lcd.clear()

    
# Make list of button value, text, and backlight color.
buttons = ( (LCD.SELECT, 'Select', (1,1,1)),
            (LCD.LEFT,   'Left'  , (1,0,0)),
            (LCD.UP,     'Up'    , (0,0,1)),
            (LCD.DOWN,   'Down'  , (0,1,0)),
            (LCD.RIGHT,  'Right' , (1,0,1)) )

writeFormat = "%Y.%m.%d.%H.%M"

# Save file on the USB
global f
f = open("/mnt/test.csv", "a")

testing = 1

while testing == 1:
    suitcaseNum = inputNum()
    f.write(strftime(writeFormat) +
            '     Suitcase Number: ' + str(suitcaseNum) + "\n")
    global bad_connections
    global reverse_polarities
    bad_connections = list()
    reverse_polarities = list()
    turnOnSwitches()
    checkConnections()
    lcd.message('switches off' + "\n"  + 'SELECT - continue')
    checkSwitchOffConnections()
    checkReversePolarity(bad_connections)
    
    f.write('Bad Connections: ' + str(bad_connections)+ "\n")
    f.write('Reverse Polarities: ' + str(reverse_polarities)+ "\n")

    lcd.clear()    
    lcd.message('RIGHT-see bad' + "\n"  + 'DOWN - continue')
    displayConnections(bad_connections)
    lcd.clear()
    lcd.message('RIGHT-see reverse' + "\n"  + 'DOWN - continue')
    displayConnections(reverse_polarities)
    testing = finishTest()
    time.sleep(0.5)

f.close()
lcd.clear()
GPIO.cleanup()
#os.system('shutdown now -h')


