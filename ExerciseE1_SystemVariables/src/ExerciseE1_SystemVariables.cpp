// ExerciseE1_SystemVariables.cpp : Defines the initialization routines for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "arxHeaders.h"
#include "acedCmdNF.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static void commandSysVar()
{
    // Create a variable of the result buffer type 
    struct resbuf rb, rb1;
    // Get the current value of the CIRCLERAD system variable 
    acedGetVar(_T("CIRCLERAD"), &rb);
    acutPrintf(_T("\nCurrent CIRCLERAD: %.2f\n"), rb.resval);
    // Define the center point for the circle 
    ads_point pt;
    pt[X] = 2.5; pt[Y] = 3.75; pt[Z] = 0.0;
    // Define the radius of the circle 
    double rrad = 2.75;
    // Provide all values to the CIRCLE command 
    if (acedCommandS(RTSTR, _T("._CIRCLE"), RTPOINT, pt,
        RTREAL, rrad, RTNONE) != RTNORM)
    {
        acutPrintf(_T("\nError: CIRCLE command failed."));
    }
    // Pause for the center point 
    if (acedCommandS(RTSTR, _T("._CIRCLE"), RTSTR, PAUSE,
        RTREAL, rrad, RTNONE) != RTNORM)
    {
        acutPrintf(_T("\nError: CIRCLE command failed."));
    }
    // Set the value of CIRCLERAD to the previous value 
    rb1.restype = RTREAL;
    rb1.resval.rreal = rb.resval.rreal;
    acedSetVar(_T("CIRCLERAD"), &rb1);
}


extern "C" AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt)
{
    switch (msg)
    {
    case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(pkt);
        acrxDynamicLinker->registerAppMDIAware(pkt);
        acutPrintf(L"\nLoading project...\n");
        // Commands to add
        acedRegCmds->addCommand(_T("AUCommands"), _T("SystemVariable"),
            _T("SystemVariable"), ACRX_CMD_MODAL, commandSysVar);//addLine  makeLayer
        break;
    case AcRx::kUnloadAppMsg:
        acutPrintf(_T("\nUnloading createLine project...\n"));
        // Command Groups to remove
        acedRegCmds->removeGroup(_T("AUCommnds"));
        break;
    default:
        break;
    }
    return AcRx::kRetOK;
}
