import qualified Data.Set as Set
import Data.Function (on)

data Subway = Subway (Set.Set Subway) deriving (Show, Ord, Eq)
type SubwayZipper = (Subway, [Subway])

newSub :: SubwayZipper -> SubwayZipper
newSub (current, bs) = (Subway Set.empty, current:bs)
prevSub :: SubwayZipper -> SubwayZipper
prevSub (current, (Subway above):bs) = (Subway (Set.insert current above), bs)

createSubway :: String -> SubwayZipper
createSubway = foldl f (Subway Set.empty, []) where
    f :: SubwayZipper -> Char -> SubwayZipper
    f zipper '0' = newSub zipper
    f zipper '1' = prevSub zipper

compareExploration :: String -> String -> Bool
compareExploration = (==) `on` createSubway

solve :: [(String, String)] -> [Bool]
solve = map (uncurry compareExploration)

-- convert single input string to a list pairs of exploration strings to
-- compare
parseInput :: String -> [(String, String)]
parseInput (_:cases) = pairwise $ words cases where
    pairwise [] = []
    pairwise (e1:e2:es) = (e1, e2):pairwise es

-- convert list of bools to single string one case per line
formatOutput :: [Bool] -> String
formatOutput = unlines . map f where
    f :: Bool -> String
    f True = "same"
    f False = "different"

main = interact (formatOutput . solve . parseInput)
