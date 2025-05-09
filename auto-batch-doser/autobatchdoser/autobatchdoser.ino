#include "Stepper_Headers/interface.h"
#include <SoftwareSerial.h>
#include "Stepper_Headers/config.h"

SoftwareSerial ESPSerial(PC6, PC7);  // RX, TX
extern MotorState motors[5];

void setup() {
  ESPSerial.begin(115200);  // Start serial communication at 9600 baud
  Stepper_Init();
  delay(10000); // Increase delay to 10s so it gets reported back to esphome
  ESPSerial.println("FW:2.0.1");
}

void loop() {
  String receivedData = "";                          // Variable to store received data
  if (ESPSerial.available()) {                       // Check if data is available
    receivedData = ESPSerial.readStringUntil('\n');  // Read data until newline
    receivedData.trim();                             // Remove any leading/trailing whitespace

    //==========================Motor 1=======================================================
     if (receivedData.equals("Motor 1 ON")) {  // Compare received string
       Stepper_Cmd(1, 1, 0);                   // Motor 1 , Power , ON
     }
     if (receivedData.equals("Motor 1 OFF")) {  // Compare received string
       Stepper_Cmd(1, 1, 1);                    // Motor 1 , Power , OFF
     }
 
     if (receivedData.equals("Motor 1 FWD")) {  // Compare received string
       Stepper_Cmd(1, 2, 0);                    // Motor 1 , Direction , Forward
     }
     if (receivedData.equals("Motor 1 REV")) {  // Compare received string
       Stepper_Cmd(1, 2, 1);                    // Motor 1 , Direction , Reverse
     }

    //==========================Motor 2=======================================================
    if (receivedData.equals("Motor 2 ON")) {  // Compare received string
      //motors[2].power_state = 1;
      Stepper_Cmd(2, 1, 0);                   // Motor 2 , Power , ON
    }
    if (receivedData.equals("Motor 2 OFF")) {  // Compare received string
      //motors[2].power_state = 0;
      Stepper_Cmd(2, 1, 1);                    // Motor 2 , Power , OFF
    }

    if (receivedData.equals("Motor 2 FWD")) {  // Compare received string
      Stepper_Cmd(2, 2, 0);                    // Motor 2 , Direction , Forward
    }
    if (receivedData.equals("Motor 2 REV")) {  // Compare received string
      Stepper_Cmd(2, 2, 1);                    // Motor 2 , Direction , Reverse
    }

    //==========================Motor 3=======================================================
    if (receivedData.equals("Motor 3 ON")) {  // Compare received string
      //motors[3].power_state = 1;
      Stepper_Cmd(3, 1, 0);                   // Motor 3 , Power , ON
    }
    if (receivedData.equals("Motor 3 OFF")) {  // Compare received string
      //motors[3].power_state = 0;
      Stepper_Cmd(3, 1, 1);                    // Motor 3 , Power , OFF
    }

    if (receivedData.equals("Motor 3 FWD")) {  // Compare received string
      Stepper_Cmd(3, 2, 0);                    // Motor 3 , Direction , Forward
    }
    if (receivedData.equals("Motor 3 REV")) {  // Compare received string
      Stepper_Cmd(3, 2, 1);                    // Motor 3 , Direction , Reverse
    }

    //==========================Motor 4=======================================================
    if (receivedData.equals("Motor 4 ON")) {  // Compare received string
      //motors[4].power_state = 1;
      Stepper_Cmd(4, 1, 0);                   // Motor 4 , Power , ON
    }
    if (receivedData.equals("Motor 4 OFF")) {  // Compare received string
      //motors[4].power_state = 0;
      Stepper_Cmd(4, 1, 1);                    // Motor 4 , Power , OFF
    }

    if (receivedData.equals("Motor 4 FWD")) {  // Compare received string
      Stepper_Cmd(4, 2, 0);                    // Motor 4 , Direction , Forward
    }
    if (receivedData.equals("Motor 4 REV")) {  // Compare received string
      Stepper_Cmd(4, 2, 1);                    // Motor 4 , Direction , Reverse
    }
  }
  speed_Adapter();
  Stepper_Clock_Loop();
}
