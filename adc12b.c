


//*******************************************************************************
// 																				*
//		PPS PVT Firmware														*
//		File:           	   	adc506a.c										*
//		PPS Inc. 	cli 		2011.06.30										*
// 																				*
//*******************************************************************************




#include <xc.h>		// Register definitions


#include "adc12b.h"			// ADC Header File.


// External Function Definitions:




//---------------------------------------------------------------------------------

// This program initilize the ADC with:
//	1) 12-bit mode;
//	2) Single channel;
//	3) Manual sampling;
//	4) Manual conversion;
//	5) AN10 and AN11.
//  6) Format: Signed Integer.



//---------------------------------------------------------------------------------
// 1) Call adc1_init() first before calling any other adc1 sub-routines.

void adc1_init(void)

{

	// ------------------------ AD1CON1 Initialization ----------------------------

	// ADON: ADC Operating Mode bit.
	//       '1' = ADC module is operating.
	//       '0' = ADC module is off.
	AD1CON1bits.ADON = 0;				// ADC Off.

	// ADSIDL: Stop in Idle Mode bit.
	//         '1' = Discontinue module operation when device enters Idle mode.
	//         '0' = Continue module operation in Idle mode.
	AD1CON1bits.ADSIDL = 1;				// Stop operating when IDLE.

	// ADDMABM: DMA Buffer Build Mode bit.
	//          '1 = DMA buffers are written in the order of conversion. The module will provide an address to the DMA
	//               channel that is the same as the address used for the non-DMA stand-alone buffer.
	//          '0 = DMA buffers are written in Scatter/Gather mode. The module will provide a scatter/gather address
	//               to the DMA channel, based on the index of the analog input and the size of the DMA buffer.
	AD1CON1bits.ADDMABM = 0;			// .

	// AD12B: 10-bit or 12-bit Operation Mode bit.
	//        '1' = 12-bit, 1-channel ADC operation.
	//        '0' = 10-bit, 4-channel ADC operation.
	AD1CON1bits.AD12B = 1;				// 12-bit Mode.

	// FORM<1:0>: Data Output Format bits.
	// For 10-bit operation:
	//            "11" = Reserved.
	//            "10" = Reserved.
	//            "01" = Signed integer (DOUT = ssss sssd dddd dddd, where s = .NOT.d<9>).
	//            "00" = Integer (DOUT = 0000 00dd dddd dddd).
	// For 12-bit operation:
	//            "11" = Signed fractional (DOUT = sddd dddd dddd 0000, where s = .NOT.d<11>).
	//            "10" = Fractional (DOUT = dddd dddd dddd 0000).
	//            "01" = Signed Integer (DOUT = ssss sddd dddd dddd, where s = .NOT.d<11>).
	//            "00" = Integer (DOUT = 0000 dddd dddd dddd).
	AD1CON1bits.FORM = 2;				// Un-Singed Integer.

	// SSRC<2:0>: Sample Clock Source Select bits.
	//            "111" = Internal counter ends sampling and starts conversion (auto-convert).
	//            "110" = Reserved.
	//            "101" = Reserved.
	//            "100" = GP timer (Timer5 for ADC1, Timer3 for ADC2) compare ends sampling and starts conversion.
	//            "011" = Reserved.
	//            "010" = GP timer (Timer3 for ADC1, Timer5 for ADC2) compare ends sampling and starts conversion.
	//            "001" = Active transition on INT0 pin ends sampling and starts conversion.
	//            "000" = Clearing sample bit ends sampling and starts conversion.
	AD1CON1bits.SSRC = 7; 				// Manual conversion.

	// SIMSAM: Simultaneous Sample Select bit (only applicable when CHPS<1:0> = 01 or 1x).
	// When AD12B = 1, SIMSAM is: U-0, Unimplemented, Read as ?0?
	//        '1' = Samples CH0, CH1, CH2, CH3 simultaneously (when CHPS<1:0> = 1x); or
	//              Samples CH0 and CH1 simultaneously (when CHPS<1:0> = 01).
	//        '0' = Samples multiple channels individually in sequence.
	AD1CON1bits.SIMSAM = 0;				// Sequencial Sample.

	// ASAM: ADC Sample Auto-Start bit.
	//       '1' = Sampling begins immediately after last conversion. SAMP bit is auto-set.
	//       '0' = Sampling begins when SAMP bit is set.
	AD1CON1bits.ASAM = 1;				// Manual sampling.

	// SAMP: ADC Sample Enable bit.
	//       '1' = ADC Sample/Hold amplifiers are sampling.
	//       '0' = ADC Sample/Hold amplifiers are holding.
	//       If ASAM = 0, software can write ?1? to begin sampling. Automatically set by hardware if ASAM = 1.
	//       If SSRC = 000, software can write ?0? to end sampling and start conversion. If SSRC ? 000,
	//       automatically cleared by hardware to end sampling and start conversion.
	AD1CON1bits.SAMP = 1;				// Start sampling.

	// ------------------------ AD1CON2 Initialization ----------------------------

	// VCFG<2:0>: Converter Voltage Reference Configuration bits.
	AD1CON2bits.VCFG = 0;				// VREFH = AVDD; VREFL = AVss.

	// CSCNA: Input Scan Select bit.
	//        '1' = Scan inputs using CH0.
	//        '0' = Do not scan inputs.
	AD1CON2bits.CSCNA = 0; 				// Scan inputs using CH0.

	// CHPS<1:0>: Channel Select bits
	//            When AD12B = 1, CHPS<1:0> is: U-0, Unimplemented, Read as ?0?.
	//            "1x" = Converts CH0, CH1, CH2, and CH3.
	//            "01" = Converts CH0 and CH1.
	//            "00" = Converts CH0.
	AD1CON2bits.CHPS =0; // Converts CH0.

	// SMPI<3:0>: Samples Convert Sequences Per Interrupt.
	//            "1111" = Interrupts at the completion of conversion for every 16th sample/convert sequence.
	//            "1110" = Interrupts at the completion of conversion for every 15th sample/convert sequence.
	//            ?
	//            ?
	//            ?
	//            "0001" = Interrupts at the completion of conversion for every 2nd sample/convert sequence.
	//            "0000" = Interrupts at the completion of conversion for every sample/convert sequence.
	AD1CON2bits.SMPI = 0;				// Select 2 conversion between interrupt.

	// BUFM: Buffer Fill Mode Select bit.
	//        '1' = Starts buffer filling the first half of the buffer on the first interrupt and the second
	//              half of the buffer on next interrupt.
	//        '0' = Always starts filling the buffer from the start address.
	AD1CON2bits.BUFM = 0;				// Filling the buffer from the start address.

	// ALTS: Alternate Input Selection Mode Select bit.
	//        '1' = MUXA and MUXB control bits alternatively select the analog input for conversion.
	//        '0' = MUXA control bits select the analog input for conversion (CSCNA = 0).
	//              Channel Scan Logic select the analog input for conversion (CSCNA = 1).
	AD1CON2bits.ALTS = 0;				// MUXA control bits select the analog input for conversion (CSCNA = 0).

	// ------------------------ AD1CON3 Initialization ----------------------------

	// ADRC: ADC Conversion Clock Source bit.
	//       '1' = ADC Internal RC Clock.
	//       '0' = Clock derived from system clock.
	AD1CON3bits.ADRC = 1;				// Use system clock.

	// SAMC<4:0>: Auto Sample Time bits.
	//            "11111" = 31 TAD.
	//            ?
	//            ?
	//            ?
	//            "00001" = 1 TAD.
	//            "00000" = 0 TAD.
	AD1CON3bits.SAMC = 10;				// 16 TAD.

	// ADCS<7:0>: ADC Conversion Clock Select bits.
	//            "11111111" = TCY ? (ADCS<7:0> + 1) = 256 ? TCY = TAD.
	//            ?
	//            ?
	//            ?
	//            "00000010" = TCY ? (ADCS<7:0> + 1) = 3 ? TCY = TAD.
	//            "00000001" = TCY ? (ADCS<7:0> + 1) = 2 ? TCY = TAD.
	//            "00000000" = TCY ? (ADCS<7:0> + 1) = 1 ? TCY = TAD.
	AD1CON3bits.ADCS = 10;				//  TCY.

	// ------------------------ AD1CON4 Initialization ----------------------------

	// DMABL<2:0>: Selects Number of DMA Buffer Locations per Analog Input bits.
	//             "111" = Allocates 128 words of buffer to each analog input.
	//             "110" = Allocates 64 words of buffer to each analog input.
	//             "101" = Allocates 32 words of buffer to each analog input.
	//             "100" = Allocates 16 words of buffer to each analog input.
	//             "011" = Allocates 8 words of buffer to each analog input.
	//             "010" = Allocates 4 words of buffer to each analog input.
	//             "001" = Allocates 2 words of buffer to each analog input.
	//             "000" = Allocates 1 word of buffer to each analog input.
	AD1CON4bits.DMABL = 1;				// 1 word of buffer.

	// ------------------------ AD1CHS123 Initialization ----------------------------

	// CH123NB<1:0>: Channel 1, 2, 3 Negative Input Select for Sample B bits.
	//               When AD12B = 1, CHxNB is: U-0, Unimplemented, Read as ?0?.
	//               "11" = CH1 negative input is AN9, CH2 negative input is AN10, CH3 negative input is AN11.
	//               "10" = CH1 negative input is AN6, CH2 negative input is AN7, CH3 negative input is AN8.
	//               "0x" = CH1, CH2, CH3 negative input is VREF-.
	AD1CHS123bits.CH123NB = 0;			// CH1, CH2, CH3 negative input is VREF-.

	// CH123SB: Channel 1, 2, 3 Positive Input Select for Sample B bit.
	//          When AD12B = 1, CHxSA is: U-0, Unimplemented, Read as ?0?.
	//          '1' = CH1 positive input is AN3, CH2 positive input is AN4, CH3 positive input is AN5.
	//          '0' = CH1 positive input is AN0, CH2 positive input is AN1, CH3 positive input is AN2.
	AD1CHS123bits.CH123SB =0;			// CH1 positive input is AN3, CH2 positive input is AN4, CH3 positive input is AN5.

	// CH123NA<1:0>: Channel 1, 2, 3 Negative Input Select for Sample A bits.
	//               When AD12B = 1, CHxNA is: U-0, Unimplemented, Read as ?0?.
	//               "11" = CH1 negative input is AN9, CH2 negative input is AN10, CH3 negative input is AN11.
	//               "10" = CH1 negative input is AN6, CH2 negative input is AN7, CH3 negative input is AN8.
	//               "0x" = CH1, CH2, CH3 negative input is VREF-.
	AD1CHS123bits.CH123NA = 0;			// CH1 negative input is AN9, CH2 negative input is AN10, CH3 negative input is AN11.

	// CH123SA: Channel 1, 2, 3 Positive Input Select for Sample A bit.
	//          When AD12B = 1, CHxSA is: U-0, Unimplemented, Read as ?0?.
	//          '1' = CH1 positive input is AN3, CH2 positive input is AN4, CH3 positive input is AN5.
	//          '0' = CH1 positive input is AN0, CH2 positive input is AN1, CH3 positive input is AN2.
	AD1CHS123bits.CH123SA = 0;			// CH1 positive input is AN3, CH2 positive input is AN4, CH3 positive input is AN5.

	// ------------------------ AD1CHS0 Initialization ----------------------------

	// CH0NB: Channel 0 Negative Input Select for Sample B bit.
	//        '1 = Channel 0 negative input is AN1.
	//        '0 = Channel 0 negative input is VREF-.
	AD1CHS0bits.CH0NB = 0;				// Channel 0 negative input is VREF-.

	// CH0SB<4:0>: Channel 0 Positive Input Select for Sample B bits.
	//             "01100" = Channel 0 positive input is AN12.
	//             "01011" = Channel 0 positive input is AN11.
	//             ?
	//             ?
	//             ?
	//             "00010" = Channel 0 positive input is AN2.
	//             "00001" = Channel 0 positive input is AN1.
	//             "00000" = Channel 0 positive input is AN0.
	AD1CHS0bits.CH0SB = 0;				// Channel 0 positive input is AN11.

	// CH0NA: Channel 0 Negative Input Select for Sample A bit.
	//        '1 = Channel 0 negative input is AN1.
	//        '0 = Channel 0 negative input is VREF-.
	AD1CHS0bits.CH0NA = 0;				// Channel 0 negative input is VREF-.

	// CH0SA<4:0>: Channel 0 Positive Input Select for Sample A bits.
	//             "01100" = Channel 0 positive input is AN12.
	//             "01011" = Channel 0 positive input is AN11.
	//             ?
	//             ?
	//             ?
	//             "00010" = Channel 0 positive input is AN2.
	//             "00001" = Channel 0 positive input is AN1.
	//             "00000" = Channel 0 positive input is AN0.
	AD1CHS0bits.CH0SA = 0;				// Channel 0 positive input is AN10.

	// ------------------------ AD1CSSH Initialization ----------------------------

	// CSS<31:16>: ADC Input Scan Selection bits(1).
	//             '1' = Select ANx for input scan.
	//             '0' = Skip ANx for input scan.
	AD1CSSH = 0x0000;					// Disable all AN16 and AN17 for scan.

	// ------------------------ AD1CSSL Initialization ----------------------------

	// CSS<15:0>: ADC Input Scan Selection bits(1).
	//            '1' = Select ANx for input scan.
	//            '0' = Skip ANx for input scan.
	AD1CSSL = 0x7;					// Eable only AN10 and AN11 for scan.

	// ------------------------ AD1PCFGH Initialization ----------------------------

	// PCFG<31:16>: ADC Port Configuration Control bits.
	//              '1' = Port pin in Digital mode, port read input enabled, ADC input multiplexor connected to AVSS.
	//              '0' = Port pin in Analog mode, port read input disabled, ADC samples pin voltage.
	AD1PCFGH = 0xFFFF;					// AN16 and AN17 pins in Digital mode.

	// ------------------------ AD1PCFGL Initialization ----------------------------

	// PCFG<15:0>: ADC Port Configuration Control bits.
	//             '1' = Port pin in Digital mode, port read input enabled, ADC input multiplexor connected to AVSS.
	//             '0' = Port pin in Analog mode, port read input disabled, ADC samples pin voltage.
	AD1PCFGL = 0xFFF0;					// AN10 and AN11 port pins in Analog mode; all other port pins in Digital mode.

	// ADON: ADC Operating Mode bit.
	//       '1' = ADC module is operating.
	//       '0' = ADC module is off.
	AD1CON1bits.ADON = 1;				// ADC On.

}




