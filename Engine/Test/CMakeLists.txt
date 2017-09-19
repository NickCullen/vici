BEGIN_MODULE()

add_executable(Test ${MODULE_SOURCES})

REF_MODULES(Test Core Platform)
