ACTION HMIActions_Init:	
	
	HmiRecipe.Status.CreateRecipeLayer.ParsStatus 	    	:= HIDE;
	HmiRecipe.Status.CreateRecipeLayer.MachConfigStatus 	:= HIDE;
	HmiRecipe.Status.DefaultRecipeLayer.Status 		    	:= HIDE;
	HmiRecipe.Status.RecipeLoadLayer.Status 		    	:= HIDE;
	HmiRecipe.Status.EditRecipeLayer.ParsStatus		    	:= HIDE;
	HmiRecipe.Status.EditRecipeLayer.MachConfigStatus   	:= HIDE;
	HmiRecipe.Status.DuplicateLayer 					    := HIDE;
	HmiRecipe.Status.CreateRecipeLayer.FileNameInputActive 	:= UNLOCK;
	
END_ACTION


ACTION LoadStatus:
	// Configure visible recipe list
	IF MpRecipeUIConnect.Recipe.List.Names[0] = '' THEN
		HmiRecipe.Status.TableConfig := '{ "specRows": [{"from":0,"to":19, "visible":false}]}';
	ELSE
		HmiRecipe.Status.TableConfig := '{ "specRows": [{"from":';
		brsitoa(MpRecipeUIConnect.Recipe.List.MaxSelection + 1, ADR(HmiRecipe.Status.TableConfig) + brsstrlen(ADR(HmiRecipe.Status.TableConfig)));
		brsstrcat(ADR(HmiRecipe.Status.TableConfig), ADR(',"to":19, "visible":false}]}'));
	END_IF

	HmiRecipe.Status.FilesAvailable := (MpRecipeUIConnect.Recipe.List.Names[0] <> '');
	HmiRecipe.Status.LoadAllowed := HmiRecipe.Status.FilesAvailable AND NOT HmiRecipe.Status.InvalidRecipe;
	HmiRecipe.Status.DeviceValid := (MpFileManagerUI_0.StatusID <> mpFILE_ERR_INVALID_FILE_DEV);

END_ACTION

