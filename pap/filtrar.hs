filtrar :: (a -> Bool) -> [a] -> [a]
-- caso base
filtrar _ [] = []
-- caso recursivo
filtrar func (x : xs)
  | func x = x : filtrar func xs
  | otherwise = filtrar func xs

verificaImpar :: Int -> Bool
verificaImpar n = (n `mod` 2) == 1