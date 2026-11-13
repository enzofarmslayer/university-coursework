def interpret(uttryck, tolkning): 

    if isinstance(uttryck, str):
        if(uttryck == "true" or uttryck == "false"):
            return uttryck
        elif uttryck in tolkning:
                return tolkning[uttryck]
            
    if uttryck[0] == "NOT":
        inre_uttryck = (interpret(uttryck[1], tolkning))
        if inre_uttryck == "true":
            return "false"
        else:
            return "true"
    
    if uttryck[1] == "OR":
        första_uttryck = interpret(uttryck[0], tolkning)
        andra_uttryck = interpret(uttryck[2], tolkning)
        if första_uttryck == "true" or andra_uttryck == "true":
            return "true"
        else:
            return "false"

    if uttryck[1] == "AND":
        första_uttryck = interpret(uttryck[0], tolkning)
        andra_uttryck = interpret(uttryck[2], tolkning)
        if första_uttryck == "true" and andra_uttryck == "true":
            return "true"
        else:
            return "false"

#print(interpret(["cat", "AND", "ball"],{"cat": "false", "ball": "true"}))

