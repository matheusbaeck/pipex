
echo "runing test 1, simple"
./pipex f_infile "grep .c" "wc -w" f_outfile
< f_infile grep .c | wc -w > f_outfile2

echo "runing test 2, no outfile"
rm -fr f_outfile*
./pipex f_infile "grep .c" "wc -w" f_outfile
< f_infile grep .c | wc -w > f_outfile2


echo "runing test 2"
rm -fr f_outfile*
./pipex f_infile "grep .c" "wc -w" f_outfile
< f_infile grep .c | wc -w > f_outfile2

echo "runing test 3, wrong command"
rm -fr f_outfile*
./pipex f_infile "greep .c" "wc -w" f_outfile
< f_infile greep .c | wc -w > f_outfile2


echo "runing test 4, multi pipes simple"
./pipex f_infile "grep ." "grep .c" "wc -w" f_outfile
< f_infile grep . | grep .c | wc -w > f_outfile2
