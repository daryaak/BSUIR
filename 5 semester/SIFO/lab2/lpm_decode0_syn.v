// megafunction wizard: %LPM_DECODE%
// GENERATION: STANDARD
// VERSION: WM1.0
// MODULE: lpm_decode 

// ============================================================
// File Name: lpm_decode0.v
// Megafunction Name(s):
// 			lpm_decode
//
// Simulation Library Files(s):
// 			lpm
// ============================================================
// ************************************************************
// THIS IS A WIZARD-GENERATED FILE. DO NOT EDIT THIS FILE!
//
// 9.1 Build 222 10/21/2009 SJ Web Edition
// ************************************************************


//Copyright (C) 1991-2009 Altera Corporation
//Your use of Altera Corporation's design tools, logic functions 
//and other software and tools, and its AMPP partner logic 
//functions, and any output files from any of the foregoing 
//(including device programming or simulation files), and any 
//associated documentation or information are expressly subject 
//to the terms and conditions of the Altera Program License 
//Subscription Agreement, Altera MegaCore Function License 
//Agreement, or other applicable license agreement, including, 
//without limitation, that your use is for the sole purpose of 
//programming logic devices manufactured by Altera and sold by 
//Altera or its authorized distributors.  Please refer to the 
//applicable agreement for further details.


//lpm_decode DEVICE_FAMILY="Stratix II" LPM_DECODES=16 LPM_WIDTH=4 data eq
//VERSION_BEGIN 9.1 cbx_cycloneii 2009:10:21:21:22:16:SJ cbx_lpm_add_sub 2009:10:21:21:22:16:SJ cbx_lpm_compare 2009:10:21:21:22:16:SJ cbx_lpm_decode 2009:10:21:21:22:16:SJ cbx_mgl 2009:10:21:21:37:49:SJ cbx_stratix 2009:10:21:21:22:16:SJ cbx_stratixii 2009:10:21:21:22:16:SJ  VERSION_END
// synthesis VERILOG_INPUT_VERSION VERILOG_2001
// altera message_off 10463


