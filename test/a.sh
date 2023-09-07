PIPEPATH=/Users/mamagalh/pipex/proj/pipex

echo ""
echo "runing test 1.1, wrong command, error expected"
rm -fr f_outfile*
$PIPEPATH   f_infile "greep -v .c" "wrong" f_outfile
< f_infile greep -v .c | wrong > f_outfile2
diff f_outfile f_outfile2 -s