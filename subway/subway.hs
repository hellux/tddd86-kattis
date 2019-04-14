import Data.List (sort)

{--
data Subway = Subway [Subway] deriving (Show)
type SubwayZipper = (Subway, [Subway])

newSub :: SubwayZipper -> SubwayZipper
newSub (current, bs) = (Subway [], current:bs)
prevSub :: SubwayZipper -> SubwayZipper
prevSub (current, (Subway above):bs) = (Subway (current:above), bs)

createSubway :: String -> SubwayZipper
createSubway = foldl f (Subway [], []) where
    f :: SubwayZipper -> Char -> SubwayZipper
    f zipper '0' = newSub zipper
    f zipper '1' = prevSub zipper

--}

depths :: String -> [Integer]
depths = sort . snd . foldl f (0, []) where
    f :: (Integer, [Integer]) -> Char -> (Integer, [Integer])
    f (depth, ds) '0' = (depth+1, depth:ds)
    f (depth, ds) '1' = (depth-1, ds)

compareExploration :: (String, String) -> Bool
compareExploration (exp1, exp2) = (depths exp1) == (depths exp2)

solve :: [String] -> [Bool]
solve (_:cases) = map compareExploration (pairwise cases) where
    pairwise [] = []
    pairwise (e1:e2:es) = (e1, e2):pairwise es

writeOutput :: [Bool] -> String
writeOutput = unlines . map f where
    f :: Bool -> String
    f True = "same"
    f False = "different"

main = interact (writeOutput . solve . words)