//synthesis_resources = lut 16 
//synopsys translate_off
`timescale 1 ps / 1 ps
//synopsys translate_on
module  lpm_decode0_decode
	( 
	data,
	eq) /* synthesis synthesis_clearbox=1 */;
	input   [3:0]  data;
	output   [15:0]  eq;
`ifndef ALTERA_RESERVED_QIS
// synopsys translate_off
`endif
	tri0   [3:0]  data;
`ifndef ALTERA_RESERVED_QIS
// synopsys translate_on
`endif

	wire  [2:0]  data_wire;
	wire  enable_wire1;
	wire  enable_wire2;
	wire  [15:0]  eq_node;
	wire  [7:0]  eq_wire1;
	wire  [7:0]  eq_wire2;
	wire  [3:0]  w_anode102w;
	wire  [3:0]  w_anode112w;
	wire  [3:0]  w_anode122w;
	wire  [3:0]  w_anode132w;
	wire  [3:0]  w_anode142w;
	wire  [3:0]  w_anode152w;
	wire  [3:0]  w_anode162w;
	wire  [3:0]  w_anode21w;
	wire  [3:0]  w_anode31w;
	wire  [3:0]  w_anode41w;
	wire  [3:0]  w_anode4w;
	wire  [3:0]  w_anode51w;
	wire  [3:0]  w_anode61w;
	wire  [3:0]  w_anode71w;
	wire  [3:0]  w_anode81w;
	wire  [3:0]  w_anode91w;

	assign
		data_wire = data[2:0],
		enable_wire1 = (~ data[3]),
		enable_wire2 = data[3],
		eq = eq_node,
		eq_node = {eq_wire2[7:0], eq_wire1},
		eq_wire1 = {w_anode81w[3], w_anode71w[3], w_anode61w[3], w_anode51w[3], w_anode41w[3], w_anode31w[3], w_anode21w[3], w_anode4w[3]},
		eq_wire2 = {w_anode162w[3], w_anode152w[3], w_anode142w[3], w_anode132w[3], w_anode122w[3], w_anode112w[3], w_anode102w[3], w_anode91w[3]},
		w_anode102w = {(w_anode102w[2] & (~ data_wire[2])), (w_anode102w[1] & (~ data_wire[1])), (w_anode102w[0] & data_wire[0]), enable_wire2},
		w_anode112w = {(w_anode112w[2] & (~ data_wire[2])), (w_anode112w[1] & data_wire[1]), (w_anode112w[0] & (~ data_wire[0])), enable_wire2},
		w_anode122w = {(w_anode122w[2] & (~ data_wire[2])), (w_anode122w[1] & data_wire[1]), (w_anode122w[0] & data_wire[0]), enable_wire2},
		w_anode132w = {(w_anode132w[2] & data_wire[2]), (w_anode132w[1] & (~ data_wire[1])), (w_anode132w[0] & (~ data_wire[0])), enable_wire2},
		w_anode142w = {(w_anode142w[2] & data_wire[2]), (w_anode142w[1] & (~ data_wire[1])), (w_anode142w[0] & data_wire[0]), enable_wire2},
		w_anode152w = {(w_anode152w[2] & data_wire[2]), (w_anode152w[1] & data_wire[1]), (w_anode152w[0] & (~ data_wire[0])), enable_wire2},
		w_anode162w = {(w_anode162w[2] & data_wire[2]), (w_anode162w[1] & data_wire[1]), (w_anode162w[0] & data_wire[0]), enable_wire2},
		w_anode21w = {(w_anode21w[2] & (~ data_wire[2])), (w_anode21w[1] & (~ data_wire[1])), (w_anode21w[0] & data_wire[0]), enable_wire1},
		w_anode31w = {(w_anode31w[2] & (~ data_wire[2])), (w_anode31w[1] & data_wire[1]), (w_anode31w[0] & (~ data_wire[0])), enable_wire1},
		w_anode41w = {(w_anode41w[2] & (~ data_wire[2])), (w_anode41w[1] & data_wire[1]), (w_anode41w[0] & data_wire[0]), enable_wire1},
		w_anode4w = {(w_anode4w[2] & (~ data_wire[2])), (w_anode4w[1] & (~ data_wire[1])), (w_anode4w[0] & (~ data_wire[0])), enable_wire1},
		w_anode51w = {(w_anode51w[2] & data_wire[2]), (w_anode51w[1] & (~ data_wire[1])), (w_anode51w[0] & (~ data_wire[0])), enable_wire1},
		w_anode61w = {(w_anode61w[2] & data_wire[2]), (w_anode61w[1] & (~ data_wire[1])), (w_anode61w[0] & data_wire[0]), enable_wire1},
		w_anode71w = {(w_anode71w[2] & data_wire[2]), (w_anode71w[1] & data_wire[1]), (w_anode71w[0] & (~ data_wire[0])), enable_wire1},
		w_anode81w = {(w_anode81w[2] & data_wire[2]), (w_anode81w[1] & data_wire[1]), (w_anode81w[0] & data_wire[0]), enable_wire1},
		w_anode91w = {(w_anode91w[2] & (~ data_wire[2])), (w_anode91w[1] & (~ data_wire[1])), (w_anode91w[0] & (~ data_wire[0])), enable_wire2};
endmodule //lpm_decode0_decode
//VALID FILE


// synopsys translate_off
`timescale 1 ps / 1 ps
// synopsys translate_on
module lpm_decode0 (
	data,
	eq2,
	eq6)/* synthesis synthesis_clearbox = 1 */;

	input	[3:0]  data;
	output	  eq2;
	output	  eq6;

	wire [15:0] sub_wire0;
	wire [6:6] sub_wire2 = sub_wire0[6:6];
	wire [2:2] sub_wire1 = sub_wire0[2:2];
	wire  eq2 = sub_wire1;
	wire  eq6 = sub_wire2;

	lpm_decode0_decode	lpm_decode0_decode_component (
				.data (data),
				.eq (sub_wire0));