//void adc1_init(void) {
//
//    // ------------------------ AD1CON1 Initialization ----------------------------
//
//    // ADON: ADC Operating Mode bit.
//    //       '1' = ADC module is operating.
//    //       '0' = ADC module is off.
//    AD1CON1bits.ADON = 0; // ADC Off.
//
//    // ADSIDL: Stop in Idle Mode bit.
//    //         '1' = Discontinue module operation when device enters Idle mode.
//    //         '0' = Continue module operation in Idle mode.
//    AD1CON1bits.ADSIDL = 1; // Stop operating when IDLE.
//
//    // ADDMABM: DMA Buffer Build Mode bit.
//    //          '1 = DMA buffers are written in the order of conversion. The module will provide an address to the DMA
//    //               channel that is the same as the address used for the non-DMA stand-alone buffer.
//    //          '0 = DMA buffers are written in Scatter/Gather mode. The module will provide a scatter/gather address
//    //               to the DMA channel, based on the index of the analog input and the size of the DMA buffer.
//    AD1CON1bits.ADDMABM = 0; // .
//
//    // AD12B: 10-bit or 12-bit Operation Mode bit.
//    //        '1' = 12-bit, 1-channel ADC operation.
//    //        '0' = 10-bit, 4-channel ADC operation.
//    AD1CON1bits.AD12B = 0; // 12-bit Mode.
//
//    // FORM<1:0>: Data Output Format bits.
//    // For 10-bit operation:
//    //            "11" = Reserved.
//    //            "10" = Reserved.
//    //            "01" = Signed integer (DOUT = ssss sssd dddd dddd, where s = .NOT.d<9>).
//    //            "00" = Integer (DOUT = 0000 00dd dddd dddd).
//    // For 12-bit operation:
//    //            "11" = Signed fractional (DOUT = sddd dddd dddd 0000, where s = .NOT.d<11>).
//    //            "10" = Fractional (DOUT = dddd dddd dddd 0000).
//    //            "01" = Signed Integer (DOUT = ssss sddd dddd dddd, where s = .NOT.d<11>).
//    //            "00" = Integer (DOUT = 0000 dddd dddd dddd).
//    AD1CON1bits.FORM = 0; // Un-Singed Integer.
//
//    // SSRC<2:0>: Sample Clock Source Select bits.
//    //            "111" = Internal counter ends sampling and starts conversion (auto-convert).
//    //            "110" = Reserved.
//    //            "101" = Reserved.
//    //            "100" = GP timer (Timer5 for ADC1, Timer3 for ADC2) compare ends sampling and starts conversion.
//    //            "011" = Reserved.
//    //            "010" = GP timer (Timer3 for ADC1, Timer5 for ADC2) compare ends sampling and starts conversion.
//    //            "001" = Active transition on INT0 pin ends sampling and starts conversion.
//    //            "000" = Clearing sample bit ends sampling and starts conversion.
//    AD1CON1bits.SSRC = 7; // Manual conversion.
//
//    // SIMSAM: Simultaneous Sample Select bit (only applicable when CHPS<1:0> = 01 or 1x).
//    // When AD12B = 1, SIMSAM is: U-0, Unimplemented, Read as ‘0’
//    //        '1' = Samples CH0, CH1, CH2, CH3 simultaneously (when CHPS<1:0> = 1x); or
//    //              Samples CH0 and CH1 simultaneously (when CHPS<1:0> = 01).
//    //        '0' = Samples multiple channels individually in sequence.
//    AD1CON1bits.SIMSAM = 0; // Sequencial Sample.
//
//    // ASAM: ADC Sample Auto-Start bit.
//    //       '1' = Sampling begins immediately after last conversion. SAMP bit is auto-set.
//    //       '0' = Sampling begins when SAMP bit is set.
//    AD1CON1bits.ASAM = 1; //// Manual sampling.
//
//    // SAMP: ADC Sample Enable bit.
//    //       '1' = ADC Sample/Hold amplifiers are sampling.
//    //       '0' = ADC Sample/Hold amplifiers are holding.
//    //       If ASAM = 0, software can write ‘1’ to begin sampling. Automatically set by hardware if ASAM = 1.
//    //       If SSRC = 000, software can write ‘0’ to end sampling and start conversion. If SSRC ? 000,
//    //       automatically cleared by hardware to end sampling and start conversion.
//    AD1CON1bits.SAMP = 1; // Start sampling.
//
//    // ------------------------ AD1CON2 Initialization ----------------------------
//
//    // VCFG<2:0>: Converter Voltage Reference Configuration bits.
//    AD1CON2bits.VCFG = 0; // VREFH = AVDD; VREFL = AVss.
//
//    // CSCNA: Input Scan Select bit.
//    //        '1' = Scan inputs using CH0.
//    //        '0' = Do not scan inputs.
//    AD1CON2bits.CSCNA = 0; // Scan inputs using CH0.
//
//    // CHPS<1:0>: Channel Select bits
//    //            When AD12B = 1, CHPS<1:0> is: U-0, Unimplemented, Read as ‘0’.
//    //            "1x" = Converts CH0, CH1, CH2, and CH3.
//    //            "01" = Converts CH0 and CH1.
//    //            "00" = Converts CH0.
//    AD1CON2bits.CHPS = 0; // Converts CH0.
//
//    // SMPI<3:0>: Samples Convert Sequences Per Interrupt.
//    //            "1111" = Interrupts at the completion of conversion for every 16th sample/convert sequence.
//    //            "1110" = Interrupts at the completion of conversion for every 15th sample/convert sequence.
//    //            •
//    //            •
//    //            •
//    //            "0001" = Interrupts at the completion of conversion for every 2nd sample/convert sequence.
//    //            "0000" = Interrupts at the completion of conversion for every sample/convert sequence.
//    AD1CON2bits.SMPI = 1; // Select 2 conversion between interrupt.
//
//    // BUFM: Buffer Fill Mode Select bit.
//    //        '1' = Starts buffer filling the first half of the buffer on the first interrupt and the second
//    //              half of the buffer on next interrupt.
//    //        '0' = Always starts filling the buffer from the start address.
//    AD1CON2bits.BUFM = 0; // Filling the buffer from the start address.
//
//    // ALTS: Alternate Input Selection Mode Select bit.
//    //        '1' = MUXA and MUXB control bits alternatively select the analog input for conversion.
//    //        '0' = MUXA control bits select the analog input for conversion (CSCNA = 0).
//    //              Channel Scan Logic select the analog input for conversion (CSCNA = 1).
//    AD1CON2bits.ALTS = 0; // MUXA control bits select the analog input for conversion (CSCNA = 0).
//
//    // ------------------------ AD1CON3 Initialization ----------------------------
//
//    // ADRC: ADC Conversion Clock Source bit.
//    //       '1' = ADC Internal RC Clock.
//    //       '0' = Clock derived from system clock.
//    AD1CON3bits.ADRC = 0; // Use system clock.
//
//    // SAMC<4:0>: Auto Sample Time bits.
//    //            "11111" = 31 TAD.
//    //            •
//    //            •
//    //            •
//    //            "00001" = 1 TAD.
//    //            "00000" = 0 TAD.
//    AD1CON3bits.SAMC = 8; // 16 TAD.
//
//    // ADCS<7:0>: ADC Conversion Clock Select bits.
//    //            "11111111" = TCY • (ADCS<7:0> + 1) = 256 • TCY = TAD.
//    //            •
//    //            •
//    //            •
//    //            "00000010" = TCY • (ADCS<7:0> + 1) = 3 • TCY = TAD.
//    //            "00000001" = TCY • (ADCS<7:0> + 1) = 2 • TCY = TAD.
//    //            "00000000" = TCY • (ADCS<7:0> + 1) = 1 • TCY = TAD.
//    AD1CON3bits.ADCS = 0; // 8 TCY.
//
//    // ------------------------ AD1CON4 Initialization ----------------------------
//
//    // DMABL<2:0>: Selects Number of DMA Buffer Locations per Analog Input bits.
//    //             "111" = Allocates 128 words of buffer to each analog input.
//    //             "110" = Allocates 64 words of buffer to each analog input.
//    //             "101" = Allocates 32 words of buffer to each analog input.
//    //             "100" = Allocates 16 words of buffer to each analog input.
//    //             "011" = Allocates 8 words of buffer to each analog input.
//    //             "010" = Allocates 4 words of buffer to each analog input.
//    //             "001" = Allocates 2 words of buffer to each analog input.
//    //             "000" = Allocates 1 word of buffer to each analog input.
//    AD1CON4bits.DMABL = 0; // 1 word of buffer.
//
//    // ------------------------ AD1CHS123 Initialization ----------------------------
//
//    // CH123NB<1:0>: Channel 1, 2, 3 Negative Input Select for Sample B bits.
//    //               When AD12B = 1, CHxNB is: U-0, Unimplemented, Read as ‘0’.
//    //               "11" = CH1 negative input is AN9, CH2 negative input is AN10, CH3 negative input is AN11.
//    //               "10" = CH1 negative input is AN6, CH2 negative input is AN7, CH3 negative input is AN8.
//    //               "0x" = CH1, CH2, CH3 negative input is VREF-.
//    AD1CHS123bits.CH123NB = 0; // CH1, CH2, CH3 negative input is VREF-.
//
//    // CH123SB: Channel 1, 2, 3 Positive Input Select for Sample B bit.
//    //          When AD12B = 1, CHxSA is: U-0, Unimplemented, Read as ‘0’.
//    //          '1' = CH1 positive input is AN3, CH2 positive input is AN4, CH3 positive input is AN5.
//    //          '0' = CH1 positive input is AN0, CH2 positive input is AN1, CH3 positive input is AN2.
//    AD1CHS123bits.CH123SB = 1; // CH1 positive input is AN3, CH2 positive input is AN4, CH3 positive input is AN5.
//
//    // CH123NA<1:0>: Channel 1, 2, 3 Negative Input Select for Sample A bits.
//    //               When AD12B = 1, CHxNA is: U-0, Unimplemented, Read as ‘0’.
//    //               "11" = CH1 negative input is AN9, CH2 negative input is AN10, CH3 negative input is AN11.
//    //               "10" = CH1 negative input is AN6, CH2 negative input is AN7, CH3 negative input is AN8.
//    //               "0x" = CH1, CH2, CH3 negative input is VREF-.
//    AD1CHS123bits.CH123NA = 3; // CH1 negative input is AN9, CH2 negative input is AN10, CH3 negative input is AN11.
//
//    // CH123SA: Channel 1, 2, 3 Positive Input Select for Sample A bit.
//    //          When AD12B = 1, CHxSA is: U-0, Unimplemented, Read as ‘0’.
//    //          '1' = CH1 positive input is AN3, CH2 positive input is AN4, CH3 positive input is AN5.
//    //          '0' = CH1 positive input is AN0, CH2 positive input is AN1, CH3 positive input is AN2.
//    AD1CHS123bits.CH123SA = 1; // CH1 positive input is AN3, CH2 positive input is AN4, CH3 positive input is AN5.
//
//    // ------------------------ AD1CHS0 Initialization ----------------------------
//
//    // CH0NB: Channel 0 Negative Input Select for Sample B bit.
//    //        '1 = Channel 0 negative input is AN1.
//    //        '0 = Channel 0 negative input is VREF-.
//    AD1CHS0bits.CH0NB = 0; // Channel 0 negative input is VREF-.
//
//    // CH0SB<4:0>: Channel 0 Positive Input Select for Sample B bits.
//    //             "01100" = Channel 0 positive input is AN12.
//    //             "01011" = Channel 0 positive input is AN11.
//    //             •
//    //             •
//    //             •
//    //             "00010" = Channel 0 positive input is AN2.
//    //             "00001" = Channel 0 positive input is AN1.
//    //             "00000" = Channel 0 positive input is AN0.
//    AD1CHS0bits.CH0SB = 0; // Channel 0 positive input is AN11.
//
//    // CH0NA: Channel 0 Negative Input Select for Sample A bit.
//    //        '1 = Channel 0 negative input is AN1.
//    //        '0 = Channel 0 negative input is VREF-.
//    AD1CHS0bits.CH0NA = 0; // Channel 0 negative input is VREF-.
//
//    // CH0SA<4:0>: Channel 0 Positive Input Select for Sample A bits.
//    //             "01100" = Channel 0 positive input is AN12.
//    //             "01011" = Channel 0 positive input is AN11.
//    //             •
//    //             •
//    //             •
//    //             "00010" = Channel 0 positive input is AN2.
//    //             "00001" = Channel 0 positive input is AN1.
//    //             "00000" = Channel 0 positive input is AN0.
//    AD1CHS0bits.CH0SA = 0; // Channel 0 positive input is AN10.
//
//    // ------------------------ AD1CSSH Initialization ----------------------------
//
//    // CSS<31:16>: ADC Input Scan Selection bits(1).
//    //             '1' = Select ANx for input scan.
//    //             '0' = Skip ANx for input scan.
//    AD1CSSH = 0x0000; // Disable all AN16 and AN17 for scan.
//
//    // ------------------------ AD1CSSL Initialization ----------------------------
//
//    // CSS<15:0>: ADC Input Scan Selection bits(1).
//    //            '1' = Select ANx for input scan.
//    //            '0' = Skip ANx for input scan.
//    AD1CSSL = 0x0C01; // Eable only AN10 and AN11 for scan.
//
//    // ------------------------ AD1PCFGH Initialization ----------------------------
//
//    // PCFG<31:16>: ADC Port Configuration Control bits.
//    //              '1' = Port pin in Digital mode, port read input enabled, ADC input multiplexor connected to AVSS.
//    //              '0' = Port pin in Analog mode, port read input disabled, ADC samples pin voltage.
//    AD1PCFGH = 0xFFFF; // AN16 and AN17 pins in Digital mode.
//
//    // ------------------------ AD1PCFGL Initialization ----------------------------
//
//    // PCFG<15:0>: ADC Port Configuration Control bits.
//    //             '1' = Port pin in Digital mode, port read input enabled, ADC input multiplexor connected to AVSS.
//    //             '0' = Port pin in Analog mode, port read input disabled, ADC samples pin voltage.
//    AD1PCFGL = 0xFFFE; // AN10 and AN11 port pins in Analog mode; all other port pins in Digital mode.
//
//    // ADON: ADC Operating Mode bit.
//    //       '1' = ADC module is operating.
//    //       '0' = ADC module is off.
//    AD1CON1bits.ADON = 1; // ADC On.
//
//}


