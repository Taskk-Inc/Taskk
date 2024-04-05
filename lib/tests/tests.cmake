macro(make_test NAME WILL_FAIL)
    add_executable(test.${NAME}.exec ${LIB_SOURCES} tests/src/${NAME}.cpp)
    add_test(test.${NAME} test.${NAME}.exec)
    set_tests_properties(test.${NAME} PROPERTIES WILL_FAIL ${WILL_FAIL})
endmacro()

# test common cases
make_test(utils.find_latest_ongoing_operation OFF)

# test invalid usage of the library
make_test(operations.attached_data.no_active_operation ON)
make_test(operations.end_non_existent_operation ON)
make_test(utils.find_non_existent_operation ON)
make_test(utils.find_outdated_operation ON)
