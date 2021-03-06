set(commands)
set(generated_materials)

foreach(dir_file IN ITEMS
	${ESOData_SOURCE_DIR}/Directives/FilenameHarvesting.dir
	${ESOData_SOURCE_DIR}/Directives/Filesystem.dir
	${ESOData_SOURCE_DIR}/Directives/SupportedVersions.dir
	${CMAKE_CURRENT_SOURCE_DIR}/UISettings.dir
)

	list(APPEND commands COMMAND cmake -E copy_if_different ${dir_file} $<TARGET_FILE_DIR:ESOBrowser>)
	
endforeach()

file(GLOB_RECURSE database_files "${ESOData_SOURCE_DIR}/Directives/Database/*.dir")
foreach(database_file IN LISTS database_files)
	file(RELATIVE_PATH relative "${ESOData_SOURCE_DIR}/Directives" "${database_file}")
	
	get_filename_component(subdirectory "${relative}" DIRECTORY)

	if(subdirectory)
		list(APPEND commands COMMAND cmake -E make_directory $<TARGET_FILE_DIR:ESOBrowser>/${subdirectory})
	endif()

	list(APPEND commands COMMAND cmake -E copy_if_different ${database_file} $<TARGET_FILE_DIR:ESOBrowser>/${relative})
endforeach()

foreach(mat_file IN ITEMS
	ESOLikeMaterialMasked
	ESOLikeMaterialOpaque
	ESOLikeMaterialTransparent
)

	list(APPEND generated_files ${CMAKE_CURRENT_BINARY_DIR}/${mat_file}.matc)

	add_custom_command(
		OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${mat_file}.matc
		COMMAND filament::matc -o ${CMAKE_CURRENT_BINARY_DIR}/${mat_file}.matc ${CMAKE_CURRENT_SOURCE_DIR}/${mat_file}.mat
		MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${mat_file}.mat
		VERBATIM
	)
	
	list(APPEND commands COMMAND cmake -E copy_if_different ${CMAKE_CURRENT_BINARY_DIR}/${mat_file}.matc $<TARGET_FILE_DIR:ESOBrowser>)
endforeach()

add_custom_target(shaders ALL DEPENDS ${generated_files})
set(AssetCopyCommands ${commands} PARENT_SCOPE)
