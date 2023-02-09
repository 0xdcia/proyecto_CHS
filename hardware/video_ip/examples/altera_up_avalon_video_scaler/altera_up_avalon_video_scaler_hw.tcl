# (C) 2001-2017 Intel Corporation. All rights reserved.
# Your use of Intel Corporation's design tools, logic functions and other 
# software and tools, and its AMPP partner logic functions, and any output 
# files from any of the foregoing (including device programming or simulation 
# files), and any associated documentation or information are expressly subject 
# to the terms and conditions of the Intel Program License Subscription 
# Agreement, Intel FPGA IP License Agreement, or other applicable 
# license agreement, including, without limitation, that your use is for the 
# sole purpose of programming logic devices manufactured by Intel and sold by 
# Intel or its authorized distributors.  Please refer to the applicable 
# agreement for further details.


# +----------------------------------------------------------------------------+
# |                                                                            |
# | Any megafunction design, and related net list (encrypted or decrypted),    |
# |  support information, device programming or simulation file, and any other |
# |  associated documentation or information provided by Altera or a partner   |
# |  under Altera's Megafunction Partnership Program may be used only to       |
# |  program PLD devices (but not masked PLD devices) from Altera.  Any other  |
# |  use of such megafunction design, net list, support information, device    |
# |  programming or simulation file, or any other related documentation or     |
# |  information is prohibited for any other purpose, including, but not       |
# |  limited to modification, reverse engineering, de-compiling, or use with   |
# |  any other silicon devices, unless such use is explicitly licensed under   |
# |  a separate agreement with Altera or a megafunction partner.  Title to     |
# |  the intellectual property, including patents, copyrights, trademarks,     |
# |  trade secrets, or maskworks, embodied in any such megafunction design,    |
# |  net list, support information, device programming or simulation file, or  |
# |  any other related documentation or information provided by Altera or a    |
# |  megafunction partner, remains with Altera, the megafunction partner, or   |
# |  their respective licensors.  No other licenses, including any licenses    |
# |  needed under any third party's intellectual property, are provided herein.|
# |  Copying or modifying any file, or portion thereof, to which this notice   |
# |  is attached violates this copyright.                                      |
# |                                                                            |
# | THIS FILE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR    |
# | IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   |
# | FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL    |
# | THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER |
# | LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING    |
# | FROM, OUT OF OR IN CONNECTION WITH THIS FILE OR THE USE OR OTHER DEALINGS  |
# | IN THIS FILE.                                                              |
# |                                                                            |
# | This agreement shall be governed in all respects by the laws of the State  |
# |  of California and by the laws of the United States of America.            |
# |                                                                            |
# +----------------------------------------------------------------------------+

# TCL File Generated by Altera University Program
# DO NOT MODIFY

set aup_version 17.1

source "../../../lib/aup_ip_generator.tcl"

# +-----------------------------------
# | module altera_up_avalon_video_scaler
# | 
set_module_property DESCRIPTION "Video Scaler for DE-series Boards"
set_module_property NAME altera_up_avalon_video_scaler
set_module_property VERSION $aup_version
set_module_property GROUP "University Program/Audio & Video/Video"
set_module_property AUTHOR "Intel FPGA University Program"
set_module_property DISPLAY_NAME "Scaler"
set_module_property DATASHEET_URL "[pwd]/../doc/Video.pdf"
#set_module_property TOP_LEVEL_HDL_FILE altera_up_avalon_video_scaler.v
#set_module_property TOP_LEVEL_HDL_MODULE altera_up_avalon_video_scaler
set_module_property INSTANTIATE_IN_SYSTEM_MODULE true
set_module_property HIDE_FROM_QUARTUS true
set_module_property EDITABLE false
set_module_property ANALYZE_HDL false
set_module_property VALIDATION_CALLBACK validate
set_module_property ELABORATION_CALLBACK elaborate
set_module_property GENERATION_CALLBACK generate
# | 
# +-----------------------------------

