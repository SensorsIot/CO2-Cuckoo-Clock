#include <DFRobotDFPlayerMini.h>

DFRobotDFPlayerMini myDFPlayer;

int numberFiles;

void printDetail(uint8_t type, int value) {
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}

void waitFinish() {
  while (!myDFPlayer.available()) {
    delay(100);
  }
  Serial.println();
  printDetail(myDFPlayer.readType(), myDFPlayer.read());
  while (!myDFPlayer.available()) {
    delay(100);
  }
  while (myDFPlayer.readType() != DFPlayerPlayFinished) printDetail(myDFPlayer.readType(), myDFPlayer.read());
}

void playFile(int number) {
  if (number > myDFPlayer.readFileCounts()){
    number = myDFPlayer.readFileCounts();
    Serial.println("File not available");
  }
  myDFPlayer.play(number);
  waitFinish();
}

void DFPlayerInit() {
  Serial2.begin(9600);
  delay(1000);
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  while (!myDFPlayer.begin(Serial2)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    delay(1000);
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.volume(20);  //Set volume value. From 0 to 30
}
