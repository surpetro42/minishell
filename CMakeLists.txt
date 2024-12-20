cmake_minimum_required(VERSION 3.26)
project(minishell C)

# Set the C standard to C99
set(CMAKE_C_STANDARD 99)

# Compiler flags
set(CMAKE_C_FLAGS "-Wall -Werror -Wextra")
# Add extra debugging flags if needed
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g3 -fsanitize=address")

# Define the source files and header files
set(SRC_FILES init.c env_struct_revert.c dollar.c dollar_2.c exec_compose.c builtin.c regular_exec.c subshell.c
        exec_and_pipes.c cleaners.c syntax_check.c tools_1.c tools_2.c tools_3.c wildcards_1.c wildcards_2.c
        block_manipulation.c h_doc_processor.c tokenizer_tools_1.c tokenizer_tools_2.c tokenizer_tools_3.c tokenizer.c
        builtins_minishel/src/functions/dollar.c builtins_minishel/src/functions_utils/utils_dollar/dollar_utils_0.c
        builtins_minishel/src/functions_utils/utils_exit/exit_utils_0.c
        builtins_minishel/src/functions_utils/utils_dollar/dollar_utils_1.c
        builtins_minishel/src/functions_utils/utils_dollar/dollar_utils_2.c
        builtins_minishel/src/functions_utils/utils_dollar/dollar_utils_3.c
        builtins_minishel/src/functions_utils/utils_dollar/dollar_utils_4.c
        builtins_minishel/src/functions_utils/utils_dollar/dollar_utils_5.c
        builtins_minishel/src/functions_utils/utils_export/export_utils_0.c
        builtins_minishel/src/functions_utils/utils_export/export_utils_1.c
        builtins_minishel/src/functions_utils/utils_export/export_utils_2.c
        builtins_minishel/src/functions_utils/utils_export/export_utils_3.c
        builtins_minishel/src/functions_utils/utils_cd/cd_utils_0.c
        builtins_minishel/src/functions_utils/utils_cd/cd_utils_1.c
        builtins_minishel/src/functions/echo.c builtins_minishel/src/functions/cd.c
        builtins_minishel/src/functions/export.c builtins_minishel/src/functions/env.c
        builtins_minishel/src/functions/unset.c builtins_minishel/src/functions/pwd.c
        builtins_minishel/src/functions/exit.c builtins_minishel/src/env/duplicate_env.c
        builtins_minishel/src/free_builtins/free_dollar.c builtins_minishel/src/free_builtins/free_exp_env_list.c
        builtins_minishel/src/free_builtins/free_export.c
        regular_exec_2.c
)

set(HEADER_FILES minishel.h)

# Readline paths
set(READLINE_DIR "${CMAKE_SOURCE_DIR}/readline-8.2")
set(READLINE_INCLUDE "${CMAKE_SOURCE_DIR}/readline/include")
set(READLINE_LIB "${CMAKE_SOURCE_DIR}/readline/lib")

# Include directories
include_directories(${READLINE_INCLUDE})

# Link libraries (readline, history, libft, and ncurses)
add_library(libft STATIC IMPORTED)
set_target_properties(libft PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/libft/libft.a")

add_executable(minishel ${SRC_FILES})

# Link against the libraries, including ncurses
target_link_libraries(minishel ${READLINE_LIB}/libreadline.a ${READLINE_LIB}/libhistory.a libft ncurses)

# Custom commands to build Readline
add_custom_target(build_readline
        COMMAND ./configure --prefix=${CMAKE_SOURCE_DIR}/readline && make && make install
        WORKING_DIRECTORY ${READLINE_DIR}
)

# Custom target for building libft
add_custom_target(build_libft
        COMMAND make
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/libft
)

# Ensure readline and libft are built before the main executable
add_dependencies(minishel build_readline build_libft)