//------------------------------- ADC1 INT Enable ----------------------------------

void adc1_int_enable(void) {

    // Timer1 Interrupt Initialization:
    IPC3bits.AD1IP = 0x01; // Set ADC1 Interrupt Priority Level: Level 1.
    IFS0bits.AD1IF = 0; // Clear ADC1 Interrupt Flag.
    IEC0bits.AD1IE = 1; // Enable ADC1 Interrupt.

}


//------------------------------- ADC1 INT Disable ----------------------------------
// 2) Call adc1_int_disable() after calling adc1_init() and before calling adc1_vib().

void adc1_int_disable(void) {

    // Timer1 Interrupt Initialization:
    IPC3bits.AD1IP = 0x01; // Set ADC1 Interrupt Priority Level: Level 1.
    IFS0bits.AD1IF = 0; // Clear ADC1 Interrupt Flag.
    IEC0bits.AD1IE = 0; // Enable ADC1 Interrupt.

}


//------------------------------- ADC INT Enable ----------------------------------
// 3) This sub-routine converts the vibration signals on AN10 and AN11.
// 4) It stores the results in the VIB_Data array, which is defined elsewhere, and
//    passed on to here as a parameter argument.
// 5) Call adc1_init() and adc1_int_disable() first before calling this sub-routine.
//    After calling those sub-routines, this subroutine can be called anytime when a
//    converssion is needed.

