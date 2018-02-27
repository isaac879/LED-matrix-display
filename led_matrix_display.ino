/*--------------------------------------------------------------------------------------------------------------------------------------------------------
 * 
 * CHECK THE CODE FOR "TODO:" AND EDIT APPROPRIATELY 
 * 
 * The code is developed for a 8x24 LED matrix display. The display is controlled by an Arduino Nano, HC-05 Bluetooth module and shift register circuits.
 * 
 * CAD files available at: Not currently publicly available.
 * 
 * All measurements are in SI units unless otherwise specified
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
 * IN THE SOFTWARE
 * 
 * Code written by isaac879
 * 
 * Last modified 27/02/2018
 *--------------------------------------------------------------------------------------------------------------------------------------------------------*/

#include <avr/pgmspace.h>
#include <Iibrary.h>//A library I created for Arduino that contains some simple functions I commonly use. Library available at: https://github.com/isaac879/Iibrary
#include "led_matrix_text.h"

#define LATCH_PIN  3
#define CLOCK_PIN 4
#define DATA_PIN 2
#define CLOCK_PIN_GROUND 6
#define DATA_PIN_GROUND 5

#define DISPLAY_MATRIX_COLUMNS 24
#define DISPLAY_MATRIX_ROWS 8

#define MAX_STRING_LENGTH 500

#define SCROLL_DELAY 45

char stringText[MAX_STRING_LENGTH];

int stringLength = 0;

unsigned int scroll_delay = 45;

byte rowSelect = 0;

bool display_array[8][24] =
{
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}  
};