# +-----------------------------------
# | files
# | 
#add_file altera_up_avalon_video_scaler.v {SYNTHESIS SIMULATION}
add_file "hdl/altera_up_video_scaler_shrink.v" {SYNTHESIS SIMULATION}
add_file "hdl/altera_up_video_scaler_multiply_width.v" {SYNTHESIS SIMULATION}
add_file "hdl/altera_up_video_scaler_multiply_height.v" {SYNTHESIS SIMULATION}
# | 
# +-----------------------------------

# +-----------------------------------
# | parameters
# | 
add_parameter width_scaling string "0.5"
set_parameter_property width_scaling DISPLAY_NAME "Width Scaling Factor"
set_parameter_property width_scaling GROUP "Scaling Parameters"
set_parameter_property width_scaling UNITS None
set_parameter_property width_scaling AFFECTS_ELABORATION true
set_parameter_property width_scaling AFFECTS_GENERATION true
set_parameter_property width_scaling ALLOWED_RANGES {"8" "4" "2" "1" "0.75" "0.5" "0.25"}
set_parameter_property width_scaling VISIBLE true
set_parameter_property width_scaling ENABLED true

add_parameter height_scaling string "1"
set_parameter_property height_scaling DISPLAY_NAME "Height Scaling Factor"
set_parameter_property height_scaling GROUP "Scaling Parameters"
set_parameter_property height_scaling UNITS None
set_parameter_property height_scaling AFFECTS_ELABORATION true
set_parameter_property height_scaling AFFECTS_GENERATION true
set_parameter_property height_scaling ALLOWED_RANGES {"8" "4" "2" "1" "0.75" "0.5" "0.25"}
set_parameter_property height_scaling VISIBLE true
set_parameter_property height_scaling ENABLED true

add_parameter include_channel boolean false
set_parameter_property include_channel DISPLAY_NAME "Output Scaling as Channel"
set_parameter_property include_channel GROUP "Scaling Parameters"
set_parameter_property include_channel UNITS None
set_parameter_property include_channel AFFECTS_ELABORATION true
set_parameter_property include_channel AFFECTS_GENERATION true
set_parameter_property include_channel VISIBLE true
set_parameter_property include_channel ENABLED true

add_parameter channel_size integer "0"
set_parameter_property channel_size DISPLAY_NAME "Channel size (# of bits)"
set_parameter_property channel_size GROUP "Scaling Parameters"
set_parameter_property channel_size UNITS None
set_parameter_property channel_size AFFECTS_ELABORATION true
set_parameter_property channel_size AFFECTS_GENERATION true
set_parameter_property channel_size ALLOWED_RANGES 0:6
set_parameter_property channel_size VISIBLE false
set_parameter_property channel_size ENABLED true
set_parameter_property channel_size DERIVED true

add_parameter width_in positive "640"
set_parameter_property width_in DISPLAY_NAME "Width (# of pixels)"
set_parameter_property width_in GROUP "Incoming Frame Resolution"
set_parameter_property width_in UNITS None
set_parameter_property width_in AFFECTS_ELABORATION true
set_parameter_property width_in AFFECTS_GENERATION true
set_parameter_property width_in VISIBLE true
set_parameter_property width_in ENABLED true

add_parameter height_in positive "240"
set_parameter_property height_in DISPLAY_NAME "Height (# of lines)"
set_parameter_property height_in GROUP "Incoming Frame Resolution"
set_parameter_property height_in UNITS None
set_parameter_property height_in AFFECTS_ELABORATION true
set_parameter_property height_in AFFECTS_GENERATION true
set_parameter_property height_in VISIBLE true
set_parameter_property height_in ENABLED true

add_parameter width_out positive "640"
set_parameter_property width_out DISPLAY_NAME "Width (# of pixels)"
set_parameter_property width_out GROUP "Outgoing Frame Resolution"
set_parameter_property width_out UNITS None
set_parameter_property width_out AFFECTS_ELABORATION FALSE
set_parameter_property width_out AFFECTS_GENERATION true
set_parameter_property width_out DERIVED true
set_parameter_property width_out VISIBLE false
set_parameter_property width_out ENABLED true

