/* Automation Studio generated header file */
/* Do not edit ! */
/* MpBackup 6.0.7003 */

#ifndef _MPBACKUP_
#define _MPBACKUP_
#ifdef __cplusplus
extern "C" 
{
#endif
#ifndef _MpBackup_VERSION
#define _MpBackup_VERSION 6.0.7003
#endif

#include <bur/plctypes.h>

#ifndef _BUR_PUBLIC
#define _BUR_PUBLIC
#endif
#ifdef _SG3
		#include "MpBase.h"
#endif

#ifdef _SG4
		#include "MpBase.h"
#endif

#ifdef _SGC
		#include "MpBase.h"
#endif



/* Datatypes and datatypes of function blocks */
typedef enum MpBackupGenerationTypeEnum
{	mpBACKUP_GENERATION_AUTO = 1,
	mpBACKUP_GENERATION_MANUAL = 0
} MpBackupGenerationTypeEnum;

typedef enum MpBackupErrorEnum
{	mpBACKUP_NO_ERROR = 0,
	mpBACKUP_ERR_ACTIVATION = -1064239103,
	mpBACKUP_ERR_MPLINK_NULL = -1064239102,
	mpBACKUP_ERR_MPLINK_INVALID = -1064239101,
	mpBACKUP_ERR_MPLINK_CHANGED = -1064239100,
	mpBACKUP_ERR_MPLINK_CORRUPT = -1064239099,
	mpBACKUP_ERR_MPLINK_IN_USE = -1064239098,
	mpBACKUP_ERR_CONFIG_NULL = -1064239096,
	mpBACKUP_ERR_CONFIG_NO_PV = -1064239095,
	mpBACKUP_ERR_CONFIG_LOAD = -1064239094,
	mpBACKUP_WRN_CONFIG_LOAD = -2137980917,
	mpBACKUP_ERR_CONFIG_SAVE = -1064239092,
	mpBACKUP_ERR_CONFIG_INVALID = -1064239091,
	mpBACKUP_ERR_INSTALL_FAILED = -1064159488,
	mpBACKUP_ERR_CREATE_FAILED = -1064159487,
	mpBACKUP_ERR_REQUEST_INFO_FAILED = -1064159486,
	mpBACKUP_WRN_UPDATE_CHECK_FAILED = -2137901309
} MpBackupErrorEnum;

typedef enum MpBackupAlarmEnum
{	mpBACKUP_ALM_CREATE_FAILED = 0,
	mpBACKUP_ALM_INSTALL_FAILED = 1,
	mpBACKUP_ALM_UPDATE_CHECK_FAILED = 2
} MpBackupAlarmEnum;

typedef struct MpBackupLastBackupType
{	plcstring Name[256];
	plcdt DateTime;
	enum MpBackupGenerationTypeEnum GenerationType;
} MpBackupLastBackupType;

typedef struct MpBackupProjectInfoCurrentType
{	plcstring ConfigurationID[256];
	plcstring ConfigurationVersion[65];
} MpBackupProjectInfoCurrentType;

typedef struct MpBackupProjectInfoRequestType
{	plcstring Name[256];
	plcstring ConfigurationID[256];
	plcstring ConfigurationVersion[65];
} MpBackupProjectInfoRequestType;

typedef struct MpBackupProjectInfoType
{	struct MpBackupProjectInfoCurrentType Current;
	struct MpBackupProjectInfoRequestType Requested;
} MpBackupProjectInfoType;

typedef struct MpBackupStatusIDType
{	enum MpBackupErrorEnum ID;
	MpComSeveritiesEnum Severity;
} MpBackupStatusIDType;

typedef struct MpBackupDiagType
{	struct MpBackupStatusIDType StatusID;
} MpBackupDiagType;

typedef struct MpBackupAutoBackupInfoType
{	plcbit InProgress;
} MpBackupAutoBackupInfoType;

typedef struct MpBackupAutoUpdateInfoType
{	plcbit IsAvailable;
	plcstring Name[256];
	plcstring ConfigurationID[256];
	plcstring ConfigurationVersion[65];
} MpBackupAutoUpdateInfoType;

typedef struct MpBackupAutoInfoType
{	struct MpBackupAutoBackupInfoType Backup;
	struct MpBackupAutoUpdateInfoType Update;
} MpBackupAutoInfoType;

typedef struct MpBackupCoreInfoType
{	struct MpBackupLastBackupType LastBackup;
	struct MpBackupProjectInfoType Project;
	struct MpBackupDiagType Diag;
	struct MpBackupAutoInfoType Automatic;
} MpBackupCoreInfoType;

typedef struct MpBackupCore
{
	/* VAR_INPUT (analog) */
	struct MpComIdentType* MpLink;
	plcstring (*DeviceName);
	plcstring (*Name);
	/* VAR_OUTPUT (analog) */
	signed long StatusID;
	struct MpBackupCoreInfoType Info;
	/* VAR (analog) */
	unsigned char InternalState;
	unsigned long InternalData[23];
	/* VAR_INPUT (digital) */
	plcbit Enable;
	plcbit ErrorReset;
	plcbit Overwrite;
	plcbit Create;
	plcbit Install;
	plcbit RequestInfo;
	/* VAR_OUTPUT (digital) */
	plcbit Active;
	plcbit Error;
	plcbit CommandBusy;
	plcbit CommandDone;
} MpBackupCore_typ;



/* Prototyping of functions and function blocks */
_BUR_PUBLIC void MpBackupCore(struct MpBackupCore* inst);


#ifdef __cplusplus
};
#endif
#endif /* _MPBACKUP_ */

