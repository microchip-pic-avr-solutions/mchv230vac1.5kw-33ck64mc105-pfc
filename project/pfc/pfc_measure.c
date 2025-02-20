// <editor-fold defaultstate="collapsed" desc="Description/Instruction ">
/**
 * @file pfc_measure.c
 *
 * @brief This module has functions for signal conditioning of measured
 *        analog feedback signals.
 *
 * Component: MEASURE
 *
 */
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Disclaimer ">

/*******************************************************************************
* SOFTWARE LICENSE AGREEMENT
* 
* � [2024] Microchip Technology Inc. and its subsidiaries
* 
* Subject to your compliance with these terms, you may use this Microchip 
* software and any derivatives exclusively with Microchip products. 
* You are responsible for complying with third party license terms applicable to
* your use of third party software (including open source software) that may 
* accompany this Microchip software.
* 
* Redistribution of this Microchip software in source or binary form is allowed 
* and must include the above terms of use and the following disclaimer with the
* distribution and accompanying materials.
* 
* SOFTWARE IS "AS IS." NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY,
* APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,
* MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL 
* MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR 
* CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO
* THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE 
* POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY
* LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL
* NOT EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR THIS
* SOFTWARE
*
* You agree that you are solely responsible for testing the code and
* determining its suitability.  Microchip has no obligation to modify, test,
* certify, or support the code.
*
*******************************************************************************/
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="HEADER FILES ">

#include <stdint.h>
#include <stdbool.h>

#include "pfc_measure.h"

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="INTERFACE FUNCTIONS ">
/**
* <B> Function: PFC_MeasureCurrentInit(PFC_MEASURE_CURRENT_T *)  </B>
*
* @brief Function to reset variables used for current offset measurement.
*        .
*
* @param Pointer to the data structure containing measured currents.
* @return none.
* @example
* <CODE> PFC_MeasureCurrentInit(&current); </CODE>
*
*/
void PFC_MeasureCurrentInit(PFC_MEASURE_CURRENT_T *pMeasure)
{
    pMeasure->counter   = 0;
    pMeasure->sum      = 0;
    pMeasure->status    = 0;
}

/**
* <B> Function: PFC_MeasureCurrentOffset(PFC_MEASURE_CURRENT_T *)  </B>
*
* @brief Function to compute current offset after measuring specified number of
*        current samples and averaging them.
*        .
* @param Pointer to the data structure containing measured current.
* @return none.
* @example
* <CODE> PFC_MeasureCurrentOffset(&current); </CODE>
*
*/
void PFC_MeasureCurrentOffset(PFC_MEASURE_CURRENT_T *pMeasure)
{
    pMeasure->sum += pMeasure->iL;

    pMeasure->counter++;

    if (pMeasure->counter >= PFC_OFFSET_COUNT_MAX)
    {
        pMeasure->offset   = (int16_t)(pMeasure->sum >> PFC_OFFSET_COUNT_BITS);

        pMeasure->counter   = 0;
        pMeasure->sum      = 0;
        pMeasure->status    = 1;
    }
}
// </editor-fold>