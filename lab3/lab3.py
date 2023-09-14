# Här kan du skriva programkod för labb 3.
#
# Programkoden kan t.ex. också delas upp i flera filer, men
# i så fall behöver du se till att de adderas till Git.

#Labb 3A
import math

board = {}

def new_board():
    return {}

def is_free(board, x, y):
    if (x,y) in board:
        return False
    else:
        return True

def place_piece(board, x, y, player):
    if is_free(board, x, y):
        board[(x,y)] = player
        return True
    else:
        return False
         
def get_piece(board, x, y):
    if is_free(board, x, y):
        return False
    else:
        return (board[(x,y)])

def remove_piece(board, x, y):
    if is_free(board, x, y):
        return False
    else:
        board.pop((x,y))
        return True
    
def move_piece(board, x1, y1, x2, y2):
    if is_free(board, x1, y1) or is_free(board, x2, y2):
        board[(x2,y2)] = board[(x1,y1)]
        board.pop((x1,y1))
        return True
    else:
        return False
    
def count(board, z, size, player):
    sum = 0
    i = 0
    
    if z == "column":
        i = 0
    else:
        i = 1

    for key in board:
        if key[i] == size and board[key] == player:
            sum += 1
    return sum

def nearest_piece(board, x, y):
    distanceDic = {}
    distanceList = []

    for key in board:
        distanceDic[key] = 0
    
    for key in distanceDic:
        z = (key[0] - x)**2 + (key[1] - y)**2
        distance = math.sqrt(z)
        distanceList.append(distance)
        distanceDic[key] = distance

    distanceList.sort()
    for key in distanceDic:
        if distanceDic[key] == distanceList[0]:
            return key

board = new_board()
print(is_free(board, 500, 100))           
# print(place_piece(board, 500, 100, "spelare1"))
# print(place_piece(board, 1, 100, "spelare2"))
# print(place_piece(board, 500, 100, "spelare2"))                           
# print(place_piece(board, 500, 200, "spelare2"))
# print(is_free(board, 500, 100))
# print(get_piece(board, 500, 100))
# print(get_piece(board, 666,666))
# print(remove_piece(board, 500, 100))              
# print(remove_piece(board, 1, 1))           
# print(is_free(board, 500, 100))
# print(move_piece(board,  500, 200, 500, 100))    
# print(get_piece(board, 500, 100))
# print(count(board, "column", 500, "spelare2"))   
# print(count(board, "row", 100, "spelare2")) 
# print(nearest_piece(board, 500, 105))   

#Labb3B

def fact(x, stop):
    if x == 0:
        return 1 
    elif stop == 1:
        return x
    else:
        return x * fact(x-1,stop-1)

def comb(n, k):
    stop = n-k
    sum = fact(n,stop)//fact(stop,stop)
    return sum

#print(comb(1000,800))
