PROGRAM
  = _ COMMENT* _ v:VERSION _ COMMENT* _ expr:EXPRESSION* {
  	return {
    	version: v,
        body: expr
    }
  }
 
EXPRESSION 
 = e:EXPR _ SEMICOLON _ COMMENT* _ {return e}
 
EXPR 
 = INCLUDE / REG / CNOT_GATE / UNITARY_GATE
 
VERSION = "OPENQASM" _ major:INT "." minor:INT SEMICOLON
  { return major + "." + minor}

INCLUDE = "include" _ '"' f:[_A-Za-z0-9./]* '"'
  { return {
  	type: "include",
    argument: f.join("")
  } }

REG = type:("creg"/"qreg") _ name:LOWERCAMELCASE _ "[" _ n:INT _ "]"
  { return {
  	type: type,
    name: name,
    argument: n
  }}
  
CNOT_GATE = "CX" _ a:ARGUMENT _ "," _ b:ARGUMENT
  { return {
  	type: "cnot",
    argument: [a,b]
  }}
  
UNITARY_GATE = "U" _ "(" _ theta:MATH_EXPR _ "," _ phi:MATH_EXPR _ "," _ lambda:MATH_EXPR _ ")" _ ARGUMENT
  { return {
  	type: "gate",
    data : [theta, phi, lambda],
    argument: 3
  }}

QUBIT = reg:LOWERCAMELCASE _ "[" _ index:INT _ "]" 
  { return {
  	type: "qubit",
    data: reg,
    argument: index
  }}
  
ARGUMENT = (QUBIT/LOWERCAMELCASE)
  
// MATH EXPRESSION ==========================
MATH_EXPR
  = additive

additive
  = _ left:subtractive _ "+" _ right:additive { return left + right; }
  / subtractive

subtractive
  = left:multiplicative _ "-" _ right:additive { return left - right }
  / multiplicative

multiplicative
  = left:exponential _ "*" _ right:additive { return left * right; }
  / exponential

exponential
  = left: negative _ "^" _ right:additive { return Math.pow(left, right) }
  / negative

negative
  = "-" _ right:func { return -right }
  / func

func
  = op:unaryop _ "(" _ exp:additive _ ")" { return op(exp) }
  / primary
  
primary
  = number
  / "(" additive:additive ")" { return additive; }

// UTILITIES ================================
COMMENT = "//" [^\n\r]* _

INT = d:[0-9]+ { return parseInt(d, 10)}

SEMICOLON = ";"

CHAR = [a-zA-Z]

LOWERCAMELCASE = f:[a-z] r:[a-zA-Z0-9]* {return f + r.join("")}

UPPERCAMELCASE = f:[A-Z] r:[a-zA-Z0-9]* {return f + r.join("")}


number "real"
  = ("pi" / "PI" / "Pi") { return Math.PI }
  / INT
  / digits:[0-9]+ { return parseInt(digits.join(""), 10); }

unaryop
  = "sin" { return Math.sin } 
  / "cos" { return Math.cos }
  / "tan" { return Math.tan }
  / "exp" { return Math.exp }
  / ("ln" / "log") { return Math.log }
  / "sqrt" { return Math.sqrt }

// optional whitespace
_  = [ \t\r\n]*

// mandatory whitespace
__ = [ \t\r\n]+
