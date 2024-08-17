#!/bin/bash

l1="======================================================================================="
l2="---------------------------------------------------------------------------------------\n"
GREEN="\033[38;2;57;181;74m"
RED="\033[38;2;222;56;43m"
BLUE="\033[38;2;34;183;235m"
YELLOW="\033[38;2;255;176;0m"
PURPLE="\033[38;2;255;105;180m"
WHITE="\033[1;37m"
RESET="\033[0m"

printf "\n\n\n\n${GREEN}test error handling on multi pipe:${RESET}"
printf "$RED$l2$RESET"

make fclean
printf "${YELLOW}[make] :${RESET} your pipex: ${PURPLE}Bonus${RESET}\n"
make bonus
printf "$RED$l2$RESET"

if ! [ -f "./pipex" ]; then
    printf "${YELLOW}Error :${RESET} No such file or directory: ${PURPLE}pipex${RESET}\n" >&2
    exit
fi

echo "Test content for input file" > in_file

run_test() {
    test_name=$1
    shell_command=$2
    shift 2
    pipex_args=$@

    printf "${PURPLE}==============>$test_name${RESET}\n"
    printf "${WHITE}Shell command: $shell_command${RESET}\n"
    printf "${WHITE}Pipex command: ./pipex $pipex_args${RESET}\n"

    echo -e "${YELLOW}Shell output:${RESET}"
    eval "$shell_command" 2>&1
    shell_exit=$?
    echo "Shell exit code: $shell_exit"
    
    echo -e "${BLUE}Pipex output:${RESET}"
    ./pipex $pipex_args 2>&1
    pipex_exit=$?
    echo "Pipex exit code: $pipex_exit"
    
    if [ $shell_exit -eq $pipex_exit ]; then
        printf "${GREEN}[OK]${RESET}\n"
    else
        printf "${RED}[KO]${RESET}\n"
    fi
    printf "$RED$l2$RESET"
}

# Test 1
run_test "Test 1" \
    "< non_exist_input cat /dev/random | head -n 5" \
    '"non_exist_input" "cat /dev/random" "head -n 5" "outfile"'

# Test 2
run_test "Test 2" \
    "< in_file catds /dev/random | ls | wc -l" \
    '"in_file" "catds /dev/random" "ls" "wc -l" "outfile"'

# Test 3
run_test "Test 3" \
    "< non_exist_input cat /dev/random | wc | ls" \
    '"non_exist_input" "cat /dev/random" "wc" "ls" "outfile"'

# Test 4
run_test "Test 4" \
    "< in_file csfat | wc -cl | wasdc | grep 0 | sort | cat" \
    '"in_file" "csfat" "wc -cl" "wasdc" "grep 0" "sort" "cat" "outfile"'

# Test 5
run_test "Test 5" \
    "< non_exist_input sleep 1 | sleep 1 | sleep 1 | sleep 1 | sleep 1 | sleep 1 | sleep 1" \
    '"non_exist_input" "sleep 1" "sleep 1" "sleep 1" "sleep 1" "sleep 1" "sleep 1" "sleep 1" "outfile"'

# Nettoyage
rm -f in_file outfile

# Terminer tous les processus en arrière-plan
for i in $(ps | grep -v zsh | grep -v TIME | grep -v tester.sh | cut -d" " -f 1); do
    kill -9 $i &> /dev/null
done