ultimoElemento :: [a] -> a
-- caso base
ultimoElemento [x] = x
-- caso recursivo
ultimoElemento (x : xs) = ultimoElemento xs
-- caso invalido
ultimoElemento [] = error "Caso inválido"