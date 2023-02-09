# TCL File Generated by Component Editor 17.1
# Thu Feb 09 17:41:00 CET 2023
# DO NOT MODIFY


# 
# video_effects "video_effects" v0
# Juan Del Pino, David Garc�a, Alejandro Jorge, Francisco Zapata, Ferr�n Zafrilla, Arnau Mart�nez 2023.02.09.17:41:00
# IP de efectos de v�deo para el proyecto
# 

# 
# request TCL package from ACDS 16.1
# 
package require -exact qsys 16.1


# 
# module video_effects
# 
set_module_property DESCRIPTION "IP de efectos de v�deo para el proyecto"
set_module_property NAME video_effects
set_module_property VERSION 0
set_module_property INTERNAL false
set_module_property OPAQUE_ADDRESS_MAP true
set_module_property GROUP proj_video_effects_ip
set_module_property AUTHOR "Juan Del Pino, David Garc�a, Alejandro Jorge, Francisco Zapata, Ferr�n Zafrilla, Arnau Mart�nez"
set_module_property DISPLAY_NAME video_effects
set_module_property INSTANTIATE_IN_SYSTEM_MODULE true
set_module_property EDITABLE true
set_module_property REPORT_TO_TALKBACK false
set_module_property ALLOW_GREYBOX_GENERATION false
set_module_property REPORT_HIERARCHY false


# 
# file sets
# 
add_fileset QUARTUS_SYNTH QUARTUS_SYNTH "" ""
set_fileset_property QUARTUS_SYNTH TOP_LEVEL video_ip
set_fileset_property QUARTUS_SYNTH ENABLE_RELATIVE_INCLUDE_PATHS false
set_fileset_property QUARTUS_SYNTH ENABLE_FILE_OVERWRITE_MODE false
add_fileset_file video_ip.v VERILOG PATH verilog/video_ip.v TOP_LEVEL_FILE
add_fileset_file avalon_mm_slave_interface.v VERILOG PATH verilog/avalon_mm_slave_interface.v
add_fileset_file avalon_st_sink_interface.v VERILOG PATH verilog/avalon_st_sink_interface.v
add_fileset_file avalon_st_source_interface.v VERILOG PATH verilog/avalon_st_source_interface.v
add_fileset_file video_effects.v VERILOG PATH verilog/video_effects.v

add_fileset SIM_VERILOG SIM_VERILOG "" ""
set_fileset_property SIM_VERILOG TOP_LEVEL video_ip
set_fileset_property SIM_VERILOG ENABLE_RELATIVE_INCLUDE_PATHS false
set_fileset_property SIM_VERILOG ENABLE_FILE_OVERWRITE_MODE false
add_fileset_file video_ip.v VERILOG PATH verilog/video_ip.v
add_fileset_file avalon_mm_slave_interface.v VERILOG PATH verilog/avalon_mm_slave_interface.v
add_fileset_file avalon_st_sink_interface.v VERILOG PATH verilog/avalon_st_sink_interface.v
add_fileset_file avalon_st_source_interface.v VERILOG PATH verilog/avalon_st_source_interface.v
add_fileset_file video_effects.v VERILOG PATH verilog/video_effects.v


# 
# parameters
# 


# 
# display items
# 


# 
# connection point avalon_streaming_sink
# 
add_interface avalon_streaming_sink avalon_streaming end
set_interface_property avalon_streaming_sink associatedClock clock
set_interface_property avalon_streaming_sink associatedReset reset
set_interface_property avalon_streaming_sink dataBitsPerSymbol 16
set_interface_property avalon_streaming_sink errorDescriptor ""
set_interface_property avalon_streaming_sink firstSymbolInHighOrderBits true
set_interface_property avalon_streaming_sink maxChannel 0
set_interface_property avalon_streaming_sink readyLatency 0
set_interface_property avalon_streaming_sink ENABLED true
set_interface_property avalon_streaming_sink EXPORT_OF ""
set_interface_property avalon_streaming_sink PORT_NAME_MAP ""
set_interface_property avalon_streaming_sink CMSIS_SVD_VARIABLES ""
set_interface_property avalon_streaming_sink SVD_ADDRESS_GROUP ""

add_interface_port avalon_streaming_sink startofpacket_in startofpacket Input 1
add_interface_port avalon_streaming_sink endofpacket_in endofpacket Input 1
add_interface_port avalon_streaming_sink data_in data Input 16
add_interface_port avalon_streaming_sink ready_out ready Output 1
add_interface_port avalon_streaming_sink valid_in valid Input 1


