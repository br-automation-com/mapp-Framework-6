
TYPE
    MpUserXErrorEnum : 
        ( (* Error numbers of library MpUserX *)
        mpUSERX_NO_ERROR := 0, (* No error *)
        mpUSERX_ERR_ACTIVATION := -1064239103, (* Could not create component [Error: 1, 0xc0910001] *)
        mpUSERX_ERR_MPLINK_NULL := -1064239102, (* MpLink is NULL pointer [Error: 2, 0xc0910002] *)
        mpUSERX_ERR_MPLINK_INVALID := -1064239101, (* MpLink connection not allowed [Error: 3, 0xc0910003] *)
        mpUSERX_ERR_MPLINK_CHANGED := -1064239100, (* MpLink modified [Error: 4, 0xc0910004] *)
        mpUSERX_ERR_MPLINK_CORRUPT := -1064239099, (* Invalid MpLink contents [Error: 5, 0xc0910005] *)
        mpUSERX_ERR_MPLINK_IN_USE := -1064239098, (* MpLink already in use [Error: 6, 0xc0910006] *)
        mpUSERX_ERR_PAR_NULL := -1064239097, (* Parameters structure is a null pointer [Error: 7, 0xc0910007] *)
        mpUSERX_ERR_CONFIG_NULL := -1064239096, (* Configuration structure is null pointer [Error: 8, 0xc0910008] *)
        mpUSERX_ERR_CONFIG_NO_PV := -1064239095, (* Configuration pointer not PV [Error: 9, 0xc0910009] *)
        mpUSERX_ERR_CONFIG_LOAD := -1064239094, (* Error loading configuration {2:ConfigName} (ErrorCause: {1:ErrorNumber}) [Error: 10, 0xc091000a] *)
        mpUSERX_WRN_CONFIG_LOAD := -2137980917, (* Warning loading configuration [Warning: 11, 0x8091000b] *)
        mpUSERX_ERR_CONFIG_SAVE := -1064239092, (* Error saving configuration {2:ConfigName} (ErrorCause: {1:ErrorNumber}) [Error: 12, 0xc091000c] *)
        mpUSERX_ERR_CONFIG_INVALID := -1064239091, (* Invalid Configuration [Error: 13, 0xc091000d] *)
        mpUSERX_ERR_USER_NOT_EXISTING := -1064144895, (* User does not exist [Error: 28673, 0xc0927001] *)
        mpUSERX_ERR_USER_EXISTS := -1064144894, (* User already exists [Error: 28674, 0xc0927002] *)
        mpUSERX_ERR_INSUFFICIENT_RIGHTS := -1064144891, (* Insufficient rights [Error: 28677, 0xc0927005] *)
        mpUSERX_ERR_ROLE_NOT_EXISTING := -1064144890, (* Role does not exist [Error: 28678, 0xc0927006] *)
        mpUSERX_ERR_USER_IS_LOCKED := -1064144888, (* User is locked [Error: 28680, 0xc0927008] *)
        mpUSERX_ERR_PASSWORD_CHANGE_REQ := -1064144887, (* Password change required [Error: 28681, 0xc0927009] *)
        mpUSERX_ERR_NO_ADMIN_RIGHTS := -1064144885, (* User has no administrator rights [Error: 28683, 0xc092700b] *)
        mpUSERX_ERR_LOGIN_INST_EXISTS := -1064144884, (* MpUserXLogin-instance already exists ({1:ErrorNumber}) [Error: 28684, 0xc092700c] *)
        mpUSERX_ERR_NOT_LOGGED_IN := -1064144883, (* No user logged in [Error: 28685, 0xc092700d] *)
        mpUSERX_WRN_PASSWORD_CHANGE_REQ := -2137886702, (* Password change required [Warning: 28690, 0x80927012] *)
        mpUSERX_ERR_ROLE_INDEX_NOT_OK := -1064144877, (* Invalid role index [Error: 28691, 0xc0927013] *)
        mpUSERX_ERR_NO_ROLENAME := -1064144876, (* No role name provided [Error: 28692, 0xc0927014] *)
        mpUSERX_ERR_LOGGED_IN := -1064144875, (* User is logged in [Error: 28693, 0xc0927015] *)
        mpUSERX_ERR_MISSING_UICONNECT := -1064144874, (* Missing value on UIConnect [Error: 28694, 0xc0927016] *)
        mpUSERX_ERR_NO_USERNAME := -1064144873, (* No username provided [Error: 28695, 0xc0927017] *)
        mpUSERX_ERR_NO_PASSWORD := -1064144872, (* No password provided [Error: 28696, 0xc0927018] *)
        mpUSERX_ERR_PASSWORD_CONFIRM := -1064144870, (* Confirmation password incorrect [Error: 28698, 0xc092701a] *)
        mpUSERX_ERR_IMPORT_DATA := -1064144868, (* Import failed for {2:Section} [Error: 28700, 0xc092701c] *)
        mpUSERX_ERR_LOAD_IMPORT_FILE := -1064144867, (* Error loading import file {2:FileName} from {3:DeviceName} ({1:ErrorNumber}) [Error: 28701, 0xc092701d] *)
        mpUSERX_ERR_SAVE_EXPORT_FILE := -1064144866, (* Error saving export file {2:FileName} to {3:DeviceName} ({1:ErrorNumber}) [Error: 28702, 0xc092701e] *)
        mpUSERX_ERR_USERNAME_TOO_SHORT := -1064144861, (* Provided username is too short [Error: 28707, 0xc0927023] *)
        mpUSERX_ERR_ROLE_EXISTS := -1064144860, (* Role with same name already exists [Error: 28708, 0xc0927024] *)
        mpUSERX_ERR_FAILED_SIGNATURES := -1064144858, (* Max. number of failed signature attempts exceeded (signature is aborted) [Error: 28710, 0xc0927026] *)
        mpUSERX_ERR_SIGNATURE_BUSY := -1064144857, (* The last signed action was not checked yet (no new signature possible) [Error: 28711, 0xc0927027] *)
        mpUSERX_ERR_IMPORT_FILE_FORMAT := -1064144855, (* Invalid import file format [Error: 28713, 0xc0927029] *)
        mpUSERX_WRN_KEY_DUPLICATE := -2137886678, (* The key {2:Key} is already in use. The value {3:Value} will be ignored. ({1:ErrorNumber}) [Warning: 28714, 0x8092702a] *)
        mpUSERX_ERR_INFO_NOT_FOUND := -1064144853, (* The requested user information was not found. [Error: 28715, 0xc092702b] *)
        mpUSERX_ERR_EMPTY_KEY := -1064144852, (* No key provided [Error: 28716, 0xc092702c] *)
        mpUSERX_ERR_BUFFER_TOO_SMALL := -1064144851, (* Provided output buffer is too small [Error: 28717, 0xc092702d] *)
        mpUSERX_ERR_LDAP_ERROR := -1064144850, (* LDAP error: {2:ErrorText} ({1:ErrorNumber}) [Error: 28718, 0xc092702e] *)
        mpUSERX_ERR_NO_SERVER_CONNECTION := -1064144849, (* No connection to the central user management server available [Error: 28719, 0xc092702f] *)
        mpUSERX_ERR_INVALID_CREDENTIALS := -1064144848, (* Invalid credentials (username and/ or password) [Error: 28720, 0xc0927030] *)
        mpUSERX_ERR_ACTION_NOT_ALLOWED := -1064144847, (* The attempted action ({2:Action}) is not allowed for central user management. [Error: 28721, 0xc0927031] *)
        mpUSERX_WRN_LDAP_WARNING := -2137886670, (* LDAP warning: {2:ErrorText} ({1:ErrorNumber}) [Warning: 28722, 0x80927032] *)
        mpUSERX_ERR_PASSWORD_RESTRICTION := -1064144845, (* Could not change password. New password does not meet password policy (e.g. length, complexity, history). [Error: 28723, 0xc0927033] *)
        mpUSERX_ERR_FUNCTION_UNAVAILABLE := -1064144844, (* Function is not available (runtime mismatch) [Error: 28724, 0xc0927034] *)
        mpUSERX_WRN_PASSWORD_WILL_EXPIRE := -2137886667, (* User's password will expire [Warning: 28725, 0x80927035] *)
        mpUSERX_WRN_INVALID_DISPLAY_NAME := -2137886666, (* Attribute {2:DisplayName} does not exist or has no valid value. 'Username' was used instead. [Warning: 28726, 0x80927036] *)
        mpUSERX_ERR_REQUEST_LIMIT := -1064144841, (* Request limit reached. Command currently not possible [Error: 28727, 0xc0927037] *)
        mpUSERX_ERR_SESSION_LIMIT := -1064144840 (* User session limit reached. Login currently not possible [Error: 28728, 0xc0927038] *)
        );
END_TYPE
