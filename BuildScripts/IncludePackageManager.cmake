
set(HUNTER_ALLOW_SPACES_IN_PATH ON)

include( "${CMAKE_CURRENT_LIST_DIR}/HunterGate.cmake")
HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.19.108.tar.gz"
    SHA1 "56cf9f1d52296373dbcc0d0c9c2b5526a0815019"
    LOCAL # load `${CMAKE_CURRENT_LIST_DIR}/cmake/Hunter/config.cmake`
)