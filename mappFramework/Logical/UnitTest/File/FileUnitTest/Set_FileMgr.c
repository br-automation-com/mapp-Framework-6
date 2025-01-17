#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

#include "UnitTest.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define TIMEOUT_TEST_CASE									\
	if (cycleCount >= 1000)									\
	{														\
		char abortMessage[80];								\
		char substate[10];									\
		memset(abortMessage, 0, sizeof(abortMessage));		\
		memset(substate, 0, sizeof(substate));				\
		itoa(TestState, substate, 10);						\
		strcpy(abortMessage, "Timeout in State = ");		\
		strcat(abortMessage, substate);						\
		TEST_FAIL(abortMessage);							\
		TEST_DONE;											\
	}

_SETUP_SET(void)
{
	TestState = 0;
	FileNumber = 0;

	if (pMpFileManagerUIConnect == NULL)
	{
		TEST_ABORT_MSG("Failed to get address of MpFileManagerUIConnect");
	}
	
	HmiFile_UT.Parameters.Fifo.Enable = false;
	HmiFile_UT.Parameters.Fifo.ScanInterval = 60;
	strcpy(HmiFile_UT.Parameters.Fifo.DeviceName, "mappUserXFiles");

	switch (SetupState)
	{
		case 0:
			TEST_BUSY_CONDITION(HmiFile_UT.Status.DeleteStep != FILE_DISABLED);
			for (USINT i=0; i<sizeof(HmiFile_UT.Status.FifoSelect)/sizeof(HmiFile_UT.Status.FifoSelect[0]); i++)
			{
				TEST_BUSY_CONDITION(HmiFile_UT.Status.FifoSelect[i] != 0);
			}
			DirInfo_UT.enable = true;
			DirInfo_UT.pDevice = (UDINT)&HmiFile_UT.Parameters.Fifo.DeviceName;
			DirInfo_UT.pPath = (UDINT)&"";
			DirInfo(&DirInfo_UT);
			TEST_BUSY_CONDITION(DirInfo_UT.status == 65535);
			TEST_ABORT_CONDITION(DirInfo_UT.status != 0);
			NumberOfFiles = DirInfo_UT.filenum;
			CurrentFile = 0;
			SetupState = (NumberOfFiles == 0) ? 10 : 1;
			break;

		case 1:
			DirRead_UT.enable = true;
			DirRead_UT.pDevice = DirInfo_UT.pDevice;
			DirRead_UT.entry = 0;
			DirRead_UT.option = fiFILE;
			DirRead_UT.pData = (UDINT)&fileInfo;
			DirRead_UT.data_len = sizeof(fileInfo);
			DirRead(&DirRead_UT);
			TEST_BUSY_CONDITION(DirRead_UT.status == 65535);
			TEST_ABORT_CONDITION(DirRead_UT.status != 0);
			SetupState = 2;
			break;

		case 2:
			FileDelete_UT.enable = true;
			FileDelete_UT.pDevice = DirInfo_UT.pDevice;
			FileDelete_UT.pName = (UDINT)&fileInfo.Filename;
			FileDelete(&FileDelete_UT);
			TEST_BUSY_CONDITION(FileDelete_UT.status == 65535);
			TEST_ABORT_CONDITION(FileDelete_UT.status != 0);

			CurrentFile++;
			SetupState = (CurrentFile >= NumberOfFiles) ? 10 : 1;
			break;

		case 10:
			if (brsstrcmp((UDINT)&pMpFileManagerUIConnect->DeviceList.DeviceNames[pMpFileManagerUIConnect->DeviceList.SelectedIndex], (UDINT)&HmiFile_UT.Parameters.Fifo.DeviceName) == 0)
			{
				SetupState = 100;
				TEST_BUSY;
			}
			for (USINT i=0; i<sizeof(pMpFileManagerUIConnect->DeviceList.DeviceNames)/sizeof(pMpFileManagerUIConnect->DeviceList.DeviceNames[0]); i++)
			{
				if (brsstrcmp((UDINT)&pMpFileManagerUIConnect->DeviceList.DeviceNames[i], (UDINT)&HmiFile_UT.Parameters.Fifo.DeviceName) == 0)
				{
					pMpFileManagerUIConnect->DeviceList.SelectedIndex = i;
					break;
				}
			}
			SetupState = 11;
			break;
		
		case 11:
			TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status == mpFILE_UI_STATUS_IDLE);
			SetupState = 12;
			break;
		
		case 12:
			TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
			SetupState = 100;
			break;
			
		case 20:
			TEST_BUSY_CONDITION(MpFileManagerUIConnect_FIFO.Status == mpFILE_UI_STATUS_IDLE);
			MpFileManagerUIConnect_FIFO.File.Refresh = true;
			TEST_BUSY_CONDITION(MpFileManagerUIConnect_FIFO.Status == mpFILE_UI_STATUS_IDLE);
			MpFileManagerUIConnect_FIFO.File.Refresh = false;
			SetupState = 21;
			break;

		case 21:
			TEST_BUSY_CONDITION(MpFileManagerUIConnect_FIFO.Status != mpFILE_UI_STATUS_IDLE);
			SetupState = 100;
			break;

		case 100:
			SetupState = 0;
			TEST_DONE;
	}
	TEST_BUSY;
}

_TEARDOWN_SET(void)
{
	/* TODO:  add code running after test set here */
	TEST_DONE;
}

bool FileIdleOrDisabled(void) {
	return ((HmiFile_UT.Status.DeleteStep == FILE_DELETE_WAIT) || (HmiFile_UT.Status.DeleteStep == FILE_DISABLED));
}

_SETUP_TEST(void) {
	TestState = 0;
	ArrangeSubState = 0;
	ActSubState = 0;
	AssertSubState = 0;
	FileNumber = 0;
	cycleCount = 0;
	NameMatch = 0;
	InNewLocation = 0;
	InOldLocation = 0;
	MultiSelectDirCopy = 0;
	MultiSelectFileCopy = 0;
	HmiFile.Status.SelectedIndex = 0;
	pMpFileManagerUIConnect->File.Copy = 0;
	pMpFileManagerUIConnect->File.CreateFolder = 0;
	pMpFileManagerUIConnect->File.Cut = 0;
	pMpFileManagerUIConnect->File.Delete = 0;
	pMpFileManagerUIConnect->File.EnterFolder = 0;
	pMpFileManagerUIConnect->File.FolderUp = 0;
	pMpFileManagerUIConnect->File.MultiSelect = 0;
	pMpFileManagerUIConnect->File.Paste = 0;
	pMpFileManagerUIConnect->File.Refresh = 0;
	pMpFileManagerUIConnect->File.Rename = 0;
	
	HmiFile_UT.Parameters.Fifo.Enable = false;
	HmiFile_UT.Parameters.Fifo.ScanInterval = 60;
	strcpy(HmiFile_UT.Parameters.Fifo.DeviceName, "mappUserXFiles");

	switch (SetupState)
	{
		case 0:
			TEST_BUSY_CONDITION(HmiFile_UT.Status.DeleteStep != FILE_DISABLED);
			for (USINT i=0; i<sizeof(HmiFile_UT.Status.FifoSelect)/sizeof(HmiFile_UT.Status.FifoSelect[0]); i++)
			{
				TEST_BUSY_CONDITION(HmiFile_UT.Status.FifoSelect[i] != 0);
			}

			DirInfo_UT.enable = true;
			DirInfo_UT.pDevice = (UDINT)&HmiFile_UT.Parameters.Fifo.DeviceName;
			DirInfo_UT.pPath = (UDINT)&"";
			DirInfo(&DirInfo_UT);
			TEST_BUSY_CONDITION(DirInfo_UT.status == 65535);
			TEST_ABORT_CONDITION(DirInfo_UT.status != 0);
			NumberOfFiles = DirInfo_UT.filenum;
			NumberOfDirs = DirInfo_UT.dirnum;
			CurrentFile = 0;
			CurrentDir = 2;
			SetupState = (NumberOfFiles == 0) ? 3 : 1;
			break;

		case 1:
			DirRead_UT.enable = true;
			DirRead_UT.pDevice = DirInfo_UT.pDevice;
			DirRead_UT.entry = 0;
			DirRead_UT.option = fiFILE;
			DirRead_UT.pData = (UDINT)&fileInfo;
			DirRead_UT.data_len = sizeof(fileInfo);
			DirRead(&DirRead_UT);
			TEST_BUSY_CONDITION(DirRead_UT.status == 65535);
			TEST_ABORT_CONDITION(DirRead_UT.status != 0);
			SetupState = 2;
			break;

		case 2:
			FileDelete_UT.enable = true;
			FileDelete_UT.pDevice = DirInfo_UT.pDevice;
			FileDelete_UT.pName = (UDINT)&fileInfo.Filename;
			FileDelete(&FileDelete_UT);
			TEST_BUSY_CONDITION(FileDelete_UT.status == 65535);
			TEST_ABORT_CONDITION(FileDelete_UT.status != 0);
			
			CurrentFile++;
			SetupState = (CurrentFile >= NumberOfFiles) ? 3 : 1;
			break;
		
		case 3:
			DirRead_UT.enable = true;
			DirRead_UT.pDevice = DirInfo_UT.pDevice;
			DirRead_UT.entry = 2;
			DirRead_UT.option = fiDIRECTORY;
			DirRead_UT.pData = (UDINT)&fileInfo;
			DirRead_UT.data_len = sizeof(fileInfo);
			DirRead(&DirRead_UT);
			TEST_BUSY_CONDITION(DirRead_UT.status == 65535);
			if (DirRead_UT.status == fiERR_NO_MORE_ENTRIES)
			{
				SetupState = 10;
				TEST_BUSY;
			}
			TEST_ABORT_CONDITION(DirRead_UT.status != 0);
			SetupState = 4;
			break;
		
		case 4:
			DirDeleteEx_UT.enable = true;
			DirDeleteEx_UT.pDevice = DirInfo_UT.pDevice;
			DirDeleteEx_UT.pName = (UDINT)&fileInfo.Filename;
			DirDeleteEx(&DirDeleteEx_UT);
			TEST_BUSY_CONDITION(DirDeleteEx_UT.status == 65535);
			TEST_ABORT_CONDITION(DirDeleteEx_UT.status != 0);
		
			CurrentDir++;
			SetupState = (CurrentDir >= NumberOfDirs) ? 10 : 3;
			break;
		
		case 10:
			if (pMpFileManagerUIConnect->Status != 0)
			{
				pMpFileManagerUIConnect->DeviceList.SelectedIndex = 0;
				TEST_BUSY;
			}
			if (brsstrcmp((UDINT)&pMpFileManagerUIConnect->DeviceList.DeviceNames[pMpFileManagerUIConnect->DeviceList.SelectedIndex], (UDINT)&HmiFile_UT.Parameters.Fifo.DeviceName) == 0)
			{
				SetupState = 100;
				TEST_BUSY;
			}
			for (USINT i=0; i<sizeof(pMpFileManagerUIConnect->DeviceList.DeviceNames)/sizeof(pMpFileManagerUIConnect->DeviceList.DeviceNames[0]); i++)
			{
				if (brsstrcmp((UDINT)&pMpFileManagerUIConnect->DeviceList.DeviceNames[i], (UDINT)&HmiFile_UT.Parameters.Fifo.DeviceName) == 0)
				{
					pMpFileManagerUIConnect->DeviceList.SelectedIndex = i;
					break;
				}
			}
			SetupState = 11;
			break;
		
		case 11:
			TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status == mpFILE_UI_STATUS_IDLE);
			SetupState = 12;
			break;
		
		case 12:
			TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
			SetupState = 100;
			break;
			
		case 20:
			TEST_BUSY_CONDITION(MpFileManagerUIConnect_FIFO.Status == mpFILE_UI_STATUS_IDLE);
			MpFileManagerUIConnect_FIFO.File.Refresh = true;
			TEST_BUSY_CONDITION(MpFileManagerUIConnect_FIFO.Status == mpFILE_UI_STATUS_IDLE);
			MpFileManagerUIConnect_FIFO.File.Refresh = false;
			SetupState = 21;
			break;

		case 21:
			TEST_BUSY_CONDITION(MpFileManagerUIConnect_FIFO.Status != mpFILE_UI_STATUS_IDLE);
			SetupState = 100;
			break;

		case 100:
			SetupState = 0;
			TEST_DONE;
	}
	TEST_BUSY;
}

