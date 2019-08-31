import processing.serial.*; // import serial library

Serial mySerial;

Cube myCube;

HScrollbar hs1;
HScrollbar hs2;
HScrollbar hs3;

Button btn1;
Button btn2;
Button btn3;
Button btn4;
Button btn5;

Button [] btns;

// Serial variables
String serialData = null;

// view variables
String selectedView;
String lastSelectedView;

// attitude variables
float yaw = 0;
float pitch = 0;
float roll =0 ;

void setup(){
  size(1000, 600, P3D);
  colorMode(RGB, 1); 
  noStroke();
  
  // Serial
  String myPort = mySerial.list() [1];
  mySerial = new Serial(this,myPort,9600);
  
  myCube = new Cube();
  
  myCube.updateCenter(width/2,height/2,0);
  
  int btnY = 100;
  int btnHeight = 50;
  int btnWidth = 150;
  btn1 = new Button(width - btnWidth - 20, btnY, btnWidth, btnHeight, "Top", 15, "top");
  btn2 = new Button(width - btnWidth - 20, btnY + 1 * (btnHeight + 10), btnWidth, btnHeight, "Front", 15, "front");
  btn3 = new Button(width - btnWidth - 20, btnY + 2 * (btnHeight + 10), btnWidth, btnHeight, "Rear", 15, "rear");
  btn4 = new Button(width - btnWidth - 20, btnY + 3 * (btnHeight + 10), btnWidth, btnHeight, "Right Side", 15, "rightSide");
  btn5 = new Button(width - btnWidth - 20, btnY + 4 * (btnHeight + 10), btnWidth, btnHeight, "Left Side", 15, "leftSide");
  
  btns = new Button [5];
  
  btns[0] = btn1;
  btns[1] = btn2;
  btns[2] = btn3;
  btns[3] = btn4;
  btns[4] = btn5;
  
  btn1.active = true;
  selectedView  = btn1.activeValue;
  lastSelectedView = btn1.activeValue;
  
  myCube.setView(selectedView);
  
  hs1 = new HScrollbar(20,height - 20, 100, 16, 16);
  hs2 = new HScrollbar(20,height - 40, 100, 16, 16);
  hs3 = new HScrollbar(20,height - 60, 100, 16, 16);
}

void draw(){
  background(0);
  
  btn1.draw();
  btn2.draw();
  btn3.draw();
  btn4.draw();
  btn5.draw();
  btn1.update();
  btn2.update();
  btn3.update();
  btn4.update();
  btn5.update();
  
  hs1.display();
  hs1.update();
  hs2.display();
  hs2.update();
  hs3.display();
  hs3.update();
  
  myCube.view = selectedView;
  
  myCube.drawAxes();
  
  textSize(15);
  fill(200,200,100);
  
  text("View: ", 50, 50);
  text(myCube.getView(), 100, 50);
  
  text("Yaw:", 145, height - 20);
  text(nfc((myCube.getYaw() * 180)/PI,2) + " deg", 205, height - 20);
  text("Pitch:", 145, height - 40);
  text(nfc((myCube.getPitch() * 180)/PI,2) + " deg", 205, height - 40);
  text("Roll:", 145, height - 60);
  text(nfc((myCube.getRoll() * 180)/PI,2) + " deg", 205, height - 60);
  
  if(mySerial.available() > 0){
    
    serialData = mySerial.readStringUntil(13);
    
    if(serialData != null){
      int p = 0, r = 0, y = 0;
      for(int i = 0; i < serialData.length(); i++){
        if(serialData.charAt(i) == 'P') { p = i; }
        if(serialData.charAt(i) == 'R') { r = i; }
        if(serialData.charAt(i) == 'Y') { y = i; }
      }
      if(y > 0 && p > 0 && r > 0){
        pitch = (float(serialData.substring(p+1,r)) * PI ) / 180;
        roll = (float(serialData.substring(r+1,y)) * PI ) / 180;
        yaw = (float(serialData.substring(y+1,serialData.length())) * PI ) / 180;
      }
      println(serialData);
    }
  } else {
    yaw =   ( hs1.getPos() - hs1.sposMin * hs1.ratio - 50 ) * 0.1;
    pitch = ( hs2.getPos() - hs2.sposMin * hs2.ratio - 50 ) * 0.01;
    roll =  ( hs3.getPos() - hs3.sposMin * hs3.ratio - 50 ) * 0.01;
  }
  myCube.updateAttitude(yaw,pitch,roll);
 
  myCube.drawCube();
}

// monitors when the mouse is released after being pressed. Used to switch between waves to be displayed
void mouseReleased()
{
  // determine which view to display by finding the active button that represents it
  // loop through the buttons
  for(int i = 0; i < btns.length; i++)
  {
    // if button is active and its value is different than the previous active value
    if(btns[i].active && btns[i].activeValue != selectedView)
    {
       selectedView = btns[i].activeValue;
       int lastBtn = 0;
       for(int j = 0; j < btns.length; j++){
         if(btns[j].activeValue == lastSelectedView){
           lastBtn = j;
         }
       }
       btns[lastBtn].active = false; // deactivate previously active button
       lastSelectedView = selectedView; // update the lastActive variable. Used in next evaluation.
       break; // exit the loop
    }
  }
}