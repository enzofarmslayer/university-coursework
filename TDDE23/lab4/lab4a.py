
def split_it(message):
    
    seq1 = ""
    seq2 = ""

    for elem in message:
        if elem.islower() or elem == "." or elem == "_":
            seq1 += elem
        elif elem.isupper() or elem == " " or elem == "|":
            seq2 += elem
    
    return (seq1, seq2)

#first, second = split_it("hTEeSj_CO")
#print(first, second)

def split_rec(message):
    if message == "":
        return ("", "")

    if message[0].islower() or message[0] == "_" or message[0] == ".":
        first, second = split_rec(message[1:])
        return (message[0] + first, second)
    elif message[0].isupper() or message[0] == " " or message[0] == "|":
        first, second = split_rec(message[1:])
        return (first, message[0] + second)
    else:
        return split_rec(message[1:])

# message = "'lMiED)teD5E,_hLAe;Nm,0@Dli&Eg ,#4aI?rN@T§&e7#4E #<(S0A?<)NT8<0'"
# result = split_rec(message)
# print(result)
