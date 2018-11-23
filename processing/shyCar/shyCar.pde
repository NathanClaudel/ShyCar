// Processing UDP example to send and receive binary data
// press f to toggel between LED flickering twice per second or not
// the LED will illuminate when any other key is held down and
// turn back off when the key is released.

import hypermedia.net.*;
import g4p_controls.*;

UDP udp; // define the UDP object

String ip = "192.168.43.92"; // the remote IP address
int port = 8888; // the destination port

GCustomSlider slider;

volatile color backgroundColor = color(0, 0, 0);

void setup() 
{
  udp = new UDP( this, 8888 ); // create a new datagram connection on port 8888
  //udp.log( true ); // <- printout the connection activity
  udp.listen( true ); // and wait for incoming message
  
  size(400, 600);
  slider  =  new  GCustomSlider(this,  50,  300,  300,  100,  null);
  slider.setShowDecor(false, true,  true,  true);
  slider.setNbrTicks(10);
  slider.setLimits(0, 0,  100);
  

}

void draw()
{
  background(backgroundColor);
  textSize(32);
  text("ShyCar", 150, 100);
  text("speed :", 50, 300); 
  fill(250, 250, 250);
}

void keyPressed() {
  
  byte[] message = new byte[2];
  
  int speed = slider.getValueI();
  
  if (key == 'z')
  {
      message[0] = (byte) speed;
      message[1] = 0;
  }
  else if(key == 's')
  {
      message[0] = (byte) -speed;
      message[1] = 0;
  }
  else if(key == 'q')
  {
      message[0] = (byte) speed;
      message[1] = -100;
  }
  else if(key == 'd')
  {
      message[0] = (byte) speed;
      message[1] = 100;
  }
  udp.send(message, ip , port);
}

void keyReleased()
{
  byte[] message = new byte[2];
  message[0] = 0;
  message[1] = 0;
  udp.send(message, ip , port);
}

void receive( byte[] data ) 
{
  if(data[0] == 'n')
  {
    backgroundColor = color(0,0,0);
  }
  else
  {
    backgroundColor = color(255,255,255);
  }
}
