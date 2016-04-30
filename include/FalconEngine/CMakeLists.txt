file(GLOB FALCON_ENGINE_HEADER_FILES *.h
	Content/*.h
	Core/*.h
	Graphics/*.h 
	Geometry/*.h 
	Input/*.h
	Math/*.h
	Utility/*.h)

include_directories(${FALCON_ENGINE_INCLUDE_DIR})
link_directories(${FALCON_ENGINE_LIBRARY_DIR})

add_library(FalconEngine.Include STATIC ${FALCON_ENGINE_HEADER_FILES})
set_target_properties(FalconEngine.Include PROPERTIES LINKER_LANGUAGE CXX)

# Add to Visual Studio filter folder
set_target_properties(FalconEngine.Include PROPERTIES FOLDER "FalconEngine Targets")
