export CAT='cat -e'
export LS='ls -a'

chmod -R 777 tmp*
rm -rf tmp*
rm -rf .tmp*
rm -rf ..tmp*

# 実行ファイル
cat << EOF > tmp.c
#include <stdio.h>
int main() {
    printf("hello\n");
}
EOF
gcc tmp.c -o tmp.out
cp tmp.out tmp000.out; chmod 000 tmp000.out;

# ディレクトリ
mkdir tmpdir
mkdir tmpdir000
mkdir tmpout
mkdir tmpout000

# 実行ファイル
cp tmp.out tmpdir/
cp tmp.out tmpdir000/
cp tmp.out tmpout/
cp tmp.out tmpout000/

# chmod
chmod 000 tmpout000/tmp.out
chmod 000 tmpdir000

# 隠しファイル
touch .tmp
touch .tmp1
touch ..tmp
touch ..tmp1
touch ..tmp.tmp
