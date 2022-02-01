
TYPE
	RecipeCommands_type : 	STRUCT 
		StoreMachineSettings : BOOL;
		FactoryResetMachineSettings : BOOL;
		SaveCurrentRecipe : BOOL;
		ImportFromUSB : BOOL;
		ExportToUSB : BOOL;
		UpdatePreviewParameters : BOOL;
		SaveSelectedRecipe : BOOL;
	END_STRUCT;
	RecipeStatus_type : 	STRUCT 
		Category : STRING[30];
		LastLoadedConfigRecipe : STRING[255];
		LastLoadedProductRecipe : STRING[255];
		DeviceDataProvider : ARRAY[0..MAX_IDX_FILE_DEV]OF STRING[100];
		DeviceName : STRING[50];
		FileName : STRING[255];
		LastSelectedIndex : UINT;
		LastStatus : MpRecipeUIStatusEnum;
		TableConfig : STRING[120];
		CopyStep : RecipeCopyStep_enum;
		CategoryDropdown : STRING[80];
	END_STRUCT;
	RecipeHmiInterface_type : 	STRUCT 
		Commands : RecipeCommands_type;
		Status : RecipeStatus_type;
	END_STRUCT;
	RecipeCopyStep_enum : 
		(
		REC_COPY_WAIT := 0,
		REC_COPY_TO_USB,
		REC_COPY_FROM_USB,
		REC_COPY_BUSY
		);
	MachineSettings_type : 	STRUCT 
		AddMachineSettingsHere1 : USINT;
		AddMachineSettingsHere2 : DINT;
		AddMachineSettingsHere3 : BOOL;
		AddMachineSettingsHere4 : REAL;
		AddMachineSettingsHere5 : UINT;
	END_STRUCT;
	Parameters_type : 	STRUCT 
		AddParametersHere1 : BOOL;
		AddParametersHere2 : STRING[80];
		AddParametersHere3 : REAL;
		AddParametersHere4 : REAL;
		AddParametersHere5 : REAL;
	END_STRUCT;
END_TYPE
