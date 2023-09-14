
def split_it(message, seq1 = [], seq2 = []):

    for elem in message:
        if elem.islower() or elem == "." or elem == "_":
            seq1.append(elem)
        elif elem.isupper() or elem == " " or elem == "|":
            seq2.append(elem)
        else:
            continue
    
    return ''.join(seq1), ''.join(seq2)

#first, second = split_it("hTEeSj_CO")
#print(first, second)

def split_rec(message, seq1='', seq2='', i=0):
    
    if i == len(message):
        return (seq1, seq2)
    
    elem = message[i]

    if elem.islower() or elem == '.' or elem == '_':
        seq1 += elem
    elif elem.isupper() or elem == " " or elem == "|":
        seq2 += elem

    return split_rec(message, seq1, seq2, i + 1)

#print(split_rec("'lMiED)teD5E,_hLAe;Nm,0@Dli&Eg ,#4aI?rN@T§&e7#4E #<(S0A?<)NT8<0'"))