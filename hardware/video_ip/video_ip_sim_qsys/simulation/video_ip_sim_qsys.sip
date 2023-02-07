set_global_assignment -entity "video_ip_sim_qsys" -library "lib_video_ip_sim_qsys" -name IP_TOOL_NAME "Qsys"
set_global_assignment -entity "video_ip_sim_qsys" -library "lib_video_ip_sim_qsys" -name IP_TOOL_VERSION "17.1"
set_global_assignment -entity "video_ip_sim_qsys" -library "lib_video_ip_sim_qsys" -name IP_TOOL_ENV "Qsys"
set_global_assignment -library "lib_video_ip_sim_qsys" -name SPD_FILE [file join $::quartus(sip_path) "../video_ip_sim_qsys.spd"]
set_global_assignment -library "lib_video_ip_sim_qsys" -name MISC_FILE [file join $::quartus(sip_path) "../../video_ip_sim_qsys.qsys"]

set_global_assignment -library "lib_video_ip_sim_qsys" -name MISC_FILE [file join $::quartus(sip_path) "video_ip_sim_qsys.v"]
set_global_assignment -library "lib_video_ip_sim_qsys" -name MISC_FILE [file join $::quartus(sip_path) "submodules/altera_reset_controller.v"]
set_global_assignment -library "lib_video_ip_sim_qsys" -name MISC_FILE [file join $::quartus(sip_path) "submodules/altera_reset_synchronizer.v"]
set_global_assignment -library "lib_video_ip_sim_qsys" -name MISC_FILE [file join $::quartus(sip_path) "submodules/altera_reset_controller.sdc"]
set_global_assignment -library "lib_video_ip_sim_qsys" -name MISC_FILE [file join $::quartus(sip_path) "submodules/video_ip_sim_qsys_mm_interconnect_0.v"]
set_global_assignment -library "lib_video_ip_sim_qsys" -name MISC_FILE [file join $::quartus(sip_path) "submodules/altera_merlin_slave_translator.sv"]
set_global_assignment -library "lib_video_ip_sim_qsys" -name MISC_FILE [file join $::quartus(sip_path) "submodules/altera_merlin_master_translator.sv"]
set_global_assignment -library "lib_video_ip_sim_qsys" -name MISC_FILE [file join $::quartus(sip_path) "submodules/video_ip.v"]
set_global_assignment -library "lib_video_ip_sim_qsys" -name MISC_FILE [file join $::quartus(sip_path) "submodules/avalon_mm_slave_interface.v"]
set_global_assignment -library "lib_video_ip_sim_qsys" -name MISC_FILE [file join $::quartus(sip_path) "submodules/avalon_st_sink_interface.v"]
set_global_assignment -library "lib_video_ip_sim_qsys" -name MISC_FILE [file join $::quartus(sip_path) "submodules/avalon_st_source_interface.v"]
set_global_assignment -library "lib_video_ip_sim_qsys" -name MISC_FILE [file join $::quartus(sip_path) "submodules/video_effects.v"]
set_global_assignment -library "lib_video_ip_sim_qsys" -name MISC_FILE [file join $::quartus(sip_path) "submodules/verbosity_pkg.sv"]
set_global_assignment -library "lib_video_ip_sim_qsys" -name MISC_FILE [file join $::quartus(sip_path) "submodules/avalon_utilities_pkg.sv"]
set_global_assignment -library "lib_video_ip_sim_qsys" -name MISC_FILE [file join $::quartus(sip_path) "submodules/altera_avalon_st_source_bfm.sv"]
set_global_assignment -library "lib_video_ip_sim_qsys" -name MISC_FILE [file join $::quartus(sip_path) "submodules/altera_avalon_st_sink_bfm.sv"]
set_global_assignment -library "lib_video_ip_sim_qsys" -name MISC_FILE [file join $::quartus(sip_path) "submodules/avalon_mm_pkg.sv"]
set_global_assignment -library "lib_video_ip_sim_qsys" -name MISC_FILE [file join $::quartus(sip_path) "submodules/altera_avalon_mm_master_bfm.sv"]
