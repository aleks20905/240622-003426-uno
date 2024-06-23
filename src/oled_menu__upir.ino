// simple project using Arduino UNO and 128x64 OLED Display to display a menu
// created by upir, 2022
// youtube channel: https://www.youtube.com/upir_upir

// YOUTUBE VIDEO: https://youtu.be/HVHVkKt-ldc

// links from the video:
// Flipper Zero menu - https://docs.flipperzero.one/basics/control#M5BZO
// WOKWI start project progress bar - https://wokwi.com/projects/300867986768527882
// image2cpp - https://javl.github.io/image2cpp/
// 128x64 SSD1306 OLED Display: https://s.click.aliexpress.com/e/_DCKdvnh
// Transparent OLED display: https://s.click.aliexpress.com/e/_Dns6eLz
// Arduino UNO: https://s.click.aliexpress.com/e/_AXDw1h
// Arduino UNO MINI: https://store.arduino.cc/products/uno-mini-le
// Big OLED Display: https://s.click.aliexpress.com/e/_ADL0T9
// Arduino breadboard prototyping shield: https://s.click.aliexpress.com/e/_ApbCwx
// u8g fonts (fonts available for u8g library): https://nodemcu-build.com/u8g-fonts.php
// u8g documentation: https://github.com/olikraus/u8glib/wiki/userreference
// Photopea (online Photoshop-like tool): https://www.photopea.com/
// image2cpp (convert images into C code): https://javl.github.io/image2cpp/
// Push buttons - https://s.click.aliexpress.com/e/_DmXS8B9

// Related videos:
// Arduino Parking Sensor - https://youtu.be/sEWw087KOj0
// Turbo pressure gauge with Arduino and OLED display - https://youtu.be/JXmw1xOlBdk
// Arduino Car Cluster with OLED Display - https://youtu.be/El5SJelwV_0
// Knob over OLED Display - https://youtu.be/SmbcNx7tbX8
// Arduino + OLED = 3D ? - https://youtu.be/kBAcaA7NAlA
// Arduino OLED Gauge - https://youtu.be/xI6dXTA02UQ
// Smaller & Faster Arduino - https://youtu.be/4GfPQoIRqW8

// https://app.clickup.com/9015050982/v/l/li/901505799224


#include <Arduino.h>
#include "U8glib.h"
#include "icons.h"
#include "screenshots.h"
#include "qr_codes.h"


U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0 | U8G_I2C_OPT_NO_ACK | U8G_I2C_OPT_FAST); // Fast I2C / TWI
// U8GLIB_SSD1306_128X64 u8g(13, 11, 8, 9, 10); // SPI connection
// for SPI connection, use this wiring:
// GND > GND
// VCC > 5V
// SCL > 13
// SDA > 11
// RES > 10
// DC > 9
// CS > 8


// 'scrollbar_background', 8x64px
const unsigned char bitmap_scrollbar_background [] PROGMEM = {
  0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 
  0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 
  0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 
  0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x00
};

// 'item_sel_outline', 128x21px
const unsigned char bitmap_item_sel_outline [] PROGMEM = {
  0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 
  0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 
  0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0
};





// ------------------ end generated bitmaps from image2cpp ---------------------------------

int frame = 0;      // frame for the inner part of the icon

const int NUM_ITEMS = 6; // number of items in the list and also the number of screenshots and screenshots with QR codes (other screens)
const int MAX_ITEM_LENGTH = 20; // maximum characters for the item name

const char menu_items [NUM_ITEMS] [MAX_ITEM_LENGTH] = {  // array with item names
  { "Up Volt Lim " }, 
  { "Low Volt Lim" }, 
  { "Up Amp lim" },   
  { "UpSoftAmp lim" },
  { "Low Amp lim" },
  { "history" }
  // { "info" } // RN valtage + amparage + etc separate menu
};
const char menu_items_details [NUM_ITEMS] [MAX_ITEM_LENGTH] = {  // array with item names
  { "Upper Voltage Lim " }, 
  { "Lower Voltage Lim" }, 
  { "Upper Amp lim" },   
  { "Upper softAmp lim" },   
  { "Lower Amp lim" },
  { "in construction..." }
};



int history_selected = 0;
int history_sel_previous; // previous item - used in the menu screen to draw the item before the selected one
int history_sel_next; // next item - used in the menu screen to draw next item after the selected one

