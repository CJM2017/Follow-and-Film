//====================================================================================================
//                                          Functions
//====================================================================================================

/* WHat will the output actually be?
   DO we need to map every thing to 0-255 range in order to have a proper analogWrite?
*/



//====================================================================================================
//                                           Altitude
//====================================================================================================

void altPIDloop()
{
  altError = currentAltitude - setAltitude;
  if(altError < 0)
  {
    altError = map(altError,-200,0,1500,1000);                                    // What do we even use for our error range?!?!                         
  }
  else
  {
    altError = map(altError,0,200,1500,2000);
  }
  
  if(abs(altError) < 30)                                                      // If the magnitude of the distance is larger than 30 meters.
    {
      altPID.SetTunings(AltConsKp,AltConsKi,AltConsKd);
    }
    else
    {
      altPID.SetTunings(AltAggKp,AltAggKi,AltAggKd);
    }
    
    altPID.Compute();
    throttle.writeMicroseconds(throttleOut);                                    // PWM Control ouput sent to pin 13, THROTTLE.
}

//====================================================================================================
//                                              Yaw  
//====================================================================================================
void yawPIDloop()
{                                                                  // Does the compss even output negative values.
  headingError = targetHeading - currentHeading;                   // CurrentHeading will come from the BN0055 When setup
  if((headingError > 0) && (headingError <= 180))
  {
    float hError = map(headingError,0,180,1500,2000);                      // Want to turn right.
  }
  else if((headingError > 0) && (headingError > 180))
  {
   float hError = map(headingError,181,360,1500,1000);                      // Want to turn left
  }
  else if((headingError < 0) && (headingError <= 180))
  {
    float hError = map(headingError,181,360,1500,1000);                     // Want to turn left
  }
  else
  {
    float hError = map(headingError,0,180,1500,2000);                     // Want to turn right.
  }

  
  if(abs(headingError) < 20)                                       // If the magnitude of the error is less than 20 deg.
    {
      altPID.SetTunings(AltConsKp,AltConsKi,AltConsKd);
    }
    else
    {
      altPID.SetTunings(AltAggKp,AltAggKi,AltAggKd);
    }
    
    altPID.Compute();
    yaw.writeMicroseconds(yawOut);                                    // PWM Control ouput sent to pin 13, THROTTLE.
}



