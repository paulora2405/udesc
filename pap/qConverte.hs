converte :: [Int] -> [String]
--base
converte [] = []
-- recursivo
converte x =
  mapear show x

mapear :: (a -> b) -> [a] -> [b]
-- base
mapear f [x] = [f x]
-- recursivo
mapear f (x : xs) =
  f x : mapear f xs