_TEARDOWN_TEST(void)
{
	HmiFile_UT.Parameters.Fifo.Enable = false;
	HmiFile_UT.Parameters.Fifo.ScanInterval = 60;
	
	TestState = 0;
	ArrangeSubState = 0;
	ActSubState = 0;
	AssertSubState = 0;
	SetupState = 0;
	cycleCount = 0;
	NameMatch = 0;
	InNewLocation = 0;
	InOldLocation = 0;
	MultiSelectDirCopy = 0;
	MultiSelectFileCopy = 0;
	HmiFile.Status.SelectedIndex = 0;
	pMpFileManagerUIConnect->File.Copy = 0;
	pMpFileManagerUIConnect->File.CreateFolder = 0;
	pMpFileManagerUIConnect->File.Cut = 0;
	pMpFileManagerUIConnect->File.Delete = 0;
	pMpFileManagerUIConnect->File.EnterFolder = 0;
	pMpFileManagerUIConnect->File.FolderUp = 0;
	pMpFileManagerUIConnect->File.MultiSelect = 0;
	pMpFileManagerUIConnect->File.Paste = 0;
	pMpFileManagerUIConnect->File.Refresh = 0;
	pMpFileManagerUIConnect->File.Rename = 0;
	brsmemcpy((UDINT)&pMpFileManagerUIConnect->File.Filter, (UDINT)&"", sizeof(pMpFileManagerUIConnect->File.Filter));
	
	HmiFile.Commands.Delete = 0;
	HmiFile.Commands.EnterFolder = 0;
	HmiFile.Commands.FolderUp = 0;
	HmiFile.Commands.MultiSelect = 0;
	HmiFile.Status.SelectedIndex = 0;
	
	FileCreate_0.enable = 0;
	FileClose_0.enable = 0;
	FileCreate(&FileCreate_0);
	FileClose(&FileClose_0);
	
	TEST_DONE;
}

_CYCLIC_SET(void)
{
	cycleCount++;
}

_TEST Create_Directory(void)
{
	TIMEOUT_TEST_CASE;
	
	switch (TestState)
	{
		case 0:
			// Select UserX file device and input directory name
			switch (ArrangeSubState)
			{
				case 0:
					brsmemcpy((UDINT)&pMpFileManagerUIConnect->File.NewName, (UDINT)&DirName, sizeof(pMpFileManagerUIConnect->File.NewName));
					ArrangeSubState = 1;
					break;
			
				case 1:
					pMpFileManagerUIConnect->File.Refresh = 1;
					ArrangeSubState = 2;
					break;
			
				case 2:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != 0);
					pMpFileManagerUIConnect->File.Refresh = 0;
					ArrangeSubState = 3;
					break;
				
				case 3:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != 0);
					for(int i = 0; i < sizeof(pMpFileManagerUIConnect->File.List.Items)/sizeof(pMpFileManagerUIConnect->File.List.Items[0]); i++)
					{
						if(brsstrcmp((UDINT)&pMpFileManagerUIConnect->File.List.Items[i].Name, (UDINT)&DirName) == 0)
						{
							TEST_FAIL("Directory with chosen name already exists");
							TEST_DONE;
						}
					}
					TestState = 1;
					break;
			}
			break;
		
		case 1:
			// Create directory
			switch (ActSubState)
			{
				case 0:
					pMpFileManagerUIConnect->File.CreateFolder = 1;
					ActSubState = 1;
					break;
					
				case 1:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_CREATE);
					pMpFileManagerUIConnect->File.CreateFolder = 0;
					ActSubState = 2;
				
				case 2:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					pMpFileManagerUIConnect->File.Refresh = 1;
					ActSubState = 3;
					break;
				
				case 3:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_REFRESH);
					pMpFileManagerUIConnect->File.Refresh = 0;
					ActSubState = 4;
					break;
				
				case 4:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					for(int i = 0; i < sizeof(pMpFileManagerUIConnect->File.List.Items)/sizeof(pMpFileManagerUIConnect->File.List.Items[0]); i++)
					{
						if(brsstrcmp((UDINT)&pMpFileManagerUIConnect->File.List.Items[i].Name, (UDINT)&DirName) == 0)
						{
							NameMatch = 1;
						}
					}
					TestState = 2;
					break;
			}
			break;
		
		case 2:
			// Check save location for directory
			TEST_ASSERT(NameMatch);
			TEST_DONE;
			break;
	}
	TEST_BUSY;
}

_TEST Add_File(void)
{
	TIMEOUT_TEST_CASE;
	
	FileCreate(&FileCreate_0);
	FileClose(&FileClose_0);
	
	switch (TestState)
	{
		case 0:
			// Select UserX file device and input file name
			switch (ArrangeSubState)
			{
				case 0:
					FileCreate_0.pDevice = (UDINT)&"mappUserXFiles";
					FileCreate_0.pFile = (UDINT)&CreateFileName;
					ArrangeSubState = 1;
					break;
			
				case 1:
					pMpFileManagerUIConnect->File.Refresh = 1;
					ArrangeSubState = 2;
					break;
			
				case 2:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					pMpFileManagerUIConnect->File.Refresh = 0;
					ArrangeSubState = 3;
					break;
				
				case 3: // Check to make sure there isn't already a file by the specified name in the directory
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != 0);
					for(int i = 0; i < sizeof(pMpFileManagerUIConnect->File.List.Items)/sizeof(pMpFileManagerUIConnect->File.List.Items[0]); i++)
					{
						if(brsstrcmp((UDINT)&pMpFileManagerUIConnect->File.List.Items[i].Name, (UDINT)&CreateFileName) == 0)
						{
							TEST_FAIL("File with chosen name already exists");
							TEST_DONE;
						}
					}
					TestState = 1;
					break;
			}
			break;
		
		case 1:
			// Create file
			switch (ActSubState)
			{
				case 0:
					FileCreate_0.enable = 1;
					ActSubState = 1;
					break;
					
				case 1:
					TEST_BUSY_CONDITION(FileCreate_0.status != 0);
					FileCreate_0.enable = 0;
					if ((FileCreate_0.status != 0) && (FileCreate_0.status != 65535))
					{
						TEST_FAIL("FileCreate function block has an error");
						TEST_ASSERT_EQUAL_INT(0, FileCreate_0.status);
						TEST_DONE;
					}
					FileClose_0.ident = FileCreate_0.ident;
					FileClose_0.enable = 1;
					ActSubState = 2;
					break;
				
				case 2:
					TEST_BUSY_CONDITION(FileClose_0.status != 0);
					FileClose_0.enable = 0;
					if ((FileClose_0.status != 0) && (FileClose_0.status != 65535))
					{
						TEST_FAIL("FileClose function block has an error");
						TEST_ASSERT_EQUAL_INT(0, FileClose_0.status);
						TEST_DONE;
					}
					pMpFileManagerUIConnect->File.Refresh = 1;
					ActSubState = 3;
					break;
			
				case 3:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_REFRESH);
					pMpFileManagerUIConnect->File.Refresh = 0;
					ActSubState = 4;
					break;
			
				case 4:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					ActSubState = 5;
					break;
				
				case 5:
					for(int i = 0; i < sizeof(pMpFileManagerUIConnect->File.List.Items)/sizeof(pMpFileManagerUIConnect->File.List.Items[0]); i++)
					{
						if(brsstrcmp((UDINT)&pMpFileManagerUIConnect->File.List.Items[i].Name, (UDINT)&CreateFileName) == 0)
						{
							NameMatch = 1;
						}
					}
					TestState = 2;
					break;
			}
			break;
		
		case 2:
			// Check save location for file
			TEST_ASSERT(NameMatch);
			TEST_DONE;
			break;
	}
	TEST_BUSY;
}

_TEST Copy_File(void)
{
	TIMEOUT_TEST_CASE;
	
	FileCreate(&FileCreate_0);
	FileClose(&FileClose_0);
	
	switch (TestState)
	{
		case 0:
			// Select UserX file device and input name of file to be copied
			switch (ArrangeSubState)
			{
				case 0:
					FileCreate_0.pDevice = (UDINT)&"mappUserXFiles";
					FileCreate_0.pFile = (UDINT)&CreateFileName;
					FileCreate_0.enable = 1;
					ArrangeSubState = 1;
					break;
					
				case 1:
					TEST_BUSY_CONDITION(FileCreate_0.status != 0);
					FileCreate_0.enable = 0;
					if ((FileCreate_0.status != 0) && (FileCreate_0.status != 65535))
					{
						TEST_FAIL("FileCreate function block has an error");
						TEST_ASSERT_EQUAL_INT(0, FileCreate_0.status);
						TEST_DONE;
					}
					FileClose_0.ident = FileCreate_0.ident;
					FileClose_0.enable = 1;
					ArrangeSubState = 2;
					break;
				
				case 2:
					TEST_BUSY_CONDITION(FileClose_0.status != 0);
					FileClose_0.enable = 0;
					if ((FileClose_0.status != 0) && (FileClose_0.status != 65535))
					{
						TEST_FAIL("FileClose function block has an error");
						TEST_ASSERT_EQUAL_INT(0, FileClose_0.status);
						TEST_DONE;
					}
					ArrangeSubState = 3;
					break;
			
				case 3:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					pMpFileManagerUIConnect->File.Refresh = 1;
					ArrangeSubState = 4;
					break;
				
				case 4:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_REFRESH);
					pMpFileManagerUIConnect->File.Refresh = 0;
					ArrangeSubState = 10;
					break;
			
				case 10:
					for(int i = 0; i < sizeof(pMpFileManagerUIConnect->File.List.Items)/sizeof(pMpFileManagerUIConnect->File.List.Items[0]); i++)
					{
						if(brsstrcmp((UDINT)&pMpFileManagerUIConnect->File.List.Items[i].Name, (UDINT)&CreateFileName) == 0)
							HmiFile.Status.SelectedIndex = i;
					}
					TestState = 1;
					break;
			}
			break;
		
		case 1:
			// Copy/paste file
			switch (ActSubState)
			{
				case 0:
					pMpFileManagerUIConnect->File.Copy = 1;
					ActSubState = 1;
					break;
				
				case 1:
					pMpFileManagerUIConnect->File.Copy = 0;
					pMpFileManagerUIConnect->File.Paste = 1;
					ActSubState = 2;
					break;
			
				case 2:
					pMpFileManagerUIConnect->File.Paste = 0;
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_PASTE);
					ActSubState = 3;
					break;
			
				case 3:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					pMpFileManagerUIConnect->File.Refresh = 1;
					ActSubState = 4;
					break;
			
				case 4:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_REFRESH);
					pMpFileManagerUIConnect->File.Refresh = 0;
					ActSubState = 5;
					break;
				
				case 5:
					// Check file list for copied file
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					for(int i = 0; i < sizeof(pMpFileManagerUIConnect->File.List.Items)/sizeof(pMpFileManagerUIConnect->File.List.Items[0]); i++)
					{
						if(brsstrcmp((UDINT)&pMpFileManagerUIConnect->File.List.Items[i].Name, (UDINT)&CopiedFileName) == 0)
						{
							NameMatch = 1;
						}
					}
					TestState = 2;
					break;
			}
			break;
		
		case 2:
			// Check if copied file was found
			TEST_ASSERT(NameMatch);
			TEST_DONE;
			break;
	}
	TEST_BUSY;
}