const int MAX_HISTORY_LEN = 5;
const char history [MAX_HISTORY_LEN] [20] = {  // array with item names
  { "Amp hight " }, 
  { "Amp low" }, 
  { "unknow err" },   
  { "idk" },   
  { "someting" }
};



int voltage = 190;
int amparage = 10;

bool var_Auto_Manual = true;
int upper_Voltage_Lim = 245;
int lower_Voltage_Lim = 180;
int upper_Amparage_Lim = 15;
int upper_Soft_Amparage_Lim = 11;
int lower_Amparage_Lim =  6;


int second_menu_items [NUM_ITEMS] = {  // array with item names
  upper_Voltage_Lim, 
  lower_Voltage_Lim, 
  upper_Amparage_Lim ,  
  upper_Soft_Amparage_Lim, 
  lower_Amparage_Lim,
  0  // count of errors on the EPROM  len(history)
};
 
// note - when changing the order of items above, make sure the other arrays referencing bitmaps
// also have the same order, for example array "bitmap_icons" for icons, and other arrays for screenshots and QR codes

#define BUTTON_UP_PIN 12 // pin for UP button 
#define BUTTON_SELECT_PIN 8 // pin for SELECT button
#define BUTTON_DOWN_PIN 4 // pin for DOWN button




int button_up_clicked = 0; // only perform action when button is clicked, and wait until another press
int button_select_clicked = 0; // same as above
int button_down_clicked = 0; // same as above

int item_selected = 0; // which item in the menu is selected
int item_sel_previous; // previous item - used in the menu screen to draw the item before the selected one
int item_sel_next; // next item - used in the menu screen to draw next item after the selected one

int current_screen = 0;   // 0 = menu, 1 = screenshot, 2 = qr






char pct[12]; // temporati var to print intgers using itoa()

void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps

  u8g.setColorIndex(1);  // set the color to white


  pinMode(2, INPUT_PULLUP);

  // define pins for buttons
  // INPUT_PULLUP means the button is HIGH when not pressed, and LOW when pressed
  // since it´s connected between some pin and GND
  pinMode(BUTTON_UP_PIN, INPUT_PULLUP); // up button
  pinMode(BUTTON_SELECT_PIN, INPUT_PULLUP); // select button
  pinMode(BUTTON_DOWN_PIN, INPUT_PULLUP); // down button

}


void loop() {

  mainCheck();

  mainMenuLogic();

  secondMenuLogic();

  selectButtonLogic();


  u8g.firstPage(); // required for page drawing mode for u8g library
  do {

    if (current_screen == 0) { // MENU SCREEN

      drawMenu(); //! Draw the main menu
    } 
    else if (current_screen == 1) { // SCREENSHOTS SCREEN
      if(item_selected == 5){
        drawHistory();

      }   
      else { drawVar(); }  // draw selected info 
    }
    //! else if (current_screen == 2) { // QR SCREEN
    //     u8g.drawBitmapP( 0, 0, 128/8, 64, bitmap_qr_codes[item_selected]); // draw qr code screenshot
    // }   

  } while ( u8g.nextPage() ); // required for page drawing mode with u8g library



  // TODO workign animation 
  frame = frame+1;            // increase the frame for the inner part of the icon
  if (frame > 2) {frame = 0;} 
  // TODO workign animation 

  
}

