# test_error_handling
touch no_permisson.tmp
chmod 000 no_permisson.tmp

# Launching tests
./test

# Cleaning
rm -f *.tmp

# minishell_tester
make all
git clone https://github.com/LucasKuhn/minishell_tester.git
cd minishell_tester
./tester
cd ..