_TEST Copy_Directory(void)
{
	TIMEOUT_TEST_CASE;
	
	switch (TestState)
	{
		case 0:
			// Select UserX file device and input name of directory to be copied
			switch (ArrangeSubState)
			{
				case 0:
					brsmemcpy((UDINT)&pMpFileManagerUIConnect->File.NewName, (UDINT)&DirName, sizeof(pMpFileManagerUIConnect->File.NewName));
					pMpFileManagerUIConnect->File.CreateFolder = 1;
					ArrangeSubState = 1;
					break;
					
				case 1:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_CREATE);
					pMpFileManagerUIConnect->File.CreateFolder = 0;
					ArrangeSubState = 2;
				
				case 2:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					pMpFileManagerUIConnect->File.Refresh = 1;
					ArrangeSubState = 3;
					break;
				
				case 3:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_REFRESH);
					pMpFileManagerUIConnect->File.Refresh = 0;
					ArrangeSubState = 10;
					break;
				
				case 10:
					for(int i = 0; i < sizeof(pMpFileManagerUIConnect->File.List.Items)/sizeof(pMpFileManagerUIConnect->File.List.Items[0]); i++)
					{
						if(brsstrcmp((UDINT)&pMpFileManagerUIConnect->File.List.Items[i].Name, (UDINT)&DirName) == 0)
							HmiFile.Status.SelectedIndex = i;
					}
					TestState = 1;
					break;
			}
			break;
		
		case 1:
			// Copy/paste directory
			switch (ActSubState)
			{
				case 0:
					pMpFileManagerUIConnect->File.Copy = 1;
					ActSubState = 1;
					break;
				
				case 1:
					pMpFileManagerUIConnect->File.Copy = 0;
					pMpFileManagerUIConnect->File.Paste = 1;
					ActSubState = 2;
					break;
			
				case 2:
					pMpFileManagerUIConnect->File.Paste = 0;
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_PASTE);
					ActSubState = 3;
					break;
			
				case 3:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					pMpFileManagerUIConnect->File.Refresh = 1;
					ActSubState = 4;
					break;
			
				case 4:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_REFRESH);
					pMpFileManagerUIConnect->File.Refresh = 0;
					ActSubState = 5;
					break;
				
				case 5:
					// Check file list for copied directory
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					for(int i = 0; i < sizeof(pMpFileManagerUIConnect->File.List.Items)/sizeof(pMpFileManagerUIConnect->File.List.Items[0]); i++)
					{
						if(brsstrcmp((UDINT)&pMpFileManagerUIConnect->File.List.Items[i].Name, (UDINT)&CopiedDirName) == 0)
						{
							NameMatch = 1;
						}
					}
					TestState = 2;
					break;
			}
			break;
		
		case 2:
			// Check if copied directory was found
			TEST_ASSERT(NameMatch);
			TEST_DONE;
			break;
	}
	TEST_BUSY;
}

_TEST Rename_File(void)
{
	TIMEOUT_TEST_CASE;
	
	FileCreate(&FileCreate_0);
	FileClose(&FileClose_0);
	
	switch (TestState)
	{
		case 0:
			// Select UserX file device and input name of file to be renamed and new name
			switch (ArrangeSubState)
			{
				case 0:
					FileCreate_0.pDevice = (UDINT)&"mappUserXFiles";
					FileCreate_0.pFile = (UDINT)&CopiedFileName;
					FileCreate_0.enable = 1;
					ArrangeSubState = 1;
					break;
					
				case 1:
					TEST_BUSY_CONDITION(FileCreate_0.status != 0);
					FileCreate_0.enable = 0;
					if ((FileCreate_0.status != 0) && (FileCreate_0.status != 65535))
					{
						TEST_FAIL("FileCreate function block has an error");
						TEST_ASSERT_EQUAL_INT(0, FileCreate_0.status);
						TEST_DONE;
					}
					FileClose_0.ident = FileCreate_0.ident;
					FileClose_0.enable = 1;
					ArrangeSubState = 2;
					break;
				
				case 2:
					TEST_BUSY_CONDITION(FileClose_0.status != 0);
					FileClose_0.enable = 0;
					if ((FileClose_0.status != 0) && (FileClose_0.status != 65535))
					{
						TEST_FAIL("FileClose function block has an error");
						TEST_ASSERT_EQUAL_INT(0, FileClose_0.status);
						TEST_DONE;
					}
					pMpFileManagerUIConnect->File.Refresh = 1;
					ArrangeSubState = 10;
					break;
				
				case 10:			
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					pMpFileManagerUIConnect->File.Refresh = 1;
					ArrangeSubState = 11;
					break;
			
				case 11:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_REFRESH);
					pMpFileManagerUIConnect->File.Refresh = 0;
					ArrangeSubState = 12;
					break;

				case 12:
					brsmemcpy((UDINT)&pMpFileManagerUIConnect->File.NewName, (UDINT)&NewFileName, sizeof(pMpFileManagerUIConnect->File.NewName));
					ArrangeSubState = 13;
					break;
				
				case 13:
					for(int i = 0; i < sizeof(pMpFileManagerUIConnect->File.List.Items)/sizeof(pMpFileManagerUIConnect->File.List.Items[0]); i++)
					{
						if(brsstrcmp((UDINT)&pMpFileManagerUIConnect->File.List.Items[i].Name, (UDINT)&CopiedFileName) == 0)
							HmiFile.Status.SelectedIndex = i;
					}
					TestState = 1;
					break;
			}
			break;
		
		case 1:
			// Rename file
			switch (ActSubState)
			{
				case 0:
					pMpFileManagerUIConnect->File.Rename = 1;
					ActSubState = 1;
					break;
			
				case 1:
					pMpFileManagerUIConnect->File.Rename = 0;
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					pMpFileManagerUIConnect->File.Refresh = 1;
					ActSubState = 2;
					break;
			
				case 2:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_REFRESH);
					pMpFileManagerUIConnect->File.Refresh = 0;
					ActSubState = 3;
					break;
				
				case 3:
					// Check file list for renamed file
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					for(int i = 0; i < sizeof(pMpFileManagerUIConnect->File.List.Items)/sizeof(pMpFileManagerUIConnect->File.List.Items[0]); i++)
					{
						if(brsstrcmp((UDINT)&pMpFileManagerUIConnect->File.List.Items[i].Name, (UDINT)&NewFileName) == 0)
						{
							NameMatch = 1;
						}
					}
					TestState = 2;
					break;
			}
			break;
		
		case 2:
			// Check if renamed file was found
			TEST_ASSERT(NameMatch);
			TEST_DONE;
			break;
	}
	TEST_BUSY;
}

_TEST Rename_Directory(void)
{
	TIMEOUT_TEST_CASE;
	
	switch (TestState)
	{
		case 0:
			// Select UserX file device and input name of directory to be renamed and new name
			switch (ArrangeSubState)
			{
				case 0:
					brsmemcpy((UDINT)&pMpFileManagerUIConnect->File.NewName, (UDINT)&CopiedDirName, sizeof(pMpFileManagerUIConnect->File.NewName));
					pMpFileManagerUIConnect->File.CreateFolder = 1;
					ArrangeSubState = 1;
					break;
					
				case 1:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_CREATE);
					pMpFileManagerUIConnect->File.CreateFolder = 0;
					ArrangeSubState = 2;
				
				case 2:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					pMpFileManagerUIConnect->File.Refresh = 1;
					ArrangeSubState = 3;
					break;
				
				case 3:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_REFRESH);
					pMpFileManagerUIConnect->File.Refresh = 0;
					ArrangeSubState = 10;
					break;
			
				case 10:
					brsmemcpy((UDINT)&pMpFileManagerUIConnect->File.NewName, (UDINT)&NewDirName, sizeof(pMpFileManagerUIConnect->File.NewName));
					ArrangeSubState = 11;
					break;
				
				case 11:
					for(int i = 0; i < sizeof(pMpFileManagerUIConnect->File.List.Items)/sizeof(pMpFileManagerUIConnect->File.List.Items[0]); i++)
					{
						if(brsstrcmp((UDINT)&pMpFileManagerUIConnect->File.List.Items[i].Name, (UDINT)&CopiedDirName) == 0)
							HmiFile.Status.SelectedIndex = i;
					}
					TestState = 1;
					break;
			}
			break;
		
		case 1:
			// Rename directory
			switch (ActSubState)
			{
				case 0:
					pMpFileManagerUIConnect->File.Rename = 1;
					ActSubState = 1;
					break;
				
				case 1:
					pMpFileManagerUIConnect->File.Rename = 0;
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					pMpFileManagerUIConnect->File.Refresh = 1;
					ActSubState = 2;
					break;
			
				case 2:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_REFRESH);
					pMpFileManagerUIConnect->File.Refresh = 0;
					ActSubState = 3;
					break;
				
				case 3:
					// Check file list for renamed directory
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					for(int i = 0; i < sizeof(pMpFileManagerUIConnect->File.List.Items)/sizeof(pMpFileManagerUIConnect->File.List.Items[0]); i++)
					{
						if(brsstrcmp((UDINT)&pMpFileManagerUIConnect->File.List.Items[i].Name, (UDINT)&NewDirName) == 0)
						{
							NameMatch = 1;
						}
					}
					TestState = 2;
					break;
			}
			break;
		
		case 2:
			// Check if renamed directory was found
			TEST_INFO("File list items are");
			for(int i = 0; i < sizeof(pMpFileManagerUIConnect->File.List.Items)/sizeof(pMpFileManagerUIConnect->File.List.Items[0]); i++)
			{
				TEST_INFO(&pMpFileManagerUIConnect->File.List.Items[i].Name);
			}
			TEST_ASSERT(NameMatch);
			TEST_DONE;
			break;
	}
	TEST_BUSY;
}

