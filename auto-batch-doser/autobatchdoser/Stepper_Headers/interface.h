#ifndef _STEPER_INTERFACE_H
#define _STEPER_INTERFACE_H

void Stepper_Init();
void Stepper_Clock_Loop();
void Stepper_Cmd(int Motor_Number , int Cmd , int State);
void speed_Adapter();

#endif