void drawMenu() {
    // selected item background
    u8g.drawBitmapP(0, 22, 128/8, 21, bitmap_item_sel_outline);

    // draw previous item as icon + label
    u8g.setFont(u8g_font_7x14);
    u8g.drawStr(4, 15, menu_items[item_sel_previous]);  // draw the var Name 
    u8g.drawStr(128-28, 15, itoa(second_menu_items[item_sel_previous] , pct, 10)); //! draw the value 
    // u8g.drawBitmapP( 4, 2, 16/8, 16, bitmap_icons[item_sel_previous]); 
    

    // draw selected item as icon + label in bold font
    u8g.setFont(u8g_font_7x14B);    
    u8g.drawStr(4, 15+20+2, menu_items[item_selected]);   
    u8g.drawStr(128-28, 15+20+2, itoa(second_menu_items[item_selected] , pct, 10)); //! draw the value 
    // u8g.drawBitmapP( 4, 24, 16/8, 16, bitmap_icons[item_selected]);  

    // draw next item as icon + label
    u8g.setFont(u8g_font_7x14);     
    u8g.drawStr(4, 15+20+20+2+2, menu_items[item_sel_next]);   
    u8g.drawStr(128-28, 15+20+20+2+2, itoa(second_menu_items[item_sel_next] , pct, 10)); //! draw the value 
    // u8g.drawBitmapP( 4, 46, 16/8, 16, bitmap_icons[item_sel_next]); 

    // draw scrollbar background
    u8g.drawBitmapP(128-8, 0, 8/8, 64, bitmap_scrollbar_background);

    // draw scrollbar handle
    u8g.drawBox(125, 64/NUM_ITEMS * item_selected, 3, 64/NUM_ITEMS); 


    // draw upir logo
    u8g.setFont(u8g_font_4x6);
    if(var_Auto_Manual){ 
      u8g.drawStr(128-16, 15+20+20+2+2+2, "On");  
    }
    else {
      u8g.drawStr(128-16, 15+20+20+2+2+2, "Off"); 
    }
    
}

void drawVar() {


    // draw selected item as icon + label in bold font
    // u8g.setFont(u8g_font_7x14B);    
    // u8g.drawStr(25, 15+20+2, menu_items[item_selected]);   
    // u8g.drawBitmapP( 4, 24, 16/8, 16, bitmap_icons[item_selected]);   

    u8g.setColorIndex(1); // white color

    u8g.setFont(u8g_font_7x14);
    u8g.drawStr(4, 16+16, menu_items_details[item_selected]); 

    // u8g.drawStr(128-26, 16+16, itoa(second_menu_items[item_selected] , pct, 10)); //! draw the value 

   
    u8g.drawStr(4, 16+16+16, itoa(second_menu_items[item_selected] , pct, 10)); 
    // u8g.drawStr(4, 16+16+16, itoa(second_menu_items[item_selected] , pct, 10)); //! draw the value 


    //u8g.setColorIndex(0);                                    // black color      
    //u8g.drawBox(1, 12, 126, 12);                             // rectangle covering the fullscreen background
    u8g.setColorIndex(1);                                      // white color   

    u8g.drawFrame(0, 5, 128, 15);
    //u8g.drawBox(2,5+2, map(progress, 150, 300, 0, 124), 10);    // actual gauge fill, remapped from 0-1023 to 0-124 (maximum rectangle size)
    




    // draw the animated inside part of the icon
    u8g.drawBitmapP(128-16, 64-16, 16/8, 9, epd_bitmap_allArray[frame]);   

  


    u8g.setFont(u8g_font_4x6);
    if(var_Auto_Manual){  u8g.drawStr(128-16, 15+20+20+2+2+2, "On");  }
    else { u8g.drawStr(128-16, 15+20+20+2+2+2, "Off"); }
  
}

void drawInfo(){}

void drawHistory(){
  // selected item background
  u8g.drawBitmapP(0, 22, 128/8, 21, bitmap_item_sel_outline);

  // draw previous item as icon + label
  u8g.setFont(u8g_font_7x14);
  u8g.drawStr(4, 15, history[history_sel_previous]);  // draw the var Name 
  
  // draw selected item as icon + label in bold font
  u8g.setFont(u8g_font_7x14B);    
  u8g.drawStr(4, 15+20+2, history[history_selected]);   

  // draw next item as icon + label
  u8g.setFont(u8g_font_7x14);     
  u8g.drawStr(4, 15+20+20+2+2, history[history_sel_next]);   
  // draw scrollbar background
  u8g.drawBitmapP(128-8, 0, 8/8, 64, bitmap_scrollbar_background);

  // draw scrollbar handle
  u8g.drawBox(125, 64/MAX_HISTORY_LEN * history_selected, 3, 64/MAX_HISTORY_LEN); 

  

}

