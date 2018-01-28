PROGRAM
  = _ COMMENT* _ v:VERSION _ COMMENT* _ expr:EXPRESSION* {
  	return {
    	version: v,
        body: expr
    }
  }
 
EXPRESSION 
 = COMMENT _ {return null}
 / e:EXPR _ SEMICOLON _ COMMENT* _ {return e}
 / e:GATE _ COMMENT* _ {return e}
 
EXPR 
 = INCLUDE 
 / MEASURE
 / RESET
 / BARRIER
 / REG 
 / CNOT_GATE 
 / UNITARY_GATE 
 / OPAQUE_GATE
 / GATE 
 / APPLY_GATE 
 
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
  	type: "application",
    name: 'cnot',
    argument: [a,b]
  }}
  
MEASURE = "measure" _ a:ARGUMENT _ "->" _ b:CARGUMENT
  {return {
  	type: "measure",
    arguments: [a, b]
  }}
  
RESET = "reset" _ a:ARGUMENT
  {return {
  	type: "reset",
    arguments: a
  }}
  
BARRIER = "barrier" _ a:ARGUMENT_LIST
  {return {
  	type: "reset",
    arguments: a
  }}

OPAQUE_GATE = "opaque" _ name:LOWERCAMELCASE _ params:("(" _ ps:ARGUMENT_LIST _ ")" {return ps})? _ args:ARGUMENT_LIST 
  {return {
  	type: "gate",
    name: name,
    argument: args,
    params: params,
    body: []
  }}
  
GATE = "gate" _ name:LOWERCAMELCASE _ params:("(" _ ps:ARGUMENT_LIST _ ")" {return ps})? _ args:ARGUMENT_LIST _ "{" _ expr:EXPRESSION* _ "}"
  {return {
  	type: "gate",
    name: name,
    argument: args,
    params: params || [],
    body: expr.filter(function(x) {
    	return x !== null
    })
  }}
  
APPLY_GATE = name:LOWERCAMELCASE _ params:("(" _ ps:MATH_EXPR_LIST _ ")" {return ps})? _ args:ARGUMENT_LIST
  {return {
  	type: 'application',
    name: name,
    params: params || [],
    argument: args
  }}
  
UNITARY_GATE = "U" _ "(" _ params:MATH_EXPR_LIST _ ")" _ a:ARGUMENT
  { return {
  	type: "unitary-gate",
    params: params,
    argument: a
  }}

QUBIT = reg:LOWERCAMELCASE _ "[" _ index:INT _ "]" 
  { return {
  	type: "qubit",
    name: reg,
    argument: index
  }}
  
BIT = reg:LOWERCAMELCASE _ "[" _ index:INT _ "]" 
  { return {
  	type: "bit",
    name: reg,
    argument: index
  }}
  
ARGUMENT = (QUBIT/LOWERCAMELCASE)

ARGUMENT_LIST 
  = h:ARGUMENT _ "," _ t:ARGUMENT_LIST  {return [h].concat(t)}
  / ARGUMENT
  
CARGUMENT = (BIT/LOWERCAMELCASE)
  
// MATH EXPRESSION ==========================
MATH_EXPR_LIST
  = h:MATH_EXPR _ "," _ t: MATH_EXPR_LIST {return [h].concat(t)}
  / MATH_EXPR

MATH_EXPR
  = additive

additive
  = _ left:subtractive _ "+" _ right:additive { return left + "+" + right; }
  / subtractive

subtractive
  = left:multiplicative _ "-" _ right:additive { return left + "-" + right }
  / multiplicative

multiplicative
  = left:divisable _ "*" _ right:additive { return left + "*" + right }
  / divisable

divisable
  = left: exponential _ "/" _ right:additive { return left + "/" + right }
  / exponential

exponential
  = left: negative _ "^" _ right:additive { return "pow(" + left + ", " + right + ")" }
  / negative

negative
  = "-" _ right:func { return "-" + right }
  / func

func
  = op:UNARYOP _ "(" _ exp:additive _ ")" _ { return op + "(" + exp + ")" }
  / primary
  
primary
  = NUMBER
  / LOWERCAMELCASE
  / "(" additive:additive ")" { return additive; }

// UTILITIES ================================
COMMENT = "//" [^\n\r]* _

INT = d:[0-9]+ { return parseInt(d, 10)}

SEMICOLON = ";"

CHAR = [a-zA-Z]

LOWERCAMELCASE = f:[a-z] r:[a-zA-Z0-9]* {return f + r.join("")}

UPPERCAMELCASE = f:[A-Z] r:[a-zA-Z0-9]* {return f + r.join("")}

NUMBER "real"
  = ("pi" / "PI" / "Pi") { return Math.PI }
  / INT
  / digits:[0-9]+ { return parseInt(digits.join(""), 10); }

UNARYOP
  = "sin"
  / "cos"
  / "tan"
  / "exp"
  / ("ln" / "log") {return "log"}
  / "sqrt"

// optional whitespace
_  = [ \t\r\n]*

// mandatory whitespace
__ = [ \t\r\n]+
