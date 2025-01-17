/* Automation Studio generated header file */
/* Do not edit ! */
/* MpAlarmX 6.0.7003 */

#ifndef _MPALARMX_
#define _MPALARMX_
#ifdef __cplusplus
extern "C" 
{
#endif
#ifndef _MpAlarmX_VERSION
#define _MpAlarmX_VERSION 6.0.7003
#endif

#include <bur/plctypes.h>

#ifndef _BUR_PUBLIC
#define _BUR_PUBLIC
#endif
#ifdef _SG3
		#include "MpBase.h"
		#include "astime.h"
#endif

#ifdef _SG4
		#include "MpBase.h"
		#include "astime.h"
#endif

#ifdef _SGC
		#include "MpBase.h"
		#include "astime.h"
#endif



/* Datatypes and datatypes of function blocks */
typedef enum MpAlarmXListUIStatusEnum
{	mpALARMX_LIST_UI_STATUS_IDLE = 0,
	mpALARMX_LIST_UI_STATUS_BUSY = 1,
	mpALARMX_LIST_UI_STATUS_WARNING = 98,
	mpALARMX_LIST_UI_STATUS_ERROR = 99
} MpAlarmXListUIStatusEnum;

typedef enum MpAlarmXStateEnum
{	mpALARMX_STATE_NONE = 0,
	mpALARMX_STATE_ACTIVE = 1,
	mpALARMX_STATE_INACTIVE = 2,
	mpALARMX_STATE_ACKNOWLEDGED = 3,
	mpALARMX_STATE_UNACKNOWLEDGED = 4,
	mpALARMX_STATE_CONFIRMED = 5,
	mpALARMX_STATE_UNCONFIRMED = 6
} MpAlarmXStateEnum;

typedef enum MpAlarmXAcknowledgeConfigEnum
{	mpALARMX_ACK_DISABLED = 0,
	mpALARMX_ACK_REQ = 1,
	mpALARMX_ACK_REQ_RESETTABLE = 2
} MpAlarmXAcknowledgeConfigEnum;

typedef enum MpAlarmXConfirmConfigEnum
{	mpALARMX_CONFIRM_DISABLED = 0,
	mpALARMX_CONFIRM_REQ = 1,
	mpALARMX_CONFIRM_AFTER_RESET = 3,
	mpALARMX_CONFIRM_REQ_RESETTABLE = 3
} MpAlarmXConfirmConfigEnum;

typedef enum MpAlarmXHistoryUIStatusEnum
{	mpALARMX_HISTORY_UI_STATUS_IDLE = 0,
	mpALARMX_HISTORY_UI_STATUS_BUSY = 1,
	mpALARMX_HISTORY_UI_STATUS_ERROR = 99
} MpAlarmXHistoryUIStatusEnum;

typedef enum MpAlarmXQueryModeEnum
{	mpALARMX_QUERY_MODE_ALL = 0,
	mpALARMX_QUERY_MODE_NEW = 1
} MpAlarmXQueryModeEnum;

typedef enum MpAlarmXMeasurementSystemEnum
{	mpALARMX_ENGINEERING_UNITS = 0,
	mpALARMX_METRIC = 1,
	mpALARMX_IMPERIAL = 2,
	mpALARMX_IMPERIAL_US = 3
} MpAlarmXMeasurementSystemEnum;

typedef enum MpAlarmXErrorEnum
{	mpALARMX_NO_ERROR = 0,
	mpALARMX_ERR_ACTIVATION = -1064239103,
	mpALARMX_ERR_MPLINK_NULL = -1064239102,
	mpALARMX_ERR_MPLINK_INVALID = -1064239101,
	mpALARMX_ERR_MPLINK_CHANGED = -1064239100,
	mpALARMX_ERR_MPLINK_CORRUPT = -1064239099,
	mpALARMX_ERR_MPLINK_IN_USE = -1064239098,
	mpALARMX_ERR_CONFIG_NULL = -1064239096,
	mpALARMX_ERR_CONFIG_NO_PV = -1064239095,
	mpALARMX_ERR_CONFIG_INVALID = -1064239091,
	mpALARMX_ERR_NAME_NULL = -1064116224,
	mpALARMX_ERR_NAME_EMPTY = -1064116223,
	mpALARMX_WRN_MISSING_UICONNECT = -2137858045,
	mpALARMX_ERR_ALARM_NOT_ACTIVE = -1064116220,
	mpALARMX_ERR_ALARM_NOT_SELECTED = -1064116219,
	mpALARMX_ERR_ACK_NOT_ALLOWED = -1064116218,
	mpALARMX_ERR_INVALID_FILE_DEV = -1064116217,
	mpALARMX_ERR_INVALID_FILE_NAME = -1064116216,
	mpALARMX_ERR_CORE_INST_EXISTS = -1064116215,
	mpALARMX_ERR_MEMORY_INIT = -1064116214,
	mpALARMX_ERR_WRITE_EXPORT_FILE = -1064116213,
	mpALARMX_ERR_NAME_NOT_FOUND = -1064116212,
	mpALARMX_ERR_QUERY_NOT_FOUND = -1064116211,
	mpALARMX_INF_QUERY_NO_DATA = 1083367438,
	mpALARMX_WRN_QUERY_INCONSISTENT = -2137858033
} MpAlarmXErrorEnum;

typedef enum MpAlarmXCfgEnum
{	mpALARMX_CFG_ALARMS = 140,
	mpALARMX_CFG_HISTORY = 120,
	mpALARMX_CFG_SNIPPET = 142,
	mpALARMX_CFG_ALARM = 141,
	mpALARMX_CFG_QUERY = 181,
	mpALARMX_CFG_CATEGORY = 161,
	mpALARMX_CFG_DEFAULTACTION = 102,
	mpALARMX_CFG_QUERIES = 180,
	mpALARMX_CFG_CATEGORIES = 160,
	mpALARMX_CFG_MAPPING = 101,
	mpALARMX_CFG_CORE = 100,
	mpALARMX_CFG_CATEGORYLINK = 104,
	mpALARMX_CFG_ALARMLINK = 103
} MpAlarmXCfgEnum;

typedef enum MpAlarmXCfgCategoryDefinedByEnum
{	mpALARMX_CFG_CATEGORY_SEVERITY = 0,
	mpALARMX_CFG_CATEGORY_CODE = 1
} MpAlarmXCfgCategoryDefinedByEnum;

typedef enum MpAlarmXCfgCoreMappingActionEnum
{	mpALARMX_CFG_CORE_NONE = 0,
	mpALARMX_CFG_CORE_REACTION = 1,
	mpALARMX_CFG_CORE_ESCALATE_ALARM = 2,
	mpALARMX_CFG_CORE_ESC_REACTION = 3,
	mpALARMX_CFG_CORE_AGGREGATEESC = 4,
	mpALARMX_CFG_CORE_AGGREGATE = 5,
	mpALARMX_CFG_CORE_REMAIN = 6
} MpAlarmXCfgCoreMappingActionEnum;

typedef enum MpAlarmXCfgCoreTaskClassEnum
{	mpALARMX_CFG_CORE_TC_CYCLIC_1 = 1,
	mpALARMX_CFG_CORE_TC_CYCLIC_2 = 2,
	mpALARMX_CFG_CORE_TC_CYCLIC_3 = 3,
	mpALARMX_CFG_CORE_TC_CYCLIC_4 = 4,
	mpALARMX_CFG_CORE_TC_CYCLIC_5 = 5,
	mpALARMX_CFG_CORE_TC_CYCLIC_6 = 6,
	mpALARMX_CFG_CORE_TC_CYCLIC_7 = 7,
	mpALARMX_CFG_CORE_TC_CYCLIC_8 = 8
} MpAlarmXCfgCoreTaskClassEnum;

typedef enum MpAlarmXCfgCoreUncfgAlarmsEnum
{	mpALARMX_CFG_CORE_DISABLED = 0,
	mpALARMX_CFG_CORE_ENABLED = 1
} MpAlarmXCfgCoreUncfgAlarmsEnum;

typedef enum MpAlarmXCfgCoreMemoryEnum
{	mpALARMX_CFG_CORE_MEM_DISABLED = 0,
	mpALARMX_CFG_CORE_ROM_DRAM = 1,
	mpALARMX_CFG_CORE_ROM_RAM = 2,
	mpALARMX_CFG_CORE_RAM = 3
} MpAlarmXCfgCoreMemoryEnum;

typedef enum MpAlarmXCfgHistoryMemoryEnum
{	mpALARMX_CFG_HISTORY_ROM_DRAM = 0,
	mpALARMX_CFG_HISTORY_ROM_RAM = 1,
	mpALARMX_CFG_HISTORY_RAM = 2
} MpAlarmXCfgHistoryMemoryEnum;

typedef enum MpAlarmXCfgHistoryScopeEnum
{	mpALARMX_CFG_HISTORY_COMPONENT = 0,
	mpALARMX_CFG_HISTORY_BRANCH = 1
} MpAlarmXCfgHistoryScopeEnum;

typedef enum MpAlarmXCfgListLimitSelectorEnum
{	mpALARMX_CFG_LIST_LIMIT_DISABLED = 0,
	mpALARMX_CFG_LIST_LIMIT_STATIC = 1,
	mpALARMX_CFG_LIST_LIMIT_DYNAMIC = 2
} MpAlarmXCfgListLimitSelectorEnum;

typedef enum MpAlarmXCfgListLimitSeleRateEnum
{	mpALARMX_CFG_LIST_RATE_DISABLED = 0,
	mpALARMX_CFG_LIST_RATE_STATIC = 1,
	mpALARMX_CFG_LIST_RATE_DYNAMIC = 2
} MpAlarmXCfgListLimitSeleRateEnum;

typedef enum MpAlarmXCfgListAckValueListEnum
{	mpALARMX_CFG_LIST_ACK_DISABLED = 0,
	mpALARMX_CFG_LIST_ACK_REQ = 1,
	mpALARMX_CFG_LIST_ACK_REQ_AND_RE = 3
} MpAlarmXCfgListAckValueListEnum;

typedef enum MpAlarmXCfgListConfValueListEnum
{	mpALARMX_CFG_LIST_CFM_DISABLED = 0,
	mpALARMX_CFG_LIST_CFM_REQUIRED = 1,
	mpALARMX_CFG_LIST_CFM_REQ_AFT_RE = 2,
	mpALARMX_CFG_LIST_CFM_REQ_AND_RE = 3
} MpAlarmXCfgListConfValueListEnum;

typedef enum MpAlarmXCfgListSettingsEnum
{	mpALARMX_CFG_LIST_STATIC = 0,
	mpALARMX_CFG_LIST_DYNAMIC = 1
} MpAlarmXCfgListSettingsEnum;

typedef enum MpAlarmXCfgListBehaviorEnum
{	mpALARMX_CFG_LIST_EDGE = 0,
	mpALARMX_CFG_LIST_PERSISTENT = 1,
	mpALARMX_CFG_LIST_USER_DEFINED = 2,
	mpALARMX_CFG_LIST_LEVEL_MONITOR = 3,
	mpALARMX_CFG_LIST_DEVIAT_MONITOR = 4,
	mpALARMX_CFG_LIST_ROC_MONITOR = 5,
	mpALARMX_CFG_LIST_DISCRETE_MON = 6
} MpAlarmXCfgListBehaviorEnum;

typedef enum MpAlarmXCfgListAutoDetectEnum
{	mpALARMX_CFG_LIST_DISABLED = 0,
	mpALARMX_CFG_LIST_ENABLED = 1
} MpAlarmXCfgListAutoDetectEnum;

typedef enum MpAlarmXCfgListValueEnum
{	mpALARMX_CFG_LIST_SNIPPET_PV = 0
} MpAlarmXCfgListValueEnum;

typedef enum MpAlarmXCfgQueryColumnsEnum
{	mpALARMX_CFG_QUERY_NAME = 0,
	mpALARMX_CFG_QUERY_MESSAGE = 1,
	mpALARMX_CFG_QUERY_INSTANCEID = 2,
	mpALARMX_CFG_QUERY_CODE = 3,
	mpALARMX_CFG_QUERY_SEVERITY = 4,
	mpALARMX_CFG_QUERY_SCOPE = 5,
	mpALARMX_CFG_QUERY_STATECHANGE = 6,
	mpALARMX_CFG_QUERY_TIMESTAMP = 7,
	mpALARMX_CFG_QUERY_ADDINFO1 = 8,
	mpALARMX_CFG_QUERY_ADDINFO2 = 9
} MpAlarmXCfgQueryColumnsEnum;

typedef enum MpAlarmXCfgQueryOperatorsEnum
{	mpALARMX_CFG_QUERY_LT = 0,
	mpALARMX_CFG_QUERY_LE = 0,
	mpALARMX_CFG_QUERY_GT = 0,
	mpALARMX_CFG_QUERY_GE = 0,
	mpALARMX_CFG_QUERY_EQ = 0,
	mpALARMX_CFG_QUERY_NE = 0,
	mpALARMX_CFG_QUERY_LIKE = 0
} MpAlarmXCfgQueryOperatorsEnum;

typedef enum MpAlarmXCfgQueryPendColumnsEnum
{	mpALARMX_CFG_QUERY_PEND_NAME = 0,
	mpALARMX_CFG_QUERY_PEND_MESSAGE = 1,
	mpALARMX_CFG_QUERY_PEND_INST_ID = 2,
	mpALARMX_CFG_QUERY_PEND_CODE = 3,
	mpALARMX_CFG_QUERY_PEND_SEVERITY = 4,
	mpALARMX_CFG_QUERY_PEND_SCOPE = 5,
	mpALARMX_CFG_QUERY_PEND_STATEACT = 6,
	mpALARMX_CFG_QUERY_PEND_STATEACK = 7,
	mpALARMX_CFG_QUERY_PEND_STATECMF = 8,
	mpALARMX_CFG_QUERY_PEND_TIME = 9,
	mpALARMX_CFG_QUERY_PEND_TIME_ACK = 10,
	mpALARMX_CFG_QUERY_PEND_ADDINFO1 = 11,
	mpALARMX_CFG_QUERY_PEND_ADDINFO2 = 12
} MpAlarmXCfgQueryPendColumnsEnum;

typedef enum MpAlarmXCfgQueryConfColumnsEnum
{	mpALARMX_CFG_QUERY_CONF_NAME = 0,
	mpALARMX_CFG_QUERY_CONF_MESSAGE = 1,
	mpALARMX_CFG_QUERY_CONF_CODE = 2,
	mpALARMX_CFG_QUERY_CONF_SEVERITY = 3,
	mpALARMX_CFG_QUERY_CONF_ADDINFO1 = 4,
	mpALARMX_CFG_QUERY_CONF_ADDINFO2 = 5
} MpAlarmXCfgQueryConfColumnsEnum;

typedef enum MpAlarmXCfgQueryUpdateModeEnum
{	mpALARMX_CFG_QUERY_ON_CHANGE = 0,
	mpALARMX_CFG_QUERY_ON_NEWREMOVED = 1
} MpAlarmXCfgQueryUpdateModeEnum;

typedef enum MpAlarmXCfgQueryCompareToEnum
{	mpALARMX_CFG_QUERY_VALUE = 0,
	mpALARMX_CFG_QUERY_PV = 1
} MpAlarmXCfgQueryCompareToEnum;

typedef enum MpAlarmXCfgQuerySourceEnum
{	mpALARMX_CFG_QUERY_PENDING = 0,
	mpALARMX_CFG_QUERY_CONFIGURED = 1,
	mpALARMX_CFG_QUERY_HISTORICAL = 2
} MpAlarmXCfgQuerySourceEnum;

typedef struct MpAlarmXStatusIDType
{	enum MpAlarmXErrorEnum ID;
	MpComSeveritiesEnum Severity;
} MpAlarmXStatusIDType;

typedef struct MpAlarmXDiagType
{	struct MpAlarmXStatusIDType StatusID;
} MpAlarmXDiagType;

typedef struct MpAlarmXHistoryUIInfoType
{	struct MpAlarmXDiagType Diag;
} MpAlarmXHistoryUIInfoType;

typedef struct MpAlarmXHistoryInfoType
{	plcstring GeneratedFileName[256];
	struct MpAlarmXDiagType Diag;
} MpAlarmXHistoryInfoType;

typedef struct MpAlarmXAlarmControlInfoType
{	struct MpAlarmXDiagType Diag;
} MpAlarmXAlarmControlInfoType;

typedef struct MpAlarmXCoreInfoType
{	struct MpAlarmXDiagType Diag;
} MpAlarmXCoreInfoType;

typedef struct MpAlarmXListUIInfoType
{	struct MpAlarmXDiagType Diag;
} MpAlarmXListUIInfoType;

typedef struct MpAlarmXQueryInfoType
{	unsigned long AvailableSpace;
	unsigned long RowsRead;
	plcbit HasMoreRows;
	struct MpAlarmXDiagType Diag;
} MpAlarmXQueryInfoType;

typedef struct MpAlarmXControlInfoType
{	struct MpAlarmXDiagType Diag;
} MpAlarmXControlInfoType;

typedef struct MpAlarmXListUIBacktraceType
{	unsigned long RecordID[10];
	plcstring LogbookName[10][101];
	signed long EventID[10];
	plcwstring Description[10][256];
} MpAlarmXListUIBacktraceType;

typedef struct MpAlarmXListUIAlarmListType
{	unsigned long Severity[50];
	unsigned long Code[50];
	plcwstring Message[50][256];
	plcwstring AdditionalInformation1[50][256];
	plcwstring AdditionalInformation2[50][256];
	unsigned long InstanceID[50];
	plcstring Scope[50][256];
	plcstring Name[50][256];
	plcbit StateActive[50];
	plcbit StateAcknowledged[50];
	plcbit StateConfirmed[50];
	plcstring Timestamp[50][51];
	unsigned short SelectedIndex;
	unsigned short MaxSelection;
	plcbit PageUp;
	plcbit PageDown;
	plcbit StepUp;
	plcbit StepDown;
	float RangeStart;
	float RangeEnd;
} MpAlarmXListUIAlarmListType;

typedef struct MpAlarmXListUIDetailsType
{	unsigned long Severity;
	unsigned long Code;
	plcwstring Message[256];
	plcwstring AdditionalInformation1[256];
	plcwstring AdditionalInformation2[256];
	unsigned long InstanceID;
	plcstring Scope[256];
	plcstring Name[256];
	plcbit StateActive;
	plcbit StateAcknowledged;
	plcbit StateConfirmed;
	plcstring Timestamp[51];
	struct MpAlarmXListUIBacktraceType Backtrace;
} MpAlarmXListUIDetailsType;

typedef struct MpAlarmXListUIConnectType
{	enum MpAlarmXListUIStatusEnum Status;
	struct MpAlarmXListUIAlarmListType AlarmList;
	plcbit Acknowledge;
	plcbit Confirm;
	plcbit AcknowledgeAll;
	struct MpAlarmXListUIDetailsType Details;
	unsigned long AcknowledgeID;
	unsigned long ConfirmID;
} MpAlarmXListUIConnectType;

typedef struct MpAlarmXListUISetupType
{	unsigned short AlarmListSize;
	unsigned char AlarmListScrollWindow;
	plcstring TimeStampPattern[51];
} MpAlarmXListUISetupType;

typedef struct MpAlarmXHistoryUIAlarmListType
{	unsigned long Severity[50];
	unsigned long Code[50];
	plcwstring Message[50][256];
	plcwstring AdditionalInformation1[50][256];
	plcwstring AdditionalInformation2[50][256];
	plcstring Scope[50][256];
	plcstring Name[50][256];
	enum MpAlarmXStateEnum OldState[50];
	enum MpAlarmXStateEnum NewState[50];
	plcstring Timestamp[50][51];
	unsigned short SelectedIndex;
	unsigned short MaxSelection;
	plcbit PageUp;
	plcbit PageDown;
	plcbit StepUp;
	plcbit StepDown;
	float RangeStart;
	float RangeEnd;
} MpAlarmXHistoryUIAlarmListType;

typedef struct MpAlarmXHistoryUIDetailsType
{	unsigned long Severity;
	unsigned long Code;
	plcwstring Message[256];
	plcwstring AdditionalInformation1[256];
	plcwstring AdditionalInformation2[256];
	plcstring Scope[256];
	plcstring Name[256];
	enum MpAlarmXStateEnum OldState;
	enum MpAlarmXStateEnum NewState;
	plcstring Timestamp[51];
} MpAlarmXHistoryUIDetailsType;

typedef struct MpAlarmXHistoryUIConnectType
{	enum MpAlarmXHistoryUIStatusEnum Status;
	struct MpAlarmXHistoryUIAlarmListType AlarmList;
	struct MpAlarmXHistoryUIDetailsType Details;
} MpAlarmXHistoryUIConnectType;

typedef struct MpAlarmXHistoryUISetupType
{	unsigned short AlarmListSize;
	unsigned char AlarmListScrollWindow;
	plcstring TimeStampPattern[51];
} MpAlarmXHistoryUISetupType;

typedef struct MpAlarmXCfgCategorySeverityType
{	plcstring Severity[21];
} MpAlarmXCfgCategorySeverityType;

typedef struct MpAlarmXCfgCategoryCodeType
{	plcstring Code[21];
} MpAlarmXCfgCategoryCodeType;

typedef struct MpAlarmXCfgCategoryDefinedByType
{	enum MpAlarmXCfgCategoryDefinedByEnum Type;
	struct MpAlarmXCfgCategorySeverityType Severity;
	struct MpAlarmXCfgCategoryCodeType Code;
} MpAlarmXCfgCategoryDefinedByType;

typedef struct MpAlarmXCfgCategoryCategoryType
{	plcstring Name[51];
	struct MpAlarmXCfgCategoryDefinedByType DefinedBy;
} MpAlarmXCfgCategoryCategoryType;

typedef struct MpAlarmXCfgCategoryAlarmCatType
{	struct MpBaseCfgArrayType Category;
} MpAlarmXCfgCategoryAlarmCatType;

typedef struct MpAlarmXCfgCategoryType
{	struct MpAlarmXCfgCategoryAlarmCatType AlarmCategories;
} MpAlarmXCfgCategoryType;

typedef struct MpAlarmXCfgCoreActparamType
{	plcstring Name[101];
} MpAlarmXCfgCoreActparamType;

typedef struct MpAlarmXCfgCoreMappingActionType
{	enum MpAlarmXCfgCoreMappingActionEnum Type;
	struct MpAlarmXCfgCoreActparamType Data;
} MpAlarmXCfgCoreMappingActionType;

typedef struct MpAlarmXCfgCoreGeneralType
{	plcbit Enable;
	enum MpAlarmXCfgCoreTaskClassEnum CyclicTaskClass;
} MpAlarmXCfgCoreGeneralType;

typedef struct MpAlarmXCfgCoreMappingIType
{	plcstring Alarm[101];
	struct MpAlarmXCfgCoreMappingActionType Action;
} MpAlarmXCfgCoreMappingIType;

typedef struct MpAlarmXCfgCoreMappingType
{	struct MpBaseCfgArrayType Mapping;
} MpAlarmXCfgCoreMappingType;

typedef struct MpAlarmXCfgCoreDefaultType
{	struct MpBaseCfgArrayType Action;
} MpAlarmXCfgCoreDefaultType;

typedef struct MpAlarmXCfgCoreAlarmMappingType
{	struct MpAlarmXCfgCoreMappingType Mapping;
	struct MpAlarmXCfgCoreDefaultType Default;
} MpAlarmXCfgCoreAlarmMappingType;

typedef struct MpAlarmXCfgCoreArgumentsType
{	unsigned long NumberOfElements;
	plcstring Arguments[9][256];
} MpAlarmXCfgCoreArgumentsType;

typedef struct MpAlarmXCfgCoreListsType
{	plcstring List[51];
	signed long CodeOffset;
	struct MpAlarmXCfgCoreArgumentsType Arguments;
} MpAlarmXCfgCoreListsType;

typedef struct MpAlarmXCfgCoreAlarmListsType
{	struct MpBaseCfgArrayType Lists;
} MpAlarmXCfgCoreAlarmListsType;

typedef struct MpAlarmXCfgCoreEnabledType
{	plcstring Alarm[101];
} MpAlarmXCfgCoreEnabledType;

typedef struct MpAlarmXCfgCoreUncfgAlarmsType
{	enum MpAlarmXCfgCoreUncfgAlarmsEnum Type;
	struct MpAlarmXCfgCoreEnabledType Enabled;
} MpAlarmXCfgCoreUncfgAlarmsType;

typedef struct MpAlarmXCfgCoreDataType
{	unsigned long Size;
	unsigned long BufferSize;
	unsigned long MaximumSaveInterval;
} MpAlarmXCfgCoreDataType;

typedef struct MpAlarmXCfgCoreMemoryType
{	enum MpAlarmXCfgCoreMemoryEnum Type;
	struct MpAlarmXCfgCoreDataType Data;
} MpAlarmXCfgCoreMemoryType;

typedef struct MpAlarmXCfgCoreRetainType
{	struct MpAlarmXCfgCoreMemoryType Memory;
} MpAlarmXCfgCoreRetainType;

typedef struct MpAlarmXCfgCoreCategoriesType
{	plcstring List[51];
} MpAlarmXCfgCoreCategoriesType;

typedef struct MpAlarmXCfgCoreAlarmCatType
{	struct MpBaseCfgArrayType Categories;
} MpAlarmXCfgCoreAlarmCatType;

typedef struct MpAlarmXCfgCoreType
{	struct MpAlarmXCfgCoreGeneralType General;
	struct MpAlarmXCfgCoreAlarmMappingType AlarmMapping;
	struct MpAlarmXCfgCoreAlarmListsType AlarmLists;
	struct MpAlarmXCfgCoreUncfgAlarmsType UnconfiguredAlarms;
	struct MpAlarmXCfgCoreRetainType Retain;
	struct MpAlarmXCfgCoreAlarmCatType AlarmCategories;
} MpAlarmXCfgCoreType;

typedef struct MpAlarmXCfgHistoryGeneralType
{	plcbit Enable;
	plcbit EnableAuditing;
} MpAlarmXCfgHistoryGeneralType;

typedef struct MpAlarmXCfgHistoryExportType
{	plcstring TimestampPattern[51];
	plcbit AutoFileExtension;
	plcstring ColumnSeparator[2];
} MpAlarmXCfgHistoryExportType;

typedef struct MpAlarmXCfgHistoryDataType
{	unsigned long Size;
	unsigned long BufferSize;
	unsigned long MaximumSaveInterval;
} MpAlarmXCfgHistoryDataType;

typedef struct MpAlarmXCfgHistoryMemoryType
{	enum MpAlarmXCfgHistoryMemoryEnum Type;
	struct MpAlarmXCfgHistoryDataType Data;
} MpAlarmXCfgHistoryMemoryType;

typedef struct MpAlarmXCfgHistoryHistoryType
{	struct MpAlarmXCfgHistoryExportType Export;
	struct MpAlarmXCfgHistoryMemoryType Memory;
	enum MpAlarmXCfgHistoryScopeEnum Scope;
} MpAlarmXCfgHistoryHistoryType;

typedef struct MpAlarmXCfgHistoryType
{	struct MpAlarmXCfgHistoryGeneralType General;
	struct MpAlarmXCfgHistoryHistoryType AlarmHistory;
} MpAlarmXCfgHistoryType;

typedef struct MpAlarmXCfgListStaticType
{	double Limit;
	plcstring LimitText[101];
	float Delay;
	double Hysteresis;
	float TimeConstant;
} MpAlarmXCfgListStaticType;

typedef struct MpAlarmXCfgListDynamicType
{	plcstring LimitPv[256];
	plcstring LimitText[101];
	plcstring DelayPv[256];
	plcstring HysteresisPv[256];
	plcstring TimeConstantPv[256];
} MpAlarmXCfgListDynamicType;

typedef struct MpAlarmXCfgListLimitSelectorType
{	enum MpAlarmXCfgListLimitSelectorEnum Type;
	struct MpAlarmXCfgListStaticType LimitStatic;
	struct MpAlarmXCfgListDynamicType LimitDynamic;
} MpAlarmXCfgListLimitSelectorType;

typedef struct MpAlarmXCfgListLimitSeleRateType
{	enum MpAlarmXCfgListLimitSeleRateEnum Type;
	struct MpAlarmXCfgListStaticType RateStatic;
	struct MpAlarmXCfgListDynamicType RateDynamic;
} MpAlarmXCfgListLimitSeleRateType;

typedef struct MpAlarmXCfgListRecordingType
{	plcbit InactiveToActive;
	plcbit ActiveToInactive;
	plcbit UnacknowledgedToAcknowledged;
	plcbit AcknowledgedToUnacknowledged;
	plcbit UnconfirmedToConfirmed;
	plcbit ConfirmedToUnconfirmed;
	plcbit Update;
} MpAlarmXCfgListRecordingType;

typedef struct MpAlarmXCfgListSettingsType
{	enum MpAlarmXCfgListSettingsEnum Type;
	struct MpAlarmXCfgListStaticType Static;
	struct MpAlarmXCfgListDynamicType Dynamic;
} MpAlarmXCfgListSettingsType;

typedef struct MpAlarmXCfgListActivationType
{	plcbit Timestamp;
	plcbit Snippets;
} MpAlarmXCfgListActivationType;

typedef struct MpAlarmXCfgListDataUpdateType
{	struct MpAlarmXCfgListActivationType Activation;
} MpAlarmXCfgListDataUpdateType;

typedef struct MpAlarmXCfgListRecedgeType
{	plcbit InactiveToActive;
	plcbit UnacknowledgedToAcknowledged;
	plcbit AcknowledgedToUnacknowledged;
	plcbit UnconfirmedToConfirmed;
	plcbit ConfirmedToUnconfirmed;
} MpAlarmXCfgListRecedgeType;

typedef struct MpAlarmXCfgListEdgeAlarmType
{	enum MpAlarmXCfgListConfValueListEnum Confirm;
	plcbit MultipleInstances;
	plcbit ReactionWhilePending;
	plcbit Retain;
	plcbit Asynchronous;
	struct MpAlarmXCfgListDataUpdateType DataUpdate;
	struct MpAlarmXCfgListRecedgeType HistoryReport;
} MpAlarmXCfgListEdgeAlarmType;

typedef struct MpAlarmXCfgListRecpersType
{	plcbit InactiveToActive;
	plcbit ActiveToInactive;
	plcbit UnacknowledgedToAcknowledged;
	plcbit AcknowledgedToUnacknowledged;
	plcbit UnconfirmedToConfirmed;
	plcbit ConfirmedToUnconfirmed;
	plcbit Update;
} MpAlarmXCfgListRecpersType;

typedef struct MpAlarmXCfgListPersAlarmType
{	enum MpAlarmXCfgListAckValueListEnum Acknowledge;
	enum MpAlarmXCfgListConfValueListEnum Confirm;
	plcbit MultipleInstances;
	plcbit ReactionWhilePending;
	plcbit Retain;
	plcbit Asynchronous;
	struct MpAlarmXCfgListDataUpdateType DataUpdate;
	struct MpAlarmXCfgListRecpersType HistoryReport;
} MpAlarmXCfgListPersAlarmType;

typedef struct MpAlarmXCfgListUserDefinedType
{	plcbit AutoReset;
	enum MpAlarmXCfgListAckValueListEnum Acknowledge;
	enum MpAlarmXCfgListConfValueListEnum Confirm;
	plcbit MultipleInstances;
	plcbit ReactionWhilePending;
	plcbit Retain;
	plcbit Asynchronous;
	struct MpAlarmXCfgListDataUpdateType DataUpdate;
	struct MpAlarmXCfgListRecordingType HistoryReport;
} MpAlarmXCfgListUserDefinedType;

typedef struct MpAlarmXCfgListLevelmonType
{	plcstring MonitoredPv[256];
	plcbit Exclusive;
	struct MpAlarmXCfgListLimitSelectorType LowLimit;
	struct MpAlarmXCfgListLimitSelectorType LowlowLimit;
	struct MpAlarmXCfgListLimitSelectorType HighLimit;
	struct MpAlarmXCfgListLimitSelectorType HighhighLimit;
	struct MpAlarmXCfgListSettingsType Settings;
} MpAlarmXCfgListLevelmonType;

typedef struct MpAlarmXCfgListLevelMonitorType
{	enum MpAlarmXCfgListAckValueListEnum Acknowledge;
	enum MpAlarmXCfgListConfValueListEnum Confirm;
	plcbit ReactionWhilePending;
	struct MpAlarmXCfgListRecordingType HistoryReport;
	struct MpAlarmXCfgListLevelmonType Monitoring;
} MpAlarmXCfgListLevelMonitorType;

typedef struct MpAlarmXCfgListMonitoringType
{	plcstring MonitoredPv[256];
	plcstring SetpointPv[256];
	plcbit Exclusive;
	struct MpAlarmXCfgListLimitSelectorType LowLimit;
	struct MpAlarmXCfgListLimitSelectorType LowlowLimit;
	struct MpAlarmXCfgListLimitSelectorType HighLimit;
	struct MpAlarmXCfgListLimitSelectorType HighhighLimit;
	struct MpAlarmXCfgListSettingsType Settings;
} MpAlarmXCfgListMonitoringType;

typedef struct MpAlarmXCfgListDeviatMonitorType
{	enum MpAlarmXCfgListAckValueListEnum Acknowledge;
	enum MpAlarmXCfgListConfValueListEnum Confirm;
	plcbit ReactionWhilePending;
	struct MpAlarmXCfgListRecordingType HistoryReport;
	struct MpAlarmXCfgListMonitoringType Monitoring;
} MpAlarmXCfgListDeviatMonitorType;

typedef struct MpAlarmXCfgListRocmonType
{	plcstring MonitoredPv[256];
	plcbit Exclusive;
	struct MpAlarmXCfgListLimitSeleRateType LowLimit;
	struct MpAlarmXCfgListLimitSeleRateType LowlowLimit;
	struct MpAlarmXCfgListLimitSeleRateType HighLimit;
	struct MpAlarmXCfgListLimitSeleRateType HighhighLimit;
	struct MpAlarmXCfgListSettingsType Settings;
} MpAlarmXCfgListRocmonType;

typedef struct MpAlarmXCfgListRocMonitorType
{	enum MpAlarmXCfgListAckValueListEnum Acknowledge;
	enum MpAlarmXCfgListConfValueListEnum Confirm;
	plcbit ReactionWhilePending;
	struct MpAlarmXCfgListRecordingType HistoryReport;
	struct MpAlarmXCfgListRocmonType Monitoring;
} MpAlarmXCfgListRocMonitorType;

typedef struct MpAlarmXCfgListTrgvalueType
{	unsigned long NumberOfElements;
	plcstring AlarmTriggerValueI[4][51];
} MpAlarmXCfgListTrgvalueType;

typedef struct MpAlarmXCfgListTrgvaluesType
{	struct MpAlarmXCfgListTrgvalueType AlarmTriggerValueI;
} MpAlarmXCfgListTrgvaluesType;

typedef struct MpAlarmXCfgListDiscMonType
{	plcstring MonitoredPv[256];
	struct MpAlarmXCfgListTrgvaluesType TriggerValues;
	struct MpAlarmXCfgListSettingsType Settings;
} MpAlarmXCfgListDiscMonType;

typedef struct MpAlarmXCfgListDiscreteMonType
{	enum MpAlarmXCfgListAckValueListEnum Acknowledge;
	enum MpAlarmXCfgListConfValueListEnum Confirm;
	plcbit ReactionWhilePending;
	struct MpAlarmXCfgListRecordingType HistoryReport;
	struct MpAlarmXCfgListDiscMonType Monitoring;
} MpAlarmXCfgListDiscreteMonType;

typedef struct MpAlarmXCfgListBehaviorType
{	enum MpAlarmXCfgListBehaviorEnum Type;
	struct MpAlarmXCfgListEdgeAlarmType Edge;
	struct MpAlarmXCfgListPersAlarmType Persistent;
	struct MpAlarmXCfgListUserDefinedType UserDefined;
	struct MpAlarmXCfgListLevelMonitorType LevelMonitor;
	struct MpAlarmXCfgListDeviatMonitorType DeviatMonitor;
	struct MpAlarmXCfgListRocMonitorType RocMonitor;
	struct MpAlarmXCfgListDiscreteMonType DiscreteMon;
} MpAlarmXCfgListBehaviorType;

typedef struct MpAlarmXCfgListAlarmType
{	plcstring Name[101];
	plcstring Message[256];
	unsigned long Code;
	unsigned long Severity;
	struct MpAlarmXCfgListBehaviorType Behavior;
	plcbit Disable;
	plcstring InhibitPv[256];
	plcstring AdditionalInformation1[256];
	plcstring AdditionalInformation2[256];
} MpAlarmXCfgListAlarmType;

typedef struct MpAlarmXCfgListAlarmListType
{	struct MpBaseCfgArrayType Alarm;
} MpAlarmXCfgListAlarmListType;

typedef struct MpAlarmXCfgListEnabledType
{	plcstring Language[21];
} MpAlarmXCfgListEnabledType;

typedef struct MpAlarmXCfgListAutoDetectType
{	enum MpAlarmXCfgListAutoDetectEnum Type;
	struct MpAlarmXCfgListEnabledType Enabled;
} MpAlarmXCfgListAutoDetectType;

typedef struct MpAlarmXCfgListSnippetPvType
{	plcstring ProcessVariable[256];
} MpAlarmXCfgListSnippetPvType;

typedef struct MpAlarmXCfgListValueType
{	enum MpAlarmXCfgListValueEnum Type;
	struct MpAlarmXCfgListSnippetPvType SnippetPv;
} MpAlarmXCfgListValueType;

typedef struct MpAlarmXCfgListSnippetType
{	plcstring Key[101];
	struct MpAlarmXCfgListValueType Value;
	plcstring Alarm[101];
} MpAlarmXCfgListSnippetType;

typedef struct MpAlarmXCfgListTextSnippetsType
{	struct MpAlarmXCfgListAutoDetectType AutoDetect;
	struct MpBaseCfgArrayType Snippet;
} MpAlarmXCfgListTextSnippetsType;

typedef struct MpAlarmXCfgListType
{	struct MpAlarmXCfgListAlarmListType AlarmList;
	struct MpAlarmXCfgListTextSnippetsType TextSnippets;
} MpAlarmXCfgListType;

typedef struct MpAlarmXCfgQueryPendColItemType
{	enum MpAlarmXCfgQueryPendColumnsEnum Column;
	plcstring ProcessVariable[256];
} MpAlarmXCfgQueryPendColItemType;

typedef struct MpAlarmXCfgQueryPendColType
{	unsigned long NumberOfElements;
	struct MpAlarmXCfgQueryPendColItemType Columns[15];
} MpAlarmXCfgQueryPendColType;

typedef struct MpAlarmXCfgQuerySelectpType
{	struct MpAlarmXCfgQueryPendColType Columns;
} MpAlarmXCfgQuerySelectpType;

typedef struct MpAlarmXCfgQueryValueType
{	plcstring Value[256];
} MpAlarmXCfgQueryValueType;

typedef struct MpAlarmXCfgQueryCompareToType
{	enum MpAlarmXCfgQueryCompareToEnum Type;
	struct MpAlarmXCfgQueryValueType Value;
} MpAlarmXCfgQueryCompareToType;

typedef struct MpAlarmXCfgQueryPendCondItemType
{	enum MpAlarmXCfgQueryPendColumnsEnum Column;
	enum MpAlarmXCfgQueryOperatorsEnum Operator;
	struct MpAlarmXCfgQueryCompareToType CompareTo;
} MpAlarmXCfgQueryPendCondItemType;

typedef struct MpAlarmXCfgQueryPendCondType
{	unsigned long NumberOfElements;
	struct MpAlarmXCfgQueryPendCondItemType WhereFilter[5];
} MpAlarmXCfgQueryPendCondType;

typedef struct MpAlarmXCfgQueryWherepType
{	plcstring Connect[256];
	struct MpAlarmXCfgQueryPendCondType WhereFilter;
} MpAlarmXCfgQueryWherepType;

typedef struct MpAlarmXCfgQueryPendingType
{	plcstring Component[51];
	struct MpAlarmXCfgQuerySelectpType Select;
	struct MpAlarmXCfgQueryWherepType Where;
} MpAlarmXCfgQueryPendingType;

typedef struct MpAlarmXCfgQueryConfColItemType
{	enum MpAlarmXCfgQueryConfColumnsEnum Column;
	plcstring ProcessVariable[256];
} MpAlarmXCfgQueryConfColItemType;

typedef struct MpAlarmXCfgQueryConfColType
{	unsigned long NumberOfElements;
	struct MpAlarmXCfgQueryConfColItemType Columns[10];
} MpAlarmXCfgQueryConfColType;

typedef struct MpAlarmXCfgQuerySelectcType
{	struct MpAlarmXCfgQueryConfColType Columns;
} MpAlarmXCfgQuerySelectcType;

typedef struct MpAlarmXCfgQueryConfCondItemType
{	enum MpAlarmXCfgQueryConfColumnsEnum Column;
	enum MpAlarmXCfgQueryOperatorsEnum Operator;
	struct MpAlarmXCfgQueryCompareToType CompareTo;
} MpAlarmXCfgQueryConfCondItemType;

typedef struct MpAlarmXCfgQueryConfCondType
{	unsigned long NumberOfElements;
	struct MpAlarmXCfgQueryConfCondItemType WhereFilter[5];
} MpAlarmXCfgQueryConfCondType;

typedef struct MpAlarmXCfgQueryWherecType
{	plcstring Connect[256];
	struct MpAlarmXCfgQueryConfCondType WhereFilter;
} MpAlarmXCfgQueryWherecType;

typedef struct MpAlarmXCfgQueryConfiguredType
{	plcstring Component[51];
	struct MpAlarmXCfgQuerySelectcType Select;
	struct MpAlarmXCfgQueryWherecType Where;
} MpAlarmXCfgQueryConfiguredType;

typedef struct MpAlarmXCfgQueryHistColItemType
{	enum MpAlarmXCfgQueryColumnsEnum Column;
	plcstring ProcessVariable[256];
} MpAlarmXCfgQueryHistColItemType;

typedef struct MpAlarmXCfgQueryHistColType
{	unsigned long NumberOfElements;
	struct MpAlarmXCfgQueryHistColItemType Columns[15];
} MpAlarmXCfgQueryHistColType;

typedef struct MpAlarmXCfgQuerySelectqType
{	struct MpAlarmXCfgQueryHistColType Columns;
} MpAlarmXCfgQuerySelectqType;

typedef struct MpAlarmXCfgQueryHistCondItemType
{	enum MpAlarmXCfgQueryColumnsEnum Column;
	enum MpAlarmXCfgQueryOperatorsEnum Operator;
	struct MpAlarmXCfgQueryCompareToType CompareTo;
} MpAlarmXCfgQueryHistCondItemType;

typedef struct MpAlarmXCfgQueryHistCondType
{	unsigned long NumberOfElements;
	struct MpAlarmXCfgQueryHistCondItemType WhereFilter[5];
} MpAlarmXCfgQueryHistCondType;

typedef struct MpAlarmXCfgQueryWhereqType
{	plcstring Connect[256];
	struct MpAlarmXCfgQueryHistCondType WhereFilter;
} MpAlarmXCfgQueryWhereqType;

typedef struct MpAlarmXCfgQueryHistoricalType
{	plcstring Component[51];
	struct MpAlarmXCfgQuerySelectqType Select;
	struct MpAlarmXCfgQueryWhereqType Where;
} MpAlarmXCfgQueryHistoricalType;

typedef struct MpAlarmXCfgQuerySourceType
{	enum MpAlarmXCfgQuerySourceEnum Type;
	struct MpAlarmXCfgQueryPendingType Pending;
	struct MpAlarmXCfgQueryConfiguredType Configured;
	struct MpAlarmXCfgQueryHistoricalType Historical;
} MpAlarmXCfgQuerySourceType;

typedef struct MpAlarmXCfgQueryQueryType
{	plcstring Name[101];
	plcstring UpdateCount[256];
	enum MpAlarmXCfgQueryUpdateModeEnum UpdateMode;
	struct MpAlarmXCfgQuerySourceType QuerySource;
} MpAlarmXCfgQueryQueryType;

typedef struct MpAlarmXCfgQueryDataQueriesType
{	struct MpBaseCfgArrayType Query;
} MpAlarmXCfgQueryDataQueriesType;

typedef struct MpAlarmXCfgQueryType
{	struct MpAlarmXCfgQueryDataQueriesType DataQueries;
} MpAlarmXCfgQueryType;

typedef struct MpAlarmXCore
{
	/* VAR_INPUT (analog) */
	struct MpComIdentType* MpLink;
	/* VAR_OUTPUT (analog) */
	signed long StatusID;
	unsigned long ActiveAlarms;
	unsigned long PendingAlarms;
	unsigned long UnacknowledgedAlarms;
	unsigned long UnconfirmedAlarms;
	struct MpAlarmXCoreInfoType Info;
	/* VAR (analog) */
	unsigned char InternalState;
	unsigned long InternalData[22];
	/* VAR_INPUT (digital) */
	plcbit Enable;
	plcbit ErrorReset;
	plcbit AcknowledgeAll;
	/* VAR_OUTPUT (digital) */
	plcbit Active;
	plcbit Error;
	plcbit CommandBusy;
	plcbit CommandDone;
} MpAlarmXCore_typ;

typedef struct MpAlarmXListUI
{
	/* VAR_INPUT (analog) */
	struct MpComIdentType* MpLink;
	struct MpAlarmXListUISetupType UISetup;
	plcstring (*Language);
	enum MpAlarmXMeasurementSystemEnum MeasurementSystem;
	struct MpAlarmXListUIConnectType* UIConnect;
	/* VAR_OUTPUT (analog) */
	signed long StatusID;
	struct MpAlarmXListUIInfoType Info;
	/* VAR (analog) */
	unsigned char InternalState;
	unsigned long InternalData[35];
	/* VAR_INPUT (digital) */
	plcbit Enable;
	plcbit ErrorReset;
	/* VAR_OUTPUT (digital) */
	plcbit Active;
	plcbit Error;
} MpAlarmXListUI_typ;

typedef struct MpAlarmXHistoryUI
{
	/* VAR_INPUT (analog) */
	struct MpComIdentType* MpLink;
	struct MpAlarmXHistoryUISetupType UISetup;
	plcstring (*Language);
	enum MpAlarmXMeasurementSystemEnum MeasurementSystem;
	struct MpAlarmXHistoryUIConnectType* UIConnect;
	/* VAR_OUTPUT (analog) */
	signed long StatusID;
	struct MpAlarmXHistoryUIInfoType Info;
	/* VAR (analog) */
	unsigned char InternalState;
	unsigned long InternalData[38];
	/* VAR_INPUT (digital) */
	plcbit Enable;
	plcbit ErrorReset;
	/* VAR_OUTPUT (digital) */
	plcbit Active;
	plcbit Error;
} MpAlarmXHistoryUI_typ;

typedef struct MpAlarmXHistory
{
	/* VAR_INPUT (analog) */
	struct MpComIdentType* MpLink;
	plcstring (*DeviceName);
	plcstring (*FileName);
	plcstring (*Language);
	enum MpAlarmXMeasurementSystemEnum MeasurementSystem;
	/* VAR_OUTPUT (analog) */
	signed long StatusID;
	unsigned long HistoryEntries;
	struct MpAlarmXHistoryInfoType Info;
	/* VAR (analog) */
	unsigned char InternalState;
	unsigned long InternalData[21];
	/* VAR_INPUT (digital) */
	plcbit Enable;
	plcbit ErrorReset;
	plcbit Overwrite;
	plcbit Export;
	plcbit Clear;
	/* VAR_OUTPUT (digital) */
	plcbit Active;
	plcbit Error;
	plcbit CommandBusy;
	plcbit CommandDone;
} MpAlarmXHistory_typ;

typedef struct MpAlarmXQuery
{
	/* VAR_INPUT (analog) */
	struct MpComIdentType* MpLink;
	enum MpAlarmXQueryModeEnum Mode;
	plcstring (*Name);
	plcstring (*Language);
	enum MpAlarmXMeasurementSystemEnum MeasurementSystem;
	/* VAR_OUTPUT (analog) */
	signed long StatusID;
	struct MpAlarmXQueryInfoType Info;
	/* VAR (analog) */
	unsigned char InternalState;
	unsigned long InternalData[22];
	/* VAR_INPUT (digital) */
	plcbit Enable;
	plcbit ErrorReset;
	plcbit Execute;
	plcbit Next;
	/* VAR_OUTPUT (digital) */
	plcbit Active;
	plcbit Error;
	plcbit CommandBusy;
	plcbit CommandDone;
} MpAlarmXQuery_typ;

typedef struct MpAlarmXAlarmControl
{
	/* VAR_INPUT (analog) */
	struct MpComIdentType* MpLink;
	plcstring (*Name);
	unsigned long ID;
	/* VAR_OUTPUT (analog) */
	signed long StatusID;
	unsigned long InstanceID;
	struct MpAlarmXAlarmControlInfoType Info;
	/* VAR (analog) */
	unsigned char InternalState;
	unsigned long InternalData[19];
	/* VAR_INPUT (digital) */
	plcbit Enable;
	plcbit ErrorReset;
	plcbit Set;
	plcbit Reset;
	plcbit Acknowledge;
	plcbit Confirm;
	/* VAR_OUTPUT (digital) */
	plcbit Active;
	plcbit Error;
	plcbit CommandBusy;
	plcbit CommandDone;
} MpAlarmXAlarmControl_typ;



/* Prototyping of functions and function blocks */
_BUR_PUBLIC void MpAlarmXCore(struct MpAlarmXCore* inst);
_BUR_PUBLIC void MpAlarmXListUI(struct MpAlarmXListUI* inst);
_BUR_PUBLIC void MpAlarmXHistoryUI(struct MpAlarmXHistoryUI* inst);
_BUR_PUBLIC void MpAlarmXHistory(struct MpAlarmXHistory* inst);
_BUR_PUBLIC void MpAlarmXQuery(struct MpAlarmXQuery* inst);
_BUR_PUBLIC void MpAlarmXAlarmControl(struct MpAlarmXAlarmControl* inst);
_BUR_PUBLIC plcbit MpAlarmXCheckState(struct MpComIdentType* MpLink, plcstring* Name, enum MpAlarmXStateEnum State);
_BUR_PUBLIC plcbit MpAlarmXCheckStateID(struct MpComIdentType* MpLink, unsigned long InstanceID, enum MpAlarmXStateEnum State);
_BUR_PUBLIC plcbit MpAlarmXCheckReaction(struct MpComIdentType* MpLink, plcstring* Name);
_BUR_PUBLIC unsigned long MpAlarmXSet(struct MpComIdentType* MpLink, plcstring* Name);
_BUR_PUBLIC signed long MpAlarmXAcknowledge(struct MpComIdentType* MpLink, plcstring* Name);
_BUR_PUBLIC signed long MpAlarmXAcknowledgeID(struct MpComIdentType* MpLink, unsigned long InstanceID);
_BUR_PUBLIC signed long MpAlarmXConfirm(struct MpComIdentType* MpLink, plcstring* Name);
_BUR_PUBLIC signed long MpAlarmXConfirmID(struct MpComIdentType* MpLink, unsigned long InstanceID);
_BUR_PUBLIC signed long MpAlarmXReset(struct MpComIdentType* MpLink, plcstring* Name);
_BUR_PUBLIC signed long MpAlarmXResetID(struct MpComIdentType* MpLink, unsigned long InstanceID);


#ifdef __cplusplus
};
#endif
#endif /* _MPALARMX_ */

