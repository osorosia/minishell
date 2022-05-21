export CAT='cat -e'
export LS='ls -a'

rm -rf tmp*

# ディレクトリ
mkdir tmpdir

# 実行ファイル
cat << EOF > tmp.c
#include <stdio.h>
int main() {
    printf("hello\n");
}
EOF
gcc tmp.c -o tmp.out
cp tmp.out tmp000.out; chmod 000 tmp000.out;

# 環境変数
export PATH="${PATH}:${PWD}"
