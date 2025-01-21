/*
  Link Analyzer: a project using Arduino to communicate with Megaman PET Link Chips
  Copyright (c) 2025 Zach Lambert

  Permission is hereby granted, free of charge, to any person obtaining a
  copy of this software and associated documentation files (the "Software"),
  to deal in the Software without restriction, including without limitation
  the rights to use, copy, modify, merge, publish, distribute, sublicense,
  and/or sell copies of the Software, and to permit persons to whom the
  Software is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
  DEALINGS IN THE SOFTWARE.
*/

#include <Wire.h>

String serialData = "";

int commonPin = 9;
int readPins[] = {11,10,8,7,6,5,4,3,2};

void setup() {
  Serial.begin(9600);

  pinMode(commonPin, OUTPUT);
  for(int i = 0; i < 9; i++){
    pinMode(readPins[i], INPUT_PULLUP);
  }
}

void loop() {
  if (Serial.available() > 0) {
    char value = Serial.read();

    if(value != '\n'){
      serialData += value;
    }else{
      runCommand(serialData.charAt(0), serialData.substring(2));
      serialData = "";
    }
  }
}

void runCommand(int command, String data){
  switch(command){
    case 'r':
      readNaviChip();
      break;
    case 'w':
      writeNaviChip(data);
      break;
    case 'p':
      Serial.println(readChip());
      break;
    case 'v':
      Serial.println("Link Analyzer Version 2.0.1");
      break;
    default:
      Serial.println("Command not found");
  }
}

String readChip(){
  String chipCode = "01";
  digitalWrite(commonPin, LOW);
  for(int i = 0; i < 9; i++){
    if(digitalRead(readPins[i]) == HIGH){
      chipCode += "0";
    }
    else{
      chipCode += "1";
    }
  }
  digitalWrite(commonPin, LOW);
  chipCode += "0";

  return chipCode;
}

void readNaviChip(){
  for(int j = 0; j < 4; j++){
    for(int i = 0; i <= 255; i++){
      int readByte = (int)readI2CByte(j, i);
      if(readByte <= 15) Serial.print("0");
      Serial.print(readI2CByte(j, i), HEX);
    }
  }
  Serial.print('\n');
}

void writeNaviChip(String data){
  int space = data.indexOf(" ");
  int startIndex = data.substring(0, space).toInt();
  data = data.substring(space + 1, data.length());
  for(int i = 0; i < data.length() / 2; i++){
    int place = startIndex + i;
    int offset = place / 256;
    if(offset > 0) place -= offset;
    place = place - (255 * offset);
    if(place > 255) place = place - 256;
    if(place < 0) place = 256 + place;
    int value = hex2int(data.substring(i * 2, (i * 2) +2));
    writeI2CByte(offset, place, value);
    delay(1);
  }
  Serial.println("Data written");
}

void writeI2CByte(int offset, byte data_addr, byte data){
  Wire.begin();
  Wire.beginTransmission(80 + offset);
  Wire.write(data_addr);
  Wire.write(data);
  Wire.endTransmission();
  Wire.end();
}

byte readI2CByte(int offset, byte data_addr){
  Wire.begin();
  byte data = NULL;
  Wire.beginTransmission(80 + offset);
  Wire.write(data_addr);  
  Wire.endTransmission();
  Wire.requestFrom(80 + offset, 1);
  if(Wire.available()){
    data = Wire.read();
  }
  Wire.end();
  return data;
}

int hex2int(String str)
{
    return (convertSingleHex(str.charAt(0)) * 16) + convertSingleHex(str.charAt(1));
}

int convertSingleHex(char ch){
  if (ch >= '0' && ch <= '9')
      return ch - '0';
  if (ch >= 'A' && ch <= 'F')
      return ch - 'A' + 10;
  if (ch >= 'a' && ch <= 'f')
      return ch - 'a' + 10;
  return -1;
}
