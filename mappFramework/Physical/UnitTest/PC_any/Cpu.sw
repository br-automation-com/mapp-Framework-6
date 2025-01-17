﻿<?xml version="1.0" encoding="utf-8"?>
<?AutomationStudio FileVersion="4.9"?>
<SwConfiguration CpuAddress="SL1" xmlns="http://br-automation.co.at/AS/SwConfiguration">
  <TaskClass Name="Cyclic#1">
    <Task Name="AppAxis_1" Source="MachineControl.AppAxis_1.AppAxis_1.prg" Memory="UserROM" Language="IEC" Debugging="true" />
    <Task Name="AppAxisUni" Source="UnitTest.AppAxis_1.AppAxisUnitTest.prg" Memory="UserROM" Language="ANSIC" Debugging="true" />
  </TaskClass>
  <TaskClass Name="Cyclic#2" />
  <TaskClass Name="Cyclic#3" />
  <TaskClass Name="Cyclic#4" />
  <TaskClass Name="Cyclic#5" />
  <TaskClass Name="Cyclic#6" />
  <TaskClass Name="Cyclic#7" />
  <TaskClass Name="Cyclic#8">
    <Task Name="AlarmMgr" Source="Infrastructure.AlarmX.AlarmMgr.prg" Memory="UserROM" Language="IEC" Debugging="true" />
    <Task Name="AlarmXUnit" Source="UnitTest.AlarmX.AlarmXUnitTest.prg" Memory="UserROM" Language="ANSIC" Debugging="true" />
    <Task Name="AuditMgr" Source="Infrastructure.Audit.AuditMgr.prg" Memory="UserROM" Language="IEC" Debugging="true" />
    <Task Name="AuditTest" Source="UnitTest.Audit.AuditTest.prg" Memory="UserROM" Language="ANSIC" Debugging="true" />
    <Task Name="UsbMgr" Source="Infrastructure.Usb.UsbMgr.prg" Memory="UserROM" Language="IEC" Debugging="true" />
    <Task Name="BackupMgr" Source="Infrastructure.Backup.BackupMgr.prg" Memory="UserROM" Language="IEC" Debugging="true" />
    <Task Name="BackupUnit" Source="UnitTest.Backup.BackupUnitTest.prg" Memory="UserROM" Language="ANSIC" Debugging="true" />
    <Task Name="RecipeMgr" Source="Infrastructure.Recipe.RecipeMgr.prg" Memory="UserROM" Language="IEC" Debugging="true" />
    <Task Name="RecipeMgrU" Source="UnitTest.Recipe.RecipeMgrUnitTest.prg" Memory="UserROM" Language="ANSIC" Debugging="true" />
    <Task Name="UserXMgr" Source="Infrastructure.UserX.UserXMgr.prg" Memory="UserROM" Language="IEC" Debugging="true" />
    <Task Name="UserXUnitT" Source="UnitTest.UserX.UserXUnitTest.prg" Memory="UserROM" Language="ANSIC" Debugging="true" />
    <Task Name="FileMgr" Source="Infrastructure.File.FileMgr.prg" Memory="UserROM" Language="IEC" Debugging="true" />
    <Task Name="FileTest" Source="UnitTest.File.FileUnitTest.prg" Memory="UserROM" Language="ANSIC" Debugging="true" />
    <Task Name="ReportMgr" Source="Infrastructure.Report.ReportMgr.prg" Memory="UserROM" Language="IEC" Debugging="true" />
    <Task Name="ReportUnit" Source="UnitTest.Report.ReportUnitTest.prg" Memory="UserROM" Language="ANSIC" Debugging="true" />
  </TaskClass>
  <NcDataObjects>
    <NcDataObject Name="mcdrivelog" Source="" Memory="UserROM" Language="Binary" />
  </NcDataObjects>
  <Binaries>
    <BinaryObject Name="mCoWebSc" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="arflatprv" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="Axis1Grp" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="Axis1Alm" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="AlarmXCfg" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="AlarmXHist" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="MachineGrp" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="arsvcreg" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="TCData" Source="" Memory="SystemROM" Language="Binary" />
    <BinaryObject Name="TCLang" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="mvLoader" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="udbdef" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="mcprofgen" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="mcacpdrv" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="FWRules" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="SLO_Speed" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="SLO_Pos" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="asfw" Source="" Memory="SystemROM" Language="Binary" />
    <BinaryObject Name="ashwd" Source="" Memory="SystemROM" Language="Binary" />
    <BinaryObject Name="ashwac" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="iomap" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="arconfig" Source="" Memory="SystemROM" Language="Binary" />
    <BinaryObject Name="sysconf" Source="" Memory="SystemROM" Language="Binary" />
    <BinaryObject Name="FileCfg" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="RecipeFile" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="UserXCfg" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="BackupCfg" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="UserXlogin" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="BackupFile" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="RecipeCSV" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="RecipeXML" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="TC" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="UnitCfg" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="CustomCfg" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="AuditCfg" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="SimpleCfg" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="VAppAxis1" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="AdvCfg" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="Role" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="User" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="AppAxis1" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="ReportFile" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="UaCsConfig" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="Axis1Alm_C" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="AlarmXHi_2" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="Axis1Alm_Q" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="AlarmXHi_1" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="AlarmXCf_2" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="AlarmXCf_1" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="Axis1Alm_1" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="Axis1Alm_L" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="Config_1" Source="" Memory="UserROM" Language="Binary" />
  </Binaries>
  <Libraries>
    <LibraryObject Name="Runtime" Source="Libraries.Runtime.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="sys_lib" Source="Libraries.sys_lib.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="AsIecCon" Source="Libraries.AsIecCon.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="astime" Source="Libraries.astime.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="AsARCfg" Source="Libraries.AsARCfg.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="AsBrStr" Source="Libraries.AsBrStr.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="snprintf" Source="UnitTest.Libraries.snprintf.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="IecCheck" Source="Libraries.IecCheck.lby" Memory="UserROM" Language="IEC" Debugging="true" />
    <LibraryObject Name="McBase" Source="Libraries.McBase.lby" Memory="UserROM" Language="binary" Debugging="true" />
    <LibraryObject Name="MpAxis" Source="Libraries.MpAxis.lby" Memory="UserROM" Language="binary" Debugging="true" />
    <LibraryObject Name="McPureVAx" Source="Libraries.McPureVAx.lby" Memory="UserROM" Language="binary" Debugging="true" />
    <LibraryObject Name="McAcpPar" Source="Libraries.McAcpPar.lby" Memory="UserROM" Language="binary" Debugging="true" />
    <LibraryObject Name="McAcpAx" Source="Libraries.McAcpAx.lby" Memory="UserROM" Language="binary" Debugging="true" />
    <LibraryObject Name="McAxis" Source="Libraries.McAxis.lby" Memory="UserROM" Language="binary" Debugging="true" />
    <LibraryObject Name="MpBase" Source="Libraries.MpBase.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="ArTextSys" Source="Libraries.ArTextSys.lby" Memory="UserROM" Language="binary" Debugging="true" />
    <LibraryObject Name="standard" Source="Libraries.standard.lby" Memory="UserROM" Language="binary" Debugging="true" />
    <LibraryObject Name="operator" Source="Libraries.operator.lby" Memory="UserROM" Language="binary" Debugging="true" />
    <LibraryObject Name="AsBrWStr" Source="Libraries.AsBrWStr.lby" Memory="UserROM" Language="binary" Debugging="true" />
    <LibraryObject Name="FileIO" Source="Libraries.FileIO.lby" Memory="UserROM" Language="binary" Debugging="true" />
    <LibraryObject Name="AsTCP" Source="Libraries.AsTCP.lby" Memory="UserROM" Language="binary" Debugging="true" />
    <LibraryObject Name="LoggingLib" Source="Libraries.LoggingLib.lby" Memory="UserROM" Language="ANSIC" Debugging="true" />
    <LibraryObject Name="ArEventLog" Source="Libraries.ArEventLog.lby" Memory="UserROM" Language="binary" Debugging="true" />
    <LibraryObject Name="UtMgr" Source="UnitTest.Libraries.UtMgr.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="UtWs" Source="UnitTest.Libraries.UtWs.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="UnitTest" Source="UnitTest.Libraries.UnitTest.lby" Memory="None" Language="ANSIC" Debugging="true" />
    <LibraryObject Name="arcoal" Source="" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="arssl" Source="" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="asepl" Source="" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="dataobj" Source="" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="mpalarmx" Source="" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="powerlnk" Source="" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="uacoalprv" Source="" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="aruser" Source="" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="mpaudit" Source="" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="asusb" Source="" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="mpfile" Source="" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="arproject" Source="" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="mpbackup" Source="" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="asiodiag" Source="" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="brsystem" Source="" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="mprecipe" Source="" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="mpuserx" Source="" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="arcert" Source="" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="ashw" Source="" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="aseth" Source="" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="mpreport" Source="" Memory="UserROM" Language="Binary" Debugging="true" />
  </Libraries>
</SwConfiguration>