void setDisplayArray(int columnOffset){
    int column = 0;
    int element = 0;
    for(int i = 0; i < DISPLAY_MATRIX_ROWS - 1; i++){//loop through the area of the display matrix
        for(int j = 0; j < DISPLAY_MATRIX_COLUMNS; j++){
            column = j + columnOffset;
            if(i == 7 || (column + 1) % 6 == 0 || column < 0) {
                display_array[i][j] = 0;
                continue;
            }
            element = column / 6;
            
            if(stringText[element]=='A'){
                display_array[i][j] = pgm_read_byte(&A_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='B'){
                display_array[i][j] = pgm_read_byte(&B_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='C'){
                display_array[i][j] = pgm_read_byte(&C_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='D'){
                display_array[i][j] = pgm_read_byte(&D_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='E'){
                display_array[i][j] = pgm_read_byte(&E_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='F'){
                display_array[i][j] = pgm_read_byte(&F_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='G'){
                display_array[i][j] = pgm_read_byte(&G_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='H'){
                display_array[i][j] = pgm_read_byte(&H_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='I'){
                display_array[i][j] = pgm_read_byte(&I_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='J'){
                display_array[i][j] = pgm_read_byte(&J_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='K'){
                display_array[i][j] = pgm_read_byte(&K_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='L'){
                display_array[i][j] = pgm_read_byte(&L_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='M'){
                display_array[i][j] = pgm_read_byte(&M_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='N'){
                display_array[i][j] = pgm_read_byte(&N_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='O'){
                display_array[i][j] = pgm_read_byte(&O_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='P'){
                display_array[i][j] = pgm_read_byte(&P_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='Q'){
                display_array[i][j] = pgm_read_byte(&Q_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='R'){
                display_array[i][j] = pgm_read_byte(&R_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='S'){
                display_array[i][j] = pgm_read_byte(&S_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='T'){
                display_array[i][j] = pgm_read_byte(&T_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='U'){
                display_array[i][j] = pgm_read_byte(&U_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='V'){
                display_array[i][j] = pgm_read_byte(&V_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='W'){
                display_array[i][j] = pgm_read_byte(&W_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='X'){
                display_array[i][j] = pgm_read_byte(&X_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='Y'){
                display_array[i][j] = pgm_read_byte(&Y_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='Z'){
                display_array[i][j] = pgm_read_byte(&Z_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='1'){
                display_array[i][j] = pgm_read_byte(&Array_1[i][(column - element) % 5]);
            }else if(stringText[element]=='2'){
                display_array[i][j] = pgm_read_byte(&Array_2[i][(column - element) % 5]);
            }else if(stringText[element]=='3'){
                display_array[i][j] = pgm_read_byte(&Array_3[i][(column - element) % 5]);
            }else if(stringText[element]=='4'){
                display_array[i][j] = pgm_read_byte(&Array_4[i][(column - element) % 5]);
            }else if(stringText[element]=='5'){
                display_array[i][j] = pgm_read_byte(&Array_5[i][(column - element) % 5]);
            }else if(stringText[element]=='6'){
                display_array[i][j] = pgm_read_byte(&Array_6[i][(column - element) % 5]);
            }else if(stringText[element]=='7'){
                display_array[i][j] = pgm_read_byte(&Array_7[i][(column - element) % 5]);
            }else if(stringText[element]=='8'){
                display_array[i][j] = pgm_read_byte(&Array_8[i][(column - element) % 5]);
            }else if(stringText[element]=='9'){
                display_array[i][j] = pgm_read_byte(&Array_9[i][(column - element) % 5]);
            }else if(stringText[element]=='0'){
                display_array[i][j] = pgm_read_byte(&Array_0[i][(column - element) % 5]);
            }else if(stringText[element]==' '){
                display_array[i][j] = pgm_read_byte(&Space_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='!'){
                display_array[i][j] = pgm_read_byte(&Exclamation_Mark_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='.'){
                display_array[i][j] = pgm_read_byte(&Full_Stop_Array[i][(column - element) % 5]);
            }else if(stringText[element]==':'){
                display_array[i][j] = pgm_read_byte(&Colon_Array[i][(column - element) % 5]);
            }else if(stringText[element]==';'){
                display_array[i][j] = pgm_read_byte(&SemiColon_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='='){
                display_array[i][j] = pgm_read_byte(&Equals_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='*'){
                display_array[i][j] = pgm_read_byte(&Times_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='+'){
                display_array[i][j] = pgm_read_byte(&Plus_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='-'){
                display_array[i][j] = pgm_read_byte(&Minus_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='?'){
                display_array[i][j] = pgm_read_byte(&Question_Mark_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='#'){
                display_array[i][j] = pgm_read_byte(&Hash_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='<'){
                display_array[i][j] = pgm_read_byte(&Left_Angle_Bracket_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='>'){
                display_array[i][j] = pgm_read_byte(&Right_Angle_Bracket_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='('){
                display_array[i][j] = pgm_read_byte(&Open_Bracket_Array[i][(column - element) % 5]);
            }else if(stringText[element]==')'){
                display_array[i][j] = pgm_read_byte(&Close_Bracket_Array[i][(column - element) % 5]);
            }else if(stringText[element]==','){
                display_array[i][j] = pgm_read_byte(&Comma_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='/'){
                display_array[i][j] = pgm_read_byte(&Slash_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='$'){
                display_array[i][j] = pgm_read_byte(&Pound_Sign_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='^'){
                display_array[i][j] = pgm_read_byte(&Up_Arrow_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='~'){
                display_array[i][j] = pgm_read_byte(&Tilde_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='_'){
                display_array[i][j] = pgm_read_byte(&Underscore_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='%'){
                display_array[i][j] = pgm_read_byte(&Percent_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='|'){
                display_array[i][j] = pgm_read_byte(&Pipe_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='['){
                display_array[i][j] = pgm_read_byte(&Square_Open_Bracket_Array[i][(column - element) % 5]);
            }else if(stringText[element]==']'){
                display_array[i][j] = pgm_read_byte(&Square_Close_Bracket_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='{'){
                display_array[i][j] = pgm_read_byte(&Curly_Open_Bracket_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='}'){
                display_array[i][j] = pgm_read_byte(&Curly_Close_Bracket_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='\\'){
                display_array[i][j] = pgm_read_byte(&Backslash_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='\''){
                display_array[i][j] = pgm_read_byte(&Apostrophe_Array[i][(column - element) % 5]);
            } else if(stringText[element]=='&'){
                display_array[i][j] = pgm_read_byte(&Ampersand_Array[i][(column - element) % 5]);
            }else if(stringText[element]=='"'){
                display_array[i][j] = pgm_read_byte(&Speech_Mark_Array[i][(column - element) % 5]);
            }else{
                display_array[i][j] = 0;
            }
        } 
    }
}
 
void setup() {
    pinMode(LATCH_PIN, OUTPUT);
    pinMode(CLOCK_PIN, OUTPUT);
    pinMode(DATA_PIN, OUTPUT);
    pinMode(CLOCK_PIN_GROUND, OUTPUT);
    pinMode(DATA_PIN_GROUND, OUTPUT);   
    Serial.begin(9600);  
    stringText[0] = ' ';
    stringText[1] = 'S';
    stringText[2] = 'E';
    stringText[3] = 'T';
    stringText[4] = ' ';
    stringText[5] = 'T';
    stringText[6] = 'E';
    stringText[7] = 'X';
    stringText[8] = 'T';
    stringText[9] = '.';
    stringLength = strlen(stringText);//number of chars in the string
}

int offset = 0;
int currentStringLength = 0;
void loop() {
    if(offset > stringLength * 6){
        offset = - (DISPLAY_MATRIX_COLUMNS - 1);  
        int i = 0;
        if(Serial.available()){
            for(int k = 0; k < stringLength; k++){//set all elements of stringText to null
                stringText[k] = '\0';
            }
        }
        while(Serial.available()){//set elemetns of stringText to the serial values sent
            stringText[i++] = Serial.read();
            if(i >= MAX_STRING_LENGTH) break;//exit the loop when the stringText array is full
        }
        stringLength = strlen(stringText);//get the new length of the string
       // printi(stringText);
       //if(stringText[0] == '@'){
       //scroll_delay = stringToInt(stringText[1 to 4]);
       //}
       //need to keep the previous string and only replace it if it's not setting the scroll speed
       //should have an option for no scroll and also have a limit for the slowest scroll (3000ms)
    }
    setDisplayArray(offset++);
    unsigned long startTime = millis();
    while(startTime + SCROLL_DELAY > millis()){
        for(int row = 0; row < DISPLAY_MATRIX_ROWS; row++){ 
            rowSelect = ~(0b00000010 << row);//starts on row 2 (index 1)
            digitalWrite(LATCH_PIN, LOW);// take the latchPin low so the LEDs don't change while you're sending in bits.
            shiftOut(DATA_PIN_GROUND, CLOCK_PIN_GROUND, LSBFIRST, rowSelect);// shift out the bits to ground register.
            for(int column = 0; column < DISPLAY_MATRIX_COLUMNS; column++){
                if(display_array[row][(DISPLAY_MATRIX_COLUMNS - 1) - column] == 1){
                    digitalWrite(DATA_PIN, HIGH);
                }else{
                    digitalWrite(DATA_PIN, LOW);
                }
                digitalWrite(CLOCK_PIN, HIGH);//Pulse Clock pin
                digitalWrite(CLOCK_PIN, LOW);
            }
            digitalWrite(LATCH_PIN, HIGH);//take the latch pin high so the LEDs will light up.
            delayMicroseconds(5);//Delay
        }
    }
}


