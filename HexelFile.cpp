/*
  Design and created by Blascarr

  HexelFile
  Name    : Blascarr
  Description: HexelFile.h
  version : 1.0

  PixelArt graphics library for TFT Displays based on Hexels format to draw with several grid frames.
  The library use different polygons in order to stablish different grids to draw in pixel format:

  HexelFile interprets the hexel format of csv files provide on "Hexels" Program with the following order.

  #Hexel data: (column), (row), (R), (G), (B), (A)
  
  Blascarr invests time and resources providing this open source code like some other libraries, please
  respect the job and support open-source hardware.
  
  **
  Written by Adrian for Blascarr
*/

#include <hexelfile.h>

#include <string.h>

const uint8_t hexelfile::maxFilenameLen = FILE_MAX_FILENAME_LEN;

hexelfile::hexelfile(const char* filename, uint8_t mode, bool caseSensitive){
	if (strlen(filename) <= maxFilenameLen)
		strcpy(_filename, filename);
	else
	_filename[0] = '\0';
	_mode = mode;
	_caseSensitive = caseSensitive;
}

hexelfile::hexelfile(String filename, uint8_t mode, bool caseSensitive){

  filename.toCharArray( _filename  , maxFilenameLen);  
  _mode = mode;
  _caseSensitive = caseSensitive;
}

bool hexelfile::validate(char* buffer, size_t len) const
{
  uint32_t pos = 0;
  error_t err;
  while ((err = readLine(_file, buffer, len, pos)) == errorNoError)
    ;
  if (err == errorEndOfFile) {
    _error = errorNoError;
    return true;
  }
  else {
    _error = err;
    return false;
  }
}

hexel hexelfile::readln(){
    hexel h;
		char caracter = hexelfile::_file.peek();

		if (hexelfile::isCommentChar(caracter)){
      do {
        caracter = hexelfile::_file.read();
        hexelfile::pos++;
      } while (!hexelfile::isCRLF(caracter));
      //Serial.println("Salto para alante");
      hexelfile::_file.read();
      hexelfile::_nline++;
      return h;
		};

    h = hexelfile::readhexel();
    
    //Debug Hexel
    /*Serial.print("Column: ");
    Serial.println(h.column);
    Serial.print("Row: ");
    Serial.println(h.row);
    Serial.print("R: ");
    Serial.println(h.R);
    Serial.print("G: ");
    Serial.println(h.G);
    Serial.print("B: ");
    Serial.println(h.B);
    Serial.print("A: ");
    Serial.println(h.A);
    Serial.println("");*/
    //End Debug

    while (hexelfile::isCRLF(hexelfile::_file.peek())){
      caracter = hexelfile::_file.read();
    } 

    hexelfile::_nline++;
    return h;
};

long hexelfile::readnumber(){

  char caracter;
  long number=0;

  do {
    caracter = hexelfile::_file.read();
    number = number*10+  (caracter-'0');  
  } while (hexelfile::isnumber(hexelfile::_file.peek()));
  //Serial.println(number);
  return number;

}

hexel hexelfile::readhexel(){
    char caracter;
    int nnum=0;
    //leer hasta fin de linea
    //Leer un numero por cada espacio...
    //#Hexel data: (column), (row), (R), (G), (B), (A)
    hexel h;

    do{
      caracter = hexelfile::_file.peek();
      if (hexelfile::isnumber(caracter)){
        //hexelfile::_file.read();
        //caracter = hexelfile::_file.peek();
        long num = hexelfile::readnumber();
        nnum++;
        switch (nnum) {
          case 1:
            h.column = num;
          break;

          case 2:
            h.row = num;
          break;

          case 3:
            h.R = num;
          break;

          case 4:
            h.G = num;
          break;

          case 5:
            h.B = num;
          break;
          
          case 6:
            h.A = num;
          break;

        }
        h.color = (h.R<<16)|(h.G<<8)|h.B;
        //Establecer una posición adicional al paso del numero
      }
      caracter = hexelfile::_file.read();
    } while (!hexelfile::isCRLF(caracter));
    return h;
}

hexelfile::error_t hexelfile::readLine(File &file, char *buffer, size_t len, uint32_t &pos)
{
  if (!file)
    return errorFileNotOpen;
 
  if (len < 3) 
    return errorBufferTooSmall;

  if (!file.seek(pos))
    return errorSeekError;

  size_t bytesRead = file.read(buffer, len);
  if (!bytesRead) {
    buffer[0] = '\0';
    //return 1; // done
    return errorEndOfFile;
  }
  
  for (size_t i = 0; i < bytesRead && i < len-1; ++i) {
    // Test for '\n' with optional '\r' too
    // if (endOfLineTest(buffer, len, i, '\n', '\r')
	
    if (buffer[i] == '\n' || buffer[i] == '\r') {
      char match = buffer[i];
      char otherNewline = (match == '\n' ? '\r' : '\n'); 
      // end of line, discard any trailing character of the other sort
      // of newline
      buffer[i] = '\0';
      
      if (buffer[i+1] == otherNewline) ++i;
      pos += (i + 1); // skip past newline(s)
      //return (i+1 == bytesRead && !file.available());
      return errorNoError;
    }
  }
  if (!file.available()) {
    // end of file without a newline
    buffer[bytesRead] = '\0';
    // return 1; //done
    return errorEndOfFile;
  }
  
  buffer[len-1] = '\0'; // terminate the string
  return errorBufferTooSmall;
}


bool hexelfile::isCommentChar(char c)
{
  return ( c == '#' || c == '//');
}

bool hexelfile::iscomma(char c)
{
  return ( c == ',');
}

bool hexelfile::isnumber(char c)
{
  return ( (c-'0') >= 0  && (c-'0') <= 9);
}

bool hexelfile::isLF(char c)
{
  return ( c == '\n'  );
}

bool hexelfile::isCR(char c)
{
  return ( c == '\r' );
}

bool hexelfile::isCRLF(char c)
{
  return ( c == '\n' ||  c == '\r' );
}

bool hexelfile::readcommentLine(char c)
{
  return ( c == '\n' ||  c == '\r' ||  c == ' '  );
}

bool hexelfile::isspace(char c)
{
  return ( c == ' ' );
}


char* hexelfile::skipWhiteSpace(char* str)
{
  char *cp = str;
  while (isspace(*cp))
    ++cp;
  return cp;
}

void hexelfile::removeTrailingWhiteSpace(char* str)
{
  char *cp = str + strlen(str) - 1;
  while (cp >= str && isspace(*cp))
    *cp-- = '\0';
}

long hexelfile::getLine() 
{
  return hexelfile::_nline;
}

bool hexelfile::getCaseSensitive(void) const
{
  return _caseSensitive;
}

void hexelfile::setCaseSensitive(bool cs)
{
  _caseSensitive = cs;
}

hexelfilestate::hexelfilestate()
{
  readLinePosition = 0;
  getValueState = funcUnset;
}
