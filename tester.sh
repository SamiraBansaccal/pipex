#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[0;33m'
NC='\033[0m' # No Color

run_test() {
    local test_num=$1
    local input_file=$2
    local cmd1=$3
    local cmd2=$4
    
    local title="$input_file $cmd1 $cmd2"
    
    echo -e "${YELLOW}Running Test $test_num: $title${NC}"
    
    if [ -f "$input_file" ]; then
        < $input_file $cmd1 | $cmd2 > shell_out 2> shell_err
    else
        echo "Input file not found" > shell_out
        echo "Input file not found" > shell_err
    fi
    
    ./pipex "$input_file" "$cmd1" "$cmd2" "out$test_num" 2> pipex_err
    
    if diff shell_out "out$test_num" > /dev/null && diff shell_err pipex_err > /dev/null; then
        echo -e "${GREEN}=== Test $test_num: $title ===${NC}" >> test_results.txt
        echo -e "${GREEN}Test $test_num: Passed${NC}"
    else
        echo -e "${RED}=== Test $test_num: $title ===${NC}" >> test_results.txt
        echo -e "${RED}Test $test_num: Failed${NC}"
    fi
    
    echo "Shell output:" >> test_results.txt
    cat shell_out >> test_results.txt
    echo "Shell error:" >> test_results.txt
    cat shell_err >> test_results.txt
    echo "Pipex output:" >> test_results.txt
    cat "out$test_num" >> test_results.txt
    echo "Pipex error:" >> test_results.txt
    cat pipex_err >> test_results.txt
    echo "" >> test_results.txt
    
    rm -f shell_out shell_err pipex_err "out$test_num"
}

rm -f test_results.txt
echo "test content" > exist_input

echo -e "${YELLOW}Compiling mandatory part...${NC}"
make

run_test 1 "non_exist_input" "cat /dev/random" "head -n 5"
run_test 2 "exist_input" "grep test" "wc -w"
run_test 3 "exist_input" "ls -l" "wc -l"
run_test 4 "non_exist_input" "ls" "wc -l"
run_test 5 "exist_input" "cat" "grep a"
run_test 6 "exist_input" "cat" "wc -l"
run_test 7 "non_exist_input" "ls" "wc"
run_test 8 "exist_input" "/bin/cat" "wc -c"

echo -e "${YELLOW}Cleaning and compiling bonus part...${NC}"
make fclean
make bonus

run_test 9 "non_exist_input" "cat /dev/random" "head -n 5"
run_test 10 "exist_input" "cat" "grep test" "wc -w"
run_test 11 "non_exist_input" "cat /dev/random" "wc" "ls"
run_test 12 "exist_input" "cat" "wc -cl" "grep 0" "sort"
run_test 13 "non_exist_input" "ls" "grep a" "wc -l" "sort" "uniq"
run_test 14 "exist_input" "cat" "wc -l" "sort" "uniq"
run_test 15 "non_exist_input" "ls" "wc" "sort" "cat"
run_test 16 "exist_input" "/bin/cat" "grep test" "wc -c"

echo -e "${YELLOW}Cleaning up...${NC}"
make fclean
rm -f exist_input

echo -e "${YELLOW}Tests completed. Results are in test_results.txt${NC}"