add_parameter height_out positive "240"
set_parameter_property height_out DISPLAY_NAME "Height (# of lines)"
set_parameter_property height_out GROUP "Outgoing Frame Resolution"
set_parameter_property height_out UNITS None
set_parameter_property height_out AFFECTS_ELABORATION FALSE
set_parameter_property height_out AFFECTS_GENERATION true
set_parameter_property height_out DERIVED true
set_parameter_property height_out VISIBLE false
set_parameter_property height_out ENABLED true

add_parameter color_bits positive "8"
set_parameter_property color_bits DISPLAY_NAME "Color Bits"
set_parameter_property color_bits GROUP "Pixel Format"
set_parameter_property color_bits UNITS None
set_parameter_property color_bits AFFECTS_ELABORATION true
set_parameter_property color_bits AFFECTS_GENERATION true
set_parameter_property color_bits VISIBLE true
set_parameter_property color_bits ENABLED true

add_parameter color_planes positive "3"
set_parameter_property color_planes DISPLAY_NAME "Color Planes"
set_parameter_property color_planes GROUP "Pixel Format"
set_parameter_property color_planes UNITS None
set_parameter_property color_planes AFFECTS_ELABORATION true
set_parameter_property color_planes AFFECTS_GENERATION true
set_parameter_property color_planes ALLOWED_RANGES {1 2 3 4}
set_parameter_property color_planes VISIBLE true
set_parameter_property color_planes ENABLED true
# | 
# +-----------------------------------

# +-----------------------------------
# | connection point clk
# | 
add_interface clk clock end
set_interface_property clk enabled true

add_interface_port clk clk clk Input 1
# | 
# +-----------------------------------

# +-----------------------------------
# | connection point reset
# | 
add_interface reset reset end
set_interface_property reset associatedClock clk
set_interface_property reset enabled true
set_interface_property reset synchronousEdges DEASSERT

add_interface_port reset reset reset Input 1
# | 
# +-----------------------------------

# +-----------------------------------
# | connection point avalon_scaler_sink
# | 
add_interface avalon_scaler_sink avalon_streaming end 
set_interface_property avalon_scaler_sink associatedClock clk
set_interface_property avalon_scaler_sink associatedReset reset
set_interface_property avalon_scaler_sink errorDescriptor ""
set_interface_property avalon_scaler_sink maxChannel 0
set_interface_property avalon_scaler_sink readyLatency 0

add_interface_port avalon_scaler_sink stream_in_startofpacket startofpacket Input 1
add_interface_port avalon_scaler_sink stream_in_endofpacket endofpacket Input 1
add_interface_port avalon_scaler_sink stream_in_valid valid Input 1
add_interface_port avalon_scaler_sink stream_in_ready ready Output 1
# | 
# +-----------------------------------

# +-----------------------------------
# | connection point avalon_scaler_source
# | 
add_interface avalon_scaler_source avalon_streaming start 
set_interface_property avalon_scaler_source associatedClock clk
set_interface_property avalon_scaler_source associatedReset reset
set_interface_property avalon_scaler_source errorDescriptor ""
set_interface_property avalon_scaler_source maxChannel 0
set_interface_property avalon_scaler_source readyLatency 0

add_interface_port avalon_scaler_source stream_out_ready ready Input 1
add_interface_port avalon_scaler_source stream_out_startofpacket startofpacket Output 1
add_interface_port avalon_scaler_source stream_out_endofpacket endofpacket Output 1
add_interface_port avalon_scaler_source stream_out_valid valid Output 1
# | 
# +-----------------------------------

