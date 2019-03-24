; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "Akks"
#define MyAppVersion "1.1"
#define MyAppPublisher "Tverd29"
#define MyAppURL "https://vk.com/id17172613"
#define MyAppExeName "Akk.exe"
#define MyAppIconName "akks.ico"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{A8626C92-E351-4541-B7DB-B52E21BE1263}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
AppVerName={#MyAppName}_{#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
; DefaultDirName={pf}\{#MyAppName}
DefaultDirName=C:\{#MyAppName}
DefaultGroupName={#MyAppName}
AllowNoIcons=yes
OutputDir=V:\Git\First\Installers\Akks_{#MyAppVersion}
OutputBaseFilename=Akks setup
PrivilegesRequired = admin
SetupIconFile=V:\Git\First\3rdParty\akks.ico
Compression=lzma
SolidCompression=yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "russian"; MessagesFile: "compiler:Languages\Russian.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked; OnlyBelowVersion: 0,6.1

[Files]
Source: "V:\Git\First\build-Akk-Desktop_Qt_5_9_5_MSVC2015_32bit-Release\release\Akk.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "V:\Git\First\3rdParty\akks.ico"; DestDir: "{app}"; Flags: ignoreversion
Source: "V:\Git\First\3rdParty\qt_libs\D3Dcompiler_47.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "V:\Git\First\3rdParty\qt_libs\libEGL.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "V:\Git\First\3rdParty\qt_libs\libGLESV2.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "V:\Git\First\3rdParty\qt_libs\opengl32sw.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "V:\Git\First\3rdParty\qt_libs\Qt5Core.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "V:\Git\First\3rdParty\qt_libs\Qt5Gui.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "V:\Git\First\3rdParty\qt_libs\Qt5Svg.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "V:\Git\First\3rdParty\qt_libs\Qt5Widgets.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "V:\Git\First\3rdParty\qt_libs\iconengines\*"; DestDir: "{app}\iconengines"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "V:\Git\First\3rdParty\qt_libs\imageformats\*"; DestDir: "{app}\imageformats"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "V:\Git\First\3rdParty\qt_libs\platforms\*"; DestDir: "{app}\platforms"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "V:\Git\First\3rdParty\qt_libs\translations\*"; DestDir: "{app}\translations"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "V:\Git\First\3rdParty\imgs\icons\*"; DestDir: "{app}\icons"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "V:\Git\First\Akk\Language\*"; DestDir: "{app}\language"; Flags: ignoreversion recursesubdirs createallsubdirs
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName};"
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{group}\{cm:ProgramOnTheWeb,{#MyAppName}}"; Filename: "{#MyAppURL}"
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}";IconFilename: "{app}\akks.ico"; Tasks: desktopicon
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: quicklaunchicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