void mainMenuLogic(){
  if (current_screen == 0) { // MENU SCREEN  //TODO replace the hole logic with rotary encoder

      // up and down buttons only work for the menu screen
      if ((digitalRead(BUTTON_UP_PIN) == LOW) && (button_up_clicked == 0)) { // up button clicked - jump to previous menu item
        item_selected = item_selected - 1; // select previous item
        button_up_clicked = 1; // set button to clicked to only perform the action once
        if (item_selected < 0) { // if first item was selected, jump to last item
          item_selected = NUM_ITEMS-1;
        }
      }
      else if ((digitalRead(BUTTON_DOWN_PIN) == LOW) && (button_down_clicked == 0)) { // down button clicked - jump to next menu item
        item_selected = item_selected + 1; // select next item
        button_down_clicked = 1; // set button to clicked to only perform the action once
        if (item_selected >= NUM_ITEMS) { // last item was selected, jump to first menu item
          item_selected = 0;
          }
      } 

      if ((digitalRead(BUTTON_UP_PIN) == HIGH) && (button_up_clicked == 1)) { // unclick  
        button_up_clicked = 0;
      }
      if ((digitalRead(BUTTON_DOWN_PIN) == HIGH) && (button_down_clicked == 1)) { // unclick  
        button_down_clicked = 0;
      }

  } //TODO replace the hole logic with rotary encoder

}



void secondMenuLogic(){

  if (current_screen == 1 && item_selected == 5) { // MENU SCREEN  //TODO replace the hole logic with rotary encoder

    if ((digitalRead(BUTTON_UP_PIN) == LOW) && (button_up_clicked == 0)) { // up button clicked - jump to previous menu item
      history_selected = history_selected - 1; // select previous item
      button_up_clicked = 1; // set button to clicked to only perform the action once

      if (history_selected < 0) { history_selected = MAX_HISTORY_LEN-1; }
    }
    else if ((digitalRead(BUTTON_DOWN_PIN) == LOW) && (button_down_clicked == 0)) { // down button clicked - jump to next menu item
      history_selected = history_selected + 1; // select next item
      button_down_clicked = 1; // set button to clicked to only perform the action once

      if (history_selected >= MAX_HISTORY_LEN) { history_selected = 0; }
    } 

    if ((digitalRead(BUTTON_UP_PIN) == HIGH) && (button_up_clicked == 1)) {   button_up_clicked = 0; }// unclick
    if ((digitalRead(BUTTON_DOWN_PIN) == HIGH) && (button_down_clicked == 1)) { button_down_clicked = 0; } // unclick   

  } //TODO replace the hole logic with rotary encoder
  

  if (current_screen == 1) { //TODO replace the hole logic with rotary encoder

    // up and down buttons only work for the menu screen
    if ((digitalRead(BUTTON_UP_PIN) == LOW) && (button_up_clicked == 0)) { // up button to change value

      second_menu_items[item_selected] ++;

      button_up_clicked = 1; // set button to clicked to only perform the action once

      // if (item_selected < 0) { // if first item was selected, jump to last item
      //   item_selected = NUM_ITEMS-1;
      // }


    }
    else if ((digitalRead(BUTTON_DOWN_PIN) == LOW) && (button_down_clicked == 0)) { // down button to change value

      // item_selected = item_selected + 1; // select next item
      second_menu_items[item_selected] --;
      
     
      button_down_clicked = 1; // set button to clicked to only perform the action once

      // if (item_selected >= NUM_ITEMS) { // last item was selected, jump to first menu item
      //   item_selected = 0;
      // }

    } 

    if ((digitalRead(BUTTON_UP_PIN) == HIGH) && (button_up_clicked == 1)) { button_up_clicked = 0; }
    if ((digitalRead(BUTTON_DOWN_PIN) == HIGH) && (button_down_clicked == 1)) { button_down_clicked = 0; }

  } //TODO replace the hole logic with rotary encoder


}