# +-----------------------------------
# | Validation function
# | 
proc validate {} {
	set width_scaling		[ get_parameter_value "width_scaling" ]
	set height_scaling	[ get_parameter_value "height_scaling" ]
	set include_channel	[ get_parameter_value "include_channel" ]
	set width_in			[ get_parameter_value "width_in" ]
	set height_in			[ get_parameter_value "height_in" ]
	set color_bits			[ get_parameter_value "color_bits" ]
	set color_planes		[ get_parameter_value "color_planes" ]

	set channel_size 0

	set width_out $width_in
	if { $width_scaling == "8" } {
		set width_out	[ format "%d" [ expr $width_in * 8 ] ]
		set channel_size [ expr $channel_size + 3 ]
	} elseif { $width_scaling == "4" } {
		set width_out	[ format "%d" [ expr $width_in * 4 ] ]
		set channel_size [ expr $channel_size + 2 ]
	} elseif { $width_scaling == "2" } {
		set width_out	[ format "%d" [ expr $width_in * 2 ] ]
		set channel_size [ expr $channel_size + 1 ]
	} elseif { $width_scaling == "0.75" } {
		set width_out	[ format "%.0f" [ expr ceil ($width_in * 0.75) ] ]
	} elseif { $width_scaling == "0.5" } {
		set width_out	[ format "%.0f" [ expr ceil ($width_in * 0.50) ] ]
	} elseif { $width_scaling == "0.25" } {
		set width_out	[ format "%.0f" [ expr ceil ($width_in * 0.25) ] ]
	}
	set_parameter_value "width_out" $width_out

	set height_out $height_in
	if { $height_scaling == "8" } {
		set height_out	[ format "%d" [ expr $height_in * 8 ] ]
		set channel_size [ expr $channel_size + 3 ]
	} elseif { $height_scaling == "4" } {
		set height_out	[ format "%d" [ expr $height_in * 4 ] ]
		set channel_size [ expr $channel_size + 2 ]
	} elseif { $height_scaling == "2" } {
		set height_out	[ format "%d" [ expr $height_in * 2 ] ]
		set channel_size [ expr $channel_size + 1 ]
	} elseif { $height_scaling == "0.75" } {
		set height_out	[ format "%.0f" [ expr ceil ($height_in * 0.75) ] ]
	} elseif { $height_scaling == "0.5" } {
		set height_out	[ format "%.0f" [ expr ceil ($height_in * 0.50) ] ]
	} elseif { $height_scaling == "0.25" } {
		set height_out	[ format "%.0f" [ expr ceil ($height_in * 0.25) ] ]
	}
	set_parameter_value "height_out" $height_out

	# Check if channel can be included
	set_parameter_value channel_size $channel_size
	if { $channel_size > 0 } {
		set_parameter_property include_channel ENABLED true
	} else {
		set_parameter_property include_channel ENABLED false
		set_parameter_value include_channel false
	}

	# Check if parameters are valid.
	if { ($width_scaling == "0.75") && (($width_in * 3) != ($width_out * 4)) } {
		send_message error "The input video format's width must be a multiple of 4 for a 0.75 width scaling factor"
	} elseif { ($width_scaling == "0.5") && ($width_in != ($width_out * 2)) } {
		send_message error "The input video format's width must be a multiple of 2 for a 0.5 width scaling factor"
	} elseif { ($width_scaling == "0.25") && ($width_in != ($width_out * 4)) } {
		send_message error "The input video format's width must be a multiple of 4 for a 0.25 width scaling factor"
	}
	if { ($height_scaling == "0.75") && (($height_in * 3) != ($height_out * 4)) } {
		send_message error "The input video format's height must be a multiple of 4 for a 0.75 height scaling factor"
	} elseif { ($height_scaling == "0.5") && ($height_in != ($height_out * 2)) } {
		send_message error "The input video format's height must be a multiple of 2 for a 0.5 height scaling factor"
	} elseif { ($height_scaling == "0.25") && ($height_in != ($height_out * 4)) } {
		send_message error "The input video format's height must be a multiple of 4 for a 0.25 height scaling factor"
	}
	if {( $width_scaling == "1" ) && ( $height_scaling == "1" )} {
		send_message error "Width Scaling Factor and Height Scaling Factor cannot both be set to 1"
	}

	send_message info "Change in Resolution: $width_in x $height_in -> $width_out x $height_out"
}
# | 
# +-----------------------------------

