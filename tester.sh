#!/bin/bash

# Fonction pour exécuter un test
run_test() {
    local test_num=$1
    local input_file=$2
    local cmd1=$3
    local cmd2=$4
    
    echo "=== Test $test_num ===" >> test_results.txt
    echo "Shell:" >> test_results.txt
    bash -c "< $input_file $cmd1 | $cmd2" 2>> test_results.txt >> test_results.txt
    echo "Pipex:" >> test_results.txt
    ./pipex "$input_file" "$cmd1" "$cmd2" "out$test_num" 2>> test_results.txt
    cat "out$test_num" >> test_results.txt
    echo "" >> test_results.txt
}

# Préparation
rm -f test_results.txt out*
echo "test" > exist_input

# Exécution des tests
run_test 1 "non_exist_input" "cat /dev/random" "wc"
run_test 2 "exist_input" "catds /dev/random" "ls"
run_test 3 "non_exist_input" "ls" "wc"
run_test 4 "exist_input" "csdfat" "wsdfc -cl"
run_test 5 "non_exist_input" "/bin/catsdc" "wcss -cl"
run_test 6 "non_exist_input" "sleep 1" "sleep 1"
run_test 7 "exist_input" "/bin/caqwdt" "/bin/lsqwd -ls"
run_test 8 "exist_input" "/srcs/a.out" "ls"

# Comparaison des résultats
echo "Différences entre Shell et Pipex :"
diff test_results.txt <(sed 's/Shell:/Pipex:/' test_results.txt | sort) || echo "Aucune différence trouvée."

# Nettoyage
rm -f exist_input out*