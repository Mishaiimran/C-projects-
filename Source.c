// program: HS1 255
// Author: Misha Imran
// Date: 9/29/2023
// Purpose: 
#include"c:/Program Files (x86)/LabJack/Drivers/LabJackUD.h"
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
int main()
{
    LJ_ERROR lj_cue;
    LJ_HANDLE lj_handle = 0;
    double capAIN0;

    lj_cue = OpenLabJack(LJ_dtU3, LJ_ctUSB, "1", 1, &lj_handle);
    lj_cue = ePut(lj_handle, LJ_ioPIN_CONFIGURATION_RESET, 0, 0, 0);

    lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 1, 0, 0, 0);
    lj_cue = AddRequest(lj_handle, LJ_ioGET_AIN, 0, 0, 0, 0);
    lj_cue = Go();
    lj_cue = GetResult(lj_handle, LJ_ioGET_AIN, 0, &capAIN0);

    while (capAIN0 < 4)
    {
        printf("Capacitor voltage is curerently at %.2fV\n", capAIN0);
        Sleep(100);
        lj_cue = AddRequest(lj_handle, LJ_ioGET_AIN, 0, 0, 0, 0);
        lj_cue = Go();
        lj_cue = GetResult(lj_handle, LJ_ioGET_AIN, 0, &capAIN0);
    }
    
    lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 1, 4.5, 0, 0);
    lj_cue = Go();
    puts("the capaciotor has reached 4V");
    system("pause");

    lj_cue = AddRequest(lj_handle, LJ_ioPUT_DAC, 1, 0, 0, 0);
    lj_cue = Go();
    
    Close();
    return 0;
}