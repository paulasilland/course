mkdir testing
cd testing

n_failed=0
n_passed=0

check_test (){
  if [ $1 -ne 0 ]; then
        echo "### ...failed...."
        n_failed=`expr $n_failed + 1`
  else
        echo "### ...passed...."
        n_passed=`expr $n_passed + 1`
  fi
}


echo "### Test 1: Deleting a single file"
touch test1.txt
rmsf test1.txt

check_test $?

echo "passed: $n_passed out of 1."
echo "failed: $n_failed out of 1."

cd ..
rm -r testing