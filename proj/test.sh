
echo "runing test 1, simple"
./pipex f_infile "grep .c" "wc -w" f_outfile
< f_infile grep .c | wc -w > f_outfile2
diff f_outfile f_outfile2 -s

echo ""
echo "runing test 2, no outfile"
rm -fr f_outfile*
./pipex f_infile "grep .c" "wc -w" f_outfile
< f_infile grep .c | wc -w > f_outfile2
diff f_outfile f_outfile2 -s

echo ""
echo "runing test 1.1, wrong command, error expected"
rm -fr f_outfile*
./pipex f_infile "greep .c" "wc -w" f_outfile

echo ""
echo "runing test 1.2, ./ls, error expected"
rm -fr f_outfile*
./pipex f_infile "./ls" "wc -w" f_outfile

echo ""
echo "runing test 1.3, wrong permition, error expected"
chmod 200 f_infile
./pipex f_infile "grep .c" "wc -w" f_outfile
chmod 400 f_infile

echo ""
echo "runing test 3.1, multi pipes simple"
./pipex f_infile "grep ." "grep .c" "wc -w" f_outfile
< f_infile grep . | grep .c | wc -w > f_outfile2
diff f_outfile f_outfile2 -s