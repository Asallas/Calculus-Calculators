#Rules

#elementary function derivative
func = {['exp()', 'exp()'], ['x^p', 'p * x^(p - 1)'],
        ['sin()', 'cos()'], ['cos()', 'sin()'], ['ln()', '1 / x'],
        ['log_a()', '1 / (x * ln(a))']}

def power(q, p):
    q1 = p * q
    return q1

def chain(f, g):
    
    pass

def quotient(f, g):
    pass

def product(f, g):
    pass

#Assume expression given is a valid algebraic expression of elementary functions
def derivative(a):
    if(isinstance(a, str) != True):
        return 'Error'
    
    p = False           #Boolean for parentheses existence
    num = 0             #Number of terms
    num1 = 0
    terms = []
    operations = []
    
    for i in a:
        if ( (i == '+' or i == '-') and p):
            num += 1
            operations[num1] = a
            num1 = num1 + 1
        
        else :
            terms[num] = a
            if (a == '('):
                p = True
            elif(a == ')'):
                p = False

    for i in terms:
        h = terms[i]
        values = []
        count = 0
        for j in h:
            values[count] = j
            count = count + 1
        
            
                
            
    
    
    