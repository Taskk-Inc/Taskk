!include "MUI2.nsh"

Name "Taskk Profiler"
OutFile "Taskk-Profiler-x64-Installer.EXE"
InstallDir "C:\Program Files\Taskk Profiler"

# Use default images from NSIS
!define MUI_HEADERIMAGE

# Header
!define MUI_PAGE_HEADER_TEXT "Taskk Inc Presents:"
!define MUI_PAGE_HEADER_SUBTEXT "Taskk Profiler (c) 2024"

# Welcome Page
!define MUI_WELCOMEPAGE_TITLE "Taskk Profiler"
!define MUI_WELCOMEPAGE_TEXT "An advanced multi-language software profiler made in C++ with Qt."
!insertmacro MUI_PAGE_WELCOME

# License Page
!define MUI_LICENSEPAGE_TEXT_TOP "This software is distributed under the MIT License :"
!define MUI_LICENSEPAGE_TEXT_BOTTOM "Please read and agree with this license to continue the installation."
!define MUI_LICENSEPAGE_CHECKBOX
!define MUI_LICENSEPAGE_CHECKBOX_TEXT "I agree."
!insertmacro MUI_PAGE_LICENSE "LICENSE"

# Installation Page
!insertmacro MUI_PAGE_INSTFILES


# Finish Page
!define MUI_FINISHPAGE_TITLE "The installation has been completed."
!define MUI_FINISHPAGE_TEXT "You may now use Taskk Profiler"
!define MUI_FINISHPAGE_RUN "$INSTDIR\Taskk Profiler.exe"
!define MUI_FINISHPAGE_RUN_TEXT "Run Taskk Profiler."
!define MUI_FINISHPAGE_LINK "Taskk Profiler On Github"
!define MUI_FINISHPAGE_LINK_LOCATION "https://github.com/Taskk-Inc/Taskk"
!insertmacro MUI_PAGE_FINISH

# Language
!insertmacro MUI_LANGUAGE "English"

Section
    # Require admin rights
    UserInfo::GetAccountType
    Pop $0
    StrCmp $0 "Admin" +3
    MessageBox MB_OK "This installer requires administrator permissions. Please restart the application as an administrator."
    Quit
	# Copy binaries
	SetOutPath $INSTDIR
	File /r "bin\"
	# Create the scripts directory
	# CreateDirectory "$\"$INSTDIR\scripts$\""
    # Write the uninstaller
    SetOutPath $INSTDIR
    WriteUninstaller "Taskk Profiler Uninstaller.exe"
    # Write start menu items
	CreateDirectory "$SMPROGRAMS\Taskk Profiler"
    CreateShortcut "$SMPROGRAMS\Taskk Profiler\Taskk Profiler.lnk" "$INSTDIR\Taskk Profiler.exe"
	CreateShortcut "$SMPROGRAMS\Taskk Profiler\Uninstall Taskk Profiler.lnk" "$INSTDIR\Taskk Profiler Uninstaller.exe"
    # Write a control panel program entry in the registry
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Taskk Profiler" \
        "DisplayName" "Taskk Profiler"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Taskk Profiler" \
        "UninstallString" "$\"$INSTDIR\Taskk Profiler Uninstaller.exe$\""
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Taskk Profiler" \
        "InstallLocation" "$\"$INSTDIR$\""
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Taskk Profiler" \
        "Publisher" "Cesar Berriot"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Taskk Profiler" \
        "URLInfoAbout" "https://github.com/CesarBerriot/Taskk Profiler"
SectionEnd

Section "Uninstall"
    # Delete files
    RMDir /r "$INSTDIR"
    # Delete start menu items
	RMDir /r "$SMPROGRAMS\Taskk Profiler"
    # Delete registry keys
    DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Taskk Profiler"
SectionEnd