# +-----------------------------------
# | Elaboration function
# | 
proc elaborate {} {
	set width_scaling		[ get_parameter_value "width_scaling" ]
	set height_scaling	[ get_parameter_value "height_scaling" ]
	set include_channel	[ get_parameter_value "include_channel" ]
	set channel_size		[ get_parameter_value "channel_size" ]
	set width_in			[ get_parameter_value "width_in" ]
	set height_in			[ get_parameter_value "height_in" ]
	set color_bits			[ get_parameter_value "color_bits" ]
	set color_planes		[ get_parameter_value "color_planes" ]

	set dw [ expr $color_bits * $color_planes ]

	if { ($color_planes == 4) || ($color_planes == 3) } {
		set ew 2
	} else {
		set ew 1
	}

	# +-----------------------------------
	# | connection point avalon_scaler_sink
	# | 
	set_interface_property avalon_scaler_sink dataBitsPerSymbol $color_bits
	set_interface_property avalon_scaler_sink symbolsPerBeat $color_planes
	
	add_interface_port avalon_scaler_sink stream_in_data data Input $dw
#	add_interface_port avalon_scaler_sink stream_in_empty empty Input $ew
	# | 
	# +-----------------------------------

	# +-----------------------------------
	# | connection point avalon_scaler_source
	# | 
	set_interface_property avalon_scaler_source dataBitsPerSymbol $color_bits
	set_interface_property avalon_scaler_source symbolsPerBeat $color_planes

	add_interface_port avalon_scaler_source stream_out_data data Output $dw
#	add_interface_port avalon_scaler_source stream_out_empty empty Output $ew
	if { $channel_size > 0 } {
		add_interface_port avalon_scaler_source stream_out_channel channel Output $channel_size
	}
	# | 
	# +-----------------------------------
	
}
# | 
# +-----------------------------------