endmodule

// ============================================================
// CNX file retrieval info
// ============================================================
// Retrieval info: PRIVATE: BaseDec NUMERIC "1"
// Retrieval info: PRIVATE: EnableInput NUMERIC "0"
// Retrieval info: PRIVATE: INTENDED_DEVICE_FAMILY STRING "Stratix II"
// Retrieval info: PRIVATE: LPM_PIPELINE NUMERIC "0"
// Retrieval info: PRIVATE: Latency NUMERIC "0"
// Retrieval info: PRIVATE: SYNTH_WRAPPER_GEN_POSTFIX STRING "1"
// Retrieval info: PRIVATE: aclr NUMERIC "0"
// Retrieval info: PRIVATE: clken NUMERIC "0"
// Retrieval info: PRIVATE: eq0 NUMERIC "0"
// Retrieval info: PRIVATE: eq1 NUMERIC "0"
// Retrieval info: PRIVATE: eq10 NUMERIC "0"
// Retrieval info: PRIVATE: eq11 NUMERIC "0"
// Retrieval info: PRIVATE: eq12 NUMERIC "0"
// Retrieval info: PRIVATE: eq13 NUMERIC "0"
// Retrieval info: PRIVATE: eq14 NUMERIC "0"
// Retrieval info: PRIVATE: eq15 NUMERIC "0"
// Retrieval info: PRIVATE: eq2 NUMERIC "1"
// Retrieval info: PRIVATE: eq3 NUMERIC "0"
// Retrieval info: PRIVATE: eq4 NUMERIC "0"
// Retrieval info: PRIVATE: eq5 NUMERIC "0"
// Retrieval info: PRIVATE: eq6 NUMERIC "1"
// Retrieval info: PRIVATE: eq7 NUMERIC "0"
// Retrieval info: PRIVATE: eq8 NUMERIC "0"
// Retrieval info: PRIVATE: eq9 NUMERIC "0"
// Retrieval info: PRIVATE: nBit NUMERIC "4"
// Retrieval info: CONSTANT: LPM_DECODES NUMERIC "16"
// Retrieval info: CONSTANT: LPM_TYPE STRING "LPM_DECODE"
// Retrieval info: CONSTANT: LPM_WIDTH NUMERIC "4"
// Retrieval info: USED_PORT: @eq 0 0 LPM_DECODES 0 OUTPUT NODEFVAL @eq[LPM_DECODES-1..0]
// Retrieval info: USED_PORT: data 0 0 4 0 INPUT NODEFVAL data[3..0]
// Retrieval info: USED_PORT: eq2 0 0 0 0 OUTPUT NODEFVAL eq2
// Retrieval info: USED_PORT: eq6 0 0 0 0 OUTPUT NODEFVAL eq6
// Retrieval info: CONNECT: @data 0 0 4 0 data 0 0 4 0
// Retrieval info: CONNECT: eq2 0 0 0 0 @eq 0 0 1 2
// Retrieval info: CONNECT: eq6 0 0 0 0 @eq 0 0 1 6
// Retrieval info: LIBRARY: lpm lpm.lpm_components.all
// Retrieval info: GEN_FILE: TYPE_NORMAL lpm_decode0.tdf TRUE
// Retrieval info: GEN_FILE: TYPE_NORMAL lpm_decode0.inc TRUE
// Retrieval info: GEN_FILE: TYPE_NORMAL lpm_decode0.cmp FALSE
// Retrieval info: GEN_FILE: TYPE_NORMAL lpm_decode0.bsf TRUE FALSE
// Retrieval info: GEN_FILE: TYPE_NORMAL lpm_decode0_inst.tdf FALSE
// Retrieval info: GEN_FILE: TYPE_NORMAL lpm_decode0_syn.v TRUE
// Retrieval info: LIB_FILE: lpm
