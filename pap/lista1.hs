concatenacao :: [a] -> [a] -> [a]
concatenacao x y = x ++ y

pertence :: Eq a => Int -> [a] -> Bool
pertence x y = True

intersecao :: Eq a => [a] -> [a] -> [a]
intersecao x y = x

inverso :: [a] -> [a]
inverso x = x

fatorial :: Integral a => a -> a
fatorial 0 = 1
fatorial n = n * fatorial (n - 1)
