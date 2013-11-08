/* 7 segment display table (index = desired value)
 Contains: 0, 1, 2, ..., 9, A, b, c, ..., G
 */
const byte dsply[] = {
  B00111111, 
  B00000110, 
  B01011011, 
  B01001111, 
  B01100110, 
  B01101101, 
  B01111101, 
  B00000111, 
  B01111111, 
  B01100111, 
  B01110111, 
  B01111100, 
  B01011000, 
  B01011110, 
  B01111001, 
  B01110001, 
  B00111101};

/* note table.  This is an arbitrary diatonic (whole note) scale arranged such that adjacent tones
 correspond to adjacent keys in the horizontal direction (e.g. asdf).  
 Octaves are available in the vertical direction. (e.g. yhb)
 */
const int notes[] = {
  440, 
  349, 
  294, 
  523, 
  1046, 
  587, 
  659, 
  698, 
  1760, 
  784, 
  880, 
  988, 
  440, 
  392, 
  1976, 
  2094, 
  880, 
  1174, 
  494, 
  1318, 
  1568, 
  330, 
  988, 
  262, 
  1396, 
  247};

/* 7 segment "swirl" table
 Makes a loop of the outer segments of the display 
 (hence only six values used).
 Clockwise if index increases, else counterclockwise.
*/
const byte swrl[] = {
  B00000001, 
  B00000010, 
  B00000100, 
  B00001000, 
  B00010000, 
  B00100000, 
  B01000000};
