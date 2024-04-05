macro(make_test name)
    add_executable(test.${name}.exec ${LIB_SOURCES} tests/src/${name}.c++)
    add_test(test.${name} test.${name}.exec)
endmacro()

make_test(attached_data.no_active_operation)
set_tests_properties(test.attached_data.no_active_operation PROPERTIES WILL_FAIL ON)