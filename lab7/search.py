from match import match
from books import db

def search(pattern, db):
    
    if not isinstance(pattern, list) or not isinstance(db, list):
        raise TypeError("Pattern and db must both be lists.")
    
    result = []
    for item in db:
        if match(item, pattern): result.append(item)

    return result

# pattern = [['författare', ['&', 'zelle']], ['titel', ['--', 'python', '--']], ['år', '&']]
# result = search(pattern, db)
# print(result)