_TEST Cut_Paste_File(void)
{
	TIMEOUT_TEST_CASE;
	
	FileCreate(&FileCreate_0);
	FileClose(&FileClose_0);
	switch (TestState)
	{
		case 0:
			// Select UserX file device and input name of file to be cut
			switch (ArrangeSubState)
			{
				case 0:
					FileCreate_0.pDevice = (UDINT)&"mappUserXFiles";
					FileCreate_0.pFile = (UDINT)&NewFileName;
					FileCreate_0.enable = 1;
					ArrangeSubState = 1;
					break;
					
				case 1:
					TEST_BUSY_CONDITION(FileCreate_0.status != 0);
					FileCreate_0.enable = 0;
					if ((FileCreate_0.status != 0) && (FileCreate_0.status != 65535))
					{
						TEST_FAIL("FileCreate function block has an error");
						TEST_ASSERT_EQUAL_INT(0, FileCreate_0.status);
						TEST_DONE;
					}
					FileClose_0.ident = FileCreate_0.ident;
					FileClose_0.enable = 1;
					ArrangeSubState = 2;
					break;
				
				case 2:
					TEST_BUSY_CONDITION(FileClose_0.status != 0);
					FileClose_0.enable = 0;
					if ((FileClose_0.status != 0) && (FileClose_0.status != 65535))
					{
						TEST_FAIL("FileClose function block has an error");
						TEST_ASSERT_EQUAL_INT(0, FileClose_0.status);
						TEST_DONE;
					}
					ArrangeSubState = 10;
					break;
			
				case 10:
					brsmemcpy((UDINT)&pMpFileManagerUIConnect->File.NewName, (UDINT)&DirName, sizeof(pMpFileManagerUIConnect->File.NewName));
					pMpFileManagerUIConnect->File.CreateFolder = 1;
					ArrangeSubState = 11;
					break;
					
				case 11:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_CREATE);
					pMpFileManagerUIConnect->File.CreateFolder = 0;
					ArrangeSubState = 12;
					break;
				
				case 12:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					pMpFileManagerUIConnect->File.Refresh = 1;
					ArrangeSubState = 13;
					break;
				
				case 13:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_REFRESH);
					pMpFileManagerUIConnect->File.Refresh = 0;
					ArrangeSubState = 20;
					break;
				
				case 20:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					for(int i = 0; i < sizeof(pMpFileManagerUIConnect->File.List.Items)/sizeof(pMpFileManagerUIConnect->File.List.Items[0]); i++)
					{
						if(brsstrcmp((UDINT)&pMpFileManagerUIConnect->File.List.Items[i].Name, (UDINT)&NewFileName) == 0)
							HmiFile.Status.SelectedIndex = i;
					}
					TestState = 1;
					break;
			}
			break;
		
		case 1:
			// Cut/paste file
			switch (ActSubState)
			{
				case 0:
					pMpFileManagerUIConnect->File.Cut = 1;
					ActSubState = 1;
					break;
				
				case 1:
					pMpFileManagerUIConnect->File.Cut = 0;
					for(int i = 0; i < sizeof(pMpFileManagerUIConnect->File.List.Items)/sizeof(pMpFileManagerUIConnect->File.List.Items[0]); i++)
					{
						if(brsstrcmp((UDINT)&pMpFileManagerUIConnect->File.List.Items[i].Name, (UDINT)&DirName) == 0)
							HmiFile.Status.SelectedIndex = i;
					}
					ActSubState = 2;
					break;
			
				case 2:
					HmiFile.Commands.EnterFolder = 1;
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_CHANGE_DIR);
					HmiFile.Commands.EnterFolder = 0;
					ActSubState = 3;
					break;
				
				case 3:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					pMpFileManagerUIConnect->File.Paste = 1;
					ActSubState = 4;
					break;
			
				case 4:
					pMpFileManagerUIConnect->File.Paste = 0;
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_PASTE);
					ActSubState = 5;
					break;
			
				case 5:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					pMpFileManagerUIConnect->File.Refresh = 1;
					ActSubState = 6;
					break;
			
				case 6:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_REFRESH);
					pMpFileManagerUIConnect->File.Refresh = 0;
					ActSubState = 7;
					break;
			
				case 7:
					// Check paste location for cut file
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					for(int i = 0; i < sizeof(pMpFileManagerUIConnect->File.List.Items)/sizeof(pMpFileManagerUIConnect->File.List.Items[0]); i++)
					{
						if(brsstrcmp((UDINT)&pMpFileManagerUIConnect->File.List.Items[i].Name, (UDINT)&NewFileName) == 0)
						{
							InNewLocation = 1;
						}
					}
					HmiFile.Commands.FolderUp = 1;
					ActSubState = 8;
					break;
				
				case 8:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_CHANGE_DIR);
					HmiFile.Commands.FolderUp = 0;
					ActSubState = 9;
					break;
				
				case 9:
					// Check old location for cut file
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					for(int i = 0; i < sizeof(pMpFileManagerUIConnect->File.List.Items)/sizeof(pMpFileManagerUIConnect->File.List.Items[0]); i++)
					{
						if(brsstrcmp((UDINT)&pMpFileManagerUIConnect->File.List.Items[i].Name, (UDINT)&NewFileName) == 0)
						{
							InOldLocation = 1;
						}
					}
					TestState = 2;
					break;
			}
			break;
		
		case 2:
			// Check new and old locations for file
			TEST_ASSERT(InNewLocation);
			TEST_ASSERT(!InOldLocation);
			TEST_DONE;
			break;
	}
	TEST_BUSY;
}

_TEST Cut_Paste_Directory(void)
{
	TIMEOUT_TEST_CASE;
	
	switch (TestState)
	{
		case 0:
			// Select UserX file device and input name of directory to be cut
			switch (ArrangeSubState)
			{
				case 0:
					brsmemcpy((UDINT)&pMpFileManagerUIConnect->File.NewName, (UDINT)&DirName, sizeof(pMpFileManagerUIConnect->File.NewName));
					pMpFileManagerUIConnect->File.CreateFolder = 1;
					ArrangeSubState = 1;
					break;
					
				case 1:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_CREATE);
					pMpFileManagerUIConnect->File.CreateFolder = 0;
					ArrangeSubState = 2;
				
				case 2:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					pMpFileManagerUIConnect->File.Refresh = 1;
					ArrangeSubState = 3;
					break;
				
				case 3:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_REFRESH);
					pMpFileManagerUIConnect->File.Refresh = 0;
					ArrangeSubState = 10;
					break;
				
				case 10:
					brsmemcpy((UDINT)&pMpFileManagerUIConnect->File.NewName, (UDINT)&NewDirName, sizeof(pMpFileManagerUIConnect->File.NewName));
					pMpFileManagerUIConnect->File.CreateFolder = 11;
					ArrangeSubState = 11;
					break;
							
				case 11:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_CREATE);
					pMpFileManagerUIConnect->File.CreateFolder = 0;
					ArrangeSubState = 12;
						
				case 12:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					pMpFileManagerUIConnect->File.Refresh = 1;
					ArrangeSubState = 13;
					break;
						
				case 13:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_REFRESH);
					pMpFileManagerUIConnect->File.Refresh = 0;
					ArrangeSubState = 14;
					break;
				
				case 14:
					for(int i = 0; i < sizeof(pMpFileManagerUIConnect->File.List.Items)/sizeof(pMpFileManagerUIConnect->File.List.Items[0]); i++)
					{
						if(brsstrcmp((UDINT)&pMpFileManagerUIConnect->File.List.Items[i].Name, (UDINT)&NewDirName) == 0)
							HmiFile.Status.SelectedIndex = i;
					}
					TestState = 1;
					break;
			}
			break;
		
		case 1:
			// Cut/paste directory
			switch (ActSubState)
			{
				case 0:
					pMpFileManagerUIConnect->File.Cut = 1;
					ActSubState = 1;
					break;
				
				case 1:
					pMpFileManagerUIConnect->File.Cut = 0;
					pMpFileManagerUIConnect->File.Refresh = 1;
					ActSubState = 2;
					break;
				
				case 2:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_REFRESH);
					pMpFileManagerUIConnect->File.Refresh = 0;
					ActSubState = 3;
					break;
				
				case 3:
					// Find folder to paste directory into
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					for(int i = 0; i < sizeof(pMpFileManagerUIConnect->File.List.Items)/sizeof(pMpFileManagerUIConnect->File.List.Items[0]); i++)
					{
						if(brsstrcmp((UDINT)&pMpFileManagerUIConnect->File.List.Items[i].Name, (UDINT)&DirName) == 0)
							HmiFile.Status.SelectedIndex = i;
					}
					ActSubState = 4;
					break;
				
				case 4:
					pMpFileManagerUIConnect->File.Refresh = 1;
					ActSubState = 5;
					break;
				
				case 5:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_REFRESH);
					pMpFileManagerUIConnect->File.Refresh = 0;
					ActSubState = 6;
					break;
			
				case 6:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					HmiFile.Commands.EnterFolder = 1;
					ActSubState = 7;
					break;
				
				case 7:
					HmiFile.Commands.EnterFolder = 0;
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_CHANGE_DIR);
					ActSubState = 8;
					break;
				
				case 8:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					pMpFileManagerUIConnect->File.Paste = 1;
					ActSubState = 9;
					break;
			
				case 9:
					pMpFileManagerUIConnect->File.Paste = 0;
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_PASTE);
					ActSubState = 10;
					break;
			
				case 10:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					pMpFileManagerUIConnect->File.Refresh = 1;
					ActSubState = 11;
					break;
			
				case 11:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_REFRESH);
					pMpFileManagerUIConnect->File.Refresh = 0;
					ActSubState = 12;
					break;
			
				case 12:
					// Check new location for cut directory
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					for(int i = 0; i < sizeof(pMpFileManagerUIConnect->File.List.Items)/sizeof(pMpFileManagerUIConnect->File.List.Items[0]); i++)
					{
						if(brsstrcmp((UDINT)&pMpFileManagerUIConnect->File.List.Items[i].Name, (UDINT)&NewDirName) == 0)
						{
							InNewLocation = 1;
						}
					}
					HmiFile.Commands.FolderUp = 1;
					ActSubState = 13;
					break;
				
				case 13:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_CHANGE_DIR);
					HmiFile.Commands.FolderUp = 0;
					ActSubState = 14;
					break;
				
				case 14:
					// Check old location for cut directory
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					for(int i = 0; i < sizeof(pMpFileManagerUIConnect->File.List.Items)/sizeof(pMpFileManagerUIConnect->File.List.Items[0]); i++)
					{
						if(brsstrcmp((UDINT)&pMpFileManagerUIConnect->File.List.Items[i].Name, (UDINT)&NewDirName) == 0)
						{
							InOldLocation = 1;
						}
					}
					TestState = 2;
					break;
			}
			break;
		
		case 2:
			// Check new and old locations for directory
			TEST_ASSERT(InNewLocation);
			TEST_ASSERT(!InOldLocation);
			TEST_DONE;
			break;
	}
	TEST_BUSY;
}

