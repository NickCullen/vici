#-------------------------------------------------------------------------------------------
# Include Hunter Package manager
#-------------------------------------------------------------------------------------------
set(HUNTER_ROOT "${TEMP_VICI_HOME}CMake/Packages")
set(HUNTER_ALLOW_SPACES_IN_PATH ON)

### Hunter snapshot that will be used ###
include("${TEMP_VICI_HOME}CMake/HunterGate.cmake")
HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.19.108.tar.gz"
    SHA1 "56cf9f1d52296373dbcc0d0c9c2b5526a0815019"
    FILEPATH "${TEMP_VICI_HOME}CMake/config.cmake"
)
