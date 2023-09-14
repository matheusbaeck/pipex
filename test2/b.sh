PIPEPATH=../proj/pipex

echo ""
echo "runing test danrodri, wrong permition outfile, error expected"
chmod 000 "f_infile"
$PIPEPATH f_infile "grep .c" "wc -w" ls f_outfile
echo "original"
< f_infile grep .c | wc -w | ls > f_outfile2
chmod 777 "f_infile"
diff -s f_outfile f_outfile2