_TEST Multiselect(void)
{
	TIMEOUT_TEST_CASE;
		
	FileCreate(&FileCreate_0);
	FileClose(&FileClose_0);
	switch (TestState)
	{
		case 0:
			// Select UserX file device and navigate into directory with test files
			switch (ArrangeSubState)
			{
			
				case 0:
					brsmemcpy((UDINT)&pMpFileManagerUIConnect->File.NewName, (UDINT)&NewDirName, sizeof(pMpFileManagerUIConnect->File.NewName));
					pMpFileManagerUIConnect->File.CreateFolder = 1;
					ArrangeSubState = 1;
					break;
					
				case 1:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_CREATE);
					pMpFileManagerUIConnect->File.CreateFolder = 0;
					ArrangeSubState = 2;
				
				case 2:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					pMpFileManagerUIConnect->File.Refresh = 1;
					ArrangeSubState = 3;
					break;
				
				case 3:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_REFRESH);
					pMpFileManagerUIConnect->File.Refresh = 0;
					ArrangeSubState = 10;
					break;
				
				case 10:
					FileCreate_0.pDevice = (UDINT)&"mappUserXFiles";
					FileCreate_0.pFile = (UDINT)&CreateFileName;
					FileCreate_0.enable = 1;
					ArrangeSubState = 11;
					break;
					
				case 11:
					TEST_BUSY_CONDITION(FileCreate_0.status != 0);
					FileCreate_0.enable = 0;
					if ((FileCreate_0.status != 0) && (FileCreate_0.status != 65535))
					{
						TEST_FAIL("FileCreate function block has an error");
						TEST_ASSERT_EQUAL_INT(0, FileCreate_0.status);
						TEST_DONE;
					}
					FileClose_0.ident = FileCreate_0.ident;
					FileClose_0.enable = 1;
					ArrangeSubState = 12;
					break;
				
				case 12:
					TEST_BUSY_CONDITION(FileClose_0.status != 0);
					FileClose_0.enable = 0;
					if ((FileClose_0.status != 0) && (FileClose_0.status != 65535))
					{
						TEST_FAIL("FileClose function block has an error");
						TEST_ASSERT_EQUAL_INT(0, FileClose_0.status);
						TEST_DONE;
					}
					ArrangeSubState = 20;
					break;
			
				case 20:
					FileCreate_0.pDevice = (UDINT)&"mappUserXFiles";
					FileCreate_0.pFile = (UDINT)&NewFileName;
					FileCreate_0.enable = 1;
					ArrangeSubState = 21;
					break;
					
				case 21:
					TEST_BUSY_CONDITION(FileCreate_0.status != 0);
					FileCreate_0.enable = 0;
					if ((FileCreate_0.status != 0) && (FileCreate_0.status != 65535))
					{
						TEST_FAIL("FileCreate function block has an error");
						TEST_ASSERT_EQUAL_INT(0, FileCreate_0.status);
						TEST_DONE;
					}
					FileClose_0.ident = FileCreate_0.ident;
					FileClose_0.enable = 1;
					ArrangeSubState = 22;
					break;
				
				case 22:
					TEST_BUSY_CONDITION(FileClose_0.status != 0);
					FileClose_0.enable = 0;
					if ((FileClose_0.status != 0) && (FileClose_0.status != 65535))
					{
						TEST_FAIL("FileClose function block has an error");
						TEST_ASSERT_EQUAL_INT(0, FileClose_0.status);
						TEST_DONE;
					}
					ArrangeSubState = 30;
					break;
			
				case 30:
					pMpFileManagerUIConnect->File.Refresh = 1;
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_REFRESH);
					pMpFileManagerUIConnect->File.Refresh = 0;
					ArrangeSubState = 31;
					break;
			
				case 31:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					TestState = 1;
			}
			break;
		
		case 1:
			// Select multiple files/directories and copy/paste
			switch (ActSubState)
			{
				case 0:
					pMpFileManagerUIConnect->File.MultiSelect = 1;
					ActSubState = 1;
					break;
				
				case 1:
					pMpFileManagerUIConnect->File.List.Items[0].IsSelected = 0;
					pMpFileManagerUIConnect->File.List.Items[1].IsSelected = 1;
					pMpFileManagerUIConnect->File.List.Items[2].IsSelected = 1;
					ActSubState = 2;
					break;
			
				case 2:
					pMpFileManagerUIConnect->File.Copy = 1;
					ActSubState = 3;
					break;
				
				case 3:
					pMpFileManagerUIConnect->File.Copy = 0;
					pMpFileManagerUIConnect->File.MultiSelect = 0;
					pMpFileManagerUIConnect->File.List.Items[0].IsSelected = 1;
					pMpFileManagerUIConnect->File.List.Items[1].IsSelected = 0;
					pMpFileManagerUIConnect->File.List.Items[2].IsSelected = 0;
					ActSubState = 4;
					break;

				case 4:
					HmiFile.Commands.EnterFolder = 1;
					ActSubState = 5;
					break;
				
				case 5:
					HmiFile.Commands.EnterFolder = 0;
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_CHANGE_DIR);
					ActSubState = 6;
					break;
				
				case 6:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					pMpFileManagerUIConnect->File.Paste = 1;
					ActSubState = 7;
					break;
			
				case 7:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_PASTE);
					pMpFileManagerUIConnect->File.Paste = 0;
					ActSubState = 8;
					break;
			
				case 8:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					pMpFileManagerUIConnect->File.Refresh = 1;
					ActSubState = 9;
					break;
			
				case 9:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_REFRESH);
					pMpFileManagerUIConnect->File.Refresh = 0;
					ActSubState = 10;
					break;
			
				case 10:
					// Check for copied file
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					for(int i = 0; i < sizeof(pMpFileManagerUIConnect->File.List.Items)/sizeof(pMpFileManagerUIConnect->File.List.Items[0]); i++)
					{
						if(brsstrcmp((UDINT)&pMpFileManagerUIConnect->File.List.Items[i].Name, (UDINT)&NewFileName) == 0)
							MultiSelectFileCopy = 1;
					}
					ActSubState = 11;
					break;
				
				case 11:
					// Check for copied directory
					for(int i = 0; i < sizeof(pMpFileManagerUIConnect->File.List.Items)/sizeof(pMpFileManagerUIConnect->File.List.Items[0]); i++)
					{
						if(brsstrcmp((UDINT)&pMpFileManagerUIConnect->File.List.Items[i].Name, (UDINT)&CreateFileName) == 0)
							MultiSelectDirCopy = 1;
					}
					ActSubState = 12;
					break;
			
				case 12:
					HmiFile.Commands.FolderUp = 1;
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_CHANGE_DIR);
					HmiFile.Commands.FolderUp = 0;
					ActSubState = 13;
					break;
				
				case 13:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					TestState = 2;
					break;
			}
			break;
		
		case 2:
			// Check if copied file and directory were found
			TEST_ASSERT(MultiSelectFileCopy);
			TEST_ASSERT(MultiSelectDirCopy);
			TEST_DONE;
			break;
	}
	TEST_BUSY;
}

_TEST Search(void)
{
	TIMEOUT_TEST_CASE;
	
	FileCreate(&FileCreate_0);
	FileClose(&FileClose_0);
	switch (TestState)
	{
		case 0:
			switch (ArrangeSubState)
			{
				case 0:
					FileCreate_0.pDevice = (UDINT)&"mappUserXFiles";
					FileCreate_0.pFile = (UDINT)&NewFileName;
					FileCreate_0.enable = 1;
					ArrangeSubState = 1;
					break;
						
				case 1:
					TEST_BUSY_CONDITION(FileCreate_0.status != 0);
					FileCreate_0.enable = 0;
					if ((FileCreate_0.status != 0) && (FileCreate_0.status != 65535))
					{
						TEST_FAIL("FileCreate function block has an error");
						TEST_ASSERT_EQUAL_INT(0, FileCreate_0.status);
						TEST_DONE;
					}
					FileClose_0.ident = FileCreate_0.ident;
					FileClose_0.enable = 1;
					ArrangeSubState = 2;
					break;
					
				case 2:
					TEST_BUSY_CONDITION(FileClose_0.status != 0);
					FileClose_0.enable = 0;
					if ((FileClose_0.status != 0) && (FileClose_0.status != 65535))
					{
						TEST_FAIL("FileClose function block has an error");
						TEST_ASSERT_EQUAL_INT(0, FileClose_0.status);
						TEST_DONE;
					}
					ArrangeSubState = 10;
					break;
				
				case 10:			
					// Set filter value to name of file
					brsmemcpy((UDINT)&pMpFileManagerUIConnect->File.Filter, (UDINT)&NewFileName, sizeof(pMpFileManagerUIConnect->File.Filter));
					TestState = 1;
					break;
			}
			break;
		
		case 1:
			// Refresh MpFileManagerUIConnect
			switch (ActSubState)
			{
				case 0:
					pMpFileManagerUIConnect->File.Refresh = 1;
					ActSubState = 1;
					break;
				
				case 1:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_REFRESH);
					pMpFileManagerUIConnect->File.Refresh = 0;
					ActSubState = 2;
					break;
			
				case 2:
					// Check if the first item in the file list is the desired file
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					if(brsstrcmp((UDINT)&pMpFileManagerUIConnect->File.List.Items[0].Name, (UDINT)&NewFileName) == 0)
						NameMatch = 1;
					ActSubState = 3;
					break;
				
				case 3:
					// Reset filter
					brsmemcpy((UDINT)&pMpFileManagerUIConnect->File.Filter,(UDINT) &"", sizeof(pMpFileManagerUIConnect->File.Filter));
					pMpFileManagerUIConnect->File.Refresh = 1;
					ActSubState = 4;
					break;
				
				case 4:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_REFRESH);
					pMpFileManagerUIConnect->File.Refresh = 0;
					ActSubState = 5;
					break;
				
				case 5:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					TestState = 2;
					break;
			}
			break;
		
		case 2:
			// Check if filter worked
			TEST_ASSERT(NameMatch);
			TEST_DONE;
			break;
	}
	TEST_BUSY;
}

_TEST Enter_Folder(void)
{
	TIMEOUT_TEST_CASE;
	
	switch (TestState)
	{
		case 0:
			
			switch (ArrangeSubState)
			{
				case 0:
					brsmemcpy((UDINT)&pMpFileManagerUIConnect->File.NewName, (UDINT)&DirName, sizeof(pMpFileManagerUIConnect->File.NewName));
					pMpFileManagerUIConnect->File.CreateFolder = 1;
					ArrangeSubState = 1;
					break;
							
				case 1:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_CREATE);
					pMpFileManagerUIConnect->File.CreateFolder = 0;
					ArrangeSubState = 2;
						
				case 2:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					pMpFileManagerUIConnect->File.Refresh = 1;
					ArrangeSubState = 3;
					break;
						
				case 3:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_REFRESH);
					pMpFileManagerUIConnect->File.Refresh = 0;
					ArrangeSubState = 10;
					break;
			
				case 10:
					// Select folder to enter
					for(int i = 0; i < sizeof(pMpFileManagerUIConnect->File.List.Items)/sizeof(pMpFileManagerUIConnect->File.List.Items[0]); i++)
					{
						if(brsstrcmp((UDINT)&pMpFileManagerUIConnect->File.List.Items[i].Name, (UDINT)&DirName) == 0)
							HmiFile.Status.SelectedIndex = i;
					}
					TestState = 1;
					break;
			}	
			break;
		
		case 1:
			// Give HMI command to enter folder
			switch (ActSubState)
			{
				case 0:
					// Acts as a delay to let the folder selection make its way to FileMgr task
					ActSubState = 1;
					break;
			
				case 1:
					HmiFile.Commands.EnterFolder = 1;
					ActSubState = 2;
					break;
				
				case 2:
					HmiFile.Commands.EnterFolder = 0;
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_CHANGE_DIR);
					ActSubState = 3;
					break;
			
				case 3:
					// Check if current directory matches what is expected
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					if(brsstrcmp((UDINT)&pMpFileManagerUIConnect->File.PathInfo.CurrentDir, (UDINT)&DirName) == 0)
						NameMatch = 1;
					ActSubState = 4;
					break;
				
				case 4:
					// Go back up to root folder
					HmiFile.Commands.FolderUp = 1;
					ActSubState = 5;
					break;
				
				case 5:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_CHANGE_DIR);
					HmiFile.Commands.FolderUp = 0;
					ActSubState = 6;
					break;
				
				case 6:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					TestState = 2;
					break;
			}
			break;
		
		case 2:
			TEST_ASSERT(NameMatch);
			TEST_DONE;
			break;
	}
	TEST_BUSY;
}

_TEST Go_Up_Level(void)
{
	TIMEOUT_TEST_CASE;
	
	switch (TestState)
	{
		case 0:
			switch (ArrangeSubState)
			{
				case 0:
					brsmemcpy((UDINT)&pMpFileManagerUIConnect->File.NewName, (UDINT)&DirName, sizeof(pMpFileManagerUIConnect->File.NewName));
					pMpFileManagerUIConnect->File.CreateFolder = 1;
					ArrangeSubState = 1;
					break;
							
				case 1:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_CREATE);
					pMpFileManagerUIConnect->File.CreateFolder = 0;
					ArrangeSubState = 2;
						
				case 2:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					pMpFileManagerUIConnect->File.Refresh = 1;
					ArrangeSubState = 3;
					break;
						
				case 3:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_REFRESH);
					pMpFileManagerUIConnect->File.Refresh = 0;
					ArrangeSubState = 10;
					break;
			
				case 10:
					// Select folder to enter
					for(int i = 0; i < sizeof(pMpFileManagerUIConnect->File.List.Items)/sizeof(pMpFileManagerUIConnect->File.List.Items[0]); i++)
					{
						if(brsstrcmp((UDINT)&pMpFileManagerUIConnect->File.List.Items[i].Name, (UDINT)&DirName) == 0)
							HmiFile.Status.SelectedIndex = i;
					}
					TestState = 1;
					break;
			}
			break;
		
		case 1:
			// Give HMI command to enter folder
			switch (ActSubState)
			{
				case 0:
					// Acts as a delay to let the folder selection make its way to FileMgr task
					ActSubState = 1;
					break;
			
				case 1:
					HmiFile.Commands.EnterFolder = 1;
					ActSubState = 2;
					break;
				
				case 2:
					HmiFile.Commands.EnterFolder = 0;
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_CHANGE_DIR);
					ActSubState = 3;
					break;
			
				case 3:
					// Check if folder was successfully entered
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					if(brsstrcmp((UDINT)&pMpFileManagerUIConnect->File.PathInfo.CurrentDir, (UDINT)&DirName) != 0)
					{
						TEST_FAIL("Directory was not successfully entered");
						TEST_DONE;
					}
					ActSubState = 4;
					break;
				
				case 4:
					// Go back up to root folder
					HmiFile.Commands.FolderUp = 1;
					ActSubState = 5;
					break;
				
				case 5:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_CHANGE_DIR);
					HmiFile.Commands.FolderUp = 0;
					ActSubState = 6;
					break;
				
				case 6:
					// Check if folder level went back up to the root
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					if(brsstrcmp((UDINT)&pMpFileManagerUIConnect->File.PathInfo.CurrentDir, (UDINT)&"") == 0)
						NameMatch = 1;
					TestState = 2;
					break;
			}
			break;
		
		case 2:
			TEST_ASSERT(NameMatch);
			TEST_DONE;
			break;
	}
	TEST_BUSY;
}

