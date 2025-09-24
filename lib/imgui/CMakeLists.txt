file(GLOB imgui_src_files "imgui/*.cpp")
set(imgui_src ${imgui_src_files} CACHE INTERNAL "")
message("[TEST_NIX_BUILDS] globbed imgui files ${imgui_src_files}")
message("[TEST_NIX_BUILDS] cached imgui files wrote in lib folder: ${imgui_src}")