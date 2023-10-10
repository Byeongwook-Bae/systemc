message(STATUS "Post install config script :")

if (BIGINT_CONFIGURATION STREQUAL "TEMPLATE_CLASS_HAS_NO_BASE_CLASS")
  set ( MYDEF "SC_BIGINT_CONFIG_TEMPLATE_CLASS_HAS_NO_BASE_CLASS" )
endif()
if (BIGINT_CONFIGURATION STREQUAL "TEMPLATE_CLASS_HAS_STORAGE")
  set ( MYDEF "SC_BIGINT_CONFIG_TEMPLATE_CLASS_HAS_STORAGE" )
endif()
if (BIGINT_CONFIGURATION STREQUAL "BASE_CLASS_HAS_STORAGE")
  set ( MYDEF "SC_BIGINT_CONFIG_BASE_CLASS_HAS_STORAGE" )
endif()

set(MYCMD bash -c " sed -i -e 's/\\/\\/ #define ${MYDEF}/   #define ${MYDEF}/g' ${SC_INSTALL_INCLUDE_DIR}/sysc/datatypes/int/sc_nbdefs.h")
message(STATUS "Running: ${MYCMD}")
execute_process( COMMAND ${MYCMD} )
message(STATUS "BIGINT_CONFIGURATION: ${BIGINT_CONFIGURATION}")

set(MYCMD bash -c " sed -i -e 's/\\/\\/ #define SC_BASE_VEC_DIGITS BASE_VEC_DIGITS_CONFIG/   #define SC_BASE_VEC_DIGITS ${BASE_VEC_DIGITS_CONFIG}/g' ${SC_INSTALL_INCLUDE_DIR}/sysc/datatypes/int/sc_nbdefs.h")
message(STATUS "Running: ${MYCMD}")
execute_process( COMMAND ${MYCMD} )
message(STATUS "BASE_VEC_DIGITS CONFIGURATION: ${BASE_VEC_DIGITS_CONFIG}")