void selectButtonLogic(){

  if ((digitalRead(BUTTON_SELECT_PIN) == LOW) && (button_select_clicked == 0)) { // select button clicked, jump between screens
    button_select_clicked = 1; // set button to clicked to only perform the action once
    if (current_screen == 0) {current_screen = 1;} // menu items screen --> screenshots screen
    //!  else if (current_screen == 1) {current_screen = 2;} // screenshots screen --> qr codes screen
    else {current_screen = 0;} // qr codes screen --> menu items screen
  }
  if ((digitalRead(BUTTON_SELECT_PIN) == HIGH) && (button_select_clicked == 1)) { button_select_clicked = 0; }// unclick

  // set correct values for the previous and next items
  item_sel_previous = item_selected - 1;
  if (item_sel_previous < 0) {item_sel_previous = NUM_ITEMS - 1;} // previous item would be below first = make it the last
  item_sel_next = item_selected + 1;  
  if (item_sel_next >= NUM_ITEMS) {item_sel_next = 0;} // next item would be after last = make it the first


  // set correct values for the previous and next items
  history_sel_previous = history_selected - 1;
  if (history_sel_previous < 0) {history_sel_previous = MAX_HISTORY_LEN - 1;} // previous item would be below first = make it the last
  history_sel_next = history_selected + 1;  
  if (history_sel_next >= MAX_HISTORY_LEN) {history_sel_next = 0;} // next item would be after last = make it the first

}

unsigned long ampHigherStartTime = 0;
unsigned long ampSoftHigherStartTime = 0;
unsigned long ampLowerStartTime = 0;
unsigned long voltageHigherStartTime = 0;
unsigned long voltageLowerStartTime = 0;

const unsigned long timeThreshold = 5000;
const unsigned long softTimeThreshold = 10000;

void mainCheck(){
  var_Auto_Manual = digitalRead(2) == HIGH;
  if (var_Auto_Manual) { // ##################checks only when in auto mode################## 

    if (checkAmpHigher())     { Serial.print("amp higher "); }
    if (checkSoftAmpHigher()) { Serial.print("soft amp higher "); }
    if (checkAmpLower())      { Serial.print("amp lower "); }
    if (checkVoltageHigher()) { Serial.print("voltage higher "); }
    if (checkVoltageLower())  { Serial.print("voltage lower "); }





  } // ##################checks only when in auto mode################## 

  else{ // ##################checks only when in manual mode################## 

  }// ##################checks only when in manual mode################## 

  // ##################imporntant check that happens all the time################## 

  // ##################imporntant check that happens all the time################## 
}

bool checkAmpHigher() {
  if (amparage > second_menu_items[2]) {
    if (ampHigherStartTime == 0) { ampHigherStartTime = millis(); } 
    
    else if (millis() - ampHigherStartTime >= timeThreshold) {
      ampHigherStartTime = 0; // Reset the timer // todo can remove it to get all the panic all the time 
      return true;
    }
  }
  else { ampHigherStartTime = 0; } // Reset the timer if condition is not met
  return false;
}

bool checkSoftAmpHigher() {
  if (amparage > second_menu_items[3]) {
    if (ampSoftHigherStartTime == 0) { ampSoftHigherStartTime = millis(); } 
    
    else if (millis() - ampSoftHigherStartTime >= softTimeThreshold) {
      ampSoftHigherStartTime = 0; // Reset the timer // todo can remove it to get all the panic all the time 
      return true;
    }
  }
  else { ampSoftHigherStartTime = 0; } // Reset the timer if condition is not met
  return false;
}

bool checkAmpLower() {
  if (amparage < second_menu_items[4]) {
    if (ampLowerStartTime == 0) { ampLowerStartTime = millis(); }
    
    else if (millis() - ampLowerStartTime >= timeThreshold) {
      ampLowerStartTime = 0; // Reset the timer // todo can remove it to get all the panic all the time 
      return true;
    }
  } 
  else { ampLowerStartTime = 0; } // Reset the timer if condition is not met
  return false;
}

bool checkVoltageHigher() {
  if (voltage > second_menu_items[0]) {
    if (voltageHigherStartTime == 0) { voltageHigherStartTime = millis(); }
    
    else if (millis() - voltageHigherStartTime >= timeThreshold) {
      voltageHigherStartTime = 0; // Reset the timer // todo can remove it to get all the panic all the time 
      return true;
    }
  } 
  else { voltageHigherStartTime = 0; } // Reset the timer if condition is not met
  return false;
}

bool checkVoltageLower() {
  if (voltage < second_menu_items[1]) {
    if (voltageLowerStartTime == 0) { voltageLowerStartTime = millis(); }
    
    else if (millis() - voltageLowerStartTime >= timeThreshold) {
      voltageLowerStartTime = 0; // Reset the timer // todo can remove it to get all the panic all the time 
      return true;
    }
  } 
  else { voltageLowerStartTime = 0; } // Reset the timer if condition is not met
  return false;
}



