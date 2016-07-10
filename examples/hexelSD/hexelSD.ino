
#include <Adafruit_GFX.h>
#include <HexelFile.h>
#include <TFTHexel.h>
#include <SPI.h>
#include <SD.h>
#include <Esplora.h>

#define SD_CS    8  // Chip select line for SD card
#define TFT_CS  7  // Chip select line for TFT display
#define TFT_DC   0  // Data/command line for TFT
#define TFT_RST  1  // Reset line for TFT (or connect to +5V)

int hexelcount = 0;
int previousBtn = 0;
//Non Blocking graphics
long previousMillis = 0;  //Reference Millis
long frame_time=300;  

#define maxhexelname 4

String nameHexel[maxhexelname+1] = {
  "Robot1.csv",
  "Robot2.csv",
  "Spiral.csv",
  "Robot4.csv",
  "ramskull.csv"
};
tfthexel tftHexel = tfthexel();

hexel  line;
void setup() {
  tftHexel.initR(0x00); 
  tftHexel.fillScreen(0x000000);
  tftHexel.initEsplora();
  tftHexel.setRotation(0);
  //tftHexel.grid_c(10);

  tftHexel.print("Initializing SD");

  if (!SD.begin(SD_CS)) {
    tftHexel.setCursor(0, 15);
    tftHexel.println("Card failed");
    // don't do anything more:
    return;
  }
  tftHexel.setCursor(0, 15);
  tftHexel.println("card initialized.");
}

void loop() {
  int buttonDown = Esplora.readButton(SWITCH_DOWN);
  int buttonUp = Esplora.readButton(SWITCH_UP);
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis > frame_time) {
    previousMillis = currentMillis;
    
    if(buttonUp == LOW){
      hexelcount++;
    }
    if(buttonDown == LOW){
      hexelcount--;
    }
    if (hexelcount > maxhexelname )hexelcount = 0;
    if (hexelcount < 0 )hexelcount = maxhexelname;
      
    if (previousBtn != hexelcount){
      previousBtn = hexelcount;

      hexelfile filehex = hexelfile(nameHexel[hexelcount]);
      
      if (!filehex.open()) {
        tftHexel.setCursor(0, 30);
        tftHexel.print("File not readed: ");
      } else {
        tftHexel.setCursor(0, 30);
        tftHexel.println("File readed: ");
        tftHexel.setCursor(0, 45);
        tftHexel.println(filehex.getFilename());
      }
      tftHexel.setCursor(0, 60);
      tftHexel.fillScreen(ST7735_WHITE);
      line = filehex.readln();
      line= filehex.readln();
      line= filehex.readln();
      line= filehex.readln();
      while (filehex._file.available() > 1) {
        line= filehex.readln();
        //Serial.println(line.column);
        //Serial.println(line.row);
        //Serial.println(line.R);
        //Serial.println(line.G);
        //Serial.println(line.B);
        if (line.A>0){
          tftHexel.drawhexel(line.column,line.row,line.color);
        }
        
      };
      
      filehex.close();
    }
  }
}

