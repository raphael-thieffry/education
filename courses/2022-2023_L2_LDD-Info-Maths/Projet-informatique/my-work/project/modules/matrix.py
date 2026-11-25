from pprint import pprint

import random as r
def random_int_list(n, bound, number_generator=(r.randint)):
    return [ number_generator(0,bound+1) for i in range(n)]

def random_int_matrix(n,bound,null_diag=True, number_generator=(r.randint)): 
    lst=[ random_int_list(n,bound, number_generator) for i in range(n)]
    if not null_diag:
        return lst
    else:
        for i in range(n):
            lst[i][i]=0
        return lst

def random_symetric_int_matrix(n,bound,null_diag=True, number_generator=(r.randint)):
    lst=[[0 for _ in range(n)] for _ in range(n)]
    for k in range(n):
        for i in range(k,n):
            lst[k][i]= number_generator(0,bound+1)
            lst[i][k]= lst[k][i]
    if not null_diag:
        return lst
    else:
        for i in range(n):
            lst[i][i]=0
        return lst
        

def random_oriented_int_matrix(n,bound,null_diag=True, number_generator=(r.randint)):
    lst= random_int_matrix(n,bound,null_diag, number_generator)
    for i in range (n):
        for j in range(i,n):
            if r.randint(0,2)==0:
                tmp = lst[i][j]
                lst[i][j] = 0
                lst[j][i] = tmp
            else:
                tmp = lst[j][i]
                lst[j][i] = 0
                lst[i][j] = tmp
    return lst

def random_triangular_int_matrix(n,bound,null_diag=True, number_generator=(r.randint)):
    lst= random_int_matrix(n,bound,null_diag, number_generator)
    for i in range(n):
        for j in range(i+1,n):
            lst [j][i]=0
    return lst




def test_random():
    # pprint(random_int_list(10, 5))
    # pprint(random_int_matrix(3, 5, False))
    # pprint(random_int_matrix(3, 5))
    # pprint(random_int_matrix(6, 5))
    
    # pprint(random_symetric_int_matrix(5,6,False))
    # pprint(random_symetric_int_matrix(5,6))
    #pprint(random_oriented_int_matrix(5,6,False))
    #pprint(random_oriented_int_matrix(4,6))
    pprint(random_triangular_int_matrix(5,5))



if __name__=="__main__":
    test_random() 