_TEST Change_Sort(void)
{
	TIMEOUT_TEST_CASE;
	
	FileCreate(&FileCreate_0);
	FileClose(&FileClose_0);
	switch (TestState)
	{
		case 0:
			switch (ArrangeSubState) 
			{
				case 0:
					FileCreate_0.pDevice = (UDINT)&"mappUserXFiles";
					FileCreate_0.pFile = (UDINT)&CreateFileName;
					FileCreate_0.enable = 1;
					ArrangeSubState = 1;
					break;
							
				case 1:
					TEST_BUSY_CONDITION(FileCreate_0.status != 0);
					FileCreate_0.enable = 0;
					if ((FileCreate_0.status != 0) && (FileCreate_0.status != 65535))
					{
						TEST_FAIL("FileCreate function block has an error");
						TEST_ASSERT_EQUAL_INT(0, FileCreate_0.status);
						TEST_DONE;
					}
					FileClose_0.ident = FileCreate_0.ident;
					FileClose_0.enable = 1;
					ArrangeSubState = 2;
					break;
							
				case 2:
					TEST_BUSY_CONDITION(FileClose_0.status != 0);
					FileClose_0.enable = 0;
					if ((FileClose_0.status != 0) && (FileClose_0.status != 65535))
					{
						TEST_FAIL("FileClose function block has an error");
						TEST_ASSERT_EQUAL_INT(0, FileClose_0.status);
						TEST_DONE;
					}
					ArrangeSubState = 3;
					break;
			
				case 3:
					FileCreate_0.pDevice = (UDINT)&"mappUserXFiles";
					FileCreate_0.pFile = (UDINT)&NewFileName;
					FileCreate_0.enable = 1;
					ArrangeSubState = 4;
					break;
				
				case 4:
					TEST_BUSY_CONDITION(FileCreate_0.status != 0);
					FileCreate_0.enable = 0;
					if ((FileCreate_0.status != 0) && (FileCreate_0.status != 65535))
					{
						TEST_FAIL("FileCreate function block has an error");
						TEST_ASSERT_EQUAL_INT(0, FileCreate_0.status);
						TEST_DONE;
					}
					FileClose_0.ident = FileCreate_0.ident;
					FileClose_0.enable = 1;
					ArrangeSubState = 5;
					break;
				
				case 5:
					TEST_BUSY_CONDITION(FileClose_0.status != 0);
					FileClose_0.enable = 0;
					if ((FileClose_0.status != 0) && (FileClose_0.status != 65535))
					{
						TEST_FAIL("FileClose function block has an error");
						TEST_ASSERT_EQUAL_INT(0, FileClose_0.status);
						TEST_DONE;
					}
					ArrangeSubState = 10;
					break;
				
				case 10:			
					// Change SortOrder value
					pMpFileManagerUIConnect->File.SortOrder = mpFILE_UI_SORT_BY_MOD_TIME_DESC;
					TestState = 1;
					break;
			}
			break;
		
		case 1:
			switch (ActSubState)
			{
				case 0:
					// Wait for sort to take effect
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_SORT);
					ActSubState = 1;
					break;
			
				case 1:
					// Make sure sort worked correctly
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					if(brsstrcmp((UDINT)&pMpFileManagerUIConnect->File.List.Items[0].Name, (UDINT)&NewFileName) == 0)
						NameMatch = 1;
					ActSubState = 2;
					break;
				
				case 2:
					pMpFileManagerUIConnect->File.SortOrder = 0;
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_SORT);
					ActSubState = 3;
					break;
			
				case 3:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					TestState = 2;
					break;
			}
			break;
		
		case 2:
			TEST_ASSERT(NameMatch);
			TEST_DONE;
			break;
	}
	TEST_BUSY;
}

_TEST Delete_File(void)
{
	TIMEOUT_TEST_CASE;
	
	FileCreate(&FileCreate_0);
	FileClose(&FileClose_0);
	switch (TestState)
	{
		case 0:
			switch (ArrangeSubState) 
			{
				case 0:
					FileCreate_0.pDevice = (UDINT)&"mappUserXFiles";
					FileCreate_0.pFile = (UDINT)&CreateFileName;
					FileCreate_0.enable = 1;
					ArrangeSubState = 1;
					break;
							
				case 1:
					TEST_BUSY_CONDITION(FileCreate_0.status != 0);
					FileCreate_0.enable = 0;
					if ((FileCreate_0.status != 0) && (FileCreate_0.status != 65535))
					{
						TEST_FAIL("FileCreate function block has an error");
						TEST_ASSERT_EQUAL_INT(0, FileCreate_0.status);
						TEST_DONE;
					}
					FileClose_0.ident = FileCreate_0.ident;
					FileClose_0.enable = 1;
					ArrangeSubState = 2;
					break;
							
				case 2:
					TEST_BUSY_CONDITION(FileClose_0.status != 0);
					FileClose_0.enable = 0;
					if ((FileClose_0.status != 0) && (FileClose_0.status != 65535))
					{
						TEST_FAIL("FileClose function block has an error");
						TEST_ASSERT_EQUAL_INT(0, FileClose_0.status);
						TEST_DONE;
					}
					ArrangeSubState = 10;
					break;
	
				case 10:
					// Select file to be deleted
					for(int i = 0; i < sizeof(pMpFileManagerUIConnect->File.List.Items)/sizeof(pMpFileManagerUIConnect->File.List.Items[0]); i++)
					{
						if(brsstrcmp((UDINT)&pMpFileManagerUIConnect->File.List.Items[i].Name, (UDINT)&CreateFileName) == 0)
							HmiFile.Status.SelectedIndex = i;
					}
					TestState = 1;
					break;
			}
			break;

		case 1:
			// Delete file
			switch (ActSubState)
			{
				case 0:
					pMpFileManagerUIConnect->File.Delete = 1;
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_DELETE);
					pMpFileManagerUIConnect->File.Delete = 0;
					ActSubState = 1;
					break;
			
				case 1:
					pMpFileManagerUIConnect->MessageBox.Confirm = 1;
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					pMpFileManagerUIConnect->MessageBox.Confirm = 0;
					ActSubState = 2;
					break;
			
				case 2:
					pMpFileManagerUIConnect->File.Refresh = 1;
					ActSubState = 3;
					break;
			
				case 3:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_REFRESH);
					pMpFileManagerUIConnect->File.Refresh = 0;
					ActSubState = 4;
					break;
				
				case 4:
					// Check for file
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					for(int i = 0; i < sizeof(pMpFileManagerUIConnect->File.List.Items)/sizeof(pMpFileManagerUIConnect->File.List.Items[0]); i++)
					{
						if(brsstrcmp((UDINT)&pMpFileManagerUIConnect->File.List.Items[i].Name, (UDINT)&CreateFileName) == 0)
							NameMatch = 1;
					}
					TestState = 2;
					break;
			}
			break;
		
		case 2:
			// Check if file was deleted
			TEST_ASSERT(!NameMatch);
			TEST_DONE;
			break;
	}
	TEST_BUSY;
}

_TEST Delete_Directory(void)
{
	TIMEOUT_TEST_CASE;
	
	switch (TestState)
	{
		case 0:
			switch (ArrangeSubState)
			{
				case 0:
					brsmemcpy((UDINT)&pMpFileManagerUIConnect->File.NewName, (UDINT)&DirName, sizeof(pMpFileManagerUIConnect->File.NewName));
					pMpFileManagerUIConnect->File.CreateFolder = 1;
					ArrangeSubState = 1;
					break;
							
				case 1:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_CREATE);
					pMpFileManagerUIConnect->File.CreateFolder = 0;
					ArrangeSubState = 2;
						
				case 2:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					pMpFileManagerUIConnect->File.Refresh = 1;
					ArrangeSubState = 3;
					break;
						
				case 3:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_REFRESH);
					pMpFileManagerUIConnect->File.Refresh = 0;
					ArrangeSubState = 10;
					break;

				case 10:
					// Select directory to be deleted
					for(int i = 0; i < sizeof(pMpFileManagerUIConnect->File.List.Items)/sizeof(pMpFileManagerUIConnect->File.List.Items[0]); i++)
					{
						if(brsstrcmp((UDINT)&pMpFileManagerUIConnect->File.List.Items[i].Name, (UDINT)&DirName) == 0)
							HmiFile.Status.SelectedIndex = i;
					}
					TestState = 1;
					break;
			}
			break;
		
		case 1:
			// Delete file
			switch (ActSubState)
			{
				case 0:
					pMpFileManagerUIConnect->File.Delete = 1;
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_DELETE);
					pMpFileManagerUIConnect->File.Delete = 0;
					ActSubState = 1;
					break;
			
				case 1:
					pMpFileManagerUIConnect->MessageBox.Confirm = 1;
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_IDLE);
					pMpFileManagerUIConnect->MessageBox.Confirm = 0;
					ActSubState = 2;
					break;
					break;
			
				case 2:
					pMpFileManagerUIConnect->File.Refresh = 1;
					ActSubState = 3;
					break;
			
				case 3:
					TEST_BUSY_CONDITION(pMpFileManagerUIConnect->Status != mpFILE_UI_STATUS_REFRESH);
					pMpFileManagerUIConnect->File.Refresh = 0;
					ActSubState = 4;
					break;
				
				case 4:
					// Check for file
					for(int i = 0; i < sizeof(pMpFileManagerUIConnect->File.List.Items)/sizeof(pMpFileManagerUIConnect->File.List.Items[0]); i++)
					{
						if(brsstrcmp((UDINT)&pMpFileManagerUIConnect->File.List.Items[i].Name, (UDINT)&DirName) == 0)
							NameMatch = 1;
					}
					TestState = 2;
					break;
			}
			break;
		
		case 2:
			// Check if file was deleted
			TEST_ASSERT(!NameMatch);
			TEST_DONE;
			break;
	}
	TEST_BUSY;
}

_TEST FIFO_20(void)
{
	TEST_DONE;
	switch (TestState)
	{
		// Arrange
		case 0:
			FileCreate_UT.enable = true;
			FileCreate_UT.pDevice = (UDINT)&"mappUserXFiles";
			snprintf2(FileName, sizeof(FileName), "TestFile%d.txt", FileNumber);
			FileCreate_UT.pFile = (UDINT)&FileName;
			FileCreate(&FileCreate_UT);
			
			TEST_BUSY_CONDITION(FileCreate_UT.status == 65535);
			TEST_ABORT_CONDITION(FileCreate_UT.status != 0);
			TestState = 1;
			break;
		
		case 1:
			FileClose_UT.enable = true;
			FileClose_UT.ident = FileCreate_UT.ident;
			FileClose(&FileClose_UT);
			
			TEST_BUSY_CONDITION(FileClose_UT.status == 65535);
			TEST_ABORT_CONDITION(FileClose_UT.status != 0);
			
			FileNumber++;
			TestState = (FileNumber >= 20) ? 10 : 0;
			break;
		
		// Act
		case 10:
			HmiFile_UT.Parameters.Fifo.Enable = true;
			strcpy(HmiFile_UT.Parameters.Fifo.DeviceName, "mappUserXFiles");
			HmiFile_UT.Parameters.Fifo.FifoType = FILE_FIFO_NUM_OF_FILES;
			HmiFile_UT.Parameters.Fifo.MaxNumberOfFiles = 10;
			HmiFile_UT.Parameters.Fifo.ScanInterval = 0;
			TEST_BUSY_CONDITION(FileIdleOrDisabled());
			TestState = 100;
			break;
			
		// Assert
		case 100:
			TEST_BUSY_CONDITION(!FileIdleOrDisabled());
			HmiFile_UT.Parameters.Fifo.Enable = false;

			DirInfo_UT.enable = true;
			DirInfo_UT.pDevice = (UDINT)&"mappUserXFiles";
			DirInfo_UT.pPath = (UDINT)&"";
			DirInfo(&DirInfo_UT);
			TEST_BUSY_CONDITION(DirInfo_UT.status == 65535);
			TEST_ABORT_CONDITION(DirInfo_UT.status != 0);
			TEST_ASSERT_EQUAL_INT(HmiFile_UT.Parameters.Fifo.MaxNumberOfFiles, DirInfo_UT.filenum);
			TEST_DONE;
			break;
	}
	TEST_BUSY;
}

