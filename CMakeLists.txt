cmake_minimum_required(VERSION 2.8.12)

project(dpp)

if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../sweet.hpp)
else()
message(fatel_error 
"The sweet.hpp folder needs to be located on the same level as the dpp folder")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}")

find_package(LLVM)

#pkg_check_modules(LLVM llvm)
#include_directories(${LLVM_INCLUDE_DIRS})
#link_directories(${LLVM_LIBRARY_DIRS})
#add_definitions(${LLVM_CFLAGS_OTHER})

## LLVM
#find_package(LLVM)
#
#if( NOT LLVM_FOUND )
#  message(FATAL_ERROR 
#	"LLVM package can't be found. Set CMAKE_PREFIX_PATH variable to LLVM's 
#	installation prefix.")
#endif()
#
#include_directories( ${LLVM_INCLUDE_DIRS} )
#link_directories( ${LLVM_LIBRARY_DIRS} )
#
#llvm_map_components_to_libraries(REQ_LLVM_LIBRARIES jit native)


set(INCLUDE_TESTS "true")
if(NOT ${INCLUDE_TESTS} MATCHES "true")
	add_definitions(-DSWEET_NO_UNITTEST)
else()
	add_definitions(-DSWEET_UNITTEST)
endif()

include_directories("../sweet.hpp")
include_directories("src/cmd")
include_directories("src/common")
include_directories("src/parser")
include_directories("src/lexer")
include_directories("src/llvmbackend")
include_directories("src/")

SET(GenCommon
	${CMAKE_SOURCE_DIR}/src/visitorinclude
	${CMAKE_SOURCE_DIR}/src/common/ast.cpp
	${CMAKE_SOURCE_DIR}/src/common/ast.hpp
	${CMAKE_SOURCE_DIR}/src/common/error.cpp
	${CMAKE_SOURCE_DIR}/src/common/error.hpp
	${CMAKE_SOURCE_DIR}/src/common/visitor.hpp
	${CMAKE_SOURCE_DIR}/src/common/multivisitor.cpp
	${CMAKE_SOURCE_DIR}/src/common/multivisitor.hpp
)

SET(GenVisitor
	${CMAKE_SOURCE_DIR}/src/common/outvisitor.cpp
	${CMAKE_SOURCE_DIR}/src/common/outvisitor.hpp
	${CMAKE_SOURCE_DIR}/src/common/dotvisitor.cpp
	${CMAKE_SOURCE_DIR}/src/common/dotvisitor.hpp
)

SET(GenParser
	${CMAKE_SOURCE_DIR}/src/parser/parser.cpp
	${CMAKE_SOURCE_DIR}/src/parser/parser.hpp
)

SET(RecdeGenOutput
	${GenCommon}
	${GenVisitor}
	${GenParser}
)

ADD_CUSTOM_COMMAND(
  OUTPUT ${RecdeGenOutput}
  COMMAND ../sweet.hpp/recde/build/recde -i dpp.js
	-ps ${CMAKE_SOURCE_DIR}/src/parser/parser.cpp
	-ph ${CMAKE_SOURCE_DIR}/src/parser/parser.hpp
	-ah ${CMAKE_SOURCE_DIR}/src/common/ast.hpp
	-as ${CMAKE_SOURCE_DIR}/src/common/ast.cpp
	-es ${CMAKE_SOURCE_DIR}/src/common/error.cpp
	-eh ${CMAKE_SOURCE_DIR}/src/common/error.hpp
	-vh ${CMAKE_SOURCE_DIR}/src/common/visitor.hpp
	-os ${CMAKE_SOURCE_DIR}/src/common/outvisitor.cpp
	-oh ${CMAKE_SOURCE_DIR}/src/common/outvisitor.hpp
	-ds ${CMAKE_SOURCE_DIR}/src/common/dotvisitor.cpp
	-dh ${CMAKE_SOURCE_DIR}/src/common/dotvisitor.hpp
	-ms ${CMAKE_SOURCE_DIR}/src/common/multivisitor.cpp
	-mh ${CMAKE_SOURCE_DIR}/src/common/multivisitor.hpp 
	-in ${CMAKE_SOURCE_DIR}/src/visitorinclude

    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} 
    DEPENDS dpp.js
)

## we have some extra modules here
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# cmd programm
set(dpp_sources 
	src/cmd/main.cpp
)

# common library
set(common_sources 
	src/common/token.cpp
	src/common/location.cpp
)

set(common_header 
	src/common/token.hpp
	src/common/location.hpp
)

# parser library
set(parser_sources 
	src/parser/parsertest1.cpp
)

set(parser_header 
)

# lexer library
set(lexer_sources 
	src/lexer/lexer.cpp
	src/lexer/numberconv.cpp
)

set(lexer_header 
	src/lexer/lexer.hpp
	src/lexer/numberconv.hpp
)

# llvm library
set(llvm_sources 
	src/llvmbackend/llvmvisitor.cpp
)

set(llvm_header 
	src/llvmbackend/llvmvisitor.hpp
)

# we love c++11 and a chatty compiler that comments on our code
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic --std=c++0x")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O1")

add_library(dppcommon SHARED ${GenCommon} 
	${common_sources} 
	${common_header}
)

add_library(dppvisitor SHARED ${GenVisitor} 
	${dppcommon}
)

add_library(dppparser SHARED ${GenParser} 
	${dppcommon} 
	${parser_sources} 
	${parser_header}
)

add_library(dpplexer SHARED 
	${lexer_sources} 
	${lexer_header} 
	${dppcommon}
)

add_library(dppllvm SHARED ${GenCommon}
	${llvm_sources}
	${llvm_header}
	${dppcommon}
)

set_target_properties(dppllvm PROPERTIES
	COMPILE_FLAGS ${LLVM_CFLAGS}
)

target_link_libraries(dppllvm ${LLVM_ALL_LIBS} pthread dl)

add_executable(dpp ${dpp_sources})
target_link_libraries(dpp dppcommon dppvisitor dppparser dpplexer dppllvm)
