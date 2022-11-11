# Comparison between M4 and M5 user interface:

## In M4:
There was no set distance of travel (paddleup/paddledown) but instead there was a continuous range of integer values the user could traverse based on the position of the Arduino. 

Using the BLE_UUID_ACCELEROMETER_X for movement.

**Pointing Arduino Nose Up: Paddle Up**

**Pointing Arduino Nose Down: Paddle Down**

**Anywhere in between: A position that interpolates between fully Up and Down**


## In M5:
The Arduino would move a set distance per sample, therefore yielding less control to the user. 

Using the BLE_UUID_ACCELEROMETER_Z for movement.

**Arduino Face Up (z > 0.7): Move Paddle Up + 45**

**Arduino Face Down (z < -0.7): Move Paddle Down - 45**

**Arduino on its Side (-0.7 >= z <= 0.7): Stay**


## **Analysis**
Overall, the M4 movement gives more control to the user, and in my opinion is more intuitive. It seems to be easier to play, less challenging, and overall a better experience for the user. 