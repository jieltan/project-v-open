////////////////////////////////////////////////////////////////////////////////////////////
// sparse_ram.svh
// Jielun Tan (jieltan@umich.edu)
// James Connolly (conjam@umich.edu)
// 08/29/2018
//
// This file contains an implementation of a memory model implemented using associative 
// arrays and supports parameterized block sizes
////////////////////////////////////////////////////////////////////////////////////////////



module sparse_ram #(parameter BLOCK_SIZE = 64, parameter BUS_WIDTH = 64, parameter ADDR_WIDTH = 32) (
	input clock, reset,
	input [BUS_WIDTH-1:0] req_data_in,
	input [ADDR_WIDTH-1:0] req_addr_in,
	input req_valid_in, 
	input resp_ready_in,

	output [BUS_WIDTH-1:0] resp_data_out,
	output [ADDR_WIDTH-1:0] resp_data_out,
	output resp_ready_out,
	output req_ready_out
);
	
