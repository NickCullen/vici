setx -m VICI_HOME %~dp0
setx -m VICI_TOOLS %VICI_HOME%Tools\Scripts
setx -m VICI_PYTHON %VICI_HOME%Tools\Windows\Python

setx -m PATH "%PATH%;%%VICI_PYTHON%%;%%VICI_TOOLS%%"