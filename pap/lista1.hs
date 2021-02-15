concatenacao :: [a] -> [a] -> [a]
-- base
concatenacao [] ys = ys
-- recursivo
concatenacao (x : xs) ys =
  x : concatenacao xs ys

pertence :: Eq a => a -> [a] -> Bool
-- base
pertence x [] = False
-- recursivo
pertence x (y : ys) =
  (x == y) || pertence x ys

-- if x == y then True else pertence x ys

intersecao :: Eq a => [a] -> [a] -> [a]
-- base
intersecao x [] = []
intersecao [] y = []
-- recursivo
intersecao (x : xs) y =
  if pertence x y then x : intersecao xs y else intersecao xs y

inverso :: [a] -> [a]
-- base
inverso [] = []
-- recursivo
inverso (x : xs) =
  concatenacao (inverso xs) [x]

primeiros :: Int -> [a] -> [a]
-- base
primeiros n [] = []
primeiros 0 _ = []
-- recursivo
primeiros n (x : xs) =
  x : primeiros (n -1) xs

ultimos :: Int -> [a] -> [a]
-- base
ultimos n [] = []
ultimos 0 _ = []
-- recursivo
ultimos n x =
  inverso (primeiros n (inverso x))

binParaInt :: String -> Int
-- base
binParaInt "0" = 0
binParaInt "1" = 1
-- recursivo
binParaInt ('0' : xs) =
  binParaInt xs
binParaInt ('1' : xs) =
  2 ^ length xs + binParaInt xs
binParaInt xs =
  error "Valor nao é binario"

-- --Versão Gaspa ( versao mamaco )
-- strParaInt :: Char -> Int
-- strParaInt '0' = 0
-- strParaInt '1' = 1

-- potencial :: Int -> Int -> Int
-- potencial _ 0 = 1
-- potencial 0 _ = 0
-- potencial n e = n * potencial n (e -1)

-- tam :: String -> Int
-- tam [] = 0
-- tam (x : xs) = 1 + tam xs

-- binParaInt :: String -> Int
-- binParaInt [] = 0
-- binParaInt (x : xs) = strParaInt x * potencial 2 (tam xs) + binParaInt xs

-- Versão Gaspa ( versao top )

-- binParaInt :: Int -> Int
-- binParaInt 0 = 0
-- binParaInt i = 2 * binParaInt (i `div` 10) + (i `mod` 10)

intParaBin :: Int -> String
-- base
intParaBin 0 = "0"
intParaBin 1 = "1"
intParaBin n
  | mod n 2 == 0 = concatenacao (intParaBin (div n 2)) "0"
  | otherwise = concatenacao (intParaBin (div n 2)) "1"

menorValor :: Ord a => [a] -> a
-- base
menorValor [x] = x
-- recursivo
menorValor (x : xs) =
  min x (menorValor xs)
-- erro
menorValor [] = error "Lista nao pode ser vazia"

removerPrimeiro :: Eq a => [a] -> a -> [a]
-- base
removerPrimeiro [] _ = []
-- recursivo
removerPrimeiro (x : xs) y
  | x == y = xs
  | otherwise = concatenacao [x] (removerPrimeiro xs y)

ordenar :: Ord a => [a] -> [a]
-- base
ordenar [x] = [x]
-- recursivo
ordenar xs =
  menorValor xs : ordenar (removerPrimeiro xs (menorValor xs))