ACTION LoadPreview:
	
	// Category name genarate	
	IF HmiRecipe.Parameters.CategoryIndex = PARAMETERS_CATEGORY_INDEX THEN
		MpRecipeUIConnect.Recipe.Filter := '*par';
		HmiRecipe.Parameters.Category := PARAMETERS_CATEGORY;
	ELSIF HmiRecipe.Parameters.CategoryIndex = MACH_CONFIG_CATEGORY_INDEX THEN
		MpRecipeUIConnect.Recipe.Filter := '*mcfg';
		HmiRecipe.Parameters.Category := MACHINE_CONFIGURATION_CATEGORY;
	END_IF;
	IF EDGEPOS(HmiRecipe.Parameters.CategoryIndex = PARAMETERS_CATEGORY_INDEX) OR 
		EDGEPOS(HmiRecipe.Parameters.CategoryIndex = MACH_CONFIG_CATEGORY_INDEX) THEN
		MpRecipeUIConnect.Recipe.Refresh := TRUE;
	END_IF;
	
	
	// Default recipe create Layer manager
	IF HmiRecipe.Status.CreateRecipeLayer.ParsStatus = HIDE AND HmiRecipe.Status.CreateRecipeLayer.MachConfigStatus = HIDE AND
		((HmiRecipe.Status.ParameterRecipeMissing AND HmiRecipe.Parameters.Category = PARAMETERS_CATEGORY) OR
		(HmiRecipe.Status.MachineSettingsRecipeMissing AND HmiRecipe.Parameters.Category = MACHINE_CONFIGURATION_CATEGORY)) THEN
		HmiRecipe.Status.DefaultRecipeLayer.Status := DISPLAY;
	ELSE
		HmiRecipe.Status.DefaultRecipeLayer.Status := HIDE;	
	END_IF;
	
	// Create Recipe Layer manager
	IF HmiRecipe.Parameters.Category = PARAMETERS_CATEGORY THEN
		IF HmiRecipe.Status.CreateDialogOpened THEN
			HmiRecipe.Status.CreateRecipeLayer.ParsStatus := DISPLAY;	  
		END_IF;	
		IF HmiRecipe.Status.CreateRecipeLayer.ParsStatus = DISPLAY AND
			(MpRecipeUIConnect.MessageBox.Cancel OR HmiRecipe.Commands.CreateRecipe) THEN
			HmiRecipe.Status.CreateRecipeLayer.ParsStatus := HIDE;
		END_IF;		
		
	ELSIF HmiRecipe.Parameters.Category = MACHINE_CONFIGURATION_CATEGORY THEN
		IF HmiRecipe.Status.CreateDialogOpened THEN
			HmiRecipe.Status.CreateRecipeLayer.MachConfigStatus := DISPLAY;	  
		END_IF;	
		IF HmiRecipe.Status.CreateRecipeLayer.MachConfigStatus = DISPLAY AND
			(MpRecipeUIConnect.MessageBox.Cancel OR HmiRecipe.Commands.CreateRecipe) THEN
			HmiRecipe.Status.CreateRecipeLayer.MachConfigStatus := HIDE;
		END_IF;
	END_IF;
	
	// Lock File name input in create layer
	IF HmiRecipe.Status.CreateRecipeLayer.ParsStatus = DISPLAY AND
		HmiRecipe.Status.ParameterRecipeMissing THEN		
		HmiRecipe.Status.CreateRecipeLayer.FileNameInputActive 	:= LOCK;		
	ELSIF HmiRecipe.Status.CreateRecipeLayer.MachConfigStatus = DISPLAY AND
		HmiRecipe.Status.MachineSettingsRecipeMissing THEN	  
		HmiRecipe.Status.CreateRecipeLayer.FileNameInputActive 	:= LOCK;
	ELSE		
		HmiRecipe.Status.CreateRecipeLayer.FileNameInputActive 	:= UNLOCK;
	END_IF;
	
	// File Duplicate manager
	IF HmiRecipe.Commands.CreateRecipe AND
		HmiRecipe.Status.FileDuplicate AND
		HmiRecipe.Status.DuplicateLayer = HIDE THEN
	  
		HmiRecipe.Commands.CreateRecipe := FALSE;
		HmiRecipe.Status.DuplicateLayer := DISPLAY;
		
	ELSIF HmiRecipe.Commands.CreateRecipe THEN		
		HmiRecipe.Status.DuplicateLayer := HIDE;
	END_IF;
	
	// Preview Recipe Layer manager
	IF HmiRecipe.Parameters.Category = MACHINE_CONFIGURATION_CATEGORY THEN
		HmiRecipe.Status.PreviewRecipeLayer.ParsStatus 		 := HIDE;
		HmiRecipe.Status.PreviewRecipeLayer.MachConfigStatus := DISPLAY;
		
	ELSIF HmiRecipe.Parameters.Category = PARAMETERS_CATEGORY THEN
		HmiRecipe.Status.PreviewRecipeLayer.MachConfigStatus := HIDE;
		HmiRecipe.Status.PreviewRecipeLayer.ParsStatus 		 := DISPLAY;	  
	END_IF;
	
	// Active Recipe declare	
	IF HmiRecipe.Parameters.Category = PARAMETERS_CATEGORY THEN	
		HmiRecipe.Status.ActiveRecipe := HmiRecipe.Status.LastLoadedProductRecipe;
		
	ELSIF HmiRecipe.Parameters.Category = MACHINE_CONFIGURATION_CATEGORY THEN		
		HmiRecipe.Status.ActiveRecipe := HmiRecipe.Status.LastLoadedConfigRecipe;
	END_IF;
	
	// Recipe Edit manager
	IF HmiRecipe.Status.EditRecipeLayer.Save THEN
		HmiRecipe.Status.EditRecipeLayer.Save			  := FALSE;		
		HmiRecipe.Status.EditRecipeLayer.ParsStatus		  := HIDE;
		HmiRecipe.Status.EditRecipeLayer.MachConfigStatus := HIDE;
		
		HmiRecipe.Commands.SaveSelectedRecipe := TRUE;
		HmiRecipe.Commands.LoadRecipe 		  := TRUE;
	END_IF;
	
	// Load preview when a recipe is selected
	IF (MpRecipeUIConnect.Recipe.List.SelectedIndex <> HmiRecipe.Status.LastSelectedIndex) OR (HmiRecipe.Status.LastMaxSelection <> MpRecipeUIConnect.Recipe.List.MaxSelection) THEN
		// Check selected recipe name is not empty
		IF (brsstrlen(ADR(MpRecipeUIConnect.Recipe.List.Names[MpRecipeUIConnect.Recipe.List.SelectedIndex])) > 0) THEN
			MpRecipe_0.FileName := ADR(MpRecipeUIConnect.Recipe.List.Names[MpRecipeUIConnect.Recipe.List.SelectedIndex]);
			MpRecipe_0.Category := ADR(HmiRecipe.Parameters.Category);
			MpRecipe_0.Load := TRUE;
			HmiRecipe.Status.LastSelectedIndex := MpRecipeUIConnect.Recipe.List.SelectedIndex;
			HmiRecipe.Status.LastMaxSelection := MpRecipeUIConnect.Recipe.List.MaxSelection;
			HmiRecipe.Status.InvalidRecipe := FALSE;
		END_IF
	END_IF

	// Reset load command on MpRecipe_0 FUB
	IF MpRecipe_0.StatusID <> 0 THEN
		HmiRecipe.Status.InvalidRecipe := TRUE;
		HmiRecipe.Commands.ResetPreview := TRUE;
	END_IF;

	IF ((MpRecipe_0.CommandDone = TRUE) OR (MpRecipe_0.Error = TRUE)) THEN
		MpRecipe_0.Load := FALSE;
	END_IF

