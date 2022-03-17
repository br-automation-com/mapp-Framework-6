
TYPE
	AxisSettingsType : {REDUND_UNREPLICABLE} 	STRUCT 
		AxisFeatures : {REDUND_UNREPLICABLE} ARRAY[0..2]OF STRING[255];
		DriveConfiguration : {REDUND_UNREPLICABLE} McCfgPureVAxType;
		BaseConfiguration : {REDUND_UNREPLICABLE} McCfgAxType;
	END_STRUCT;
	AxisMachineSettingsType : {REDUND_UNREPLICABLE} 	STRUCT 
		ReferencePosition : {REDUND_UNREPLICABLE} LREAL := 0; (*[mm] Axis position after reference*)
	END_STRUCT;
	AxisControlCommandType : {REDUND_UNREPLICABLE} 	STRUCT 
		UpdatePreviewParameters : {REDUND_UNREPLICABLE} BOOL;
		LoadRecipeParameters : {REDUND_UNREPLICABLE} BOOL;
		SaveRecipeParameters : {REDUND_UNREPLICABLE} BOOL;
		Power : {REDUND_UNREPLICABLE} BOOL;
		Reference : {REDUND_UNREPLICABLE} BOOL;
		MoveAbsolute : {REDUND_UNREPLICABLE} BOOL;
		MoveAdditive : {REDUND_UNREPLICABLE} BOOL;
		MoveToStart : {REDUND_UNREPLICABLE} BOOL;
		Abort : {REDUND_UNREPLICABLE} BOOL;
		Stop : {REDUND_UNREPLICABLE} BOOL;
		Reset : {REDUND_UNREPLICABLE} BOOL;
		JogPositive : {REDUND_UNREPLICABLE} BOOL;
		JogNegative : {REDUND_UNREPLICABLE} BOOL;
		Start : {REDUND_UNREPLICABLE} BOOL;
	END_STRUCT;
	AxisControlParametersType : {REDUND_UNREPLICABLE} 	STRUCT 
		HomePosition : {REDUND_UNREPLICABLE} LREAL := 0;
		Position : {REDUND_UNREPLICABLE} LREAL := 0;
		Distance : {REDUND_UNREPLICABLE} LREAL := 180;
		Velocity : {REDUND_UNREPLICABLE} REAL := 360;
		Acceleration : {REDUND_UNREPLICABLE} REAL := 360;
		Deceleration : {REDUND_UNREPLICABLE} REAL := 360;
		JogVelocity : {REDUND_UNREPLICABLE} REAL := 100;
		StopDeceleration : {REDUND_UNREPLICABLE} REAL := 720; (*[mm/s2] Deceleration for stopping*)
		ProductNumber : {REDUND_UNREPLICABLE} INT := 0; (*Product Number*)
		ProductLength : {REDUND_UNREPLICABLE} REAL := 70; (*Real Product Length*)
	END_STRUCT;
	AxisControlStatusType : {REDUND_UNREPLICABLE} 	STRUCT 
		TaskName : {REDUND_UNREPLICABLE} STRING[80];
		MachineSettingsName : {REDUND_UNREPLICABLE} STRING[255];
		ProductSettingsName : {REDUND_UNREPLICABLE} STRING[255];
		ProductPreviewSettingsName : {REDUND_UNREPLICABLE} STRING[255];
		Status : {REDUND_UNREPLICABLE} STRING[80]; (*Machine Status*)
		IsReady : {REDUND_UNREPLICABLE} BOOL;
		ErrorActive : {REDUND_UNREPLICABLE} BOOL;
		Busy : {REDUND_UNREPLICABLE} BOOL;
		ReferenceRequired : {REDUND_UNREPLICABLE} BOOL;
		Position : {REDUND_UNREPLICABLE} LREAL;
		Velocity : {REDUND_UNREPLICABLE} REAL;
		Current : {REDUND_UNREPLICABLE} REAL;
		LagError : {REDUND_UNREPLICABLE} LREAL;
		MotorTemperature : {REDUND_UNREPLICABLE} REAL;
		IsHomed : {REDUND_UNREPLICABLE} BOOL;
		IsPowered : {REDUND_UNREPLICABLE} BOOL;
	END_STRUCT;
	AxisControlType : {REDUND_UNREPLICABLE} 	STRUCT 
		Command : {REDUND_UNREPLICABLE} AxisControlCommandType;
		Parameters : {REDUND_UNREPLICABLE} AxisControlParametersType;
		Status : {REDUND_UNREPLICABLE} AxisControlStatusType;
	END_STRUCT;
	StateEnum : 
		(
		STATE_INIT,
		STATE_POWER_ON,
		STATE_HOME,
		STATE_REFERENCE,
		STATE_MOVE_TO_HOME_POSITION,
		STATE_READY,
		STATE_MANUAL_OPERATION,
		STATE_AUTOMATIC_OPERATION,
		STATE_STOPPING,
		STATE_STOPPED,
		STATE_ABORTING,
		STATE_ABORTED,
		STATE_CLEARING,
		STATE_RESETTING
		);
	ConfigurationStateEnum : 
		(
		CONFIG_STATE_INIT,
		CONFIG_STATE_READ,
		CONFIG_STATE_WRITE,
		CONFIG_STATE_READY
		);
	AutomaticStateEnum : 
		(
		AUTOMATIC_STATE_IDLE,
		AUTOMATIC_STATE_RUNNING
		);
	ManualStateEnum : 
		(
		MANUAL_STATE_IDLE,
		MANUAL_STATE_JOG,
		MANUAL_STATE_MOVE,
		MANUAL_STATE_STOPPING
		);
	AxisRecipeType : 	STRUCT 
		EditDialogOpened : BOOL;
		CreateDialogOpened : BOOL;
		SaveRecipe : BOOL;
		LoadRecipe : BOOL;
		CreateRecipe : BOOL;
		State : AxisRecipeStep_enum;
		CategoryDropdown : STRING[50];
	END_STRUCT;
	AxisRecipeStep_enum : 
		(
		REC_AXIS_WAIT,
		REC_AXIS_LOAD,
		REC_AXIS_SAVE,
		REC_AXIS_CREATE,
		REC_AXIS_STORE_MACH_SETTINGS,
		REC_AXIS_FACTORY_RESET
		);
END_TYPE
