#include "Stepper_Headers/Interface.h"
#include <SoftwareSerial.h>

SoftwareSerial ESPSerial(PC6, PC7);  // RX, TX

void setup() {
  ESPSerial.begin(115200);  // Start serial communication at 9600 baud
  Stepper_Init();
}

void loop() {
  Stepper_Clock_Loop();

  String receivedData = "";                          // Variable to store received data
  if (ESPSerial.available()) {                       // Check if data is available
    receivedData = ESPSerial.readStringUntil('\n');  // Read data until newline
    receivedData.trim();                             // Remove any leading/trailing whitespace

    //==========================Motor 1=======================================================
    if (receivedData.equals("Motor 1 ON")) {  // Compare received string
    ESPSerial.println("Motor 1 is ON now");
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
      Stepper_Cmd(2, 1, 0);                   // Motor 2 , Power , ON
    }
    if (receivedData.equals("Motor 2 OFF")) {  // Compare received string
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
      Stepper_Cmd(3, 1, 0);                   // Motor 3 , Power , ON
    }
    if (receivedData.equals("Motor 3 OFF")) {  // Compare received string
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
      Stepper_Cmd(4, 1, 0);                   // Motor 4 , Power , ON
    }
    if (receivedData.equals("Motor 4 OFF")) {  // Compare received string
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
}
