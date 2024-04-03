//***********************************************************************
// Copyright: B&R Industrial Automation GmbH
// Author: B&R Industrial Automation GmbH
// Created: Sept 1, 2022
// Description: Task for audit management.
//***********************************************************************

PROGRAM _INIT

	// Create folder for this component on the user file device
	DirCreateAudit(enable := TRUE, pDevice := ADR('mappAuditFiles'), pName := ADR('/'));

	// Wait for DirCreate_0 to complete.
	WHILE (DirCreateAudit.status = ERR_FUB_BUSY) DO
		DirCreateAudit();
	END_WHILE
	
	// Check if folder already exist and if so disabled the function block call
	IF DirCreateAudit.status = fiERR_DIR_ALREADY_EXIST OR (DirCreateAudit.status = ERR_OK) THEN
		DirCreateAudit(enable := FALSE);
	END_IF

	// Initialize mapp function blocks
	MpAuditTrailSys.Enable := TRUE;
	MpAuditTrailSys.MpLink := ADR(gMpLinkAuditTrail);
	HmiAudit.Parameters.FileName := 'Archive_%Y_%m_%d_%H_%M_%S';
	MpAuditTrailSys.FileName := ADR(HmiAudit.Parameters.FileName); 
	MpAuditTrailSys.Language := ADR('en');
	MpAuditTrailSys.DeviceName := ADR('mappAuditFiles');
	MpAuditTrailSys();
	
#warning "USER WRN: TODO: replace config FB"
//	  MpAuditTrailConfigSys.Enable := TRUE;
//	  MpAuditTrailConfigSys.MpLink := ADR(gMpLinkAuditTrail);
//	  MpAuditTrailConfigSys.Configuration := ADR(AuditTrailConfig);
//	  MpAuditTrailConfigSys.Load := TRUE;
//	  MpAuditTrailConfigSys();

	MpAuditTrailCEvents.Enable := TRUE;
	MpAuditTrailCEvents.MpLink := ADR(gMpLinkCustomEvents);
	MpAuditTrailCEvents();

	MpAuditTrailUISys.MpLink := ADR(gMpLinkAuditTrail);
	MpAuditTrailUISys.UIConnect := ADR(MpAuditTrailUIConnect);
	MpAuditTrailUISys.UISetup.EventListSize := SIZEOF(MpAuditTrailUIConnect.Output.EventID) / SIZEOF(MpAuditTrailUIConnect.Output.EventID[0]);
	MpAuditTrailUISys.UISetup.ScrollWindow := 1;
	MpAuditTrailUISys.Enable := TRUE;
	MpAuditTrailUISys();
	
	// Initialize custom events
	CustomEvent[0].Type := "Custom Event Type";
	CustomEvent[0].Msg := "Custom Event Message";
	CustomEvent[0].Comment := "Custom Event Comment";

	CustomEvent[1].Type := "Audit Test";
	CustomEvent[1].Msg := "This is a custom event test msg";
	CustomEvent[1].Comment := "If you see this it was a success!";

	CustomEvent[2].Type := "Cmd Exe";
	CustomEvent[2].Msg := "The run query command was pressed on the HMI";
	CustomEvent[2].Comment := "Result can be seen in the Query tab";

	HmiAudit.Status.Query.Name := 'UserEvents';
	HmiAudit.Status.Query.Option := 0;

	// Configuring the query selection, reading the available components
	HmiAudit.Parameters.QuerySelection[0] := 'UserXMgr';
	HmiAudit.Parameters.QuerySelection[1] := 'RecipeMgr';

	IF (ST_ident(ADR(HmiAudit.Parameters.QuerySelection[0]), 0, ADR(ident)) = 0) AND (ST_ident(ADR(HmiAudit.Parameters.QuerySelection[1]), 0, ADR(ident)) = 0) THEN
		HmiAudit.Status.DeviceDataProvider[0] := '{"value":"UserEvents","text":"User Events Query"}';
		HmiAudit.Status.DeviceDataProvider[1] := '{"value":"RecipeEvents","text":"Recipe Events Query"}';
	ELSIF (ST_ident(ADR(HmiAudit.Parameters.QuerySelection[0]), 0, ADR(ident)) <> 0) AND (ST_ident(ADR(HmiAudit.Parameters.QuerySelection[1]), 0, ADR(ident)) = 0) THEN
		HmiAudit.Status.DeviceDataProvider[0] := '{"value":"RecipeEvents","text":"Recipe Events Query"}';
	ELSIF (ST_ident(ADR(HmiAudit.Parameters.QuerySelection[0]), 0, ADR(ident)) = 0) AND (ST_ident(ADR(HmiAudit.Parameters.QuerySelection[1]), 0, ADR(ident)) <> 0) THEN
		HmiAudit.Status.DeviceDataProvider[0] := '{"value":"UserEvents","text":"User Events Query"}';
	END_IF

	// Restored the retained values to the archive settings
	HmiAudit.Parameters.ArchiveSettings := ArchiveSettingsRetain;

