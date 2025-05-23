#include "Arduino.h"
#include "Stepper_Headers/config.h"
#include "Stepper_Headers/interface.h"

#define Power 1
#define Direction 2

MotorState motors[5];  // Array for 4 motors (index 1-4)

// Helper function to get the enable pin for a specific motor
int getEnablePin(int motorNumber) {
  switch (motorNumber) {
    case 1: return Motor1_ENABLE_PIN;
    case 2: return Motor2_ENABLE_PIN;
    case 3: return Motor3_ENABLE_PIN;
    case 4: return Motor4_ENABLE_PIN;
    default: return -1;
  }
}

// Helper function to get the clock pin for a specific motor
int getClockPin(int motorNumber) {
  switch (motorNumber) {
    case 1: return Motor1_CLK_PIN;
    case 2: return Motor2_CLK_PIN;
    case 3: return Motor3_CLK_PIN;
    case 4: return Motor4_CLK_PIN;
    default: return -1;
  }
}

// Helper function to get the direction pin for a specific motor
int getDirPin(int motorNumber) {
  switch (motorNumber) {
    case 1: return Motor1_DIR_PIN;
    case 2: return Motor2_DIR_PIN;
    case 3: return Motor3_DIR_PIN;
    case 4: return Motor4_DIR_PIN;
    default: return -1;
  }
}

void Stepper_Init() {
  pinMode(Motor1_DIR_PIN, OUTPUT);
  pinMode(Motor1_ENABLE_PIN, OUTPUT);
  pinMode(Motor1_CLK_PIN, OUTPUT);

  pinMode(Motor2_DIR_PIN, OUTPUT);
  pinMode(Motor2_ENABLE_PIN, OUTPUT);
  pinMode(Motor2_CLK_PIN, OUTPUT);

  pinMode(Motor3_DIR_PIN, OUTPUT);
  pinMode(Motor3_ENABLE_PIN, OUTPUT);
  pinMode(Motor3_CLK_PIN, OUTPUT);

  pinMode(Motor4_DIR_PIN, OUTPUT);
  pinMode(Motor4_ENABLE_PIN, OUTPUT);
  pinMode(Motor4_CLK_PIN, OUTPUT);

  digitalWrite(Motor1_ENABLE_PIN, HIGH);  // Disable driver
  digitalWrite(Motor2_ENABLE_PIN, HIGH);  // Disable driver
  digitalWrite(Motor3_ENABLE_PIN, HIGH);  // Disable driver
  digitalWrite(Motor4_ENABLE_PIN, HIGH);  // Disable driver

  digitalWrite(Motor1_DIR_PIN, HIGH);
  digitalWrite(Motor2_DIR_PIN, HIGH);
  digitalWrite(Motor3_DIR_PIN, HIGH);
  digitalWrite(Motor4_DIR_PIN, HIGH);

  // Initialize motor states
  for (int i = 1; i <= 4; i++) {
    motors[i].stepDelay = SPEED_START;
    motors[i].lastChange = 0;
    motors[i].lastStepTime = 0;
    motors[i].isActive = false;
    motors[i].isRampingDown = false;
    motors[i].directionChangePending = false;
    motors[i].newDirection = 0;
    motors[i].stepState = false;
    motors[i].stepCounter = 0;
  }
}