_TEST FIFO_60(void)
{
	TEST_DONE;
	switch (TestState)
	{
		// Arrange
		case 0:
			FileCreate_UT.enable = true;
			FileCreate_UT.pDevice = (UDINT)&"mappUserXFiles";
			snprintf2(FileName, sizeof(FileName), "TestFile%d.txt", FileNumber);
			FileCreate_UT.pFile = (UDINT)&FileName;
			FileCreate(&FileCreate_UT);
			
			TEST_BUSY_CONDITION(FileCreate_UT.status == 65535);
			TEST_ABORT_CONDITION(FileCreate_UT.status != 0);
			TestState = 1;
			break;
		
		case 1:
			FileClose_UT.enable = true;
			FileClose_UT.ident = FileCreate_UT.ident;
			FileClose(&FileClose_UT);
			
			TEST_BUSY_CONDITION(FileClose_UT.status == 65535);
			TEST_ABORT_CONDITION(FileClose_UT.status != 0);
			
			FileNumber++;
			TestState = (FileNumber >= 60) ? 10 : 0;
			break;
		
		// Act
		case 10:
			HmiFile_UT.Parameters.Fifo.Enable = true;
			strcpy(HmiFile_UT.Parameters.Fifo.DeviceName, "mappUserXFiles");
			HmiFile_UT.Parameters.Fifo.FifoType = FILE_FIFO_NUM_OF_FILES;
			HmiFile_UT.Parameters.Fifo.MaxNumberOfFiles = 15;
			HmiFile_UT.Parameters.Fifo.ScanInterval = 0;
			TEST_BUSY_CONDITION(FileIdleOrDisabled());
			TestState = 100;
			break;
			
		// Assert
		case 100:
			TEST_BUSY_CONDITION(!FileIdleOrDisabled());
			HmiFile_UT.Parameters.Fifo.Enable = false;

			DirInfo_UT.enable = true;
			DirInfo_UT.pDevice = (UDINT)&"mappUserXFiles";
			DirInfo_UT.pPath = (UDINT)&"";
			DirInfo(&DirInfo_UT);
			TEST_BUSY_CONDITION(DirInfo_UT.status == 65535);
			TEST_ABORT_CONDITION(DirInfo_UT.status != 0);
			TEST_ASSERT_EQUAL_INT(HmiFile_UT.Parameters.Fifo.MaxNumberOfFiles, DirInfo_UT.filenum);
			TEST_DONE;
			break;
		
	}
	TEST_BUSY;
}

_TEST FIFO_140(void)
{
	TEST_DONE;
	switch (TestState)
	{
		// Arrange
		case 0:
			FileCreate_UT.enable = true;
			FileCreate_UT.pDevice = (UDINT)&"mappUserXFiles";
			snprintf2(FileName, sizeof(FileName), "TestFile%d.txt", FileNumber);
			FileCreate_UT.pFile = (UDINT)&FileName;
			FileCreate(&FileCreate_UT);
			
			TEST_BUSY_CONDITION(FileCreate_UT.status == 65535);
			TEST_ABORT_CONDITION(FileCreate_UT.status != 0);
			TestState = 1;
			break;
		
		case 1:
			FileClose_UT.enable = true;
			FileClose_UT.ident = FileCreate_UT.ident;
			FileClose(&FileClose_UT);
			
			TEST_BUSY_CONDITION(FileClose_UT.status == 65535);
			TEST_ABORT_CONDITION(FileClose_UT.status != 0);
			
			FileNumber++;
			TestState = (FileNumber >= 140) ? 10 : 0;
			break;
		
		// Act
		case 10:
			HmiFile_UT.Parameters.Fifo.Enable = true;
			strcpy(HmiFile_UT.Parameters.Fifo.DeviceName, "mappUserXFiles");
			HmiFile_UT.Parameters.Fifo.FifoType = FILE_FIFO_NUM_OF_FILES;
			HmiFile_UT.Parameters.Fifo.MaxNumberOfFiles = 15;
			HmiFile_UT.Parameters.Fifo.ScanInterval = 0;
			TEST_BUSY_CONDITION(FileIdleOrDisabled());
			TestState = 100;
			break;
			
		// Assert
		case 100:
			TEST_BUSY_CONDITION(!FileIdleOrDisabled());
			HmiFile_UT.Parameters.Fifo.Enable = false;

			DirInfo_UT.enable = true;
			DirInfo_UT.pDevice = (UDINT)&"mappUserXFiles";
			DirInfo_UT.pPath = (UDINT)&"";
			DirInfo(&DirInfo_UT);
			TEST_BUSY_CONDITION(DirInfo_UT.status == 65535);
			TEST_ABORT_CONDITION(DirInfo_UT.status != 0);
			TEST_ASSERT_EQUAL_INT(HmiFile_UT.Parameters.Fifo.MaxNumberOfFiles, DirInfo_UT.filenum);
			TEST_DONE;
			break;
		
	}
	TEST_BUSY;
}

_TEST FIFO_MaxFiles60(void)
{
	TEST_DONE;
	switch (TestState)
	{
		// Arrange
		case 0:
			FileCreate_UT.enable = true;
			FileCreate_UT.pDevice = (UDINT)&"mappUserXFiles";
			snprintf2(FileName, sizeof(FileName), "TestFile%d.txt", FileNumber);
			FileCreate_UT.pFile = (UDINT)&FileName;
			FileCreate(&FileCreate_UT);
			
			TEST_BUSY_CONDITION(FileCreate_UT.status == 65535);
			TEST_ABORT_CONDITION(FileCreate_UT.status != 0);
			TestState = 1;
			break;
		
		case 1:
			FileClose_UT.enable = true;
			FileClose_UT.ident = FileCreate_UT.ident;
			FileClose(&FileClose_UT);
			
			TEST_BUSY_CONDITION(FileClose_UT.status == 65535);
			TEST_ABORT_CONDITION(FileClose_UT.status != 0);
			
			FileNumber++;
			TestState = (FileNumber >= 100) ? 10 : 0;
			break;
		
		// Act
		case 10:
			HmiFile_UT.Parameters.Fifo.Enable = true;
			strcpy(HmiFile_UT.Parameters.Fifo.DeviceName, "mappUserXFiles");
			HmiFile_UT.Parameters.Fifo.FifoType = FILE_FIFO_NUM_OF_FILES;
			HmiFile_UT.Parameters.Fifo.MaxNumberOfFiles = 60;
			HmiFile_UT.Parameters.Fifo.ScanInterval = 0;
			TEST_BUSY_CONDITION(FileIdleOrDisabled());
			TestState = 100;
			break;
			
		// Assert
		case 100:
			TEST_BUSY_CONDITION(!FileIdleOrDisabled());
			HmiFile_UT.Parameters.Fifo.Enable = false;

			DirInfo_UT.enable = true;
			DirInfo_UT.pDevice = (UDINT)&"mappUserXFiles";
			DirInfo_UT.pPath = (UDINT)&"";
			DirInfo(&DirInfo_UT);
			TEST_BUSY_CONDITION(DirInfo_UT.status == 65535);
			TEST_ABORT_CONDITION(DirInfo_UT.status != 0);
			TEST_ASSERT_EQUAL_INT(HmiFile_UT.Parameters.Fifo.MaxNumberOfFiles, DirInfo_UT.filenum);
			TEST_DONE;
			break;
		
	}
	TEST_BUSY;
}

_TEST FIFO_MaxFiles120(void)
{
	TEST_DONE;
	switch (TestState)
	{
		// Arrange
		case 0:
			FileCreate_UT.enable = true;
			FileCreate_UT.pDevice = (UDINT)&"mappUserXFiles";
			snprintf2(FileName, sizeof(FileName), "TestFile%d.txt", FileNumber);
			FileCreate_UT.pFile = (UDINT)&FileName;
			FileCreate(&FileCreate_UT);
			
			TEST_BUSY_CONDITION(FileCreate_UT.status == 65535);
			TEST_ABORT_CONDITION(FileCreate_UT.status != 0);
			TestState = 1;
			break;
		
		case 1:
			FileClose_UT.enable = true;
			FileClose_UT.ident = FileCreate_UT.ident;
			FileClose(&FileClose_UT);
			
			TEST_BUSY_CONDITION(FileClose_UT.status == 65535);
			TEST_ABORT_CONDITION(FileClose_UT.status != 0);
			
			FileNumber++;
			TestState = (FileNumber >= 200) ? 10 : 0;
			break;
		
		// Act
		case 10:
			HmiFile_UT.Parameters.Fifo.Enable = true;
			strcpy(HmiFile_UT.Parameters.Fifo.DeviceName, "mappUserXFiles");
			HmiFile_UT.Parameters.Fifo.FifoType = FILE_FIFO_NUM_OF_FILES;
			HmiFile_UT.Parameters.Fifo.MaxNumberOfFiles = 120;
			HmiFile_UT.Parameters.Fifo.ScanInterval = 0;
			TEST_BUSY_CONDITION(FileIdleOrDisabled());
			TestState = 100;
			break;
			
		// Assert
		case 100:
			TEST_BUSY_CONDITION(!FileIdleOrDisabled());
			HmiFile_UT.Parameters.Fifo.Enable = false;

			DirInfo_UT.enable = true;
			DirInfo_UT.pDevice = (UDINT)&"mappUserXFiles";
			DirInfo_UT.pPath = (UDINT)&"";
			DirInfo(&DirInfo_UT);
			TEST_BUSY_CONDITION(DirInfo_UT.status == 65535);
			TEST_ABORT_CONDITION(DirInfo_UT.status != 0);
			TEST_ASSERT_EQUAL_INT(HmiFile_UT.Parameters.Fifo.MaxNumberOfFiles, DirInfo_UT.filenum);
			TEST_DONE;
			break;
		
	}
	TEST_BUSY;
}

_TEST FIFO_MaxFolderSize_30Files(void)
{
	TEST_DONE;
	switch (TestState)
	{
		// Arrange
		case 0:
			FileCreate_UT.enable = true;
			FileCreate_UT.pDevice = (UDINT)&"mappUserXFiles";
			snprintf2(FileName, sizeof(FileName), "TestFile%d.txt", FileNumber);
			FileCreate_UT.pFile = (UDINT)&FileName;
			FileCreate(&FileCreate_UT);
			
			TEST_BUSY_CONDITION(FileCreate_UT.status == 65535);
			TEST_ABORT_CONDITION(FileCreate_UT.status != 0);
			TestState = 1;
			break;
		
		case 1:
			FileWrite_UT.enable = true;
			FileWrite_UT.ident = FileCreate_UT.ident;
			FileWrite_UT.offset = 0;
			FileWrite_UT.pSrc = (UDINT)&testData;
			FileWrite_UT.len = sizeof(testData);
			FileWrite(&FileWrite_UT);
			TEST_BUSY_CONDITION(FileWrite_UT.status == 65535);
			TEST_ABORT_CONDITION(FileWrite_UT.status != 0);
			TestState = 2;
			break;
			
		case 2:
			FileClose_UT.enable = true;
			FileClose_UT.ident = FileCreate_UT.ident;
			FileClose(&FileClose_UT);
			
			TEST_BUSY_CONDITION(FileClose_UT.status == 65535);
			TEST_ABORT_CONDITION(FileClose_UT.status != 0);
			
			FileNumber++;
			TestState = (FileNumber >= 30) ? 10 : 0;
			break;
		
		// Act
		case 10:
			HmiFile_UT.Parameters.Fifo.Enable = true;
			strcpy(HmiFile_UT.Parameters.Fifo.DeviceName, "mappUserXFiles");
			HmiFile_UT.Parameters.Fifo.FifoType = FILE_FIFO_SIZE_OF_FOLDER;
			HmiFile_UT.Parameters.Fifo.MaxFolderSize = 20;
			HmiFile_UT.Parameters.Fifo.ScanInterval = 0;
			TEST_BUSY_CONDITION(FileIdleOrDisabled());
			TestState = 100;
			break;
			
		// Assert
		case 100:
			TEST_BUSY_CONDITION(!FileIdleOrDisabled());
			HmiFile_UT.Parameters.Fifo.Enable = false;

			DirInfo_UT.enable = true;
			DirInfo_UT.pDevice = (UDINT)&"mappUserXFiles";
			DirInfo_UT.pPath = (UDINT)&"";
			DirInfo(&DirInfo_UT);
			TEST_BUSY_CONDITION(DirInfo_UT.status == 65535);
			TEST_ABORT_CONDITION(DirInfo_UT.status != 0);
			TEST_ASSERT_EQUAL_INT(20, DirInfo_UT.filenum);
			TEST_DONE;
			break;
		
	}
	TEST_BUSY;
}

