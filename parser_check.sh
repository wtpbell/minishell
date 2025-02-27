#!/bin/bash

# Color definitions
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

# Test counters
TOTAL=0
PASSED=0

# Helper function to extract token chain and AST
extract_token_chain() {
    local output="$1"
    echo "$output" | grep "Token Chain:" | sed 's/.*Token Chain: //'
}

extract_ast() {
    local output="$1"
    echo "$output" | grep -A 10 "After parse_complete_bonus:"
}

# Test function with special handling for empty inputs
test_parser() {
    local input="$1"
    local description="$2"
    local expect_output="${3:-1}"  # 1 means expect output, 0 means don't expect output
    ((TOTAL++))

    echo -e "\n${YELLOW}Test #$TOTAL: $description${NC}"
    echo -e "Input: '$input'"

    # Get minishell output
    local output=$(echo "$input" | ./minishell)
    local token_chain=$(extract_token_chain "$output")
    local ast=$(extract_ast "$output")

    # For empty/whitespace inputs, we expect no token chain or AST
    if [ "$expect_output" -eq 0 ]; then
        if [ -z "$token_chain" ] && [ -z "$ast" ]; then
            echo -e "${GREEN}✓ Test passed (Empty input handled correctly)${NC}"
            ((PASSED++))
            return 0
        else
            echo -e "${RED}❌ Test failed (Expected no output for empty input)${NC}"
            return 1
        fi
    fi

    # For normal inputs, we expect both token chain and AST
    echo -e "${BLUE}Token Chain:${NC}"
    echo "$token_chain"
    echo -e "${BLUE}AST Structure:${NC}"
    echo "$ast"

    if [ -n "$token_chain" ] && [ -n "$ast" ]; then
        echo -e "${GREEN}✓ Test passed${NC}"
        ((PASSED++))
        return 0
    else
        echo -e "${RED}❌ Test failed${NC}"
        return 1
    fi
}

echo "=== Starting Comprehensive Parser Tests ==="

# 1. Simple Commands
echo -e "\n${BLUE}=== Simple Commands ===${NC}"
test_parser "/bin/ls" "Absolute path simple command"
test_parser "/bin/pwd" "Absolute path pwd"
test_parser "/bin/echo hello" "Absolute path with argument"
test_parser "" "Empty command" 0       # Expect no output
test_parser "   " "Spaces only" 0      # Expect no output
test_parser "	" "Tabs only" 0        # Expect no output

# 2. Arguments
echo -e "\n${BLUE}=== Arguments ===${NC}"
test_parser "/bin/ls -l" "Single argument"
test_parser "/bin/ls -la" "Multiple combined arguments"
test_parser "/bin/ls -l -a -h" "Multiple separate arguments"
test_parser "/usr/bin/grep hello test.txt" "Command with multiple arguments"

# 3. Echo Tests
echo -e "\n${BLUE}=== Echo Command ===${NC}"
test_parser "echo hello world" "Basic echo"
test_parser "echo testing spaces" "Echo with spaces"
test_parser "echo -n hello" "Echo with -n option"
test_parser "echo -n \"no newline\"" "Echo -n with quotes"
test_parser "echo hello      world" "Echo with multiple spaces"

# 4. Quotes
echo -e "\n${BLUE}=== Quote Handling ===${NC}"
test_parser "echo \"hello world\"" "Double quotes"
test_parser "echo \"  multiple   spaces  \"" "Double quotes with spaces"
test_parser "echo \"cat lol.c | cat > lol.c\"" "Double quotes with operators"
test_parser "echo 'hello world'" "Single quotes"
test_parser "echo '  multiple   spaces  '" "Single quotes with spaces"
test_parser "echo '\$USER'" "Single quotes with variables"
test_parser "echo \"hello 'world'\"" "Nested quotes"
test_parser "echo 'hello \"world\"'" "Nested quotes reversed"

# 5. Environment Variables
echo -e "\n${BLUE}=== Environment Variables ===${NC}"
test_parser "echo \$PATH" "Basic variable expansion"
test_parser "echo \"\$PATH\"" "Variable in double quotes"
test_parser "echo '\$PATH'" "Variable in single quotes"
test_parser "echo \$NON_EXISTENT" "Non-existent variable"

# 6. Redirections
echo -e "\n${BLUE}=== Redirections ===${NC}"
test_parser "echo hello > file1" "Output redirection"
test_parser "cat < file1" "Input redirection"
test_parser "echo append >> file1" "Append redirection"
test_parser "cat < input > output" "Combined redirections"
test_parser "cat << EOF" "Heredoc"

# 7. Pipes
echo -e "\n${BLUE}=== Pipes ===${NC}"
test_parser "ls | grep a" "Simple pipe"
test_parser "cat file | grep hello | wc -l" "Multiple pipes"
test_parser "ls | grep a | sort | uniq" "Complex pipeline"
test_parser "echo hello | cat | cat | cat" "Long pipeline"

# 8. Bonus Features
echo -e "\n${BLUE}=== Bonus Features ===${NC}"
test_parser "ls && echo success" "AND operator"
test_parser "ls || echo failed" "OR operator"
test_parser "ls *.c" "Wildcard"
test_parser "(ls)" "Simple parentheses"
test_parser "((ls) && echo a) || echo b" "Nested parentheses"

# 9. Complex Combinations
echo -e "\n${BLUE}=== Complex Combinations ===${NC}"
test_parser "echo hello > file && cat < file | grep hello > output" "Complex redirections with AND"
test_parser "ls | grep a > output && cat output | wc -l" "Pipes with redirections and AND"
test_parser "(ls && echo test) | grep a" "Parentheses with pipe"
test_parser "ls *.c && echo \"found\" || echo \"not found\"" "Wildcards with logical operators"

# Final Results
echo -e "\n=== Test Results ==="
echo -e "Total tests: $TOTAL"
echo -e "Passed: ${GREEN}$PASSED${NC}"
echo -e "Failed: ${RED}$((TOTAL-PASSED))${NC}"
echo "Success rate: $(( (PASSED * 100) / TOTAL ))%"

# Memory leak check reminder
echo -e "\n${BLUE}Don't forget to check for memory leaks:${NC}"
echo "Run: valgrind --leak-check=full ./minishell"



echo $?HELLO
