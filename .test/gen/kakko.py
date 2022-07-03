aaa = ["aaa", "echo aaa"]
bbb = ["bbb", "echo bbb"]
ccc = ["ccc", "echo ccc"]

op = [" || ", " && ", " ; "]

for a in aaa:
    for b in bbb:
        for c in ccc:
            for i in range(len(op)):
                for j in range(len(op)):
                    for left in range(3):
                        for right in range(left, 3):
                            str = ''
                            if left == 0:
                                str += '('
                            str += a
                            if right == 0:
                                str += ')'

                            str += op[i]

                            if left == 1:
                                str += '('
                            str += b
                            if right == 1:
                                str += ')'

                            str += op[j]

                            if left == 2:
                                str += '('
                            str += b
                            if right == 2:
                                str += ')'
                            
                            print(str)
                            print("echo $?")
