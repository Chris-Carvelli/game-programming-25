file(GLOB file_src_list "*.c" "*.cpp")

message("[TEST_NIX_BUILDS] cached imgui libraries read in exercises folder: ${imgui_src}")

foreach(file_src ${file_src_list})
	get_filename_component(targetname ${file_src} NAME)
	add_executable(${targetname} ${file_src} ${imgui_src})
	
	target_include_directories(${targetname} PRIVATE ${CMAKE_SOURCE_DIR}/lib/itu)
	target_include_directories(${targetname} PRIVATE ${CMAKE_SOURCE_DIR}/lib/imgui)

	target_link_libraries(${targetname} PRIVATE SDL3::SDL3)
	target_link_libraries(${targetname} PRIVATE box2d::box2d)
endforeach()
