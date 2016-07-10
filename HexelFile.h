/*
  Design and created by Blascarr

  TFTHexel
  Name    : Blascarr
  Description: TFTHexel.h
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

#ifndef _HEXELFILE_H
#define _HEXELFILE_H
#define FILE_MAX_FILENAME_LEN 26
#define MAX_FILE_LEN 100

#include "SD.h"

/*---------------------------------------------------------------------------------------*/
/*--------------------------------- Hexel Object --------------------------------------*/
/*---------------------------------------------------------------------------------------*/

struct hexel{
	int column;
	int row;
	int R;
	int G;
	int B;
	int A;
	unsigned long color;
};

//This class is used to create the position record of the file every time in methods "readline"
class hexelfilestate;

class hexelfile{
	public:
		long _nline=0;
		enum error_t {
			errorNoError = 0,
			errorFileNotFound,
			errorFileNotOpen,
			errorBufferTooSmall,
			errorSeekError,
			errorSectionNotFound,
			errorKeyNotFound,
			errorEndOfFile,
			errorUnknownError,
		};

		static const uint8_t maxFilenameLen;
		char _filename[FILE_MAX_FILENAME_LEN];
		uint8_t _mode;
		mutable error_t _error;
		mutable File _file;
		bool _caseSensitive;

		//Control position, line number and buffer reading
		
		char buffer[MAX_FILE_LEN];
		unsigned long int pos=0;
		
		hexelfile(const char* filename, uint8_t mode = FILE_READ, bool caseSensitive = false);
		hexelfile(String filename, uint8_t mode = FILE_READ, bool caseSensitive = false);
		
		//Main Methods
		inline bool open(void); // Returns true if open succeeded
		inline void close(void);

		inline bool isOpen(void) const;

		inline error_t getError(void) const;
		inline void clearError(void) const;
		// Get the file mode (FILE_READ/FILE_WRITE)
		inline uint8_t getMode(void) const;

		// Get the filename associated with the hexel file object
		inline const char* getFilename(void) const;
		long getLine();
		bool validate(char* buffer, size_t len) const;

		hexel readln();
		long readnumber();
		hexel readhexel();
		// Utility function to read a line from a file, make available to all
		//static int8_t readLine(File &file, char *buffer, size_t len, uint32_t &pos);
		static error_t readLine(File &file, char *buffer, size_t len, uint32_t &pos);
		static bool isCommentChar(char c);
		static bool iscomma(char c);
		static bool isCRLF(char c);
		static bool isCR(char c);
		static bool isLF(char c);
		static bool isspace(char c);
		static bool isnumber(char c);
		static bool readcommentLine(char c);
		static char* skipWhiteSpace(char* str);
		static void removeTrailingWhiteSpace(char* str);

		bool getCaseSensitive(void) const;
		void setCaseSensitive(bool cs);

	protected:

	private:
		
};

bool hexelfile::open(void)
{
	if (_file) _file.close();
	_file = SD.open(_filename, _mode);
	
	if (isOpen()) {
		_error = errorNoError;
	return true;
	}
	else {
		_error = errorFileNotFound;
	return false;
	}
}

void hexelfile::close(void)
{
  if (_file)
	_file.close();
}

bool hexelfile::isOpen(void) const
{
	return (_file == true);
}

hexelfile::error_t hexelfile::getError(void) const
{
	return _error;
}

void hexelfile::clearError(void) const
{
	_error = errorNoError;
}

uint8_t hexelfile::getMode(void) const
{
	return _mode;
}

const char* hexelfile::getFilename(void) const
{
	return _filename;
}

class hexelfilestate {
	public:
		hexelfilestate();

	private:
		enum {funcUnset = 0,
			funcFindSection,
			funcFindKey,
		};

		uint32_t readLinePosition;
		uint8_t getValueState;

		friend class hexelfile;
};

#endif