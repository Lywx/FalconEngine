file(GLOB FALCON_ENGINE_HEADER_FILES *.h
	Content/*.h 
	Content/*.inl

	Core/*.h 
	Core/*.inl

	Graphics/*.h 
	Graphics/*.inl
	Geometry/*.h 
	Geometry/*.inl 

	Input/*.h
	Input/*.inl
 
	Math/*.h
	Math/*.inl

	Utility/*.h
	Utility/*.inl
	)

include_directories(${FALCON_ENGINE_INCLUDE_DIR})
link_directories(${FALCON_ENGINE_LIBRARY_DIR})

add_library(FalconEngine.Include STATIC ${FALCON_ENGINE_HEADER_FILES})
set_target_properties(FalconEngine.Include PROPERTIES LINKER_LANGUAGE CXX)

# Add to Visual Studio filter folder
set_target_properties(FalconEngine.Include PROPERTIES FOLDER "FalconEngine Targets")