END_PROGRAM

PROGRAM _CYCLIC

	// Call all cyclic actions
	ExecuteQuery;
	QueryTableConfig;
	ArchiveExport;
	ArchiveSettings;
	ChangeConfiguration;

	// Sample code for how custom events can be triggered. Use custom events as needed around the application for debugging purposes.
	IF EDGEPOS(CustomEvent[0].Set) THEN
		MpAuditCustomEvent(gMpLinkCustomEvents,CustomEvent[0].Type,CustomEvent[0].Msg,CustomEvent[0].Comment);
	END_IF
	IF EDGENEG(CustomEvent[1].Set) THEN
		MpAuditCustomEvent(gMpLinkCustomEvents,CustomEvent[1].Type,CustomEvent[1].Msg,CustomEvent[1].Comment);
	END_IF

	// Change sample variable randomly to trigger a value change event
	IF VariableMonitorExample = 0 THEN
		VariableMonitorExample := 10.5;
	END_IF

	// Error reset
	IF NOT MpAuditTrailSys.Error THEN
		MpAuditTrailSys.ErrorReset := FALSE;
	END_IF

	// Assign MpLinks & address references
	MpAuditTrailSys.MpLink := ADR(gMpLinkAuditTrail);
	MpAuditTrailSys.DeviceName := ADR('mappAuditFiles');
	MpAuditTrailSys.FileName := ADR(HmiAudit.Parameters.FileName); 
	MpAuditTrailSys.Language := ADR('en');
	#warning "USER WRN: TODO: replace config FB"
   // MpAuditTrailConfigSys.MpLink := ADR(gMpLinkAuditTrail);
	//MpAuditTrailConfigSys.Configuration := ADR(AuditTrailConfig);
	MpAuditTrailCEvents.MpLink := ADR(gMpLinkCustomEvents);
	MpAuditTrailUISys.MpLink := ADR(gMpLinkAuditTrail);
	MpAuditTrailUISys.UIConnect := ADR(MpAuditTrailUIConnect);

	// Call function blocks
	MpAuditTrailSys();
	#warning "USER WRN: TODO: replace config FB"
	//MpAuditTrailConfigSys();
	MpAuditTrailCEvents();
	MpAuditTrailUISys();

END_PROGRAM

PROGRAM _EXIT

	// Disable the function blocks to unlink the MpLinks
	MpAuditTrailSys.Enable := FALSE;
	#warning "USER WRN: TODO: replace config FB"
	//MpAuditTrailConfigSys.Enable := FALSE;
	MpAuditTrailCEvents.Enable := FALSE;
	MpAuditTrailUISys.Enable := FALSE;

	// Call function blocks
	MpAuditTrailSys();
	#warning "USER WRN: TODO: replace config FB"
	//MpAuditTrailConfigSys();
	MpAuditTrailCEvents();
	MpAuditTrailUISys();

END_PROGRAM