# 
# connection point avalon_streaming_source
# 
add_interface avalon_streaming_source avalon_streaming start
set_interface_property avalon_streaming_source associatedClock clock
set_interface_property avalon_streaming_source associatedReset reset
set_interface_property avalon_streaming_source dataBitsPerSymbol 16
set_interface_property avalon_streaming_source errorDescriptor ""
set_interface_property avalon_streaming_source firstSymbolInHighOrderBits true
set_interface_property avalon_streaming_source maxChannel 0
set_interface_property avalon_streaming_source readyLatency 0
set_interface_property avalon_streaming_source ENABLED true
set_interface_property avalon_streaming_source EXPORT_OF ""
set_interface_property avalon_streaming_source PORT_NAME_MAP ""
set_interface_property avalon_streaming_source CMSIS_SVD_VARIABLES ""
set_interface_property avalon_streaming_source SVD_ADDRESS_GROUP ""

add_interface_port avalon_streaming_source data_out data Output 16
add_interface_port avalon_streaming_source startofpacket_out startofpacket Output 1
add_interface_port avalon_streaming_source endofpacket_out endofpacket Output 1
add_interface_port avalon_streaming_source ready_in ready Input 1
add_interface_port avalon_streaming_source valid_out valid Output 1


# 
# connection point clock
# 
add_interface clock clock end
set_interface_property clock clockRate 0
set_interface_property clock ENABLED true
set_interface_property clock EXPORT_OF ""
set_interface_property clock PORT_NAME_MAP ""
set_interface_property clock CMSIS_SVD_VARIABLES ""
set_interface_property clock SVD_ADDRESS_GROUP ""

add_interface_port clock clk clk Input 1


# 
# connection point reset
# 
add_interface reset reset end
set_interface_property reset associatedClock clock
set_interface_property reset synchronousEdges DEASSERT
set_interface_property reset ENABLED true
set_interface_property reset EXPORT_OF ""
set_interface_property reset PORT_NAME_MAP ""
set_interface_property reset CMSIS_SVD_VARIABLES ""
set_interface_property reset SVD_ADDRESS_GROUP ""

add_interface_port reset reset reset Input 1


# 
# connection point avalon_slave
# 
add_interface avalon_slave avalon end
set_interface_property avalon_slave addressUnits WORDS
set_interface_property avalon_slave associatedClock clock
set_interface_property avalon_slave associatedReset reset
set_interface_property avalon_slave bitsPerSymbol 8
set_interface_property avalon_slave burstOnBurstBoundariesOnly false
set_interface_property avalon_slave burstcountUnits WORDS
set_interface_property avalon_slave explicitAddressSpan 0
set_interface_property avalon_slave holdTime 0
set_interface_property avalon_slave linewrapBursts false
set_interface_property avalon_slave maximumPendingReadTransactions 0
set_interface_property avalon_slave maximumPendingWriteTransactions 0
set_interface_property avalon_slave readLatency 0
set_interface_property avalon_slave readWaitTime 1
set_interface_property avalon_slave setupTime 0
set_interface_property avalon_slave timingUnits Cycles
set_interface_property avalon_slave writeWaitTime 0
set_interface_property avalon_slave ENABLED true
set_interface_property avalon_slave EXPORT_OF ""
set_interface_property avalon_slave PORT_NAME_MAP ""
set_interface_property avalon_slave CMSIS_SVD_VARIABLES ""
set_interface_property avalon_slave SVD_ADDRESS_GROUP ""

add_interface_port avalon_slave address address Input 3
add_interface_port avalon_slave read read Input 1
add_interface_port avalon_slave readdata readdata Output 32
add_interface_port avalon_slave write write Input 1
add_interface_port avalon_slave writedata writedata Input 32
add_interface_port avalon_slave chipselect chipselect Input 1
set_interface_assignment avalon_slave embeddedsw.configuration.isFlash 0
set_interface_assignment avalon_slave embeddedsw.configuration.isMemoryDevice 0
set_interface_assignment avalon_slave embeddedsw.configuration.isNonVolatileStorage 0
set_interface_assignment avalon_slave embeddedsw.configuration.isPrintableDevice 0


# 
# connection point irq_sender
# 
add_interface irq_sender interrupt end
set_interface_property irq_sender associatedAddressablePoint avalon_slave
set_interface_property irq_sender associatedClock clock
set_interface_property irq_sender associatedReset reset
set_interface_property irq_sender bridgedReceiverOffset ""
set_interface_property irq_sender bridgesToReceiver ""
set_interface_property irq_sender ENABLED true
set_interface_property irq_sender EXPORT_OF ""
set_interface_property irq_sender PORT_NAME_MAP ""
set_interface_property irq_sender CMSIS_SVD_VARIABLES ""
set_interface_property irq_sender SVD_ADDRESS_GROUP ""

add_interface_port irq_sender irq_sender irq Output 1

