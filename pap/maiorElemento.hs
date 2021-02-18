maiorElemento :: Ord a => [a] -> a
-- caso base
maiorElemento [x] = x
-- caso recursivo
maiorElemento (x : y : xs)
  | x > y = maiorElemento $ x : xs
  | otherwise = maiorElemento $ y : xs
-- caso invalido
maiorElemento [] = error "Caso inválido"
