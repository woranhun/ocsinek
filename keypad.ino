#include <Keypad.h>
#include <stdio.h>

#define MaxInputLen 64
const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {3, 4, 5, 6}; 
byte colPins[COLS] = {7, 8, 9, 10}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
  Serial.begin(9600);
}
char* getString(){
	char pressed;
	int i =0;
	char* inp =(char*)malloc(sizeof(char)*(MaxInputLen+1));
	while((pressed = customKeypad.getKey())!='#'){
		if(pressed){
			if(pressed=='*'){
				i--;
			}else{
				Serial.println(pressed);
				inp[i]=pressed;
				i++;
			}
		}
	}
	inp[i++]=0;
	return inp;
}
int convertStringToInt(char* str){
	int n =0;
	int szorzo=1;
	int slen= strlen(str);
	for(int i = slen; i>0;i--){
		n+=((int)str[i-1]-'0')*szorzo;
		szorzo*=10;
	}
	return n;
}
  
void loop(){
	char* str =getString();
	int a = convertStringToInt(str);
	Serial.print("Output:");
	Serial.println(str);
	Serial.println(a);
	free(str);
}