# +-----------------------------------
# | Generation function
# | 
proc generate {} {
	send_message info "Starting Generation of Video Scaler"

	# get parameter values
	set width_scaling		[ get_parameter_value "width_scaling" ]
	set height_scaling	[ get_parameter_value "height_scaling" ]
	set include_channel	[ get_parameter_value "include_channel" ]
	set channel_size		[ get_parameter_value "channel_size" ]
	set width_in			[ get_parameter_value "width_in" ]
	set height_in			[ get_parameter_value "height_in" ]
	set width_out			[ get_parameter_value "width_out" ]
	set height_out			[ get_parameter_value "height_out" ]
	set color_bits			[ get_parameter_value "color_bits" ]
	set color_planes		[ get_parameter_value "color_planes" ]

	# get parameter values
	set dw	[ format "DW:%d" [ expr (($color_bits * $color_planes) - 1) ] ]
	if { $include_channel } {
		set cw	[ format "CW:%d" [ expr $channel_size - 1 ] ]
	} else {
		set cw	"CW:0"
	}
	if { ($color_planes == 4) || ($color_planes == 3) } {
		set ew "EW:1"
	} else {
		set ew "EW:0"
	}
	
	set wiw		[ format "WIW:%.0f" [ expr ceil ((log ($width_in) / (log (2))) - 1.0) ] ]
	set hiw		[ format "HIW:%.0f" [ expr ceil ((log ($height_in) / (log (2))) - 1.0) ] ]
	set width	"WIDTH_IN:$width_in"

	set width_mask	"WIDTH_DROP_MASK:4'b0000"
	if { $width_scaling == "0.25" } {
		set width_mask	"WIDTH_DROP_MASK:4'b0111"
	} elseif { $width_scaling == "0.5" } {
		set width_mask	"WIDTH_DROP_MASK:4'b0101"
	} elseif { $width_scaling == "0.75" } {
		set width_mask	"WIDTH_DROP_MASK:4'b0100"
	}

	set height_mask	"HEIGHT_DROP_MASK:4'b0000"
	if { $height_scaling == "0.25" } {
		set height_mask	"HEIGHT_DROP_MASK:4'b1110"
	} elseif { $height_scaling == "0.5" } {
		set height_mask	"HEIGHT_DROP_MASK:4'b1010"
	} elseif { $height_scaling == "0.75" } {
		set height_mask	"HEIGHT_DROP_MASK:4'b1000"
	}

	if { ($width_scaling == "0.25") || ($width_scaling == "0.5") || ($width_scaling == "0.75") } {
		set mh_ww		[ format "MH_WW:%.0f" [ expr ceil ((log ($width_out) / (log (2))) - 1.0) ] ]
		set mh_width_in "MH_WIDTH_IN:$width_out"
	} else {
		set mh_ww		[ format "MH_WW:%.0f" [ expr ceil ((log ($width_in) / (log (2))) - 1.0) ] ]
		set mh_width_in "MH_WIDTH_IN:$width_in"
	}
	set mh_cw	"MH_CW:0"
	if { $height_scaling == "8" } {
		set mh_cw	"MH_CW:2"
	} elseif { $height_scaling == "4" } {
		set mh_cw	"MH_CW:1"
	}

	set mw_cw	"MW_CW:0"
	if { $width_scaling == "8" } {
		set mw_cw	"MW_CW:2"
	} elseif { $width_scaling == "4" } {
		set mw_cw	"MW_CW:1"
	}

	# set section values
	set use_image_shrink "USE_IMAGE_SHRINK:0"
	if { ($width_scaling == "0.75") || ($width_scaling == "0.5") || ($width_scaling == "0.25") } {
		set use_image_shrink "USE_IMAGE_SHRINK:1"
	} elseif { ($height_scaling == "0.75") || ($height_scaling == "0.5") || ($height_scaling == "0.25") } {
		set use_image_shrink "USE_IMAGE_SHRINK:1"
	}

	set use_width_enlarge "USE_WIDTH_ENLARGE:0"
	if { ($width_scaling == "8") || ($width_scaling == "4") || ($width_scaling == "2") } {
		set use_width_enlarge "USE_WIDTH_ENLARGE:1"
	}

	set use_height_enlarge "USE_HEIGHT_ENLARGE:0"
	if { ($height_scaling == "8") || ($height_scaling == "4") || ($height_scaling == "2") } {
		set use_height_enlarge "USE_HEIGHT_ENLARGE:1"
	}

	# set arguments
	set params "$dw;$cw;$ew;$wiw;$hiw;$width;$width_mask;$height_mask;$mh_ww;$mh_width_in;$mh_cw;$mw_cw"
	set sections "$use_image_shrink;$use_width_enlarge;$use_height_enlarge"

	# get generation settings
#	set dest_language	[ get_generation_property HDL_LANGUAGE ]
	set dest_dir 		[ get_generation_property OUTPUT_DIRECTORY ]
	set dest_name		[ get_generation_property OUTPUT_NAME ]
	
	add_file "$dest_dir$dest_name.v" {SYNTHESIS SIMULATION}
	# add_file "$dest_dir/altera_up_video_scaler_shrink.v" SYNTHESIS
	# add_file "$dest_dir/altera_up_video_scaler_multiply_width.v" SYNTHESIS
	# add_file "$dest_dir/altera_up_video_scaler_multiply_height.v" SYNTHESIS

	# Generate HDL
	alt_up_generate "$dest_dir$dest_name.v" "hdl/altera_up_avalon_video_scaler.v" "altera_up_avalon_video_scaler" $dest_name $params $sections
	# file copy -force "hdl/altera_up_video_scaler_shrink.v" $dest_dir
	# file copy -force "hdl/altera_up_video_scaler_multiply_width.v" $dest_dir
	# file copy -force "hdl/altera_up_video_scaler_multiply_height.v" $dest_dir
}
# | 
# +-----------------------------------


## Add documentation links for user guide and/or release notes
add_documentation_link "User Guide" https://documentation.altera.com/#/link/bhc1411020596507/bhc1411020313996
add_documentation_link "Release Notes" https://documentation.altera.com/#/link/hco1421698042087/hco1421697985505
