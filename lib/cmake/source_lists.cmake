set(LIB_API_SOURCES
        # api declarations
        include/taskk.h
        include/taskk.hpp
        include/taskk/c/taskk_api.h
        include/taskk/cxx/include_all.hpp
        include/taskk/cxx/data_types/data_types.hpp
        include/taskk/cxx/macros/make_scope_operation.hpp
        include/taskk/cxx/macros/taskk_api.hpp
        include/taskk/cxx/macros/utils.hpp
        # api definitions
        src/taskk/c_api.cpp
        src/taskk/cxx_wrapper.cpp
        src/taskk/cxx/data_types.cpp)

set(LIB_SOURCES
        # logic
        src/logic/logic.cpp
        src/logic/logic.hpp
        # data types
        src/data_types/data_types.hpp
        # globals
        src/globals/globals.hpp
        # utils
        src/utils/utils.cpp
        src/utils/utils.hpp
        # i/o
        src/io/io.cpp
        src/io/io.hpp
        #json
        src/json/json.cpp
        src/json/json.hpp
        #macros
        src/macros/custom_types.hpp
        src/macros/functions.hpp
        # templates
        include/taskk/cxx/templates/attach_auto_overloads.hpp)