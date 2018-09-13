/////////////////////////////////////////////
///This code was written by Joshua Stevens
///on 9/5/18 to display a traffic light.
///
///Code is written for Arduino mini connected
///to 3 relay switched toggle the lights.
/////////////////////////////////////////////
//#defines
#define RedLight 3
#define YellowLight 5
#define GreenLight 7

//Enums
enum Color {Red, Yellow, Green, Off};

//Variables
unsigned elapsedTime = 0;
bool on = true;                  //<----------set to false so if we reset (power goes out) we don't turn on when nobody is at the shop
Color currentColor;
Color newColor;


//Setup
void setup() 
{
  //Set the lights to output
  pinMode(RedLight, OUTPUT);
  pinMode(YellowLight, OUTPUT);
  pinMode(GreenLight, OUTPUT);
  //default the light to green
  currentColor = Green;
  newColor = Green;
  digitalWrite(GreenLight, HIGH);
  Serial.begin(9600);
}


//Loop
void loop() 
{
  if (on)
  {
    //change light color based on time
    //Green (0 - 10 seconds)
    if (elapsedTime <= 10000)
    {
      //check to see if we should flash green
      if (elapsedTime > 5000)
      {
        if (elapsedTime % 1000 < 500)
          newColor = Green;
        else
          newColor = Off;
      }
      else
        newColor = Green;      
    }

    //Yellow (10 - 15 seconds)
    else if (elapsedTime > 10000 && elapsedTime <= 15000)
      newColor = Yellow;

    //Red (15 - 30 seconds)
    else
    {
      newColor = Red;
      //reset timer if we have gone over 30 seconds
      if (elapsedTime > 30000)
        elapsedTime = 0;
    }


    //check if we have a new color
    if (newColor != currentColor)
    {
      //switch on the new color
      switch (newColor)
      {
        case Green:
        {
          digitalWrite(RedLight, LOW);
          digitalWrite(GreenLight, HIGH);
          Serial.println("Switching Green");
          break;
        }
        case Yellow:
        {
          digitalWrite(GreenLight, LOW);
          digitalWrite(YellowLight, HIGH);
          Serial.println("Switching Yellow");
          break;
        }
        case Red:
        {
          digitalWrite(YellowLight, LOW);
          digitalWrite(RedLight, HIGH);
          Serial.println("Switching Red");
          break;
        }
        case Off:
        {
          digitalWrite(RedLight, LOW);
          digitalWrite(YellowLight, LOW);
          digitalWrite(GreenLight, LOW);
          Serial.println("Switching Off");
        }
      }
      
      //set the current color
      currentColor  = newColor;
    }

    //add to the timer
    delay(10);
    elapsedTime += 10;
  }

  //TODO check for IR input (Might need to put in a check so that we don't toggle every loop)
  if (false)
  {
    //if already on, turn off
    if (on)
      on = false;
    //if turning on
    else
    {
      on = true;
      elapsedTime = 0;
    }  
  }

}
