function test_function()
   m = [ 1, 2; 3, 4; 5, 6 ]
   v = [ 1, 2, 3, 4, 5, 6 ]
   p = { 1, 2, 3, 4, 5, 6 }
   g = { 'a', 'b', 'c' }
   li_sp = linspace(1, 10, 100)
   lo_sp = logspace(1, 10, 10)
   mynum = 123
   zeros(4)
   zeros(1, 3)
   zeros(5, 1)
   zeros(3, 2)
   6 * ones(6)
   ident = eye(2)
   eye(4, 3)
   ident = fliplr(ident)
   ident = flipud(ident)
   v = v((1+1):4)
end
