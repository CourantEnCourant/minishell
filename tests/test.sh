# test_error_handling
touch no_permisson.tmp
chmod 000 no_permisson.tmp

# Launching tests
./test

# Cleaning
rm -f *.tmp