void adc1_vib(signed int *VIB_Data) {

    unsigned char i;

    // Sample and convert AN10:
    AD1CHS0bits.CH0SA = 10; // Choose AN10 to sample.
    AD1CON1bits.SAMP = 1; // Start sampling.
    for (i = 0; i < 25; i++); // DelayUs(10); // wait for sampling time (10us).
    AD1CON1bits.SAMP = 0; // Start conversion.
    while (!AD1CON1bits.DONE); // Wait for the conversion to complete.
    VIB_Data[0] = ADC1BUF0; // Read the conversion result.

    // Sample and convert AN11:
    AD1CHS0bits.CH0SA = 11; // Choose AN11 to sample.
    AD1CON1bits.SAMP = 1; // Start sampling.
    for (i = 0; i < 25; i++); // DelayUs(10); // wait for sampling time (10us).
    AD1CON1bits.SAMP = 0; // Start conversion.
    while (!AD1CON1bits.DONE); // Wait for the conversion to complete.
    VIB_Data[1] = ADC1BUF0; // Read the conversion result.

}

int adc1_an0(unsigned char ch) {

    int i, j;

    // Sample and convert AN10:
    AD1CHS0bits.CH0SA = ch; // Choose AN10 to sample.
    AD1CON1bits.SAMP = 1; // Start sampling.
    for (i = 0; i < 25; i++); // DelayUs(10); // wait for sampling time (10us).
    AD1CON1bits.SAMP = 0; // Start conversion.
    while (!AD1CON1bits.DONE); // Wait for the conversion to complete.
    j = ADC1BUF0; // Read the conversion result.
    return j;


}
