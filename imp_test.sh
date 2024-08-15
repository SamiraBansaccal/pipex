#!/bin/bash

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
NC='\033[0m' # No Color

l1="======================================================================================="
l2="---------------------------------------------------------------------------------------"

# Function to run a test
run_test() {
    local test_name="$1"
    local command="$2"
    local expected_output_file="expected_output.txt"
    local actual_output_file="actual_output.txt"

    echo -e "\n${PURPLE}==============>Test: ${test_name}${NC}"
    echo -e "${YELLOW}Command: ${command}${NC}"
    
    # Run the expected command
    eval "$command" > "$expected_output_file" 2>/dev/null

    # Run your pipex program
    ./pipex "${@:3}" > "$actual_output_file" 2>&1

    # Compare outputs
    if diff -q "$expected_output_file" "$actual_output_file" >/dev/null; then
        echo -e "${GREEN}Test passed!${NC}"
    else
        echo -e "${RED}Test failed. Differences:${NC}"
        echo -e "${YELLOW}Expected output:${NC}"
        cat "$expected_output_file"
        echo -e "\n${YELLOW}Actual output:${NC}"
        cat "$actual_output_file"
        echo -e "\n${YELLOW}Diff:${NC}"
        diff -u "$expected_output_file" "$actual_output_file"
    fi
    
    # Clean up
    rm -f "$expected_output_file" "$actual_output_file"
}

echo -e "$RED$l1\n"
echo -e "\t\t\tPIPEX TESTER"
echo -e "\n$l1$NC\n"

# Clean and compile mandatory part
echo -e "${YELLOW}Cleaning previous build...${NC}"
make fclean

echo -e "\n${YELLOW}Compiling pipex (mandatory part)...${NC}"
make
echo -e "$RED$l2$NC"

# Create test files
echo "This is a test file" > infile
echo "Another test file" > infile2

echo -e "${YELLOW}Running tests for mandatory part...${NC}"

# Run mandatory tests
run_test "Simple pipe" "< infile cat | wc -l" "infile" "cat" "wc -l" "outfile"
run_test "Grep and wc" "< infile grep test | wc -w" "infile" "grep test" "wc -w" "outfile"
run_test "Non-existent command" "< infile nonexistentcmd | wc -l" "infile" "nonexistentcmd" "wc -l" "outfile"
run_test "Non-existent input file" "< nonexistentfile cat | wc -l" "nonexistentfile" "cat" "wc -l" "outfile"

# Clean and compile bonus part
echo -e "\n${YELLOW}Cleaning previous build...${NC}"
make fclean

echo -e "\n${YELLOW}Compiling pipex (bonus part)...${NC}"
make bonus
echo -e "$RED$l2$NC"

echo -e "${YELLOW}Running tests for bonus part...${NC}"

# Run bonus tests
run_test "Multiple pipes" "< infile cat | grep test | wc -w" "infile" "cat" "grep test" "wc -w" "outfile"
run_test "Four commands" "< infile cat | grep test | tr a-z A-Z | wc -w" "infile" "cat" "grep test" "tr a-z A-Z" "wc -w" "outfile"

# Here_doc test
run_test "Here_doc" "cat << EOF | sed 's/a/A/g'
hello
world
this is a test
EOF" "here_doc" "EOF" "cat" "sed 's/a/A/g'" "outfile"

# Clean up
rm -f infile infile2 outfile

echo -e "\n${YELLOW}All tests completed.${NC}"

# Final clean up
echo -e "\n${YELLOW}Cleaning up...${NC}"
make fclean

echo -e "\n${GREEN}Testing complete!${NC}"