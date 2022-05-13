aaa = ["aaa", "echo aaa"]
bbb = ["bbb", "echo bbb"]
ccc = ["ccc", "echo ccc"]

op = [" || ", " && ", " ; "]

for a in aaa:
    for b in bbb:
        for c in ccc:
            for i in range(len(op)):
                for j in range(len(op)):
                    str = a + op[i] + b + op[j] + c
                    print(str)
                    print("echo $?")