void speed_Adapter() {
  // Update speed for each active motor independently
  for (int i = 1; i <= 4; i++) {
    if (motors[i].isRampingDown) {
      // Ramping down logic for power off - takes priority over everything else
      unsigned long elapsed = millis() - motors[i].lastChange;

      if (elapsed < 125) {
        motors[i].stepDelay = SPEED_75_PERCENT;  // First slowdown step
      } else if (elapsed < 250) {
        motors[i].stepDelay = SPEED_50_PERCENT;  // Second slowdown step
      } else if (elapsed < 375) {
        motors[i].stepDelay = SPEED_25_PERCENT;  // Third slowdown step
      } else if (elapsed < 500) {
        motors[i].stepDelay = SPEED_START;  // Final slowdown step
      } else {
        // When we've fully ramped down
        motors[i].isRampingDown = false;
        motors[i].isActive = false;
        motors[i].directionChangePending = false;  // Cancel any direction change if shutting down
        digitalWrite(getEnablePin(i), HIGH);       // Actually disable the motor
      }
    } else if (motors[i].directionChangePending) {
      // Ramping down logic for direction change
      unsigned long elapsed = millis() - motors[i].lastChange;

      if (elapsed < 100) {
        motors[i].stepDelay = SPEED_75_PERCENT;  // First slowdown step for direction change
      } else if (elapsed < 200) {
        motors[i].stepDelay = SPEED_50_PERCENT;  // Second slowdown step
      } else if (elapsed < 300) {
        motors[i].stepDelay = SPEED_START;  // Final slowdown step
      } else {
        // When we've fully ramped down for direction change
        // Change direction
        digitalWrite(getDirPin(i), motors[i].newDirection);

        // Reset for ramp up
        motors[i].directionChangePending = false;
        motors[i].lastChange = millis();  // Reset timer for ramping up
      }
    } else if (motors[i].isActive) {
      // Normal ramping up logic when active and not changing direction
      unsigned long elapsed = millis() - motors[i].lastChange;

      if (elapsed >= 500) {
        motors[i].stepDelay = SPEED_100_PERCENT;  // Fastest speed
      } else if (elapsed >= 375) {
        motors[i].stepDelay = SPEED_75_PERCENT;
      } else if (elapsed >= 250) {
        motors[i].stepDelay = SPEED_50_PERCENT;
      } else if (elapsed >= 125) {
        motors[i].stepDelay = SPEED_25_PERCENT;
      } else {
        motors[i].stepDelay = SPEED_START;  // Starting speed
      }
    }else{
      motors[i].lastChange = millis();
    }
  }
}

void Stepper_Clock_Loop() {
  unsigned long currentTime = micros();

  // Handle each motor independently
  for (int m = 1; m <= 4; m++) {

    if (motors[m].isActive || motors[m].isRampingDown || motors[m].directionChangePending) {
      // Only process motors that are active, ramping down, or changing direction

      // Check if it's time for this motor to take a step
      if (currentTime - motors[m].lastStepTime >= motors[m].stepDelay) {
        // Toggle step pin state
        motors[m].stepState = !motors[m].stepState;
        digitalWrite(getClockPin(m), motors[m].stepState ? HIGH : LOW);

        // Update last step time
        motors[m].lastStepTime = currentTime;

        // Count completed steps (one complete step is HIGH then LOW)
        if (!motors[m].stepState) {  // If we just went LOW, that's a complete step
          motors[m].stepCounter++;

          // Reset counter after 200 steps (one full rotation)
          if (motors[m].stepCounter >= 200) {
            motors[m].stepCounter = 0;
          }
        }
      }
    }
  }
  // if (motors[1].power_state == 1) {
  //   Stepper_Cmd(1, 1, 0);  // Motor 1 , Power , ON
  // } else {
  //   Stepper_Cmd(1, 1, 1);  // Motor 1 , Power , OFF
  // }
}

void Stepper_Cmd(int Motor_Number, int Cmd, int State) {  // CMD case 1 -> Power   case 2 -> Direction
  if (Motor_Number < 1 || Motor_Number > 4) return;       // Validate motor number

  switch (Cmd) {
    case Power:
      if (State == 0) {  // Power ON
        motors[Motor_Number].lastChange = millis();
        motors[Motor_Number].lastStepTime = micros();  // Initialize step timing
        motors[Motor_Number].stepDelay = SPEED_START;  // Start at slow speed
        motors[Motor_Number].isActive = true;
        motors[Motor_Number].isRampingDown = false;
        motors[Motor_Number].directionChangePending = false;
        motors[Motor_Number].stepCounter = 0;           // Reset step counter
        motors[Motor_Number].stepState = false;         // Start with step pin LOW
        digitalWrite(getClockPin(Motor_Number), LOW);   // Ensure clock pin starts LOW
        digitalWrite(getEnablePin(Motor_Number), LOW);  // Enable driver
      } else {                                          // Power OFF - start ramping down
        motors[Motor_Number].lastChange = millis();
        motors[Motor_Number].isRampingDown = true;
        // Power off command takes priority over direction change
        motors[Motor_Number].directionChangePending = false;
        // Note: We don't immediately disable the motor - we'll ramp down and disable after
      }
      break;

    case Direction:
      if (motors[Motor_Number].isActive && !motors[Motor_Number].isRampingDown) {
        // If motor is active AND not already ramping down, start the direction change process
        motors[Motor_Number].lastChange = millis();
        motors[Motor_Number].directionChangePending = true;
        motors[Motor_Number].newDirection = State;
        // Actual direction change will happen after slowing down in speed_Adapter
      } else if (!motors[Motor_Number].isActive) {
        // If motor is not active, change direction immediately
        digitalWrite(getDirPin(Motor_Number), State);
      }
      // If motor is ramping down for power off, ignore direction change
      break;
  }
}
