# TFTHexel
PixelArt graphics library for TFT Displays based on Hexels format to draw with several grid frames.

The library use different polygons in order to stablish different grids to draw in different formats:
<ul>
<li> Hexels</li>
<li> Trixels</li>
<li> Pixels</li>
</ul>

This differents interpretations on graphics allow us to create hexel in order to create 3D models on a 2D TFT Display with a different interpretation on depth figures.

This library need also:
<ul>
  <li>Adafruit_GFX.h</li>
  <li>Adafruit_ST7735.h</li
</ul>

Arduino Board read image information from SD card with a <a href="examples/hexelSD">.csv</a> exported from <a href="http://www.marmoset.co/hexels">Marmoset - Hexels 2</a> program.


<p align="center">
  <img  src="img/Hexel1.png" width="200"/>
  <img  src="img/Hexel2.png" width="200"/>
  <img  src="img/Hexel3.png" width="200"/>
  <img  src="img/Hexel4.png" width="200"/>
</p>

Hexel grid class is based on geometric triangles ordered in columns and rows with the following structure: 

<p align="center">
  <img  src="img/HexelGridPoints.jpg" width="250"/>
  <img  src="img/Hexel4Grid.jpg" width="250"/>
  <img  src="img/Hexel4Grid_Xtended.jpg" width="250"/>
</p>

<p align="center">
  <img  src="img/Hexel4Grid_module.jpg" width="250"/>
  <img  src="img/Hexel4Grid_Sectors.jpg" width="250"/>
  <img  src="img/Hexel4Grid_triangles.jpg" width="250"/>
</p>

![Temple Aqualung](img/Temple_Aqualung.png)

<p align="center">
  <img  src="img/Earth.png" width="250"/>
  <img  src="img/DinoHexel.png" width="250"/>
  <img  src="img/LagoonCastle.png" width="250"/>
</p>

This library has been tested with Arduino Esplora and a TFT display. 

<p>
#define SD_CS    8  // Chip select line for SD card
<br>
#define TFT_CS  7  // Chip select line for TFT display
<br>
#define TFT_DC   0  // Data/command line for TFT
<br>
#define TFT_RST  1  // Reset line for TFT (or connect to +5V)
</p>


If you use another board, you can change your pins in <b>config.h</b>.

![Creatice Commons Licence](img/icon_cc.png)
