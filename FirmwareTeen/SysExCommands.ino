// Copyright 2019 Sergio Retamero.
//
// Author: Sergio Retamero (sergio.retamero@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// See http://creativecommons.org/licenses/MIT/ for more information.
//
// -----------------------------------------------------------------------------
//

#include "PrjIncludes.h"

/** @addtogroup SysEx
 *  @{
 */

/**
 *  \file SysExSendRec.ino
 *  \brief SysEx Send/Receive commands
 */  



/**
 * \brief Proccess SysEx global commands 
 * 
 * \param SysExPacket 
 */
void VCMCApp::ProcessSysExCommand(VCMCSysExPacket *SysExPacket){
    uint8_t bComm = SysExPacket->Slot; // Global commands are stored in the slot as 7 bits value
    if( SysExPacket->Length <1) return;
    
    switch(bComm){
        case SENDCURRENTCONFIG:
            DP("Sending Current SysEx config");
            FlashAcc.SaveCfgSysEx(-1);
            break;
        case RESETMODULE:
            DP("Reset module");
            ResetCPU();
            break;
        case FACTORYDEFAULT:
            DP("Reset module to factory default");
            FactoryReset();
            break;
        case SAVETOSLOT:
            D(Serial.printf("Save to Slot %d.\n",SysExPacket->pData[0]));
            FlashAcc.SaveCfg(SysExPacket->pData[0]);
            break;
        case LOADSLOT:
            DP("Load Slot");
            FlashAcc.LoadCfg(SysExPacket->pData[0]);
            break;
        default:
            DP("SysEx General command not recognized");
    }
}



/** @} */