_TEST FIFO_MaxFolderSize_60Files(void)
{
	TEST_DONE;
	switch (TestState)
	{
		// Arrange
		case 0:
			FileCreate_UT.enable = true;
			FileCreate_UT.pDevice = (UDINT)&"mappUserXFiles";
			snprintf2(FileName, sizeof(FileName), "TestFile%d.txt", FileNumber);
			FileCreate_UT.pFile = (UDINT)&FileName;
			FileCreate(&FileCreate_UT);
			
			TEST_BUSY_CONDITION(FileCreate_UT.status == 65535);
			TEST_ABORT_CONDITION(FileCreate_UT.status != 0);
			TestState = 1;
			break;
		
		case 1:
			FileWrite_UT.enable = true;
			FileWrite_UT.ident = FileCreate_UT.ident;
			FileWrite_UT.offset = 0;
			FileWrite_UT.pSrc = (UDINT)&testData;
			FileWrite_UT.len = sizeof(testData);
			FileWrite(&FileWrite_UT);
			TEST_BUSY_CONDITION(FileWrite_UT.status == 65535);
			TEST_ABORT_CONDITION(FileWrite_UT.status != 0);
			TestState = 2;
			break;
			
		case 2:
			FileClose_UT.enable = true;
			FileClose_UT.ident = FileCreate_UT.ident;
			FileClose(&FileClose_UT);
			
			TEST_BUSY_CONDITION(FileClose_UT.status == 65535);
			TEST_ABORT_CONDITION(FileClose_UT.status != 0);
			
			FileNumber++;
			TestState = (FileNumber >= 60) ? 10 : 0;
			break;
		
		// Act
		case 10:
			HmiFile_UT.Parameters.Fifo.Enable = true;
			strcpy(HmiFile_UT.Parameters.Fifo.DeviceName, "mappUserXFiles");
			HmiFile_UT.Parameters.Fifo.FifoType = FILE_FIFO_SIZE_OF_FOLDER;
			HmiFile_UT.Parameters.Fifo.MaxFolderSize = 40;
			HmiFile_UT.Parameters.Fifo.ScanInterval = 0;
			TEST_BUSY_CONDITION(FileIdleOrDisabled());
			TestState = 100;
			break;
			
		// Assert
		case 100:
			TEST_BUSY_CONDITION(!FileIdleOrDisabled());
			HmiFile_UT.Parameters.Fifo.Enable = false;

			DirInfo_UT.enable = true;
			DirInfo_UT.pDevice = (UDINT)&"mappUserXFiles";
			DirInfo_UT.pPath = (UDINT)&"";
			DirInfo(&DirInfo_UT);
			TEST_BUSY_CONDITION(DirInfo_UT.status == 65535);
			TEST_ABORT_CONDITION(DirInfo_UT.status != 0);
			TEST_ASSERT_EQUAL_INT(40, DirInfo_UT.filenum);
			TEST_DONE;
			break;
		
	}
	TEST_BUSY;
}

_TEST FIFO_MaxFolderSize_Keep60Files(void)
{
	TEST_DONE;
	switch (TestState)
	{
		// Arrange
		case 0:
			FileCreate_UT.enable = true;
			FileCreate_UT.pDevice = (UDINT)&"mappUserXFiles";
			snprintf2(FileName, sizeof(FileName), "TestFile%d.txt", FileNumber);
			FileCreate_UT.pFile = (UDINT)&FileName;
			FileCreate(&FileCreate_UT);
			
			TEST_BUSY_CONDITION(FileCreate_UT.status == 65535);
			TEST_ABORT_CONDITION(FileCreate_UT.status != 0);
			TestState = 1;
			break;
		
		case 1:
			FileWrite_UT.enable = true;
			FileWrite_UT.ident = FileCreate_UT.ident;
			FileWrite_UT.offset = 0;
			FileWrite_UT.pSrc = (UDINT)&testData;
			FileWrite_UT.len = sizeof(testData);
			FileWrite(&FileWrite_UT);
			TEST_BUSY_CONDITION(FileWrite_UT.status == 65535);
			TEST_ABORT_CONDITION(FileWrite_UT.status != 0);
			TestState = 2;
			break;
			
		case 2:
			FileClose_UT.enable = true;
			FileClose_UT.ident = FileCreate_UT.ident;
			FileClose(&FileClose_UT);
			
			TEST_BUSY_CONDITION(FileClose_UT.status == 65535);
			TEST_ABORT_CONDITION(FileClose_UT.status != 0);
			
			FileNumber++;
			TestState = (FileNumber >= 90) ? 10 : 0;
			break;
		
		// Act
		case 10:
			HmiFile_UT.Parameters.Fifo.Enable = true;
			strcpy(HmiFile_UT.Parameters.Fifo.DeviceName, "mappUserXFiles");
			HmiFile_UT.Parameters.Fifo.FifoType = FILE_FIFO_SIZE_OF_FOLDER;
			HmiFile_UT.Parameters.Fifo.MaxFolderSize = 60;
			HmiFile_UT.Parameters.Fifo.ScanInterval = 0;
			TEST_BUSY_CONDITION(FileIdleOrDisabled());
			TestState = 100;
			break;
			
		// Assert
		case 100:
			TEST_BUSY_CONDITION(!FileIdleOrDisabled());
			HmiFile_UT.Parameters.Fifo.Enable = false;

			DirInfo_UT.enable = true;
			DirInfo_UT.pDevice = (UDINT)&"mappUserXFiles";
			DirInfo_UT.pPath = (UDINT)&"";
			DirInfo(&DirInfo_UT);
			TEST_BUSY_CONDITION(DirInfo_UT.status == 65535);
			TEST_ABORT_CONDITION(DirInfo_UT.status != 0);
			TEST_ASSERT_EQUAL_INT(60, DirInfo_UT.filenum);
			TEST_DONE;
			break;
		
	}
	TEST_BUSY;
}

_TEST FIFO_MaxFolderSize_Keep120Files(void)
{
	TEST_DONE;
	switch (TestState)
	{
		// Arrange
		case 0:
			FileCreate_UT.enable = true;
			FileCreate_UT.pDevice = (UDINT)&"mappUserXFiles";
			snprintf2(FileName, sizeof(FileName), "TestFile%d.txt", FileNumber);
			FileCreate_UT.pFile = (UDINT)&FileName;
			FileCreate(&FileCreate_UT);
			
			TEST_BUSY_CONDITION(FileCreate_UT.status == 65535);
			TEST_ABORT_CONDITION(FileCreate_UT.status != 0);
			TestState = 1;
			break;
		
		case 1:
			FileWrite_UT.enable = true;
			FileWrite_UT.ident = FileCreate_UT.ident;
			FileWrite_UT.offset = 0;
			FileWrite_UT.pSrc = (UDINT)&testData;
			FileWrite_UT.len = sizeof(testData);
			FileWrite(&FileWrite_UT);
			TEST_BUSY_CONDITION(FileWrite_UT.status == 65535);
			TEST_ABORT_CONDITION(FileWrite_UT.status != 0);
			TestState = 2;
			break;
			
		case 2:
			FileClose_UT.enable = true;
			FileClose_UT.ident = FileCreate_UT.ident;
			FileClose(&FileClose_UT);
			
			TEST_BUSY_CONDITION(FileClose_UT.status == 65535);
			TEST_ABORT_CONDITION(FileClose_UT.status != 0);
			
			FileNumber++;
			TestState = (FileNumber >= 140) ? 10 : 0;
			break;
		
		// Act
		case 10:
			HmiFile_UT.Parameters.Fifo.Enable = true;
			strcpy(HmiFile_UT.Parameters.Fifo.DeviceName, "mappUserXFiles");
			HmiFile_UT.Parameters.Fifo.FifoType = FILE_FIFO_SIZE_OF_FOLDER;
			HmiFile_UT.Parameters.Fifo.MaxFolderSize = 120;
			HmiFile_UT.Parameters.Fifo.ScanInterval = 0;
			TEST_BUSY_CONDITION(FileIdleOrDisabled());
			TestState = 100;
			break;
			
		// Assert
		case 100:
			TEST_BUSY_CONDITION(!FileIdleOrDisabled());
			HmiFile_UT.Parameters.Fifo.Enable = false;

			DirInfo_UT.enable = true;
			DirInfo_UT.pDevice = (UDINT)&"mappUserXFiles";
			DirInfo_UT.pPath = (UDINT)&"";
			DirInfo(&DirInfo_UT);
			TEST_BUSY_CONDITION(DirInfo_UT.status == 65535);
			TEST_ABORT_CONDITION(DirInfo_UT.status != 0);
			TEST_ASSERT_EQUAL_INT(120, DirInfo_UT.filenum);
			TEST_DONE;
			break;
		
	}
	TEST_BUSY;
}
/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2023-04-03 16:22:59Z
By B+R UnitTest Helper Version: 2.0.1.59
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("Create_Directory", Create_Directory), 
	new_TestFixture("Add_File", Add_File), 
	new_TestFixture("Copy_File", Copy_File), 
	new_TestFixture("Copy_Directory", Copy_Directory), 
	new_TestFixture("Rename_File", Rename_File), 
	new_TestFixture("Rename_Directory", Rename_Directory), 
	new_TestFixture("Cut_Paste_File", Cut_Paste_File), 
	new_TestFixture("Cut_Paste_Directory", Cut_Paste_Directory), 
	new_TestFixture("Multiselect", Multiselect), 
	new_TestFixture("Search", Search), 
	new_TestFixture("Enter_Folder", Enter_Folder), 
	new_TestFixture("Go_Up_Level", Go_Up_Level), 
	new_TestFixture("Change_Sort", Change_Sort), 
	new_TestFixture("Delete_File", Delete_File), 
	new_TestFixture("Delete_Directory", Delete_Directory), 
	new_TestFixture("FIFO_20", FIFO_20), 
	new_TestFixture("FIFO_60", FIFO_60), 
	new_TestFixture("FIFO_140", FIFO_140), 
	new_TestFixture("FIFO_MaxFiles60", FIFO_MaxFiles60), 
	new_TestFixture("FIFO_MaxFiles120", FIFO_MaxFiles120), 
	new_TestFixture("FIFO_MaxFolderSize_30Files", FIFO_MaxFolderSize_30Files), 
	new_TestFixture("FIFO_MaxFolderSize_60Files", FIFO_MaxFolderSize_60Files), 
	new_TestFixture("FIFO_MaxFolderSize_Keep60Files", FIFO_MaxFolderSize_Keep60Files), 
	new_TestFixture("FIFO_MaxFolderSize_Keep120Files", FIFO_MaxFolderSize_Keep120Files), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(Set_FileMgr, "Set_FileMgr", setupTest, teardownTest, fixtures, setupSet, teardownSet, cyclicSetCaller);

