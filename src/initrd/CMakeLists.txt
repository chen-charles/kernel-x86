add_custom_target(initrd ALL COMMAND tar "cvf" "${PROJECT_BINARY_DIR}/initrd" "-C" "${CMAKE_CURRENT_SOURCE_DIR}/initrd" ".")
