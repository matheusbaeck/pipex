#! /bin/bash

function test {
	< $1 $2 $3 > bash
	./pipex $1 $2 $3 $4
	diff bash $4
	if [[ $? = 0]]; then
		echo OK
	else
		echo KO
	fi;
}

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

# cat /dev/urandom | head -1

# bash-3.2$ fjdgsfhdsghdahdgsahjdshsa|ls -la > out
# bash: fjdgsfhdsghdahdgsahjdshsa: command not found
# bash-3.2$ cat out
# total 128
# drwxr-xr-x  16 mamagalh  2019    544 Aug  4 20:09 .
# drwxr-xr-x   7 mamagalh  2019    238 Aug  4 17:42 ..
# -rw-r--r--   1 mamagalh  2019   1301 Aug  4 17:52 Makefile
# -r--------   1 mamagalh  2019    819 Aug  4 18:07 f_infile
# -rw-r--r--   1 mamagalh  2019      9 Aug  4 19:01 f_outfile
# -rw-r--r--   1 mamagalh  2019      9 Aug  4 19:01 f_outfile2
# drwxr-xr-x  50 mamagalh  2019   1700 Aug  4 19:06 libft
# -rw-r--r--   1 mamagalh  2019   2241 Aug  4 20:08 main.c
# -rw-r--r--   1 mamagalh  2019      0 Aug  4 20:10 out
# -rw-r--r--   1 mamagalh  2019      0 Aug  4 18:19 outfile
# -rw-r--r--   1 mamagalh  2019    315 Aug  4 20:00 ouut
# -rw-r--r--   1 mamagalh  2019   2287 Aug  4 19:05 pathing.c
# -rw-r--r--   1 mamagalh  2019   2515 Aug  4 19:05 pipe.c
# -rwxr-xr-x   1 mamagalh  2019  21988 Aug  4 20:07 pipex
# -rw-r--r--   1 mamagalh  2019   1629 Aug  4 18:10 pipex.h
# -rw-r--r--   1 mamagalh  2019   1060 Aug  4 20:00 test.sh
# bash-3.2$ 