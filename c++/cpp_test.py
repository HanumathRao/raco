from raco.datalog.grammar import parse
from raco.scheme import Scheme
from raco.catalog import ASCIIFile
from raco.language import PythonAlgebra, PseudoCodeAlgebra, CCAlgebra#, ProtobufAlgebra
from raco.algebra import LogicalAlgebra
from raco.compile import compile, optimize, common_subexpression_elimination, showids
import scan_code as sc

query = 'A(a1,a2) :- R(a1,x),S(x,y),T(y,z),U(z,a2),z=100,y=50'
parsedprogram = parse(query)
exprs = parsedprogram.toRA()
ra = exprs
result = optimize(ra, target=CCAlgebra, source=LogicalAlgebra)
physicalplan = result
print physicalplan[0][1].leftconditions
print physicalplan[0][1].rightconditions
print physicalplan[0][1].finalcondition
tmp = sc.cpp_code(physicalplan,'A')
tmp.gen_code()