END_ACTION

ACTION RecipeHMIcommands:

	CASE HmiRecipe.Status.HMIcommand OF
		REC_HMI_WAIT:
			// The following commands are triggered directly from the HMI. If you imported the mapp View front end of
			// the Framework, then this is already taken care of. If you did not, then your visualization must
			// trigger each one of these command variables (CreateRecipe, SaveSelectedRecipe, LoadRecipe).
			IF (MpRecipeUIConnect.Status <> mpRECIPE_UI_STATUS_IDLE) THEN
				// MpRecipe is active so don't issue a new command
			ELSIF HmiRecipe.Commands.CreateRecipe THEN
				HmiRecipe.Status.HMIcommand := REC_HMI_CREATE;
				HmiRecipe.Commands.CreateRecipe := FALSE;
			ELSIF HmiRecipe.Commands.SaveSelectedRecipe THEN
				HmiRecipe.Status.HMIcommand := REC_HMI_SAVE;
				HmiRecipe.Commands.SaveSelectedRecipe := FALSE;
			ELSIF HmiRecipe.Commands.LoadRecipe THEN
				HmiRecipe.Status.HMIcommand := REC_HMI_LOAD;
				HmiRecipe.Status.RecipeLoadLayer.Status := HIDE;
				HmiRecipe.Commands.LoadRecipe := FALSE;
				IF (brsstrcmp(ADR(HmiRecipe.Parameters.Category), ADR(PARAMETERS_RECIPE)) = 0) THEN
					HmiRecipe.Status.ProductRecipeLoaded := FALSE;
				ELSE
					HmiRecipe.Status.ConfigRecipeLoaded := FALSE;
				END_IF
			ELSIF HmiRecipe.Commands.ResetPreview THEN
				HmiRecipe.Status.HMIcommand := REC_HMI_RESET_PREVIEW;
				HmiRecipe.Commands.ResetPreview := FALSE;
			END_IF

		REC_HMI_CREATE:
			IF (brsstrcmp(ADR(HmiRecipe.Parameters.Category), ADR(PARAMETERS_RECIPE)) = 0) THEN
				ParametersPreview := ParametersEdit;
				brsstrcpy(ADR(MpRecipeUIConnect.New.FileName), ADR(HmiRecipe.Parameters.FileName));
				brsstrcat(ADR(MpRecipeUIConnect.New.FileName), ADR('.par'));
				// If the default recipe was initially missing and just now created, immediately load it
				IF HmiRecipe.Status.ParameterRecipeMissing THEN
					HmiRecipe.Commands.LoadRecipe := TRUE;
				END_IF
			ELSIF (brsstrcmp(ADR(HmiRecipe.Parameters.Category), ADR(MACHINE_CONFIGURATION_RECIPE)) = 0) THEN
				MachineSettingsPreview := MachineSettingsEdit;
				brsstrcpy(ADR(MpRecipeUIConnect.New.FileName), ADR(HmiRecipe.Parameters.FileName));
				brsstrcat(ADR(MpRecipeUIConnect.New.FileName), ADR('.mcfg'));
				// If the default recipe was initially missing and just now created, immediately load it
				IF HmiRecipe.Status.MachineSettingsRecipeMissing THEN
					HmiRecipe.Commands.LoadRecipe := TRUE;
				END_IF
			END_IF

			Header.Name := MpRecipeUIConnect.New.FileName;
			DTGetTime_0.enable := TRUE;
			REPEAT
				DTGetTime_0();
				UNTIL (DTGetTime_0.status = 0)
			END_REPEAT;
			Header.DateTime := DTGetTime_0.DT1;
			DTGetTime_0.enable := FALSE;
			DTGetTime_0();
			MpRecipeUIConnect.New.Create := TRUE;

			HmiRecipe.Status.HMIcommand := REC_HMI_WAIT;

		REC_HMI_LOAD:
			IF (MpRecipeUIConnect.Status = mpRECIPE_UI_STATUS_IDLE) THEN
				IF (brsstrcmp(ADR(HmiRecipe.Parameters.Category), ADR(PARAMETERS_RECIPE)) = 0) THEN
					Parameters := ParametersPreview;
					HmiRecipe.Status.ProductRecipeLoaded := TRUE;
					// If the default recipe was initially missing and just now created, then it is the last loaded recipe
					IF HmiRecipe.Status.ParameterRecipeMissing THEN
						HmiRecipe.Status.LastLoadedProductRecipe := DEFAULT_PARAMETERS;
						brsstrcat(ADR(HmiRecipe.Status.LastLoadedProductRecipe), ADR(PARAMETERS_FILE_EXTENSION));
						HmiRecipe.Status.ParameterRecipeMissing := FALSE;
						// Otherwise, the last loaded recipe is the selected recipe
					ELSE
						HmiRecipe.Status.LastLoadedProductRecipe := MpRecipeUIConnect.Recipe.List.Names[MpRecipeUIConnect.Recipe.List.SelectedIndex];
					END_IF
				ELSIF (brsstrcmp(ADR(HmiRecipe.Parameters.Category), ADR(MACHINE_CONFIGURATION_RECIPE)) = 0) THEN
					MachineSettings := MachineSettingsPreview;
					HmiRecipe.Status.ConfigRecipeLoaded := TRUE;
					// If the default recipe was initially missing and just now created, then it is the last loaded recipe
					IF HmiRecipe.Status.MachineSettingsRecipeMissing THEN
						HmiRecipe.Status.LastLoadedConfigRecipe := DEFAULT_MACHINE_CONFIGURATION;
						brsstrcat(ADR(HmiRecipe.Status.LastLoadedConfigRecipe), ADR(MACHINE_CONFIG_FILE_EXTENSION));
						HmiRecipe.Status.MachineSettingsRecipeMissing := FALSE;
						// Otherwise, the last loaded recipe is the selected recipe
					ELSE
						HmiRecipe.Status.LastLoadedConfigRecipe := MpRecipeUIConnect.Recipe.List.Names[MpRecipeUIConnect.Recipe.List.SelectedIndex];
					END_IF
				END_IF
				HmiRecipe.Status.HMIcommand := REC_HMI_WAIT;
			END_IF

		REC_HMI_SAVE:
			IF (MpRecipeUIConnect.Status = mpRECIPE_UI_STATUS_IDLE) THEN

				IF (brsstrcmp(ADR(HmiRecipe.Parameters.Category), ADR(PARAMETERS_RECIPE)) = 0) THEN
					ParametersPreview := ParametersEdit;
				ELSIF (brsstrcmp(ADR(HmiRecipe.Parameters.Category), ADR(MACHINE_CONFIGURATION_RECIPE)) = 0) THEN
					MachineSettingsPreview := MachineSettingsEdit;
				END_IF

				IF (brsstrlen(ADR(HmiRecipe.Status.SelectedRecipe)) > 0) THEN
					MpRecipe_0.FileName := ADR(HmiRecipe.Status.SelectedRecipe);
					MpRecipe_0.Save := TRUE;
				END_IF

				HmiRecipe.Status.HMIcommand := REC_HMI_WAIT;
			END_IF

		REC_HMI_RESET_PREVIEW:
			IF (brsstrcmp(ADR(HmiRecipe.Parameters.Category), ADR(PARAMETERS_RECIPE)) = 0) THEN
				brsmemset(ADR(ParametersPreview), 0, SIZEOF(ParametersPreview));
			ELSIF (brsstrcmp(ADR(HmiRecipe.Parameters.Category), ADR(MACHINE_CONFIGURATION_RECIPE)) = 0) THEN
				brsmemset(ADR(MachineSettingsPreview), 0, SIZEOF(MachineSettingsPreview));
			END_IF
			HmiRecipe.Status.HMIcommand := REC_HMI_WAIT;

	END_CASE

	// If the Edit or Create dialog boxes open, copy the Preview structure into the Edit structure.
	IF HmiRecipe.Status.EditDialogOpened OR HmiRecipe.Status.CreateDialogOpened THEN
		IF (brsstrcmp(ADR(HmiRecipe.Parameters.Category), ADR(PARAMETERS_RECIPE)) = 0) THEN
			ParametersEdit := ParametersPreview;
			IF HmiRecipe.Status.ParameterRecipeMissing THEN
				HmiRecipe.Parameters.FileName := DEFAULT_PARAMETERS;
			ELSE
				HmiRecipe.Parameters.FileName:= 'newParameters';
			END_IF
			
			// Open parameter dialog
			IF HmiRecipe.Status.EditDialogOpened THEN
				HmiRecipe.Status.EditRecipeLayer.ParsStatus := DISPLAY;				
			ELSIF HmiRecipe.Status.CreateDialogOpened THEN
			END_IF;
			
		ELSIF (brsstrcmp(ADR(HmiRecipe.Parameters.Category), ADR(MACHINE_CONFIGURATION_RECIPE)) = 0) THEN
			MachineSettingsEdit := MachineSettingsPreview;
			IF HmiRecipe.Status.MachineSettingsRecipeMissing THEN
				HmiRecipe.Parameters.FileName := DEFAULT_MACHINE_CONFIGURATION;
			ELSE
				HmiRecipe.Parameters.FileName := 'newMachineConfig';
			END_IF
			
			// Open machine dialog
			IF HmiRecipe.Status.EditDialogOpened THEN
				HmiRecipe.Status.EditRecipeLayer.MachConfigStatus := DISPLAY;
			ELSIF HmiRecipe.Status.CreateDialogOpened THEN
			END_IF;
			
		END_IF
			
		HmiRecipe.Status.EditDialogOpened := FALSE;
		HmiRecipe.Status.CreateDialogOpened := FALSE;
	END_IF

	// Check if the file name has already been used
	HmiRecipe.Status.FileDuplicate := FALSE;
	FOR i:=0 TO ((SIZEOF(MpRecipeUIConnect.Recipe.List.Names) / SIZEOF(MpRecipeUIConnect.Recipe.List.Names[0])) - 1) DO
		temp := HmiRecipe.Parameters.FileName;
		IF (brsstrcmp(ADR(HmiRecipe.Parameters.Category), ADR(PARAMETERS_RECIPE)) = 0) THEN
			brsstrcat(ADR(temp),ADR(PARAMETERS_FILE_EXTENSION));
		ELSIF (brsstrcmp(ADR(HmiRecipe.Parameters.Category), ADR(MACHINE_CONFIGURATION_RECIPE)) = 0) THEN
			brsstrcat(ADR(temp),ADR(MACHINE_CONFIG_FILE_EXTENSION));
		END_IF
		IF temp = MpRecipeUIConnect.Recipe.List.Names[i] THEN
			HmiRecipe.Status.FileDuplicate := TRUE;
		END_IF
	END_FOR

	// Update status information
	HmiRecipe.Status.LastStatus := MpRecipeUIConnect.Status;
	HmiRecipe.Status.SelectedRecipe := MpRecipeUIConnect.Recipe.List.Names[MpRecipeUIConnect.Recipe.List.SelectedIndex];

END_ACTION