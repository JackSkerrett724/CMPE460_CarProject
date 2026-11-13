# groups.cmake

# group lib
add_library(Group_lib OBJECT
  "${SOLUTION_ROOT}/../../lib/sysctl.c"
  "${SOLUTION_ROOT}/CarProject/adc12.c"
  "${SOLUTION_ROOT}/CarProject/camera.c"
  "${SOLUTION_ROOT}/CarProject/led.c"
  "${SOLUTION_ROOT}/CarProject/timers.c"
  "${SOLUTION_ROOT}/CarProject/uart.c"
  "${SOLUTION_ROOT}/CarProject/i2c.c"
  "${SOLUTION_ROOT}/CarProject/switches.c"
  "${SOLUTION_ROOT}/../../lib/lab4/I2C/oled.c"
)
target_include_directories(Group_lib PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
  "${SOLUTION_ROOT}/../../lib/lab6"
  "${SOLUTION_ROOT}/../../lib"
  "${SOLUTION_ROOT}/../../lib/lab5"
  "${SOLUTION_ROOT}/../../lib/lab2"
  "${SOLUTION_ROOT}/../../lib/lab4/I2C"
  "${SOLUTION_ROOT}/../../lib/lab1"
)
target_compile_definitions(Group_lib PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
add_library(Group_lib_ABSTRACTIONS INTERFACE)
target_link_libraries(Group_lib_ABSTRACTIONS INTERFACE
  ${CONTEXT}_ABSTRACTIONS
)
target_compile_options(Group_lib PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_lib PUBLIC
  Group_lib_ABSTRACTIONS
)

# group Source Group 1
add_library(Group_Source_Group_1 OBJECT
  "${SOLUTION_ROOT}/../../source/ti/devices/msp/m0p/startup_system_files/keil/startup_mspm0g350x_uvision.s"
  "${SOLUTION_ROOT}/CarProject/main.c"
)
target_include_directories(Group_Source_Group_1 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Group_Source_Group_1 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
add_library(Group_Source_Group_1_ABSTRACTIONS INTERFACE)
target_link_libraries(Group_Source_Group_1_ABSTRACTIONS INTERFACE
  ${CONTEXT}_ABSTRACTIONS
)
target_compile_options(Group_Source_Group_1 PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_Source_Group_1 PUBLIC
  Group_Source_Group_1_ABSTRACTIONS
)
set(COMPILE_DEFINITIONS
  _RTE_
  __MSPM0G3507__
)
cbuild_set_defines(AS_ARM COMPILE_DEFINITIONS)
set_source_files_properties("${SOLUTION_ROOT}/../../source/ti/devices/msp/m0p/startup_system_files/keil/startup_mspm0g350x_uvision.s" PROPERTIES
  COMPILE_FLAGS "${COMPILE_DEFINITIONS}"
)
