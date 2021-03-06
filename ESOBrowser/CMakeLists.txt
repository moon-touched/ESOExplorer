add_executable(ESOBrowser
	BinaryFileViewWidget.cpp
	BinaryFileViewWidget.h
	DatabaseBrowserWidget.cpp
	DatabaseBrowserWidget.h
	DatabaseBrowserWidget.ui
	DatabaseRecordViewerItemDelegate.cpp
	DatabaseRecordViewerItemDelegate.h
	DatabaseRecordViewerWidget.cpp
	DatabaseRecordViewerWidget.h
	DatabaseRecordViewerWidget.ui
	DataStorage.cpp
	DataStorage.h
	DDSFileViewWidget.cpp
	DDSFileViewWidget.h
	DDSTexture.cpp
	DDSTexture.h
	DefSearchWidget.cpp
	DefSearchWidget.h
	DefSearchWidget.ui
	DummyTabWidget.cpp
	DummyTabWidget.h
	DummyTabWidget.ui
	ESOBrowserMainWindow.cpp
	ESOBrowserMainWindow.h
	ESOBrowserMainWindow.ui
	ESOBrowserSelectDepotDialog.cpp
	ESOBrowserSelectDepotDialog.h
	ESOBrowserSelectDepotDialog.ui
	ESODatabaseDefModel.cpp
	ESODatabaseDefModel.h
	ESODatabaseModel.cpp
	ESODatabaseModel.h
	ESOFilesystemModel.cpp
	ESOFilesystemModel.h
	DatabaseRecordViewerWidget.cpp
	DatabaseRecordViewerWidget.h
	FilamentEngineInstance.cpp
	FilamentEngineInstance.h
	FilamentTypeHelpers.cpp
	FilamentTypeHelpers.h
	FilamentViewport.cpp
	FilamentViewport.h
	FileNameExtractor.cpp
	FileNameExtractor.h
	FileNameExtractorCallbacks.cpp
	FileNameExtractorCallbacks.h
	FilesystemBrowserWidget.cpp
	FilesystemBrowserWidget.h
	FilesystemBrowserWidget.ui
	FileTypeDetector.cpp
	FileTypeDetector.h
	FileViewWidget.cpp
	FileViewWidget.h
	FileViewWidget.ui
	Granny2FileViewWidget.cpp
	Granny2FileViewWidget.h
	Granny2Model.cpp
	Granny2Model.h
	Granny2Renderable.cpp
	Granny2Renderable.h
	HexView.cpp
	HexView.h
	main.cpp
	ModelViewerWidget.cpp
	ModelViewerWidget.h
	ModelViewerWidget.ui
	NameHarvestingEngine.cpp
	NameHarvestingEngine.h
	NameHarvestingWidget.cpp
	NameHarvestingWidget.h
	NameHarvestingWidget.ui
	PersistentTabWidget.cpp
	PersistentTabWidget.h
	TextFileViewWidget.cpp
	TextFileViewWidget.h
	UISettingsDirectiveFile.cpp
	UISettingsDirectiveFile.h
)

target_link_libraries(ESOBrowser PRIVATE Qt5::Widgets Qt5::Sql ESOData DirectXTex granny filament::filament)

set_target_properties(ESOBrowser PROPERTIES 
	AUTOUIC TRUE
	AUTOMOC TRUE
	AUTORCC TRUE
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED TRUE
)

add_custom_target(CopyAssets
	${AssetCopyCommands}
	COMMAND cmake -E copy_if_different ${GRANNY2_EXECUTABLE} $<TARGET_FILE_DIR:ESOBrowser>
)

add_dependencies(ESOBrowser shaders)
