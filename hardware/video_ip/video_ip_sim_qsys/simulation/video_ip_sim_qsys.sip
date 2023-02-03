set_global_assignment -entity "video_ip_sim_qsys" -library "lib_video_ip_sim_qsys" -name IP_TOOL_NAME "Qsys"
set_global_assignment -entity "video_ip_sim_qsys" -library "lib_video_ip_sim_qsys" -name IP_TOOL_VERSION "17.1"
set_global_assignment -entity "video_ip_sim_qsys" -library "lib_video_ip_sim_qsys" -name IP_TOOL_ENV "Qsys"
set_global_assignment -library "lib_video_ip_sim_qsys" -name SPD_FILE [file join $::quartus(sip_path) "../video_ip_sim_qsys.spd"]
set_global_assignment -library "lib_video_ip_sim_qsys" -name MISC_FILE [file join $::quartus(sip_path) "../../video_ip_sim_qsys.qsys"]

set_global_assignment -library "lib_video_ip_sim_qsys" -name MISC_FILE [file join $::quartus(sip_path) "video_ip_sim_qsys.v"]
