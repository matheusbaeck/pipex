PIPEPATH=../proj/pipex

echo "runing test 1, simple"
$PIPEPATH  f_infile "grep .c" "wc -w" f_outfile
< f_infile grep .c | wc -w > f_outfile2
diff f_outfile f_outfile2 -s

echo ""
echo "runing test 2, no outfile"
rm -fr f_outfile*
$PIPEPATH   f_infile "grep -v .c" "cat" f_outfile
< f_infile grep -v .c | cat > f_outfile2
diff f_outfile f_outfile2 -s

echo ""
echo "runing test 1.1, wrong command, error expected"
$PIPEPATH   f_infile "greep -v .c" "wrong" f_outfile
< f_infile greep -v .c | wrong > f_outfile2
diff f_outfile f_outfile2 -s

echo ""
echo "runing test 1.2, wrong permition, error expected"
chmod 200 f_infile
$PIPEPATH   f_infile ls "grep .c" "wc" f_outfile
< f_infile ls | grep .c | wc > f_outfile2
diff f_outfile f_outfile2 -s
chmod 400 f_infile

echo ""
echo "runing test 1.3, ./ls, error expected"
$PIPEPATH   f_infile "./ls" "wc -w" ls f_outfile
echo "original"
< f_infile ./ls | "wc -w" | ls >f_outfile2
diff f_outfile f_outfile2 -s

echo ""
echo "runing test 3.1, multi pipes simple"
$PIPEPATH   f_infile "grep ." "grep .c" "wc -w" f_outfile
< f_infile grep . | grep .c | wc -w > f_outfile2
diff f_outfile f_outfile2 -s

echo ""
echo "runing test 5.1, hakin 1, 3 error expected"
$PIPEPATH   f_infile "jdgsfhdsg" "shdusah" "udhubsa" "/bin/ls" f_outfile
< f_infile jdgsfhdsg | shdusah | udhubsa | /bin/ls > f_outfile2
diff f_outfile f_outfile2 -s

echo ""
echo "runing test 5.2, hakin 2, 3 error expected"
$PIPEPATH   f_infile "cat /dev/urandom" "head -1" f_outfile && cat f_outfile

echo ""
echo "runing test danrodri, wrong permition outfile, error expected"
chmod 000 f_infile
$PIPEPATH   f_infile "grep .c" "wc -w" ls f_outfile
echo "original"
< f_infile grep .c | wc -w | ls >f_outfile2
chmod 777 f_infile
diff f_outfile f_outfile2 -s

echo ""
echo "extra error expected"
env -i $PIPEPATH   f_infile "jdgsfhdsg" "shdusah" "udhubsa" "/bin/ls" f_outfile
echo "original"
env -i < f_infile jdgsfhdsg | shdusah | udhubsa | /bin/ls > f_outfile2
diff f_outfile f_outfile2 -s

echo ""
echo "extra error expected"
env -i $PIPEPATH f_infile "jdgsfhdsg" "shdusah" "udhubsa" "/bin/ls" f_outfile
echo "original"
env -i < f_infile jdgsfhdsg | shdusah | udhubsa | /bin/ls > f_outfile2
diff f_outfile f_outfile2 -s

echo ""
echo "extra error expected"
chmod 000 f_infile
env -i $PIPEPATH f_infile "/bin/ls" "/bin/cat" "/bin/cat" "/bin/cat" f_outfile
echo "original"
env -i < f_infile /bin/ls | /bin/cat | /bin/cat | /bin/cat | /bin/cat  > f_outfile2
chmod 777 f_infile
diff f_outfile f_outfile2 -s


# cat /dev/urandom | head -1

# bash-3.2$ fjdgsfhdsghdahdgsahjdshsa|ls -la > out

# void	leaks(void)
# {
# 	system("leaks -q pipex");
# } atexit(leaks);
