(*Structure types*)

TYPE
	FileHmiInterfaceType : 	STRUCT  (*Structure to hold commands, parameters and status from the HMI*)
		Commands : FileHmiCommandsType; (*Structure to hold the commands from the HMI*)
		Parameters : FileHmiParametersType; (*Structure to hold parameters for the mapp View HMI*)
		Status : FileHmiStatusType; (*Structure to hold status information from the mapp View HMI*)
	END_STRUCT;
	FileHmiCommandsType : 	STRUCT  (*Structure to hold the commands from the HMI*)
		Delete : BOOL; (*Delete file*)
		FolderUp : BOOL; (*Move back/up a folder*)
		EnterFolder : BOOL; (*Move forward/down a folder*)
		CheckFolder : BOOL; (*Run the FIFO check to determine if old files should be deleted*)
		FileList : FileHmiCommandsFileListType; (*VC4 structure of commands*)
	END_STRUCT;
	FileHmiCommandsFileListType : 	STRUCT  (*Structure of VC4 commands*)
		PageDown : BOOL; (*VC4 button PageDown*)
		PageUp : BOOL; (*VC4 button PageUp*)
		StepDown : BOOL; (*VC4 button StepDown*)
		StepUp : BOOL; (*VC4 button StepUp*)
		Clicked : BOOL; (*VC4 button clicked*)
	END_STRUCT;
	FileHmiParametersType : 	STRUCT  (*Structure to hold parameters for the mapp View HMI*)
		OldSortOrder : MpFileManagerUISortOrderEnum; (*Previous sord order*)
		Fifo : FileHmiParaFifoType; (*Parameters for the FIFO feature (first-in-first-out)*)
	END_STRUCT;
	FileHmiStatusType : 	STRUCT  (*Structure to hold status information from the mapp View HMI*)
		FileNames : ARRAY[0..49]OF STRING[80]; (*List of file names*)
		TimeStamps : ARRAY[0..49]OF STRING[80]; (*List of time stamps for file names*)
		InfoFile : FileHmiStatusInfoFileType; (*VC4 info about selected file*)
		Type : ARRAY[0..49]OF DINT; (*List of file types*)
		Size : ARRAY[0..49]OF STRING[80]; (*List of file sizes*)
		DeviceDataProvider : ARRAY[0..MAX_IDX_FILE_DEV]OF STRING[100]; (*Data provider for the file device selector*)
		FifoSelect : ARRAY[0..MAX_IDX_FILE_DEV]OF DINT; (*Indicate FIFO selected file device*)
		DeviceName : STRING[50]; (*File device name*)
		FileName : STRING[255]; (*Fille name*)
		IsFolder : BOOL; (*Flag for whether the item is a folder (versus a file)*)
		BackButton : BOOL; (*Flag for whether the back button should be shown*)
		DeleteStep : FileDeleteStepEnum; (*Enumeration for automatic file deletion steps*)
		AutoDeleteSelected : USINT; (*Number of selected items*)
		FolderSize : REAL; (*Size of currently selected folder*)
		SelectedIndex : USINT; (*Selected index in the file list*)
		FifoConfigEnable : BOOL; (*Disable FIFO access or change confirmation when FIFO is active*)
		FIFOLayerStatus : USINT; (*VC4 FIFO layer status*)
		FIFOLayerObjects : FileHmiStatusFIFOLayerOptType; (*VC4 FIFO option visibility control*)
		DefaultFileSelected : BOOL; (*The default recipe is selected*)
	END_STRUCT;
	FileHmiStatusFIFOLayerOptType : 	STRUCT  (*VC4 FIFO option visibility control*)
		MaxNumberOfFilesVisiblity : USINT; (*VC4 max number of files option*)
		MaxFolderSizeVisiblity : USINT; (*VC4 folder size option*)
	END_STRUCT;
	FileHmiStatusInfoFileType : 	STRUCT  (*VC4 structure for  file type information details*)
		IsSelected : ARRAY[0..49]OF STRING[1]; (*VC4 file is selected*)
		Type : ARRAY[0..49]OF STRING[80]; (*VC4 file is of type*)
	END_STRUCT;
	FileHmiParaFifoType : 	STRUCT  (*Parameters for the FIFO feature (first-in-first-out)*)
		Enable : BOOL; (*FIFO enable*)
		DeviceName : STRING[50]; (*File device that the FIFO is active on*)
		FifoType : FileFifoTypeEnum; (*Defines the delete behavior of the FIFO*)
		ScanInterval : DINT := 60; (*[minutes]*)
		MaxFileAge : UINT := 365; (*[days] Files older than 1 year will be deleted*)
		MaxFolderSize : REAL := 1000; (*[kB] - Max size of files inside the active folder*)
		MaxNumberOfFiles : UINT := 20; (*Max number of files inside active folder*)
		SelectedDevice : UINT;
	END_STRUCT;
	FilePathCheckType : 	STRUCT  (*Setup for checking available folders / file devices for FIleManager*)
		Folder : ARRAY[0..9]OF STRING[20]; (*Folder name in user partition*)
		PrgName : ARRAY[0..9]OF STRING[12]; (*Program name for mapp framework components*)
		DeviceList : MpFileManagerUIDeviceListType; (*Device name*)
	END_STRUCT;
END_TYPE

(*Enumerations*)

TYPE
	FileDeleteStepEnum : 
		( (*Enumeration for file deletion steps*)
		FILE_DISABLED, (*Disabled*)
		FILE_DELETE_WAIT, (*Wait state*)
		FILE_SCAN_FOLDER_WAIT, (*Wait for check for old files command*)
		FILE_SELECT_DEVICE, (*Switch file device to the configured one *)
		FILE_REFRESH, (*Refreshing the data*)
		FILE_SORT_BY_DATE, (*Sort by date so the oldest files are at the end*)
		FILE_SORT_BY_DATE_WAIT, (*Wait step switching sorting mode*)
		FILE_GO_TO_END, (*Pages down until at the end of the file list*)
		FILE_GO_TO_END_1, (*Pages down until at the end of the file list*)
		FILE_CHECK_FOR_FILTER, (*Check which delete filter is active*)
		FILE_SELECT_OLDEST_FILES_0, (*Scan and select all file over the filter setting*)
		FILE_CALC_FOLDER_SIZE, (*Calculate the overall file size in the open folder*)
		FILE_CALC_FOLDER_SCROLL,
		FILE_SELECT_OLDEST_FILES_1, (*Scan and select all file over the filter setting*)
		FILE_DELETE_FILES, (*Set command to delete the selected oldest files*)
		FILE_CONFIRM_DELETE, (*Confirm the file delete*)
		FILE_CONFIRM_DELETE_WAIT, (*Wait for the automatic refresh after file deletion*)
		FILE_RESET_SORT_BY, (*Restore old sort order*)
		FILE_RESET_SORT_BY_WAIT (*Waiting for restore previous sort order*)
		);
	FileFifoTypeEnum : 
		( (*Defines the delete behavior of the FIFO*)
		FILE_FIFO_NUM_OF_FILES := 0, (*Delete according to total number of files*)
		FILE_FIFO_SIZE_OF_FOLDER (*Delete according to maximum folder size*)
		);
	FileTypeEnum : 
		( (*Defines the type of file in order to update the displayed icon*)
		FOLDER := 0, (*Folder*)
		FILE := 1, (*File*)
		FILE_SELECTED := 2 (*The selected file*)
		);
END_TYPE
