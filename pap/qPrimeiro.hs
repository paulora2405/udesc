primeiro :: (a -> Bool) -> [a] -> Maybe a
-- base
primeiro f [] = Nothing
-- recursivo
primeiro f (x : xs)
  | f x = Just x
  | otherwise = primeiro f xs