/*******************************************
 Sparki Line-following example
 
 Threshold is the value that helps you 
 determine what's black and white. Sparki's 
 infrared reflectance sensors indicate white 
 as close to 900, and black as around 200.
 This example uses a threshold of 700 for 
 the example, but if you have a narrow line, 
 or perhaps a lighter black, you may need to 
 adjust.
********************************************/
//3592 ms for 10cm
//.87 cm/s
#include <Sparki.h> // include the sparki library

  double x = 0;     // left/right directions
  double y = 0;     // forward/backward directions 
  double theta = 0; // initial heading = 0, CW to 360
  double wr = 5.5/2;   // cm
  double ad = 7.5;   // cm
 // double pi = 3.14159265359; //value of pi
  double v;
  double phi;  

void setup() 
{
  double x = 25;
  double t1 = millis();
  sparki.moveForward(x);
  double t2 = millis();
  double t = t2-t1;
  v = x/(t/1000);
  phi = v/wr;
 // sparki.print(v);
 // sparki.updateLCD();
 //calculate the angular rotation (phi) by measuring a 2pi wheel rotation
}

void loop() {
  int threshold = 700;
  int f = 0;
  int l = 0;
  int r = 0;
  //delay(00);
  unsigned long t1 = millis();
  int lineLeft   = sparki.lineLeft();   // measure the left IR sensor
  int lineCenter = sparki.lineCenter(); // measure the center IR sensor
  int lineRight  = sparki.lineRight();  // measure the right IR sensor

  if ( lineCenter < threshold ) // if line is below left line sensor
  {  
    sparki.moveForward(); // move forward
    f = 1;
  }
  else{
    if ( lineLeft < threshold ) // if line is below left line sensor
    {  
      sparki.moveLeft(); // turn left
      l = 1;
    
    }
  
    if ( lineRight < threshold ) // if line is below right line sensor
    { 
      sparki.moveRight(); // turn right
      r = 1;
    }
  }

  sparki.clearLCD(); // wipe the screen
 
  //sparki.updateLCD(); // display all of the information written to the screen

  unsigned long t2 = millis();

  //sparki.print("Delta-t Total = ");
  unsigned long del_t = t2-t1;
  
  delay(100-del_t); // wait 0.1 seconds including code execution
  
  if (f == 1){
    y = y + .1*v*sin(theta);
    x = x + .1*v*cos(theta);
  }
  
  if (l == 1){
    theta = theta - .1*(wr/ad)*(phi+phi);
  }
  
  if (r == 1){
    theta = theta + .1*(wr/ad)*(phi+phi);
  }
    
  sparki.print("X: "); // show left line sensor on screen
  sparki.println(x);
  
  sparki.print("Y: "); // show center line sensor on screen
  sparki.println(y);
  
  sparki.print("Heading: "); // show right line sensor on screen
  sparki.println(theta);
  
  
  //unsigned long t3 = millis();
  //sparki.println(t3-t1);
  sparki.updateLCD();
}
